#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


void bubbleSort(int arr[], int n)
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

void display(int arr[], int n)
{
    int i;

    for(i = 0; i < n; i++)
        printf("%d ", arr[i]);

    printf("\n");
}


int main()
{
    int choice, n, i;
    pid_t pid;


    printf("1. Zombie Process\n");
    printf("2. Orphan Process\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);


    printf("Enter number of elements: ");
    scanf("%d", &n);


    int arr[n];

    printf("Enter elements:\n");

    for(i = 0; i < n; i++)
        scanf("%d", &arr[i]);



    if(choice == 1)
    {
        pid = fork();


        if(pid == 0)
        {
            printf("\n----- Child Process -----\n");
            printf("Child PID: %d\n", getpid());

            bubbleSort(arr, n);
            printf("Sorted Array by Child: ");
            display(arr, n);

            printf("Child exiting...\n");

            exit(0);
        }

        else
        {
            printf("\n----- Parent Process -----\n");
            printf("Parent PID: %d\n", getpid());
            sleep(10);
            printf("LOOK for Z");
            system("ps -l");

            bubbleSort(arr, n);
            printf("Sorted Array by Parent: ");
            display(arr, n);
            wait(NULL);
            printf("zombie removed");
        }
    }



    else if(choice == 2)
    {
        pid = fork();


        if(pid == 0)
        {
            sleep(5);

            printf("\n----- Child Process -----\n");
            printf("Child PID: %d\n,,New Parent PID: %d\n", getpid(),getppid());

            
            bubbleSort(arr, n);
            printf("Sorted Array by Child: ");
            display(arr, n);
            sleep(2);
            printf("Parent eexiting ,child orphan ,new pid is %d",getppid());
        }


        else
        {
            printf("\n----- Parent Process -----\n");
            printf("Parent exit Parent PID: %d\n", getpid());

            bubbleSort(arr, n);
            printf("Sorted Array by Parent: ");
            display(arr, n);

            exit(0);
        }
    }


    else
    {
        printf("Invalid Choice!\n");
    }


    return 0;
}
