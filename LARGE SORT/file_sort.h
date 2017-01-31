#ifndef __FILE_SORT_H__
#define __FILE_SORT_H__

#include<string.h>
#include<dirent.h>
#include<sys/stat.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include "heap.h"
unsigned long long file_no=0,sorted_file_no=0;
int cur_run_size=0;
int new_file;

#define RUN_SIZE 16*1024


heap_node* read_heap_node(int);

void sort_individual_file(int fd)
{
	char sorted_file_name[1000];
	char path[1000];
	getcwd(path,1000);
	strcat(path,"/sorted/");
	DIR* dir=opendir(path);
	if(dir==NULL)
	{

		if(-1==(mkdir(path,S_IRWXU | S_IRWXG | S_IRWXO))){perror("sorted directory error\n");exit(0);}


	}
	sprintf(sorted_file_name,"%ssorted%llu.csv",path,sorted_file_no);
	int sorted_new_file=creat(sorted_file_name,0644);
	if(sorted_new_file==-1)
	{
		printf("file no is %llu\n",sorted_file_no);
		perror("creation of sorted files\n");
		exit(0);

	}


	heap_node heap[300];
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
	//heap_print(heap);
	while(!heap_empty())
	{
		heap_node t=pop_min(heap);
		if( -1==(write(sorted_new_file,t.str,strlen(t.str))))
		{perror("write error sorted file\n");exit(0);}
	//	printf("%llu\n",t.data);

	}
	sorted_file_no+=1;
//	printf("sorted file %llu\n",sorted_file_no-1);
	close(sorted_new_file);
//	realloc(heap,0);
//	free(heap);
//	printf("returning\n");

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
		temp->fd=fd;
	//	printf("%llu %s\n",temp->data,temp->str);
		return temp;
	}
	temp->str[k]=ch;
	k++;
	

}

return NULL;

}

void merge_files()
{
	
	DIR* dir;
	unsigned long long level=0;
	struct dirent* entry;
	char path[1000];
	getcwd(path,1000);
	strcat(path,"/sorted/");
	dir=opendir(path);
	char level_path[1000];
	int i;
	if(dir==NULL){
	perror("already sorted files not found\n");exit(0);}
	char sorted_file_name[1000];
	char trash_file_name[1000];
	int sorted_new_file;
	heap_node* temp;
	int count=0;
	sprintf(trash_file_name,"%s%s",path,"trash/");
	mkdir(trash_file_name,S_IRWXU | S_IRWXG | S_IRWXO);

	while(1)
	{
	count=0;
	  heap_node heap[MAX_FD];
	  int sorted_fds[MAX_FD];

	for(i=0;i<MAX_FD;)
	{
//		printf("here\n");
		entry=readdir(dir);
		//printf("read dir after\n");
		if(entry==NULL)
			break;

		if(strcmp(entry->d_name,"trash")!=0 && strcmp(entry->d_name, ".")!=0 && strcmp(entry->d_name, "..")!=0)
		{
		i++;
		count+=1;
//		printf("inside if\n");
//		printf("%s\n",entry->d_name);
		sprintf(sorted_file_name,"%s%s",path,entry->d_name);

		sorted_fds[i]=open(sorted_file_name,O_RDWR);

//		printf("After sorted fd count\n");
		
		sprintf(trash_file_name,"%s%s%s",path,"trash/",entry->d_name);
//		printf("%s %s\n",sorted_file_name,trash_file_name);
		rename(sorted_file_name,trash_file_name);
//		printf("After rename\n");
		 temp=read_heap_node(sorted_fds[i]);

		if(temp!=NULL)
		heap_insert(heap,temp);

		
		}

	}

//	printf("After loop count= %d\n",count);
	if(entry==NULL)
	{
	printf("in null\n");
		if(count==1){
			printf("done sorting\n");return;}
	dir=opendir(path);


	}

	sprintf(sorted_file_name,"%ssorted%llu.csv",path,level);
//	printf("sorted file name %s\n",sorted_file_name);
	sorted_new_file=creat(sorted_file_name,0644);
	if(sorted_new_file==-1)
	{
		perror("error creating file in merge files\n");
		exit(0);

	}
	while(!heap_empty(heap))
	{
		 heap_node t=pop_min(heap);
//		 printf("heap %s\n",t.str);
	 if( -1==(write(sorted_new_file,t.str,strlen(t.str))))
	 {
		perror("write error level sorted file\n");
				exit(0);
	 }
	 temp=read_heap_node(t.fd);
	 if(temp!=NULL)
	 	heap_insert(heap,temp);
	 
	
	}
//	printf("out loop and closing loop\n");
	close(sorted_new_file);
//	printf("closed\n");
	for(int j=0;j<i;j++)
	{
		//printf("closing file %d i=%d \n",j,i);
		close(sorted_fds[j]);
	}
	sprintf(trash_file_name,"%s%s",path,"trash/");
	
	DIR* trash_dir=opendir(trash_file_name);
	struct dirent* trash_entry;
	while( (trash_entry=readdir(trash_dir))!=NULL)
		{
			if( strcmp(trash_entry->d_name,".")!=0 && strcmp(trash_entry->d_name,"..")!=0)
			{

		strcat(trash_file_name,trash_entry->d_name);	
unlink(trash_file_name);
			}
		}


	}

}

void sort(int fd)
{
	struct dirent* entry;
	char path[1000];
	getcwd(path,1000);
	printf("%s\n",path);
	strcat(path,"/temp_files/");
	DIR* dir=opendir(path);
	char temp_path[strlen(path)+20],file_name[1000],buf[RUN_SIZE],temp[10000];
	int k=0;
	cur_run_size=0;
	ssize_t len;
	unsigned long long val=0;
	
	if(dir==NULL)
	{
//		printf("here\n");
		if(-1==(mkdir(path,0666))){perror("error creating directory\n");exit(0);}
		
	
	while(1)
	{
//	printf("in whille\n");

		sprintf(file_name,"%stemp%llu.csv",path,file_no);
		new_file=creat(file_name,S_IRWXU | S_IRWXG | S_IRWXO);
	if(new_file==-1)
	{
		printf("file no is %llu\n",file_no);
		perror("creation of temp files\n");
		exit(0);

	}

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

	close(new_file);
	 file_no+=1;
	 }

	}
	
	
	dir=opendir(path);
	 while((entry=readdir(dir))!=NULL ){
//	printf("%s\n",entry->d_name);
		if( (strncmp(entry->d_name,"temp",4))==0){
	 	sprintf(file_name,"%s%s",path,entry->d_name);
	 	new_file=open(file_name,O_RDWR);
		if(new_file==-1)
			{printf("%s\n",file_name);perror("cant open frpm dirent\n");}
		sort_individual_file(new_file);
		close(new_file);
//		printf("before unlink\n");
		if(-1== (remove(file_name)))
		{
			printf("%s\n",file_name);
			perror("error unlinking file");
			exit(0);
		}
//		printf("After unlink\n");
		
	
		}
		}
	//	printf("befoire closedir\n");
		closedir(dir);
	//	delete[] temp_files;
		
	printf("sorting individual files completed\n\n");
	
	merge_files();
	
/*	for(unsigned long long i=0;i<file_no;i++)
		lseek(temp_files[i],0,SEEK_SET);

	heap_node* heap=malloc(sizeof(heap_node)*file_no);

	for(unsigned long long i=0;i<file_no;i++)
	{
		heap_insert(heap,read_heap_node(temp_files[i]));

	}

*/	
}

#endif
