// #include <stdio.h>
// #include <unistd.h>
// #include <sys/wait.h>

// int main()
// {
//     if (fork() == 0)
//     {
//         printf("A");
//     }
//     else
//     {
//         pid_t pid;
//         if ((pid = fork()) == 0)
//         {
//             printf("B");
//         }
//         else
//         {
//             waitpid(pid, NULL, 0);
//             printf("C");
//         }
//     }
//     printf("D");
//     return 0;
// }




#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    if (fork() == 0) {
        if (fork() == 0) {
            printf("A");
        } else {
            wait(NULL);
            printf("B");
            exit(0);
        }
    } else {
        if (fork() == 0) {
            printf("C");
        } else {       
            printf("D");
            exit(0);
        }
    }
    printf("E");
    wait(NULL);
    return 0;
}