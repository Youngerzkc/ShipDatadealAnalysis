#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include <unistd.h>
#define len 5
#define len2 12
double lngAverage(double lng[],long num);
double latAverage(double lat[],long num);
double computeDistance(double a1,double a2,double b1,double b2);
double lngPortAverage(char *name );
double latPortAverage(char *name);

int  comparePortBase(char* file,double lng,double lat,double lng_port[],double lat_port[],char *name[], double r[],long num);
int main(int argc,char **argv){
    size_t n; 
    char *line=NULL;
	char *line1=NULL;
    char *line2=NULL;
    char seg1[]="|- :";
    char *substr=NULL;
    char *substr2=NULL;
    char *charlist[len]={NULL};

    double lng_value=0;
    double lat_value=0;
    FILE *fp=NULL;
 
    fp =fopen(argv[1],"r+"); 
	if (fp ==NULL){
		perror("fopen()");
		return -1;
	}
    int j=0,i=0,m=0;
    while(-1 != getline(&line1,&n,fp) )
    {
        j++;
    }
    free(line1);
    fclose(fp);
    char *portName[j];
    double lng_port[j];
    double lat_port[j];
    double r_port[j];
    fp =fopen(argv[1],"r+"); 
	    if (fp ==NULL){
		    perror("fopen()");
		    return -1;
    	}
    int k=0; //行数
    //fp---->argv[1] 港口信息文  
    while(-1  !=  getline( &line, &n,fp)){
               portName[k]=malloc(n);
               for(m=0;m<len;m++)
				{
			    	charlist[m]=(char*)malloc(n);
				}
			    substr=strtok(line,seg1);
			    while(substr!=NULL)
		    	{
                strcpy(charlist[i],substr);
                substr=strtok(NULL,seg1);
                i++;
		        } 
                strcpy(portName[k],charlist[0]);
                lng_port[k]=atof(charlist[1]);
                lat_port[k]=atof(charlist[2]);
                r_port[k]=atof(charlist[3]);
	        	i=0;
                k++;
                fflush(NULL);
               for(m=0;m<len;m++){
                 free(charlist[m]);
                }
        }
        free(line);
        fclose(fp);
     printf("k is %d\n",k);
     lng_value = lngPortAverage(argv[2]);
     printf("lng_value is %lf\n",lng_value);
     lat_value = latPortAverage(argv[2]);
     printf("lat_value is %lf\n",lat_value);
    comparePortBase(argv[2],lng_value,lat_value,lng_port,lat_port,portName,r_port,k);

        return 0;

}
double lngPortAverage(char *name)
{
    char *line1=NULL;
    char  *line2=NULL;
    char  seg1[]="|- :";
    char *substr=NULL;
    char *packlist[len2]={NULL};
    double lng_value=0,lng_sum=0;
 
    FILE *fp2=NULL;
     size_t h;
     fp2 =fopen(name,"r+"); 
	 if (fp2 ==NULL){
		perror("fopen()");
		return -1;
	 }
         int v=0;//行数
             while(-1 != getline(&line1,&h,fp2) )
            {
                        v++;
            }
            printf("vvvvv is %d\n",v);
           
            fclose(fp2);
            free(line1);
            fp2= fopen(name,"r+");   
            if(fp2==NULL){
                    perror("fopen()");
                    return -1;
            }
            int t=0;  
            double lng[v],lat[v];
            int m=0,i=0;
            while(-1  !=  getline( &line2, &h,fp2))
        {
                    
                     for(m=0;m<len2;m++)
				{
			    	packlist[m]=(char*)malloc(h);
                
                }
                substr=strtok(line2,seg1);
			    while(substr!=NULL)
		    	{    
              	
                strcpy(packlist[i],substr);
                substr=strtok(NULL,seg1);
              //  sleep(1);
                i++;
		        }    
	        	
                lng[t]=atof(packlist[8]);
                lat[t]=atof(packlist[9]);
                lng_sum +=lng[t];
          
	        	i=0;
                t++;
               for(m=0;m<len2;m++){
                 free(packlist[m]);
                }
                
        }  
        lng_value = lng_sum/t;
        free(line1);
        fclose(fp2);
        return lng_value;
}
double latPortAverage(char *name){
    char *line1=NULL;
    char  *line2=NULL;
    char  seg1[]="|- :";
    char *substr=NULL;
    char *packlist[len2]={NULL};
    double lat_value=0,lat_sum=0;
  //打开小数据包 
    FILE *fp2=NULL;
     size_t h;
     fp2 =fopen(name,"r+"); 
	 if (fp2 ==NULL){
		perror("fopen()");
		return -1;
	 }
         int v=0;//行数
             while(-1 != getline(&line1,&h,fp2) )
            {
                        v++;
            }
          
           
            fclose(fp2);
            free(line1);
            fp2= fopen(name,"r+");   
            if(fp2==NULL){
                    perror("fopen()");
                    return -1;
            }
            int t=0;  
            double lng[v],lat[v];
            int m=0,i=0;///////////////////////////////////////jia
            while(-1  !=  getline( &line2, &h,fp2))
        {
                      
                     for(m=0;m<len2;m++)
				{
			    	packlist[m]=(char*)malloc(h);
                
                }
                substr=strtok(line2,seg1);
			    while(substr!=NULL)
		    	{    
                	
                strcpy(packlist[i],substr);
                substr=strtok(NULL,seg1);
            
                i++;
		        }    
	        	
                lat[t]=atof(packlist[9]);
              
                lat_sum +=lat[t];
	        	i=0;
                t++;
               for(m=0;m<len2;m++){
                 free(packlist[m]);
                }
                
        }  
        lat_value = lat_sum/t;
     
        free(line1);
        fclose(fp2);
        return lat_value;
}
//1 属于该港口
//0 不属于港口
int  comparePortBase(char*filename,double lng,double lat,double lng_port[] ,double lat_port[],char *name[],double r[],long num){
    double ret1;
    int i=0;
    char *savePath=NULL;
    savePath="cp  -rf  ";
    while(i<num)
    {
        printf("hello\n");
        ret1 = computeDistance(lng,lat,lng_port[i],lat_port[i]);
        printf("average distance is %lf\n",ret1);
        printf("port base is %lf\n",r[i]);
        if(ret1< r[i])
        {
           char *copyfile=NULL;
            copyfile=(char*)malloc(strlen(savePath)+strlen(filename)+32+strlen(name[i]));
            *copyfile='\0';
          //  printf("<<<<<<<<<%s\n",savePath);
            strcat(copyfile,savePath);
          //  printf("copyfile is %s\n",copyfile);
            strcat(copyfile,filename);
            strcat(copyfile,"  ./portBlock/");
            strcat(copyfile,name[i]);
            strcat(copyfile,"/");
            printf("start copy file.\n");
            system(copyfile);
            printf("savePath is %s\n",copyfile);
            printf("port base is %lf",r[i]);
            printf("%s\n",name[i]);
           // printf("the pwd is ");
            system("pwd");
          //  printf("i-------------->>>><<<<<<%d\n",i);
            printf("属于该包\n"); 
            sleep(2);
            free(copyfile);
          //  sleep(10);
            return 0;
        }
        i++;
    }
   return 1;
}
double computeDistance(double a1,double a2,double b1,double b2){
    double sum=(b1-a1)*(b1-a1)+(b2-a2)*(b2-a2);
    return sqrt(sum);
}
