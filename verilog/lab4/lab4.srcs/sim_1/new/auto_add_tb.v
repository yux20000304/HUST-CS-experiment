`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/05/04 22:14:35
// Design Name: 
// Module Name: auto_add_tb
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


module auto_add_tb();
    reg clk,rst,start;
    wire done;
    wire [31:0] sum_out;
    auto_add A1 (clk,rst,start,done,sum_out);
    
    initial begin
        clk<=0;
        rst<=1;
        start<=0;
        #15 rst<=0;
        #5 start<=1;
        #980 $stop;
    end

    always begin
    #10 clk<=~clk;
    end
endmodule
