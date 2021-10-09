`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/05/04 23:18:39
// Design Name: 
// Module Name: datapath_tb
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


module datapath_tb();
    reg clk,rst,SUM_SEL,NEXT_SEL,A_SEL,LD_SUM,LD_NEXT;
    
    wire NEXT_ZERO;
    wire [31:0] sum_out;
    initial begin
        clk<=0;
        rst<=0;
        SUM_SEL<=1;
        NEXT_SEL<=1;
        A_SEL<=1;
        LD_SUM<=1;
        LD_NEXT<=1;
        #10 clk<=~clk;
        #200 $stop;
    end
    
   datapath_top D1 (.clk(clk), .rst(rst), .SUM_SEL(SUM_SEL), .NEXT_SEL(NEXT_SEL), .A_SEL(A_SEL), .LD_SUM(LD_SUM), .LD_NEXT(LD_NEXT), .NEXT_ZERO(NEXT_ZERO), .sum_out(sum_out));

endmodule
