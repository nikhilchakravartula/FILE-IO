#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<fcntl.h>

int main()
{
	int fd=open("sample.txt",O_RDONLY);
	if(fd==-1)
	{
		perror("open");
		exit(0);
	}
	off_t off=lseek(fd,0,SEEK_END);
	if(off==-1)
	{
		perror("seek");
		exit(0);
	}
	printf("size is %d",off);
	return 0;
	return 0;
}
