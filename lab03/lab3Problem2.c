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
#include <ctype.h>

// Setup Defines
#define MAX_WORDS 50
#define MAX_LETTERS 20

// Comparison function for Words!
// This is based on the link for the Lab guide: https://www.tutorialspoint.com/c_standard_library/c_function_qsort.htm
int compare(const void *arg1, const void *arg2){
   return strcasecmp(*(const char **)arg1, *(const char **)arg2);
}

int isVowel(const char *word){
    int resp;
    switch (word[0])
    {
        case 'A':
        case 'E':
        case 'I':
        case 'O':
        case 'U':
            resp = 1;
            break;
        default:
            resp = 0;
            break;
    }

    return resp;
}

int main()
{
    // Set Variables
    char buffer[MAX_WORDS * MAX_LETTERS + 1]; // Add the +1 for spaces...
    const char delim[] = " "; // Set the delimiter
    char *word; // Temp Word holder

    int wordCnt = 0;
    char *words[MAX_WORDS];

    // Ask user to give us a sentence!
    printf("Enter a line of text: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }

    // Start teh processing
    printf("Words starting with vowels:\n");

    // Convert ALL to Upper Case - Just looper over the entire buffer
    for(int i=0; i < sizeof(buffer); i++){
        buffer[i] = toupper(buffer[i]);
    }

    // Get "Words"
    word = strtok(buffer, delim);
   
    // Loop over "word" until NULL
    while( word != NULL ) {

        // Check for Newline  and Remove!
        int size = strlen(word);
        if (word[size - 1] == '\n'){
            word[size - 1] = '\0';
        }

        // Check if Word stars with a Vowel!
        if(isVowel(word) == 1) {

            // Dynamically allocate memory and copy the word into the "words" array!
            words[wordCnt] = (char *)malloc((strlen(word) + 1) * sizeof(char));
            strcpy(words[wordCnt], word);  // Copy the "word" to "words"
            wordCnt = wordCnt + 1; // Incrment the counter!
        }

        // Get next word
        word = strtok(NULL, delim);
    }

    // Use qsort to sort our "words"
    qsort(words, wordCnt, sizeof(char *), compare);

    // Print the "words" from teh sort!
    for(int i = 0; i < wordCnt; i++){
        printf("%s\n", words[i]);
    }

    return 0;
}