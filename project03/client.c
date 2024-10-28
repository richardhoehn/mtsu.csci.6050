/*

Name:  Richard Hoehn
Class: CSCI-6050
Proj:  03
Date:  2024-11-07
Desc:  Client App

*/

// Libs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Includes
#include "csapp.h"

// Function Declarations
int isNumber(const char *str);
void printStars(int);
void printError(const char *);
int promptMenuSelect(void);
char *promptLine(char *);
int promptLineInt(char *);
char *promptLineStr(char *);
int promptLineOps(char *);
void sendPayload(int, char *);

// Constants
const int MAX_INPUT_LENGTH = 100;
const char *VALID_OPS[] = {">", "<", "==", ">=", "<="}; // Allowed operators
const int VALID_OPS_NUM = 5;                            // Number of allowed operators

/* -----------------------------------------------------------------------
Func: Main App Loop
----------------------------------------------------------------------- */
int main(int argc, char *argv[])
{
    // Set Variables
    int clientFd;      // File Descriptor to communicate with the server
    char *host, *port; // String of Port & Host
    size_t n;

    char buffer[MAXLINE]; // MAXLINE = 8192 defined in csapp.h
    char payload[MAXLINE];

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
    if (!isNumber(port)) {
        printError("Port must be a valid number.");
        exit(1);
    }

    clientFd = Open_clientfd(host, port); // wrapper function that calls getadderinfo, socket and connect functions for client side

    // Resetting the Buffer!
    bzero(buffer, MAXLINE);

    while (1)
    {
        // Start Prompt
        int sel = promptMenuSelect();

        // Setup Vars
        char *firstName = NULL;
        char *lastName = NULL;
        char *department = NULL;
        char *zipCode = NULL;
        int salary;
        int op;

        // Add Record
        if (sel == 1)
        {
            firstName = promptLineStr("Enter first name:");
            lastName = promptLineStr("Enter last name:");
            department = promptLineStr("Enter Department:");
            salary = promptLineInt("Enter Salary:");
            sprintf(payload, "1,%s,%s,%s,%d", firstName, lastName, department, salary);
            printf("Payload: %s\n", payload);
            sendPayload(clientFd, payload);
        }

        // Search By Name
        if (sel == 2)
        {
            firstName = promptLineStr("Enter first name:");
            lastName = promptLineStr("Enter last name:");
            sprintf(payload, "2,%s,%s", firstName, lastName);
            printf("Payload: %s\n", payload);
            sendPayload(clientFd, payload);
        }

        // Search by Zip Code
        if (sel == 3)
        {
            zipCode = promptLineStr("Enter Zip Code:");
            sprintf(payload, "3,%s", zipCode);
            printf("Payload: %s\n", payload);
            sendPayload(clientFd, payload);
        }

        // Search by Salary
        if (sel == 4)
        {
            salary = promptLineInt("Enter Salary:");
            printf("Salary: %d\n", salary);
            op = promptLineOps("Enter Comparision Type ['>','<','==','>=','<=']:");
            sprintf(payload, "4,%d,%d", salary, op);
            printf("Payload: %s\n", payload);
            sendPayload(clientFd, payload);
        }

        // Free Vars - Potential Memory Leak

        free(firstName);
        free(lastName);
        free(department);
        free(zipCode);

        // Terminate
        if (sel == 5)
        {
            sprintf(payload, "5");
            printf("Payload: %s\n", payload);
            sendPayload(clientFd, payload);
            break;
        }
    }

    // Close Server Connection
    Close(clientFd);

    return 0;
}


void sendPayload(int fd, char * payload)
{
    char buffer[MAXLINE]; // MAXLINE = 8192 defined in csapp.h

    // sending the message received from the user to the server
    int n = write(fd, payload, strlen(payload));
    if (n < 0)
    {
        perror("Write Error!!");
        return;
    }

    // waiting for the message from the server.
    // the message will be stored in buffer variable.
    n = read(fd, buffer, MAXLINE);
    if (n < 0)
    {
        perror("Read Error!!");
        return;
    }

    printf("Message from Server:\n");
    // displaying the message in buffer on the console
    Fputs(buffer, stdout);
}


/* -----------------------------------------------------------------------
Func: isNumber()
What: This function check if the string is a number
In:   String
Out:  Int
----------------------------------------------------------------------- */
int isNumber(const char *str) {
    // Check if each character in the string is a digit
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit((unsigned char)str[i])) {
            return 0;  // Return 0 if any character is not a digit
        }
    }
    return 1;  // Return 1 if all characters are digits
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
        free(out);              // Free memory before returning
        return result;
    }
    else
    {
        printError("Please enter a valid integer.");
        free(out);                    // Free memory before retrying
        return promptLineInt(prompt); // Repeat the prompt
    }
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
Func: promptLineOps()
What: This function prompts the user to input a comparison operator
      from the allowed options: ['>','<','==','>=','<=']
In:   String (prompt)
Out:  Int (index of valid operator in the array)
----------------------------------------------------------------------- */
int promptLineOps(char *prompt)
{
    char *out = NULL;
    int index = -1;

    while (index == -1)
    {
        out = promptLine(prompt); // Get user input

        // Check if the input matches any of the valid operators
        for (int i = 0; i < VALID_OPS_NUM; i++)
        {
            if (strcmp(out, VALID_OPS[i]) == 0)
            {
                index = i; // Store the index of the matched operator
                break;
            }
        }

        if (index == -1)
        {
            printError("Invalid operator.");
            free(out); // Free memory before retrying
        }
    }

    free(out);    // Free memory after a valid input is found
    return index; // Return the index of the valid operator
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

/* -----------------------------------------------------------------------
Func: printStars()
What: This function prints a line of "stars" ending with a new-line
In:   int - Stars to print
Out:  void
----------------------------------------------------------------------- */
void printStars(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("*");
    }
    printf("\n");
}

/* -----------------------------------------------------------------------
Func: printError()
What: This function prints an error message based on input
In:   char array
Out:  void
----------------------------------------------------------------------- */
void printError(const char *strError)
{
    printf("\n");
    printStars(strlen(strError) + 8);
    printf("!!! %s !!!\n", strError);
    printStars(strlen(strError) + 8);
    printf("\n");
}

/* -----------------------------------------------------------------------
Func: promptMenuSelect()
What: This function asks use to select an option
In:   void
Out:  int (1-5)
----------------------------------------------------------------------- */
int promptMenuSelect(void)
{
    int resp = 0;

    while (1)
    {
        printf("\n");
        printf("(1) Add record\n");
        printf("(2) Search by Name\n");
        printf("(3) Search by Zip Code\n");
        printf("(4) Search by Salary\n");
        printf("(5) Terminate\n");
        printf("Select an option [1,2,3,4 or 5]: ");

        // Make sure Input is a Number!
        if (scanf("%d", &resp) != 1)
        {
            printError("Invalid input! Please enter a number.");

            // Clear the Buffer!
            while (getchar() != '\n')
                ;
            continue;
        }

        // Clear any additional leftover characters in the buffer
        while (getchar() != '\n')
            ;

        if (resp >= 1 && resp <= 5)
        {                // Check if input is within valid range
            return resp; // Return valid input
        }
        else
        {
            printError("Wrong code! Please try again.");
        }
    }

    return resp;
}