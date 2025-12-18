#include <stdio.h>

typedef struct {
    int pid;
    int burst;
} process;

void waitingtime(process p[], int n, int waiting[], int quantum) {
    int rem_bt[n];
    int i;

    // Copy burst times
    for (i = 0; i < n; i++) {
        rem_bt[i] = p[i].burst;
        waiting[i] = 0;
    }

    int t = 0;   // current time

    while (1) {
        int done = 1;

        for (i = 0; i < n; i++) {
            if (rem_bt[i] > 0) {
                done = 0;  // process still remaining

                if (rem_bt[i] > quantum) {
                    t += quantum;
                    rem_bt[i] -= quantum;
                }
                else {
                    t += rem_bt[i];
                    waiting[i] = t - p[i].burst;
                    rem_bt[i] = 0;
                }
            }
        }

        if (done == 1)
            break;
    }
}

void turnaroundtime(process p[], int n, int waiting[], int turnaround[]) {
    int i;
    for (i = 0; i < n; i++) {
        turnaround[i] = p[i].burst + waiting[i];
    }
}

void calculateTime(process p[], int n, int quantum) {
    int waiting[n], turnaround[n], i;
    int totalwaiting = 0, totalturnaround = 0;

    waitingtime(p, n, waiting, quantum);
    turnaroundtime(p, n, waiting, turnaround);

    printf("\nProcess\t\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (i = 0; i < n; i++) {
        totalwaiting += waiting[i];
        totalturnaround += turnaround[i];
        printf("%d\t\t%d\t\t%d\t\t%d\n",
               p[i].pid, p[i].burst, waiting[i], turnaround[i]);
    }

    printf("\nAverage waiting time = %.2f", (float)totalwaiting / n);
    printf("\nAverage turnaround time = %.2f\n", (float)totalturnaround / n);
}

int main() {
    int n, quantum, i;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    process p[n];

    for (i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Burst Time for process %d: ", i + 1);
        scanf("%d", &p[i].burst);
    }

    printf("Enter quantum size: ");
    scanf("%d", &quantum);

    calculateTime(p, n, quantum);

    return 0;
}

