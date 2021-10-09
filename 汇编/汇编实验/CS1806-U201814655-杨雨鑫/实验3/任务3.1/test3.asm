NAME SHOP_MAIN      ;主商店
EXTRN FUN6:NEAR,PRINT_INFO:NEAR
PUBLIC GOOD,GA1
.386
INCLUDE MACRO.LIB
DATA SEGMENT USE16 PARA PUBLIC 'D1'
SNAME  DB  0AH,0DH,'YYX_SHOP',0,0AH,0DH,'$'   ;网店名称，用0结束
BNAME  DB  'YUXIN',0  ;老板姓名
BPASS  DB  '123456',0,0 ,0  ;密码
AUTH   DB  0                 ;当前登录状态，0表示顾客状态，1表示登陆成功，2表示退出程序
GOOD   DW  0                ;当前浏览商品名称或地址（自行确定）
N    EQU   30               ;商品总数
GA1   DB    'PEN', 6 DUP(0) ,3 ,10  ;商品名称及折扣
      DW   35,56,70,25,?,?       ; 进货价格，销售价格，进货数量，销售数量，推荐度还未计算
GA2   DB    'BOOK', 5 DUP(0) ,4 ,9  ;商品名称及折扣
      DW   12,30,25,5,?,?         ;推荐度还未计算
GAN   DB N-2 DUP( 'TempValue' ,0,8,15,0,20,0,30,0,2,0,?,0,?,0)

TEMP DB   10	;用来存储输入的指令
          DB   0
          DB 10 DUP(0)


OUTPUT_CS DB 'CS:$'
TAB  DB '0123456789ABCDEF'
COUNT1 EQU 5    ;用来验证老板姓名
COUNT2 EQU 6    ;用来验证密码
COUNT3 EQU 3    ;用来验证第一个商品名
COUNT4 EQU 4    ;用来验证第二个商品名

INNAME DB 20    ;代表最多输入20个字母
       DB 0     ;用来记录输入的字母数量
       DB 20 DUP(0) ;建立一个数组来存储输入的姓名
INPASSWORD DB 10    ;最多输入10个数字
           DB 0     ;用来记录输入的数字数量
           DB 10 DUP(0) ;建立一个数组用来存储输入的密码
INCOMMODITY DB 10       ;用来存储输入的商品名称
            DB 0
            DB 10 DUP(0)

TIP1 DB 0AH,0DH,'NAME ERROR',0AH,0DH,'$'         ;提示信息
TIP2 DB 0AH,0DH,'PLEASE INPUT NAME:',0AH,0DH,'$'
TIP3 DB 0AH,0DH,'PLEASE INPUT PASSWORD:',0AH,0DH,'$'
TIP4 DB 0AH,0DH,'SIGN_UP SUCCESSFUL',0AH,0DH,'$'
TIP5 DB 0AH,0DH,'PASSWORD ERROR',0AH,0DH,'$'
TIP6 DB 0AH,0DH,'PLEASE INPUT COMMODITY NAME:',0AH,0DH,'$'
TIP7 DB 0AH,0DH,'NOT FIND,TRY AGAIN',0AH,0DH,'$'
TIP8 DB 0AH,0DH,'FIND SUCCESSFULLY',0AH,0DH,'$'
TIP9 DB 0AH,0DH,'BUY SUCCESSFULLY',0AH,0DH,'$'
TIP10 DB 0AH,0DH,'PLEASE CHOOSE OPTION',0AH,0DH,'$'
TIP11 DB 0AH,0DH,'NO GOOD IN VIEW',0AH,0DH,'$'
TIP12 DB 0AH,0DH,'CALCULATE SUCCESSFULLY',0AH,0DH,'$'
TIP13 DB 0AH,0DH,'BUY FAILED',0AH,0DH,'$'
TIP20 DB 0AH,0DH,'YOU ARE NOT BOSS',0AH,0DH,'$' 

MENU DB 0AH,0DH,'MENU',0AH,0DH,0AH,0DH,'1.LOGIN 2.SEARCH 3.BUY 4.RECOMMEND 6.MODIFY 8.OUTPUT CS 9.EXIT',0AH,0DH,'$'



DATA ENDS

STACK SEGMENT USE16 PARA STACK 'S1'
    DB 300 DUP(0)
STACK ENDS

CODE SEGMENT USE16 PARA PUBLIC 'C1'
    ASSUME DS:DATA,SS:STACK,CS:CODE,ES:DATA
START:
    MOV AX,DATA
    MOV DS,AX
    MOV ES,AX
INSTRUCT:
    MOV CX,N
    LEA SI,GA1
LOOP1:
    MOV AL,BYTE PTR [SI+10]
    MOV BL,BYTE PTR [SI+13]
    MOV BH,10
    IMUL BL
    IDIV BH
    MOV [SI+21],AL         ;计算出实际销售价格
    ADD SI,23
    LOOP LOOP1

    WRITE SNAME
    WRITE MENU
    WRITE TIP10
    INPUT TEMP
    MOV	AL,TEMP+2
    CMP AL,'0'
    JZ EXIT
    CMP AL,'1'
    JZ P1
    CMP AL,'2'
    JZ P2
    CMP AL,'3'
    JZ P3
    CMP AL,'4'
    JZ P4
    CMP AL,'6'
    JZ P6
    CMP AL,'8'
    JZ P8
    CMP AL,'9'
    JZ EXIT

P1:
    CALL FUN1   ;进入第一个功能函数
    CMP AUTH,0  ;判断是否为顾客状态
    JZ INSTRUCT
    CMP AUTH,1  ;判断是否为登录状态
    JZ INSTRUCT
    CMP AUTH,2  ;判断是否为输入错误
    JZ P1

P2:     ;寻找商品
    WRITE TIP6
    INPUT INCOMMODITY
    CALL FUN2
    JMP INSTRUCT

P3:
    CMP GOOD,0  ;观察GOOD是否为0
    JNZ NOTZERO1
    WRITE TIP11
    JZ INSTRUCT
NOTZERO1:
    CALL FUN3
    JMP INSTRUCT
P4:
    CALL FUN4
    JMP INSTRUCT
P6:
    CMP AUTH,0
    JNZ COMPAREGOOD
    WRITE TIP20
    JZ INSTRUCT
COMPAREGOOD:
    CMP GOOD,0  ;观察GOOD是否为0
    JNZ NOTZERO2
    WRITE TIP11
    JZ INSTRUCT
NOTZERO2:
    CALL FUN6
    JMP INSTRUCT

P8:
    CALL FUN8
    JMP INSTRUCT
EXIT:
    MOV AH,4CH
    INT 21H



FUN1 PROC       ;登陆验证
    WRITE TIP2        ;显示提示信息
    INPUT INNAME
    CMP INNAME+2,0DH  ;比较输入的是否为回车
    JZ GO0
    CMP INNAME+2,'q'   ;比较是否为退出字符
    JZ GO3
    WRITE TIP3
    INPUT INPASSWORD

    MOV CL,COUNT1           ;验证姓名
	LEA SI,BNAME
	LEA DI,INNAME+2
	CMP CL,INNAME+1        ;长度不相等，姓名肯定错误
    JNZ WRONG1

FLAG1:
    MOV BL,[DI]
	CMP BYTE PTR [SI],BL
	JNZ WRONG1
	INC SI
	INC DI
	DEC CX
	CMP CX,0		;比较计数器是否为0
	JNZ FLAG1

	MOV CL,COUNT2          ;验证密码
	LEA SI,BPASS
	LEA DI,INPASSWORD+2
	CMP CL,INPASSWORD+1        ;长度不相同，密码肯定错误
    JNZ WRONG2

FLAG2:
    MOV BL,[DI]
	CMP BYTE PTR [SI],BL
	JNZ WRONG2
	INC SI
	INC DI
	DEC CX
	CMP CX,0
	JNZ FLAG2

    JMP LOGIN_SUCCESSFUL    ;成功登入

WRONG1:             ;姓名错误
    MOV AUTH,2
    WRITE TIP1
    RET

WRONG2:             ;密码错误
    MOV AUTH,2
    WRITE TIP5
    RET

LOGIN_SUCCESSFUL:
    MOV AUTH,1
    WRITE TIP4
    RET

GO0:
    MOV AUTH,0  ;代表为顾客状态
    RET
GO1:
    MOV AUTH,1
    RET
GO2:
    MOV AUTH,2  ;输入错误
    RET
GO3:
    MOV AUTH,0  ;退出
    RET

FUN1 ENDP       ;结束子程序

FUN2 PROC           ;查找商品，把商品序号返回到GOOD中存储
    LEA DI,INCOMMODITY+2
    MOV CX,N
    LEA SI,GA1
LOOP2:
    PUSH CX
    MOV CX,0
    MOV CL,[SI+9]
    CMP CL,INCOMMODITY+1    ;判断字符数是否相同
    JNZ NEXTGOOD
FLAG3:
    MOV BL,[DI]         ;移动到第一个字符
    MOV BH,[SI]
    CMP BL,BH
    JNZ NEXTGOOD        ;如果两个字符不同，则搜索下一个商品
    INC SI
    INC DI
    DEC CX
    CMP CX,0
    JNZ FLAG3   ;如果CX不为0，则继续循环
    JMP SUCCESS
NEXTGOOD:
    ADD SI,23
    POP CX
    LOOP LOOP2
    JMP SEARCHFAILED

SUCCESS:
    POP CX
    WRITE TIP8
    SUB CX,30
    NEG CX
    INC CX
    MOV GOOD,CX      ;商品即为所求
    CALL PRINT_INFO
    RET
SEARCHFAILED:
    WRITE TIP7
    MOV GOOD,0
    RET

FUN2 ENDP

FUN3 PROC
    MOV CX,GOOD
    DEC CX
    LEA SI,GA1
LOOP3:
    ADD SI,23
    LOOP LOOP3
    JMP BUY
BUY:
    MOV AX,WORD PTR [SI+17]     ;销售数量
    MOV BX,WORD PTR [SI+15]     ;进货数量
    SUB BX,AX
    CMP BX,0
    JZ BUYFAILED
    INC WORD PTR [SI+17] 
    WRITE TIP9
    RET
BUYFAILED:
    WRITE TIP13
    RET

FUN3 ENDP

FUN4 PROC
    PUSH SI
    PUSH CX
    PUSH EBX
    PUSH EAX
    PUSH EDX
    MOV CX,N
    LEA SI,GA1
XUNHUAN:
    PUSH CX
    MOV EDX,0
    XOR EBX,EBX
    XOR EAX,EAX
    MOV AX,WORD PTR [SI+17]     ;销售数量
    MOV BX,WORD PTR [SI+15]     ;进货数量
    SAL EBX,1
    SAL EAX,7   ;已售数量*128
    IDIV EBX
    MOV CX,AX   ;存储结果
    XOR EBX,EBX
    XOR EAX,EAX
    MOV AX,WORD PTR [SI+11]     ;进货价
    MOV BX,WORD PTR [SI+21]		;销售价
    MOV EDX,0
    SAL EAX,7       ;进货价*128
    IDIV EBX
    ADD AX,CX       ;把两个结果相加
    MOV WORD PTR [SI+19],AX
    ADD SI,23
    POP CX
    LOOP XUNHUAN 
    WRITE TIP12
    POP EDX
    POP EAX
    POP EBX
    POP CX
    POP SI
    RET
FUN4 ENDP


FUN8 PROC
F8:		
	MOV AH, 15
	INT 10H
	MOV AH, 0
	INT 10H
	WRITE OUTPUT_CS
	LEA BX, TAB		;16进制字符转换表放入BX

	MOV AX, CS
	AND AX, 0F000H
	SHR AX, 12
	XLAT TAB
	MOV DL, AL
	MOV AH,	2		;输出CS的最高位
	INT 21H
	
	MOV AX, CS
	AND AX, 0F00H
	SHR AX, 8
	XLAT TAB
	MOV DL, AL
	MOV AH, 2		;输出CS的次高位
	INT 21H
	
	MOV AX, CS
	AND AX, 00F0H
	SHR AX, 4
	XLAT TAB
	MOV DL, AL
	MOV AH, 2		;输出CS的次低位
	INT 21H
		
	MOV AX, CS	
	AND AX, 000FH
	XLAT TAB
	MOV DL, AL
	MOV AH, 2		;输出CS的最低位
	INT 21H

	MOV AH, 1
	INT 21H
	JMP INSTRUCT
FUN8 ENDP


CODE ENDS
    END START

