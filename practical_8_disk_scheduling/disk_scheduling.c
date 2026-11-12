#include <stdio.h>
#include <stdlib.h>

int cur;
int total;

void move(int to)
{
    total = total + abs(to - cur);
    cur = to;
    printf(" -> %d", cur);
}

void sort(int a[], int n)
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

void sstf(int req[], int n, int head)
{
    int done[50];
    int i, c;
    int pos = 0;
    int min;

    for (i = 0; i < n; i++)
    {
        done[i] = 0;
    }

    total = 0;
    cur = head;
    printf("\nSSTF seek sequence: %d", head);

    for (c = 0; c < n; c++)
    {
        min = 9999;
        for (i = 0; i < n; i++)
        {
            if (done[i] == 0 && abs(req[i] - cur) < min)
            {
                min = abs(req[i] - cur);
                pos = i;
            }
        }
        done[pos] = 1;
        move(req[pos]);
    }

    printf("\nSSTF total head movement = %d\n", total);
}

void scan(int req[], int n, int head, int size)
{
    int i;

    total = 0;
    cur = head;
    printf("\nSCAN seek sequence: %d", head);

    for (i = 0; i < n; i++)
    {
        if (req[i] >= head)
        {
            move(req[i]);
        }
    }

    move(size - 1);

    for (i = n - 1; i >= 0; i--)
    {
        if (req[i] < head)
        {
            move(req[i]);
        }
    }

    printf("\nSCAN total head movement = %d\n", total);
}

void clook(int req[], int n, int head)
{
    int i;

    total = 0;
    cur = head;
    printf("\nC-LOOK seek sequence: %d", head);

    for (i = 0; i < n; i++)
    {
        if (req[i] >= head)
        {
            move(req[i]);
        }
    }

    for (i = 0; i < n; i++)
    {
        if (req[i] < head)
        {
            move(req[i]);
        }
    }

    printf("\nC-LOOK total head movement = %d\n", total);
}

int main()
{
    int n, i, head, size;
    int req[50];

    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter request queue: ");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &req[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter disk size (total cylinders): ");
    scanf("%d", &size);

    sstf(req, n, head);

    sort(req, n);

    scan(req, n, head, size);
    clook(req, n, head);

    return 0;
}
