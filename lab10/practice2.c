#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    printf("I am: %d\n", (int)getpid());
    pid_t pid = fork();

    if (pid < 0)
    { /* error occurred */
        perror("Fork failed");
    }

    if (pid == 0)
    { /* child process */
        printf("Child 1 - Hello World!\n");

        pid_t pid = fork();
        if (pid == 0)
        { /* child process */
            printf("Child 2 - Hello World!\n");
            exit(0);
        }

        exit(0);
    }

    /* parent process */
    wait(NULL);
    printf("Parent Process is Exiting\n");
    return (0);
}