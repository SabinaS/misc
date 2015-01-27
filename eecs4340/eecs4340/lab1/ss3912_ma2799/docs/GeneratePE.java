public class GeneratePE
{
    public static void main(String[] args)
    {
        for (int i = 31; i >= 0; i--) {
            StringBuilder bitString = new StringBuilder("32'b");
            for (int j = 0; j < 32; j++) {
                if (j % 4 == 0 && j != 0)
                    bitString.append("_");
                if (j == i)
                    bitString.append("1");
                else if (j < i)
                    bitString.append("0");
                else if (j > i)
                    bitString.append("x");
            }
            System.out.println(bitString.toString() + " : begin\n\tout_o = 5'd" + (31 - i) + ";\n\tvalid_o = '1;\nend");
        }
    }
}
