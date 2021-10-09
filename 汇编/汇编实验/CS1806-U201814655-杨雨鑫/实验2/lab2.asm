.386
DATA SEGMENT USE16
SNAME  DB  'YYX_SHOP',0,0AH,0DH,'$'   ;网店名称，用0结束
BNAME  DB  'YUXIN',0  ;老板姓名
BPASS  DB  '123456',0,0 ,0  ;密码
AUTH   DB  0                 ;当前登录状态，0表示顾客状态，1表示登陆成功，2表示退出程序
GOOD   DB  0                ;当前浏览商品名称或地址（自行确定）
N    EQU   30               ;商品总数
GA1   DB    'PEN', 7 DUP(0) ,10  ;商品名称及折扣
      DW   35,56,200,25,?,?       ; 进货价格，销售价格，进货数量，销售数量，推荐度还未计算
GA2   DB    'BOOK', 6 DUP(0) ,9  ;商品名称及折扣
      DW   12,30,200,5,?,?         ;推荐度还未计算
GAN   DB N-2 DUP( 'TempValue' ,0,8,15,0,20,0,30,0,2,0,?,?);

TEMP DB   20	;用来存储输入的指令
          DB   0
          DB 10 DUP(0)
OUTPUT_CS DB 'CS:$'
TAB  DB '0123456789ABCDEF'

COUNT1 EQU 5    ;用来验证老板姓名
COUNT2 EQU 6    ;用来验证密码
COUNT3 EQU 3    ;用来验证第一个商品名
COUNT4 EQU 4    ;用来验证第二个商品名

NUM EQU 3000
M DW 3000

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
TIP4 DB 0AH,0DH,'SING_UP SUCCESSFUL',0AH,0DH,'$'
TIP5 DB 0AH,0DH,'PASSWORD ERROR',0AH,0DH,'$'
TIP6 DB 0AH,0DH,'PLEASE INPUT COMMODITY NAME:',0AH,0DH,'$'
TIP7 DB 0AH,0DH,'NOT FIND,TRY AGAIN',0AH,0DH,'$'
TIP8 DB 0AH,0DH,'FIND SUCCESSFULLY',0AH,0DH,'$'
TIP9 DB 0AH,0DH,'BUY SUCCESSFULLY',0AH,0DH,'$'
TIP10 DB 0AH,0DH,'PLEASE CHOOSE OPTION',0AH,0DH,'$'
TIP11 DB 0AH,0DH,'NO GOOD IN VIEW',0AH,0DH,'$'
TIP12 DB 0AH,0DH,'CALCULATE SUCCESSFULLY',0AH,0DH,'$'

MENU DB 0AH,0DH,'MENU',0AH,0DH,0AH,0DH,'1.LOGIN 2.SEARCH 3.BUY 4.RECOMMEND 8.OUTPUT CS 9.EXIT',0AH,0DH,'$'

DATA ENDS

STACK SEGMENT USE16 STACK
    DB 300 DUP(0)
STACK ENDS

CODE SEGMENT USE16
    ASSUME DS:DATA,SS:STACK,CS:CODE,ES:DATA
START:
    MOV AX,DATA
    MOV DS,AX
    MOV ES,AX

MOV AL,BYTE PTR GA1+10
    MOV BL,BYTE PTR GA1+13
    MOV BH,10
    IMUL BL
    IDIV BH
    MOV [GA1+21],AL

    MOV AL,BYTE PTR GA2+10
    MOV BL,BYTE PTR GA2+13
    MOV BH,10
    IMUL BL
    IDIV BH
    MOV [GA2+21],AL
    ;计算出实际销售价格
    LEA DX,SNAME    ;把DX寄存器放在商店名的地址处
    MOV AH,9        ;9号中断，输出商店名
    INT 21H
    JMP INSTRUCT

INSTRUCT:
    LEA DX,MENU
    MOV AH,9
    INT 21H
    LEA DX,TIP10
    MOV AH,9
    INT 21H
    LEA DX,TEMP
    MOV AH,10
    INT 21H
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
    CMP AUTH,3  ;判断是否为退出程序
    JZ EXIT

P2:     ;寻找商品
    LEA DX,TIP6     ;提示输入商品名称
    MOV AH,9
    INT 21H
    LEA DX,INCOMMODITY  ;读取输入的商品名称
    MOV AH,10
    INT 21H
    CALL FUN2
    JMP INSTRUCT

P3:
    MOV AX, 0
    CALL TIMER  ;开始计时
    MOV CX,1000  ;初始化计数器
XUNHUAN1:
    CMP GOOD,0  ;观察GOOD是否为0
    JNZ NOTZERO1
    JZ XUNHUAN1
NOTZERO1:
    CALL FUN3
    CALL FUN4
    DEC CX 
    CMP CX,0
    JNZ XUNHUAN1
P3LAST:
    MOV AX,1
    CALL TIMER  ;输出计时结果
    JMP INSTRUCT
P4:
    CALL FUN4
    JMP INSTRUCT
P8:
    CALL FUN8
    JMP INSTRUCT
EXIT:
    MOV AH,4CH
    INT 21H



FUN1 PROC       ;登陆验证
    LEA DX,TIP2     ;提示用户输入姓名
    MOV AH,9
    INT 21H         ;显示提示信息
    LEA DX,INNAME   ;接受姓名
    MOV AH,10
    INT 21H
    CMP INNAME+2,0DH  ;比较输入的是否为回车
    JZ GO0
    CMP INNAME+2,'q'   ;比较是否为退出字符
    JZ GO3
    LEA DX,TIP3     ;提示用户输入密码
    MOV AH,9
    INT 21H
    LEA DX,INPASSWORD
    MOV AH,10
    INT 21H

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
    LEA DX,TIP1     ;输出提示信息
    MOV AH,9
    INT 21H
    RET

WRONG2:             ;密码错误
    MOV AUTH,2
    LEA DX,TIP5
    MOV AH,9
    INT 21H
    RET

LOGIN_SUCCESSFUL:
    MOV AUTH,1
    LEA DX,TIP4
    MOV AH,9
    INT 21H
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
    MOV AUTH,3  ;退出
    RET

FUN1 ENDP       ;结束子程序

FUN2 PROC           ;查找商品，把商品序号返回到GOOD中存储
    LEA SI,GA1
    LEA DI,INCOMMODITY+2
    MOV CL,COUNT3
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
    LEA DX,TIP8
    MOV AH,9
    INT 21H
    MOV GOOD,1      ;1号商品即为所求
    RET

NEXTGOOD:
    LEA SI,GA2
    LEA DI,INCOMMODITY+2
    MOV CL,COUNT4
    CMP CL,INCOMMODITY+1    ;判断字符数是否相同
    JNZ FAILED
FLAG4:
    MOV BL,[DI]         ;移动到第一个字符
    MOV BH,[SI]
    CMP BL,BH
    JNZ FAILED        ;如果两个字符不同，则搜索下一个商品
    INC SI
    INC DI
    DEC CX
    CMP CX,0
    JNZ FLAG4   ;如果CX不为0，则继续循环
    LEA DX,TIP8
    MOV AH,9
    INT 21H
    MOV GOOD,2      ;2号商品即为所求
    RET

FAILED:
    LEA DX,TIP7
    MOV AH,9
    INT 21H
    MOV GOOD,0
    RET

FUN2 ENDP

FUN3 PROC
    CMP GOOD,1
    JZ GOOD1
    CMP GOOD,2
    JZ  GOOD2
    RET
GOOD1:
    MOV AX,WORD PTR GA1+17     ;销售数量
    MOV BX,WORD PTR GA1+15     ;进货数量
    SUB BX,AX
    CMP BX,0
    JNZ PURCHASE1
    RET
PURCHASE1:
    INC WORD PTR GA1+17 
    RET
GOOD2:
    MOV AX,WORD PTR GA2+17     ;销售数量
    MOV BX,WORD PTR GA2+15     ;进货数量
    SUB BX,AX
    CMP BX,0
    JNZ PURCHASE2
    RET
PURCHASE2:
    INC WORD PTR GA2+17 
    RET
FUN3 ENDP

FUN4 PROC
    LEA SI,GA1
    XOR BX,BX
    MOV AX,WORD PTR GA1+17     ;销售数量
    MOV BX,WORD PTR GA1+15     ;进货数量
    SAL BX,1
    IMUL EAX,128   ;已售数量*128
    CWD     ;字转双字
    IDIV BX
    MOV DI,AX   ;存储结果
    MOV AX,WORD PTR GA1+11     ;进货价
    MOV BX,WORD PTR GA1+21		;销售价
    IMUL EAX,128       ;进货价*128
    CWD
    IDIV BX
    ADD AX,DI       ;把两个结果相加
    MOV WORD PTR [GA1+19],AX
    LEA SI,GA2
    XOR BX,BX
    MOV AX,WORD PTR GA2+17
    MOV BX,WORD PTR GA2+15
    SAL BX,1
    IMUL EAX,128
    CWD
    IDIV BX
    MOV DI,AX
    XOR BX,BX
    MOV AX,WORD PTR GA2+11
    MOV BX,WORD PTR GA2+21
    IMUL EAX,128
    CWD
    IDIV BX
    ADD AX,DI
    MOV WORD PTR [GA2+19],AX
    RET
FUN4 ENDP

FUN8 PROC
F8:		
	MOV AH, 15
	INT 10H
	MOV AH, 0
	INT 10H
	LEA DX, OUTPUT_CS
	MOV AH, 9
	INT 21H
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

TIMER	PROC
	PUSH  DX
	PUSH  CX
	PUSH  BX
	MOV   BX, AX
	MOV   AH, 2CH
	INT   21H	     ;CH=hour(0-23),CL=minute(0-59),DH=second(0-59),DL=centisecond(0-100)
	MOV   AL, DH
	MOV   AH, 0
	IMUL  AX,AX,1000
	MOV   DH, 0
	IMUL  DX,DX,10
	ADD   AX, DX
	CMP   BX, 0
	JNZ   _T1
	MOV   CS:_TS, AX
_T0:	POP   BX
	POP   CX
	POP   DX
	RET
_T1:	SUB   AX, CS:_TS
	JNC   _T2
	ADD   AX, 60000
_T2:	MOV   CX, 0
	MOV   BX, 10
_T3:	MOV   DX, 0
	DIV   BX
	PUSH  DX
	INC   CX
	CMP   AX, 0
	JNZ   _T3
	MOV   BX, 0
_T4:	POP   AX
	ADD   AL, '0'
	MOV   CS:_TMSG[BX], AL
	INC   BX
	LOOP  _T4
	PUSH  DS
	MOV   CS:_TMSG[BX+0], 0AH
	MOV   CS:_TMSG[BX+1], 0DH
	MOV   CS:_TMSG[BX+2], '$'
	LEA   DX, _TS+2
	PUSH  CS
	POP   DS
	MOV   AH, 9
	INT   21H
	POP   DS
	JMP   _T0
_TS	DW    ?
 	DB    'Time elapsed in ms is '
_TMSG	DB    12 DUP(0)
TIMER   ENDP

CODE ENDS
    END START

