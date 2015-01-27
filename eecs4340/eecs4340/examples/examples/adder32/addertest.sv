module addertest();

reg[31:0] a,b;
wire [31:0] sum;

adder32 myadder(.a_i(a),
		.b_i(b),
		.sum_o(sum));

initial begin
  $vcdpluson;
  // making input signals 0 at start
  a='0;
  b='0;
  
  #5 a = 32'h0000_0000; // wait 5 cycles
  b = 32'h0000_0001;
  $display("value of sum for 1st set of inputs is %h\n",sum);
  
  #5 a = 32'h0000_1001;
  b = 32'h0000_A00A;
  $display("value of sum for 2st set of inputs is %h\n",sum);
  
  #5 a = 32'h0000_0001;
  b = 32'h0000_FFFF;
  $display("value of sum for 3st set of inputs is %h\n",sum);

end

endmodule
