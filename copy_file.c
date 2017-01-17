#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{

int fd=creat("sample1.txt",O_WRONLY);
if(fd==-1)
{
perror("Cannot create output file");
exit(0);

}
	
	int fd1=open("sample.txt",O_RDONLY);
	if(fd1==-1)
	{

	perror("cannot open input file");
	exit(0);
	}

	char buf[1024];
	ssize_t len1,len2;
	off_t file_size=lseek(fd1,0,SEEK_END);
	if(file_size==-1)
	{
		perror("seek");
		exit(0);
	}
	if(-1==lseek(fd1,0,SEEK_SET))
	{
		perror("lseek");
		exit(0);
	}

	while( (len1=read(fd1,buf,file_size))!=0)
	{
		if(len1==-1)
		{
				perror("read");
				exit(0);
		}
		printf("length is %d\n",len1);
		buf[len1]='\0';
		len2=write(fd,buf,len1);
		if(len2==-1)
		{
			perror("write");
			exit(0);
		}

	}
	printf("DONE SUCCESSFULLY");
return 0;
}
