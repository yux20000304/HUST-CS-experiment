#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>

#define MAX 128

FILE* f;
char s[MAX];
int ret;

void generate_progress(const char* command)
{
  f = popen(command, "r");
  if(f != NULL)
  {
    while((ret = fread(s,1,MAX,f)) > 0)
      fwrite(s,1,ret,stdout);
    pclose(f);
  }
  else
    printf("popen分配内存失败！\n");
  exit(0);
}

int main()
{
  pid_t p1, p2, p3;
  p1 = fork();
  if(p1 < 0)
  {
    printf("创建子进程1失败！\n");
    exit(1);
  }

  if(p1 == 0) // 子进程1
  {
    execv("./build-window1-Desktop_Qt_5_12_10_GCC_64bit-Debug/window1",NULL);
    exit(0);
  }
  p2 = fork();
  if(p2 < 0)
  {
    printf("创建子进程2失败！\n");
    exit(1);
  }

  if(p2 == 0) // 子进程2
  {
    execv("./build-Server-Desktop_Qt_5_12_10_GCC_64bit-Debug/Server",NULL);
    exit(0);
  }

  p3 = fork();
  if(p3 < 0)
  {
    printf("创建子进程3失败！\n");
    exit(1);
  }
  if(p3 == 0) // 子进程3
  {
    execv("./build-Client-Desktop_Qt_5_12_10_GCC_64bit-Debug/Client",NULL);
    exit(0);
  }
  waitpid(p1, NULL, 0);
  waitpid(p2, NULL, 0);
  waitpid(p3, NULL, 0);
  printf("Done.\n");
  return 0;
}
