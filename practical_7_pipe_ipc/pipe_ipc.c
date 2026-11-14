
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main()
{
    int p1[2], p2[2];
    int n, fd, pid;
    char path[100];
    char buf[1000];

    pipe(p1);
    pipe(p2);

    pid = fork();

    if (pid > 0)
    {
        close(p1[0]);
        close(p2[1]);

        printf("Enter file pathname: ");
        scanf("%s", path);

        write(p1[1], path, strlen(path) + 1);
        close(p1[1]);

        printf("\nContents of file:\n");

        n = read(p2[0], buf, sizeof(buf));
        write(1, buf, n);

        close(p2[0]);
        wait(NULL);
    }
    else if (pid == 0)
    {
        close(p1[1]);
        close(p2[0]);

        read(p1[0], path, sizeof(path));
        close(p1[0]);

        fd = open(path, O_RDONLY);

        if (fd < 0)
        {
            strcpy(buf, "File not found\n");
            write(p2[1], buf, strlen(buf));
        }
        else
        {
            n = read(fd, buf, sizeof(buf));
            write(p2[1], buf, n);
            close(fd);
        }

        close(p2[1]);
    }

    return 0;
}
