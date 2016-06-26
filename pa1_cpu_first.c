#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>


float threadFunc_int(long int noItr)
{
	int i,val1=1,val2=2,val3=4;
	struct timeval start_time;
	struct timeval end_time;

	gettimeofday(&start_time,NULL);

	for(i=0;i<noItr;i++)
	{
		val1=val2*val3;
		val3=val1+val2;
		val2=val3-val1;
		val1=val2/val3;

	}
	gettimeofday(&end_time,NULL);
	printf("%d %d",end_time.tv_sec,start_time.tv_sec);
	float timeTaken=(float)(end_time.tv_sec-start_time.tv_sec);
	return timeTaken;
}
float threadFunc_float(long int noItr)
{
		int i;
	 float val1=1.2,val2=2.4,val3=4.6;

	struct timeval start_time;
	struct timeval end_time;

	gettimeofday(&start_time,NULL);

	for(i=0;i<noItr;i++)
	{
		val1=val2*val3;
		val3=val1+val2;
		val2=val3-val1;
		val1=val2/val3;
	}
	gettimeofday(&end_time,NULL);
	float timeTaken=(float)(end_time.tv_sec-start_time.tv_sec);

	return timeTaken;
}

int main(void)
{
	int i=0;
	int noThreads;
	struct timeval begin_time;
	struct timeval last_time;
	int op;
	float timeTaken=0;
	float avgTime=0.0;

	printf("Enter Operation to Perform 1 int 2 float");
		fflush(stdout);
		scanf("%d",&op);
		printf("Enter threads");
		fflush(stdout);
		scanf("%d",&noThreads);
		pthread_t pth[noThreads];

	for(i=0;i<noThreads;i++)
	{
	if(op==1)
	pthread_create(&pth[i],NULL,threadFunc_int,100000000);
	else
	pthread_create(&pth[i],NULL,threadFunc_float,100000000);
	}
	for(i=0;i<noThreads;i++)
	{
		pthread_join(pth[i],&timeTaken);
		avgTime=avgTime+timeTaken;
	}

	float ops=(float)(100000000*4*noThreads)/avgTime;
	if(op==1)
	{
	printf(" Iops in Hertz is %f",(double)ops);
	printf(" Iops in Giga Hertz is %f",ops/1000000000);
	}
	else
	{
		printf(" Flops in Hertz is %lf",ops);
		printf(" Flops in Giga Hertz is %f",ops/1000000000);
	}
	return 0;
}

