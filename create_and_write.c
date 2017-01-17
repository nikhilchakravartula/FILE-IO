#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
int main()
{

	int fd=creat("openwriteutil.txt",0644);
	if(fd==-1)
	{
		perror("open");
		exit(0);
	}
	ssize_t len=write(fd,"ABCDEFGHIJKLMNOPQRSTUVWXYZ",26);
	if(len==-1)
	{
		perror("write");
		exit(0);
	}
	

	return 0;
}
