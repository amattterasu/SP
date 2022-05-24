#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

struct Ball
{
    int x;
    int y;
};

int main()
{
    printf("\n\n -- FIRST --\n\n");
    int count = 0;
    pid_t pid;

    while (true)
    {
        printf("PARENT: Enter count (1 - 10)\n");
        scanf("%d", &count);
        if (count <= 10 && count > 0)
            break;

        printf("PARENT: Enter count (1 - 10)\n");
    }

    Ball *balls = new Ball[count];

    for (int i = 0; i < count; ++i)
    {
        balls[i].x = rand() % 10;
        balls[i].y = rand() % 10;
    }

    int rv;
    for (int i = 0; i < count; i++)
    {
        pid = fork();
        if (pid == 0)
        {
            rv = i;
            break;
        }
        printf("PARENT: PARENT created CHILDREN with PID = %d and ID = %d\n", pid, i);
    }

    switch (pid)
    {
    case -1:
        perror("fork");
        exit(1);
    case 0:
        printf("CHILDREN: PID = %d\n", getpid());
        printf("CHILDREN: ID = %d\n", rv);

        char tempX[2];
        char tempY[2];
        char tempID[2];
        tempX[0] = balls[rv].x + '0';
        tempX[1] = 0;
        tempY[0] = balls[rv].y + '0';
        tempY[1] = 0;
        tempID[0] = rv + '0';
        tempID[1] = 0;

        execl("second", "second", &tempX, &tempY, tempID, NULL);
        exit(0);
    default:
        printf("PARENT: completed creating CHILDREN\n");
        printf("PARENT: PARENTS PID = %d\n", getpid());

        for (int i = 0; i < count; i++)
        {
            wait(&rv);
            printf("\nPARENT: CHILDREN exit сode = %d\n", WEXITSTATUS(rv));
        }
    }
}