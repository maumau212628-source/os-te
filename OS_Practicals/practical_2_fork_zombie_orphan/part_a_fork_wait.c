#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void sort_ascending(int a[], int n)
{
    int i, j, temp;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - 1 - i; j++)
        {
            if (a[j] > a[j + 1])
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

void sort_descending(int a[], int n)
{
    int i, j, temp;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - 1 - i; j++)
        {
            if (a[j] < a[j + 1])
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

void show(int a[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main()
{
    int n, i;
    int a[50];
    int pid;

    printf("Enter number of integers: ");
    scanf("%d", &n);

    printf("Enter %d integers: ", n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }

    pid = fork();

    if (pid == 0)
    {
        sort_ascending(a, n);
        printf("Child (ascending): ");
        show(a, n);
    }
    else
    {
        wait(NULL);
        sort_descending(a, n);
        printf("Parent (descending): ");
        show(a, n);
    }

    return 0;
}
