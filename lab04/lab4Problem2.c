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
#include <string.h>

// Setup Defines
#define MAX_LETTERS 256




// Start Application
int main(int argc, char* argv[]){

    // Set Variables
    char username[MAX_LETTERS];
    char password[MAX_LETTERS];

    FILE *fp;
    char *filename = "userdata.txt";

    // Make user Userdata File is Avaiable!
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Userdata File Missing!\n");
        return 1;
    }

    // Ask user to give us a sentence!
    printf("Username: ");
    if (fgets(username, sizeof(username), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }

    printf("Password: ");
    if (fgets(password, sizeof(password), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }

    // Check input Length
    if(strlen(username) < 2){
        printf("No Username provided!\n");
        return 1;
    }
     if(strlen(password) < 2){
        printf("No Password provided!\n");
        return 1;
    }

    


    printf("Size %lu\n", strlen(username));

    //printf("Username & Password: %c-%c", username, password);

    // Close Userdata File
    fclose(fp);

    return 0;
}