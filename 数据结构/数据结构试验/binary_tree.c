/* Binary Tree On sequence Structure */
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include<math.h>

/*---------page 10 on textbook ---------*/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2

typedef int status;
typedef char ElemType; //数据元素类型定义

int key_value = 0;
/*-------page 22 on textbook -------*/
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10

typedef struct BiNode
{
    ElemType elem;
    struct BiNode *pre;
    struct BiNode *left;
    struct BiNode *right;
    int key;
} BiNode; //BiNode为二叉树结构体

typedef struct Treehead
{
    char name[100];
    BiNode *root;
    int id; //表示该树的id值
    struct Treehead *next;
    struct Treehead *pre;
    int nodes;
} Treehead; //Treehead为二叉树的头部，用来存储树的名字以及树的节点个数

BiNode *CreateBiTree(BiNode *T);                        //创建二叉树
status DestroyBiTree(Treehead *T);                      //销毁二叉树
status ClearBiTree(BiNode *T);                          //清空二叉树
status BiTreeEmpty(BiNode *T);                          //检查二叉树是否为空
status BiTreeDepth(BiNode *T);                          //检查树的深度
BiNode *LocateNode(BiNode *T, int e);                   //根据键值定位节点
status Assign(BiNode *T, int e, ElemType value);        //修改节点的值
BiNode *GetSibling(BiNode *T, int e);                   //获得兄弟节点
status InsertNode(BiNode *T, int e, int LR, BiNode *c); //插入节点
BiNode *DeleteNode(BiNode *T, int e);                   //删除节点
status PreOrderTraverse(BiNode *T);                     //先序遍历
status InOrderTraverse(BiNode *T);                      //中序遍历
status PostOrderTraverse(BiNode *T);                    //后序遍历
status LevelOrderTraverse(BiNode *T);                   //层序遍历
status SaveBiTree(Treehead *T);                         //保存二叉树
BiNode *LoadBiTree(BiNode *T);                          //加载二叉树
BiNode *CreateBiTree2(BiNode *T, ElemType **p);
BiNode visualprint(BiNode *T);

/*功能函数声明*/
int main(void)
{
    Treehead *head = NULL, *tail = NULL, *p = NULL, *q = NULL;
    int op = 1, id, renumber, key, LR;
    ElemType value;
    while (op)
    {
        system("cls");
        printf("\n\n");
        printf("      Menu for Binary Tree On Sequence Structure \n");
        printf("-------------------------------------------------\n");
        printf("    	  1. CreateTree      9. InsertNode\n");
        printf("    	  2. DestroyTree     10. DeleteNode\n");
        printf("    	  3. ClearTree      11. PreOrderTraverse\n");
        printf("    	  4. TreeEmpty      12. InOrderTrabverse\n");
        printf("    	  5. TreeDepth      13.PostOrderTraverse\n");
        printf("    	  6. LocateNode     14.LevelOrderTraverse\n");
        printf("    	  7. AssignNode     15.SaveBiTree\n");
        printf("          8. GetSibling     16.LoadBiTree\n");
        printf("          0. Exit           \n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~15]:");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            printf("请输入二叉树的前序序列:\n");
            if (head == NULL)
            {
                head = (Treehead *)malloc(sizeof(Treehead));
                tail = head;
                head->id = 1;
                p = head;
                head->pre = NULL;
                head->next = NULL;
            }
            else if (head != NULL)
            {
                tail = (Treehead *)malloc(sizeof(Treehead));
                p->next = tail;
                tail->pre = p;
                tail->id = p->id + 1;
                p = tail;
                tail->next = NULL;
            }
            tail->root = NULL;
            tail->nodes = 0;
            q = head;
            if ((tail->root = CreateBiTree(tail->root)) != NULL)
            {
                tail->root->pre = NULL;
                printf("请输入二叉树的名称:\n");
                fflush(stdin);
                gets(p->name);
                printf("二叉树创建成功！\n");
            }
            else
                printf("二叉树创建失败！\n");
            q->nodes = key_value;
            key_value = 0;
            printf("请输入任意键继续\n");
            getchar();
            getchar();
            break;
        case 2:
            printf("请输入二叉树的id:\n");
            scanf("%d", &id);
            while (q != NULL && q->id != id)
                q = q->next;
            if (q == NULL)
                printf("二叉树不存在！\n");
            else
            {
                if (q == head)
                    head = head->next;
                if (q == tail)
                    tail = tail->pre;
                DestroyBiTree(q);
                printf("二叉树删除成功！\n");
            }
            q = head;
            printf("请输入任意键继续\n");
            getchar();
            getchar();
            break;
        case 3:
            printf("请输入二叉树的id:\n");
            scanf("%d", &id);
            while (q != NULL && q->id != id)
                q = q->next;
            if (q == NULL)
                printf("二叉树不存在！\n");
            else
            {
                ClearBiTree(q->root);
                q->root = NULL;
                printf("二叉树清空成功!\n");
            }
            q = head;
            printf("请输入任意键继续\n");
            getchar();
            getchar();
            break;
        case 4:
            printf("请输入二叉树的id:\n");
            scanf("%d", &id);
            while (q != NULL && q->id != id)
                q = q->next;
            while (q != NULL && q->id != id)
                q = q->next;
            if (q == NULL)
                printf("二叉树不存在！\n");
            else
            {
                if (BiTreeEmpty(q->root) == OK)
                    printf("二叉树%s是空树!\n", q->name);
                else
                    printf("二叉树%s不是空树!\n", q->name);
            }
            q = head;
            printf("请输入任意键继续\n");
            getchar();
            getchar();
            break;
        case 5:
            printf("请输入二叉树的id:\n");
            scanf("%d", &id);
            while (q != NULL && q->id != id)
                q = q->next;
            while (q != NULL && q->id != id)
                q = q->next;
            if (q == NULL)
                printf("二叉树不存在！\n");
            else
            {
                printf("二叉树的深度为:%d\n", BiTreeDepth(q->root));
            }
            q = head;
            printf("请输入任意键继续\n");
            getchar();
            getchar();
            break;
        case 6:
            printf("请输入二叉树的id:\n");
            scanf("%d", &id);
            while (q != NULL && q->id != id)
                q = q->next;
            while (q != NULL && q->id != id)
                q = q->next;
            if (q == NULL)
                printf("二叉树不存在！\n");
            else
            {
                printf("请输入需要查找节点的键值:\n");
                scanf("%d", &key);
                BiNode *node;
                node = LocateNode(q->root, key);
                if (node != NULL)
                    printf("该节点的值为:%c\n", node->elem);
                else
                    printf("该节点不存在!\n");
            }
            q = head;
            printf("请输入任意键继续\n");
            getchar();
            getchar();
            break;
        case 7:
            printf("请输入二叉树的id:\n");
            scanf("%d", &id);
            while (q != NULL && q->id != id)
                q = q->next;
            while (q != NULL && q->id != id)
                q = q->next;
            if (q == NULL)
                printf("二叉树不存在！\n");
            else
            {
                printf("请输入需要修改的节点的键值:\n");
                scanf("%d", &key);
                printf("输入修改后的节点值:\n");
                fflush(stdin);
                scanf("%c", &value);
                if (Assign(q->root, key, value) == OK)
                    printf("节点值成功修改!\n");
                else
                    printf("节点值修改失败!\n");
            }
            q = head;
            printf("请输入任意键继续\n");
            getchar();
            getchar();
            break;
        case 8:
            printf("请输入二叉树的id:\n");
            scanf("%d", &id);
            while (q != NULL && q->id != id)
                q = q->next;
            while (q != NULL && q->id != id)
                q = q->next;
            if (q == NULL)
                printf("二叉树不存在！\n");
            else
            {
                printf("请输入需要获取兄弟结点的键值:\n");
                scanf("%d", &key);
                BiNode *bro;
                bro = GetSibling(q->root, key);
                if (bro == NULL)
                    printf("该节点的兄弟节点不存在!\n");
                else
                    printf("该节点的兄弟节点的节点值为:%c\n", bro->elem);
            }
            q = head;
            printf("请输入任意键继续\n");
            getchar();
            getchar();
            break;
        case 9:
            printf("请输入二叉树的id:\n");
            scanf("%d", &id);
            while (q != NULL && q->id != id)
                q = q->next;
            while (q != NULL && q->id != id)
                q = q->next;
            if (q == NULL)
                printf("二叉树不存在！\n");
            else
            {
                printf("请输入需要插入的的节点的键值:\n");
                scanf("%d", &key);
                printf("请输入需要插入的子树，0代表左树，1代表右树\n");
                scanf("%d", &LR);
                printf("请输入需要插入节点的值:\n");
                fflush(stdin);
                scanf("%c", &value);
                BiNode *c = NULL;
                c = (BiNode *)malloc(sizeof(BiNode));
                c->elem = value;
                c->left = NULL;
                c->right = NULL;
                c->pre = NULL;
                c->key = ++q->nodes;
                if (InsertNode(q->root, key, LR, c) == OK)
                    printf("节点成功插入!\n");
                else
                {
                    printf("节点插入失败!\n");
                    q->nodes--;
                }
            }
            q = head;
            printf("请输入任意键继续\n");
            getchar();
            getchar();
            break;
        case 10:
            printf("请输入二叉树的id:\n");
            scanf("%d", &id);
            while (q != NULL && q->id != id)
                q = q->next;
            while (q != NULL && q->id != id)
                q = q->next;
            if (q == NULL)
                printf("二叉树不存在！\n");
            else
            {
                printf("请输入需要删除结点的键值:\n");
                scanf("%d", &key);
                q->root = DeleteNode(q->root, key);
                q->nodes--;
            }
            q = head;
            printf("请输入任意键继续\n");
            getchar();
            getchar();
            break;
        case 11:
            printf("请输入二叉树的id:\n");
            scanf("%d", &id);
            while (q != NULL && q->id != id)
                q = q->next;
            while (q != NULL && q->id != id)
                q = q->next;
            if (q == NULL)
                printf("二叉树不存在！\n");
            else
            {
                PreOrderTraverse(q->root);
            }
            q = head;
            printf("\n请输入任意键继续\n");
            getchar();
            getchar();
            break;
        case 12:
            printf("请输入二叉树的id:\n");
            scanf("%d", &id);
            while (q != NULL && q->id != id)
                q = q->next;
            while (q != NULL && q->id != id)
                q = q->next;
            if (q == NULL)
                printf("二叉树不存在！\n");
            else
            {
                InOrderTraverse(q->root);
            }
            q = head;
            printf("\n请输入任意键继续\n");
            getchar();
            getchar();
            break;
        case 13:
            printf("请输入二叉树的id:\n");
            scanf("%d", &id);
            while (q != NULL && q->id != id)
                q = q->next;
            while (q != NULL && q->id != id)
                q = q->next;
            if (q == NULL)
                printf("二叉树不存在！\n");
            else
            {
                PostOrderTraverse(q->root);
            }
            q = head;
            printf("\n请输入任意键继续\n");
            getchar();
            getchar();
            break;
        case 14:
            printf("请输入二叉树的id:\n");
            scanf("%d", &id);
            while (q != NULL && q->id != id)
                q = q->next;
            while (q != NULL && q->id != id)
                q = q->next;
            if (q == NULL)
                printf("二叉树不存在！\n");
            else
            {
                LevelOrderTraverse(q->root);
            }
            q = head;
            printf("\n请输入任意键继续\n");
            getchar();
            getchar();
            break;
        case 15:
            printf("请输入二叉树的id:\n");
            scanf("%d", &id);
            while (q != NULL && q->id != id)
                q = q->next;
            while (q != NULL && q->id != id)
                q = q->next;
            if (q == NULL)
                printf("二叉树不存在！\n");
            else
            {
                SaveBiTree(q);
            }
            q = head;
            printf("请输入任意键继续\n");
            getchar();
            getchar();
            break;
        case 16:
            printf("请输入二叉树的id:\n");
            scanf("%d", &id);
            while (q != NULL && q->id != id)
                q = q->next;
            while (q != NULL && q->id != id)
                q = q->next;
            if (q == NULL)
                printf("二叉树不存在！\n");
            else
            {
                q->root = LoadBiTree(q->root);
            }
            q = head;
            printf("请输入任意键继续\n");
            getchar();
            getchar();
            break;
        case 0:
            break;
        } //end of switch
    }     //end of while
    printf("欢迎下次再使用本系统！\n");
    return 0;
} //end of main()

BiNode *CreateBiTree(BiNode *T)
{
    char ch;
    BiNode *trans = NULL; //用来存储函数的返回值的指针
    fflush(stdin);        //清空缓存区
    scanf("%c", &ch);
    if (ch != '#')
    {
        if (!(T = (BiNode *)malloc(sizeof(BiNode))))
            return NULL;
        T->elem = ch;
        T->key = ++key_value;
        trans = CreateBiTree(T->left);
        T->left = trans;
        if (trans != NULL)
            trans->pre = T;
        trans = CreateBiTree(T->right);
        T->right = trans;
        if (trans != NULL)
            trans->pre = T;
    }
    else
    {
        T = NULL; //若输入为‘#’，则返回NULL指针
    }
    return T;
}

status DestroyBiTree(Treehead *T)
{
    ClearBiTree(T->root); //调用清空函数把二叉树清空
    if (T->pre != NULL)   //删除存储树的表头
        T->pre->next = T->next;
    if (T->next != NULL)
        T->next->pre = T->pre;
    free(T);
    T = NULL;
    return OK;
}

status ClearBiTree(BiNode *T)
{
    if (T == NULL)
        return INFEASTABLE;
    else
    {
        ClearBiTree(T->left);
        ClearBiTree(T->right);
        free(T);
        T = NULL;
    }
    return OK;
}

status BiTreeEmpty(BiNode *T) //检查二叉树的头节点来判断是否为空树
{
    if (!T)
        return OK;
    else
        return ERROR;
}

status BiTreeDepth(BiNode *T)
{
    int HL = 0, HR = 0, MAXH = 0;
    if (T != NULL)
    { //递归查找左右子树的深度，选取深度较大的子节点的深度加一作为返回值
        HL = BiTreeDepth(T->left);
        HR = BiTreeDepth(T->right);
        MAXH = (HL > HR) ? HL : HR;
        return (MAXH + 1);
    }
    return MAXH;
}

BiNode *LocateNode(BiNode *T, int e)
{
    if (T == NULL)
        return NULL;
    else
    {
        if (T->key == e)
            return T;
        else
        { //递归查找左右子树
            BiNode *pl = NULL, *pr = NULL, *p;
            pl = LocateNode(T->left, e);
            pr = LocateNode(T->right, e);
            p = pl ? pl : pr;
            return p;
        }
    }
}

status Assign(BiNode *T, int e, ElemType value)
{
    BiNode *p;
    p = LocateNode(T, e); //根据键值定位需要修改的节点
    if (p == NULL)
        return ERROR;
    p->elem = value;
    return OK;
}

BiNode *GetSibling(BiNode *T, int e)
{
    BiNode *p;
    p = LocateNode(T, e);
    if (p == NULL || p->pre == NULL) //判断该节点是否在树中
        return NULL;
    if (p->pre->left == p)
        return p->pre->right;
    else if (p->pre->right == p)
        return p->pre->left;
}

status InsertNode(BiNode *T, int e, int LR, BiNode *c)
{ //根据传入的键值，以及LR判断插入左树还是右树，c为需要插入的节点
    BiNode *p;
    p = LocateNode(T, e);
    if (p == NULL)
        return ERROR;
    if (LR == 0)
    {
        c->right = p->left;
        if (c->right != NULL)
            c->right->pre = c;
        p->left = c;
        c->pre = p;
    }
    else if (LR == 1)
    {
        c->right = p->right;
        if (c->right != NULL)
            c->right->pre = c;
        p->right = c;
        c->pre = p;
    }
    return OK;
}

BiNode *DeleteNode(BiNode *T, int e)
{ //根据传入的键值删除相应的节点
    BiNode *p;
    p = LocateNode(T, e);
    if (p == NULL)
        return T;
    if (p->pre == NULL)
    { //该节点为根节点，分为四种情况，第一种左右子树都为空，第二种左子树为空，第三种右子树为空，第四种左右子树都不为空
        if (p->left == NULL && p->right == NULL)
        {
            free(p);
            T = NULL;
        }
        if (p->right != NULL && p->left == NULL)
        {
            T = p->right;
            T->pre = NULL;
            free(p);
        }
        if (p->right == NULL && p->left != NULL)
        {
            T = p->left;
            T->pre = NULL;
            free(p);
        }
        else if (p->right != NULL && p->left != NULL)
        {
            T = p->left;
            BiNode *q = p->left;
            while (q->right != NULL)
                q = q->right;
            q->right = p->right;
            q->right->pre = q;
            T->pre = NULL;
            free(p);
        }
    } //若删除的为根节点，该节点没有父亲节点，故需要单独分情况讨论
    else
    { //删除的节点不为根节点
        if (p->left == NULL && p->right == NULL)
        {
            if (p->pre->left == p)
                p->pre->left = NULL;
            else
                p->pre->right = NULL;
            free(p);
        }
        if (p->right != NULL && p->left == NULL)
        {
            if (p->pre->left == p)
                p->pre->left = p->right;
            else
                p->pre->right = p->right;
            free(p);
        }
        if (p->right == NULL && p->left != NULL)
        {
            if (p->pre->left == p)
                p->pre->left = p->left;
            else
                p->pre->right = p->left;
            free(p);
        }
        else if (p->right != NULL && p->left != NULL)
        {
            if (p->pre->left == p)
            {
                p->pre->left = p->left;
                p->left->pre = p->pre;
                BiNode *q = p->left;
                while (q->right != NULL)
                    q = q->right;
                q->right = p->right;
                p->right->pre = q;
                free(p);
            }
            if (p->pre->right == p)
            {
                p->pre->right = p->left;
                p->left->pre = p->pre;
                BiNode *q = p->left;
                while (q->right != NULL)
                    q = q->right;
                q->right = p->right;
                p->right->pre = q;
                free(p);
            }
        }
    }
    printf("该节点成功删除!\n");
    return T;
}

status PreOrderTraverse(BiNode *T)
{ //利用堆栈实现
    BiNode *ptr[100];
    int top = -1;
    BiNode *pt = T;
    ptr[++top] = pt;
    while (top != -1)
    {
        pt = ptr[top--];         //每次栈顶元素出栈
        printf("%c ", pt->elem); //输出
        if (pt->right)
            ptr[++top] = pt->right;
        if (pt->left)
            ptr[++top] = pt->left;
    }
    return OK;
}

status InOrderTraverse(BiNode *T)
{ //利用递归实现
    if (T != NULL)
    {
        InOrderTraverse(T->left);
        printf("%c ", T->elem);
        InOrderTraverse(T->right);
    }
    return OK;
}

status PostOrderTraverse(BiNode *T)
{ //利用递归实现
    if (T != NULL)
    {
        PostOrderTraverse(T->left);
        PostOrderTraverse(T->right);
        printf("%c ", T->elem);
    }
    return OK;
}

status LevelOrderTraverse(BiNode *T)
{ //利用队列实现层序遍历
    BiNode queue[100], *front = queue, *back = queue;
    if (T != NULL)
    {
        *back = *T;
        back++;
        while (front != back)
        {
            if (front->left != NULL)
            {
                *back = *front->left;
                back++;
            }
            if (front->right != NULL)
            {
                *back = *front->right;
                back++;
            }
            printf("%c ", front->elem);
            front++;
        }
    }
    return OK;
}

status SaveBiTree(Treehead *T)
{
    FILE *fp;
    char filename[30];
    printf("input file name: ");
    scanf("%s", filename);                    // 写文件
    if ((fp = fopen(filename, "wb")) == NULL) //文件打开失败
    {
        printf("File open error\n ");
        return 1;
    }
    ElemType a;
    BiNode *ptr[100];
    int top = -1;
    BiNode *pt = T->root;
    ptr[++top] = pt;
    while (top != -1)
    {
        pt = ptr[top--]; //每次栈顶元素出栈
        if (pt)
            a = pt->elem;
        else
            a = '#';
        fwrite(&a, sizeof(ElemType), 1, fp);
        if (pt->right)
            ptr[++top] = pt->right;
        else if (pt->elem != '#' && pt->right == NULL)
        {
            ptr[++top] = (BiNode *)malloc(sizeof(BiNode));
            ptr[top]->elem = '#';
            ptr[top]->left = NULL;
            ptr[top]->right = NULL;
        }
        if (pt->left)
            ptr[++top] = pt->left;
        else if (pt->elem != '#' && pt->left == NULL)
        {
            ptr[++top] = (BiNode *)malloc(sizeof(BiNode));
            ptr[top]->elem = '#';
            ptr[top]->left = NULL;
            ptr[top]->right = NULL;
        }
    }
    fclose(fp);
    printf("文件成功保存!\n");
    return OK;
}

BiNode *LoadBiTree(BiNode *T)
{
    FILE *fp;
    char filename[30];
    printf("input file name: ");
    scanf("%s", filename);
    if ((fp = fopen(filename, "rb")) == NULL)
    {
        printf("File open error\n ");
        return NULL;
    }
    BiNode *p = T;
    ElemType a[100], *b;
    b = a;
    while (fread(b, sizeof(ElemType), 1, fp))
    {
        b++;
    }
    b = a;
    T = CreateBiTree2(T, &b);
    fclose(fp);
    return T;
}

BiNode *CreateBiTree2(BiNode *T, ElemType **p)
{ //利用递归实现二叉树的加载，该函数使用了二级指针
    char ch;
    BiNode *trans = NULL;
    ch = **p;
    ElemType *q = *p;
    q = q + 1;
    *p = q;
    if (ch != '#')
    {
        if (!(T = (BiNode *)malloc(sizeof(BiNode))))
            return NULL;
        T->elem = ch;
        T->key = ++key_value;
        trans = CreateBiTree2(T->left, p);
        T->left = trans;
        if (trans != NULL)
            trans->pre = T;
        trans = CreateBiTree2(T->right, p);
        T->right = trans;
        if (trans != NULL)
            trans->pre = T;
    }
    else
    {
        T = NULL;
    }
    return T;
}

BiNode visualprint(BiNode *T){
    int i=pow(2,BiTreeDepth(T)),n=2,k=0;
    BiNode queue[100], *front = queue, *back = queue;
    if (T != NULL)
    {
        *back = *T;
        back++;
        while (front != back)
        {
            if (front->left != NULL)
            {
                *back = *front->left;
                back++;
            }
            if (front->right != NULL)
            {
                *back = *front->right;
                back++;
            }
            while(k<i/n)
                printf(" ");
            printf("%c", front->elem);
            front++;
        }
    }
}