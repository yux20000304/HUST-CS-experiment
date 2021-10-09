`timescale 1ns / 1ps

module memory(address, data);
    parameter WIDTH = 32;    
    input [WIDTH-1:0] address;
    output [WIDTH-1:0] data;

    reg [WIDTH-1:0] ram[4*WIDTH-1:0];

    initial begin
        $readmemh("C:/Users/WidenSun/Desktop/verilog/lab4/lab4.srcs/sources_1/new/ram_init.txt", ram);
    end

    assign data =ram[address];
    
endmodule