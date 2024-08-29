/*

Name:  Richard Hoehn
Class: CSCI-6050
Lab:   02
Prob:  02
Date:  2024-08-29
Desc:  Permutation and Combination Output App

*/

// Setup Includes & Libs
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Function Declarations
int factorial(int n);

// Start Program
int main(int argc, char* argv[]){
    
    // Setup Varibales
    int n;
    int r; 
    
    // Make Sure I got two (2) values!
    if(argc == 2){
        printf("\n");
        printf("*** Missing Correct Argument Count of 2! ***\n");
        printf("\n");
        return -1;
    }

    // Get Args
    n = atoi(argv[1]); // Get "n"
    r = atoi(argv[2]); // Get "r"
 
    printf("Fac 'n' = %d\n", factorial(n));
    printf("Fac 'r' = %d\n", factorial(r));

    return 0;
}


int factorial(int n) {
    int factorial = 1;

    // Simple loop over the factorial
    for (int i = 1; i <= n; i++) {
        factorial *= i;
    }

    return factorial;
}
