#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>

int main() {
    int i, n, k, request[50], move = 0, cp, index[50], min, a[50], j = 0, mini, cp1;

    printf("Enter the current position: ");
    scanf("%d", &cp);
    cp1 = cp;

    printf("Enter the number of requests: ");
    scanf("%d", &n);

    printf("Enter the request order: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &request[i]);
    }

    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
            index[i] = abs(cp - request[i]);
        }

        min = index[0];
        mini = 0;

        for (i = 1; i < n; i++) {
            if (min > index[i]) {
                min = index[i];
                mini = i;
            }
        }

        a[j] = request[mini];
        j++;
        cp = request[mini];
        request[mini] = 999;  // mark as processed
    }

    printf("\nSequence is: ");
    printf("%d", cp1);
    move = move + abs(cp1 - a[0]);
    printf(" -> %d", a[0]);

    for (i = 1; i < n; i++) {
        move = move + abs(a[i] - a[i - 1]);
        printf(" -> %d", a[i]);
    }

    printf("\nTotal head movement = %d\n", move);

    getch();
    return 0;
}

