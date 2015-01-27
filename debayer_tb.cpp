 #include "debayer_tb.h"
 
 extern ifstream input;
 extern ifstream golden_output;
 extern int num_samples;
 
 
 void debayer_tb::dmac()
 {
     /**
      * Implement the testbench as a single process that replaces a DMA
      * controller. DMA allows to transfer data from the main memory
      * (usually DRAM) to the local memory of a device (a scratch pad).
      * Debayer must use its interface's signals to tell the DMAC which
      * is the initial pixel to transfer and how many pixels are required
      * to process the next token.
      * 1. accelerator_if: process all pixels in one burst
      * 2. circular_buffer: process one row per burst (notice taht to start
      *                     you must firt read five rows!)
      *
      * Your DMAC should do the following (partialy implemented for you)
      * a. De-activate the DUT reset active
      * b. Read input.txt to determine input image and its size
      * c. Configure the DUT with the image size and set conf_done signal
      * d. Wait for read/write requests and handle them properly
      *    Use FlexChannels with bufdin and bufdout initators to pass image
      *    pixels to/from DUT
      * e. Check for debayer_done(), which should be set when the DUT has
      *    comleted one full image. At this point the TB must set the DUT
      *    reset for at least one clock cycle. Next TB should validate the
      *    output by reading golden output images. Finally TB should start
      *    over from step a. until all of the images listed in input.txt
      *    have been processed. Make sure to print a time stamp every time
      *    one image is complete.
      * f. Call sc_stop() and print simulation summary. (already implemented)
      */
 
     // RESET
     int count = 0;
     bool finished = true;
     int image_size = 0;
     int bayer_size = 0;
     int debayer_size = 0;
     rst_dut.write(false);
     wait();
 
 
     while(count < num_samples) {
 
         if (finished && !rst_dut.read()) {
             // Read input and configure
             //wait();
             cout << "rpocessing image" << endl;
             std::string test_filename;
             input >> std::dec >> image_size;
             cout << "got image_size" << image_size << endl;
             input >> test_filename; //mimicing solutions
             cout << "got test_filename" << test_filename << endl;
 
             bayer_size = image_size*image_size;
             debayer_size = (image_size-2*PAD)* (image_size-2*PAD);
 
             cout << "setting to zero" << endl;
             //set everything to zero first
             for(int i = 0; i < bayer_size; i++){
                 bayer[i] = 0;
             }
             for(int i = 0; i < debayer_size; i++){
                 debayer[i].b = 0;
                 debayer[i].g = 0;
                 debayer[i].r = 0;
             }
 
             cout << "about to read image" << endl;
 
             //read the image
             read_image_file(bayer, sizeof(u16), test_filename.c_str(), ".", sizeof(u16)*bayer_size);
 
             //write the signals
             finished = false;
             conf_size.write(image_size);
             rst_dut.write(true);
             conf_done.write(true);
             bufdin.reset_put();
             bufdout.reset_get();
 
         }// end if
 
         cout << "read all images" << endl;
 
         do { wait(); }
         while (!rd_request.read() && !wr_request.read() && !debayer_done.read());

	  cout << "waited" << endl;
 
         if (debayer_done.read()) {
             cout << "TB: DEBAYER done @ " << sc_time_stamp() << endl;
             // Reset DUT
             rst_dut.write(false);
             wait();
 
             // Write output file and validate
             std::string exp_filename;
             golden_output >> exp_filename;
             std::stringstream res_filename; //mimicking solutions
             res_filename << "../output/" << std::setw(4) << std::setfill('0') << count << ".bin";
 
             cout << "writing to file" << exp_filename << endl;
 
             write_image_file((void *) debayer, sizeof(u16),
                     res_filename.str().c_str(), ".", image_size-2*PAD,image_size-2*PAD, 3);
 
 
             for(int i = 0;i<((image_size-2*PAD)*(image_size-2*PAD));i++) {
                 gold_debayer[i].b = 0;
                 gold_debayer[i].g = 0;
                 gold_debayer[i].r = 0;
             }
 
             cout << "reading the golden output" << endl;
 
             read_image_file((void *) gold_debayer, sizeof(rgb_pixel),
                     exp_filename.c_str(), ".",
                     sizeof(rgb_pixel)*(image_size-2*PAD)*(image_size-2*PAD));
 
             for (int i = 0; i <( (image_size-2*PAD)*(image_size-2*PAD)); i++) {
                 if (gold_debayer[i].b != debayer[i].b ||
                         gold_debayer[i].g != debayer[i].g ||
                         gold_debayer[i].r != debayer[i].r) {
                     mismatches++;
                     break;
                 }
             }
 
             // Process next image if any
             count++;
             finished = true;
             cout << "finished with test bench" << endl;
             continue;
         }//end debayer_done.read()
 
         cout << "not debayer_done" << endl;
 
         if (rd_request.read()) {
             cout << "more read requests" << endl;
             // Process read request and synchronize with a 4-phases handshake
             rd_grant.write(true);
             int rdlength = rd_length.read();
             int rdindex = rd_index.read();
 
             //wait();
             do{wait();} while(rd_request.read());
 
             cout << "waited some more" << endl;
 
             rd_grant.write(false);
             // Uncomment for debugging (you will need it!)
              cout << "TB: READ BURST; len = " << rdlength
                   << "; index = " << rdindex << endl;
 
             // DMA from memory to DUT
             for(int i = (rdindex*image_size); i<(rdindex*image_size+rdlength); i++){
                 bufdin.put(bayer[i]);
                 wait();
             }
 
         } else {
             // Process write request and synchronize with a 4-phases handshake
 
             int  wrlength = wr_length.read();
             int wrindex = wr_index.read();
 
             cout << "not rd_request" << endl;
             //wait();
             wr_grant.write(true);
             do{wait();} while(wr_request.read());
             cout << "never wr_request" << endl;
             wr_grant.write(false);
             // Uncomment for debugging (you will need it!)
              cout << "TB: WRITE BURST; len = " << wrlength
                   << "; index = " << wrindex << endl;
 
	             // DMA from device to memory
             for(int i = (wrindex*(image_size-2*PAD)); i<(wrindex*image_size+wrlength); i++){
                 debayer[i] = bufdout.get();
                 //cout << "debayed" << endl; 
 
                 wait();
                 //cout << "end debayed" << endl; 
             }
 
         }//end else
 
         cout << "ended else" << endl;
     }//end while
 
     cout << "end while" << endl;
 
     // Stop simulation
     sc_stop();
     cout << "stopped simulation" << endl;
     int errors = getMismatches();     // show the testing summary
     if (errors > 0)
         cout << "Simulation with " << errors << " mismatches." << endl;
     else
         cout << "Simulation successful! @ " << sc_time_stamp() << endl;
     input.close();
     golden_output.close();
 }
	
