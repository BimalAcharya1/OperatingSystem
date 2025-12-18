#include <stdio.h>
#include <conio.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int main()
{
    int i, j, k, n, m;
    int available[MAX_RESOURCES];
    int max_claim[MAX_PROCESSES][MAX_RESOURCES];
    int allocation[MAX_PROCESSES][MAX_RESOURCES];
    int need[MAX_PROCESSES][MAX_RESOURCES];
    int work[MAX_RESOURCES];
    int finish[MAX_PROCESSES];
    int safe_sequence[MAX_PROCESSES];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the number of resources: ");
    scanf("%d", &m);

    printf("Enter the available instances of each resource:\n");
    for (i = 0; i < m; i++) {
        printf("Resource %d: ", i + 1);
        scanf("%d", &available[i]);
    }

    printf("Enter the maximum claim for each process:\n");
    for (i = 0; i < n; i++) {
        printf("Process %d:\n", i + 1);
        for (j = 0; j < m; j++) {
            printf("Resource %d: ", j + 1);
            scanf("%d", &max_claim[i][j]);
        }
    }

    printf("Enter the allocation for each process:\n");
    for (i = 0; i < n; i++) {
        printf("Process %d:\n", i + 1);
        for (j = 0; j < m; j++) {
            printf("Resource %d: ", j + 1);
            scanf("%d", &allocation[i][j]);
            need[i][j] = max_claim[i][j] - allocation[i][j];   // FIXED
        }
    }

    // Initialize work = available
    for (i = 0; i < m; i++) {
        work[i] = available[i];
    }

    // Initialize finish array
    for (i = 0; i < n; i++) {
        finish[i] = 0;
    }

    int count = 0;

    while (count < n) {
        int found = 0;

        for (i = 0; i < n; i++) {
            if (finish[i] == 0) {

                // Check if need <= work
                for (j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        break;
                    }
                }

                // If all resources can be allocated
                if (j == m) {
                    for (k = 0; k < m; k++) {
                        work[k] += allocation[i][k];
                    }

                    safe_sequence[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (found == 0) {
            break;
        }
    }

    if (count == n) {
        printf("\nSystem is in a safe state and safe sequence is: ");
        for (i = 0; i < n; i++) {
            printf("%d ", safe_sequence[i] + 1);
        }
        printf("\n");
    } else {
        printf("\nSystem is in an unsafe state.\n");
    }
    getch();
    return 0;
}

