#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define SHMKEY 10
#define SEMKEY 100


int shmid[20];  //共享内存存储标识符
int sid = 0;    
char *addr[10];
int *length[10];



void P(int semid, int index)
{
    struct sembuf sem;
    sem.sem_num = index;
    sem.sem_op = -1;
    sem.sem_flg = 0;
    semop(semid, &sem, 1);
    return;
}
void V(int semid, int index)
{
    struct sembuf sem;
    sem.sem_num = index;
    sem.sem_op = 1;
    sem.sem_flg = 0;
    semop(semid, &sem, 1);
    return;
}
void readbuf()
{
    int j = 0;
    int fp = open("./input", O_RDONLY);
    if(fp==-1){
        printf("open error!\n");
        return;
    }
    printf("read begin!\n");
    while(1)
    {   
        P(sid,2);       //消耗一个空闲缓冲区
        printf("read!\n");
        P(sid, 1);      //互斥信号灯
        *(length[j])=read(fp, addr[j], 1024);
        if(*(length[j]) <= 0){      //把产品放入缓存区
            V(sid,1);
            break;
        }
        V(sid,1);
        V(sid,0);   //增加一个产品
        if (j == 9)     //读取环路结束，缓冲区已经满了
            j = 0;
        else
            j++;
    }
    printf("read over!\n");
    close(fp);
    return;
}
int main()
{
    int i;
    printf("readthread begin!\n");
    for (i = 0; i < 10; i++)    //获取共享内存组
    {
        shmid[i] = shmget((key_t)(SHMKEY + i), 1024, 0666 | IPC_CREAT);
        addr[i] = shmat(shmid[i], 0, 0);    //建立数组环形缓冲
    }
    for (i = 10; i < 20; i++)    //获取共享内存组
    {
        shmid[i] = shmget((key_t)(SHMKEY + i), sizeof(int), 0666 | IPC_CREAT);
        length[i-10] = shmat(shmid[i], 0, 0); 
    }
    sid = semget((key_t)SEMKEY, 3, 0666);   //获取信号灯
    readbuf();
    for (i = 0; i < 20; i++)
    {
        shmdt(addr[i]);
    }
    return 0;
}