#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>

struct my_data_struct
{
	int a;
	double d;


};
int main()
{
	FILE* fp=fopen("binaryfile","w+");
	if(fp==NULL)
	{
	perror("open");
	exit(0);
	}
	
	struct my_data_struct s={5,5.6};
	fwrite(&s,sizeof(struct my_data_struct),1,fp);
	rewind(fp);
	fread(&s,sizeof(struct my_data_struct),1,fp);

	printf("read! %d %f",s.a,s.d);
	return 0;

}
