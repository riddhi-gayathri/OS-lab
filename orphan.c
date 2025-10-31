#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {

	pid_t child_pid, my_pid, parent_pid;
	int i=10;
	
	child_pid = fork();
	
	if(child_pid < 0) {
		printf("Fork failed! Exiting\n");
		exit(0);
	} 

	if(child_pid == 0) {
		//child process
		printf("[CHILD] This is a child process\n");

		my_pid = getpid();
		parent_pid = getppid();

		printf("[CHILD] My pid is %d\n", my_pid);
		printf("[CHILD] My parent's pid is %d\n", parent_pid);	
		printf("[CHILD] Exiting\n");
		exit(0);	
		
	} else {
		// parent process
		printf("[PARENT] This is a parent process\n");

		my_pid = getpid();
		parent_pid = getppid();

		printf("[PARENT] My pid is %d\n", my_pid);
		printf("[PARENT] My parent's pid is %d\n", parent_pid);	
		printf("[PARENT] Sleeping for 10 seconds\n");
		sleep(10);

		printf("[PARENT] Child pid = %d has ended, but it has an entry in process table\n", child_pid);
		printf("[PARENT] It is a zombie process\n\n\n");
	}

	return 0;
}
