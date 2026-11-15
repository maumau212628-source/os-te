
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Ascending Order Function
void ascending(int arr[], int n)
{
    int i, j, temp;

    for(i = 0; i < n - 1; i++)
    {
        for(j = 0; j < n - i - 1; j++)
        {
            if(arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Descending Order Function
void descending(int arr[], int n)
{
    int i, j, temp;

    for(i = 0; i < n - 1; i++)
    {
        for(j = 0; j < n - i - 1; j++)
        {
            if(arr[j] < arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Display Function
void display(int arr[], int n)
{
    int i;

    for(i = 0; i < n; i++)
        printf("%d ", arr[i]);

    printf("\n");
}

int main()
{
    int choice;
    pid_t pid;

    printf("1. Fork and Wait (Sorting)\n");
    printf("2. Zombie Process\n");
    printf("3. Orphan Process\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch(choice)
    {
        // Fork and Wait - Sorting
        case 1:
        {
            int n, i;

            printf("Enter number of elements: ");
            scanf("%d", &n);

            if(n <= 0)
            {
                printf("Invalid number of elements!\n");
                break;
            }

            int arr[n];

            printf("Enter the elements:\n");

            for(i = 0; i < n; i++)
                scanf("%d", &arr[i]);

            pid = fork();

            if(pid < 0)
            {
                printf("Fork Failed!\n");
                exit(1);
            }

            else if(pid == 0)
            {
                printf("\n----- Child Process -----\n");
                printf("Child PID: %d\n", getpid());

                ascending(arr, n);

                printf("Sorted Array by Child (Ascending): ");
                display(arr, n);

                exit(0);
            }

            else
            {
                wait(NULL);

                printf("\n----- Parent Process -----\n");
                printf("Parent PID: %d\n", getpid());

                descending(arr, n);

                printf("Sorted Array by Parent (Descending): ");
                display(arr, n);
            }

            break;
        }

        // Zombie Process
        case 2:
        {
            pid = fork();

            if(pid < 0)
            {
                printf("Fork Failed!\n");
                exit(1);
            }

            else if(pid == 0)
            {
                printf("\nChild Process\n");
                printf("PID = %d\n", getpid());
                printf("Child exiting...\n");
                exit(0);
            }

            else
            {
                printf("\nParent Process\n");
                printf("PID = %d\n", getpid());
                printf("Sleeping for 10 seconds...\n");

                sleep(10);

                printf("Parent exiting...\n");
            }

            break;
        }

        // Orphan Process
        case 3:
        {
            pid = fork();

            if(pid < 0)
            {
                printf("Fork Failed!\n");
                exit(1);
            }

            else if(pid > 0)
            {
                printf("\nParent Process\n");
                printf("PID = %d\n", getpid());
                printf("Parent exiting...\n");

                exit(0);
            }

            else
            {
                sleep(5);

                printf("\nChild Process\n");
                printf("PID = %d\n", getpid());
                printf("New Parent PID = %d\n", getppid());

                printf("Child became an Orphan Process.\n");
            }

            break;
        }

        default:
            printf("Invalid Choice!\n");
    }

    return 0;
}
