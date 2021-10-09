`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/04/17 19:34:05
// Design Name: 
// Module Name: lab3_3_tb
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


module lab3_3_tb();
    reg in_clk,in_ShiftEn,in_ShiftIn;
    wire [3:0] ParallelOut_out;
    wire ShiftOut_out;
    
    Serial_in_Parallel_out_enable test(.clk(in_clk),.ShiftEn(in_ShiftEn),.ShiftIn(in_ShiftIn),.ShiftOut(ShiftOut_out),.ParallelOut(ParallelOut_out));
    
    initial begin
        in_clk=1'b0;
    end
    
    always
        #10 in_clk= !in_clk;
    
    initial begin
        in_ShiftIn=1'b0;
        #10 in_ShiftIn= !in_ShiftIn;
        #50 in_ShiftIn= !in_ShiftIn;
        #40 in_ShiftIn= !in_ShiftIn;
        #60 in_ShiftIn= !in_ShiftIn;
        #20 in_ShiftIn= !in_ShiftIn;
        #40 in_ShiftIn= !in_ShiftIn;
        #80 $stop;
    end
    
    initial begin
        in_ShiftEn=1'b0;
        #40 in_ShiftEn= !in_ShiftEn;
        #60 in_ShiftEn= !in_ShiftEn;
        #40 in_ShiftEn= !in_ShiftEn;
        #160 $stop;
    end

endmodule
