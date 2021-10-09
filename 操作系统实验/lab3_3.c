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
int shmid[20];
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
void writebuf()
{
    int fp = open("./output", O_WRONLY | O_CREAT);
    int j=0;
    while(1)
    {
        P(sid, 0);  //消耗一次写入次数
        P(sid, 1);  //互斥信号灯
        if(write(fp, addr[j], *(length[j])) <1024){       //从缓存区取出一个产品
            V(sid,1);
            break;
        }
        V(sid,1);
        V(sid,2);   //增加一个空闲缓存区
        printf("write!\n");
        if (j == 9)     //写入环路满了
            j = 0;
        else
            j++;
    }
    puts("write over!");
    close(fp);
    return;
}
int main()
{
    int i = 0;
    puts("writethread begin!"); //写进程进入
    for (i = 0; i < 10; i++)    //获取共享内存组
    {
        shmid[i] = shmget((key_t)(SHMKEY + i), 1024, 0666 | IPC_CREAT);
        addr[i] = shmat(shmid[i], 0, 0); //建立数组环形缓冲
    }
    for (i = 10; i < 20; i++)    //获取共享内存组
    {
        shmid[i] = shmget((key_t)(SHMKEY + i), sizeof(int), 0666 | IPC_CREAT);
        length[i-10] = shmat(shmid[i], 0, 0); //建立数组环形缓冲
    }
    sid = semget((key_t)SEMKEY, 3, 0666); //获取共享信号灯
    writebuf();
    for (i = 0; i < 20; i++) //撤销共享缓存区
    {
        shmdt(addr[i]);
    }
    return 0;
}