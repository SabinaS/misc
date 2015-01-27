module cam	(read_i, read_index_i, write_i, write_index_i, write_data_i, search_i,
		search_data_i, read_valid_o, read_value_o, search_valid_o,
		search_index_o, clk, rst);

	parameter WORD_SIZE = 32;
	parameter WORD_BITS = 5;
	parameter NUM_ELEMS = 32;
	parameter PLUS_VALID = WORD_SIZE + 1; 

	input clk;
	input rst;

	input[WORD_SIZE-1:0]	write_data_i;
	input[WORD_SIZE-1:0]	search_data_i;
	input[WORD_BITS-1:0]	read_index_i;
	input[WORD_BITS-1:0]	write_index_i;
	input			read_i;
	input			write_i;
	input			search_i;
	output[WORD_SIZE-1:0]	read_value_o;
	output[WORD_BITS-1:0]	search_index_o;
	output			read_valid_o;
	output			search_valid_o;

// The output array of the FFs. Valid-data (valid is the MSB, data are the LSBs)
wire[(PLUS_VALID)*NUM_ELEMS-1 : 0] ff_out;
// The input array for the FFs. Write_enable-data (Write_enable is the MSB, data are the LSBs)
reg[NUM_ELEMS-1 : 0] write_enables;

// Output holding registers
reg[WORD_SIZE-1:0] read_value;
reg[WORD_SIZE-1:0] search_index;
reg read_valid;
reg search_valid;

assign read_value_o = read_value;
assign search_index_o = search_index;
assign read_valid_o = read_valid;
assign search_valid_o = search_valid;

genvar i;
generate
for (i = 1; i <= NUM_ELEMS; i++) begin
	eff U (.write_enable_i(write_enables[i-1]),
		.data_i(write_data_i),
		.valid_o(ff_out[i*(PLUS_VALID)-1]),
		.data_o(ff_out[i*(PLUS_VALID)-2:(i-1)*(PLUS_VALID)]),
		.*);
end
endgenerate

/*test stuff
eff a (.write_enable_i(write_enables[32]), .data_i(write_data_i), .valid_o(ff_out[32-1]), data_o(ff_out[32-2:0]));

16'b0000_0000_0000_001x: out_o=4'd1;// x stands for dont care
16'b0000_0000_0000_01xx: out_o=4'd2;// bit positions at "x" will be ignored
16'b0000_0000_0000_1xxx: out_o=4'd3;
16'b0000_0000_0001_xxxx: out_o=4'd4;
16'b0000_0000_001x_xxxx: out_o=4'd5;
16'b0000_0000_01xx_xxxx: out_o=4'd6;
16'b0000_0000_1xxx_xxxx: out_o=4'd7;
16'b0000_0001_xxxx_xxxx: out_o=4'd8;
16'b0000_001x_xxxx_xxxx: out_o=4'd9;
16'b0000_01xx_xxxx_xxxx: out_o=4'd10;
16'b0000_1xxx_xxxx_xxxx: out_o=4'd11;
16'b0001_xxxx_xxxx_xxxx: out_o=4'd12;
16'b001x_xxxx_xxxx_xxxx: out_o=4'd13;
16'b01xx_xxxx_xxxx_xxxx: out_o=4'd14;
16'b1xxx_xxxx_xxxx_xxxx: out_o=4'd15;
default: out_o=4'd0;
//end test stuff*/	

// Reading
always_comb begin
	if (rst)
		{read_valid, read_value} = '0;
	else if (read_i)
		{read_valid, read_value} = ff_out[read_index_i*PLUS_VALID +: PLUS_VALID];
	else
		{read_valid, read_value} = '0;
end

// Searching
always_comb begin
	logic [4:0] i;
	logic found = '0;
	if (rst)
		{search_index, search_valid} = '0;
	else begin
		for(i='0; i<NUM_ELEMS; i=i+1) begin
			if (ff_out[i*PLUS_VALID +: PLUS_VALID] == {1'd1,search_data_i}
				&& search_i) begin
				search_index = i;
				search_valid = '1;
				found = '1;
			end
		end
		if (!found) begin
			search_valid = '0;
			search_index = '0;
		end
	end
end

// Writing
always_comb begin
	logic[WORD_BITS-1:0] cur_addr;
	// Reset
	if (rst) write_enables = '0;
	// Find the correct address
	else begin
		for (cur_addr = 0; cur_addr < NUM_ELEMS; cur_addr++) begin
			if (cur_addr == write_index_i && write_i) begin
				write_enables[cur_addr] = '1;
			end else begin
				write_enables[cur_addr] = '0;
			end
		end
	end
end

endmodule
