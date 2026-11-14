
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define FIFO1 "/tmp/fifo1"
#define FIFO2 "/tmp/fifo2"

int main()
{
    char text[1000], result[200];
    int fd1, fd2, i, n;
    int chars = 0, words = 0, lines = 0, inword = 0;
    FILE *fp;

    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    printf("Waiting for data...\n");

    fd1 = open(FIFO1, O_RDONLY);
    n = read(fd1, text, sizeof(text) - 1);
    text[n] = '\0';
    close(fd1);

    for (i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == '\n')
            lines++;
        else
            chars++;

        if (text[i] == ' ' || text[i] == '\n')
            inword = 0;
        else if (inword == 0)
        {
            words++;
            inword = 1;
        }
    }

    fp = fopen("result.txt", "w");
    fprintf(fp, "Characters = %d\nWords = %d\nLines = %d\n", chars, words, lines);
    fclose(fp);

    fp = fopen("result.txt", "r");
    n = fread(result, 1, sizeof(result) - 1, fp);
    result[n] = '\0';
    fclose(fp);

    fd2 = open(FIFO2, O_WRONLY);
    write(fd2, result, strlen(result));
    close(fd2);

    printf("Result saved and sent to Process 1.\n");

    return 0;
}
