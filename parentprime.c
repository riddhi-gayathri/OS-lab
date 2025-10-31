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
int i,j,k,n1,n2,shm_fd;
pid_t pid;
const int Size =4096;
void *ptr;
if(argc>2){
sscanf(argv[1],"%d",&i);
sscanf(argv[2],"%d",&j);
if(i<2){
printf("ERROR input:%d\n",i);
return 0;
}
}
else{
printf("ERROR:Minimum of two arguments must be passed as command line argument!\n");
exit(0);
}
pid=fork();
if(pid==0)
{
execlp("./child","child",argv[1],argv[2],NULL);
}
else if(pid>0)
{
wait(NULL);
printf("\n Parent:Child completed\n");
shm_fd=shm_open("dragon1428",O_RDONLY,0666);
ptr=mmap(0,Size,PROT_READ,MAP_SHARED,shm_fd,0);
printf("Parent printing:\n");
printf("%s",(char *)ptr);
shm_unlink("dargon1428");
}
printf("\n");
return 0;
}
