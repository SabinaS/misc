module eff_test();

wire [31:0] data_o;
wire valid_o;
reg [31:0] data_i;
reg write_enable_i;
reg clk;
reg rst; 

eff test_eff(.*);

always #1 clk = ~clk;

initial begin
	$vcdpluson;
	clk = '0;
	rst = '0;
	write_enable_i = '0;
	data_i = '0;

	// Wait a cycle and reset
	@(posedge clk)#1 rst = '1;
	@(posedge clk)#1 rst = '0; 
	
	// We should read all zeroes initially
	$display("Reg data: 0x%h\n reg valid: 0x%h\n", data_o, valid_o);
	
	// Write something
	@(posedge clk)#1 write_enable_i = '1;
	data_i = 32'd56;
	@(posedge clk)#1 write_enable_i = '0;
	
	// Read it back
	$display("Reg data: 0x%h\n reg valid: 0x%h\n", data_o, valid_o);

	// Reset again
	@(posedge clk)#1 rst = '1;
	@(posedge clk)#1 rst = '0;
	
	// Confirm reset
	$display("Reg data: 0x%h\n reg valid: 0x%h\n", data_o, valid_o);
	
	// Write something again
	@(posedge clk)#1 write_enable_i = '1;
	data_i = 32'd32;
	@(posedge clk)#1 write_enable_i = '0;
	// Read it back
	$display("Reg data: 0x%h\n reg valid: 0x%h\n", data_o, valid_o);
	
	// Write another something
	@(posedge clk)#1 write_enable_i = '1;
	data_i = 32'd50;
	@(posedge clk)#1 write_enable_i = '0;
	// Read it back
	$display("Reg data: 0x%h\n reg valid: 0x%h\n", data_o, valid_o);

	@(posedge clk)#1 $finish; 
	
end

endmodule
