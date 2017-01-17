#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<fcntl.h>
#include<error.h>
int main()
{
	ssize_t ret;
	size_t len;
	char ch;
	int fd=open("sample.txt",O_RDONLY);
	if(fd==-1)
	{
		perror("open");
		exit(0);
	}

	while( (ret=read(fd,&ch,1)) !=0)
	{
		if(ret==-1)
		{
			perror("read");

		}
		if(ch=='i')
		{
			printf("i\n");
		}

	}



	return 0;
}
