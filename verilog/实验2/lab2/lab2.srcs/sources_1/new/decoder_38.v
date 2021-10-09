`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/04/10 16:03:09
// Design Name: 
// Module Name: decoder_38
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




module decoder_38(F, CBA);
  input [2:0] CBA;
  output reg [7:0] F;


  always @(CBA)
  begin
    case(CBA)
      3'd0: F = 8'b1111_1110;
      3'd1: F = 8'b1111_1101;
      3'd2: F = 8'b1111_1011;
      3'd3: F = 8'b1111_0111;
      3'd4: F = 8'b1110_1111;
      3'd5: F = 8'b1101_1111;
      3'd6: F = 8'b1011_1111;
      3'd7: F = 8'b0111_1111;
    endcase
  end
endmodule