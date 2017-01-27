#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include "heap.h"
unsigned long long file_no=0;
int cur_run_size=0;
int new_file;
#define RUN_SIZE 16*1024


heap_node* read_heap_node(int);

void sort_individual_file(int fd)
{

	heap_node* heap=malloc(sizeof(heap_node)*300);
	ssize_t len;
	char ch;
	unsigned long long val=0;
	while(1)
	{
	heap_node* temp=read_heap_node(fd);
	if(temp==NULL)
	break;

	heap_insert(heap,temp);



	}

	while(!heap_empty())
	{
		heap_node t=pop_min(heap);
		printf("%llu\n",t.data);


	}




}


heap_node* read_heap_node(int fd)
{
ssize_t len;
bool flag=0;
heap_node* temp=malloc(sizeof(heap_node));
char ch;
int k=0;
unsigned long long val=0;
while(1)
{
	len=read(fd,&ch,1);
	if(len==0)
	break;
	if(flag==0)
	{
		if(ch==',')
		{
			flag=true;
		}
		else
		val=val*10ULL+(ch-'0');
	}
	if(ch=='\n'||ch==EOF)
	{
		temp->str[k]='\n';
		temp->str[k+1]='\0';
		temp->data=val;
		printf("%llu %s\n",temp->data,temp->str);
		return temp;
	}
	temp->str[k]=ch;
	k++;
	

}

return NULL;

}
void sort(int fd)
{

/*
	char buf[RUN_SIZE];
	int k=0;
	cur_run_size=0;
	char temp[10000];
	ssize_t len;
	char file_name[1000000];
	unsigned long long val=0;
	int* temp_files=malloc(sizeof(int)*10000000);
	while(1)
	{

	sprintf(file_name,"temp%llu.csv",file_no);
	
	
	new_file=creat(file_name,0644);
	if(new_file==-1)
	{
		printf("file no is %llu\n",file_no);
		perror("creation of temp files\n");
		exit(0);

	}

	temp_files[file_no]=new_file;

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

	close(temp_files[file_no]);
	 file_no+=1;
	 }
*/	 //for(unsigned long long i=0;i<file_no;i++){
	 	new_file=open("temp0.csv",O_RDWR);
		sort_individual_file(new_file);
	//	}
/*	for(unsigned long long i=0;i<file_no;i++)
		lseek(temp_files[i],0,SEEK_SET);

	heap_node* heap=malloc(sizeof(heap_node)*file_no);

	for(unsigned long long i=0;i<file_no;i++)
	{
		heap_insert(heap,read_heap_node(temp_files[i]));

	}

*/	
}
