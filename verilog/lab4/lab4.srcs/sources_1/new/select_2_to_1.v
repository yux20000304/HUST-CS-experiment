`timescale 1ns / 1ps


module select_2_to_1(a, b, c_out, sel);
        parameter WIDTH = 32;
        
        input [WIDTH-1:0] a,b;
        input sel;
        output [WIDTH-1:0] c_out;
        
        assign c_out = (sel)? a: b;
       
endmodule