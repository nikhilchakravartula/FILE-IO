#include<stdio.h>
#include<stdlib.h>
int main()
{
	FILE* fp=fopen("bufferedioutil.txt","w+");
	if(!fp)
	{
		fprintf(stderr,"cant open file");
		exit(0);
	}
	char buf[]="first line of the file";
	fputs(buf,fp);

	char buf1[100];
	rewind(fp);
	 if(fgets(buf1,99,fp))
	 {
		printf("%s",buf1);

	 }
	 else

	 {
		fprintf(stderr,"error while reading");
		exit(0);

	 }
fclose(fp);	

return 0;
}
