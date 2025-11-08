#include<stdio.h>
#include<conio.h>
typedef struct{
	int pid;
	int burst;
}process;

void calculateTime(process p[], int n, int waiting[], int turnaround[]){
	int i;
	waiting[0] = 0;
	for(i=1;i<n;i++)
		waiting[i]=waiting[i-1] + p[i-1].burst;
	for(i=0;i<n;i++)
		turnaround[i] = waiting[i] + p[i].burst;
}

void calculateAverage(process p[], int n){
	int i, waiting[n], turnaround[n];
	int TotalWaiting = 0, TotalTurnAround = 0;
	calculateTime(p, n, waiting, turnaround);
	printf("Processs\t Burst Time\t Waiting Time\t Turn Around Time");
	for(i=0;i<n;i++){
		TotalWaiting += waiting[i];
		TotalTurnAround += turnaround[i];
		printf("\n%d\t\t %d\t\t %d\t\t %d\n", p[i].pid, p[i].burst, waiting[i], turnaround[i]);
	}
	double averagewaiting=(double)TotalWaiting/n;
	double averageturnaround=(double)TotalTurnAround/n;
	printf("\nAverage waiting time: %f",averagewaiting);
	printf("\nAverage turnaround time: %f",averageturnaround);
}

int main(){
	int i, n;
    printf("Enter number of processes: ");
    scanf("%d",&n);
    process p[n];
    printf("Enter burst time for each processes: \n\n");
    for(i=0;i<n;i++){
    	printf("Process %d\n",i+1);
    	p[i].pid = i+1;
    	printf("Enter Burst time: ");
    	scanf("%d",&p[i].burst);
	}
	calculateAverage(p, n);
	return 0;
}
