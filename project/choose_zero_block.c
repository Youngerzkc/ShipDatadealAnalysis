#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define SIZE 1024
#define NAMESIZE 32
#define len 12
int main(int argc,char **argv){
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
	free(line1);
	fclose(fp1);		
	int num[j];
	int m=0;
	char *str[j];	
	fp1 =fopen(argv[1],"r+"); 
	while(-1  !=  getline( &line, &n,fp1))
	{
			str[m]=malloc(n);
			strcpy(str[m],line);
			substr=strtok(line,seg);
			num[m]=atoi(substr);
			m++;
	}
		free(line);
		fclose(fp1);
		int k=0;
		FILE *fp[m];
		char name[NAMESIZE];	
		i=0;
	while(i<j){
				if(num[i+1]-num[i]==1)
				{
						sprintf(name,"%d.txt",k);
						fp[k]=fopen(name,"a+");
						if(fp==NULL){
						perror("fopen");
						}
						fprintf(fp[k],"%s",str[i]);
						fflush(fp[k]);
						if(i+2<=j && (num[i+2]-num[i+1]!=1)){
						fprintf(fp[k],"%s",str[i+1]);
						fflush(fp[k]);
						fclose(fp[k]);
						k++;
						i++;
					 continue;
				}		
				i++;
				fclose(fp[k]);
				continue;	
			}
		
			i++;
	}
	for(i=0;i<=j;i++){
		free(str[i]);
	}
	

	return 0; 
}