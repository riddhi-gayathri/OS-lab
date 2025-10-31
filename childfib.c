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
int
main (int argc, char *argv[])
{
     int k = 2, n1, n2, n3;
     int shm_fd = shm_open ("dragon", O_CREAT | O_RDWR, 0666);
     void *ptr;
     ftruncate (shm_fd, 4096);
     ptr = mmap (0, 4096, PROT_WRITE, MAP_SHARED, shm_fd, 0);
     printf ("Child\n");
     int i = atoi (argv[1]);
     n1 = 0;
     n2 = 1;
     sprintf (ptr, "%d\t", n1);
     ptr += strlen (ptr);
     printf ("%d\t", n1);
     sprintf (ptr, "%d\t", n2);
     ptr += strlen (ptr);
     printf ("%d\t", n2);
     while (k != i)
       {
	    n3 = n2 + n1;
	    sprintf (ptr, "%d\t", n3);
	    printf ("%d\t", n3);
	    n1 = n2;
	    n2 = n3;
	    ptr += strlen (ptr);
	    k++;
       }
}
