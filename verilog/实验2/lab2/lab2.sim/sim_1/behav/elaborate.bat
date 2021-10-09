@echo off
set xv_path=C:\\Xilinx\\Vivado\\Vivado\\2015.2\\bin
call %xv_path%/xelab  -wto bf3d5107f7ae474eaf42eb0e0cacb7b0 -m64 --debug typical --relax --mt 2 -L xil_defaultlib -L unisims_ver -L unimacro_ver -L secureip --snapshot testbench_decoder38_behav xil_defaultlib.testbench_decoder38 xil_defaultlib.glbl -log elaborate.log
if "%errorlevel%"=="0" goto SUCCESS
if "%errorlevel%"=="1" goto END
:END
exit 1
:SUCCESS
exit 0
