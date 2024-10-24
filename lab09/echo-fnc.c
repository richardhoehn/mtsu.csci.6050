#include "csapp.h"

// Bad Way of Coding - We should ALWAYS use a buffer for the char!


int main(void)
{
    char c;

    while(Read(STDIN_FILENO, &c, 1) != 0){
        Write(STDOUT_FILENO, &c, 1);
    }

    return 0;
}