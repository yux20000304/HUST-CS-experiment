@echo off
set xv_path=C:\\Xilinx\\Vivado\\Vivado\\2015.2\\bin
call %xv_path%/xsim testbench_decoder38_behav -key {Behavioral:sim_1:Functional:testbench_decoder38} -tclbatch testbench_decoder38.tcl -log simulate.log
if "%errorlevel%"=="0" goto SUCCESS
if "%errorlevel%"=="1" goto END
:END
exit 1
:SUCCESS
exit 0
