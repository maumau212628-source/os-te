#include <stdio.h>

int main()
{
    int n, m, i, j, k;
    int alloc[10][10];
    int max[10][10];
    int need[10][10];
    int avail[10];
    int finish[10];
    int safe[10];
    int count = 0;
    int found;
    int can_run;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    printf("Enter Allocation matrix:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("Enter Max matrix:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter Available resources: ");
    for (j = 0; j < m; j++)
    {
        scanf("%d", &avail[j]);
    }

    for (i = 0; i < n; i++)
    {
        finish[i] = 0;
        for (j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    printf("\nNeed matrix:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    while (count < n)
    {
        found = 0;

        for (i = 0; i < n; i++)
        {
            if (finish[i] == 0)
            {
                can_run = 1;

                for (j = 0; j < m; j++)
                {
                    if (need[i][j] > avail[j])
                    {
                        can_run = 0;
                    }
                }

                if (can_run == 1)
                {
                    for (k = 0; k < m; k++)
                    {
                        avail[k] = avail[k] + alloc[i][k];
                    }
                    safe[count] = i;
                    count++;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (found == 0)
        {
            printf("\nSystem is in UNSAFE state (deadlock possible)\n");
            return 0;
        }
    }

    printf("\nSystem is in SAFE state\n");
    printf("Safe sequence: ");
    for (i = 0; i < n; i++)
    {
        printf("P%d", safe[i]);
        if (i < n - 1)
        {
            printf(" -> ");
        }
    }
    printf("\n");

    return 0;
}
