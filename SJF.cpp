#include<stdio.h>
#include<conio.h>

typedef struct{
	int pid;
	int brust;
}process;
void swap(process*a,process *b){
	
	process temp;
	temp=*a;
	*a=*b;
	*b=temp;
}
void sort(process p[],int n){
	int i,j,min;
	for(i=0;i<n-1;i++){
		min=i;
		for(j=i+1;j<n;j++){
		 if(p[j].brust<p[min].brust)
		 min=j;
		}
		swap(&p[i],&p[min]);
	}
}
void calculateTime(process p[], int n,int waiting[],int turnaround[]){
	int i;
	waiting[0]=0;
	for(i=0;i<n;i++)
	    waiting[i]=waiting[i-1]+p[i-1].brust;
	for(i=0;i<n;i++)
	    turnaround[i]=waiting[i]+p[i].brust;
}
void calculateAverage(process p[], int n){
	int i,waiting[n],turnaround[n];
	int totalwaiting=0,totalturnaround=0;
	sort(p,n);
	calculateTime(p,n,waiting,turnaround);
	printf("PROCESS\tBRUST TIME\tWAITING TIME\tTURNAROUND TIME\n");
	for(i=0;i<n;i++){
		totalwaiting+=waiting[i];
		totalturnaround+=turnaround[i];
		printf("%d\t\t %d\t\t%d \t\t%d\n",p[i].pid,p[i].brust,waiting[i],turnaround[i]);
	}
	double averagewaiting=(double)totalwaiting/n;
	double averageturnaround=(double)totalturnaround/n;
	printf("\nAverage waiting time: %f",averagewaiting);
	printf("\nAverage Turnaround time: %f", averageturnaround);
}
int main(){
	int i,n;
	printf("Enter the Number of Processes:");
	scanf("%d",&n);
	process p[n];
	printf("Enter brust time:");
	for(i=0;i<n;i++){
		printf("Processs %d:\n",i+1);
		p[i].pid=i+1;
		printf("Brust Time:");
		scanf("%d",&p[i].brust);
	}
	calculateAverage(p,n);
	getch();
}
