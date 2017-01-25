#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
int main()
{
	FILE* fp=fopen("read_ints_util.txt","r");

	if(fp==NULL)
	{
		perror("open");
		exit(0);
	}
	printf("here\n");
	int i;
	while( 0 != (fscanf(fp,"%d",&i))  )
	{
		printf("%d",i);
		if(i==541)
		break;
		printf("\n");

	}

	return 0;
}
