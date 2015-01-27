module search_comb (
	search_data_i,
	eff_out_data,
	eff_out_valid,
	search_valid_o,
	search_index_o
);

	parameter NUM_ELEMS = 32;
	parameter WORD_BITS = 5;
	parameter WORD_SIZE = 2 ** WORD_BITS;

	input [WORD_SIZE - 1 : 0] search_data_i;
	input [WORD_SIZE * NUM_ELEMS - 1 : 0] eff_out_data;
	input [NUM_ELEMS - 1 : 0] eff_out_valid;
	output search_valid_o;
	output [WORD_BITS - 1 : 0] search_index_o;

// Maps the output of the search data being compared to the storage via AND gates
wire [NUM_ELEMS - 1 : 0] and_array_out;

priorityencoder pencoder(
	.inp_i(and_array_out),
	.out_o(search_index_o),
	.valid_o(search_valid_o)
);

// We used a generate for loop because our eff held 32*32 indeces. Since each data entry was
// stored across 32 bits, we needed to look at 32 indeces at once. 
//AND together the search_data_i and eff_out_data registers to see which of the data matches.
//AND eff_out_valid with the previous result and place that into and_array_out to make 
//sure the matched data is valid as well.
//Feed and_array_out into the priority encoder to get the search_index_o and search_valid_o.
generate
	genvar i;
	for (i = 0; i < NUM_ELEMS; i++) begin : and_gates
		assign and_array_out[i] = ((search_data_i == eff_out_data[WORD_SIZE * i +: WORD_SIZE]) && eff_out_valid[i]);
	end
endgenerate

endmodule

