module cam_test();

reg read, write, search;
reg [4:0] read_index, write_index;
reg [31:0] write_data, search_data;
wire read_valid, search_valid;
wire [4:0] search_index;
wire [31:0] read_value;
reg clk;
reg rst; 

cam testcam(
	.read_i(read), .read_index_i(read_index), 
	.write_i(write), .write_index_i(write_index), .write_data_i(write_data), 
	.search_i(search), .search_data_i(search_data), 
	.read_valid_o(read_valid), .read_value_o(read_value), 
	.search_valid_o(search_valid), .search_index_o(search_index),
	.*
);

initial begin
	$vcdpluson;
	clk = 0;
	write = 0; 
	read = 0;
	search = 0; 

 	forever begin
	      	#1  clk = ~clk;
 	end
	#1 rst=1;
	#1 rst=0; 
	
	#5 write = 1'b1; 
	write_index = 5'h1;
	write_data = 32'h0000_0001; 
	$display("wrote write_data: %h\n to write_index: %h\n", write_data, write_index); 
	
	#5 write = 1'b0; 
	read = 1'b1;
	read_index = 5'h1;
	$display("read read_value: %h\n and read_valid: %h\n from read_index: %h\n", read_value, read_valid, read_index);

	#5 search = 1'b1;
	search_data = 32'h0000_0001;
	$display("searched for search_data: %h\n and got search_valid: %h\n and search_index: %h\n", search_data, search_valid, search_index); 

	#20 $finish; 
	
end

endmodule
