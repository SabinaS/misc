module xor_test();

reg a,b;
wire result;

xor_gate my_xor (
	.a_i(a),
	.b_i(b),
	.out_o(result)
);

initial begin
$vcdpluson;

// making input signals 0 at start
a='0;
b='0;

#5	a = 1'b0;
	b = 1'b0;
$display( "xor of 1st set of inputs is %h, expected 0\n", result );

#5	a = 1'b1;
	b = 1'b0;
$display( "xor of 2nd set of inputs is %h, expected 1\n", result );

#5	a = 1'b0;
	b = 1'b1;
$display( "xor of 3rd set of inputs is %h, expected 1\n", result );

#5	a = 1'b1;
	b = 1'b1;
$display( "xor of 4th set of inputs is %h, expected 0\n", result );

end

endmodule
