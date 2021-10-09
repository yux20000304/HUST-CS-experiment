`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/04/10 19:22:31
// Design Name: 
// Module Name: MUX2_1
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


module MUX2_1(a,b,sel,out2);
    input a,b,sel;
    output out2;
    assign out2 = (a&sel) |(b&(~sel));

endmodule
