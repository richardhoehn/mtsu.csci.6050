// Setup Includes & Libs
#include <stdio.h>

// Start Program
int main(){
    int a = 7;
    int *c = &a;
    c = c+0;
    printf("%p\n",&a);
    printf("%x\n",c);
}

