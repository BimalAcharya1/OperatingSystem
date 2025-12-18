#include<stdio.h>
#include<conio.h>
#include<math.h>
int main()
{
	int headposition, n, i, j, k, seek=0, maxrange=199, difference, temp, temp1=0, temp2=0;
	float averageSeekTime;
	printf("Enter the number of queue requests: ");
	scanf("%d", &n);
	int queue[n], queue1[n], queue2[n];
	printf("Enter the head position: ");
	scanf("%d", &headposition);
	printf("Enter the disks positions to be read(queue): ");
	for(i=0; i<n; i++) {
		scanf("%d", &temp);
		if(temp > headposition) {
			queue1[temp1] = temp;
			temp1++;
		}
		else {
			queue2[temp2] = temp;
			temp2++;
		}
	}
	for(i=0; i<temp1-1; i++){
		for(j=i+1; j<temp1; j++) {
			if(queue1[i] > queue1[j]) {
				temp = queue1[i];
				queue1[i] = queue1[j];
				queue1[j] = temp;
			}
		}
	}
	for(i=0; i<temp2-1; i++) {
		for(j=i+1; j<temp2; j++) {
			if(queue2[i] > queue2[j]) {
				temp = queue2[i];
				queue2[i] = queue2[j];
				queue2[j] = temp;
			}
		}
	}
	for(i = 1, j = 0; j<temp1; i++, j++) {
		queue[i] = queue1[j];
	}
	queue[i] = maxrange;
	queue[i+1] = 0;
	for(i=temp1+3, j = 0; j<temp2; i++, j++) {
		queue[i] = queue2[j];
	}
	queue[0] = headposition;
	printf("%d", queue[0]);
	for (j=0; j<n+2; j++) {
		difference = abs (queue[j+1] - queue[j]);
		seek = seek + difference;
		printf(" -> %d", queue[j+1]);
	}
	averageSeekTime = seek/(float)n;
	printf("\nTotal seek time = %d", seek);
	printf("\nAverage seek time = %f", averageSeekTime);
	getch();
	return 0;
}
