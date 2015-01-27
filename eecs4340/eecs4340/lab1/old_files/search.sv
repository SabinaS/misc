module search (
	search_valid_i,
	search_data_i,
	search_valid_o,
	search_index_o,

	parameter NUM_ELEMS=32
); 

	input search_valid_i;
	input [31:0] search_data_i;
	output logic search_valid_o;
	output logic [4:0] search_index_o;

	//logic valid = '0;
	//const int NUM_ELEMS = 32; 
	//ff_out = 

	always_comb begin
		for(logic [4:0] i=0; i<NUM_ELEMS; i=i+1) begin
			if(ff_out[(i+1)*33] && ff_out[(i+1)*33-2:i*33]==search_data_i[i]) begin
				search_index_o = i;
				search_valid_o = '1; 
			end
		end
	end

endmodule
