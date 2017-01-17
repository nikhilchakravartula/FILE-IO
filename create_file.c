#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
	//*int fd=open("new_file.txt",O_WRONLY|O_TRUNC|O_CREAT,0600);
	int fd=creat("new_file.txt",0644);
	if(fd==-1)
	{
		perror("opening");
		exit(0);
	}



	return 0;
}
