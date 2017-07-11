#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(int argc,char **argv){
	if(argc!=2){
		fprintf(stderr,"%s","please input legal usage...sort file");
		return -1;
	}		
	char sortSpeedFile[1024]="sort  -nk 1 -t '|' ";
	strcat(sortSpeedFile,argv[1]);
	strcat(sortSpeedFile," -o ");
	strcat(sortSpeedFile,argv[1]);
	system (sortSpeedFile);
	return 0;
}
