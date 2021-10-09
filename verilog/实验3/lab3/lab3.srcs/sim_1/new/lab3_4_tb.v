`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/04/17 21:27:46
// Design Name: 
// Module Name: lab3_4_tb
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


module lab3_4_tb();
       reg clk;
       reg en,rst;
       wire [3:0] Q;
   
       initial begin
           clk = 1'b0;
       end
   
       always
           #5 clk = !clk;
       
       initial begin
           rst = 1'b0;
           #40 rst = !rst;
           #20 rst = !rst;
           #240 $stop;
       end
       
        initial begin
             en = 1'b0;
             #20 en = !en;
             #150 en = !en;
             #40 en = !en;
             #90 $stop;
        end
       
       CNT4_synch_reset_enable test(clk, rst, en, Q);
    
endmodule
