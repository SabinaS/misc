module eff #(parameter WIDTH = 32)
(
	input clk,
	input rst,
	input write_enable_i,
	input [WIDTH - 1 : 0] data_i,
	output valid_o,
	output [WIDTH - 1 : 0] data_o
);

reg [WIDTH - 1 : 0] data;
reg valid;

assign data_o = data;
assign valid_o = valid;

always_ff @(posedge clk) begin
	if (rst) begin
		data <= '0;
		valid <= '0;
	end else if (write_enable_i) begin
		data <= data_i;
		valid <= '1;
	end
end

endmodule

