.386
.MODEL FLAT,STDCALL
OPTION CASEMAP:NONE

WinMain PROTO:DWORD,:DWORD,:DWORD,:DWORD
WndProc PROTO:DWORD,:DWORD,:DWORD,:DWORD
CAMMEND PROTO:DWORD
F2T10 PROTO
CHANGE PROTO

include      D:\masm32\INCLUDE\windows.inc
include      D:\masm32\INCLUDE\user32.inc
include      D:\masm32\INCLUDE\kernel32.inc
include      D:\masm32\INCLUDE\gdi32.inc
includelib   D:\masm32\LIB\user32.lib
includelib   D:\masm32\LIB\kernel32.lib
includelib   D:\masm32\LIB\gdi32.lib



.DATA
	ClassName DB "YYX'S SHOP",0    ;�̵���
	AppName DB "YYX'S SHOP",0
	hInstance DD 0                     ;ʵ�����
	CommandLine DD 0

	;��Ϣ����ʾ��Ϣ
	szDlgTitle DB "A WIN32 PROCESS",0
	szMsg DB "����CS1806������",0
	MB_OK EQU 0
 
	;��ʾ��Ϣ
	My_shop DB "��ӭ����",0
	Num0 DB $-My_shop-1
	Goods_name DB "��Ʒ����",0
	Num1 DB $ - Goods_name-1
	Discount DB "�ۿ�",0
	Num2 DB $-Discount-1
	InPrice DB "������",0
	Num3 DB $-InPrice-1
	OutPrice DB "���ۼ�",0
	Num4 DB $-OutPrice-1
	InNumber DB "��������",0
	Num5 DB $-InNumber-1
	OutNumber DB "��������",0
	Num6 DB $-OutNumber-1
	Recom  DB "�Ƽ���",0
	Num7 DB $-Recom-1
	Fenge DB "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"
	Num8 DB $-Fenge-1

	;��Ʒ��Ϣ�ṹ
	Goods struct
		good_name DB 10 dup(0)	;��Ʒ����
		discount DB 0	;��Ʒ�ۿ�
		inprice DW 0	;�����۸�
		outprice DW 0	;���ۼ۸�
		inmumber DW 0	;��������
		outnumber DW 0	;��������
		recommdation DW 0	;�Ƽ���
	Goods ends

N EQU 5           ;�ݶ�5����Ʒ


BUF Goods <'pencil  ',8,67,133,200,100,0>
    Goods <'book    ',9,26,60,300,200,0>
	Goods <'cola    ',7,50,99,400,250,0>
	Goods <'notebook',7,48,88,180,100,0>
	Goods <'wine    ',8,28,58,200,88,0>

num DD 65
thestr DB 20 DUP(0)
strlength DB 0

.STACK 10000
.CODE 
;----------------------------------������---------------------------
START:
	INVOKE GetModuleHandle,NULL                  ;��ȡ�����汾���ھ��
	MOV hInstance,EAX
	INVOKE GetCommandLine
	MOV CommandLine,EAX
	INVOKE WinMain,hInstance,NULL,CommandLine,SW_SHOWDEFAULT    ;���ô���������
	INVOKE ExitProcess,EAX

;------------------------����������-----------------------------

WinMain PROC hInst:DWORD,hPrevInst:DWORD,CmdLine:DWORD,CmdShow:DWORD
	LOCAL wc: WNDCLASSEX       ;������������Ϣ����Ҫ��Ϣ�ɸýṹ˵��
	LOCAL msg:MSG              ;��Ϣ�ṹ�������ڴ�Ż�ȡ����Ϣ
	LOCAL hwnd:HWND            ;��Ŵ��ھ��
	LOCAL Wwd:DWORD            ;��Ŵ���λ�úʹ�С��Ϣ
	LOCAL Wht:DWORD
	LOCAL Wtx:DWORD
	LOCAL Wty:DWORD
	
	LEA ESI,BUF
	MOV wc.cbSize ,SIZEOF WNDCLASSEX

	MOV wc.style,CS_HREDRAW or CS_VREDRAW
								;���ڷ��
	MOV wc.lpfnWndProc,OFFSET WndProc       ;�����ڹ��̵���ڵ�ַ

	MOV wc.cbWndExtra,NULL
	MOV wc.cbClsExtra,NULL
	PUSH hInst
	POP wc.hInstance
	MOV wc.hbrBackground,COLOR_WINDOW+1       ;������ɫΪ��ɫ
	;MOV wc.lpszMenuName,NULL                 ;�����ϲ˵�
	MOV wc.lpszClassName,OFFSET ClassName
	INVOKE LoadIcon,NULL,IDI_APPLICATION
	MOV wc.hIcon,EAX               ;�����ͼ��ľ��
	MOV wc.hIconSm,0
	INVOKE LoadCursor,NULL,IDC_ARROW
	MOV wc.hCursor,EAX
	INVOKE RegisterClassEx,ADDR wc
	
	MOV Wwd,750
	MOV Wht,400
	MOV Wtx,10
	MOV Wty,10
	
	
INVOKE CreateWindowEx,NULL,ADDR ClassName,ADDR AppName,
	WS_OVERLAPPEDWINDOW+ WS_VISIBLE,   ;��������ʾ�Ĵ���
	Wtx,Wty,Wwd,Wht,
	NULL,NULL,
	hInst,NULL
MOV hwnd,EAX
INVOKE LoadMenu,hInst,600             ;����˵���Դ
INVOKE SetMenu,hwnd,EAX

startLoop:
	INVOKE GetMessage,ADDR msg,NULL,0,0
	CMP EAX,0
	JE EXITLOOP
	INVOKE TranslateMessage,ADDR msg
	INVOKE DispatchMessage,ADDR msg
	JMP startLoop
EXITLOOP:
	MOV EAX,msg.wParam
	RET
WinMain ENDP

;----------------������Ϣ�������---------------
WndProc proc hWin:DWORD,uMsg:DWORD,wParam:DWORD,IParam:DWORD
	LOCAL hdc:HDC
	.if uMsg==WM_COMMAND
		.if wParam==1000             ;����˳�����
			INVOKE PostQuitMessage,NULL
		.elseif wParam==1100         ;�����Ƽ���
			LEA EDI,BUF
			INVOKE CAMMEND,EDI
		.elseif wParam==1300
			MOV CX,4
CHANGE_LOP2:
			INVOKE CHANGE
			LOOP CHANGE_LOP2
		.elseif wParam==1200
			INVOKE GetDC,hWin
			MOV hdc,EAX
			INVOKE TextOut,hdc,10,15,ADDR My_shop,Num0
			INVOKE TextOut,hdc,10,45,ADDR Goods_name,Num1
			INVOKE TextOut,hdc,110,45,ADDR Discount,Num2
			INVOKE TextOut,hdc,210,45,ADDR InPrice,Num3
			INVOKE TextOut,hdc,310,45,ADDR OutPrice,Num4
			INVOKE TextOut,hdc,410,45,ADDR InNumber,Num5
			INVOKE TextOut,hdc,510,45,ADDR OutNumber,Num6
			INVOKE TextOut,hdc,610,45,ADDR Recom,Num7
			INVOKE TextOut,hdc,10,65,ADDR Fenge,Num8
                ;���ȫ����Ʒ��Ϣ
				LEA ESI,BUF
				MOV EBX,21
				MOV ECX,0
				MOV num,90
			goods_loop:       
				PUSH ECX                  
				INVOKE TextOut,hdc,10,num,ADDR [ESI],8             ;�����Ʒ��
				XOR EAX,EAX

				MOV AL,BYTE PTR [ESI+10]                           ;����ۿ�
				INVOKE F2T10
				INVOKE TextOut,hdc,110,num,ADDR thestr,strlength

				MOV AX,WORD PTR [ESI+11]                           ;���������
				INVOKE F2T10
				INVOKE TextOut,hdc,210,num,ADDR thestr,strlength

				MOV AX,WORD PTR [ESI+13]                           ;������ۼ�
				INVOKE F2T10
				INVOKE TextOut,hdc,310,num,ADDR thestr,strlength

				MOV AX,WORD PTR [ESI+15]                           ;�����������
				INVOKE F2T10
				INVOKE TextOut,hdc,410,num,ADDR thestr,strlength

				MOV AX,WORD PTR [ESI+17]                           ;�����������
				INVOKE F2T10
				INVOKE TextOut,hdc,510,num,ADDR thestr,strlength

				MOV AX,WORD PTR [ESI+19]                           ;����Ƽ���
				INVOKE F2T10
				INVOKE TextOut,hdc,610,num,ADDR thestr,strlength

				POP ECX
				INC CX
				ADD ESI,EBX
				ADD num,30
				CMP CX,5
				JB goods_loop

		.elseif wParam==1900          ;�鿴��Ϣ
			INVOKE MessageBoxA,0,ADDR szMsg,ADDR szDlgTitle,MB_OK
			;
		.endif
	.elseif uMsg==WM_DESTROY
		INVOKE PostQuitMessage,NULL
	.else
		INVOKE DefWindowProc,hWin,uMsg,wParam,IParam
		ret
	.endif
		MOV EAX,0
		RET
WndProc endp


;�����Ƽ���
CAMMEND PROC  PAR1:DWORD                          ;����Ϊ��Ʒ��ַ
		PUSHA;����16λ�洢����ջ

CYCLE_BEGIN:
		MOV CX,N        ;��Ʒ����CX
		MOV EBP,PAR1
CYCLE:
		MOV AX,DS:[EBP+11];������
		MOV BX,DS:[EBP+13];���ۼ�
		MOV SI,128
		MUL SI;�����۳�128
		DIV BX;���ó����ۼ�
		PUSH AX
		MOV SI,10
		MOVSX BX,BYTE PTR DS:[EBP+10];�ۿ�
		POP AX
		MUL SI;�����۳�128�������ۼ۳�10
		DIV BX;�ϲ����ó����ۿ�
		PUSH AX;��ջ
		MOV AX,DS:[EBP+17];��������
		MOV BX,DS:[EBP+15];��������
		MOV SI,128
		MUL SI;����������128
		DIV BX;���ó�����������
		POP BX;��ջ��BX
		ADD AX,BX;�Ƽ������
		MOV DS:[EBP+19],AX;���Ƽ��ȷ�����Ʒ��Ϣ֮��

CYCLE_JUDGE:
		;ѭ�������ж�
		ADD EBP,BYTE PTR 21
		DEC CX;CX��Ϊ�����ѭ����ֱ��N����Ʒ�Ƽ��ȶ��������
		JNZ CYCLE

		POPA;�ָ��ֳ�
		RET;����
CAMMEND ENDP


	
F2T10 PROC             ;��ڲ���ΪҪ��������ֱ�����EAX�У����ܽ�ת��������ݱ��浽�ص�ַ
	PUSH ESI
	PUSH CX
	PUSH BX
	PUSH DX
	XOR ECX,ECX          ;����������
	MOV BX,10         ;����
F2T1:
	XOR EDX,EDX
	DIV EBX
	PUSH DX
	INC CX
	OR EAX,EAX
	JNZ F2T1
	
	LEA ESI,thestr
	MOV strlength,CL       ;���洮����
	MOV EDX,0
	MOV EBX,0
F2T3:
	POP BX
	ADD BX,30H
	MOV BYTE PTR [ESI+EDX],BL  ;��ת�����ASCII�뱣�浽thestr��ַ��
	INC EDX
	DEC CX
	CMP CX,0
	JNZ F2T3
	POP DX
	POP BX
	POP CX
	POP ESI
	RET
F2T10 ENDP



CHANGE PROC

	PUSHA
	MOV ECX,4
	LEA ESI,BUF
	MOV EDX,0
	MOV EAX,0
	MOV EBX,0
SORT_LOP1:
	MOV AX,WORD PTR [ESI+19]
	MOV BX,WORD PTR [ESI+40]
	CMP AX,BX
	JB CHANGE_TWO 
BACK:
	ADD ESI,21
	XOR AX,AX
	XOR BX,BX
	LOOP SORT_LOP1
	POPA
	RET


CHANGE_TWO:
	PUSHA
	MOV ECX,5
CHANGE_LOP:
	MOV EAX,0
	MOV EBX,0
	MOV EAX,DWORD PTR [ESI]
	MOV EBX,DWORD PTR [ESI+21]
	MOV DWORD PTR [ESI],EBX
	MOV DWORD PTR [ESI+21],EAX
	ADD ESI,4
	LOOP CHANGE_LOP
	MOV AL,BYTE PTR [ESI-3]
	MOV BL,BYTE PTR [ESI+18]
	MOV BYTE PTR [ESI-3],BL
	MOV BYTE PTR [ESI+18],AL
	POPA
	JMP BACK


CHANGE ENDP

END START
