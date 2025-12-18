#include<stdio.h>
#include<conio.h>
typedef struct
{
	int pid;
	int arrival;
	int burst;
}process;

void calculate(process p[],int n)
{
	int i, smallest, count=0, time, limit;
	float waiting = 0, turnaround = 0, end;
	float averagewaiting, averageturnaround;
	int temp[n];
	for(i=0; i<n; i++)
	{
		temp[i]=p[i].burst;
	}
	p[9].burst = 9999;
	for(time=0; count != n; time++)
	{
		smallest=9;
		for(i= 0; i<n; i++)
		{
			if(p[i].arrival <= time && p[i].burst<p[smallest].burst && p[i].burst>0)
			{
				smallest=i;
			}
		}
		p[smallest].burst--;
		if(p[smallest].burst==0)
		{
			count++;
			end= time + 1;
			waiting = waiting + end -p[smallest].arrival - temp[smallest];
			turnaround= turnaround + end - p[smallest].arrival;
		}
	}
	averagewaiting = waiting/n;
	averageturnaround = turnaround/n;
	printf("\nAverage Waiting Time: %.2f", averagewaiting);
	printf("\nAverage Turnaround Time: %.2f", averageturnaround);
	printf("\nTotal Time: %d",time);
}

int main(){
	int i,n;
	printf("Enter the number of processes: ");
	scanf("%d",&n);
	process p[n];
	for(i=0; i<n; i++)
	{
		printf("Process %d\n",i+1);
		p[i].pid=i+1;
		printf("Arrival Time: ");
		scanf("%d",&p[i].arrival);
		printf("Burst Time: ");
		scanf("%d",&p[i].burst);
	}
	calculate(p,n);
	getch();
	return 0;
}
