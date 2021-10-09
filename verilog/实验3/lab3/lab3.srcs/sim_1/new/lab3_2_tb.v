`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/04/17 15:37:52
// Design Name: 
// Module Name: lab3_2_tb
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


module lab3_2_tb();
    reg in_clk,in_rst,in_en;
    reg [3:0] in_D;
    wire [3:0] out_Q;
    Register_synch_reset test(.D(in_D), .clk(in_clk), .rst(in_rst), .en(in_en), .Q(out_Q));

    initial begin
        in_clk=1'b0;
    end   
    always
        #10 in_clk= !in_clk;
 
        initial begin
            in_rst=1'b0;
            #80 in_rst= !in_rst;
            #50 in_rst= !in_rst;
            #70 $stop;
        end
        
        initial begin
            in_en=1'b0;
            #40 in_en= !in_en;
            #20 in_en= !in_en;
            #40 in_en= !in_en;
            #20 in_en= !in_en;
            #40 in_en= !in_en;
            #20 in_en= !in_en;
            #20 $stop;
        end
        
        initial begin
            in_D=4'b0000;
            #20 in_D=4'b0101;
            #40 in_D=4'b1001;
            #140 $stop;
        end    

endmodule
