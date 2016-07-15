

#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

#include <fcntl.h>
#include <sys/stat.h>
pthread_mutex_t lock;

int threadFunc_int(int s)
{

	int i=0,a=1,b=2,c=4;

	struct timeval t1;
	struct timeval t2;

		gettimeofday(&t1,NULL);
	for(i=0;i<s;i++)
	{

		a=b*c;
		c=a+b;
		b=c-a;
		a=(int)b/c;

		gettimeofday(&t2,NULL);
		if(t2.tv_sec-t1.tv_sec==1)
				{
			//printf("i is %d",i);
			return i;
				}
	}
}

int threadFunc_float(int s)
{

	int i;
	float a=1.2,b=2.3,c=4.5;

	struct timeval t1;
	struct timeval t2;


	int timer=0;

	while(timer==0)
	{
		gettimeofday(&t1,NULL);

	for(i=0;i<s;i++)
	{

		a=b*i;
		c=a+b;
		b=c-a;
		a=(float)b/c;

		gettimeofday(&t2,NULL);
		if(t2.tv_sec-t1.tv_sec==1)
				{
			timer=1;
			//printf("%d",i);
			return i;
				}
	}
	}
}

int main(void)
{
	int i=0,j=0;
	int noThreads;
	int op;
	/* if (pthread_mutex_init(&lock, NULL) != 0)
	      {
	          printf("\n mutex init failed\n");
	          return 1;
	      }
	 */

printf("Enter Operation 1 int 2 float");
fflush(stdout);
scanf("%d",&op);
	printf("Enter threads");
	fflush(stdout);
		scanf("%d",&noThreads);
		pthread_t pth[noThreads];
		char *fileName="values.txt";
		int fileDesc = open(fileName,O_CREAT|O_RDWR,S_IRWXU);

	for(j=0;j<600;j++)
	{
	int f=0;
	float avg=0;
	for(i=0;i<noThreads;i++)
	{
	if(op==1)
	{
	pthread_create(&pth[i],NULL,threadFunc_int,100000000);
	}
	else
	{

		pthread_create(&pth[i],NULL,threadFunc_float,100000000);
	}
	}



	for(i=0;i<noThreads;i++)
	{
		pthread_join(pth[i],&f);
		avg=(float)avg+(f*4);
		//printf("avg is %f",avg);
	}

	//printf("\n avg is %d",(int)avg/noThreads);
	float iops=(float)(avg/noThreads);
	printf("\n flops is %f ",iops);
	printf("\n flops in Giga Hertz is %f",iops/1000000000);

	char *c = (char *)malloc(sizeof(char)*10);

	 sprintf (c,"%f",iops/1000000000);
	 strcat(c,"\r\n");
    write(fileDesc,c,strlen(c));
			}
	return 0;
}



