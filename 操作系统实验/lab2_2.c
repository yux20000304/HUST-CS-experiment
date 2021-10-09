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

void compute(){
    int i;
    for(i=1;i<101;i++){
        P(light,2);
        count+=i;
        if(count%2==0)
            V(light,0);
        else
            V(light,1);
    }
    return;
    
}

void print1(){
    int k;
    for(k=1;k<101;k++){
        P(light,0);
        printf("process 1 print:%d\n",count);
        V(light,2);  
        if(count==5050)
            return;
    }
}

void print2(){
    int j;
    for(j=1;j<101;j++){
        P(light,1);
        printf("process 2 print:%d\n",count);
        V(light,2); 
        if(count==4851)
            return;
    }
}

int main(){
    light=semget(IPC_PRIVATE,3,IPC_CREAT|0666);
    semctl(light,0,SETVAL,0);   //同步信号灯
    semctl(light,1,SETVAL,0);   //同步信号灯
    semctl(light,2,SETVAL,1);   //同步信号灯
    pthread_create(&thread1, NULL, compute, NULL);
    pthread_create(&thread2, NULL, print1, NULL);
    pthread_create(&thread3, NULL, print2, NULL);   //创建三个线程
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    pthread_join(thread3,NULL);
    return 0;
}
