#include <stdio.h>

typedef struct process {
    int processId;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int turnAroundTime;
    int waitingTime;
    int responseTime;
} Process;

void sjfPreemptive(Process[], int);

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    Process processes[n];

   
    for (int i = 0; i < n; i++) {
        printf("Process %d\n", i + 1);
        printf("Enter Arrival Time: ");
        scanf("%d", &processes[i].arrivalTime);
        printf("Enter Burst Time: ");
        scanf("%d", &processes[i].burstTime);
        processes[i].processId = i + 1;
        processes[i].remainingTime = processes[i].burstTime;
    }

    sjfPreemptive(processes, n);
    return 0;
}

void sjfPreemptive(Process processes[], int n) {
    int timeProgress[100], processTrack[100];
    int j = -1, k = -1;
    float avgWaitingTime = 0, avgTurnAroundTime = 0, avgResponseTime = 0;
    int totalWaitingTime = 0, totalTurnAroundTime = 0, totalResponseTime = 0;
    int elapsedTime = 0, remainingProcesses = n;
    int isFirstResponse[n];
    for (int i = 0; i < n; i++) isFirstResponse[i] = 1;

    timeProgress[++j] = 0;

    while (remainingProcesses > 0) {
        int exec = -1;
        int shortest = 9999;
        int earliestArrival = 9999;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= elapsedTime && processes[i].remainingTime > 0) {
                if (processes[i].remainingTime < shortest || (processes[i].remainingTime == shortest && processes[i].arrivalTime < earliestArrival)) {
                    shortest = processes[i].remainingTime;
                    earliestArrival = processes[i].arrivalTime;
                    exec = i;
                }
            }
        }

        if (exec == -1) {
            processTrack[++k] = 0; 
            elapsedTime++;
            timeProgress[++j] = elapsedTime;
            continue;
        }

        if (isFirstResponse[exec]) {
            processes[exec].responseTime = elapsedTime - processes[exec].arrivalTime;
            isFirstResponse[exec] = 0;
        }

        processes[exec].remainingTime--;
        processTrack[++k] = processes[exec].processId;
        elapsedTime++;
        timeProgress[++j] = elapsedTime;

        if (processes[exec].remainingTime == 0) {
            processes[exec].completionTime = elapsedTime;
            processes[exec].turnAroundTime = elapsedTime - processes[exec].arrivalTime;
            processes[exec].waitingTime = processes[exec].turnAroundTime - processes[exec].burstTime;

            totalTurnAroundTime += processes[exec].turnAroundTime;
            totalWaitingTime += processes[exec].waitingTime;
            totalResponseTime += processes[exec].responseTime;

            remainingProcesses--;
        }
    }

    avgTurnAroundTime = (float)totalTurnAroundTime / n;
    avgWaitingTime = (float)totalWaitingTime / n;
    avgResponseTime = (float)totalResponseTime / n;

    printf("\nObservation Table\nPID\tAT\tBT\tCT\tTT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
            processes[i].processId,
            processes[i].arrivalTime,
            processes[i].burstTime,
            processes[i].completionTime,
            processes[i].turnAroundTime,
            processes[i].waitingTime,
            processes[i].responseTime);
    }

    printf("\nGantt Chart:\n(P0 = idle)\n");
    for (int i = 0; i <= k; i++) {
        printf("| P%d ", processTrack[i]);
    }
    printf("|\n");
    for (int i = 0; i <= j; i++) {
        printf("%d\t", timeProgress[i]);
    }
    printf("\n");

    printf("\nAverage Waiting Time: %.2f\n", avgWaitingTime);
    printf("Average Turnaround Time: %.2f\n", avgTurnAroundTime);
    printf("Average Response Time: %.2f\n", avgResponseTime);
}
