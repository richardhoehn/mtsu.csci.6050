/*

Name:  Richard Hoehn
Class: CSCI-6050
Proj:  03
Date:  2024-11-07
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

typedef struct
{
    char firstName[MAX_LENGTH];
    char lastName[MAX_LENGTH];
    char zipCode[MAX_LENGTH];
    char department[MAX_LENGTH];
    int salary;

} Struct_Employee_Info;

// Function Declarations
char *serverRead(int);
void serverWrite(int, char *);
void printStars(int);
void printError(const char *);

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
                serverWrite(connFd, "Sel 1:\nHello\n");
            }

            if(sel == 2){
                serverWrite(connFd, "Sel 2:\n");
            }

            if(sel == 3){
                serverWrite(connFd, "Sel 3:\n");
            }

            if(sel == 4){
                serverWrite(connFd, "Sel 4:\n");
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

    printf("Server received %ld bytes message\n", n);
    printf("Message from Client: %s\n", buffer);

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