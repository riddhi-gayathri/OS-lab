#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/mman.h>
#include<sys/wait.h>
#include<unistd.h>
#include<string.h>
#include<sys/shm.h>
#include<sys/stat.h>
#include<fcntl.h>
int main(int argc,char * argv[])
{
int i;
pid_t pid;
int k,n1,n2,n3;
const int Size =4096;
int shmid;
void *ptr;
shmid=shmget((key_t)1121,4096,0666|IPC_CREAT);
ptr=shmat(shmid,NULL,0666);
if(argc>1){
sscanf(argv[1],"%d",&i);
if(i<1){
printf("ERROR input:%d\n",i);
return 0;
}
}
else{
return 1;
}
pid=fork();
if(pid==0)
{
execlp("./fib","fib",argv[1],NULL);
}
else if(pid>0)
{
wait(NULL);
printf("\n Parent:Child completed\n");
printf("Parent printing:\n");
printf("%s",(char *)ptr);
shmdt(ptr);
}
printf("\n");
return 0;
}

