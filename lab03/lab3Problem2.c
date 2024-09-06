/*

Name:  Richard Hoehn
Class: CSCI-6050
Lab:   03
Prob:  02
Date:  2024-09-06
Desc:  Sort And Determine Vovels

*/

// Setup Includes & Libs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Setup Defines
#define MAX_WORDS 50
#define MAX_LETTERS 20

// Comparison function
int compare(const void *arg1, const void *arg2){
   return strcasecmp(*(const char **)arg1, *(const char **)arg2);
}

int main()
{
    // Set Variables
    char buffer[MAX_WORDS * MAX_LETTERS + 1];
    const char delim[] = " ";
    char *token;


    printf("Enter a line of text: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
       printf("Error reading input.\n");
        return 1;
    }

    // Convert ALL to Upper Case
    int j = 0;
    char tempChar;
 
    while (buffer[j]) {
        tempChar = buffer[j];
        buffer[j] = toupper(tempChar);
        j++;
    }

    
    

    /* get the first token */
    token = strtok(buffer, delim);
   
    /* walk through other tokens */
    while( token != NULL ) {
        printf( "%s\n", token );
    
        token = strtok(NULL, delim);
    }

    
    return 0;
}