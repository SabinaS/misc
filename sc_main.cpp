 #endif
 ifstream input;             // input.txt
 ifstream golden_output;     // golden_output.txt
 int num_samples;            // number of input images
 
 int sc_main(int, char **) {
     sc_report_handler::set_actions("/IEEE_Std_1666/deprecated", SC_DO_NOTHING);
 
     debayer dut("dut");
     debayer_tb tb("tb");
 
     input.open("../input/input.txt");
     golden_output.open("../input/golden_output.txt");
     int clk_in;     // T_clk
     int rst_in;     // t_rst
     input >> clk_in >> rst_in >> num_samples;
     cout << "Clock: " << clk_in << " ns; Reset hold: " << rst_in << " ns" << endl;
 
     sc_clock             clk("clk", clk_in, SC_NS);    // clock
     sc_signal<bool>      rst("rst");                   // reset
     sc_signal<bool>      rst_dut("rst_dut");           // reset
 
     sc_signal<unsigned>        rd_index("rd_index");
     sc_signal<unsigned>        rd_length("rd_length");
     sc_signal<bool>            rd_request("rd_request");
     sc_signal<bool>            rd_grant("rd_grant");
     sc_signal<unsigned>        wr_index("wr_index");
     sc_signal<unsigned>        wr_length("wr_length");
     sc_signal<bool>            wr_request("wr_request");
     sc_signal<bool>            wr_grant("wr_grant");
     put_get_channel<u16>       bufdin("bufdin");
     put_get_channel<rgb_pixel> bufdout("bufdout");
     sc_signal<unsigned>        conf_size("conf_size");
     sc_signal<bool>            conf_done("conf_done");
     sc_signal<bool>            debayer_done("debayer_done");
 
     // Declare TB and DUT modules. Make sure CtoS can instantiate the scheduled version
 
     // Connect ports
     dut.clk(clk);
     dut.rst(rst_dut);
     dut.rd_request(rd_request);
     dut.rd_index(rd_index);
     dut.conf_done(conf_done);
     dut.rd_grant(rd_grant);
     dut.wr_request(wr_request);
     dut.rd_length(rd_length);
     dut.wr_index(wr_index);
     dut.conf_size(conf_size);
     dut.wr_grant(wr_grant);
     dut.bufdout(bufdout);
     dut.wr_length(wr_length);
     dut.bufdin(bufdin);
     dut.debayer_done(debayer_done);
 
     tb.clk(clk);
     tb.rst(rst);
     tb.rst_dut(rst_dut);
     tb.bufdout(bufdout);
     tb.rd_request(rd_request);
     tb.rd_index(rd_index);
     tb.rd_length(rd_length);
     tb.wr_length(wr_length);
     tb.rd_grant(rd_grant);
     tb.wr_index(wr_index);
     tb.wr_request(wr_request);
     tb.bufdin(bufdin);
     tb.conf_done(conf_done);
     tb.conf_size(conf_size);
     tb.wr_grant(wr_grant);
     tb.debayer_done(debayer_done);
 
     cout << "here" << endl;
     // Reset and run simulation
     rst.write(false);
     sc_start(rst_in,SC_NS);
 
     cout << "here2" << endl;
 
     rst.write(true);
     cout << "about to start" << endl;
     sc_start();
 
     /**
      * The testbench calls sc_stop() after the last image has been
      * processed. Please notice how the overall latency changes when
      * you add FlexChannels interfaces to connect design submodules.
      * When you will run scheduling with CtoS, please also notice
      * how different micro-architectures translate into different
      * latency/throughput.
      */
 
     return 0;
 }

