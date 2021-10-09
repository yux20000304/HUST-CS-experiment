`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/04/17 14:45:09
// Design Name: 
// Module Name: lab3_1_tb
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


module lab3_1_tb();
    reg clk;
        reg D;
        wire Qa, Qb, Qc;
    
        initial begin
            clk = 1'b0;
            #100 $stop;
        end
    
        always
            #20 clk = !clk;
        
        initial begin
            D = 1'b0;
            #17 D = !D;
            #6  D = !D;
            #3  D = !D;
            #6  D = !D;
            #10 D = !D;
            #6  D = !D;
            #3  D = !D;
            #3  D = !D;
            #8  D = !D;
            #3  D = !D;
            #3  D = !D;
            #14 D = !D;
        end
        
        D_latch myDlatch(clk, D, Qa);
        D_ff myDff(clk, D, Qb);
        D_ff_n myDffn(clk, D, Qc);
endmodule
