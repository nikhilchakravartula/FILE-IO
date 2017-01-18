#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<errno.h>
#include<error.h>
int main()
{
	int fd=creat("blockutil.txt",0644);
	if(fd==-1)
	{
		perror("read");
		exit(0);
	}
	int cl=close(fd);
	if(cl==-1)
	{
		perror("close");
		exit(0);

	}
	fd=open("blockutil.txt",O_RDONLY);
	if(fd==-1)
	{
		perror("read");
		exit(0);
	}
	char buf[1024];
	ssize_t len=read(fd,buf,1024);
	printf("length is %d",len);
	start:
	if(len==-1)
	{
		if(errno==EINTR)
		{
			goto start;
		}
		if(errno==EAGAIN)
		{
			goto start;
		}
		
		perror("read");
		//if(errno==EINTR)
		exit(0);

	}



}
