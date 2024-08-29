/*

Name:  Richard Hoehn
Class: CSCI-6050
Lab:   02
Prob:  02
Date:  2024-08-29
Desc:  Permutation and Combination Output App

*/

// Setup Inclddes & Libs
#include <stdio.h>

// Function Declarations
long factorial(long n);

// Start Program
int main(int argc, char* argv[]){
    
    // Setup Varibales
    long n; // Using "long" due to factorial size
    long r; // Using "long" due to factorial size
    
    // Make Sure I got two (2) valdes!
    if(argc == 2){
        printf("\n");
        printf("*** Missing Correct Argument Count of 2! ***\n");
        printf("\n");
        return -1;
    }

    // Get Args
    n = atoi(argv[1]); // Get "n"
    r = atoi(argv[2]); // Get "r"

    // Check "n""
    if(n < 1 || n > 20){
        printf("\n");
        printf("*** Input of 'n' Incorrect! ***\n");
        printf("\n");
        return -1;
    }

    // Check "r"
    if(r < 1 || r > 20){
        printf("\n");
        printf("*** Input of 'r' Incorrect! ***\n");
        printf("\n");
        return -1;
    }

    if(r > n){
        printf("\n");
        printf("Error: r should be less than or equal to n\n");
        printf("\n");
        return -1;
    }

    long p = factorial(n) / factorial(n-r);
    long c = p / factorial(r);
 
    printf("P(%ld,%ld) = %ld\n", n, r, p);
    printf("C(%ld,%ld) = %ld\n", n, r, c);

    return 0;
}


long factorial(long n) {
    long factorial = 1;

    // Simple loop over the factorial - it gets big quick!
    for (int i = 1; i <= n; i++) {
        factorial *= i;
    }

    return factorial;
}
