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
int main (int argc, char *argv[])
{
     int i;
     pid_t pid;
     int k, n1, n2, n3;
     const int Size = 4096;
     int shm_fd;
     void *ptr;
     if (argc > 1)
       {
	    sscanf (argv[1], "%d", &i);
	    if (i < 1)
	      {
		   printf ("ERROR input:%d\n", i);
		   return 0;
	      }
       }
     else
       {
	    printf ("ERROR:not passing N in command line \n");
	    exit (0);
       }
     pid = fork ();
     if (pid == 0)
       {
	    execlp ("./fib", "fib", argv[1], NULL);
       }
     else if (pid > 0)
       {
	    wait (NULL);
	    printf ("\n Parent:Child completed\n");
	    shm_fd = shm_open ("dragon", O_RDONLY, 0666);
	    ptr = mmap (0, Size, PROT_READ, MAP_SHARED, shm_fd, 0);
	    printf ("Parent printing:\n");
	    printf ("%s", (char *) ptr);
	    shm_unlink ("dargon");
       }
     printf ("\n");
     return 0;
}

