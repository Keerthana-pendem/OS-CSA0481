#include <stdio.h>
struct Process 
{
    int processId;
    int arrivalTime;
    int burstTime;
};
void calculateTimes(struct Process processes[],int n,int waitingTime[],int turnaroundTime[]) 
{
    waitingTime[0]=0;
    turnaroundTime[0]=processes[0].burstTime;
    for (int i=1;i<n;i++) 
	{
        waitingTime[i]=turnaroundTime[i-1];
        turnaroundTime[i]=waitingTime[i]+processes[i].burstTime;
    }
}
void calculateAverages(int waitingTime[],int turnaroundTime[],int n,float *averageWaitingTime,float *averageTurnaroundTime) {
    int totalWaitingTime=0,totalTurnaroundTime=0;
    for (int i=0;i<n;i++) 
	{
        totalWaitingTime+=waitingTime[i];
        totalTurnaroundTime+=turnaroundTime[i];
    }
    *averageWaitingTime=(float)totalWaitingTime/n;
    *averageTurnaroundTime=(float)totalTurnaroundTime/n;
}
void displaySchedule(struct Process processes[],int n,int waitingTime[],int turnaroundTime[]) 
{
    printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i=0;i<n;i++) 
	{
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].processId, processes[i].arrivalTime,processes[i].burstTime, waitingTime[i], turnaroundTime[i]);
    }
}
int main() 
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process processes[n];
    for (int i=0;i<n;i++) 
	{
        processes[i].processId =i+1;
        processes[i].arrivalTime =0;
        printf("Enter burst time for process %d:",i+1);
        scanf("%d", &processes[i].burstTime);
    }
    int waitingTime[n],turnaroundTime[n];
    calculateTimes(processes,n,waitingTime,turnaroundTime);
    displaySchedule(processes,n,waitingTime,turnaroundTime);
    float averageWaitingTime, averageTurnaroundTime;
    calculateAverages(waitingTime,turnaroundTime,n,&averageWaitingTime,&averageTurnaroundTime);
    printf("\nAverage Waiting Time: %.2f\n", averageWaitingTime);
    printf("Average Turnaround Time: %.2f\n", averageTurnaroundTime);
    return 0;
}
