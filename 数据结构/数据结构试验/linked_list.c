/* Linked List On sequence Structure */
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

typedef struct ListNode
{ //链表元素结构体
    ElemType elem;
    struct ListNode *next;
} ListNode,*ListNodePtr;        //ListNode为结构体，*ListNodePtr为结构体元素指针


status InitList(ListNode **L);
status DestroyList(ListNodePtr  L);
status ClearList(ListNodePtr  L);
status ListEmpty(ListNodePtr  L);
int ListLength(ListNodePtr  L);
status GetElem(ListNodePtr  L, int i, ElemType *e);
int LocateElem(ListNodePtr  L, ElemType e);
status PriorElem(ListNodePtr  L, ElemType cur, ElemType *pre_e);
status NextElem(ListNodePtr  L, ElemType cur, ElemType *next_e);
status ListInsert(ListNodePtr  L, int i, ElemType e);
status ListDelete(ListNodePtr  L, ElemType *e, int i);
status ListTrabverse(ListNodePtr  L);
status LoadList(ListNodePtr  L);
status SaveList(ListNodePtr  L);
status InputData(ListNodePtr  L);
/*功能函数声明*/
int main(void)
{
    ListNodePtr L[3];
    int i;
    for(i=0;i<3;i++)
        L[i]=NULL;
    int op = 1, renumber, flag, mail, id = 1;
    while (op)
    {
        system("cls");
        printf("\n\n");
        printf("      Menu for Linked List On Sequence Structure \n");
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
            if(id<0||id>3)
                printf("超出id范围\n");
            else{
                if (InitList(L+id-1) == OK)
                {
                    printf("线性表创建成功！\n");
                }
                else
                    printf("线性表创建失败！\n");
            }
            printf("请输入任意键继续\n");
            getchar();
            getchar();
            break;
        case 2:
            printf("请输入表的id值[1~3]:");
            scanf("%d", &id);
            if (id < 0||id>3)
                printf("超出id范围\n");
            else{
                if ((renumber = DestroyList(L[id-1])) == OK)
                {
                    printf("线性表删除成功！\n");
                    L[id-1] = NULL;
                }
                else if (renumber == INFEASTABLE)
                    printf("线性表不存在！\n");
                else
                    printf("线性表删除失败！\n");
            }
            printf("请输入任意键继续\n");
            getchar();
            getchar();
            break;
        case 3:
            printf("请输入表的id值[1~3]:");
            scanf("%d", &id);
            if (id > 3 || id < 0)
                printf("超出id范围\n");
            else{
                if ((renumber = ClearList(L [id - 1])) == OK)
                    printf("线性表清除成功！\n");
                else if (renumber == INFEASTABLE)
                    printf("线性！\n");
            }
            printf("请输入任意键继续\n");
            getchar();
            getchar();
            break;
        case 4:
            printf("请输入表的id值[1~3]:");
            scanf("%d", &id);
            if (id > 3 || id < 0)
                printf("超出id范围\n");
            else{
                if ((renumber = ListEmpty(L [ id - 1])) == INFEASTABLE)
                    printf("线性表不存在！\n");
                else if (renumber == TRUE)
                    printf("线性表是空的！\n");
                else
                    printf("线性表不是空的！\n");
            }
            printf("请输入任意键继续\n");
            getchar();
            getchar();
            break;
        case 5:
            printf("请输入表的id值[1~3]:");
            scanf("%d", &id);
            if (id > 3 || id < 0)
                printf("超出id范围\n");
            else{
                if ((renumber = ListLength(L [id - 1])) != INFEASTABLE)
                    printf("线性表长度为:%d\n", renumber);
                else
                    printf("线性表不存在！\n");
                }
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
                if ((renumber = GetElem(L [ id - 1], flag, &mail)) == OK)
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
                if ((renumber = LocateElem(L [id - 1], flag)) > 0)
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
                if ((renumber = PriorElem(L [id - 1], flag, &mail)) == OK)
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
                if ((renumber = NextElem(L [id - 1], flag, &mail)) == OK)
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
                if ((renumber = ListInsert(L [id - 1], flag, mail)) == OK)
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
                if ((renumber = ListDelete(L [id - 1], &mail, flag)) == OK)
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
            else{ 
                if (ListTrabverse(L[id - 1])==INFEASTABLE)
                    printf("线性表不存在！\n");
            }
            printf("请输入任意键继续\n");
            getchar();
            getchar();
            break;
        case 13:
            printf("请输入表的id值[1~3]:");
            scanf("%d", &id);
            if (id > 3 || id < 0)
                printf("超出id范围\n");
            else if ((renumber = LoadList(L[id - 1])) == OK)
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
            else{ 
                if ((renumber = SaveList(L [id - 1])) == OK)
                    printf("文件成功保存\n");
                else if (renumber == 1)
                    printf("无法打开文件\n");
                else
                    printf("线性表不存在\n");
            }
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
            else if (InputData(L [id - 1]) == OK)
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

status InitList(ListNode **L){
    *L=(ListNode *)malloc(sizeof(ListNode));
    if(!L)
        return OVERFLOW;
    (*L)->elem=0;        //把表长清0
    (*L)->next=NULL;       //把指针域赋值为NULL
    return OK;
}

status DestroyList(ListNodePtr  L){
    if(!L)
        return INFEASTABLE;
    ListNodePtr p=L;
    while(!p){
        p=p->next;      //两个指针，一个用来判断是否到了表的尾部，另外一个用来释放存储空间
        free(L);
        L=p;
    }
    return OK;
}

status ClearList(ListNodePtr  L){
    if(!L)
        return INFEASTABLE;
    DestroyList(L->next);       //调用销毁表的函数，把除了表头以外的节点全部摧毁掉
    L->next=NULL;
    L->elem=0;
    return OK;
}

status ListEmpty(ListNodePtr  L){
    if(!L)
        return INFEASTABLE;
    if(L->elem==0)
        return TRUE;
    else
        return FALSE;
}

int ListLength(ListNodePtr  L){
    if(!L)
        return INFEASTABLE;
    return L->elem;           //把表长赋值给e元素的数据域
}

status GetElem(ListNodePtr  L, int i, ElemType *e){
    if(!L)
        return INFEASTABLE;
    ListNode *p=L;
    if(i<1||i>L->elem)
        return ERROR;
    while(i>0){             //遍历整个线性表，直到找到所输入的位置
        p=p->next;
        i--;
    }
    *e=p->elem;             //把该位置的元素赋值给e的数据域
    return OK;
}

int LocateElem(ListNodePtr  L, ElemType e){
    if(!L)
        return INFEASTABLE;
    int count=0;
    ListNode *p=L;
    while(p){
        if(p->elem==e)      //判断该节点存储的元素是否为需要寻找的元素
            return count;     //该元素的的位置
        p=p->next;
        count++;
    }
    return ERROR;
}

status PriorElem(ListNodePtr  L, ElemType cur, ElemType *pre_e){
    if(!L)
        return INFEASTABLE;
    ListNode *p=L->next;
    while(p->next!=NULL){
        if(p->next->elem==cur){         //如果该节点的后继节点的存储值和cur变量相同，则把该节点的存储值赋值给pre_e
                *pre_e=p->elem;   
                return OK;
        }
        p=p->next;
    }
    return  ERROR;
}

status NextElem(ListNodePtr  L, ElemType cur, ElemType *next_e){
    if(!L)
        return INFEASTABLE;
    ListNode *p=L->next;
    while(p&&p->next){        //注意要排除p不是尾节点
        if(cur==p->elem){
            *next_e=p->next->elem;
            return OK;
        }
        p=p->next;
    }
    return ERROR;
}

status ListInsert(ListNodePtr  L, int i, ElemType e){
    if(!L)
        return INFEASTABLE;
    if(i<1||i>L->elem+1)
        return ERROR;
    ListNode *p=L,*q=NULL;
    while(i>1){         //把p指针移动到需要添加元素的位置
        p=p->next;
        i--;
    }
    q=(ListNodePtr)malloc(sizeof(ListNode));
    q->elem=e;
    q->next=p->next;
    p->next=q;
    L->elem++;
    return OK;
}

status ListDelete(ListNodePtr  L, ElemType *e, int i){
    if(!L)
        return INFEASTABLE;
    if(i<1||i>L->elem)
        return ERROR;
    ListNode *p=L;
    while(i>1){         //把p指针移动到需要删除的位置
        p=p->next;
        i--;
    }
    *e=p->next->elem;
    p->next=p->next->next;
    L->elem--;
    return OK;
}

status ListTrabverse(ListNodePtr  L){
    if (!L)
        return INFEASTABLE;
    ListNode *p=L->next;
    printf("\n-----------all elements -----------------------\n");
    for (; p ; p=p->next)
        printf("%d ",p->elem);
    printf("\n------------------ end ------------------------\n");
    return OK;
}

status LoadList(ListNodePtr  L)
{
    if (!L)          // 线性表未创建
        return INFEASTABLE;


    //读文件
    FILE *fp;
    char filename[30];
    printf("input file name: ");
    scanf("%s", filename);
    L->elem = 0;
    if ((fp = fopen(filename, "rb")) == NULL)
    {
        printf("File open error\n ");
        return 1;
    }
    ListNode *p=L,*q=NULL;
    q=(ListNode *)malloc(sizeof(ListNode));
    while (fread(&(q->elem), sizeof(ElemType), 1, fp)){
        p->next=q;
        q=(ListNode *)malloc(sizeof(ListNode));
        p=p->next;
        p->next=NULL;
        L->elem++;
    }
    fclose(fp);
    return OK;
}

status SaveList(ListNodePtr  L)
{
    if (!L)
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
    int a[100],i;
    ListNode *p=L;
    for(i=0;i<L->elem&&p->next!=NULL;i++){        //把链表中的元素存储到数组中
        p=p->next;
        a[i]=p->elem;
    }
    fwrite(a, sizeof(ElemType), L->elem, fp);
    fclose(fp);
    return OK;
}

status InputData(ListNodePtr  L){
    if(!L)
        return INFEASTABLE;
    ListNode *p=L;
    while(p->next!=NULL)
        p=p->next;
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
        p->next=(ListNode *)malloc(sizeof(ListNode));
        p=p->next;
        p->elem=a[i];
        p->next=NULL;
    }
    L->elem += i;
    return OK;
}