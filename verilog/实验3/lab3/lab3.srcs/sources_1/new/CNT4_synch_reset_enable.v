`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/04/17 21:18:53
// Design Name: 
// Module Name: CNT4_synch_reset_enable
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


module CNT4_synch_reset_enable(input clk, input rst, input en, output reg [3:0] Q);
    always @(posedge clk)
       if (rst) begin         // Í¬²½¸´Î»
           Q <= 4'b0;
       end 
       else begin
           if (en) begin
               Q<=Q+1;
           end
       end








endmodule

