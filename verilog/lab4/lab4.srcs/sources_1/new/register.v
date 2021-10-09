`timescale 1ns / 1ps


module register(clk, rst, load, d, q);
        parameter WIDTH = 32;
        
        input clk,rst,load;
        input [WIDTH-1:0] d;
        output reg [WIDTH-1:0] q;
        
        initial begin
            q<=0;
        end
        
        always @(posedge clk) begin
            if(rst==1)
                q<=0;
            else if (load==1)
                q<=d;
        end
        
endmodule