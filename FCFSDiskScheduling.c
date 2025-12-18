#include<stdio.h>
#include<conio.h>
#include<math.h>
int main()
{
	int i, n, request[50], move=0, current;
	printf("Enter the current position: ");
	scanf("%d", &current);
	printf("Enter the number of requests: ");
	scanf("%d", &n);
	printf("Enter the request order: ");
	for(i=0; i<n; i++) {
		scanf("%d", &request[i]);
	}
	move = move + abs(current-request[0]);
	printf("%d -> %d", current, request[0]);
	for(i=1; i<n; i++) {
		move += abs(request[i] - request[i-1]);
		printf(" -> %d", request[i]);
	}
	printf("\nTotal head movement = %d", move);
	getch();
	return 0;
}
