#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

int *rand_int(int n)
{
    int f = open("/dev/random", O_RDONLY);
    if (f < 0)
    {
        printf("Error %d: %s\n", errno, strerror(errno));
        return 0;
    }

    unsigned int *arr = malloc(sizeof(int) * n);

    int e = read(f, arr, sizeof(int) * n);
    if (e < 0)
    {
        printf("Error %d: %s\n", errno, strerror(errno));
        return 0;
    }

    int i = 0;
    for (i = 0; i < n; i++)
    {
        printf("Random int #%d: %u\n", i, arr[i]);
    }
    close(f);
    return arr;
}

int main()
{
    int f = open("temp", O_CREAT | O_RDWR, 0600);
    int e;
    
    e = write(f, rand_int(10), sizeof(int) * 10);
    if (e < 0)
    {
        printf("Error %d: %s\n", errno, strerror(errno));
        return 0;
    }

    return 0;
}
