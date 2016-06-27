#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <malloc.h>




pthread_mutex_t lock;
struct timeval start_time,end_time;

float seq_thread_func(long int size)
{
	// allocate a memory of blocksize 20 mb ,
	//read blocks of data using sequentital access from one memory area to other using memcpy
	//and return the time taken for read and write

	int k=0;
	pthread_mutex_lock(&lock);

	long int blockSize=(long int)(20*1000000)/size;
	char *mem1;
    char *mem2;
    mem1=malloc(blockSize*size);
    mem2=malloc(blockSize*size);
	strncat(mem2,"hello",blockSize*size);
   	gettimeofday(&start_time,NULL);
   	for(k=0;k<(long int)(blockSize);k++)
	    {
		memcpy(mem1+k,mem2+k,size);
		// copy required bytes from one memory to other sequentially
        }
   	gettimeofday(&end_time,NULL);

    double data1=(double)start_time.tv_sec+((double)start_time.tv_usec/1000000);
      double data2=(double)end_time.tv_sec+((double)end_time.tv_usec/1000000);
      float dataTime=data2-data1;//calculate the time taken for read and write in sec
      free(mem1);
      free(mem2);

      printf("%f",dataTime);
    pthread_mutex_unlock(&lock);

    return dataTime;
}


float random_thread_func(long int size)
{

	// allocate a memory of blocksize 20 mb ,
	//read blocks of data using random access from one memory area to other using memcpy
	//and return the time taken for read and write

	int random_pos=0,k;
	pthread_mutex_lock(&lock);
	long int blockSize=(1000000*20)/size;
    char *mem1;
    char *mem2;

	mem1=malloc(blockSize*size);//allocate memory
	mem2=malloc(blockSize*size);//allocate memory

	strncat(mem2,"hello",blockSize*size);
   	gettimeofday(&start_time,NULL);

	for(k=0;k<(long int)blockSize;k++)
    {

		random_pos = rand()%(blockSize);
    		memcpy(mem1+random_pos,mem2+random_pos,size);
    		// copy required bytes from one memory to other in random_pos position
    }

   	gettimeofday(&end_time,NULL);
    double data1=(double)start_time.tv_sec+((double)start_time.tv_usec/1000000);
      double data2=(double)end_time.tv_sec+((double)end_time.tv_usec/1000000);
      float dataTime=data2-data1;//calculate the time taken for read and write in sec
      free(mem1);
      free(mem2);
printf("%f",dataTime);
    pthread_mutex_unlock(&lock);

    return dataTime;

}


void main()
{

  float throughput,latency;
int access;
int nothreads;
int operation;
long int size;
int i;

float timeTaken=0,data=0;
   printf("\n Block size:(Select 1 for 1B=1,2 for 1KB=1024,3 for 1MB=1048576):");
   fflush(stdout);
   scanf("%d",&size);
   printf("Access Method : 1-Sequential 2-Random");
   fflush(stdout);
   scanf("%d",&access);
   printf("Enter number of threads 1,2,4 :");
   fflush(stdout);
   scanf("%d",&nothreads);
   pthread_t  pth[nothreads];
   if(size==2)
   {
		// if 2 is selected assign 1024 bytes to read and write in memory

   size=(long int)1024;
   }
   if(size==3)
   {
	      // if 3 is selected assign 1024*2014 bytes to read and write in memory

   	size=(long int)(1024*1024);
   }


   if (pthread_mutex_init(&lock, NULL) != 0)
      {
          printf("\n mutex init failed\n");
          return 1;
      }
   // create given no of threads  and perform operations (read/write)
    for(i=0;i<nothreads;i++)
   {
	if(access==1)
    	//this block is for doing memcopy sequentially
   pthread_create(&pth[i],NULL,seq_thread_func,(long int)size);
	else
    	//this block is for doing memcopy to random memory
   pthread_create(&pth[i],NULL,random_thread_func,(long int)size);
	 }


    // joining the thread with other thread
   for(i=0;i<nothreads;i++)
   {
   pthread_join(pth[i],&data);
   timeTaken=timeTaken+data;		// add the time taken for all threads
   }
   printf("%f",timeTaken);
   timeTaken=timeTaken/nothreads;
   latency=(float)(timeTaken*size*1000)/(2*1000000*20);

   printf("Latency in milliseconds : %f \n",latency);
      throughput = (float)(1000000*20*2)/(timeTaken);//(no of loops*size*2/time taken)
       printf("Throughput in MB/sec : %f\n",(throughput)/(1024*1024));

       	   	   int filesc;
       	   	   char *fs="values.txt";
       	   	   filesc = open(fs,O_CREAT|O_RDWR,S_IRWXU);

       	   	 char *c = (char *)malloc(sizeof(char)*10000);
       	  char *s = (char *)malloc(sizeof(char)*10);
       	            	 	s[0]='\0';

       	 		c[0] = '\0';

        		strcat(c,"\r\n");
       	 		strcat(c,"size");
       	 		strcat(c," ");
       	 		strcat(c,"threads");
       	 		strcat(c," ");
       	 		strcat(c,"access");
       	 		strcat(c," ");
       	 		strcat(c,"throughput");
       	 		strcat(c,"   ");
       	 		strcat(c,"latency");
       	 		strcat(c,"\r\n");
          	 	sprintf (s,"%d",(int)size);
       	 		strcat(c,s);
       	 		strcat(c,"   ");
       	 		s[0]='\0';
       	 		sprintf (s,"%d",(int)nothreads);
       	 		strcat(c,s);
       	 		strcat(c,"     ");
       	 		sprintf(s,"%d",(int)access);
       	 		strcat(c,s);
       	 		strcat(c,"     ");
       	 		sprintf(s,"%f",(float)throughput/(1024*1024));
       	 		strcat(c,s);
       	 		strcat(c,"   ");
       	 	s[0]='\0';
       	 		sprintf(s,"%f",(float)latency);
       	 		strcat(c,s);
       	 		strcat(c,"\r\n");

       	 		printf("\n c is \n %s",c);

       	 	    write(filesc,c,strlen(c));
       	 	    	free(c);
       	 		free(s);

}
