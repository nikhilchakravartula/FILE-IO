#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include "heap.h"
int file_no=0;
int cur_run_size=0;
int new_file;
#define RUN_SIZE 8*1024
void sort(int fd)
{
	char buf[16384];
	cur_run_size=0;
	char temp[1000];
	int k=0;
	ssize_t len;
	char file_name[1000000];
	unsigned long long val=0;
	int temp_files[10000000ULL];
	while(1)
	{



	sprintf(file_name,"temp%d.csv",file_no);
	
	
	new_file=open(file_name,O_CREAT|O_TRUNC|O_RDWR);

	temp_files[file_no]=new_file;

	cur_run_size=0;

	 	len=read(fd,buf,RUN_SIZE);

	
		if(len==0)
		break;

		
		if( len==-1)
		{
			
			perror("read");
			exit(0);
		}

		for(int i=0; i<len;i++)
		{
			if(buf[i]=='\n')
			{
				temp[k]='\n';
				write(new_file,temp,k+1);
				k=0;
			}
			else
			{
				temp[k++]=buf[i];


			}

		}

	 file_no+=1;
	 }

	heap_node* heap=malloc(sizeof(heap_node)*file_no);
}
