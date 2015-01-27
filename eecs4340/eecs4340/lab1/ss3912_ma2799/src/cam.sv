module cam	(read, read_index, write, write_index, write_data, search,
		search_data, read_valid, read_value, search_valid,
		search_index, clk, rst);

	parameter WORD_BITS = 5;
	parameter WORD_SIZE = 2 ** WORD_BITS;
	parameter NUM_ELEMS = 32;

	input clk;
	input rst;

	input [WORD_SIZE-1:0]	write_data;
	input [WORD_SIZE-1:0]	search_data;
	input [WORD_BITS-1:0]	read_index;
	input [WORD_BITS-1:0]	write_index;
	
	input			read;
	input			write;
	input			search;
	
	output [WORD_SIZE-1:0]	read_value;
	output [WORD_BITS-1:0]	search_index;
	
	output			read_valid;
	output			search_valid;

// The output array of the FFs
wire [NUM_ELEMS - 1 : 0] eff_out_valid;
wire [WORD_SIZE * NUM_ELEMS - 1 : 0] eff_out_data;
// The write enable array for the FFs. The data inputs are all tied to the input of this module
reg [NUM_ELEMS-1:0] write_enables;

// Output holding registers
reg [WORD_SIZE-1:0] read_value_reg;
reg [WORD_BITS-1:0] search_index_reg;
reg read_valid_reg;
reg search_valid_reg;

assign read_value = read_value_reg;
assign search_index = search_index_reg;
assign read_valid = read_valid_reg;
assign search_valid = search_valid_reg;

//Generating 32 enable registers for each entry
generate
	genvar i;
	for (i = 0; i < NUM_ELEMS; i++) begin
		eff #(WORD_SIZE) eff_loop
			(.write_enable_i(write_enables[i]),
			.data_i(write_data),
			.valid_o(eff_out_valid[i]),
			.data_o(eff_out_data[i * WORD_SIZE +: WORD_SIZE]),
			.rst(rst),
			.clk(clk)
		);
	end
endgenerate

// Outputs to the search combinatorial circuit
wire search_valid_block;
wire [WORD_BITS-1:0] search_index_block;
search_comb search_block (
	.search_data_i(search_data),
	.search_valid_o(search_valid_block),
	.search_index_o(search_index_block),
	.*
);

// Holds the location of the previous address we enabled
reg [WORD_BITS-1:0] prev_addr;
always_comb begin
	// Reset
	if (rst) begin
		read_value_reg = '0;
		search_index_reg = '0;
		read_valid_reg = '0;
		search_valid_reg = '0;
		write_enables = '0;
		prev_addr = '0;
	end

    // Reset takes precedence over all other signals. Reading, writing, and
    // searching can happen simultaneously due to the separate if blocks.
	else begin
        // Writing
		if (write) begin
			// Set the write enable of prev_addr to 0
			write_enables[prev_addr] = '0;
			// Set the write enable of the current address to 1
			write_enables[write_index] = '1;
			// Save the new write_index
			prev_addr = write_index;
		end else begin
			write_enables[prev_addr] = '0;
		end
	
		// Reading
        // Simply retrieve the appropriate index
		if (read) begin
			{read_valid_reg, read_value_reg} = {eff_out_valid[read_index], eff_out_data[read_index * WORD_SIZE +: WORD_SIZE]};
		end else begin
			{read_valid_reg, read_value_reg} = '0;
		end
	
		// Searching
        // Simply retrieve the output from the search_comb
		if (search) begin
			{search_valid_reg, search_index_reg} = {search_valid_block, search_index_block};
		end else begin
			{search_valid_reg, search_index_reg} = '0;
		end
	end
end

endmodule

