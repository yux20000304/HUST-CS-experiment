NAME PRINT_AND_MODIFY      ;功能2和功能6

EXTRN GOOD:WORD,GA1:BYTE
PUBLIC FUN6,PRINT_INFO
.386
INCLUDE MACRO.LIB
DATA SEGMENT USE16 PARA PUBLIC 'D1'

INNUM DB   10	;用来存储输入的数字
        DB   0
        DB 10 DUP(0)
NUM DW 20 DUP(0)    ;用来存储输出的十进制字符

TIP14 DB 0AH,0DH,'DISCOUNT: ','$'
TIP15 DB 0AH,0DH,'COST PRICE: ','$'
TIP16 DB 0AH,0DH,'SELL PRICE: ','$'
TIP17 DB 0AH,0DH,'BUY QUANTITY: ','$'
TIP18 DB 0AH,0DH,'SALES QUANTITY: ','$'
TIP19 DB 0AH,0DH,'RECOMMENDATION: ','$'
TIP21 DB '>>','$'
DATA ENDS

STACK SEGMENT USE16 PARA STACK 'S1'
    DB 300 DUP(0)
STACK ENDS

CODE SEGMENT USE16 PARA PUBLIC 'C1'
    ASSUME DS:DATA,SS:STACK,CS:CODE,ES:DATA
FUN6 PROC
    MOV CX,GOOD
    DEC CX
    LEA SI,GA1
    CMP CX,0
    JZ PRINT_COMMODITY_NAME
LOOP6:
    ADD SI,23
    LOOP LOOP6
PRINT_COMMODITY_NAME:
    PUSH SI
    MOV CL,BYTE PTR [SI+9]
LOOP7:
    MOV DL,BYTE PTR [SI]
    MOV AH,2
    INT 21H
    INC SI
    LOOP LOOP7      ;输出商品名称
    POP SI
    ADD SI,10

    WRITE TIP14
    MOV EAX,0
    MOV AL,[SI]
    CALL RADIX
    WRITE TIP21
    PUSH SI
    CALL LOAD_DATA
    POP SI
    MOV [SI],AL     ;修改折扣
    ADD SI,1

    WRITE TIP15
    MOV EAX,0
    MOV AX,[SI]
    CALL RADIX
    WRITE TIP21
    PUSH SI
    CALL LOAD_DATA
    POP SI
    MOV [SI],AX     ;修改进货价格
    ADD SI,2

    WRITE TIP16
    MOV EAX,0
    MOV AX,[SI]
    CALL RADIX
    WRITE TIP21
    PUSH SI
    CALL LOAD_DATA
    POP SI
    MOV [SI],AX     ;修改销售价格
    ADD SI,2

    WRITE TIP17
    MOV EAX,0
    MOV AX,[SI]
    CALL RADIX
    WRITE TIP21
    PUSH SI
    CALL LOAD_DATA
    POP SI
    MOV [SI],AX     ;修改进货数量
    ADD SI,2

    RET
FUN6 ENDP


PRINT_INFO PROC
    MOV CX,GOOD
    DEC CX
    LEA SI,GA1
    CMP CX,0
    JZ PRINT_NAME
LOOP4:
    ADD SI,23
    LOOP LOOP4
PRINT_NAME:
    PUSH SI
    MOV CL,BYTE PTR [SI+9]
LOOP5:
    MOV DL,BYTE PTR [SI]
    MOV AH,2
    INT 21H
    INC SI
    LOOP LOOP5      ;输出商品名称
    POP SI
    ADD SI,10
    WRITE TIP14
    MOV EAX,0
    MOV AL,[SI]
    CALL RADIX
    INC SI
    WRITE_NUM TIP15
    ADD SI,2
    WRITE_NUM TIP16
    ADD SI,2
    WRITE_NUM TIP17
    ADD SI,2
    WRITE_NUM TIP18
    ADD SI,2
    WRITE_NUM TIP19
    ADD SI,2
    MOV DL,0AH
    MOV AH,2
    INT 21H
    RET

PRINT_INFO ENDP

RADIX PROC      ;需要事先把EAX赋值
	PUSH CX
	PUSH EDX
    PUSH SI
    MOV SI,NUM
	XOR CX,CX
	MOV EBX,10
LOP1:
	XOR EDX,EDX
	DIV EBX
	PUSH DX
	INC CX
	OR EAX,EAX
	JNZ LOP1
LOP2:
	POP AX
	CMP AL,10
	JB L1
	ADD AL,7
L1:
	ADD AL,30H
	MOV DL,AL
    MOV AH,2
    INT 21H
	INC SI
	LOOP LOP2
    POP SI
	POP EDX
	POP CX
	RET
RADIX ENDP

LOAD_DATA PROC
    INPUT INNUM     ;读取数字
    MOV CX,0
    MOV CL,INNUM+1  ;计数器初始化
    LEA SI,INNUM+2
    MOV AX,0
LOOP8:
    IMUL AX,10
    MOV BX,0
    MOV BL,BYTE PTR [SI]
    SUB BX,30H
    ADD AX,BX
    INC SI
    LOOP LOOP8
    RET

LOAD_DATA ENDP
CODE ENDS
END
