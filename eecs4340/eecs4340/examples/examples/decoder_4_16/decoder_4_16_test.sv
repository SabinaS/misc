module decoder_4_16_test();

	reg [3:0] decoder_i;
	logic [15:0] decoder_o;

	decoder_4_16 my_decoder (
		.decoder_i(decoder_i),
		.decoder_o(decoder_o)
	);

	initial begin
		$vcdpluson;

		// making input signal 0 at start
		decoder_i = 4'd0;
		#5 $display( "decode of input 0 is %h, expected 0x0001\n", decoder_o );
		decoder_i = 4'd1;
		#5 $display( "decode of input 1 is %h, expected 0x0002\n", decoder_o );
		decoder_i = 4'd2;
		#5 $display( "decode of input 2 is %h, expected 0x0004\n", decoder_o );
		decoder_i = 4'd3;
		#5 $display( "decode of input 3 is %h, expected 0x0008\n", decoder_o );
		decoder_i = 4'd4;
		#5 $display( "decode of input 4 is %h, expected 0x0010\n", decoder_o );
		decoder_i = 4'd5;
		#5 $display( "decode of input 5 is %h, expected 0x0020\n", decoder_o );
		decoder_i = 4'd6;
		#5 $display( "decode of input 6 is %h, expected 0x0040\n", decoder_o );
		decoder_i = 4'd7;
		#5 $display( "decode of input 7 is %h, expected 0x0080\n", decoder_o );
		decoder_i = 4'd8;
		#5 $display( "decode of input 8 is %h, expected 0x0100\n", decoder_o );
		decoder_i = 4'd9;
		#5 $display( "decode of input 9 is %h, expected 0x0200\n", decoder_o );
		decoder_i = 4'd10;
		#5 $display( "decode of input 10 is %h, expected 0x0400\n", decoder_o );
		decoder_i = 4'd11;
		#5 $display( "decode of input 11 is %h, expected 0x0800\n", decoder_o );
		decoder_i = 4'd12;
		#5 $display( "decode of input 12 is %h, expected 0x1000\n", decoder_o );
		decoder_i = 4'd13;
		#5 $display( "decode of input 13 is %h, expected 0x2000\n", decoder_o );
		decoder_i = 4'd14;
		#5 $display( "decode of input 14 is %h, expected 0x4000\n", decoder_o );
		decoder_i = 4'd15;
		#5 $display( "decode of input 15 is %h, expected 0x8000\n", decoder_o );

	end

endmodule
