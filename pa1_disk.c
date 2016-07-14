//Assignment program to benchmark hard disk performance
//@author : Tejus Prasad

#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

#include <fcntl.h>
#include <sys/stat.h>

int fileDesc ;
pthread_mutex_t lock;

struct timeval start_time,end_time;

float write_thread_seq(long int size)
 {
	// open the file , write blocks of data using sequential access and return the time taken for write

      pthread_mutex_lock(&lock);

      long int blockSize=(long int)((1000000*20)/size);

      char *fileName="trial.txt";
         fileDesc = open(fileName,O_RDWR,S_IRWXU);
         	 int itr;

    		char *writeData;
    		writeData=(char *)malloc(size);
            gettimeofday(&start_time,NULL);

    		for(itr=0;itr<blockSize;itr++)
    		 {
    		int currentPageSize =write(fileDesc,writeData,size);//write sequentially from starting position of file
    		 }

        	gettimeofday(&end_time,NULL);

        	double data1=(double)start_time.tv_sec+((double)start_time.tv_usec/1000000);
        	           double data2=(double)end_time.tv_sec+((double)end_time.tv_usec/1000000);
        	          float dataTime=(double)data2-data1;//calculate the time taken for write in sec

    		pthread_mutex_unlock(&lock);
    		free(writeData);
        	return dataTime;
}

float read_thread_seq(long int size)
 {

	// open the file , read blocks of data using sequential access and return the time taken for read

	long int blockSize=(long int)(1000000*20)/size;
     pthread_mutex_lock(&lock);
        char *fileName="trial.txt";
         fileDesc = open(fileName,O_RDWR,S_IRWXU);
         int itr;
 		char *readData;
    	 readData=(char *)malloc(size);

     	gettimeofday(&start_time,NULL);
     	        for(itr=0;itr<blockSize;itr++)
     	        {
     	        int currentPageSize =read(fileDesc,readData,size);//read sequentially from starting position of file
     	        }

        	gettimeofday(&end_time,NULL);

        	double data1=(double)start_time.tv_sec+((double)start_time.tv_usec/1000000);
        	           double data2=(double)end_time.tv_sec+((double)end_time.tv_usec/1000000);
        	           float dataTime=data2-data1;//calculate the time taken for read in sec

    	  	pthread_mutex_unlock(&lock);
    	  	free(readData);
    	  	return dataTime;
}

float write_thread_random(long int size)
 {
	// open the file , write blocks of data using random access and return the time taken for write


		int itr;
	off_t random_pos;
	long int blockSize=(long int)(1000000*20)/size;
    char *fileName="trial.txt";
    char *writeData;

    fileDesc = open(fileName,O_RDWR,S_IRWXU);
    pthread_mutex_lock(&lock);

    writeData=(char *)malloc(size);
	gettimeofday(&start_time,NULL);

        for(itr=0;itr<blockSize;itr++)
        {

        random_pos = rand()%(int)blockSize;//assign random block to write
        int currentPageSize =pwrite(fileDesc,writeData,size,random_pos);// writes from random block position
        }
    	gettimeofday(&end_time,NULL);

    	double data1=(double)start_time.tv_sec+((double)start_time.tv_usec/1000000);
    	           double data2=(double)end_time.tv_sec+((double)end_time.tv_usec/1000000);
    	    float dataTime=data2-data1;//calculate the time taken for write in sec
    	    free(writeData);

    	    pthread_mutex_unlock(&lock);
  	   	  return dataTime;
        	}

float read_thread_random(long int size)
 {
	// open the file , read blocks of data using random access and return the time taken for read
 		int itr;
 		off_t random_pos;
        long int blockSize=(long int)(1000000*20)/size;
        char *fileName="trial.txt";
        char *readData;
        fileDesc = open(fileName,O_RDWR,S_IRWXU);
        pthread_mutex_lock(&lock);

		readData=(char *)malloc(size);

    		gettimeofday(&start_time,NULL);

            for(itr=0;itr<blockSize;itr++)
            {
            random_pos = rand()%(int)blockSize;//assign random block to read
            int currentPageSize =pread(fileDesc,readData,size,random_pos);// read from random block position
            }
           gettimeofday(&end_time,NULL);
           double data1=(double)start_time.tv_sec+((double)start_time.tv_usec/1000000);
           double data2=(double)end_time.tv_sec+((double)end_time.tv_usec/1000000);
           float dataTime=data2-data1; //calculate the time taken for read in sec
           free(readData);

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
float timeTaken=0,dataTime;
   printf("Enter Operation to perform 1-Read 2-Write");
   fflush(stdout);
   scanf("%d",&operation);
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
	// if 2 is selected assign 1024 bytes to read or write from disk
size=(long int)(1024);
}
if(size==3)
{   // if 3 is selected assign 1024*2014 bytes to read or write from disk
	size=(long int)(1024*1024);

}

   if (pthread_mutex_init(&lock, NULL) != 0)
      {
          printf("\n mutex init failed\n");
          return 1;
      }
          char *fileName="trial.txt";
          	  char *f="hs";
          	  fileDesc = open(fileName,O_CREAT|O_RDWR,S_IRWXU);

          for(i=0;i<=(1024*1024*20);i++)
           {
              int currentPageSize =write(fileDesc,f,2);
           }

          // create given no of threads  and perform operations (read/write)
for(i=0;i<nothreads;i++)
{
	if(access==1 && operation==1)
	{
		//this block is for read operation sequential access
		pthread_create(&pth[i],NULL,read_thread_seq,(long int)size);
		//creates a thread and calls read_thread function
	}
	if(access==2 && operation==1 )
	{		//this block is for read operation random access
			pthread_create(&pth[i],NULL,read_thread_random,(long int)size);
			//creates a thread and calls read_thread_random function

	}
	if(access==1 && operation==2)
	{	//this block is for write operation using sequential access
		pthread_create(&pth[i],NULL,write_thread_seq,(long int)size);
		//creates a thread and calls write_thread_seq function

	}
	if(access==2 && operation==2)
	{	//this block is for write operation using random access
			pthread_create(&pth[i],NULL,write_thread_random,(long int)size);
			//creates a thread and calls write_thread_random function

	}

	}
// joining the thread with other thread
for(i=0;i<nothreads;i++)
{
	 pthread_join(pth[i],&dataTime);
	timeTaken=(float)timeTaken+dataTime; // add the time taken for all threads
}
	timeTaken=(timeTaken)/nothreads;
	throughput=(float)(1000000*20)/(timeTaken);  //(no of loops*size*2/time taken)
     latency=(float)(timeTaken*1000*size)/(1000000*20);


  	if(access==1 && operation==1)
  	 {
  	     printf("Throughput for sequential access read is %f ",(float)(throughput)/(1024*1024));
  	     printf("Latency for sequential access read is %f",latency);
  	 }

 	if(access==2 && operation==1)
 	{
     printf("Throughput for random access read is  %f",(float)(throughput)/(1024*1024));
     printf("Latency for random access read is %f",latency);

 	}  	if(access==1 && operation==2)
 	 {
 	     printf("Throughput for sequential access  write is %f",throughput/(1024*1024));
	     printf("Latency for sequential access write is %f",latency);

 	 }

 	if(access==2 && operation==2)
 	{
     printf("Throughput for random access write is %f",throughput/(1024*1024));
	     printf("Latency for random access write is %f",latency);

 	}
 	//store result in file
 		 int filesc;
 	     char *fs="values.txt";
 	     filesc = open(fs,O_CREAT|O_RDWR,S_IRWXU);

	 	char *c = (char *)malloc(sizeof(char)*10000);
	 	char *s = (char *)malloc(sizeof(char)*100);
			c[0] = '\0';
 			strcat(c,"\r\n");
	 		strcat(c,"size");
	 		strcat(c,"  ");
	 		strcat(c,"operation");
	 		strcat(c,"  ");
	 		strcat(c,"threads");
	 		strcat(c,"  ");
	 		strcat(c,"access");
	 		strcat(c,"  ");
	 		strcat(c,"throughput");
	 		strcat(c,"  ");
	 		strcat(c,"latency");
	 		strcat(c,"\r\n");

	 		sprintf (s,"%d",(int)size);
	 		strcat(c,s);
	 		strcat(c,"  ");

	 		sprintf (s,"%d",(int)operation);
	 		strcat(c,s);
	 		strcat(c,"  ");

	 		sprintf (s,"%d",(int)nothreads);
	 		strcat(c,s);
	 		strcat(c,"  ");

	 		sprintf (s,"%d",(int)access);
	 		strcat(c,s);
	 		strcat(c,"  ");

	 		sprintf (s,"%f",(float)throughput/(1024*1024));
	 		strcat(c,s);
	 		strcat(c,"  ");
	 		sprintf (s,"%f",(float)latency);
	 		strcat(c,s);
	 		strcat(c,"\r\n");

	 		printf("\n c is \n %s",c);
	 	    write(filesc,c,strlen(c));

}
