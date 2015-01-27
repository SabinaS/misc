module cam_test();

reg clk, rst;
reg read, write, search;
reg [4:0] read_index, write_index;
reg [31:0] write_data, search_data;
wire read_valid, search_valid;
wire [4:0] search_index;
wire [31:0] read_value;

cam test_cam(.*);

always #1 clk = ~clk;

initial begin
    $vcdpluson;
    clk = '0;
    rst = '0;
    read = '0;
    write = '0;
    search = '0;
    read_index = '0;
    write_index = '0;
    write_data = '0;
    search_data = '0;

    // Write suite
    @(posedge clk)#1
    write = '1; 
    write_index = 5'd0; 
    write_data = 32'd252716804;
    @(posedge clk)#1
    write = '0;

    @(posedge clk)#1
    write = '1; 
    write_index = 5'd1; 
    write_data = 32'd2083095019;
    @(posedge clk)#1
    write = '0;

    @(posedge clk)#1
    write = '1; 
    write_index = 5'd2; 
    write_data = 32'd903105144;
    @(posedge clk)#1
    write = '0;

    @(posedge clk)#1
    write = '1; 
    write_index = 5'd3; 
    write_data = 32'd2135975199;
    @(posedge clk)#1
    write = '0;

    @(posedge clk)#1
    write = '1; 
    write_index = 5'd4; 
    write_data = 32'd1888322633;
    @(posedge clk)#1
    write = '0;

    @(posedge clk)#1
    write = '1; 
    write_index = 5'd5; 
    write_data = 32'd1370598736;
    @(posedge clk)#1
    write = '0;

    @(posedge clk)#1
    write = '1; 
    write_index = 5'd6; 
    write_data = 32'd2052941940;
    @(posedge clk)#1
    write = '0;

    @(posedge clk)#1
    write = '1; 
    write_index = 5'd7; 
    write_data = 32'd869860297;
    @(posedge clk)#1
    write = '0;

    @(posedge clk)#1
    write = '1; 
    write_index = 5'd8; 
    write_data = 32'd1854710691;
    @(posedge clk)#1
    write = '0;

    @(posedge clk)#1
    write = '1; 
    write_index = 5'd9; 
    write_data = 32'd1167206717;
    @(posedge clk)#1
    write = '0;

    @(posedge clk)#1
    write = '1; 
    write_index = 5'd10; 
    write_data = 32'd322352349;
    @(posedge clk)#1
    write = '0;

    @(posedge clk)#1
    write = '1; 
    write_index = 5'd11; 
    write_data = 32'd592336807;
    @(posedge clk)#1
    write = '0;

    @(posedge clk)#1
    write = '1; 
    write_index = 5'd12; 
    write_data = 32'd1265649029;
    @(posedge clk)#1
    write = '0;

    @(posedge clk)#1
    write = '1; 
    write_index = 5'd13; 
    write_data = 32'd991675989;
    @(posedge clk)#1
    write = '0;

    @(posedge clk)#1
    write = '1; 
    write_index = 5'd14; 
    write_data = 32'd632131144;
    @(posedge clk)#1
    write = '0;

    @(posedge clk)#1
    write = '1; 
    write_index = 5'd15; 
    write_data = 32'd877381591;
    @(posedge clk)#1
    write = '0;

    @(posedge clk)#1
    write = '1; 
    write_index = 5'd16; 
    write_data = 32'd1104858987;
    @(posedge clk)#1
    write = '0;

    @(posedge clk)#1
    write = '1; 
    write_index = 5'd17; 
    write_data = 32'd2146541410;
    @(posedge clk)#1
    write = '0;

    @(posedge clk)#1
    write = '1; 
    write_index = 5'd18; 
    write_data = 32'd191858588;
    @(posedge clk)#1
    write = '0;

    @(posedge clk)#1
    write = '1; 
    write_index = 5'd19; 
    write_data = 32'd581682344;
    @(posedge clk)#1
    write = '0;

    @(posedge clk)#1
    write = '1; 
    write_index = 5'd20; 
    write_data = 32'd929412097;
    @(posedge clk)#1
    write = '0;

    @(posedge clk)#1
    write = '1; 
    write_index = 5'd21; 
    write_data = 32'd2068509145;
    @(posedge clk)#1
    write = '0;

    @(posedge clk)#1
    write = '1; 
    write_index = 5'd22; 
    write_data = 32'd1057555153;
    @(posedge clk)#1
    write = '0;

    @(posedge clk)#1
    write = '1; 
    write_index = 5'd23; 
    write_data = 32'd696644851;
    @(posedge clk)#1
    write = '0;

    @(posedge clk)#1
    write = '1; 
    write_index = 5'd24; 
    write_data = 32'd1537638867;
    @(posedge clk)#1
    write = '0;

    @(posedge clk)#1
    write = '1; 
    write_index = 5'd25; 
    write_data = 32'd1369366276;
    @(posedge clk)#1
    write = '0;

    @(posedge clk)#1
    write = '1; 
    write_index = 5'd26; 
    write_data = 32'd719582390;
    @(posedge clk)#1
    write = '0;

    @(posedge clk)#1
    write = '1; 
    write_index = 5'd27; 
    write_data = 32'd357419824;
    @(posedge clk)#1
    write = '0;

    @(posedge clk)#1
    write = '1; 
    write_index = 5'd28; 
    write_data = 32'd1083087523;
    @(posedge clk)#1
    write = '0;

    @(posedge clk)#1
    write = '1; 
    write_index = 5'd29; 
    write_data = 32'd1494160920;
    @(posedge clk)#1
    write = '0;

    @(posedge clk)#1
    write = '1; 
    write_index = 5'd30; 
    write_data = 32'd195284964;
    @(posedge clk)#1
    write = '0;

    @(posedge clk)#1
    write = '1; 
    write_index = 5'd31; 
    write_data = 32'd1790345930;
    @(posedge clk)#1
    write = '0;

    // Read/assert suite

    // Asynchronous waits added to prevent edge errors
    #1
    read = '1;
    read_index = 5'd0;
    #1
    $display("Read 0x%h from 0x%h, valid: %d", read_value, read_index, read_valid);
    assert(read_value == 32'hf102704);

    #1
    read = '1;
    read_index = 5'd1;
    #1
    $display("Read 0x%h from 0x%h, valid: %d", read_value, read_index, read_valid);
    assert(read_value == 32'h7c2981eb);

    #1
    read = '1;
    read_index = 5'd2;
    #1
    $display("Read 0x%h from 0x%h, valid: %d", read_value, read_index, read_valid);
    assert(read_value == 32'h35d44a78);

    #1
    read = '1;
    read_index = 5'd3;
    #1
    $display("Read 0x%h from 0x%h, valid: %d", read_value, read_index, read_valid);
    assert(read_value == 32'h7f50651f);

    #1
    read = '1;
    read_index = 5'd4;
    #1
    $display("Read 0x%h from 0x%h, valid: %d", read_value, read_index, read_valid);
    assert(read_value == 32'h708d8449);

    #1
    read = '1;
    read_index = 5'd5;
    #1
    $display("Read 0x%h from 0x%h, valid: %d", read_value, read_index, read_valid);
    assert(read_value == 32'h51b1ad50);

    #1
    read = '1;
    read_index = 5'd6;
    #1
    $display("Read 0x%h from 0x%h, valid: %d", read_value, read_index, read_valid);
    assert(read_value == 32'h7a5d6874);

    #1
    read = '1;
    read_index = 5'd7;
    #1
    $display("Read 0x%h from 0x%h, valid: %d", read_value, read_index, read_valid);
    assert(read_value == 32'h33d903c9);

    #1
    read = '1;
    read_index = 5'd8;
    #1
    $display("Read 0x%h from 0x%h, valid: %d", read_value, read_index, read_valid);
    assert(read_value == 32'h6e8ca3a3);

    #1
    read = '1;
    read_index = 5'd9;
    #1
    $display("Read 0x%h from 0x%h, valid: %d", read_value, read_index, read_valid);
    assert(read_value == 32'h4592293d);

    #1
    read = '1;
    read_index = 5'd10;
    #1
    $display("Read 0x%h from 0x%h, valid: %d", read_value, read_index, read_valid);
    assert(read_value == 32'h1336b4dd);

    #1
    read = '1;
    read_index = 5'd11;
    #1
    $display("Read 0x%h from 0x%h, valid: %d", read_value, read_index, read_valid);
    assert(read_value == 32'h234e57a7);

    #1
    read = '1;
    read_index = 5'd12;
    #1
    $display("Read 0x%h from 0x%h, valid: %d", read_value, read_index, read_valid);
    assert(read_value == 32'h4b704585);

    #1
    read = '1;
    read_index = 5'd13;
    #1
    $display("Read 0x%h from 0x%h, valid: %d", read_value, read_index, read_valid);
    assert(read_value == 32'h3b1bc655);

    #1
    read = '1;
    read_index = 5'd14;
    #1
    $display("Read 0x%h from 0x%h, valid: %d", read_value, read_index, read_valid);
    assert(read_value == 32'h25ad8e48);

    #1
    read = '1;
    read_index = 5'd15;
    #1
    $display("Read 0x%h from 0x%h, valid: %d", read_value, read_index, read_valid);
    assert(read_value == 32'h344bc7d7);

    #1
    read = '1;
    read_index = 5'd16;
    #1
    $display("Read 0x%h from 0x%h, valid: %d", read_value, read_index, read_valid);
    assert(read_value == 32'h41dacf6b);

    #1
    read = '1;
    read_index = 5'd17;
    #1
    $display("Read 0x%h from 0x%h, valid: %d", read_value, read_index, read_valid);
    assert(read_value == 32'h7ff19f62);

    #1
    read = '1;
    read_index = 5'd18;
    #1
    $display("Read 0x%h from 0x%h, valid: %d", read_value, read_index, read_valid);
    assert(read_value == 32'hb6f879c);

    #1
    read = '1;
    read_index = 5'd19;
    #1
    $display("Read 0x%h from 0x%h, valid: %d", read_value, read_index, read_valid);
    assert(read_value == 32'h22abc4a8);

    #1
    read = '1;
    read_index = 5'd20;
    #1
    $display("Read 0x%h from 0x%h, valid: %d", read_value, read_index, read_valid);
    assert(read_value == 32'h3765b401);

    #1
    read = '1;
    read_index = 5'd21;
    #1
    $display("Read 0x%h from 0x%h, valid: %d", read_value, read_index, read_valid);
    assert(read_value == 32'h7b4af1d9);

    #1
    read = '1;
    read_index = 5'd22;
    #1
    $display("Read 0x%h from 0x%h, valid: %d", read_value, read_index, read_valid);
    assert(read_value == 32'h3f0902d1);

    #1
    read = '1;
    read_index = 5'd23;
    #1
    $display("Read 0x%h from 0x%h, valid: %d", read_value, read_index, read_valid);
    assert(read_value == 32'h2985f4f3);

    #1
    read = '1;
    read_index = 5'd24;
    #1
    $display("Read 0x%h from 0x%h, valid: %d", read_value, read_index, read_valid);
    assert(read_value == 32'h5ba681d3);

    #1
    read = '1;
    read_index = 5'd25;
    #1
    $display("Read 0x%h from 0x%h, valid: %d", read_value, read_index, read_valid);
    assert(read_value == 32'h519edf04);

    #1
    read = '1;
    read_index = 5'd26;
    #1
    $display("Read 0x%h from 0x%h, valid: %d", read_value, read_index, read_valid);
    assert(read_value == 32'h2ae3f4b6);

    #1
    read = '1;
    read_index = 5'd27;
    #1
    $display("Read 0x%h from 0x%h, valid: %d", read_value, read_index, read_valid);
    assert(read_value == 32'h154dcb30);

    #1
    read = '1;
    read_index = 5'd28;
    #1
    $display("Read 0x%h from 0x%h, valid: %d", read_value, read_index, read_valid);
    assert(read_value == 32'h408e9aa3);

    #1
    read = '1;
    read_index = 5'd29;
    #1
    $display("Read 0x%h from 0x%h, valid: %d", read_value, read_index, read_valid);
    assert(read_value == 32'h590f1618);

    #1
    read = '1;
    read_index = 5'd30;
    #1
    $display("Read 0x%h from 0x%h, valid: %d", read_value, read_index, read_valid);
    assert(read_value == 32'hba3cfe4);

    #1
    read = '1;
    read_index = 5'd31;
    #1
    $display("Read 0x%h from 0x%h, valid: %d", read_value, read_index, read_valid);
    assert(read_value == 32'h6ab682ca);

    // Search suite
    #1
    search = '1;
    search_data = 32'd252716804;
    #1
    $display("Searched 0x%h, found at 0x%h, valid: %d", search_data, search_index, search_valid);
    assert(search_index == 5'h0);

    #1
    search = '1;
    search_data = 32'd2083095019;
    #1
    $display("Searched 0x%h, found at 0x%h, valid: %d", search_data, search_index, search_valid);
    assert(search_index == 5'h1);

    #1
    search = '1;
    search_data = 32'd2135975199;
    #1
    $display("Searched 0x%h, found at 0x%h, valid: %d", search_data, search_index, search_valid);
    assert(search_index == 5'h3);

    #1
    search = '1;
    search_data = 32'd869860297;
    #1
    $display("Searched 0x%h, found at 0x%h, valid: %d", search_data, search_index, search_valid);
    assert(search_index == 5'h7);

    #1
    search = '1;
    search_data = 32'd877381591;
    #1
    $display("Searched 0x%h, found at 0x%h, valid: %d", search_data, search_index, search_valid);
    assert(search_index == 5'hf);

    #1
    search = '1;
    search_data = 32'd1790345930;
    #1
    $display("Searched 0x%h, found at 0x%h, valid: %d", search_data, search_index, search_valid);
    assert(search_index == 5'h1f);

    #1
    read = '0;
    search = '0;


    // Reset
    @(posedge clk)#1 rst = '1;
    @(posedge clk)#1 rst = '0;

    // Proving reset
    #1
    search = '1;
    search_data = 32'd252716804;
    #1
    assert(search_valid == '0);

    #1
    search = '1;
    search_data = 32'd2083095019;
    #1
    assert(search_valid == '0);

    #1
    search = '1;
    search_data = 32'd903105144;
    #1
    assert(search_valid == '0);

    #1
    search = '1;
    search_data = 32'd2135975199;
    #1
    assert(search_valid == '0);

    #1
    search = '1;
    search_data = 32'd1888322633;
    #1
    assert(search_valid == '0);

    #1
    search = '1;
    search_data = 32'd1370598736;
    #1
    assert(search_valid == '0);

    #1
    search = '1;
    search_data = 32'd2052941940;
    #1
    assert(search_valid == '0);

    #1
    search = '1;
    search_data = 32'd869860297;
    #1
    assert(search_valid == '0);

    #1
    search = '1;
    search_data = 32'd1854710691;
    #1
    assert(search_valid == '0);

    #1
    search = '1;
    search_data = 32'd1167206717;
    #1
    assert(search_valid == '0);

    #1
    search = '1;
    search_data = 32'd322352349;
    #1
    assert(search_valid == '0);

    #1
    search = '1;
    search_data = 32'd592336807;
    #1
    assert(search_valid == '0);

    #1
    search = '1;
    search_data = 32'd1265649029;
    #1
    assert(search_valid == '0);

    #1
    search = '1;
    search_data = 32'd991675989;
    #1
    assert(search_valid == '0);

    #1
    search = '1;
    search_data = 32'd632131144;
    #1
    assert(search_valid == '0);

    #1
    search = '1;
    search_data = 32'd877381591;
    #1
    assert(search_valid == '0);

    #1
    search = '1;
    search_data = 32'd1104858987;
    #1
    assert(search_valid == '0);

    #1
    search = '1;
    search_data = 32'd2146541410;
    #1
    assert(search_valid == '0);

    #1
    search = '1;
    search_data = 32'd191858588;
    #1
    assert(search_valid == '0);

    #1
    search = '1;
    search_data = 32'd581682344;
    #1
    assert(search_valid == '0);

    #1
    search = '1;
    search_data = 32'd929412097;
    #1
    assert(search_valid == '0);

    #1
    search = '1;
    search_data = 32'd2068509145;
    #1
    assert(search_valid == '0);

    #1
    search = '1;
    search_data = 32'd1057555153;
    #1
    assert(search_valid == '0);

    #1
    search = '1;
    search_data = 32'd696644851;
    #1
    assert(search_valid == '0);

    #1
    search = '1;
    search_data = 32'd1537638867;
    #1
    assert(search_valid == '0);

    #1
    search = '1;
    search_data = 32'd1369366276;
    #1
    assert(search_valid == '0);

    #1
    search = '1;
    search_data = 32'd719582390;
    #1
    assert(search_valid == '0);

    #1
    search = '1;
    search_data = 32'd357419824;
    #1
    assert(search_valid == '0);

    #1
    search = '1;
    search_data = 32'd1083087523;
    #1
    assert(search_valid == '0);

    #1
    search = '1;
    search_data = 32'd1494160920;
    #1
    assert(search_valid == '0);

    #1
    search = '1;
    search_data = 32'd195284964;
    #1
    assert(search_valid == '0);

    #1
    search = '1;
    search_data = 32'd1790345930;
    #1
    assert(search_valid == '0);


    // Verifying asynchronous operation
    @(posedge clk)#1
    read = '1;
    read_index = 5'd4;
    search = '1;
    search_data = 32'd768774901;
    write = '1; 
    write_index = 5'd4; 
    write_data = 32'd768774901;
    @(posedge clk)#1
    $display("Read 0x%h from 0x%h, valid: %d", read_value, read_index, read_valid);
    $display("Searched 0x%h, found at 0x%h, valid: %d", search_data, search_index, search_valid);
    assert(search_index == 5'h4);
    
    @(posedge clk)#1 $finish; 
    
end

endmodule

