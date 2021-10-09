`timescale 1ns / 1ps

module adder(a_in, b_in, c_out);
        parameter WIDTH = 32;
        
        input [WIDTH-1:0] a_in,b_in;
        output [WIDTH-1:0] c_out;
        
        assign c_out = a_in +b_in;
endmodule