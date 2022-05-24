#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    printf("-- SECOND --\n");
    printf("CHILDREN %s: get %d parameters: ", argv[3], argc);
    for (int i = 0; i < argc; i++)
        printf("%s ", argv[i]);

    if (argc != 4)
    {
        printf("CHILDREN %s: ERROR in paremeters\n\n", argv[3]);
        
        exit(-1);
    }
    int x = (int)*argv[1] - '0';
    int y = (int)*argv[2] - '0';

    int offsetX = x + (rand() % 101) - 50;
    int offsetY = y + (rand() % 101) - 50;

    if (offsetY < 0)
    {
        printf("\nCHILDREN %s: move from (%d, %d) to (%d, %d) and DESTROY\n",
               argv[3], x, y, offsetX, offsetY);

        exit(1);
    }

    printf("CHILDREN %s: move from (%d, %d) to (%d, %d)\n",
           argv[3], x, y, offsetX, offsetY);

    exit(0);
}