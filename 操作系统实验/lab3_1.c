#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

#define SHMKEY 10
#define SEMKEY 100

int shmkey,i=0;
int shmid[10]; //用来记录缓冲区块号
int sid;        //用来记录信号灯的顺序

int main(){
    pid_t p1 ,p2;
    sid = semget((key_t)SEMKEY, 3, IPC_CREAT | 0666); //创建两个信号灯
    if (sid == -1)                                    //创建失败
        return -1;
    semctl(sid,0,SETVAL,0); //同步信号灯，表示产品的数量
    semctl(sid,1,SETVAL,1); //互斥信号灯
    semctl(sid,2,SETVAL,10); //同步信号灯表示空闲缓冲区的数量
    for (i = 0; i < 10; i++)     //创建十个共享内存
    {
        shmid[i] = shmget((key_t)(SHMKEY + i), 1024, 0666 | IPC_CREAT);
    }
    for (i = 10; i < 20; i++)    //获取共享内存组
    {
        shmid[i] = shmget((key_t)(SHMKEY + i), sizeof(int), 0666 | IPC_CREAT);
    }
    if ( (p1=fork()) == 0) //创建读进程
    {
        puts("Create readthread!\n");
        execv("./lab3_2", NULL); //执行读进程
    }
    else
    { 
        if ( (p2=fork())  == 0) //创建写进程
        {
            puts("Create writethread!\n");
            execv("./lab3_3", NULL); //执行写进程
        }
    }
    wait(&p1); //等待进程执行完
    wait(&p2);
    semctl(sid, 0, IPC_RMID);
    for (i = 0; i < 20; i++) //撤销共享缓存区
    {
        shmctl(shmid[i], IPC_RMID, 0);
    }
    return 0;
}