/*

Name:  Richard Hoehn
Class: CSCI-6050
Lab:   04
Prob:  02
Date:  2024-09-10
Desc:  Checkig Username and Password

*/

// Setup Includes & Libs
#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Setup Defines
#define MAX_LETTERS 128
#define USERDATA "userdata.txt"

// Start Application
int main(int argc, char *argv[])
{

    // Set Variables
    char username[MAX_LETTERS];
    char password[MAX_LETTERS];

    FILE *fp;
    char *filename = USERDATA;
    char line[MAX_LETTERS + MAX_LETTERS + MAX_LETTERS]; // Made it 3x the size of the Letters Max
    const char delim[] = " ";                           // Set the delimiter
    char *word;                                         // Temp Word holder
    int cmpRes;
    int found = 0;

    // Make user Userdata File is Avaiable!
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Userdata File Missing!\n");
        return 1;
    }

    // Ask user to give username and password
    printf("Username: ");
    scanf("%s", username);

    printf("Password: ");
    scanf("%s", password);

    // Iterate of Userdata to Find User and Pwd
    while (fgets(line, sizeof(line), fp))
    {
        // Get Username from Line
        word = strtok(line, delim);
        cmpRes = strcmp(username, word);
        if (cmpRes != 0)
        {
            continue;
        }

        // Get Password from Line
        word = strtok(NULL, delim);
        cmpRes = strcmp(password, word);
        if (cmpRes != 0)
        {
            continue;
        }

        // Get Value
        word = strtok(NULL, delim);
        printf("The amount is: %s", word);
        found = 1;
    }

    if(found == 0){
        printf("username/password missmatch!!!\n");
    }

    // Close Userdata File
    fclose(fp);

    return 0;
}