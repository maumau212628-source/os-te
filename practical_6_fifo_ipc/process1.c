#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define FIFO1 "/tmp/fifo1"
#define FIFO2 "/tmp/fifo2"

int main()
{
    char text[1000] = "";
    char line[200];
    char result[1000];
    int fd1, fd2, n;

    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    printf("Enter sentences (empty line to stop):\n");
    while (fgets(line, sizeof(line), stdin) != NULL && line[0] != '\n')
    {
        strcat(text, line);
    }

    fd1 = open(FIFO1, O_WRONLY);
    write(fd1, text, strlen(text));
    close(fd1);

    fd2 = open(FIFO2, O_RDONLY);
    n = read(fd2, result, sizeof(result) - 1);
    result[n] = '\0';
    close(fd2);

    printf("\nResult received from Process 2:\n%s", result);

    return 0;
}
