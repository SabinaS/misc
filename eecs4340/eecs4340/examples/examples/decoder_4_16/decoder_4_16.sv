//Simple 4 bit to 16 wire decoder.
module decoder_4_16 ( decoder_i, decoder_o );

	input [3:0] decoder_i;
	output [15:0] decoder_o;

 	reg [15:0] mid;
	
	always_comb begin
		case(decoder_i)
		
			4'd0:  mid = 16'b0000_0000_0000_0001;
			4'd1:  mid = 16'b0000_0000_0000_0010;
			4'd2:  mid = 16'b0000_0000_0000_0100;
			4'd3:  mid = 16'b0000_0000_0000_1000;
			
			4'd4:  mid = 16'b0000_0000_0001_0000;
			4'd5:  mid = 16'b0000_0000_0010_0000;
			4'd6:  mid = 16'b0000_0000_0100_0000;
			4'd7:  mid = 16'b0000_0000_1000_0000;
			
			4'd8:  mid = 16'b0000_0001_0000_0000;
			4'd9:  mid = 16'b0000_0010_0000_0000;
			4'd10: mid = 16'b0000_0100_0000_0000;
			4'd11: mid = 16'b0000_1000_0000_0000;
			
			4'd12: mid = 16'b0001_0000_0000_0000;
			4'd13: mid = 16'b0010_0000_0000_0000;
			4'd14: mid = 16'b0100_0000_0000_0000;
			4'd15: mid = 16'b1000_0000_0000_0000;

		endcase
	end
	
	assign decoder_o = mid;	

endmodule