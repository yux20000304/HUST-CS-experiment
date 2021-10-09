`timescale 10ps / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/04/10 16:42:35
// Design Name: 
// Module Name: testbench_decoder38
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module testbench_decoder38();
       reg [2:0] in;
       wire [7:0] out;
       decoder_38 test(.F(out), .CBA(in));
       
       initial 
       begin 
       $display ("$time::[in] [out]------");
       $monitor ("%t::", $time, "[%b]\t[%b]", in, out);
       end
   
       initial begin
           for (in = 0; in <= 3'b111; in = in + 1)
               #2;    
           #2 $stop;
       end

endmodule
