#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdbool.h>
#include<time.h>
#include<string.h>
#define NUM_SPECS 7
#define SIZE_ARRAY 100000000ULL
#define NUM_DES 4
#define NUM_PRO 4
#define FILE_SIZE 10ULL*1024ULL*1024ULL*1024ULL

char* spec[NUM_SPECS]={"Computer Science and Engineering,","Electrical and Electronic Engineering,","Electronic and Communication Engineering,","Mechanical Engineering,","Civil Engineering,","Metallurgical Engineering,","Chemical Engineering,"};

char * des[NUM_DES]={"PROFESSOR,","ASSISTANT-PROFESSOR,","TEACHING-ASSISTANT,","LECTURER,"};

char* pro[NUM_PRO]={"Machine Learning\n","Operating System\n","DataBase Management System\n","Application\n"};

unsigned long long  arr[SIZE_ARRAY];

int new_file;

void initialise()
{
unsigned long long i=0,j=SIZE_ARRAY-1,temp;
	for(i=0;i<SIZE_ARRAY;i++)
	{
		arr[i]=i+1;
	}

	for(i=SIZE_ARRAY-1;i>=1;i--)
	{
		j=rand()%(i+1);
		temp=arr[j];
		arr[j]=arr[i];
		arr[i]=temp;
		

	}

	new_file=creat("file1.csv",0644);
	
}


unsigned long long file_size=0;

void write_name(int fd,char* buf)
{

	char ch;
	buf[0]='\0';
	int i=0;
	ssize_t len;
	while (len!=0)
	{
		len=read(fd,&ch,1);
		if(len==-1)
		{
		perror("read");
		exit(0);
		}

		if(ch=='\0' ||ch=='\n' || ch==EOF)
		{
			
			buf[i-1]=',';
			//printf("%s\n",buf);
			write(new_file,buf,i);
			file_size+=i;
			return;
		}
		else
		{
			buf[i++]=ch;

		}
	
	}
	return;


}

unsigned long long a=0,b=0;
void  write_roll()
{

	
	b=arr[a];
	a++;

	int k;
	char buf[11];
	for( k=0;k<11;k++)
	buf[k]='0';
	
	buf[10]=',';
	k=0;
	char* temp=buf+9;
	while(b)
	{
	*temp=b%10+'0';
	b=b/10;
	k++;
	temp--;
	}
	write(new_file,temp+1,k+1);


	

}

void write_spec()
{
	char* s=spec[ rand()%NUM_SPECS];
	write(new_file,s,strlen(s));
	file_size+=strlen(s);

}

void write_pro()
{

	char* p=pro[rand()%NUM_PRO];
	write(new_file,p,strlen(p));
	file_size+=strlen(p);
}
int write_des()
{
	return rand()%NUM_DES;
}


int main()

{
	srand(time(NULL));
	initialise();

	int fd=open("names.csv",O_RDONLY|O_SYNC);
	if(fd==-1)
	{
	perror("open");
	exit(0);
	}
	char buf[100];
	char * roll;
	char comma=',';
	char newline='\n';
	unsigned long long  i=1;
	//char* name=get_name(fd);
	while(1)
	{
		write_roll();
		write_name(fd,buf);
		write_spec();
		write_pro();
		if(file_size> FILE_SIZE)
		break;
		
		if(buf[0]==NULL)
		{
		lseek(fd,0,SEEK_SET);
		}

	}
	
	close(fd);
	close(new_file);

return 0;

}
