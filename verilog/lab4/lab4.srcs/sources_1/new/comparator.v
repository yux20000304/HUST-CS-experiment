`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/05/04 11:34:08
// Design Name: 
// Module Name: comparator
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


module comparator(a,b,is_great,is_less,is_equal );
        parameter WIDTH = 32;
        
        input [WIDTH-1:0] a,b;
        output reg is_great,is_less,is_equal;
        
        initial begin
            is_great<=0;
            is_less<=0;
            is_equal<=0;
        end
        
        always @(a,b) begin
            if(a==b) begin
                is_equal=1;
                is_great=0;
                is_less=0;
            end
             if(a>b) begin
                    is_equal=0;
                    is_great=1;
                    is_less=0;
             end
              if(a<b) begin
                     is_equal=0;
                     is_great=0;
                     is_less=1;
              end
        end
        
        
endmodule
