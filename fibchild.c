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
#include<errno.h>

int main(int argc, char *argv[])
{
    int k = 2, n1, n2, n3;
    void *ptr;
    int shmid;

    // Check if correct number of arguments provided
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number_of_fibonacci_terms>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Convert argument to integer and check validity
    int i = atoi(argv[1]);
    if (i <= 0) {
        fprintf(stderr, "Error: Number of terms must be a positive integer greater than 0\n");
        exit(EXIT_FAILURE);
    }

    // Get shared memory segment
    shmid = shmget((key_t)1121, 4096, 0666);
    if (shmid == -1) {
        perror("shmget failed");
        exit(EXIT_FAILURE);
    }

    // Attach shared memory
    ptr = shmat(shmid, NULL, 0666);
    if (ptr == (void*)-1) {
        perror("shmat failed");
        exit(EXIT_FAILURE);
    }

    printf("Child\n");

    n1 = 0;
    n2 = 1;

    // Write and print first two terms
    sprintf(ptr, "%d\t", n1);
    ptr += strlen(ptr);
    printf("%d\t", n1);

    sprintf(ptr, "%d\t", n2);
    ptr += strlen(ptr);
    printf("%d\t", n2);

    // Generate remaining terms
    while (k != i) {
        n3 = n2 + n1;
        sprintf(ptr, "%d\t", n3);
        printf("%d\t", n3);
        n1 = n2;
        n2 = n3;
        ptr += strlen(ptr);
        k++;
    }

    // Detach shared memory before removing
    if (shmdt(ptr) == -1) {
        perror("shmdt failed");
    }

    // Remove shared memory segment
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl IPC_RMID failed");
    }

    return 0;
}
