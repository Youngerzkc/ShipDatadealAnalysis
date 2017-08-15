#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define SIZE 128
#define len 12
int main(int argc,char **argv){
	size_t n; 
	int speed_up=150;
	int speed_down=0;
	double	lng_left = 103.045532;
	double	lng_right = 121.737185;
	double	lat_down = 28.131065;
	double	lat_up = 32.440479;
	char *line=NULL;
	FILE *fp,*fp1,*fp2;
	char seg[]="|- :";
	int speed;
	double dimension_lng;
	double dimension_lat;
	fp =fopen(argv[1],"r+"); 
	if (fp ==NULL){
		perror("fopen()");
		return -1;
	}
	fp1=fopen("./data.txt","aw+");//data.txt 为选出四列有效的数据
	fp2=fopen("./speed_zero.txt","aw+");//速度为0的文件
	char *substr=NULL;
	char *charlist[len];
	int i=0,j=0,m=0,s=0;
	while(-1  !=  getline( &line, &n,fp))
	{	
			for(m=0;m<len;m++)
				{
				charlist[m]=(char*)malloc(SIZE);
				}
				substr=strtok(line,seg);
				while(substr!=NULL)
			{
                // printf("i---->%d---->",i);
        	    strcpy(charlist[i],substr);
	            // printf("%d-->%s\n",i,charlist[i]);
                substr=strtok(NULL,seg);
                i++;
			}
		i=0;
		if(j==0){
					fprintf(fp1,"%s %s %s %s",charlist[0],charlist[2],charlist[5],charlist[6]);
					fprintf(fp2,"%s %s %s %s",charlist[0],charlist[2],charlist[5],charlist[6]); 
					 for(m=0;m<len;m++)
					 {
					 free(charlist[m]);
					 }	
					 j++;
					continue;
				}
				speed=atoi(charlist[7]);//
				dimension_lng=atof(charlist[10]);
				dimension_lat=atof(charlist[11]);
				if( (speed >=speed_down && speed<=speed_up) &&\
				(dimension_lng>=lng_left && dimension_lng<=lng_right) &&\
				(dimension_lat>=lat_down&&dimension_lat<=lat_up)&&\
				((dimension_lng-(long)dimension_lng) && (dimension_lat-(long)dimension_lat) )
				)
			 {
				fprintf(fp1,"%s-%s-%s %s:%s:%s %s %s %s",\
				charlist[0],charlist[1],charlist[2],charlist[3],charlist[4],charlist[5],\
				charlist[7],charlist[10],charlist[11]);
				fflush(fp1);
				/*
					经纬度为整数不写入
				*/	
				if(speed==0){
				fprintf(fp2,"%d %s-%s-%s %s:%s:%s %s %s %s",\
				j,charlist[0],charlist[1],charlist[2],charlist[3],charlist[4],charlist[5],\
				charlist[7],charlist[10],charlist[11]);
					fflush(NULL);
				}
				j++;
			} 	
		 for(m=0;m<len;m++)
		 {
			 free(charlist[m]);
		 }
	}	
	free(line);
	fclose(fp);
	fclose(fp1);
	fclose(fp2);
	return 0; 
}
