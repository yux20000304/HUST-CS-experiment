#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
 
# define BUFFER_LEN 4096
# define COPYMODE 0664
 
void copy(int fdin, int fdout)
{
	char buffer[BUFFER_LEN];
	ssize_t size;
	while(size = read(fdin, buffer, BUFFER_LEN)){
		if(write(fdout,buffer,size)!=size){
			perror("write error");
			exit(1);
		}
	}
	
	if(size<0){
		perror("read error");
  		exit(1);
	}
 
}
 
 
 
int main(int argc, char *argv[])
{
	int fd_in = STDIN_FILENO;
	int fd_out = STDOUT_FILENO;
	if(argc!=3){
		printf("argc error\n");
		exit(1);
	}
	if((fd_in = open(argv[1],O_RDONLY))==-1){
		perror("open error");
		exit(1);
	}
	if((fd_out = creat(argv[2],COPYMODE))==-1){
		perror("open error");
		exit(1);
	}
 
	copy(fd_in,fd_out);	
	return 0;
 
}

