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
#include<math.h>
int main(int argc,char * argv[])
{
void *ptr;
int shm_fd=shm_open("dragon1428",O_CREAT|O_RDWR,0666);
ftruncate(shm_fd,4096);
ptr=mmap(0,4096,PROT_WRITE,MAP_SHARED,shm_fd,0);
printf("Child\n");
int i=atoi(argv[1]);
int j=atoi(argv[2]);
int flag=0;
printf("The prime numbers in the range %d and %d ar \n",i,j);
for(int n=i;n<j;n++){
flag=0;
for(int k=2;k<=n/2;k++){
if(n%k==0){
flag=1;
break;
}
}
if(flag==0)
{
sprintf(ptr,"%d\t",n);
printf("%d\t",n);
}
}
printf("\n");
return 0;
}
