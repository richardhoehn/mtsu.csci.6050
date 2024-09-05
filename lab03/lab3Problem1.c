/*

Name:  Richard Hoehn
Class: CSCI-6050
Lab:   03
Prob:  01
Date:  2024-09-05
Desc:  Reverse an array of integers

*/

// Setup Includes & Libs
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, *arr, i;
    //getting the size of array
    scanf("%d", &n);
    arr = (int*) malloc(n * sizeof(int));

    //getting the element of the array
    for(i = 0; i < n; i++) {
        scanf("%d", arr + i);
    }

    //TODO: Write the logic to reverse the array "arr" here

    // START - Here
    int half; // Get half the array!
    half = n / 2; // Get half the array!

    for(i = 0; i < half; i++) {
        int temp;
        temp = arr[i];
        arr[i] = arr[n-i-1];
        arr[n-i-1] = temp;
    }
    
    //END TODO
      
    // Printing the resulting reversed array
    for(i = 0; i < n; i++)
        printf("%d ", *(arr + i));
    printf("\n");
    return 0;
}