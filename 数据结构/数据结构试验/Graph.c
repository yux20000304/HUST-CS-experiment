/*Graph On Adjacency List*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define DG 1
#define DN 2
#define UDG 3
#define UDN 4 //常量定义

#define INITLENGTH 80
#define INCREMENT 20
#define MAXVERTEXNUM 20


int visit[20];

typedef int status;
typedef int ElemType;
typedef int KeyType;//数据元素类型定义

typedef struct ArcNode {    //弧度定义
	int rad;
	struct ArcNode *next;
}ArcNode;

typedef struct Vertex { //顶点定义
    char data;
    int key;
	struct ArcNode *firstArc;
}Vertex;

typedef struct Graph{   //图定义
	struct Vertex elem[MAXVERTEXNUM];
	char name[100];
	int vernum;     //顶点数
	int arcnum;     //弧度数
    int id;         //表示该图的id值
    struct Graph *next;
    struct Graph *pre;
}Graph;


status CreateGraph(char value[],int arcnode[],int vnum,int arcnum,Graph *a);
status DestroyGraph(Graph *a);
Vertex *LocateVex(Graph *a,int key);
status PutVex (Graph *a,int key,char value);
Vertex *FirstAdjVex(Graph *a,int key);
Vertex *NextAdjVex(Graph *a,int v,int w);
status InsertVex(Graph *a,char v);
status DeleteVex(Graph *a,int v);   //v是删除节点的键值
status InsertArc(Graph *a,int v,int w);
status DeleteArc(Graph *a,int v,int w);
status DFSTraverse(Graph *a);
void DFS(Graph *a,int v);
status BFSTraverse(Graph *a);
void BFS(int i,Graph *a);
status SaveGraph(Graph *a);
status LoadGraph(Graph *a);

int main(void)
{
    Graph *head=NULL,*tail=NULL,*p=NULL,*q=NULL;
    int op = 1,vnum=0,anum=0,i=0,id=0,key_value;
    while (op)
    {
        system("cls");
        printf("\n\n");
        printf("      Menu for Digraph On Sequence Structure \n");
        printf("-------------------------------------------------\n");
        printf("    	  1. CreateGraph      9. InsertArc\n");
        printf("    	  2. DestroyGraph    10. DeleteArc\n");
        printf("    	  3. LocateVex       11. DFSTraverse\n");
        printf("    	  4. PutVex          12. BFSTrabverse\n");
        printf("    	  5. FirstAdjVex     13.SaveGraph\n");
        printf("    	  6. NextAdjVex      14.LoadGraph\n");
        printf("    	  7. InsertVex     \n");
        printf("          8. DeleteVex     \n");
        printf("          0. Exit           \n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~15]:");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            if(head==NULL){
                head=(Graph *)malloc(sizeof(Graph));
                tail=head;
                head->id = 1;
                p=head;
                head->pre=NULL;
                head->next=NULL;
            }
            else if (head != NULL)
            {
                tail = (Graph *)malloc(sizeof(Graph));
                p->next = tail;
                tail->pre = p;
                tail->id = p->id + 1;
                p = tail;
                tail->next = NULL;
            }
            q = head;
            printf("请输入图的名称:\n");
            fflush(stdin);
            gets(tail->name);
            printf("请输入顶点数和边数:\n");
            scanf("%d %d",&vnum,&anum);
            char a[1000];
            int b[1000]; 
            printf("请输入顶点的值:\n");
            fflush(stdin);
            for(i=0;i<vnum;i++){
                scanf("%c",&a[i]);
                fflush(stdin);
            }
            printf("请输入弧的信息(a,b):\n");
            for(i=0;i<anum*2;i++){
                scanf("%d",&b[i]);
                scanf("%d",&b[++i]);
            }
            CreateGraph(a,b,vnum,anum,tail);
            printf("图%s创建成功!\n",tail->name);
            printf("请输入任意键继续\n");
            getchar();
            getchar();
            break;
        case 2:
            printf("请输入图的id:\n");
            scanf("%d", &id);
            while (q != NULL && q->id != id)
                q = q->next;
            if (q == NULL)
                printf("图不存在！\n");
            else
            {
                if (q == head)
                    head = head->next;
                if (q == tail)
                    tail = tail->pre;
                DestroyGraph(q);
            }
            q = head;
            printf("请输入任意键继续\n");
            getchar();
            getchar();
            break;
        case 3:
            printf("请输入图的id:\n");
            scanf("%d", &id);
            while (q != NULL && q->id != id)
                q = q->next;
            if (q == NULL)
                printf("图不存在！\n");
            else
            {
                printf("请输入需要查找的顶点的键值:\n");
                scanf("%d",&key_value);
                Vertex *node=NULL;
                node=LocateVex(q,key_value);
                if(node==NULL||node->key==-1)
                    printf("该节点不存在!\n");
                else 
                    printf("该顶点的值为%c\n",node->data);
            }
            q = head;
            printf("请输入任意键继续\n");
            getchar();
            getchar();
            break;
        case 4:
            printf("请输入图的id:\n");
            scanf("%d", &id);
            while (q != NULL && q->id != id)
                q = q->next;
            if (q == NULL)
                printf("图不存在！\n");
            else
            {
                char ch;
                printf("请输入需要修改的顶点的键值:\n");
                scanf("%d",&key_value);
                printf("请输入修改后的节点的值:\n");
                fflush(stdin);
                scanf("%c",&ch);
                if(PutVex(q,key_value,ch)==ERROR)
                    printf("修改失败!\n");
                else
                    printf("修改成功\n");
            }
            q = head;
            printf("请输入任意键继续\n");
            getchar();
            getchar();
            break;
        case 5:
            printf("请输入图的id:\n");
            scanf("%d", &id);
            while (q != NULL && q->id != id)
                q = q->next;
            if (q == NULL)
                printf("图不存在！\n");
            else
            {
                Vertex *p=NULL;
                printf("请输入需要寻找的弧度的顶点的键值:\n");
                scanf("%d",&key_value);
                p=FirstAdjVex(q,key_value);
                if(p==NULL)
                    printf("不存在第一邻接点!\n");
                else
                    printf("第一邻接点值为:%c\n",p->data);
            }
            q = head;
            printf("请输入任意键继续\n");
            getchar();
            getchar();
            break;
        case 6:
             printf("请输入图的id:\n");
            scanf("%d", &id);
            while (q != NULL && q->id != id)
                q = q->next;
            if (q == NULL)
                printf("图不存在！\n");
            else
            {
                Vertex *p=NULL;
                int v,w;
                printf("请输入需要寻找下一邻接点的两个顶点的键值:(a,b)\n");
                scanf("%d %d",&v,&w);
                p=NextAdjVex(q,v,w);
                if(p==NULL)
                    printf("不存在下一邻接点!\n");
                else
                    printf("下一邻接点值为:%c\n",p->data);
            }
            q = head;
            printf("请输入任意键继续\n");
            getchar();
            getchar();
            break;
        case 7:
            printf("请输入图的id:\n");
            scanf("%d", &id);
            while (q != NULL && q->id != id)
                q = q->next;
            if (q == NULL)
                printf("图不存在！\n");
            else
            {
                char ch;
                int re;
                printf("请输入需要添加的点的值:\n");
                fflush(stdin);
                scanf("%c",&ch);
                re=InsertVex(q,ch);
                if(re==OK)
                    printf("节点成功添加!\n");
                else
                    printf("节点添加失败\n");
            }
            q = head;
            printf("请输入任意键继续\n");
            getchar();
            getchar();
            break;
        case 8:
            printf("请输入图的id:\n");
            scanf("%d", &id);
            while (q != NULL && q->id != id)
                q = q->next;
            if (q == NULL)
                printf("图不存在！\n");
            else
            {
                int re,key;
                printf("请输入需要删除的顶点的键值:\n");
                scanf("%d",&key);
                re=DeleteVex(q,key);
                if(re==OK)
                    printf("该节点成功删除!\n");
                else
                    printf("该节点删除失败!\n");
            }
            q = head;
            printf("请输入任意键继续\n");
            getchar();
            getchar();
            break;
        case 9:
            printf("请输入图的id:\n");
            scanf("%d", &id);
            while (q != NULL && q->id != id)
                q = q->next;
            if (q == NULL)
                printf("图不存在！\n");
            else
            {
                int v,w,re;
                printf("请输入需要插入的弧的信息:(a,b)\n");
                scanf("%d %d",&v,&w);
                re=InsertArc(q,v,w);
                if(re==OK)
                    printf("弧成功插入!\n");
                else
                    printf("弧插入失败!\n");
            }
            q = head;
            printf("请输入任意键继续\n");
            getchar();
            getchar();
            break;
        case 10:
            printf("请输入图的id:\n");
            scanf("%d", &id);
            while (q != NULL && q->id != id)
                q = q->next;
            if (q == NULL)
                printf("图不存在！\n");
            else
            {
                int v,w,re;
                printf("请输入需要删除的弧的信息:(a,b)\n");
                scanf("%d %d",&v,&w);
                re=DeleteArc(q,v,w);
                if(re==OK)
                    printf("弧成功删除!\n");
                else
                    printf("弧删除失败!\n");
            }
            q = head;
            printf("请输入任意键继续\n");
            getchar();
            getchar();
            break;
        case 11:
            printf("请输入图的id:\n");
            scanf("%d", &id);
            while (q != NULL && q->id != id)
                q = q->next;
            if (q == NULL)
                printf("图不存在！\n");
            else
            {
                DFSTraverse(q);
            }
            q = head;
            printf("\n请输入任意键继续\n");
            getchar();
            getchar();
            break;
        case 12:
            printf("请输入图的id:\n");
            scanf("%d", &id);
            while (q != NULL && q->id != id)
                q = q->next;
            if (q == NULL)
                printf("图不存在！\n");
            else
            {
                BFSTraverse(q);
            }
            q = head;
            printf("\n请输入任意键继续\n");
            getchar();
            getchar();
            break;
        case 13:
            printf("请输入图的id:\n");
            scanf("%d", &id);
            while (q != NULL && q->id != id)
                q = q->next;
            if (q == NULL)
                printf("图不存在！\n");
            else
            {
                SaveGraph(q);
            }
            q = head;
            printf("\n请输入任意键继续\n");
            getchar();
            getchar();
            break;
        case 14:
             printf("请输入图的id:\n");
            scanf("%d", &id);
            while (q != NULL && q->id != id)
                q = q->next;
            if (q == NULL)
                printf("图不存在！\n");
            else
            {
                LoadGraph(q);
            }
            q = head;
            printf("\n请输入任意键继续\n");
            getchar();
            getchar();
            break;
        case 15:
           
            printf("请输入任意键继续\n");
            getchar();
            getchar();
            break;
        case 16:
            
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

status CreateGraph(char value[],int arcnode[],int vnum,int arcnum,Graph *a){
    if(a==NULL)
        return ERROR;
    int i;
    ArcNode *p=NULL;
    a->vernum=vnum;
    a->arcnum=arcnum;
    for(i=0;i<a->vernum;i++){
        (a->elem+i)->data=value[i];
        (a->elem+i)->firstArc=NULL;
        (a->elem+i)->key=i+1;
    }
    for(i=0;i<a->arcnum*2;i++){
        p=(struct ArcNode *)malloc(sizeof(ArcNode));
        p->next=a->elem[arcnode[i]-1].firstArc;
        a->elem[arcnode[i]-1].firstArc=p;
        p->rad=arcnode[++i];
    }
    return OK;
}

status DestroyGraph(Graph *a){
     if (a->pre != NULL)   //删除存储树的表头
        a->pre->next = a->next;
    if (a->next != NULL)
        a->next->pre = a->pre;
    printf("图%s删除成功！\n",a->name);
    free(a);
    a = NULL;
    return OK;
}

Vertex *LocateVex(Graph *a,int key){
    int i;
    for(i=0;i<a->vernum;i++)
    {
        if(key==(a->elem+i)->key)
            return (a->elem+i);
    }
    return NULL;
}

status PutVex (Graph *a,int key,char value){
    Vertex *p=NULL;
    p=LocateVex(a,key);
    if(p==NULL)
        return ERROR;
    p->data=value;
    return OK;
}

Vertex *FirstAdjVex(Graph *a,int key){
    Vertex *p=NULL,*q=NULL;
    p=LocateVex(a,key);
    if(p==NULL)
        return NULL;
    if(p->firstArc==NULL)
        return NULL;
    else{
        q=LocateVex(a,p->firstArc->rad);
        return q;
    }   
}

Vertex *NextAdjVex(Graph *a,int v,int w){
    Vertex *p=LocateVex(a,v);
    if(p==NULL)
        return NULL;
    ArcNode *q=p->firstArc;
    while(q!=NULL){
        if(q->rad==w){
            if(q->next==NULL)
                return NULL;
            else
                return LocateVex(a,q->next->rad);
        }
        else
            q=q->next;
    }
    if(q==NULL)
        return NULL;
}

status InsertVex(Graph *a,char v){
    if(a->vernum>=MAXVERTEXNUM)
        return ERROR;
    a->elem[a->vernum].data=v;
    a->elem[a->vernum].firstArc=NULL;
    a->elem[a->vernum].key=a->elem[a->vernum-1].key+1;
    a->vernum++;
    return OK;
}

status DeleteVex(Graph *a,int v){
    int i;
    for(i=1;i<=a->vernum;i++){
        DeleteArc(a,v,i);
        DeleteArc(a,i,v);
    }
    Vertex *p=NULL;
    p=LocateVex(a,v);
    if(p==NULL)
        return ERROR;
    while(a->elem[a->vernum].key!=p->key){
        p->data=(p+1)->data;
        p->key=(p+1)->key;
        p->firstArc=(p+1)->firstArc;
        p=p+1;
    }
    a->vernum--;
    return OK;
}

status InsertArc(Graph *a,int v,int w){
    Vertex *q=LocateVex(a,v);
    if(q==NULL)
        return ERROR;
    ArcNode *p=q->firstArc;
    while(p!=NULL){
        if(p->rad==w)
            return ERROR;
        p=p->next;
    }
    p=(ArcNode *)malloc(sizeof(ArcNode));
    p->rad=w;
    p->next=q->firstArc;
    q->firstArc=p;
    a->arcnum++;
    return OK;
}

status DeleteArc(Graph *a,int v,int w){
    Vertex *q=LocateVex(a,v);
    if(q==NULL)
        return ERROR;
    else{
        ArcNode *p=q->firstArc,*ql=NULL;
        if(p==NULL)
            return OK;
        if(p->rad==w){
            q->firstArc=p->next;
            free(p);
            a->arcnum--;
            p=NULL;
            return OK;
        }
        while(p->next!=NULL){
            if(p->next->rad==w)
                break;
            p=p->next;
        }
        if(p->next==NULL)
            return OK;
        if(p->next->rad==w){
            ql=p->next;
            p->next=ql->next;
            free(ql);
            a->arcnum--;
            ql=NULL;
        }
        return OK;
    }
}

status DFSTraverse(Graph* a)
{
    int v=0;
    for(v=0;v<a->vernum;v++)
        visit[v]=0;
    for(v=0;v<a->vernum;v++){
        if(!visit[v])
            DFS(a,v);
    }
    return OK;
}

void DFS(Graph *a,int v){
    visit[v]=1;
    printf("%c ",a->elem[v].data);
    int w=0;
    ArcNode *p=a->elem[v].firstArc;
    while(p!=NULL){
        Vertex *q=NULL;
        q=LocateVex(a,p->rad);
        for(w=0;w<a->vernum;w++){
            if(a->elem[w].key==q->key)
                break;
        }
        if(!visit[w])
            DFS(a,w);
        p=p->next;
    }
}


status BFSTraverse(Graph* a)
{
	int v=0,w;
    for(v=0;v<a->vernum;v++)
        visit[v]=0;;
    Vertex *queue[20],*pt=NULL,*front=queue,*back=queue;
    for(v=0;v<a->vernum;v++){
        if(!visit[v]){
            *back=a->elem[v];
            back++;
            while(front!=back){
                ArcNode *q=front->firstArc;
                for(w=0;w<a->vernum;w++){
                    if(a->elem[w].key==front->key)
                    break;
                }
                if(!visit[w])
                    printf("%c ",front->data);
                visit[w]=1;
                front++;
                while(q!=NULL){
                    *back=*LocateVex(a,q->rad);
                    back++;
                    q=q->next;
                }
            }
        }
    }
    return OK;
}

status SaveGraph(Graph *a)
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
    fwrite(&a->vernum, sizeof(ElemType), 1, fp);
    fwrite(&a->arcnum, sizeof(ElemType), 1, fp);
    int i;
    for(i=0;i<a->vernum;i++)
    {
        fwrite(&(a->elem[i].data),sizeof(char),1,fp);
        fwrite(&(a->elem[i].key),sizeof(int),1,fp);
    }  
    for(i=0;i<a->arcnum;i++){
        ArcNode *p=a->elem[i].firstArc;
        while(p!=NULL)
        {
            fwrite(&(a->elem[i].key),sizeof(int),1,fp);
            fwrite(&(p->rad),sizeof(int),1,fp);
            p=p->next;
        }
    }
    fclose(fp);
    printf("文件成功保存!\n");
    return OK;
}

status LoadGraph(Graph *a){
    FILE *fp;
    char filename[30];
    printf("input file name: ");
    scanf("%s", filename);
    if ((fp = fopen(filename, "rb")) == NULL)
    {
        printf("File open error\n ");
        return ERROR;
    }
    int i,vnum,anum;
    fread(&(a->vernum), sizeof(int), 1, fp);
    fread(&(a->arcnum), sizeof(int), 1, fp);
    if(a==NULL)
        return ERROR;
    ArcNode *p=NULL;
    for(i=0;i<a->vernum;i++){
        fread(&((a->elem+i)->data), sizeof(char), 1, fp);
        fread(&((a->elem+i)->key), sizeof(int), 1, fp);
        (a->elem+i)->firstArc=NULL;
    }
    int b[100];
    for(i=0;i<a->arcnum*2;i++){
        fread(&b[i],sizeof(int),1,fp);
    }
    for(i=0;i<a->arcnum*2;i++){
        p=(struct ArcNode *)malloc(sizeof(ArcNode));
        p->next=LocateVex(a,b[i])->firstArc;
        LocateVex(a,b[i])->firstArc=p;
        p->rad=b[++i];
    }
    fclose(fp);
    return OK;
}