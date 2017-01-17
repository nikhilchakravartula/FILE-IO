#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
int main()
{
	int fd=open("sample.txt",O_RDONLY);
	if(fd==-1)
	{
		perror("open");
		exit(0);
	}
	char buf1[1024];
	ssize_t len;
	while( (len=read(fd,buf1,1024))!=0)
	{

		if(len==-1)
		{
			perror("read");
			exit(0);
		}
		printf("%s",buf1);
	}

return 0;
}
