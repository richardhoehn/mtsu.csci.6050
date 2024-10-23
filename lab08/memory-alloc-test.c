// Meory Allocation Tests
#include <stdio.h>
#include <stdlib.h>


int main() {
    printf("Testing Memory Allocations!\n");

    // Start Here!
    int *mallocPtr = malloc(500* sizeof(int));

    mallocPtr[0] = 55;

    printf("Malloc Ptr[0] = %d\n", mallocPtr[0]);


    // Free
    free(mallocPtr);

    mallocPtr[0] = 44;


    printf("Malloc Ptr[0] = %d\n", mallocPtr[0]);

    // char *str;

    // printf("1.\n");

    // str = malloc(5);

    // printf("2.\n");

    // str = "Hello"; 

    // printf("3.\n");

    // printf("Text: %s\n", str);

    // printf("4.\n");

    // free(str);

    // printf("5.\n");

    // int *arr;
    // arr = malloc(3 * sizeof(int));
    // arr[3] = 42; 

    // free(arr);

    // int *arr = malloc(5 * sizeof(int));
    // free(arr);
    // arr[2] = 10; 

    // printf("arr[2] = %d\n", arr[2]);

    // int *arr2;
    // for (int i = 0; i < 5; i++) {
    //     arr2[i] = i; 
    // }

    // int *arr;
    // arr = malloc(3 * sizeof(int));
    // arr = malloc(5 * sizeof(int)); 

    // free(arr);

    int *ptr;
    free(ptr); 

    return 0;
}