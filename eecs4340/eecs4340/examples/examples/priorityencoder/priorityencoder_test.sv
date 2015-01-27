module priorityencoder_test();

	reg [15:0] inp;
	wire [3:0] out;
	wire valid;

	priorityencoder myencoder(
		.inp_i(inp),
		.out_o(out),
		.valid_o(valid)
	);

	initial begin
	$vcdpluson;
	// making input signals 0 at start
	inp = 16'd0;
	#2 $display("value of valid signal is %d\n",valid);

	#5 inp = 16'h0001;
	#2 $display("value of out for 1st set of inputs is %h\n",out);
	$display("value of valid signal is %d\n",valid);

	#5 inp = 16'h0010;
	#2 $display("value of out for 2st set of inputs is %h\n",out);
	$display("value of valid signal is %d\n",valid);

	#5 inp = 16'h0100;
	#2 $display("value of out for 3st set of inputs is %d\n",out);
	$display("value of valid signal is %d\n",valid);

	end

endmodule