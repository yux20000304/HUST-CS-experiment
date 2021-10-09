`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/05/04 18:49:04
// Design Name: 
// Module Name: FSM_tb
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


module FSM_tb();
        reg clk;
        reg rst, start;
        reg next_zero;
        wire ld_sum, ld_next, sum_sel, next_sel, a_sel, done;
        
        FSM FSM1(.clk(clk), 
          .rst(rst), 
          .start(start), 
          .next_zero(next_zero), 
          .ld_sum(ld_sum), 
          .ld_next(ld_next), 
          .sum_sel(sum_sel), 
          .next_sel(next_sel), 
          .a_sel(a_sel), 
          .done(done));
        
        initial begin
        clk <= 0;
        rst <= 1;
        start <= 0;
        next_zero =0;
        #15 rst<=0;
        #20 start<=1;
        #85 next_zero =1;
        #20 start<=0;
        #50 $stop;
        end
        
        always begin
        #10 clk <= ~clk;
        end

endmodule
