// Setup Includes & Libs
#include <stdio.h>

int main() {
    int matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int *ptr = matrix;
    printf("%d", ptr[4]);
    return 0;
}