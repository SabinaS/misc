module priorityencoder(
	inp_i,
	out_o,
	valid_o
);

	input [32:0] inp_i;
	output logic [5:0] out_o;
	output logic valid_o;

	always_comb begin
		casex (inp_i)
			32'b0000_0000_0000_0000_0000_0000_0000_0001 : out_o = 6'd0
			32'b0000_0000_0000_0000_0000_0000_0000_001x : out_o = 6'd1
			32'b0000_0000_0000_0000_0000_0000_0000_01xx : out_o = 6'd2
			32'b0000_0000_0000_0000_0000_0000_0000_1xxx : out_o = 6'd3
			32'b0000_0000_0000_0000_0000_0000_0001_xxxx : out_o = 6'd4
			32'b0000_0000_0000_0000_0000_0000_001x_xxxx : out_o = 6'd5
			32'b0000_0000_0000_0000_0000_0000_01xx_xxxx : out_o = 6'd6
			32'b0000_0000_0000_0000_0000_0000_1xxx_xxxx : out_o = 6'd7
			32'b0000_0000_0000_0000_0000_0001_xxxx_xxxx : out_o = 6'd8
			32'b0000_0000_0000_0000_0000_001x_xxxx_xxxx : out_o = 6'd9
			32'b0000_0000_0000_0000_0000_01xx_xxxx_xxxx : out_o = 6'd10
			32'b0000_0000_0000_0000_0000_1xxx_xxxx_xxxx : out_o = 6'd11
			32'b0000_0000_0000_0000_0001_xxxx_xxxx_xxxx : out_o = 6'd12
			32'b0000_0000_0000_0000_001x_xxxx_xxxx_xxxx : out_o = 6'd13
			32'b0000_0000_0000_0000_01xx_xxxx_xxxx_xxxx : out_o = 6'd14
			32'b0000_0000_0000_0000_1xxx_xxxx_xxxx_xxxx : out_o = 6'd15
			32'b0000_0000_0000_0001_xxxx_xxxx_xxxx_xxxx : out_o = 6'd16
			32'b0000_0000_0000_001x_xxxx_xxxx_xxxx_xxxx : out_o = 6'd17
			32'b0000_0000_0000_01xx_xxxx_xxxx_xxxx_xxxx : out_o = 6'd18
			32'b0000_0000_0000_1xxx_xxxx_xxxx_xxxx_xxxx : out_o = 6'd19
			32'b0000_0000_0001_xxxx_xxxx_xxxx_xxxx_xxxx : out_o = 6'd20
			32'b0000_0000_001x_xxxx_xxxx_xxxx_xxxx_xxxx : out_o = 6'd21
			32'b0000_0000_01xx_xxxx_xxxx_xxxx_xxxx_xxxx : out_o = 6'd22
			32'b0000_0000_1xxx_xxxx_xxxx_xxxx_xxxx_xxxx : out_o = 6'd23
			32'b0000_0001_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx : out_o = 6'd24
			32'b0000_001x_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx : out_o = 6'd25
			32'b0000_01xx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx : out_o = 6'd26
			32'b0000_1xxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx : out_o = 6'd27
			32'b0001_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx : out_o = 6'd28
			32'b001x_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx : out_o = 6'd29
			32'b01xx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx : out_o = 6'd30
			32'b1xxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx : out_o = 6'd31
			default: out_o=6'd32;
		endcase

		if (inp_i == 32'd0) begin
			valid_o = 1'b0;
		end

		else begin
			valid_o = 1'b1;
		end
	end

endmodule
