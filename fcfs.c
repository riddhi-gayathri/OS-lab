#include<stdio.h>
#include<stdlib.h>
typedef struct node{
int pid,at,bt,ct,tat,wt,rt;
}p;
void fcfs(p[],int);
int main()
{
int n;
printf("Enter the number of process:");
scanf("%d",&n);
p ps[n];
for(int i=0;i<n;i++)
{
printf("Process %d\n",i+1);
printf("Enter the arrival time:");
scanf("%d",&ps[i].at);
printf("Enter the burst time:");
scanf("%d",&ps[i].bt);
ps[i].pid=i+1;
printf("\n");
}
for(int i=0;i<n-1;i++)
{
for(int j=0;j<n-i-1;j++)
{
if(ps[j].at>ps[j+1].at)
{
p temp=ps[j];
ps[j]=ps[j+1];
ps[j+1]=temp;
}
}
}
fcfs(ps,n);
return 0;
}

void fcfs(p ps[],int n)
{
int et=0,twt=0,ttat=0,trt=0;
float awt=0,art=0,atat=0;
for(int i=0;i<n;i++)
{
if(ps[i].at>et)
et=et+(ps[i].at-et);
int temp=et;
ps[i].rt=et-ps[i].at;
et+=ps[i].bt;
ps[i].ct=et;
ps[i].tat=ps[i].ct-ps[i].at;
ps[i].wt=ps[i].tat-ps[i].bt;
printf("/(%d)p%d(%d)",temp,ps[i].pid,et);
}
printf("\n");
printf("Observation table\npid\tAT\tBT\tCT\tTT\tWT\tRT\n");
for(int i=0;i<n;i++){
printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",ps[i].pid,ps[i].at,ps[i].bt,ps[i].ct,ps[i].tat,ps[i].wt,ps[i].rt);
ttat+=ps[i].tat;
twt+=ps[i].wt;
trt+=ps[i].rt;
}
atat=(float)ttat/n;
awt=(float)twt/n;
art=(float)trt/n;
printf("\nAverage Waiting time %.2f\n",awt);
printf("\nAverage Turn Around time %.2f\n",atat);
printf("\nAverage Response time %.2f\n",art);
}

