/*

Name:  Richard Hoehn
Class: CSCI-6050
Proj:  01
Date:  2024-09-09
Desc:  Hex Creater App - Similar to the xxd command.

*/

// Setup Includes & Libs
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


// Start Program
int main(int argc, char* argv[]){
    // Setup main varibles
    char * filename;
    FILE * file;
    char fileChar;
    int  fileCharCount = 0;
    char hexCharArr[16];
    char strCharArr[16];
    unsigned char buffer[17];
    

    // Make Sure I got a Filename
    if(argc != 2){
        printf("\n");
        printf("*** Missing File to open! ***\n");
        printf("\n");
        return -1;
    }

    // Get Filename to open from Argument
    filename = argv[1];

    // Opening text file - READ-ONLY
    file = fopen(filename, "r");

    // Check if File was opened? Fail if it was not!
    if (file == NULL) {
        printf("Error in opening file");
        return 1;
    }

    while(fread(buffer, 16, 1, file) != 0){
        
        printf("%08x: ", fileCharCount);
        fileCharCount = fileCharCount + 16;

        for(int i=0; i < 16; i++)
        {
            printf("%02x%02x ", buffer[i], buffer[i+1]);
            i = i + 1;
            
        }

        // Spacer
        printf(" ");
        
        for(int j = 0; j < 16; j++)
        {
            if(isprint(buffer[j]))
                printf("%c", buffer[j]);
            else
                printf(".");
        }

        // Got to NEXT line
        printf("\n");
    }

    // Close File - Important for memory management
    fclose(file);

    // Close App - All good.
    return 0;
}
