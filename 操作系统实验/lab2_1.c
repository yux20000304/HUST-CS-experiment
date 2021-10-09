#include <linux/sem.h> 
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int light;  //信号量
int count=0;  //共享变量
pthread_t thread1,thread2,thread3;  //线程号

void P(int semid, int index)
{	   
	struct sembuf sem;	
	sem.sem_num = index;
	sem.sem_op = -1;	
	sem.sem_flg = 0; 
	semop(semid,&sem,1);		
	return;
}

void V(int semid,int index)
{	
	struct sembuf sem;	
	sem.sem_num = index;
	sem.sem_op =  1;
	sem.sem_flg = 0;	
	semop(semid,&sem,1);	
	return;
}

void buy1(){
    int i=0;
    while(count<100){
        P(light,0);
        count++;
        i++;
        V(light,0);
        usleep(20);
    }
    printf("buyer1 has bought %d pieces\n",i);
    return ;
}

void buy2(){
    int i=0;
    while(count<100){
        P(light,0);
        count++;
        i++;
        V(light,0);
        usleep(20);
    }
    printf("buyer2 has bought %d pieces\n",i);
    return ;
}

void buy3(){
    int i=0;
    while(count<100){
        P(light,0);
        count++;
        i++;
        V(light,0);
        usleep(20);
    }
    printf("buyer3 has bought %d pieces\n",i);
    return ;
}

int main(){
    light=semget(IPC_PRIVATE,1,IPC_CREAT|0666);
    semctl(light,0,SETVAL,1);   //互斥信号灯
    pthread_create(&thread1, NULL, buy1, NULL);
    pthread_create(&thread2, NULL, buy2, NULL);
    pthread_create(&thread3, NULL, buy3, NULL);   //创建三个线程
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    pthread_join(thread3,NULL);
    return 0;
}
