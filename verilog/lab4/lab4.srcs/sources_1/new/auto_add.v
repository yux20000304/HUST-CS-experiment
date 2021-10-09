`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/05/04 21:05:04
// Design Name: 
// Module Name: auto_add
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


module auto_add(clk,rst,start,done,sum_out);
        input clk,rst,start;
        output done;
        output [31:0] sum_out;
        
        wire next_zero;
        wire ld_sum,ld_next;
        wire sum_sel, next_sel;
        wire a_sel;
        
        datapath_top D1 (.clk(clk), .rst(rst), .SUM_SEL(sum_sel), .NEXT_SEL(next_sel), .A_SEL(a_sel), .LD_SUM(ld_sum), .LD_NEXT(ld_next), .NEXT_ZERO(next_zero), .sum_out(sum_out));
        FSM F1 (.clk(clk),.rst(rst),.start(start),.next_zero(next_zero), .ld_sum(ld_sum), .ld_next(ld_next), .sum_sel(sum_sel), .next_sel(next_sel), .a_sel(a_sel), .done(done));



endmodule

