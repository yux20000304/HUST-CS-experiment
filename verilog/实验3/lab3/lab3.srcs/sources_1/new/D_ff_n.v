`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/04/17 13:58:34
// Design Name: 
// Module Name: D_ff_n
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


module D_ff_n(input clk, input D, output reg Q);
    always @ (negedge clk)    //  ±÷”œ¬Ωµ—ÿ¥•∑¢
            Q <= D;
endmodule

