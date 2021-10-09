addi $sp,$sp,1024  #$sp init
 addi $s0,$0,-1
 addi $s1,$0,0
 sw $s0,512($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
 sw $s0,512($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
 sw $s0,512($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
 sw $s0,512($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
 sw $s0,512($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
 sw $s0,512($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
 sw $s0,512($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
 sw $s0,512($s1)
 add $s0,$zero,0   
 addi $s1,$zero,28   #排序区间
 lw $s3,512($s0)     
 lw $s4,512($s1)
 slt $t0,$s3,$s4
 beq $t0,$0,sort_next   #降序排序
 sw $s3, 512($s1)
 sw $s4, 512($s0)   
 addi $s1, $s1, -4   
 beq $s0, $s1,  sort_next1  
 beq $0,$0,sort_loop
 addi $s0,$s0,4
 addi $s1,$zero,28
 beq $s0, $s1, ProgramEnd
 beq $0,$0,sort_loop
 beq $0,$0,ProgramEnd  #死循环
  addi $sp,$sp,8    #push registers  需要保留哪些寄存器？ 中断程序用到的寄存器
  sw $s0,0($sp)
  sw $s1,4($sp)
  addi $s1,$0,0x240
  lw $s0,($s1)
  addi $s0,$s0,1
  sw $s0,($s1)
  sw $s0,4($s1)
  sw $s0,8($s1)
  sw $s0,12($s1)
  sw $s0,16($s1)
  sw $s0,20($s1)
  sw $s0,24($s1)
  sw $s0,28($s1)
  lw $s1,4($sp)   #pop registers
  lw $s0,0($sp)
  addi $sp,$sp,-8
  eret
  addi $sp,$sp,8    #push registers  需要保留哪些寄存器？ 中断程序用到的寄存器
  sw $s0,0($sp)
  sw $s1,4($sp)
  addi $s1,$0,0x280
  lw $s0,($s1)
  addi $s0,$s0,-1
  sw $s0,($s1)
  sw $s0,4($s1)
  sw $s0,8($s1)
  sw $s0,12($s1)
  sw $s0,16($s1)
  sw $s0,20($s1)
  sw $s0,24($s1)
  sw $s0,28($s1)
  
  lw $s1,4($sp)   #pop registers
  lw $s0,0($sp)
  addi $sp,$sp,-8
  eret

