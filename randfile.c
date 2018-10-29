#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

int *rand_int(int n)
{
    int f = open("/dev/urandom", O_RDONLY);
    if (f < 0)
    {
        return 0;
    }
    unsigned int *arr = malloc(sizeof(int) * n);
    if (read(f, arr, sizeof(int) * n) < 0)
    {
        return 0;
    }
    close(f);
    return arr;
}

int main()
{
    int NUM = 10;

    int i;
    int *p = rand_int(NUM);
    if (!p)
    {
        printf("Error %d: %s\n", errno, strerror(errno));
        return 1;
    }

    printf("Randomly generated numbers:\n");
    for (i = 0; i < NUM; i++)
    {
        printf("Random int #%d: %u\n", i, p[i]);
    }

    int f = open("temp", O_RDWR | O_CREAT | O_TRUNC, 0600);
    if (f < 0)
    {
        printf("Error %d: %s\n", errno, strerror(errno));
    }
    
    printf("Writing to file..\n");
    if (write(f, p, sizeof(int) * NUM) < 0)
    {
        printf("Error %d: %s\n", errno, strerror(errno));
        return 1;
    }

    printf("Reading from file..\n");
    if (read(f, p, sizeof(int) * NUM) < 0)
    {
        printf("Error %d: %s\n", errno, strerror(errno));
        return 1;
    }

    for (i = 0; i < NUM; i++)
    {
        printf("Reading int #%d: %u\n", i, p[i]);
    }

    free(p);
    return 0;
}
