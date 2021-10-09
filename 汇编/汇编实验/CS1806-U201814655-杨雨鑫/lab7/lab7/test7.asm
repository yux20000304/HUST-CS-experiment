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
	ClassName DB "YYX'S SHOP",0    ;商店名
	AppName DB "YYX'S SHOP",0
	hInstance DD 0                     ;实例句柄
	CommandLine DD 0

	;消息框显示信息
	szDlgTitle DB "A WIN32 PROCESS",0
	szMsg DB "我是CS1806杨雨鑫",0
	MB_OK EQU 0
 
	;提示信息
	My_shop DB "欢迎光临",0
	Num0 DB $-My_shop-1
	Goods_name DB "商品名称",0
	Num1 DB $ - Goods_name-1
	Discount DB "折扣",0
	Num2 DB $-Discount-1
	InPrice DB "进货价",0
	Num3 DB $-InPrice-1
	OutPrice DB "销售价",0
	Num4 DB $-OutPrice-1
	InNumber DB "进货总数",0
	Num5 DB $-InNumber-1
	OutNumber DB "已售总数",0
	Num6 DB $-OutNumber-1
	Recom  DB "推荐度",0
	Num7 DB $-Recom-1
	Fenge DB "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"
	Num8 DB $-Fenge-1

	;商品信息结构
	Goods struct
		good_name DB 10 dup(0)	;商品名称
		discount DB 0	;商品折扣
		inprice DW 0	;进货价格
		outprice DW 0	;销售价格
		inmumber DW 0	;进货数量
		outnumber DW 0	;销售数量
		recommdation DW 0	;推荐度
	Goods ends

N EQU 5           ;暂定5种商品


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
;----------------------------------主程序---------------------------
START:
	INVOKE GetModuleHandle,NULL                  ;获取并保存本窗口句柄
	MOV hInstance,EAX
	INVOKE GetCommandLine
	MOV CommandLine,EAX
	INVOKE WinMain,hInstance,NULL,CommandLine,SW_SHOWDEFAULT    ;调用窗口主程序
	INVOKE ExitProcess,EAX

;------------------------窗口主程序-----------------------------

WinMain PROC hInst:DWORD,hPrevInst:DWORD,CmdLine:DWORD,CmdShow:DWORD
	LOCAL wc: WNDCLASSEX       ;创建主窗口信息所需要信息由该结构说明
	LOCAL msg:MSG              ;信息结构变量用于存放获取的消息
	LOCAL hwnd:HWND            ;存放窗口句柄
	LOCAL Wwd:DWORD            ;存放窗口位置和大小信息
	LOCAL Wht:DWORD
	LOCAL Wtx:DWORD
	LOCAL Wty:DWORD
	
	LEA ESI,BUF
	MOV wc.cbSize ,SIZEOF WNDCLASSEX

	MOV wc.style,CS_HREDRAW or CS_VREDRAW
								;窗口风格
	MOV wc.lpfnWndProc,OFFSET WndProc       ;本窗口过程的入口地址

	MOV wc.cbWndExtra,NULL
	MOV wc.cbClsExtra,NULL
	PUSH hInst
	POP wc.hInstance
	MOV wc.hbrBackground,COLOR_WINDOW+1       ;背景颜色为白色
	;MOV wc.lpszMenuName,NULL                 ;窗口上菜单
	MOV wc.lpszClassName,OFFSET ClassName
	INVOKE LoadIcon,NULL,IDI_APPLICATION
	MOV wc.hIcon,EAX               ;保存带图标的句柄
	MOV wc.hIconSm,0
	INVOKE LoadCursor,NULL,IDC_ARROW
	MOV wc.hCursor,EAX
	INVOKE RegisterClassEx,ADDR wc
	
	MOV Wwd,750
	MOV Wht,400
	MOV Wtx,10
	MOV Wty,10
	
	
INVOKE CreateWindowEx,NULL,ADDR ClassName,ADDR AppName,
	WS_OVERLAPPEDWINDOW+ WS_VISIBLE,   ;创建可显示的窗口
	Wtx,Wty,Wwd,Wht,
	NULL,NULL,
	hInst,NULL
MOV hwnd,EAX
INVOKE LoadMenu,hInst,600             ;读入菜单资源
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

;----------------窗口消息处理程序---------------
WndProc proc hWin:DWORD,uMsg:DWORD,wParam:DWORD,IParam:DWORD
	LOCAL hdc:HDC
	.if uMsg==WM_COMMAND
		.if wParam==1000             ;点击退出程序
			INVOKE PostQuitMessage,NULL
		.elseif wParam==1100         ;计算推荐度
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
                ;输出全部商品信息
				LEA ESI,BUF
				MOV EBX,21
				MOV ECX,0
				MOV num,90
			goods_loop:       
				PUSH ECX                  
				INVOKE TextOut,hdc,10,num,ADDR [ESI],8             ;输出商品名
				XOR EAX,EAX

				MOV AL,BYTE PTR [ESI+10]                           ;输出折扣
				INVOKE F2T10
				INVOKE TextOut,hdc,110,num,ADDR thestr,strlength

				MOV AX,WORD PTR [ESI+11]                           ;输出进货价
				INVOKE F2T10
				INVOKE TextOut,hdc,210,num,ADDR thestr,strlength

				MOV AX,WORD PTR [ESI+13]                           ;输出销售价
				INVOKE F2T10
				INVOKE TextOut,hdc,310,num,ADDR thestr,strlength

				MOV AX,WORD PTR [ESI+15]                           ;输出进货总数
				INVOKE F2T10
				INVOKE TextOut,hdc,410,num,ADDR thestr,strlength

				MOV AX,WORD PTR [ESI+17]                           ;输出已售总数
				INVOKE F2T10
				INVOKE TextOut,hdc,510,num,ADDR thestr,strlength

				MOV AX,WORD PTR [ESI+19]                           ;输出推荐度
				INVOKE F2T10
				INVOKE TextOut,hdc,610,num,ADDR thestr,strlength

				POP ECX
				INC CX
				ADD ESI,EBX
				ADD num,30
				CMP CX,5
				JB goods_loop

		.elseif wParam==1900          ;查看信息
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


;计算推荐度
CAMMEND PROC  PAR1:DWORD                          ;参数为商品首址
		PUSHA;所有16位存储器进栈

CYCLE_BEGIN:
		MOV CX,N        ;商品数给CX
		MOV EBP,PAR1
CYCLE:
		MOV AX,DS:[EBP+11];进货价
		MOV BX,DS:[EBP+13];销售价
		MOV SI,128
		MUL SI;进货价乘128
		DIV BX;所得除销售价
		PUSH AX
		MOV SI,10
		MOVSX BX,BYTE PTR DS:[EBP+10];折扣
		POP AX
		MUL SI;进货价乘128除以销售价乘10
		DIV BX;上步所得除以折扣
		PUSH AX;入栈
		MOV AX,DS:[EBP+17];进货总数
		MOV BX,DS:[EBP+15];已售数量
		MOV SI,128
		MUL SI;进货总数乘128
		DIV BX;所得除以已售数量
		POP BX;退栈到BX
		ADD AX,BX;推荐度相加
		MOV DS:[EBP+19],AX;将推荐度放在商品信息之后

CYCLE_JUDGE:
		;循环继续判断
		ADD EBP,BYTE PTR 21
		DEC CX;CX不为零继续循环，直到N个商品推荐度都计算完毕
		JNZ CYCLE

		POPA;恢复现场
		RET;返回
CAMMEND ENDP


	
F2T10 PROC             ;入口参数为要输出的数字保存在EAX中，功能将转化后的数据保存到特地址
	PUSH ESI
	PUSH CX
	PUSH BX
	PUSH DX
	XOR ECX,ECX          ;计数器清零
	MOV BX,10         ;基数
F2T1:
	XOR EDX,EDX
	DIV EBX
	PUSH DX
	INC CX
	OR EAX,EAX
	JNZ F2T1
	
	LEA ESI,thestr
	MOV strlength,CL       ;保存串长度
	MOV EDX,0
	MOV EBX,0
F2T3:
	POP BX
	ADD BX,30H
	MOV BYTE PTR [ESI+EDX],BL  ;将转换后的ASCII码保存到thestr地址中
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
