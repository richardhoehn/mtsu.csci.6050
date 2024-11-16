/*

Name:  Richard Hoehn
Class: CSCI-6050
Proj:  04
Date:  2024-11-19
Desc:  Server App

*/

// Libs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Includes
#include "csapp.h"

#define MAX_SIZE 1000
#define MAX_LENGTH 25
#define FILENAME "records.csv"

typedef struct
{
    char firstName[MAX_LENGTH];
    char lastName[MAX_LENGTH];
    char zipCode[MAX_LENGTH];
    char department[MAX_LENGTH];
    int salary;

} Employee;

// Function Declarations
char *serverRead(int);
void serverWrite(int, char *);
void printStars(int);
void printError(const char *);
int updateEmployees(Employee employees[]);
void appendToFile(char *);

// Creating Definition Functions for the Operators!
int greater_than(int a, int b) { return a > b; }
int less_than(int a, int b) { return a < b; }
int greater_than_or_equal(int a, int b) { return a >= b; }
int less_than_or_equal(int a, int b) { return a <= b; }
int equal(int a, int b) { return a == b; }

// With this special Funciotn we are mapping based on the comparison operator string
// Note: This is a pointer coming back from the function to the definition
int (*get_comp_func(const char *operator))(int, int) {
    if (strcmp(operator, ">") == 0) { return &greater_than; }
    if (strcmp(operator, "<") == 0) { return &less_than; }
    if (strcmp(operator, ">=") == 0) { return &greater_than_or_equal; }
    if (strcmp(operator, "<=") == 0) { return &less_than_or_equal; }
    if (strcmp(operator, "==") == 0) { return &equal; }
    return NULL; // Return NULL if operator is invalid
}

// Function to append employee info into the result buffer using snprintf
void append_employee_info(char *result, Employee e) {
    snprintf(
        result + strlen(result),   // Set the location to start writting
        MAX_SIZE - strlen(result), // Max Length to stop
        "%s,%s,%s,%s,%d\n",        // Formatted String
        e.firstName,
        e.lastName,
        e.zipCode,
        e.department,
        e.salary);
}

char *searchByName(Employee employees[], int count, const char *firstName, const char *lastName) {
    char *result = malloc(MAX_SIZE * sizeof(char));
    bzero(result, MAX_SIZE);

    // Flag "found"
    int found = 0;

    // Start For-Loop
    for (int i = 0; i < count; i++) {
        // Create a copy of the Empoyee - Makes Code a bit easier
        Employee e = employees[i];

        // Check First Name & Last Name
        // I am using a simple "or" and then to see if the value is still "zero"!
        if ((strcmp(e.firstName, firstName) | strcmp(e.lastName, lastName)) == 0) {
            // Set "found" flag to true
            found = 1;
            // Append Employee to results
            append_employee_info(result, e);
        }
    }

    // Check found Flag
    if (found == 0) {
        strcpy(result, "No matching records found.\n");
    }

    return result;
}

char *searchByZipCode(Employee employees[], int count, const char *zipCode) {
    char *result = malloc(MAX_SIZE * sizeof(char));
    bzero(result, MAX_SIZE);

    // Flag "found"
    int found = 0;

    // Start For-Loop
    for (int i = 0; i < count; i++) {
        // Create a copy of the Empoyee - Makes Code a bit easier
        Employee e = employees[i];

        // Check Zip Code are equal to eachother
        if (strcmp(e.zipCode, zipCode) == 0) {
            // Set "found" flag to true
            found = 1;

            // Append Employee to results
            append_employee_info(result, e);
        }
    }

    // Check found Flag
    if (found == 0) {
        strcpy(result, "No matching records found.\n");
    }

    return result;
}

char *searchBySalary(Employee employees[], int count, int salary, const char *comparisonOperator) {
    char *result = malloc(MAX_SIZE * sizeof(char));
    bzero(result, MAX_SIZE);

    // Flag "found"
    int found = 0;

    // Get the function pointer based on the operator string
    int (*comparison)(int, int) = get_comp_func(comparisonOperator);

    // Start For-Loop
    for (int i = 0; i < count; i++) {
        // Create a copy of the Empoyee - Makes Code a bit easier
        Employee e = employees[i];

        // Based on the Comparrison we will get a "0" or "1"
        if (comparison(e.salary, salary))
        {
            // Set "found" flag to true
            found = 1;

            // Append Employee to results
            append_employee_info(result, e);
        }
    }

    // Check found Flag
    if (found == 0)
    {
        strcpy(result, "No matching records found.\n");
    }

    return result;
}

// Main Server Application!
int main(int argc, char *argv[])
{
    int listenfd;
    int connFd; // file descriptor to communicate with the client
    socklen_t clientlen;
    struct sockaddr_storage clientaddr; /* Enough space for any address */

    char client_hostname[MAXLINE], client_port[MAXLINE];


    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }

    listenfd = Open_listenfd(argv[1]); // wrapper function that calls getadderinfo, socket, bind, and listen functions in the server side

    // Server runs in the infinite loop.
    // To stop the server process, it needs to be killed using the Ctrl+C key.
    while (1)
    {
        clientlen = sizeof(struct sockaddr_storage);

        // wait for the connection from the client.
        connFd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
        Getnameinfo((SA *)&clientaddr, clientlen, client_hostname,
                    MAXLINE, client_port, MAXLINE, 0);

        printf("Connected to (%s, %s)\n", client_hostname, client_port);

         // Employee Setup
        Employee employees[MAX_SIZE];
        int employeeCount = updateEmployees(employees);

        while (1)
        {
            // Read the payload from client
            char *buffer = serverRead(connFd);
            if (buffer == NULL)
            {
                printError("Buffer Corrupt!");
                break;
            }

            // Parse the buffer in the main loop
            char *token = strtok(buffer, ",");
            int sel = atoi(token); // Convert the first token to an int

            if(sel == 1){
                char *record = strtok(NULL, "\0");  // Capture the rest of the buffer as the record
                appendToFile(record);
                employeeCount = updateEmployees(employees);
                serverWrite(connFd, "Record added Sucessfully!!\n");
            }

            if(sel == 2){
                char *firstName = strtok(NULL, ",");  // Get First Name
                char *lastName = strtok(NULL, ",");  // Get Last Name
                char *searchResult = searchByName(employees, employeeCount, firstName, lastName);
                serverWrite(connFd, searchResult);
            }

            if(sel == 3){
                char *zipCode = strtok(NULL, ",");  // Get Zip Code
                char *searchResult = searchByZipCode(employees, employeeCount, zipCode);
                serverWrite(connFd, searchResult);
            }

            if(sel == 4){
                int salary = atoi(strtok(NULL, ","));
                char *op = strtok(NULL, ",");
                char *searchResult = searchBySalary(employees, employeeCount, salary, op);
                serverWrite(connFd, searchResult);
            }
                
            if (sel == 5)
            {
                serverWrite(connFd, "Connection Closed!!\n");
                break; // Exit Reading Loop & close Connection
            }
            

            free(buffer); // Free allocated buffer after processing
        }

        Close(connFd);
        printf("(%s, %s) disconnected\n", client_hostname, client_port);
    }
    exit(0);
}


/* -----------------------------------------------------------------------
Func: updateEmployees()
What: This function prints an error message based on input
In:   - employee Array - Pointer
Out:  - (int) count of employees
----------------------------------------------------------------------- */
int updateEmployees(Employee employees[]) {
    FILE *file = fopen(FILENAME, "r");
    int count = 0;

    if (file == NULL) {
        printf("Unable to open the file.\n");
        return 1;
    }

    char line[MAX_SIZE];

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^,],%[^,],%[^,],%[^,],%d",
               employees[count].firstName,
               employees[count].lastName,
               employees[count].zipCode,
               employees[count].department,
               &employees[count].salary);
        count++;
    }

    fclose(file); // Close File!
    return count; // Return employee count!
}


void appendToFile(char *record) {
    FILE *file = fopen(FILENAME, "a");  // Open in append mode
    if (file == NULL) {
        printf("Unable to open the file.\n");
        return;
    }

    // Write the record and add a newline
    fprintf(file, "\n%s", record);

    fclose(file); // Close the file
    return;
}



/* -----------------------------------------------------------------------
Func: printError()
What: This function prints an error message based on input
In:   (char *) Text to print
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
Func: serverRead()
What: This function read data from client
In:   (int) File Descriptor
Out:  (char *) - Payload sent
----------------------------------------------------------------------- */
char *serverRead(int fd)
{
    char *buffer = malloc(MAXLINE); // Allocate buffer on the heap
    if (buffer == NULL)
    {
        perror("Memory allocation failed");
        return NULL;
    }

    bzero(buffer, MAXLINE);

    // Read data from the client
    size_t n = read(fd, buffer, MAXLINE - 1); // Leave space for null terminator
    if (n < 0)
    {
        perror("Read Error!!");
        free(buffer); // Free the allocated memory on error
        return NULL;
    }

    buffer[n] = '\0'; // Null-terminate the string

    return buffer; // Return the buffer directly
}


/* -----------------------------------------------------------------------
Func: serverWrite()
What: This function writes back to Client
In: - (int) File Descriptor
    - (char *) Payload to send 
Out:  void
----------------------------------------------------------------------- */
void serverWrite(int fd, char * payload)
{
    int n = write(fd, payload, strlen(payload));
    if (n < 0)
    {
        perror("Write Error!!");
        return;
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


