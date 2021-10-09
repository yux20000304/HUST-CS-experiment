.386
STACK 	SEGMENT USE16 STACK
        DB 200 DUP(0)
STACK 	ENDS

DATA	SEGMENT USE16	
		SUM  DW  ?
    X    DB  50
    Y    DD  -1000
    Z    DB  'HELLO!$'
DATA	ENDS

CODE	SEGMENT USE16
		ASSUME  CS:CODE, SS:STACK, DS:DATA, ES:DATA
START:	MOV  AX, DATA
		MOV  DS, AX
		
    MOV AX, 0
    CALL TIMER
    
		MOV  CX, 50		
		MOV  AX, 0		
		MOV  BX, 1	
NEXT:	ADD  AX, BX
		INC  BX
		INC  BX			
		DEC  CX		
		JNE   NEXT		
		MOV  SUM, AX
		
    MOV AX, 1
    CALL TIMER
    
		MOV  AH, 4CH
		INT  21H	
    
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
   
CODE	ENDS
	END  START
