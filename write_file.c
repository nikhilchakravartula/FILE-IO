#include<stdio.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#define MAXLEN 1024
#include<stdlib.h>
int main()
{
	off_t off;
	ssize_t len;
	char buf[]="\nWRITING AT END.THIS IS NEWLY WRITTEN LINE\n";
	int fd=open("writeutil.txt",O_WRONLY);
	if(fd==-1)
	{
		printf("ERROR OPENING\n");
		perror("open");

	}

	/*len=write(fd,buf,sizeof(buf));
	if(len==-1)
	{
		perror("write\n");
		exit(0);
	}
	printf("Written to the file");*/
	off=lseek(fd,0,SEEK_END);
	if(off==-1)
	{
		printf("SEEK ERROR");
		perror("seek");
	}
	len=write(fd,buf,sizeof(buf));
	if(len==-1)
	{
		printf("cant write");
		perror("Write");

	}
	printf("written to end of the file\n");

	return 0;
}
