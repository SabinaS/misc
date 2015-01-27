public class GenerateTest
{
    public static final int NUM_ELEMS = 32;

    /**
     * @param args
     */
    public static void main(String[] args)
    {
        StringBuilder build = new StringBuilder();
        build.append("module cam_test();\r\n" + "\r\n" + "reg clk, rst;\r\n"
            + "reg read, write, search;\r\n" + "reg [4:0] read_index, write_index;\r\n"
            + "reg [31:0] write_data, search_data;\r\n" + "wire read_valid, search_valid;\r\n"
            + "wire [4:0] search_index;\r\n" + "wire [31:0] read_value;\r\n" + "\r\n"
            + "cam test_cam(.*);\r\n" + "\r\n" + "always #1 clk = ~clk;\r\n" + "\r\n"
            + "initial begin\r\n" + "    $vcdpluson;\r\n" + "    clk = '0;\r\n"
            + "    rst = '0;\r\n" + "    read = '0;\r\n" + "    write = '0;\r\n"
            + "    search = '0;\r\n" + "    read_index = '0;\r\n" + "    write_index = '0;\r\n"
            + "    write_data = '0;\r\n" + "    search_data = '0;\r\n");
        Scratch.addComment(build, "Write suite");
        int[] values = new int[Scratch.NUM_ELEMS];
        for (int i = 0; i < Scratch.NUM_ELEMS; i++) {
            Scratch.clockWait(build, 1);
            values[i] = (int) Math.round(Math.random() * Integer.MAX_VALUE);
            Scratch.addWrite(build, i, values[i]);
            Scratch.clockWait(build, 1);
            Scratch.stopWrite(build);
            if (i != Scratch.NUM_ELEMS - 1)
                build.append("\n");
        }
        Scratch.addComment(build, "Read/assert suite");
        Scratch.addComment(build, "Asynchronous waits added to prevent edge errors");
        for (int i = 0; i < Scratch.NUM_ELEMS; i++) {
            Scratch.asyncWait(build, 1);
            Scratch.addRead(build, i);
            Scratch.asyncWait(build, 1);
            Scratch.printRead(build);
            build.append("    assert(read_value == 32'h" + Integer.toHexString(values[i]) + ");\n");
            if (i != Scratch.NUM_ELEMS - 1)
                build.append("\n");
        }

        Scratch.addComment(build, "Search suite");
        for (int i = Scratch.NUM_ELEMS; i > 0; i /= 2) {
            int pos = Scratch.NUM_ELEMS / i - 1;
            Scratch.asyncWait(build, 1);
            Scratch.addSearch(build, values[pos]);
            Scratch.asyncWait(build, 1);
            Scratch.printSearch(build);
            build.append("    assert(search_index == 5'h" + Integer.toHexString(pos) + ");\n");
            build.append("\n");
        }

        Scratch.asyncWait(build, 1);
        Scratch.stopRead(build);
        Scratch.stopSearch(build);
        build.append("\n");

        // Reset
        Scratch.addComment(build, "Reset");
        Scratch.addReset(build);

        // Prove reset
        Scratch.addComment(build, "Proving reset");
        for (int i = 0; i < Scratch.NUM_ELEMS; i++) {
            Scratch.asyncWait(build, 1);
            Scratch.addSearch(build, values[i]);
            Scratch.asyncWait(build, 1);
            build.append("    assert(search_valid == '0);\n");
            build.append("\n");
        }

        // Asynchronous behavior
        Scratch.addComment(build, "Verifying asynchronous operation");
        int val = (int) Math.round(Math.random() * Integer.MAX_VALUE);
        int pos = (int) Math.round(Math.random() * 31);
        Scratch.clockWait(build, 1);
        Scratch.addRead(build, pos);
        Scratch.addSearch(build, val);
        Scratch.addWrite(build, pos, val);
        Scratch.clockWait(build, 1);
        // Scratch.asyncWait(build, 1);
        Scratch.printRead(build);
        Scratch.printSearch(build);
        build.append("    assert(search_index == 5'h" + Integer.toHexString(pos) + ");\n");

        // Done
        build.append("    \r\n" + "    @(posedge clk)#1 $finish; \r\n" + "    \r\n" + "end\r\n"
            + "\r\n" + "endmodule");
        System.out.println(build);
    }

    public static void addComment(StringBuilder build, String comment)
    {
        build.append("\n    // " + comment);
        build.append("\n");
    }

    public static void addReset(StringBuilder build)
    {
        build.append("    @(posedge clk)#1 rst = '1;\r\n" + "    @(posedge clk)#1 rst = '0;");
        build.append("\n");
    }

    public static void clockWait(StringBuilder build, int val)
    {
        build.append("    ");
        build.append("@(posedge clk)#" + val);
        build.append("\n");
    }

    public static void asyncWait(StringBuilder build, int val)
    {
        build.append("    ");
        build.append("#" + val);
        build.append("\n");
    }

    public static void addSearch(StringBuilder build, int val)
    {
        build.append("    ");
        build.append("search = '1;\r\n" + "    search_data = 32'd" + val + ";");
        build.append("\n");
    }

    public static void addRead(StringBuilder build, int index)
    {
        build.append("    ");
        build.append("read = '1;\r\n" + "    read_index = 5'd" + index + ";");
        build.append("\n");
    }

    public static void addWrite(StringBuilder build, int index, int val)
    {
        build.append("    ");
        build.append("write = '1; \r\n" + "    write_index = 5'd" + index + "; \r\n"
            + "    write_data = 32'd" + val + ";");
        build.append("\n");
    }

    public static void stopSearch(StringBuilder build)
    {
        build.append("    ");
        build.append("search = '0;");
        build.append("\n");
    }

    public static void stopRead(StringBuilder build)
    {
        build.append("    ");
        build.append("read = '0;");
        build.append("\n");
    }

    public static void stopWrite(StringBuilder build)
    {
        build.append("    ");
        build.append("write = '0;");
        build.append("\n");
    }

    public static void printSearch(StringBuilder build)
    {
        build.append("    ");
        build
            .append("$display(\"Searched 0x%h, found at 0x%h, valid: %d\", search_data, search_index, search_valid);");
        build.append("\n");
    }

    public static void printRead(StringBuilder build)
    {
        build.append("    ");
        build
            .append("$display(\"Read 0x%h from 0x%h, valid: %d\", read_value, read_index, read_valid);");
        build.append("\n");
    }

    public static void printWrite(StringBuilder build)
    {
        build.append("    ");
        build
            .append("$display(\"wrote write_data: 0x%h\\nto write_index: 0x%h\", write_data, write_index);");
        build.append("\n");
    }
}

