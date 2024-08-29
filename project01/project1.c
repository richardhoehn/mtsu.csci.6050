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
    unsigned char buffer[16];
    int readBufferSize;
    

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

    // Loop
    while(!feof(file)){

        // Read (try) 16 chars into the buffer. 
        // I get the size read so I can keep track of how to display
        readBufferSize = (int)fread(buffer, 1, 16, file);

        // Exit out if we did not read anything!
        if(readBufferSize == 0){break;}

        // Print the Char read count
        printf("%08x: ", fileCharCount);
        fileCharCount = fileCharCount + readBufferSize;

        // Loop over the Read Buffer!
        for(int i=0; i < readBufferSize; i++)
        {
            printf("%02x", buffer[i]);
            if(i != 0 && (i % 2) == 1){
                printf(" ");
            }
            
        }

        // Expand spacing if the Buffer is less than 16
        for(int i=readBufferSize; i < 16; i++){
            printf("  ");
            if(i != 0 && (i % 2) == 1){
                printf(" ");
            }
        }
        

        // Spacer
        printf(" ");
        
        for(int j = 0; j < readBufferSize; j++)
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
