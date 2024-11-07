#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
    pid_t pid;
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        /* Child process */
        printf("Hello from the child process!\n");
        exit(EXIT_SUCCESS);
    }
    else
    {
        /* Parent process */
        printf("Hello from the parent process!\n");
        exit(EXIT_SUCCESS);
    }
}