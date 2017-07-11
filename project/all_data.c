#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define SIZE 1024
#define NAMESIZE 32
#define len 12
int main(int argc,char **argv)
{
	size_t n; 
	char *line=NULL;
	char *line1=NULL;
	char*line2=NULL;
	char**ptr=NULL;
	FILE *fp1,*fp2;
	char seg[]="- ";
	char *substr=NULL;
	char *charlist[len];
	
	fp1 =fopen(argv[1],"r+"); 
	if (fp1 ==NULL){
		perror("fopen()");
		return -1;
	}
	int i=0,j=0;
	while(-1  !=  getline( &line1, &n,fp1))
	{
		j++;
	}
	// printf("j----->%d\n",j);
	free(line1);
	fclose(fp1);		
	// printf("%d\n",j);
	int num[j];
	int m=0;
	char *str[j];	
	fp1 =fopen(argv[1],"r+"); 
	while(-1  !=  getline( &line, &n,fp1))
	{
		m++;
	}

	free(line);
	fclose(fp1);
	
	return 0; 
}