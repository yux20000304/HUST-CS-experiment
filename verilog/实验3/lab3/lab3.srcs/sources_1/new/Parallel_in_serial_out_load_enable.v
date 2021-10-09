`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/04/17 18:04:42
// Design Name: 
// Module Name: Parallel_in_serial_out_load_enable
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


module Parallel_in_serial_out_load_enable(clk, ShiftIn, ParallelIn, load, ShiftEn, ShiftOut, RegContent);
    input clk, ShiftIn, load, ShiftEn;
    input [3:0] ParallelIn;
    output ShiftOut;
    output [3:0] RegContent;

    reg [3:0] shift_reg;

    always @(posedge clk)
        if (load)
            shift_reg <= ParallelIn;
        else if (ShiftEn)
            shift_reg <= {shift_reg[2:0], ShiftIn};

    assign ShiftOut = shift_reg[3];
    assign RegContent = shift_reg;
endmodule

