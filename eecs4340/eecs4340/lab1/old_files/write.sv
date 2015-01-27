always_ff @(posedge clk) begin
	// Find the correct address
	logic[WORD_BITS-1:0] cur_addr;
	for (cur_addr = 0; cur_addr < NUM_ELEMS; cur_addr++) begin
		if (cur_addr == write_index_i) begin
			ff_in[cur_addr] <= '1;
		end else begin
			ff_in[cur_addr] <= '0;
		end
	end
end
