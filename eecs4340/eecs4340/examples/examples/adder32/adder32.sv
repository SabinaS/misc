module adder32 (a_i,b_i,sum_o);

	input[31:0] a_i;
	input[31:0] b_i;
	output logic [31:0] sum_o;

	always_comb begin
	  sum_o = a_i + b_i;
	end

endmodule
