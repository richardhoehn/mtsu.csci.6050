/*

Name:  Richard Hoehn
Class: CSCI-6050
Lab:   02
Prob:  01
Date:  2024-08-29
Desc:  Print a Decending and Acending Cube

*/

// Setup Includes & Libs
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


// Start Program
int main(int argc, char* argv[]){
    // Setup Variables
    int iterator;
    
    // Make Sure I got a Value!
    if(argc == 1){
        printf("\n");
        printf("*** Missing Single Argument! ***\n");
        printf("\n");
        return -1;
    }

    // Set Iterator
    iterator = atoi(argv[1]);

    // Check for Number
    if(iterator < 1 || iterator > 9){
        printf("\n");
        printf("*** Input Incorrect! ***\n");
        printf("\n");
        return -1;
    }

    // Set size of Matrix
    int size = 2 * iterator - 1;

    // Declare a 2D array for Numbers
    int matrix[size][size];

    // Lop the Matrix!
    for (int layer = 0; layer < iterator; layer++) {

        // Loop the Layer - It increments as we move down!
        for (int i = layer; i < size - layer; i++) {

            int mirror = size - layer - 1;
            int val = iterator - layer;

            matrix[layer][i] = val;   // Top row
            matrix[mirror][i] = val;  // Bottom row

            matrix[i][layer]  = val;  // Left column
            matrix[i][mirror] = val;  // Right column
        }
    }

    // Print the matrix
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}
