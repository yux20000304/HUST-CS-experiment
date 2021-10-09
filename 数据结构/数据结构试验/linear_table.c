/* Linear Table On sequence Structure */
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

/*---------page 10 on textbook ---------*/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2

typedef int status;
typedef int ElemType; //数据元素类型定义

/*-------page 22 on textbook -------*/
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10

typedef struct
{ //顺序表（顺序结构）的定义
    ElemType *elem;
    int length;
    int listsize;
} SqList;
/*-----page 19 on textbook ---------*/
status InitList(SqList *L);
status DestroyList(SqList *L);
status ClearList(SqList *L);
status ListEmpty(SqList *L);
int ListLength(SqList *L);
status GetElem(SqList *L, int i, ElemType *e);
int LocateElem(SqList *L, ElemType e);
status PriorElem(SqList *L, ElemType cur, ElemType *pre_e);
status NextElem(SqList *L, ElemType cur, ElemType *next_e);
status ListInsert(SqList *L, int i, ElemType e);
status ListDelete(SqList *L, ElemType *e, int i);
status ListTrabverse(SqList L);
status LoadList(SqList *L);
status SaveList(SqList *L);
status InputData(SqList *L);
/*功能函数声明*/
int main(void)
{
    SqList L[3] = {0};
    int op = 1, renumber, flag, mail, id = 0;
    while (op)
    {
        system("cls");
        printf("\n\n");
        printf("      Menu for Linear Table On Sequence Structure \n");
        printf("-------------------------------------------------\n");
        printf("    	  1. InitList        8. PriorElem\n");
        printf("    	  2. DestroyList     9. NextElem\n");
        printf("    	  3. ClearList      10. ListInsert\n");
        printf("    	  4. ListEmpty      11. ListDelete\n");
        printf("    	  5. ListLength     12. ListTrabverse\n");
        printf("    	  6. GetElem        13.LoadList\n");
        printf("    	  7. LocateElem     14.SaveList\n");
        printf("          0. Exit           15.InputData\n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~15]:");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            printf("请输入表的id值[1~3]:");
            scanf("%d", &id);
            if (id > 3 || id < 0)
                printf("超出id范围\n");
            else if (InitList(L + id - 1) == OK)
            {
                printf("线性表创建成功！\n");
            }
            else
                printf("线性表创建失败！\n");
            printf("请输入任意键继续\n");
            getchar();
            getchar();
            break;
        case 2:
            printf("请输入表的id值[1~3]:");
            scanf("%d", &id);
            if (id > 3 || id < 0)
                printf("超出id范围\n");
            else if ((renumber = DestroyList(L + id - 1)) == OK)
            {
                printf("线性表删除成功！\n");
                L->elem = NULL;
            }
            else if (renumber == INFEASTABLE)
                printf("线性表不存在！\n");
            else
                printf("线性表删除失败！\n");
            printf("请输入任意键继续\n");
            getchar();
            getchar();
            break;
        case 3:
            printf("请输入表的id值[1~3]:");
            scanf("%d", &id);
            if (id > 3 || id < 0)
                printf("超出id范围\n");
            else if ((renumber = ClearList(L + id - 1)) == OK)
                printf("线性表清除成功！\n");
            else if (renumber == INFEASTABLE)
                printf("线性表是空的！\n");
            printf("请输入任意键继续\n");
            getchar();
            getchar();
            break;
        case 4:
            printf("请输入表的id值[1~3]:");
            scanf("%d", &id);
            if (id > 3 || id < 0)
                printf("超出id范围\n");
            else if ((renumber = ListEmpty(L + id - 1)) == INFEASTABLE)
                printf("线性表不存在！\n");
            else if (renumber == TRUE)
                printf("线性表是空的！\n");
            else
                printf("线性表不是空的！\n");
            printf("请输入任意键继续\n");
            getchar();
            getchar();
            break;
        case 5:
            printf("请输入表的id值[1~3]:");
            scanf("%d", &id);
            if (id > 3 || id < 0)
                printf("超出id范围\n");
            else if ((renumber = ListLength(L + id - 1)) != INFEASTABLE)
                printf("线性表长度为:%d\n", renumber);
            else
                printf("线性表不存在！\n");
            printf("请输入任意键继续\n");
            getchar();
            getchar();
            break;
        case 6:
            printf("请输入表的id值[1~3]:");
            scanf("%d", &id);
            if (id > 3 || id < 0)
                printf("超出id范围\n");
            else
            {
                printf("请输入元素位置");
                scanf("%d", &flag);
                if ((renumber = GetElem(L + id - 1, flag, &mail)) == OK)
                    printf("位置%d的元素是%d\n", flag, mail);
                else if (renumber == ERROR)
                    printf("该位置越界！\n");
                else
                    printf("线性表不存在！\n");
            }
            printf("请输入任意键继续\n");
            getchar();
            getchar();
            break;
        case 7:
            printf("请输入表的id值[1~3]:");
            scanf("%d", &id);
            if (id > 3 || id < 0)
                printf("超出id范围\n");
            else
            {
                printf("输入需要定位的元素:");
                scanf("%d", &flag);
                if ((renumber = LocateElem(L + id - 1, flag)) > 0)
                    printf("匹配成功，该元素位置为:%d\n", renumber);
                else if (renumber == ERROR)
                    printf("匹配失败！\n");
                else
                    printf("线性表不存在！\n");
            }
            printf("请输入任意键继续\n");
            getchar();
            getchar();
            break;
        case 8:
            printf("请输入表的id值[1~3]:");
            scanf("%d", &id);
            if (id > 3 || id < 0)
                printf("超出id范围\n");
            else
            {
                printf("输入需要寻找前驱的元素:");
                scanf("%d", &flag);
                if ((renumber = PriorElem(L + id - 1, flag, &mail)) == OK)
                    printf("该数据的前驱元素为:%d\n", mail);
                else if (renumber == ERROR)
                    printf("该元素没有前驱元素\n");
                else
                    printf("线性表不存在！\n");
            }
            printf("请输入任意键继续\n");
            getchar();
            getchar();
            break;
        case 9:
            printf("请输入表的id值[1~3]:");
            scanf("%d", &id);
            if (id > 3 || id < 0)
                printf("超出id范围\n");
            else
            {
                printf("输入需要寻找后继的元素:");
                scanf("%d", &flag);
                if ((renumber = NextElem(L + id - 1, flag, &mail)) == OK)
                    printf("该数据的后继元素为:%d\n", mail);
                else if (renumber == ERROR)
                    printf("该数据没有后继元素\n");
                else
                    printf("线性表不存在\n");
            }
            printf("请输入任意键继续\n");
            getchar();
            getchar();
            break;
        case 10:
            printf("请输入表的id值[1~3]:");
            scanf("%d", &id);
            if (id > 3 || id < 0)
                printf("超出id范围\n");
            else
            {
                printf("请输入需要插入元素的位置:");
                scanf("%d", &flag);
                printf("请输入插入元素的值");
                scanf("%d", &mail);
                if ((renumber = ListInsert(L + id - 1, flag, mail)) == OK)
                    printf("插入成功!\n");
                else if (renumber == OVERFLOW)
                    printf("存储分配失败\n");
                else if (renumber == ERROR)
                    printf("插入元素的位置输入不合法\n");
                else
                    printf("线性表不存在\n");
            }
            printf("请输入任意键继续\n");
            getchar();
            getchar();
            break;
        case 11:
            printf("请输入表的id值[1~3]:");
            scanf("%d", &id);
            if (id > 3 || id < 0)
                printf("超出id范围\n");
            else
            {
                printf("请输入需要删除的元素的位置:");
                scanf("%d", &flag);
                if ((renumber = ListDelete(L + id - 1, &mail, flag)) == OK)
                    printf("该节点删除成功,删除的节点的值为:%d\n", mail);
                else if (renumber == ERROR)
                    printf("删除元素的位置输入不合法\n");
                else
                    printf("线性表不存在\n");
            }
            printf("请输入任意键继续\n");
            getchar();
            getchar();
            break;
        case 12:
            printf("请输入表的id值[1~3]:");
            scanf("%d", &id);
            if (id > 3 || id < 0)
                printf("超出id范围\n");
            else if (ListTrabverse(L[id - 1]))
                printf("线性表不存在！\n");
            printf("请输入任意键继续\n");
            getchar();
            getchar();
            break;
        case 13:
            printf("请输入表的id值[1~3]:");
            scanf("%d", &id);
            if (id > 3 || id < 0)
                printf("超出id范围\n");
            else if ((renumber = LoadList(L + id - 1)) == OK)
                printf("线性表成功赋值\n");
            else if (renumber == 1)
                printf("无法打开文件\n");
            else
                printf("线性表不存在\n");
            printf("请输入任意键继续\n");
            getchar();
            getchar();
            break;
        case 14:
            printf("请输入表的id值[1~3]:");
            scanf("%d", &id);
            if (id > 3 || id < 0)
                printf("超出id范围\n");
            else if ((renumber = SaveList(L + id - 1)) == OK)
                printf("文件成功保存\n");
            else if (renumber == 1)
                printf("无法打开文件\n");
            else
                printf("线性表不存在\n");
            printf("请输入任意键继续\n");
            getchar();
            getchar();
            break;
        case 15:
            printf("请输入表的id值[1~3]:");
            scanf("%d", &id);
            if (id > 3 || id < 0)
            {
                printf("超出id范围\n");
                getchar();
            }
            else if (InputData(L + id - 1) == OK)
                printf("数据成功输入\n");
            else
            {
                printf("线性表不存在\n");
                getchar();
            }
            printf("请输入任意键继续\n");
            getchar();
            break;
        case 0:
            break;
        } //end of switch
    }     //end of while
    printf("欢迎下次再使用本系统！\n");
    return 0;
} //end of main()
/*--------page 23 on textbook --------------------*/

status InitList(SqList *L) //初始化表
{
    L->elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType)); //分配内存
    if (!L->elem)                                                    //如果L分配失败，返回overflow
        exit(OVERFLOW);
    L->length = 0;
    L->listsize = LIST_INIT_SIZE;
    return OK;
}

status DestroyList(SqList *L)
{
    if (!L->elem)
        return INFEASTABLE;
    L->listsize = L->length = 0; //把表长和空间清0
    free(L->elem);               //释放存储空间
    return OK;
}

status ClearList(SqList *L)
{ //把表中的数据清除
    if (!L->elem)
        return INFEASTABLE;
    L->length = 0;
    return OK;
}

status ListEmpty(SqList *L)
{ //检测线性表是否为空
    if (!L->elem)
        return INFEASTABLE;
    if (L->length == 0)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

int ListLength(SqList *L)
{ //输出线性表长度
    if (!L->elem)
        return INFEASTABLE;
    return L->length;
}

status GetElem(SqList *L, int i, ElemType *e)
{
    if (!L->elem)
        return INFEASTABLE;
    if (i < 1 || i > L->length)
        return ERROR;        // 判断位置是否越界，越界则返回错误
    *e = *(L->elem + i - 1); //e变量用来存储该元素的值
    return OK;
}

int LocateElem(SqList *L, ElemType e)
{ //e为需要定位的元素
    if (!L->elem)
        return INFEASTABLE;
    int i;
    for (i = 1; i <= L->length; i++)
    {
        if (L->elem[i - 1] == e) //如果匹配成功，则返回该元素的位置
            return i;
    }
    return ERROR; //匹配失败，返回ERROR
}

status PriorElem(SqList *L, ElemType cur, ElemType *pre_e)
{ //pre_e用来存储前驱存储的元素
    if (!L->elem)
        return INFEASTABLE;
    int index = LocateElem(L, cur) - 1; //定义位置变量
    if (index <= 0)
        return ERROR;
    *pre_e = *(L->elem + index - 1); //pre_e指针指向前驱元素
    return OK;
}

status NextElem(SqList *L, ElemType cur, ElemType *next_e)
{ //next_e用来存储后继的元素
    if (!L->elem)
        return INFEASTABLE;
    int index = LocateElem(L, cur); //定义位置变量
    if (index < 0 || index >= L->length)
        return ERROR;
    *next_e = *(L->elem + index); //next_e指针指向后继元素
    return OK;
}

status ListInsert(SqList *L, int i, ElemType e)
{
    //在顺序线性表L中第i个位置之前插入新的元素e
    //i的合法值为1<=i<=L->length+1
    ElemType *newbase;
    ElemType *p, *q;
    if (!L->elem)
        return INFEASTABLE;
    if (i < 1 || i > L->length + 1)
        return ERROR; //i值不合法
    if (L->length >= L->listsize)
    { //当前存储空间已满，增加分配
        newbase = (ElemType *)realloc(L->elem, (L->listsize + LISTINCREMENT) * sizeof(ElemType));
        if (!newbase)
            return OVERFLOW;          //存储分配失败
        L->elem = newbase;            //新的基址
        L->listsize += LISTINCREMENT; //增加存储容量
    }
    q = &(L->elem[i - 1]);                       //q为插入位置
    for (p = &(L->elem[L->length]); p >= q; --p) //插入位置及之后的元素右移
        *(p + 1) = *p;
    *q = e;      //插入e
    ++L->length; //表长增1
    return OK;
}

status ListDelete(SqList *L, ElemType *e, int i)
{ //删除表中的第i个元素，并用e返回其值
    ElemType *p, *q;
    if (!L->elem)
        return INFEASTABLE;
    if ((i < 1) || (i > L->length))
        return ERROR;            //i值不合法
    p = &(L->elem[i - 1]);       //p为被删除元素的位置
    *e = *p;                     //被删除元素的值赋给e
    q = L->elem + L->length - 1; //表尾元素的位置
    for (++p; p <= q; ++p)
        *(p - 1) = *p; //被删除元素之后的元素左移
    --L->length;       //表长减一
    return OK;
}

status ListTrabverse(SqList L)
{
    if (!L.elem)
        return INFEASTABLE;
    int i;
    printf("\n-----------all elements -----------------------\n");
    for (i = 0; i < L.length; i++)
        printf("%d ", L.elem[i]);
    printf("\n------------------ end ------------------------\n");
    return L.length;
}

status SaveList(SqList *L)
{
    if (!L->elem)
        return INFEASTABLE;
    FILE *fp;
    char filename[30];
    printf("input file name: ");
    scanf("%s", filename);                    // 写文件
    if ((fp = fopen(filename, "wb")) == NULL) //文件打开失败
    {
        printf("File open error\n ");
        return 1;
    }
    fwrite(L->elem, sizeof(ElemType), L->length, fp);
    fclose(fp);
    return OK;
}

status LoadList(SqList *L)
{
    if (!L) // 线性表未创建
        return INFEASTABLE;
    else if (!L->elem)
        return INFEASTABLE;

    //读文件
    FILE *fp;
    char filename[30];
    printf("input file name: ");
    scanf("%s", filename);
    L->length = 0;
    if ((fp = fopen(filename, "rb")) == NULL)
    {
        printf("File open error\n ");
        return 1;
    }
    while (fread(&(L->elem[L->length]), sizeof(ElemType), 1, fp))
        L->length++;
    fclose(fp);
    return OK;
}

status InputData(SqList *L)
{
    if (!L->elem)
        return INFEASTABLE;
    char str[100];
    int i = 0, count = 0, a[100] = {0}, symbol = 0;
    printf("请输入一串元素\n");
    getchar();
    gets(str);
    while (1)
    {
        while (str[i] && (str[i] < '0' || str[i] > '9') && str[i] != '-') //判断负数的情况
            i++;
        if (str[i])
        {
            if (str[i] == '-')
            {
                symbol = 1;
                i++;
            }
            while (str[i] >= '0' && str[i] <= '9')
            {
                a[count] = 10 * a[count] + str[i] - '0';
                i++;
            }
            if (symbol == 1)
                a[count] = -a[count];
            symbol = 0;
            count++;
        }
        else
            break;
    }
    for (i = 0; i < count; i++)
    { //接着之前的数据在之后继续加新的数据
        L->elem[L->length + i] = a[i];
    }
    L->length += i;
    return OK;
}