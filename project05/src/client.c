/*

Name:  Richard Hoehn
Class: CSCI-6050
Proj:  Final
Date:  2024-11-07
Desc:  Client App - Final Project

*/

// Libs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Includes
#include "csapp.h"
#include "helper.h"

// Function Declarations
char *promptLine(char *);
int promptLineInt(char *);
char *promptLineStr(char *);
void sendName(int);
void sendPlayerMove(int);

// Constants
const int MAX_INPUT_LENGTH = 100;

/* -----------------------------------------------------------------------
Func: Main App Loop
----------------------------------------------------------------------- */
int main(int argc, char *argv[])
{
    // Set Variables
    int clientFd;      // File Descriptor to communicate with the server
    char *host, *port; // String of Port & Host

    char buffer[MAXLINE]; // MAXLINE = 8192 defined in csapp.h

    // Make suer we got the correct argument count
    if (argc != 3)
    {
        printError("Missing Correct Count of Arguments!");
        printError("App needs: 'host' & 'port' entered as arguments");
        exit(0);
    }

    // Set host & Port for Connections
    host = argv[1];
    port = argv[2];

    // Validate port as a number
    if (!isNumber(port))
    {
        printError("Port must be a valid number.");
        exit(1);
    }

    clientFd = Open_clientfd(host, port); // wrapper function that calls getadderinfo, socket and connect functions for client side

    // Resetting the Buffer!
    bzero(buffer, MAXLINE);

    int loop = 1;

    while (loop)
    {
        // Read Response
        readPayload(clientFd, buffer);

        printf("Server Message: %s\n", buffer);

        // Parse the buffer in the main loop
        char *token = strtok(buffer, ",");

        int cmd = atoi(token); // Convert the first token to an int

        // Server Requesting Name
        switch (cmd)
        {
        case 1: // Server Requests "Name"
            printError("   Welcome to Tic-Tac-Toe   ");
            sendName(clientFd);
            break;
        case 2: // Server Requests "Player Move"
            sendPlayerMove(clientFd);
            break;
        case 3: // Draw Board
            token = strtok(NULL, ",");
            printf("Board: %s\n", token);
            break;
        case 99: // close Connection
            loop = 0;
            break;
        default:
            break;
        }

        // Resetting the Buffer
        bzero(buffer, MAXLINE);
    }

    // Close Server Connection
    Close(clientFd);

    return 0;
}

void sendName(int clientFd)
{
    // Get Name and Send to Server!
    char *name = promptLineStr("Enter your Name:");
    printf("Sending: %s\n", name);
    sendPayload(clientFd, name);
}

void sendPlayerMove(int clientFd)
{
    // Get Move and Send to Server!
    int move = promptLineInt("Enter your Move:");
    printf("Sending: %d\n", move);
    char payload[MAXLINE];
    sprintf(payload, "%d", move);
    sendPayload(clientFd, payload);
}

/* -----------------------------------------------------------------------
Func: promptLineInt()
What: This function prints a line and asks for input of Int
In:   String
Out:  Int
----------------------------------------------------------------------- */
int promptLineInt(char *prompt)
{
    char *out = promptLine(prompt); // Allocate memory for user input

    // Check if the input string is a valid integer
    int is_valid = isNumber(out);

    if (is_valid)
    {
        int result = atoi(out); // Convert string to integer

        // Check if the integer is within the range [1, 9]
        if (result >= 1 && result <= 9)
        {
            free(out); // Free memory before returning
            return result;
        }
        else
        {
            printError("Please enter number between 1 and 9.");
        }
    }
    else
    {
        printError("Please enter a valid integer.");
    }

    free(out);                    // Free memory before retrying
    return promptLineInt(prompt); // Repeat the prompt
}

/* -----------------------------------------------------------------------
Func: promptLineStr()
What: This function prints a line and asks for non-empty string input
In:   String (prompt)
Out:  String (non-empty input)
----------------------------------------------------------------------- */
char *promptLineStr(char *prompt)
{
    char *out = promptLine(prompt); // Allocate memory for user input

    // Check if the input string is non-empty
    if (out != NULL && strlen(out) > 0)
    {
        return out; // Return the valid, non-empty string
    }
    else
    {
        printError("Input cannot be empty. Please enter at least one character.");
        free(out);                    // Free memory before retrying
        return promptLineStr(prompt); // Repeat the prompt
    }
}

/* -----------------------------------------------------------------------
Func: promptLine()
What: This function prints a line and asks for input then returns
In:   String
Out:  String
----------------------------------------------------------------------- */
char *promptLine(char *prompt)
{
    char *resp = malloc(MAX_INPUT_LENGTH); // Allocate memory for the response
    if (resp == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    printf("%s ", prompt);

    // Read input and store it directly in `resp`
    if (fgets(resp, MAX_INPUT_LENGTH, stdin) != NULL)
    {
        // Remove newline if present
        resp[strcspn(resp, "\n")] = '\0';
        return resp; // Return the input as a string
    }
    else
    {
        printf("Error reading input.\n");
        free(resp);
        return NULL;
    }
}