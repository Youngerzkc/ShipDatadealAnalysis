/*
    新的船数据信息经异常处理之后会筛选符合条件的速度为0的文件块
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#define len 12
#define SIZE 1024
#define  M   5
#define MinTime  (1*60*60L)
int compareFirstAndLast(long a,long b);

int main(int argc,char **argv){
    size_t n; 
	char *line=NULL;
    char *line1=NULL;
    char seg[]="|- :";
    char *substr=NULL;
    char *charlist[len];
    FILE *fp;
    fp =fopen(argv[1],"r+"); 
	if (fp ==NULL){
		perror("fopen()");
		return -1;
	}
    int j=0;
    while(-1 != getline(&line1,&n,fp) )
    {
        j++;
    }
    fclose(fp);
    free(line1);
    time_t timesec[j];
    int year[j],mon[j],day[j],hour[j],min[j],sec[j];
    struct tm timep[j];
    double lng[j],lat[j];
    double lng_value=0,lng_sum=0;
    double lat_value=0,lat_sum=0;
    double point_distance[j];
    double sum_point_distance=0;
    double average_point_distance=0;
    char rmFile[SIZE]="rm -rf ";
    int i=0,m=0,k=0;
       fp =fopen(argv[1],"r+"); 
	if (fp ==NULL){
		perror("fopen()");
		return -1;
	}
    while(-1  !=  getline( &line, &n,fp))
    {
            
              for(m=0;m<len;m++)
				{
			    	charlist[m]=(char*)malloc(n);
				}
			    substr=strtok(line,seg);
			    while(substr!=NULL)
		    	{
        	    strcpy(charlist[i],substr);
                substr=strtok(NULL,seg);
                i++;
		        }
                year[k]=atoi(charlist[1]);
                mon[k]=atoi(charlist[2]);
                day[k]=atoi(charlist[3]);
                hour[k]=atoi(charlist[4]);
                min[k]=atoi(charlist[5]);
                sec[k]=atoi(charlist[6]);
                timep[k].tm_year=year[k];
                timep[k].tm_mon=mon[k];
                timep[k].tm_mday=day[k];
                timep[k].tm_hour=hour[k];
                timep[k].tm_min=min[k];
                timep[k].tm_sec=sec[k];
                timesec[k]=mktime(&timep[k]);
                lng[k]=atof(charlist[8]);
                lat[k]=atof(charlist[9]);
                lng_sum +=lng[k];
                lat_sum +=lat[k];
   
	        	i=0;
             for(m=0;m<len;m++){
                 free(charlist[m]);
                }
                  k++;
                  
        }
            free(line);
       
       
          if(k<2){
               printf("%s\n",argv[1]);
                printf("至少有3行\n");
                strcat(rmFile,argv[1]);
                system(rmFile);
                return -1;
          }
            int ret1=compareFirstAndLast(timesec[k-1],timesec[0]);
            if(ret1!=1){
               
                printf("%s\n",argv[1]);
                printf("第一个条件不符合\n");
                strcat(rmFile,argv[1]);
                system(rmFile);

                return -1;
            }
            
     
    return 0;
}
//1 .有效包
//0  无效包
int compareFirstAndLast(long a,long b){
    printf("判断第一个和最后一个\n");
    if( (a - b )> MinTime )
    {
        //sleep(5);
        printf("判断第一个 和最后一个 差 %ld\n", a-b-MinTime);
        return 1;
    }   
    return 0;
}

//1.有效
//2.无效

