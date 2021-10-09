`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/04/10 19:35:15
// Design Name: 
// Module Name: MUX3_1
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


module MUX3_1(u,v,w,s0,s1,m);
    input u,v,w;
    input s0,s1;
    output m;
    wire temp;
    
    
    MUX2_1(.a(v), .b(u),.sel(s0),.out2(temp));
    MUX2_1(.a(w), .b(temp),.sel(s1), .out2(m));
    
endmodule
