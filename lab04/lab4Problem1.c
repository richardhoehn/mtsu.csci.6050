/*

Name:  Richard Hoehn
Class: CSCI-6050
Lab:   04
Prob:  01
Date:  2024-09-10
Desc:  Readinga File and Output Chars

*/

// Setup Includes & Libs
#include <stdio.h>
#include <ctype.h>

// Start Application
int main(int argc, char* argv[]){

    // Setup Vars
    FILE *fp;     // File Pointer
    char ch;      // Char that is read one-by-one
    char arr[11]; // Array of 10 chars + NullPointer
    int cnt = 0;  // Counter

    // Make Sure I got a Arg Value!
    if(argc != 2){
        printf("\n");
        printf("*** Missing Correcy Argument Count! ***\n");
        printf("\n");
        return -1;
    }

    // Open File for reading!
    fp = fopen( argv[1], "r" ); 

    // Check open File!
    if ( fp == 0 ) 
    { 
        printf("Error - No File to open!\n");
        return 1; 
    } 

    // File is Open - Read Char by Char
    while ((ch = fgetc(fp) )!= EOF) {

        if(isprint(ch))
            arr[cnt] = ch; // Set the Char
        else
            arr[cnt] = '.';

        // Always Set the end!
        arr[cnt+1] = '\0'; // Set the Null-Pointer

        // Increment Counter
        cnt = cnt + 1;
        
        // Check if Buffer is Full.
        if(cnt == 10){
            printf("%s\n", arr);
            cnt = 0; // Set the counter!
        }
    }

    // Check for Remaining Chars!
    if(cnt != 0){
        printf("%s\n", arr);
    }

    // Close File (pointer)
    fclose(fp); 

    return 0;
}