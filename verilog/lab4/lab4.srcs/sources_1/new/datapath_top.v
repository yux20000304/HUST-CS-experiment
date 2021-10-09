`timescale 1ns / 1ps


module datapath_top(clk, rst, SUM_SEL, NEXT_SEL, A_SEL, LD_SUM, LD_NEXT, NEXT_ZERO, sum_out);
    input clk,rst,SUM_SEL,NEXT_SEL,A_SEL,LD_SUM,LD_NEXT;    
    output NEXT_ZERO;
    output [31:0] sum_out;
    
    wire [31:0] ADD_OUT1,ADD_OUT2;
    wire [31:0] REG_OUT1,REG_OUT2;
    wire [31:0] SELECT_OUT1,SELECT_OUT2,SELECT_OUT3;
    wire [31:0] MEMORY_DATA;
    
    assign sum_out=REG_OUT1;
    
    memory RAM1(.address(SELECT_OUT3),.data(MEMORY_DATA));
    
    adder A1(.a_in(REG_OUT1),.b_in(MEMORY_DATA),.c_out(ADD_OUT1));
    adder A2(.a_in(1), .b_in(REG_OUT2), .c_out(ADD_OUT2));
    
    register REG1(.clk(clk), .rst(rst), .load(LD_SUM), .d(SELECT_OUT1), .q(REG_OUT1));
    register REG2(.clk(clk), .rst(rst), .load(LD_NEXT), .d(SELECT_OUT2), .q(REG_OUT2));

    select_2_to_1 SELECT1(.a(ADD_OUT1), .b(0), .c_out(SELECT_OUT1), .sel(SUM_SEL));
    select_2_to_1 SELECT2(.a(MEMORY_DATA), .b(0), .c_out(SELECT_OUT2), .sel(NEXT_SEL));
    select_2_to_1 SELECT3(.a(ADD_OUT2), .b(REG_OUT2), .c_out(SELECT_OUT3), .sel(A_SEL));
    
    comparator C1(.a(SELECT_OUT2),.b(0),.is_equal(NEXT_ZERO));

endmodule

