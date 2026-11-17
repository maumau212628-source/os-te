
#include <stdio.h>
#include <stdlib.h>

int cur, total;

void move(int x)
{
    total = total + abs(x - cur);
    cur = x;
    printf(" -> %d", cur);
}

void sort(int a[], int n)
{
    int t;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
            }
        }
    }
}

void sstf(int a[], int n, int head)
{
    int done[50], min, pos;

    for (int i = 0; i < n; i++)
        done[i] = 0;

    cur = head;
    total = 0;

    printf("\nSSTF: %d", head);

    for (int i = 0; i < n; i++)
    {
        min = 9999;

        for (int j = 0; j < n; j++)
        {
            if (done[j] == 0)
            {
                if (abs(a[j] - cur) < min)
                {
                    min = abs(a[j] - cur);
                    pos = j;
                }
            }
        }

        done[pos] = 1;
        move(a[pos]);
    }

    printf("\nTotal movement = %d\n", total);
}

void scan(int a[], int n, int head, int size)
{
    cur = head;
    total = 0;

    printf("\nSCAN: %d", head);

    for (int i = 0; i < n; i++)
    {
        if (a[i] >= head)
            move(a[i]);
    }

    move(size - 1);

    for (int i = n - 1; i >= 0; i--)
    {
        if (a[i] < head)
            move(a[i]);
    }

    printf("\nTotal movement = %d\n", total);
}

void clook(int a[], int n, int head)
{
    cur = head;
    total = 0;

    printf("\nC-LOOK: %d", head);

    for (int i = 0; i < n; i++)
    {
        if (a[i] >= head)
            move(a[i]);
    }

    for (int i = 0; i < n; i++)
    {
        if (a[i] < head)
            move(a[i]);
    }

    printf("\nTotal movement = %d\n", total);
}

int main()
{
    int a[50], n, head, size;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter request queue: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter disk size: ");
    scanf("%d", &size);

    sort(a, n);

    sstf(a, n, head);
    scan(a, n, head, size);
    clook(a, n, head);

    return 0;
}
