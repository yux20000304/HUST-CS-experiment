#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MaxNumVar 100000

#define TRUE 1

#define FALSE 0

#define OK 1


typedef struct varWatch
{
	struct varList *positive; //邻接表:正文字，负文字.
	struct varList *negative;
	int pos_num;
	int neg_num;
	int flag;
} Var_watch,varWatch;

typedef struct varList
{
	struct clause *p;	 //指向一个子句，用来存储该子句的地址
	struct varList *next; //指向下一个与该文字关联的子句
	int satisfied;
} Var_List,VarList;

typedef struct clause
{
	struct clauseLiteral *p;   //指向子句中的下一个文字
	struct clause *nextclause; //指向下一个子句
	int word_num;
	int flag;
} clause;

typedef struct  clauseLiteral
{
	int data;					//文字的值
	struct clauseLiteral *next; //指向子句中的下一个文字
} clauseLiteral;

typedef int status;
static int number_var;  //变元数
static int clause_num;  //语句数

int answer[MaxNumVar];	//完成答案输出
int stack_answer[MaxNumVar];//搜索路径栈
int *top=stack_answer,*bottom=stack_answer;

int decision[MaxNumVar];
int *first=decision,*last=decision;

int InitSat(clause **S, Var_watch *var_watch);
int LoadCnf(clause **S, Var_watch var_watch[], FILE *fp);
int GetNum(FILE *fp);
int Putclause(clause *ctemp, int var, Var_watch var_watch[]);
int abs(int a);
int DPLL(clause *S,Var_watch *var_watch);
clause *pan_duan(clause *S);
int unique(clause *single,Var_watch *var_watch);
int empty_set(clause *q);
int empty_clause(clause *q);
int stragety(Var_watch *var_watch);
int reset(varWatch *var_watch,int temp);
int delete_var(clause *pt,int temp);
int search(Var_watch *var_watch,int temp);
int print_answer();
int save_answer(int result, char *filename,int time);
int SAT();
int answer_test(clause *S,FILE *fp,varWatch *var_watch);
int last_branch(varWatch *var_watch);



char cnfpath[100];

status Sudoku();
status InitSudoku(int level);
status calculate(int n, int m);
status Generatecnf(int level);
status Rule1(int level, FILE *fp);
status Rule2(int level, FILE *fp);
status Rule3(int level, FILE *fp);
void Rule2_clause(int arr[], int level, int wordnum, int k1, int k2, FILE *fp);


int main() {
	int op = 1;
	while (op) {
		printf("\n\n");
		printf("\t\t                     Menu \n");
		printf("\t=====================================================\n");
		printf("\t\t1.  Sudoku   2.  SAT    0.Exit\n");
		printf("\t=====================================================\n");
		printf("\t\t        CS1806 YYX U201814655\n\n\n");
		printf("\t\t Choose your operation[0~2]: ");
		scanf("%d", &op);
		system("cls");
		switch (op) {
		case 1:
		    Sudoku();
			break;
		case 2:
			SAT();
			break;
		case 0:
			exit(0);
		default:
			printf("\t\t\tPlease choose your operation again[0~2]:");
			scanf("%d", &op);
		}
	}
	return 0;
}



int SAT()
{
    clause *S = NULL;                   //分配一个字句指针
    Var_watch var_watch[MaxNumVar + 1]; //最大变元数目加一个空间
    FILE *fp;                           //文件指针
    char filename[300];                 //文件名
    int op = 1, result, i;
    clock_t start, finish;
    int time_sign;
    while (op)
    {
        printf("\n\n");
        printf("\t                                SAT Menu\n");
        printf("=====================================================================\n");
        printf("\t1.         New SAT   2.  Answer Test  0.  Main menu\n");
        printf("=====================================================================\n");
        printf("\t\t     Choose your operation[0~2]:   ");
        scanf("%d", &op);
        system("cls");
        switch (op)
        {
        case 1:
            InitSat(&S, var_watch); //初始化
            printf("please input the cnf path:\n");
            scanf("%s", filename, 300);
            fp = fopen(filename, "r");
            start = clock();
            if (fp == NULL)
            {
                printf("open document failed!\n ");
                break;
            }
            else
                LoadCnf(&S, var_watch, fp); //调用LoadCnf 函数，读取文件
            result = DPLL(S, var_watch);
            finish = clock();
            time_sign = (finish - start); //时间记录
            if (result == TRUE)
            {
                printf("time to solve the sat problem is: %d ms\n", time_sign);
                print_answer();
                save_answer(result, filename, time_sign);
            }
            else
            {
                printf("no solution!\n");
            }
            break;
        case 2:
            InitSat(&S, var_watch); //初始化
            printf("please input the cnf path you want to prove:\n");
            scanf("%s", filename, 300);
            fp = fopen(filename, "r");
            if (fp == NULL)
            {
                printf("res open failed!\n ");
                break;
            }
            else
                LoadCnf(&S, var_watch, fp); //调用LoadCnf 函数，读取文件
            printf("please input the res path tou want to prove:\n");
            scanf("%s", filename, 300);
            fp = fopen(filename, "r");
            result = answer_test(S, fp, var_watch);
            if (result == TRUE)
            {
                printf("satisfied!\n");
            }
            else
            {
                printf("unsatisfied!\n");
            }
            break;
        case 0:
            return 0;
        default:
            printf("\t\t\tPlease choose your operation again[0~2]:");
            scanf("%d", &op);
        }
    }
    return 0;
}




int InitSat(clause **S, Var_watch var_watch[])
{
    clause *cfront = *S, *crear;   //头尾子句指针
    clauseLiteral *lfront, *lrear; //头尾文字指针，子句初始化
    int i;
    while (cfront) //如果头字句不为空
    {
        crear = cfront->nextclause; //把尾字句指针设为头字句指针的指针域
        lfront = cfront->p;         //把头文字指针设为头字句指针的文字域
        while (lfront)              //如果头文字指针不为空
        {
            lrear = lfront->next; //把尾文字指针移到头文字指针的后面
            free(lfront);         //释放头文字指针
            lfront = lrear;       //再将头文字指针向后移一位
        }
        free(cfront);   //把最后的文字释放
        cfront = crear; //把头字句指针往后一位
    }                   //到此处已经把所有的字句以及文字删除
    *S = NULL;          //把字句指针赋值为NULL
    number_var = 0;     //把变元数目赋值为0
    clause_num = 0;     //把已知变元数目赋值为0
    for (i = 1; i < MaxNumVar; i++)
    {
        var_watch[i].positive = NULL; //文字邻接表指针指向空
        var_watch[i].negative = NULL;
        var_watch[i].pos_num=0;
        var_watch[i].neg_num=0;
        var_watch[i].flag=0;
        answer[i] = 0;
    }
    top = stack_answer;
    bottom = stack_answer;
    return 0;
}

int LoadCnf(clause **S, Var_watch *var_watch, FILE *fp)
{
    char c;
    clause *clausetemp, *cp = NULL; //两个指针，用来构建字句单链表
    clauseLiteral *p, *q;           //两个指针，用来构建文字单链表
    int var;                        //变量的值
    int numclauseVar;               //作为计数器统计子句中的文字个数
    fscanf(fp, "%c", &c);
    while (c == 'c')
    {
        while (c != '\n' && c != '\r')
            fscanf(fp, "%c", &c);
        fscanf(fp, "%c", &c);
        if (c == '\n') //读取换行符
            fscanf(fp, "%c", &c);
    }
    fscanf(fp, " cnf ");     //读到文件的信息段
    number_var = GetNum(fp); //读取变量数，并赋值给numVar
    clause_num = GetNum(fp); //读取子句数
    var = GetNum(fp);        //再次调用，读取下一行第一个变量值，把值赋给var
    while (1)
    {
        numclauseVar = 0;                              //把计数器初始化
        clausetemp = (clause *)malloc(sizeof(clause)); //创建字句链表的头指针
        p = clausetemp->p;                             //p为头子句的下一个文字
        while (var)                                    //var不为0，即该子句还有文字没有读取
        {
            ++numclauseVar;                                     //计数器，统计子句的变元数目
            q = (clauseLiteral *)malloc(sizeof(clauseLiteral)); //把单链表的表头创建出来
            q->data = var;                                      //文字的值域改成var
            q->next = NULL;                                     //文字的指针域赋值为NULL，防止回溯出现问题
            if (numclauseVar == 1)                              //如果为该语句的第一个文字
            {
                clausetemp->p = q; //把子句的文字指针指向第一个文字
                p = q;             //把p指针指向第一个文字
            }
            else //如果不为该语句的第一个文字
            {
                p->next = q; //把两个文字之间联系起来
                p = p->next; //把p指针往后移动一位，和q指向同一文字
            }
            Putclause(clausetemp, var, var_watch); //储存该文字所处子句的字句地址
            var = GetNum(fp);                      //继续读取下一个文字
        }                                          //该子句读取完毕
        clausetemp->word_num = numclauseVar;       //把该子句的文字个数存储
        clausetemp->flag = 0;                      //把子句设置为未满足子句
        if (*S == NULL)                            //如果此时S指向的为空子句，即刚读取了第一个不可化简的字句
        {
            *S = clausetemp; //S赋值为字句的头指针
            cp = clausetemp; //子句的尾指针赋值为子句的头指针
            cp->nextclause = NULL;
        }
        else //刚读取了一个不可简化的子句
        {
            cp->nextclause = clausetemp;
            cp = cp->nextclause;
            cp->nextclause = NULL;
        }
        var = GetNum(fp); //读取下一行字句的第一个文字
        if (feof(fp))     //若到达文件尾，再执行一次读文件操作时，设置文件结束标志
            break;
    }
    return 0;
}

int GetNum(FILE *fp)
{
    char c;
    int sign = 1, num = 0; //num 文字的值,sign标记文字极性
    fscanf(fp, "%c", &c);
    if (c == '-')
    {
        sign = -1; //sign变为-1，为负文字
        fscanf(fp, "%c", &c);
    }
    else if (c == '0')
    { //子句结束
        fscanf(fp, "%c", &c);
        if (c == '\r') //换行
            fscanf(fp, "%c", &c);
        return num;
    }
    else if (c == '\n')
        return 0;
    else if (feof(fp))
        return 0;
    while (c != ' ' && c != '\n' && c != '\r')
    {
        num = num * 10 + c - '0'; //得到文字的值
        fscanf(fp, "%c", &c);
    }
    if (c == '\r')
        fscanf(fp, "%c", &c);
    return sign * num; //用来得到有正负号的文字
}

int Putclause(clause *ctemp, int var, Var_watch var_watch[]) //ctemp为要记录的子句地址
{
    Var_List *p, *q;                  //varlist指针
    if (var > 0) {                     //如果该变元大于0
        p = var_watch[var].positive;  //p指针为该变元所在位置的第一个正文字
        var_watch[var].pos_num++;
    }
    else{                              //如果该变元小于0
        p = var_watch[-var].negative; //p指针为该变元所在位置的第一个负文字
         var_watch[-var].neg_num++;
    }
    if (p == NULL)
    { //如果p是链表的第一个
        p = (VarList *)malloc(sizeof(VarList));
        p->p = ctemp; //将需要储存的子句地址存储下来
        if (var > 0){
            var_watch[var].positive = p;
        }
        else{
            var_watch[-var].negative = p;
        }
    }
    else
    { //p不是链表的第一个
        while (p->next)
            p = p->next;
        q = (VarList *)malloc(sizeof(VarList));
        q->p = ctemp;
        p->next = q;
        p = p->next;
    }
    p->satisfied = 0; //把标记清0
    p->next = NULL;   //将p的指针域赋值为NULL
    return 0;
}

int abs(int a)
{
    if (a >= 0)
        return a;
    else
        return -a;
}

int DPLL(clause *S, Var_watch *var_watch)
{
    int response;
    clause *temp;
    if (empty_set(S))
        return TRUE;
    else if (!empty_clause(S))
        return FALSE;
    while (temp = pan_duan(S))
    {
        unique(temp, var_watch);
        if (empty_set(S))
            return TRUE;
        else if (!empty_clause(S))
            return FALSE;
    }
    if (empty_set(S))
        return TRUE;
    else if (!empty_clause(S))
        return FALSE;
    response = stragety(var_watch);
    *top = response;
    top++;
    *first = response;
    first++;
    search(var_watch, response); //删除含有response的文字
    if (DPLL(S, var_watch))      //对现在的邻接表进行递归
        return TRUE;
    response = last_branch(var_watch); //返回上一个分支点
    search(var_watch, response);
    return DPLL(S, var_watch);
}

clause *pan_duan(clause *S)
{ //判断子句集是否含有单子句，返回一个单子句
    clause *q = S;
    while (q)
    {
        if (q->flag == 1)
        {
            q = q->nextclause;
            continue;
        }
        if (q->word_num != 1)
        {
            q = q->nextclause;
            continue;
        }
        else
            break;
    }
    return q;
}

int unique(clause *single, Var_watch *var_watch)
{ //传入一个单子句，对子句集进行单子句操作
    int temp;
    Var_List *p, *q;
    temp = single->p->data;
    *top = temp;
    top++;
    if (temp > 0)
    { //该文字为正文字
        p = var_watch[temp].positive;
        while (p)
        {
            if (p->p->flag == 0)
            { //该文字所在子句为未满足
                p->p->flag = 1;
                p->satisfied = 1;
            }
            p = p->next;
        }
        q = var_watch[temp].negative;
        while (q)
        {
            if (q->p->flag == 0)
            { //该文字所在的子句为未满足
                q->p->word_num--;
                delete_var(q->p, -temp);
            }
            q = q->next;
        }
    }
    else
    { //该文字为负文字
        p = var_watch[-temp].negative;
        while (p)
        {
            if (p->p->flag == 0)
            { //该文字所在子句为未满足
                p->p->flag = 1;
                p->satisfied = 1;
            }
            p = p->next;
        }
        q = var_watch[-temp].positive;
        while (q)
        {
            if (q->p->flag == 0)
            { //该文字所在的子句为未满足
                q->p->word_num--;
                delete_var(q->p, -temp);
            }
            q = q->next;
        }
    }
    var_watch[abs(temp)].flag=1;
    return OK;
}

int empty_set(clause *q)
{ //判断子句集是否为空
    int i=0;
    for(i=0;i<clause_num;i++)
    {
        if (q->flag == 0)
            return FALSE;
        q = q->nextclause;
    }
    return TRUE;
}

int empty_clause(clause *q)
{ //判断是否有空子句
    while (q)
    {
        if (q->flag == 0 && q->p == NULL)
            return FALSE;
        q = q->nextclause;
    }
    return TRUE;
}

int stragety(Var_watch *var_watch)
{
    int i=1;
    int max_num=0;
    int choose_num=0;
    for(i=1;i<=number_var;i++){
        if(var_watch[i].flag==1){

            continue;
        }
        else{
            if(var_watch[i].pos_num>max_num){
                max_num=var_watch[i].pos_num;
                choose_num=i;
            }
            if(var_watch[i].neg_num>max_num){
                max_num=var_watch[i].neg_num;
                choose_num=-i;
            }
        }
    }
    return choose_num;
}

int reset(varWatch *var_watch, int temp)
{ //重新将上一步撤销
    Var_List *p, *q;
    if (temp > 0)
    { //该文字为正文字
        p = var_watch[temp].positive;
        while (p)
        {
            if (p->p->flag == 1 && p->satisfied == 1)
            { //该文字所在子句为已满足且为此次操作造成
                p->p->flag = 0;
                p->satisfied = 0;
            }
            p = p->next;
        }
        q = var_watch[temp].negative;
        while (q)
        {
            if (q->p->flag == 0)
            { //该文字所在的子句为未满足
                q->p->word_num++;
                clauseLiteral *pt = (clauseLiteral *)malloc(sizeof(clauseLiteral));
                pt->data = -temp;
                pt->next = q->p->p;
                q->p->p = pt;
            }
            q = q->next;
        }
    }
    else
    { //该文字为负文字
        p = var_watch[-temp].negative;
        while (p)
        {
            if (p->p->flag == 1 && p->satisfied == 1)
            { //该文字所在子句为满足,且是由本次操作造成的
                p->p->flag = 0;
                p->satisfied = 0;
            }
            p = p->next;
        }
        q = var_watch[-temp].positive;
        while (q)
        {
            if (q->p->flag == 0)
            { //该文字所在的子句为未满足
                q->p->word_num++;
                clauseLiteral *pt = (clauseLiteral *)malloc(sizeof(clauseLiteral));
                pt->data = -temp;
                pt->next = q->p->p;
                q->p->p = pt;
            }
            q = q->next;
        }
    }
    var_watch[abs(temp)].flag=0;
    return OK;
}

int delete_var(clause *pt, int temp)
{ //把该变元从子句集中删除
    clauseLiteral *p = pt->p, *q = NULL;
    if (p->data == temp)
    {
        pt->p = p->next;
        free(p);
    }
    else
    {
        while (p->next->data != temp)
            p = p->next;
        q = p->next;
        p->next = q->next;
        free(q);
    }
    return OK;
}

int search(Var_watch *var_watch, int temp)
{ //删除所有与含temp的文字
    Var_List *p, *q;
    if (temp > 0)
    { //该文字为正文字
        p = var_watch[temp].positive;
        while (p)
        {
            if (p->p->flag == 0)
            { //该文字所在子句为未满足
                p->p->flag = 1;
                p->satisfied = 1;
            }
            p = p->next;
        }
        q = var_watch[temp].negative;
        while (q)
        {
            if (q->p->flag == 0)
            { //该文字所在的子句为未满足
                q->p->word_num--;
                delete_var(q->p, -temp);
            }
            q = q->next;
        }
    }
    else
    { //该文字为负文字
        p = var_watch[-temp].negative;
        while (p)
        {
            if (p->p->flag == 0)
            { //该文字所在子句为未满足
                p->p->flag = 1;
                p->satisfied = 1;
            }
            p = p->next;
        }
        q = var_watch[-temp].positive;
        while (q)
        {
            if (q->p->flag == 0)
            { //该文字所在的子句为未满足
                q->p->word_num--;
                delete_var(q->p, -temp);
            }
            q = q->next;
        }
    }
    var_watch[abs(temp)].flag=1;
    return OK;
}

int last_branch(varWatch *var_watch)
{
    top--;
    first--;
    while (*top != *first)
    {
        reset(var_watch, *top);
        top--;
    }
    reset(var_watch, *top);
    *top = -*top;
    top++;
    return *(top - 1);
}

int print_answer()
{
    int i;
    while (top != bottom)
    {
        answer[abs(*bottom)] = (*bottom) / (abs(*bottom));
        bottom++;
    }
    for (i = 1; i <= number_var; i++)
    {
        if (answer[i] == 1 || answer[i] == 0)
            printf("%d ", i);
        if (answer[i] == -1)
            printf("%d ", answer[i] * i);
    }
    return OK;
}

int save_answer(int result, char *filename, int time)
{
    FILE *fp;
    int p = 0, i;
    while (filename[p] != 0)
        p++;
    while (filename[p] != '.')
        p--;
    p++;
    filename[p] = 'r';
    p++;
    filename[p] = 'e';
    p++;
    filename[p] = 's';
    p++; //把文件名补充完整
    filename[p] = 0;
    fp = fopen(filename, "w");
    if (result == 1)
        fprintf(fp, "s 1\r\n");
    else
        fprintf(fp, "s 0\r\n");
    fprintf(fp, "v ");
    for (i = 1; i <= number_var; i++)
    {
        if (answer[i] == 1)
            fprintf(fp, "%d ", answer[i] * i);
        else if (answer[i] == -1)
            fprintf(fp, "%d ", answer[i] * i);
        else if (answer[i] == 0)
            fprintf(fp, "%d ", i);
    }
    fprintf(fp, "\r\n");
    fprintf(fp, "t %d\r\n", time);
    fclose(fp);
    return 0;
}

int answer_test(clause *S, FILE *fp, varWatch *var_watch)
{
    char c;
    int temp, i;
    fscanf(fp, "%c", &c);
    while (c != 'v')
    {
        fscanf(fp, "%c", &c);
    }
    fscanf(fp, "%c", &c); //读取空格
    temp = GetNum(fp);
    for (i = 1; i <= number_var; i++)
    {
        if (temp > 0)
        {
            answer[temp] = 1;
        }
        else
        {
            answer[-temp] = -1;
        }
        temp = GetNum(fp);
    }
    for (i = 1; i <= number_var; i++)
    {
        VarList *pt = NULL;
        if (answer[i] == 1)
        {
            pt = var_watch[i].positive;
            while (pt)
            {
                pt->p->flag = 1;
                pt = pt->next;
            }
        }
        if (answer[i] == -1)
        {
            pt = var_watch[i].negative;
            while (pt)
            {
                pt->p->flag = 1;
                pt = pt->next;
            }
        }
    }
    return empty_set(S);
}

status Sudoku(){
	int level,temp,i,j,k;
	clause *S = NULL;
    Var_watch var_watch[MaxNumVar + 1];
    FILE *fp;
    srand((unsigned)time(NULL));
	printf("please input the level of the binary sudoku:\n");
	scanf("%d",&level);
	InitSudoku(level);
	InitSat(&S, var_watch); //初始化
	fp = fopen(cnfpath, "r");
    if (fp == NULL){
        printf("open document failed!\n ");
    }
	else
    LoadCnf(&S, var_watch, fp); //调用LoadCnf 函数，读取文件
    for(i=0;i<level/2;i++){
    	temp=rand()%(level*level)+1;
    	*top=temp;
    	top++;
    	search(var_watch,temp);
	}
	DPLL(S, var_watch);
    while (top != bottom)
    {
        answer[abs(*bottom)] = (*bottom) / (abs(*bottom));
        bottom++;
    }
    for(i=1;i<=level*level;){
        for(k = 0; k < level; k++)
			printf("____");
       	printf("\n|");
    	for(j=1;j<=level;j++){
    		if(answer[i]==1)
    		printf("1  |");
    		else
    		printf("0  |");
    		i++;
		}
    	printf("\n");
	}
	for(k = 0; k < level; k++)
			printf("____");
	printf("\n");
	for(i=1;i<level*(level-2)+1;i++){
		temp=rand()%(level*level)+1;
		answer[temp]=0;
	}
	printf("the sudoku is:\n");
	for(i=1;i<=level*level;){
        for(k = 0; k < level; k++)
			printf("____");
       	printf("\n|");
    	for(j=1;j<=level;j++){
    		if(answer[i]==1)
    		printf("1  |");
    		else if(answer[i]==-1)
    		printf("0  |");
    		else
    		printf("   |");
    		i++;
		}
    	printf("\n");
	}
	for(k = 0; k < level; k++)
			printf("____");
	printf("\n");
	return 0;
}



status InitSudoku(int level)
{                                                                   //初始化数独,level代表阶数
    int result;                                                     //判断是否有解
    int *puzzle = (int *)malloc((level * level + 1) * sizeof(int)); //给数独分配空间
    number_var = level * level;
    clause_num = 0;
    clause_num += 2 * level * (level - 2) * 2;                     //第一个约束，每一行要取level-3个语句数
    clause_num += 2 * level * calculate(level, level / 2 + 1) * 2; //第二个约束产生的语句数
    number_var += 2 * calculate(level, 2) * (3 * level + 2);
    clause_num += 2 * calculate(level, 2) * (10 * level + 2); //第三个约束产生的语句数和变元数
    Generatecnf(level);
                    //加载数独cnf文件
    return 0;
}

status calculate(int n, int m) //n>=m>=0
{
    int i, a;
    if (m + m > n)
        m = n - m; //be faster
    for (i = 1, a = 1; i <= m; i++, n--)
        a = a * n / i;
    return a;
}

status Generatecnf(int level)
{
    FILE *fp;
    strcpy(cnfpath, "./binary_puzzle.cnf");
    fp = fopen(cnfpath, "w+"); // 打开文件
    fprintf(fp, "p cnf %d %d\n", number_var, clause_num);
    Rule1(level, fp);
    Rule2(level, fp);
    Rule3(level, fp);
    fclose(fp);
    return OK;
}

status Rule1(int level, FILE *fp)
{ //第一个约束条件，每行每列不允许有连续的三个0或三个1出现
    int i, j;
    for (i = 0; i < level; i++) //行生成的语句
    {
        for (j = 0; j < level - 2; j++)
        {
            fprintf(fp, "%d ", i * level + j + 1);
            fprintf(fp, "%d ", i * level + j + 2);
            fprintf(fp, "%d ", i * level + j + 3);
            fprintf(fp, "0\n");
        }
        for (j = 0; j < level - 2; j++)
        {
            fprintf(fp, "%d ", -(i * level + j + 1));
            fprintf(fp, "%d ", -(i * level + j + 2));
            fprintf(fp, "%d ", -(i * level + j + 3));
            fprintf(fp, "0\n");
        }
    }
    for (i = 0; i < level - 2; i++) //列生成的语句
    {
        for (j = 0; j < level; j++)
        {
            fprintf(fp, "%d ", i * level + j + 1);
            fprintf(fp, "%d ", (i + 1) * level + j + 1);
            fprintf(fp, "%d ", (i + 2) * level + j + 1);
            fprintf(fp, "0\n");
        }
        for (j = 0; j < level; j++)
        {
            fprintf(fp, "%d ", -(i * level + j + 1));
            fprintf(fp, "%d ", -((i + 1) * level + j + 1));
            fprintf(fp, "%d ", -((i + 2) * level + j + 1));
            fprintf(fp, "0\n");
        }
    }
    return OK;
}

status Rule2(int level, FILE *fp)
{                                               //第二个约束条件，每一行每一列中的1和0的个数相同
    int i, j, wordnum = level / 2 + 1, l[1000]; //wordnum代表阶数的一半加一，用来代表生成的语句的文字数量
    for (i = 0; i < level; i++)                 //行
    {
        for (j = 0; j < level; j++) //记录该行的正变元
            l[j] = level * i + j + 1;
        Rule2_clause(l, level, wordnum, 0, 0, fp); //把该行生成的正变元子句存储起来
        for (j = 0; j < level; j++)                //记录该行的负变元
            l[j] = -(level * i + j + 1);
        Rule2_clause(l, level, wordnum, 0, 0, fp); //把该行的负变元子句存储起来
    }
    for (i = 0; i < level; i++) //列
    {
        for (j = 0; j < level; j++)
            l[j] = level * j + i + 1;
        Rule2_clause(l, level, wordnum, 0, 0, fp);
        for (j = 0; j < level; j++)
            l[j] = -(level * j + i + 1);
        Rule2_clause(l, level, wordnum, 0, 0, fp);
    }
    return OK;
}

void Rule2_clause(int arr[], int level, int wordnum, int k1, int k2, FILE *fp) //把生成的子句写入文件中
{
    static int rec[1000]; //记录组合序列
    int i;
    if (k1 == wordnum) //输出当前序列
    {
        for (i = 0; i < wordnum; ++i)
            fprintf(fp, "%d ", rec[i]);
        fprintf(fp, "0\n");
    }
    else
    {
        for (i = k2; i < level; ++i)
        {
            rec[k1] = arr[i];                             //子序列赋值
            Rule2_clause(arr, level, wordnum, k1 + 1, i + 1, fp); //递归回溯
        }
    }
}

status Rule3(int level, FILE *fp)
{                                                  //第三个约束条件
    int i, j, k, literal_name = level * level + 1; //生成的中间变元从的编号接在数独最大变元的后一位
    for (i = 0; i < level - 1; i++)                //从第一行开始选取第一个比较行
    {
        for (j = i + 1; j < level; j++) //从第一个比较行之后逐行进行比对
        {
            for (k = 0; k < level; k++) //确定需要比较的两行之后开始从每行的第一个开始比较
            {
                // 15711= 51∧71转换的结果
                fprintf(fp, "%d %d 0\n", i * level + k + 1, -literal_name);                            //51∨ ?15711
                fprintf(fp, "%d %d 0\n", j * level + k + 1, -literal_name);                            //71∨ ?15711
                fprintf(fp, "%d %d %d 0\n", -(i * level + k + 1), -(j * level + k + 1), literal_name); //?51∨ ?71∨15711
                literal_name += 1;                                                                     //获得下一个变元编号
                // 15710= ?51∧?71转换的结果
                fprintf(fp, "%d %d 0\n", -(i * level + k + 1), -literal_name);                   //?51∨ ?15710
                fprintf(fp, "%d %d 0\n", -(j * level + k + 1), -literal_name);                   //?71∨ ?15710
                fprintf(fp, "%d %d %d 0\n", i * level + k + 1, j * level + k + 1, literal_name); //51∨71∨15710
                literal_name += 1;
                // 1571= 15711∨15710转换的结果
                fprintf(fp, "%d %d 0\n", -(literal_name - 2), literal_name);                    //?15711∨1571
                fprintf(fp, "%d %d 0\n", -(literal_name - 1), literal_name);                    //?15710∨1571
                fprintf(fp, "%d %d %d 0\n", literal_name - 1, literal_name - 2, -literal_name); //15711∨15710∨?1571
                literal_name += 1;
            }
            // 157= ?[1571∧1572∧…∧1578]
            fprintf(fp, "%d ", -literal_name); //?157∨?1571∨?1572∨…∨?1578
            for (k = 1; k < level + 1; k++)
                fprintf(fp, "%d ", -(literal_name + 2 - k * 3));
            fprintf(fp, "0\n");
            for (k = 1; k < level + 1; k++) //（1571∨157）∧（1572∨157）…（1578∨157）
                fprintf(fp, "%d %d 0\n", literal_name + 2 - k * 3, literal_name);
            fprintf(fp, "%d 0\n", literal_name);
            literal_name += 1;
        }
    }
    for (i = 0; i < level - 1; i++)     //列,和行的类似
    {
        for (j = i + 1; j < level; j++)
        {
            for (k = 0; k < level; k++)
            {
                fprintf(fp, "%d %d 0\n", k * level + i + 1, -literal_name);
                fprintf(fp, "%d %d 0\n", k * level + j + 1, -literal_name);
                fprintf(fp, "%d %d %d 0\n", -(k * level + i + 1), -(k * level + j + 1), literal_name);
                literal_name += 1;
                fprintf(fp, "%d %d 0\n", -(k * level + i + 1), -literal_name);
                fprintf(fp, "%d %d 0\n", -(k * level + j + 1), -literal_name);
                fprintf(fp, "%d %d %d 0\n", k * level + i + 1, k * level + j + 1, literal_name);
                literal_name += 1;
                fprintf(fp, "%d %d 0\n", -(literal_name - 2), literal_name);
                fprintf(fp, "%d %d 0\n", -(literal_name - 1), literal_name);
                fprintf(fp, "%d %d %d 0\n", literal_name - 1, literal_name - 2, -literal_name);
                literal_name += 1;
            }
            fprintf(fp, "%d ", -literal_name);
            for (k = 1; k < level + 1; k++)
                fprintf(fp, "%d ", -(literal_name + 2 - k * 3));
            fprintf(fp, "0\n");
            for (k = 1; k < level + 1; k++)
                fprintf(fp, "%d %d 0\n", literal_name + 2 - k * 3, literal_name);
            fprintf(fp, "%d 0\n", literal_name);
            literal_name += 1;
        }
    }
    return OK;
}
