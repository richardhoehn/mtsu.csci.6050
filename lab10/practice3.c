#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int num = 0;
    int fact = 1;
    int i;

    printf("I am: %d\n", (int)getpid());
    pid_t pid = fork();

    if (pid < 0)
    { /* error occurred */
        perror("Fork failed");
    }

    if (pid == 0)
    { /* child process */
        printf("Child 1 - Enter Number: ");

        // Make sure Input is a Number!
        scanf("%d", &num);

        // Clear any additional leftover characters in the buffer
        while (getchar() != '\n');

        int fact = 1, i;

        // Loop from 1 to N to get the factorial
        for (i = 1; i <= num; i++)
        {
            fact *= i;
        }

        printf("Factorial for %d is %d\n", num, fact);

        exit(0);
    }

    /* parent process */
    wait(NULL);
    printf("Parent Process is Exiting\n");
    return (0);
}