#include "debayer_tb.h"

extern ifstream input;
extern ifstream golden_output;
extern int num_samples;

void debayer_tb::dmac()
{

	
	int count = 0;
	int size = 0;
	int num_bayer = 0;
	int num_debayer = 0;
	bool ready = true;

	
	rst_dut.write(false);
	wait();


	while(count < num_samples) {
		if (!rst_dut.read() && ready) {
			
		        cout << "processing next image." << endl;
		        std::string test_filename;

		        input >> std::dec >> size;
		        input >> test_filename;

		        num_bayer = size*size;
		        num_debayer = (size-2*PAD)*(size-2*PAD);
			
			for(int i = 0;i<num_bayer;i++){
				bayer[i] = 0;
			}

			for(int i = 0;i<num_debayer;i++) {
				debayer[i].r = 0;
				debayer[i].g = 0;
				debayer[i].b = 0;
			}

			read_image_file(
				bayer,
				sizeof(u16),
				test_filename.c_str(),
				".",
				sizeof(u16) * num_bayer);

			
			ready = false;
			rst_dut.write(true);
			conf_size.write(size);
			conf_done.write(true);
			bufdin.reset_put();
			bufdout.reset_get();
		}

		do { wait(); }
		while (!rd_request.read() && !wr_request.read() && !debayer_done.read());
		if (debayer_done.read()) {
			cout << "TB: DEBAYER done @ " << sc_time_stamp() << endl;
			
			rst_dut.write(false);
			wait();

			
			std::string exp_filename;
			golden_output >> exp_filename;
			std::stringstream res_filename;
			res_filename << "../output/" << std::setw(4) << std::setfill('0') << count << ".bin";

			cout << "sample #" << count << " @ " << sc_time_stamp();
			cout << " : OUTPUT: " << exp_filename << endl;


			write_image_file((void *) debayer, sizeof(u16),
				res_filename.str().c_str(), ".", size-2*PAD,size-2*PAD, 3);


			for(int i = 0;i<(size-2*PAD)*(size-2*PAD);i++) {
				gold_debayer[i].r = 0;
				gold_debayer[i].g = 0;
				gold_debayer[i].b = 0;
			}

			read_image_file((void *) gold_debayer, sizeof(rgb_pixel),
			                exp_filename.c_str(), ".",
			                sizeof(rgb_pixel) * (size-2*PAD)*(size-2*PAD));

			for (int i = 0; i < (size-2*PAD)*(size-2*PAD); i++) {
			        if (gold_debayer[i].r != debayer[i].r ||
			            gold_debayer[i].g != debayer[i].g ||
			            gold_debayer[i].b != debayer[i].b) {
			                mismatches++;
			                cout << "debayer[" << i << "] doesn't match" << endl;
					cout <<"gold r: " << gold_debayer[i].r << "  your r: " << debayer[i].r << endl;
					cout <<"gold g: " << gold_debayer[i].g << "  your g: " << debayer[i].g << endl;
					cout <<"gold b: " << gold_debayer[i].b << "  your b: " << debayer[i].b << endl;
			                break;
			        }
			}

			
			count++;
			cout << "tb done." << endl;
			ready = true;
			continue;
		}

		if (rd_request.read()) { //1
			
			int index = rd_index.read();
			int length = rd_length.read();
			rd_grant.write(true); //2
			do{wait();} while(rd_request.read()); //3
			rd_grant.write(false); //4

		
			 for(int i = index*size; i<(index*size+length);i++){
			 	bufdin.put(bayer[i]); 
				wait();
			 }
		} else { 
			
			int index = wr_index.read();
			int length = wr_length.read();
			wr_grant.write(true); //2
			do{wait();}while(wr_request.read());//3
			wr_grant.write(false); //4

			
			for(int i = index*(size-2*PAD); i<(index*(size-2*PAD)+length);i++){
				debayer[i] = bufdout.get(); 
				wait();
			}
		}
	}

	
	sc_stop();
	int errors = getMismatches();     // show the testing summary
	if (errors > 0)
		cout << "Simulation with " << errors << " mismatches." << endl;
	else
		cout << "Simulation successful! @ " << sc_time_stamp() << endl;
	input.close();
	golden_output.close();
}

