
#include <stdio.h>

typedef struct process {
    int processId;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnAroundTime;
    int waitingTime;
    int finished;
    int responseTime;
} Process;

void sjfNP(Process[], int);

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    Process processes[n];

    // Accept process details
    for (int i = 0; i < n; i++) {
        printf("Process %d\n", i + 1);
        printf("Enter Arrival Time: ");
        scanf("%d", &processes[i].arrivalTime);
        printf("Enter Burst Time: ");
        scanf("%d", &processes[i].burstTime);
        processes[i].processId = i + 1;
        processes[i].finished = 0;
    printf("\n");
}

    sjfNP(processes, n);
    return 0;
}

void sjfNP(Process processes[], int n) {
    float avgWaitingTime = 0, avgTurnAroundTime = 0, avgResponseTime = 0;
    int totalWaitingTime = 0, totalTurnAroundTime = 0, totalResponseTime = 0;
    int elapsedTime = 0, remainingProcesses = n;
int exec;
    printf("\nGantt chart:\n");

    while (remainingProcesses) {
        exec = -1;
        int shortestBurstTime = 9999;

        for (int i = 0; i < n; i++) {
            if (!processes[i].finished && processes[i].arrivalTime <= elapsedTime) {
                if (processes[i].burstTime < shortestBurstTime) {
                    exec = i;
                    shortestBurstTime = processes[i].burstTime;
                }
            }
        }

        if (exec == -1) {
            printf("|(%d)*(%d)", elapsedTime, elapsedTime + 1);
            elapsedTime++;
        } else {
            int temp = elapsedTime;
            processes[exec].responseTime = elapsedTime - processes[exec].arrivalTime;
            elapsedTime += processes[exec].burstTime;
            processes[exec].finished = 1;
            processes[exec].completionTime = elapsedTime;
            remainingProcesses--;

            processes[exec].turnAroundTime = processes[exec].completionTime - processes[exec].arrivalTime;
            processes[exec].waitingTime = processes[exec].turnAroundTime - processes[exec].burstTime;

            printf("|(%d) P%d (%d)", temp, processes[exec].processId, elapsedTime);
        }
    }

    printf("\n\nPID\tAT\tBT\tCT\tTT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
            processes[i].processId,
            processes[i].arrivalTime,
            processes[i].burstTime,
            processes[i].completionTime,
            processes[i].turnAroundTime,
            processes[i].waitingTime,
            processes[i].responseTime);

        totalTurnAroundTime += processes[i].turnAroundTime;
        totalWaitingTime += processes[i].waitingTime;
        totalResponseTime += processes[i].responseTime;
}
avgTurnAroundTime=(float) totalTurnAroundTime/n;
avgWaitingTime=(float) totalWaitingTime/n;
avgResponseTime=(float) totalResponseTime/n;

printf("\n avearge Waiting time:%.21f\n",avgWaitingTime);
printf("\n avearge TurnAround time:%.21f\n",avgTurnAroundTime);
printf("\n avearge Response time:%.21f\n",avgResponseTime);
}
