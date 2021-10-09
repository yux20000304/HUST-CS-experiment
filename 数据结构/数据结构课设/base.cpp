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
	struct varList *positive; //�ڽӱ�:�����֣�������.
	struct varList *negative;
	int pos_num;
	int neg_num;
	int flag;
} Var_watch,varWatch;

typedef struct varList
{
	struct clause *p;	 //ָ��һ���Ӿ䣬�����洢���Ӿ�ĵ�ַ
	struct varList *next; //ָ����һ��������ֹ������Ӿ�
	int satisfied;
} Var_List,VarList;

typedef struct clause
{
	struct clauseLiteral *p;   //ָ���Ӿ��е���һ������
	struct clause *nextclause; //ָ����һ���Ӿ�
	int word_num;
	int flag;
} clause;

typedef struct  clauseLiteral
{
	int data;					//���ֵ�ֵ
	struct clauseLiteral *next; //ָ���Ӿ��е���һ������
} clauseLiteral;

typedef int status;
static int number_var;  //��Ԫ��
static int clause_num;  //�����

int answer[MaxNumVar];	//��ɴ����
int stack_answer[MaxNumVar];//����·��ջ
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
    clause *S = NULL;                   //����һ���־�ָ��
    Var_watch var_watch[MaxNumVar + 1]; //����Ԫ��Ŀ��һ���ռ�
    FILE *fp;                           //�ļ�ָ��
    char filename[300];                 //�ļ���
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
            InitSat(&S, var_watch); //��ʼ��
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
                LoadCnf(&S, var_watch, fp); //����LoadCnf ��������ȡ�ļ�
            result = DPLL(S, var_watch);
            finish = clock();
            time_sign = (finish - start); //ʱ���¼
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
            InitSat(&S, var_watch); //��ʼ��
            printf("please input the cnf path you want to prove:\n");
            scanf("%s", filename, 300);
            fp = fopen(filename, "r");
            if (fp == NULL)
            {
                printf("res open failed!\n ");
                break;
            }
            else
                LoadCnf(&S, var_watch, fp); //����LoadCnf ��������ȡ�ļ�
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
    clause *cfront = *S, *crear;   //ͷβ�Ӿ�ָ��
    clauseLiteral *lfront, *lrear; //ͷβ����ָ�룬�Ӿ��ʼ��
    int i;
    while (cfront) //���ͷ�־䲻Ϊ��
    {
        crear = cfront->nextclause; //��β�־�ָ����Ϊͷ�־�ָ���ָ����
        lfront = cfront->p;         //��ͷ����ָ����Ϊͷ�־�ָ���������
        while (lfront)              //���ͷ����ָ�벻Ϊ��
        {
            lrear = lfront->next; //��β����ָ���Ƶ�ͷ����ָ��ĺ���
            free(lfront);         //�ͷ�ͷ����ָ��
            lfront = lrear;       //�ٽ�ͷ����ָ�������һλ
        }
        free(cfront);   //�����������ͷ�
        cfront = crear; //��ͷ�־�ָ������һλ
    }                   //���˴��Ѿ������е��־��Լ�����ɾ��
    *S = NULL;          //���־�ָ�븳ֵΪNULL
    number_var = 0;     //�ѱ�Ԫ��Ŀ��ֵΪ0
    clause_num = 0;     //����֪��Ԫ��Ŀ��ֵΪ0
    for (i = 1; i < MaxNumVar; i++)
    {
        var_watch[i].positive = NULL; //�����ڽӱ�ָ��ָ���
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
    clause *clausetemp, *cp = NULL; //����ָ�룬���������־䵥����
    clauseLiteral *p, *q;           //����ָ�룬�����������ֵ�����
    int var;                        //������ֵ
    int numclauseVar;               //��Ϊ������ͳ���Ӿ��е����ָ���
    fscanf(fp, "%c", &c);
    while (c == 'c')
    {
        while (c != '\n' && c != '\r')
            fscanf(fp, "%c", &c);
        fscanf(fp, "%c", &c);
        if (c == '\n') //��ȡ���з�
            fscanf(fp, "%c", &c);
    }
    fscanf(fp, " cnf ");     //�����ļ�����Ϣ��
    number_var = GetNum(fp); //��ȡ������������ֵ��numVar
    clause_num = GetNum(fp); //��ȡ�Ӿ���
    var = GetNum(fp);        //�ٴε��ã���ȡ��һ�е�һ������ֵ����ֵ����var
    while (1)
    {
        numclauseVar = 0;                              //�Ѽ�������ʼ��
        clausetemp = (clause *)malloc(sizeof(clause)); //�����־������ͷָ��
        p = clausetemp->p;                             //pΪͷ�Ӿ����һ������
        while (var)                                    //var��Ϊ0�������Ӿ仹������û�ж�ȡ
        {
            ++numclauseVar;                                     //��������ͳ���Ӿ�ı�Ԫ��Ŀ
            q = (clauseLiteral *)malloc(sizeof(clauseLiteral)); //�ѵ�����ı�ͷ��������
            q->data = var;                                      //���ֵ�ֵ��ĳ�var
            q->next = NULL;                                     //���ֵ�ָ����ֵΪNULL����ֹ���ݳ�������
            if (numclauseVar == 1)                              //���Ϊ�����ĵ�һ������
            {
                clausetemp->p = q; //���Ӿ������ָ��ָ���һ������
                p = q;             //��pָ��ָ���һ������
            }
            else //�����Ϊ�����ĵ�һ������
            {
                p->next = q; //����������֮����ϵ����
                p = p->next; //��pָ�������ƶ�һλ����qָ��ͬһ����
            }
            Putclause(clausetemp, var, var_watch); //��������������Ӿ���־��ַ
            var = GetNum(fp);                      //������ȡ��һ������
        }                                          //���Ӿ��ȡ���
        clausetemp->word_num = numclauseVar;       //�Ѹ��Ӿ�����ָ����洢
        clausetemp->flag = 0;                      //���Ӿ�����Ϊδ�����Ӿ�
        if (*S == NULL)                            //�����ʱSָ���Ϊ���Ӿ䣬���ն�ȡ�˵�һ�����ɻ�����־�
        {
            *S = clausetemp; //S��ֵΪ�־��ͷָ��
            cp = clausetemp; //�Ӿ��βָ�븳ֵΪ�Ӿ��ͷָ��
            cp->nextclause = NULL;
        }
        else //�ն�ȡ��һ�����ɼ򻯵��Ӿ�
        {
            cp->nextclause = clausetemp;
            cp = cp->nextclause;
            cp->nextclause = NULL;
        }
        var = GetNum(fp); //��ȡ��һ���־�ĵ�һ������
        if (feof(fp))     //�������ļ�β����ִ��һ�ζ��ļ�����ʱ�������ļ�������־
            break;
    }
    return 0;
}

int GetNum(FILE *fp)
{
    char c;
    int sign = 1, num = 0; //num ���ֵ�ֵ,sign������ּ���
    fscanf(fp, "%c", &c);
    if (c == '-')
    {
        sign = -1; //sign��Ϊ-1��Ϊ������
        fscanf(fp, "%c", &c);
    }
    else if (c == '0')
    { //�Ӿ����
        fscanf(fp, "%c", &c);
        if (c == '\r') //����
            fscanf(fp, "%c", &c);
        return num;
    }
    else if (c == '\n')
        return 0;
    else if (feof(fp))
        return 0;
    while (c != ' ' && c != '\n' && c != '\r')
    {
        num = num * 10 + c - '0'; //�õ����ֵ�ֵ
        fscanf(fp, "%c", &c);
    }
    if (c == '\r')
        fscanf(fp, "%c", &c);
    return sign * num; //�����õ��������ŵ�����
}

int Putclause(clause *ctemp, int var, Var_watch var_watch[]) //ctempΪҪ��¼���Ӿ��ַ
{
    Var_List *p, *q;                  //varlistָ��
    if (var > 0) {                     //����ñ�Ԫ����0
        p = var_watch[var].positive;  //pָ��Ϊ�ñ�Ԫ����λ�õĵ�һ��������
        var_watch[var].pos_num++;
    }
    else{                              //����ñ�ԪС��0
        p = var_watch[-var].negative; //pָ��Ϊ�ñ�Ԫ����λ�õĵ�һ��������
         var_watch[-var].neg_num++;
    }
    if (p == NULL)
    { //���p������ĵ�һ��
        p = (VarList *)malloc(sizeof(VarList));
        p->p = ctemp; //����Ҫ������Ӿ��ַ�洢����
        if (var > 0){
            var_watch[var].positive = p;
        }
        else{
            var_watch[-var].negative = p;
        }
    }
    else
    { //p��������ĵ�һ��
        while (p->next)
            p = p->next;
        q = (VarList *)malloc(sizeof(VarList));
        q->p = ctemp;
        p->next = q;
        p = p->next;
    }
    p->satisfied = 0; //�ѱ����0
    p->next = NULL;   //��p��ָ����ֵΪNULL
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
    search(var_watch, response); //ɾ������response������
    if (DPLL(S, var_watch))      //�����ڵ��ڽӱ���еݹ�
        return TRUE;
    response = last_branch(var_watch); //������һ����֧��
    search(var_watch, response);
    return DPLL(S, var_watch);
}

clause *pan_duan(clause *S)
{ //�ж��Ӿ伯�Ƿ��е��Ӿ䣬����һ�����Ӿ�
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
{ //����һ�����Ӿ䣬���Ӿ伯���е��Ӿ����
    int temp;
    Var_List *p, *q;
    temp = single->p->data;
    *top = temp;
    top++;
    if (temp > 0)
    { //������Ϊ������
        p = var_watch[temp].positive;
        while (p)
        {
            if (p->p->flag == 0)
            { //�����������Ӿ�Ϊδ����
                p->p->flag = 1;
                p->satisfied = 1;
            }
            p = p->next;
        }
        q = var_watch[temp].negative;
        while (q)
        {
            if (q->p->flag == 0)
            { //���������ڵ��Ӿ�Ϊδ����
                q->p->word_num--;
                delete_var(q->p, -temp);
            }
            q = q->next;
        }
    }
    else
    { //������Ϊ������
        p = var_watch[-temp].negative;
        while (p)
        {
            if (p->p->flag == 0)
            { //�����������Ӿ�Ϊδ����
                p->p->flag = 1;
                p->satisfied = 1;
            }
            p = p->next;
        }
        q = var_watch[-temp].positive;
        while (q)
        {
            if (q->p->flag == 0)
            { //���������ڵ��Ӿ�Ϊδ����
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
{ //�ж��Ӿ伯�Ƿ�Ϊ��
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
{ //�ж��Ƿ��п��Ӿ�
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
{ //���½���һ������
    Var_List *p, *q;
    if (temp > 0)
    { //������Ϊ������
        p = var_watch[temp].positive;
        while (p)
        {
            if (p->p->flag == 1 && p->satisfied == 1)
            { //�����������Ӿ�Ϊ��������Ϊ�˴β������
                p->p->flag = 0;
                p->satisfied = 0;
            }
            p = p->next;
        }
        q = var_watch[temp].negative;
        while (q)
        {
            if (q->p->flag == 0)
            { //���������ڵ��Ӿ�Ϊδ����
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
    { //������Ϊ������
        p = var_watch[-temp].negative;
        while (p)
        {
            if (p->p->flag == 1 && p->satisfied == 1)
            { //�����������Ӿ�Ϊ����,�����ɱ��β�����ɵ�
                p->p->flag = 0;
                p->satisfied = 0;
            }
            p = p->next;
        }
        q = var_watch[-temp].positive;
        while (q)
        {
            if (q->p->flag == 0)
            { //���������ڵ��Ӿ�Ϊδ����
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
{ //�Ѹñ�Ԫ���Ӿ伯��ɾ��
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
{ //ɾ�������뺬temp������
    Var_List *p, *q;
    if (temp > 0)
    { //������Ϊ������
        p = var_watch[temp].positive;
        while (p)
        {
            if (p->p->flag == 0)
            { //�����������Ӿ�Ϊδ����
                p->p->flag = 1;
                p->satisfied = 1;
            }
            p = p->next;
        }
        q = var_watch[temp].negative;
        while (q)
        {
            if (q->p->flag == 0)
            { //���������ڵ��Ӿ�Ϊδ����
                q->p->word_num--;
                delete_var(q->p, -temp);
            }
            q = q->next;
        }
    }
    else
    { //������Ϊ������
        p = var_watch[-temp].negative;
        while (p)
        {
            if (p->p->flag == 0)
            { //�����������Ӿ�Ϊδ����
                p->p->flag = 1;
                p->satisfied = 1;
            }
            p = p->next;
        }
        q = var_watch[-temp].positive;
        while (q)
        {
            if (q->p->flag == 0)
            { //���������ڵ��Ӿ�Ϊδ����
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
    p++; //���ļ�����������
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
    fscanf(fp, "%c", &c); //��ȡ�ո�
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
	InitSat(&S, var_watch); //��ʼ��
	fp = fopen(cnfpath, "r");
    if (fp == NULL){
        printf("open document failed!\n ");
    }
	else
    LoadCnf(&S, var_watch, fp); //����LoadCnf ��������ȡ�ļ�
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
{                                                                   //��ʼ������,level�������
    int result;                                                     //�ж��Ƿ��н�
    int *puzzle = (int *)malloc((level * level + 1) * sizeof(int)); //����������ռ�
    number_var = level * level;
    clause_num = 0;
    clause_num += 2 * level * (level - 2) * 2;                     //��һ��Լ����ÿһ��Ҫȡlevel-3�������
    clause_num += 2 * level * calculate(level, level / 2 + 1) * 2; //�ڶ���Լ�������������
    number_var += 2 * calculate(level, 2) * (3 * level + 2);
    clause_num += 2 * calculate(level, 2) * (10 * level + 2); //������Լ��������������ͱ�Ԫ��
    Generatecnf(level);
                    //��������cnf�ļ�
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
    fp = fopen(cnfpath, "w+"); // ���ļ�
    fprintf(fp, "p cnf %d %d\n", number_var, clause_num);
    Rule1(level, fp);
    Rule2(level, fp);
    Rule3(level, fp);
    fclose(fp);
    return OK;
}

status Rule1(int level, FILE *fp)
{ //��һ��Լ��������ÿ��ÿ�в�����������������0������1����
    int i, j;
    for (i = 0; i < level; i++) //�����ɵ����
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
    for (i = 0; i < level - 2; i++) //�����ɵ����
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
{                                               //�ڶ���Լ��������ÿһ��ÿһ���е�1��0�ĸ�����ͬ
    int i, j, wordnum = level / 2 + 1, l[1000]; //wordnum���������һ���һ�������������ɵ�������������
    for (i = 0; i < level; i++)                 //��
    {
        for (j = 0; j < level; j++) //��¼���е�����Ԫ
            l[j] = level * i + j + 1;
        Rule2_clause(l, level, wordnum, 0, 0, fp); //�Ѹ������ɵ�����Ԫ�Ӿ�洢����
        for (j = 0; j < level; j++)                //��¼���еĸ���Ԫ
            l[j] = -(level * i + j + 1);
        Rule2_clause(l, level, wordnum, 0, 0, fp); //�Ѹ��еĸ���Ԫ�Ӿ�洢����
    }
    for (i = 0; i < level; i++) //��
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

void Rule2_clause(int arr[], int level, int wordnum, int k1, int k2, FILE *fp) //�����ɵ��Ӿ�д���ļ���
{
    static int rec[1000]; //��¼�������
    int i;
    if (k1 == wordnum) //�����ǰ����
    {
        for (i = 0; i < wordnum; ++i)
            fprintf(fp, "%d ", rec[i]);
        fprintf(fp, "0\n");
    }
    else
    {
        for (i = k2; i < level; ++i)
        {
            rec[k1] = arr[i];                             //�����и�ֵ
            Rule2_clause(arr, level, wordnum, k1 + 1, i + 1, fp); //�ݹ����
        }
    }
}

status Rule3(int level, FILE *fp)
{                                                  //������Լ������
    int i, j, k, literal_name = level * level + 1; //���ɵ��м��Ԫ�ӵı�Ž�����������Ԫ�ĺ�һλ
    for (i = 0; i < level - 1; i++)                //�ӵ�һ�п�ʼѡȡ��һ���Ƚ���
    {
        for (j = i + 1; j < level; j++) //�ӵ�һ���Ƚ���֮�����н��бȶ�
        {
            for (k = 0; k < level; k++) //ȷ����Ҫ�Ƚϵ�����֮��ʼ��ÿ�еĵ�һ����ʼ�Ƚ�
            {
                // 15711= 51��71ת���Ľ��
                fprintf(fp, "%d %d 0\n", i * level + k + 1, -literal_name);                            //51�� ?15711
                fprintf(fp, "%d %d 0\n", j * level + k + 1, -literal_name);                            //71�� ?15711
                fprintf(fp, "%d %d %d 0\n", -(i * level + k + 1), -(j * level + k + 1), literal_name); //?51�� ?71��15711
                literal_name += 1;                                                                     //�����һ����Ԫ���
                // 15710= ?51��?71ת���Ľ��
                fprintf(fp, "%d %d 0\n", -(i * level + k + 1), -literal_name);                   //?51�� ?15710
                fprintf(fp, "%d %d 0\n", -(j * level + k + 1), -literal_name);                   //?71�� ?15710
                fprintf(fp, "%d %d %d 0\n", i * level + k + 1, j * level + k + 1, literal_name); //51��71��15710
                literal_name += 1;
                // 1571= 15711��15710ת���Ľ��
                fprintf(fp, "%d %d 0\n", -(literal_name - 2), literal_name);                    //?15711��1571
                fprintf(fp, "%d %d 0\n", -(literal_name - 1), literal_name);                    //?15710��1571
                fprintf(fp, "%d %d %d 0\n", literal_name - 1, literal_name - 2, -literal_name); //15711��15710��?1571
                literal_name += 1;
            }
            // 157= ?[1571��1572�ġ���1578]
            fprintf(fp, "%d ", -literal_name); //?157��?1571��?1572�š���?1578
            for (k = 1; k < level + 1; k++)
                fprintf(fp, "%d ", -(literal_name + 2 - k * 3));
            fprintf(fp, "0\n");
            for (k = 1; k < level + 1; k++) //��1571��157���ģ�1572��157������1578��157��
                fprintf(fp, "%d %d 0\n", literal_name + 2 - k * 3, literal_name);
            fprintf(fp, "%d 0\n", literal_name);
            literal_name += 1;
        }
    }
    for (i = 0; i < level - 1; i++)     //��,���е�����
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
