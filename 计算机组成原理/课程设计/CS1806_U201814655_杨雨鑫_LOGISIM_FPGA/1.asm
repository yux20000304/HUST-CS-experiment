########################
## main
#########################
addi $a1,$0,2
start:
nop
nop
nop
j start

#################################################
## int
################################################
# 读取按键值
lw $v1,0
# 判断按下
lw $t0, ($v1)
bne $t0,$0,exit
bne $t7,$0,exit

# 


# 计算偏移
beq $v1,4 offset1
beq $v1,8 offset2
beq $v1,12 offset3
beq $v1,16 offset4
beq $v1,20 offset5
beq $v1,24 offset6
beq $v1,28 offset7
beq $v1,32 offset8
beq $v1,36 offset9

offset1:
addi $t1,$0,0
addi $t2,$0,0
beq $a1,1, play1_1
beq $a1,2, play2_1
play1_1:
ori $t8,$t8,1
j draw
play2_1:
ori $t9,$t9,1
j draw


offset2:
addi $t1,$0,42
addi $t2,$0,0
beq $a1,1, play1_2
beq $a1,2, play2_2
play1_2:
ori $t8,$t8,2
j draw
play2_2:
ori $t9,$t9,2
j draw

offset3:
addi $t1,$0,84
addi $t2,$0,0
beq $a1,1, play1_3
beq $a1,2, play2_3
play1_3:
ori $t8,$t8,4
j draw
play2_3:
ori $t9,$t9,4
j draw

offset4:
addi $t1,$0,0
addi $t2,$0,42
beq $a1,1, play1_4
beq $a1,2, play2_4
play1_4:
ori $t8,$t8,8
j draw
play2_4:
ori $t9,$t9,8
j draw

offset5:
addi $t1,$0,42
addi $t2,$0,42
beq $a1,1, play1_5
beq $a1,2, play2_5
play1_5:
ori $t8,$t8,16
j draw
play2_5:
ori $t9,$t9,16
j draw

offset6:
addi $t1,$0,84
addi $t2,$0,42
beq $a1,1, play1_6
beq $a1,2, play2_6
play1_6:
ori $t8,$t8,32
j draw
play2_6:
ori $t9,$t9,32
j draw

offset7:
addi $t1,$0,0
addi $t2,$0,84
beq $a1,1, play1_7
beq $a1,2, play2_7
play1_7:
ori $t8,$t8,64
j draw
play2_7:
ori $t9,$t9,64
j draw

offset8:
addi $t1,$0,42
addi $t2,$0,84
beq $a1,1, play1_8
beq $a1,2, play2_8
play1_8:
ori $t8,$t8,128
j draw
play2_8:
ori $t9,$t9,128
j draw

offset9:
addi $t1,$0,84
addi $t2,$0,84
beq $a1,1, play1_9
beq $a1,2, play2_9
play1_9:
ori $t8,$t8,256
j draw
play2_9:
ori $t9,$t9,256
j draw

draw:
beq $a1, 2, drawtick
j drawx

drawx:
addi $s0, $0, 36
addi $s1, $0, 5
loop1:
add $a0, $0, $s0
add $a0, $a0,$t1  ## add x offset
sll $a0,$a0,8
add $a0,$a0, $s0
add $a0,$a0, $t2  ## add y offset
addi   $v0,$0,34         # system call for LED display 
syscall                 # display 
addi $s0,$s0,-1

bne $s0, $s1, loop1

addi $s2, $0, 36
addi $s0,$0,36
loop2:
add $a0, $0, $s0
add $a0, $a0,$t1  ## add x offset
sll $a0,$a0,8
add $a0,$a0,$s1
add $a0,$a0, $t2  ## add y offset
addi   $v0,$0,34         # system call for LED display 
syscall  
addi $s0,$s0,-1
addi $s1,$s1,1
bne $s1,$s2,loop2

# store $a1 ->($v1)
sw $a1,($v1)
# judge
andi $s0, $t8,7
beq $s0,7,success1
andi $s0, $t8,56
beq $s0,56,success1
andi $s0, $t8,448
beq $s0,448,success1
andi $s0, $t8,73
beq $s0,73,success1
andi $s0, $t8,146
beq $s0,146,success1
andi $s0, $t8,292
beq $s0,292,success1
andi $s0, $t8,273
beq $s0,273,success1
andi $s0, $t8,84
beq $s0,84,success1
# change $a1
addi $a1,$0,2
j exit

# show X success
# draw play1 sucess, and ignore any button
success1:
addi $t7,,$0,1
addi $a0,$0, 0xA3
sll $a0,$a0,8
addi $a0,$a0,0xB2
sll $a0,$a0,8
addi $a0,$a0, 0xCA
sll $a0,$a0,8
addi $a0,$a0,0xA4

addi   $v0,$0,35         # system call for LED display 
syscall 

# change $a1
addi $a1,$0,2
j exit

drawtick:

addi $s0, $0, 6
addi $s1, $0, 20
addi $s2, $0, 13
loop3:
add $a0,$0,$s0
add $a0,$a0,$t1
sll $a0,$a0,8
add $a0,$a0,$s1
add $a0,$a0, $t2  ## add y offset
addi   $v0,$0,34         # system call for LED display 
syscall  
addi $s0,$s0,1
addi $s1,$s1,1
addi $s2,$s2,-1
bne $s2,$0,loop3

addi $s2, $0, 19
loop4:
add $a0,$0,$s0
add $a0,$a0,$t1
sll $a0,$a0,8
add $a0,$a0,$s1
add $a0,$a0, $t2  ## add y offset
addi   $v0,$0,34         # system call for LED display 
syscall  
addi $s0,$s0,1
addi $s1,$s1,-1
addi $s2,$s2,-1
bne $s2,$0,loop4

# store $a1 ->($v1)
sw $a1,($v1)

# judge

# tie
or $t6,$t8,$t9
beq $t6,511,tie
# win
andi $s0, $t9,7
beq $s0,7,success2
andi $s0, $t9,56
beq $s0,56,success2
andi $s0, $t9,448
beq $s0,448,success2
andi $s0, $t9,73
beq $s0,73,success2
andi $s0, $t9,146
beq $s0,146,success2
andi $s0, $t9,292
beq $s0,292,success2
andi $s0, $t9,273
beq $s0,273,success2
andi $s0, $t9,84
beq $s0,84,success2
# change $a1
addi $a1,$0,1
j exit
tie:
addi $a0,$0, 0xC6
sll $a0,$a0,8
addi $a0,$a0,0xBD
sll $a0,$a0,8
addi $a0,$a0, 0xBE
sll $a0,$a0,8
addi $a0,$a0,0xD6

addi   $v0,$0,35         # system call for LED display 
syscall 

j exit
# show tick success
# draw play2 sucess, and ignore any button
success2:
addi $t7,$0,1
addi $a0,$0, 0xA3
sll $a0,$a0,8
addi $a0,$a0,0xB1
sll $a0,$a0,8
addi $a0,$a0, 0xCA
sll $a0,$a0,8
addi $a0,$a0,0xA4

addi   $v0,$0,35         # system call for LED display 
syscall 

# change $a1
addi $a1,$0,1
j exit



exit:
eret
