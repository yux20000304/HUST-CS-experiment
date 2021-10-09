`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/04/17 15:29:33
// Design Name: 
// Module Name: Register_synch_reset
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


module Register_synch_reset(input [3:0] D, input clk, input rst, input en, output reg [3:0] Q);
    always @(posedge clk)
        if (rst) begin         // Í¬²½¸´Î»
            Q <= 4'b0;
        end 
        else begin
            if (en) begin
                Q<=D;
            end
        end
endmodule
