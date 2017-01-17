#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#define MAXLEN 1024
int main(int argc,char** argv)
{	
	int cl;
	ssize_t len;
	char buf[MAXLEN];
	int fd=open("sample.txt",O_RDONLY);
	if(fd==-1)
	{
		printf("ERROR IN OPENING THE FILE");
		perror("OPEN ERROR");
		return 0;
	}
	len=read(fd,buf,MAXLEN);
	cl=close(fd);
	if(cl==-1)
	{

		perror("close");
	}
	if(len==-1)
	{
		printf("ERROR IN READING");
		perror("read");
		return 0;
	}
	buf[len]='\0';
	printf("CONTENTS READ ARE\t%s",buf);
	return 0;

	
}
