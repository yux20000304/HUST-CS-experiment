#include<stdio.h>
#include<linux/kernel.h>
#include<sys/syscall.h>
#include<unistd.h>

int main(int argc,char *argv[]){
  long int ret=syscall(335,argv[1],argv[2]);
  printf("%ld\n",ret); 
  return 0;
}
