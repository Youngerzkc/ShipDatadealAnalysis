#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#define len 12
#define SIZE 1024
#define  M   5
#define MaxTime  (3*60*60L)
#define MinTime    (1*60*60L)
int seclectionNum(double latPoint[],double lngPoint[],int num);
int compareFirstAndLast(long a,long b);
int compareBeside(long a[],long num);
int computeValue(int num,double point[],double average);
double computeDistance(double a1,double a2,double b1,double b2);
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
            lng_value = lng_sum/k;
            lat_value = lat_sum/k;
         for(i=0;i<k;i++){
            point_distance[i]=computeDistance(lng_value,lat_value,lng[i],lat[i]);//
            sum_point_distance+=point_distance[i];
            }
            average_point_distance=sum_point_distance/k;
            //由条件判断至少文件有3行
          if(k<3){
                strcat(rmFile,argv[1]);
                system(rmFile);
                return -1;
                 }
            int ret1=compareFirstAndLast(timesec[k-1],timesec[0]);
            if(ret1!=1){
                /*
                删除该包
                */
                strcat(rmFile,argv[1]);
                system(rmFile);
                return -1;
            }
            int ret2=compareBeside(timesec,k-1);
           if(ret2!=1){
                 /*
                删除该包
                */
                 strcat(rmFile,argv[1]);
                 system(rmFile);
                 return -2;
             }
             double ret3=computeValue(k-1,point_distance,average_point_distance);
              if(ret3!=1){
                 /*
                删除该包
                */
                 strcat(rmFile,argv[1]);
                 system(rmFile);
                 return -3;
              }
    return 0;
}
//1 .有效包
//0  无效包
int compareFirstAndLast(long a,long b){
    if( (a - b )> MaxTime )
    {
        return 1;
    }   
    return 0;
}
//1 .有效包
//0  无效包
int compareBeside(long a[],long num){
    int i=0;
    for(i=0;i<num-1;i++){
       if(a[i+1]-a[i]>MinTime)
         {
        return 0;
         }
    }  
    return 1;
}
//1.有效
//0.无效
int computeValue(int num,double point[],double average){
    int i=0;
    for(i=0;i<num;i++)
    {
       if( point[i] > M*average)
           {
            return 0;
           }
    }
    return 1;
}

//1.有效
//0.无效

double computeDistance(double a1,double a2,double b1,double b2)
{
    double sum=(b1-a1)*(b1-a1)+(b2-a2)*(b2-a2);
    return sqrt(sum);
}