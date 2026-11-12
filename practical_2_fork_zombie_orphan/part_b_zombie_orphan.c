#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int choice;
    int pid;

    printf("1. Zombie process\n");
    printf("2. Orphan process\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    pid = fork();

    if (pid < 0)
    {
        printf("Fork failed\n");
        exit(1);
    }

    if (choice == 1)
    {
        if (pid == 0)
        {
            printf("Child %d is exiting\n", getpid());
            exit(0);
        }
        else
        {
            printf("Parent %d is sleeping, not calling wait\n", getpid());
            sleep(3);
            printf("Look for Z (zombie) in the S column:\n");
            system("ps -l");
            wait(NULL);
            printf("Zombie removed. Parent exiting\n");
        }
    }
    else if (choice == 2)
    {
        if (pid == 0)
        {
            printf("Child %d, parent is %d\n", getpid(), getppid());
            sleep(3);
            printf("Child is now an orphan, new parent is %d\n", getppid());
        }
        else
        {
            sleep(1);
            printf("Parent %d is exiting without wait\n", getpid());
            exit(0);
        }
    }
    else
    {
        printf("Invalid choice\n");
    }

    return 0;
}
