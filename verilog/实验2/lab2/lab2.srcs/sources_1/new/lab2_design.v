`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/04/10 13:14:20
// Design Name: 
// Module Name: lab2_design
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


module lab2_design(a,b,sel,out3);          
    input a,b,sel;
    output out3;
    reg out3;
 
   always @ (sel)
   begin
   if(sel == 1'b1)
       out3 = a;
    else
       out3 = b;
    end
endmodule



