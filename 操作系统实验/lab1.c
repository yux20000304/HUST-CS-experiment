#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define N 20
pid_t pid1, pid2; //代表两个进程
int i;

void signalhandler(int sigNum)
{
    if (SIGUSR1 == sigNum)
    {
        printf("Child process 1 is killed by parent\n");
        exit(0);
    }
    if (SIGUSR2 == sigNum)
    {
        printf("Child process 2 is killed by parent\n");
        exit(0);
    }
    if (SIGINT == sigNum)
    {                        //收到软中断信号，发送sigusr1和sigusr2
        kill(pid1, SIGUSR1); //终止进程一
        kill(pid2, SIGUSR2); //终止进程二
        i = N;
        return;
    }
}

int main()
{
    int count1 = 1, count2 = 1; //记录发送次数，初始值为1
    int pipefd[2];              //pipe[0]只用于读，pipe1[1]只能用于写
    char sendbuf[100];          //用来记录父进程发送的消息
    char readbuf[100];          //用来记录从管道中读取的信息
    pipe(pipefd);               //创建无名管道
    signal(SIGINT, signalhandler);
    pid1 = fork(); //创建子进程1
    if (pid1 == 0)
    { //进程一
        signal(SIGUSR1, signalhandler);
        signal(SIGINT, SIG_IGN);
        while (1)
        {
            sleep(1);
            read(pipefd[0], readbuf, sizeof(readbuf));
            printf("process 1 %d times receive:%s", count1, readbuf);
            count1++;
        }
    }
    pid2 = fork(); //创建子进程2
    if (pid2 == 0)
    { //进程二
        signal(SIGUSR2, signalhandler);
        signal(SIGINT, SIG_IGN);
        while (1)
        {
            sleep(1);
            read(pipefd[0], readbuf, sizeof(readbuf));
            printf("process 2 %d times receive:%s", count1, readbuf);
            count1++;
        }
    }
    for (i = 1; i < N; i++)
    {
        sprintf(sendbuf, "I send you %d times\n", i);
        write(pipefd[1], sendbuf, sizeof(sendbuf));
        sleep(1);
    }
    if (i == N)
    {
        kill(pid1, SIGUSR1); //终止进程一
        kill(pid2, SIGUSR2); //终止进程二
        printf("all the message has been sent\n");
        return 0;
    }
    wait(&pid1);
    wait(&pid2);
    close(pipefd[0]);
    close(pipefd[1]);
    printf("parent process is killed!\n");
    return 0;
}