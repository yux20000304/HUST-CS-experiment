`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/04/10 15:42:58
// Design Name: 
// Module Name: three_choose
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


module three_choose(u,v,w,s0,s1,m);
    input u,v,w,s0,s1;
    output m;
    lab2_design(v,u,s0,temp1);
    lab2_design(w,temp1,s1,m);
endmodule
