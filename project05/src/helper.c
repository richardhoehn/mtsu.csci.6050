#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#include "csapp.h"
#include "helper.h"


/* -----------------------------------------------------------------------
Func: clearScreen()
What: This function clears the command line screen
In:   void
Out:  void
----------------------------------------------------------------------- */
void msleep(int milliseconds) {
    usleep(milliseconds * 1000); // Convert milliseconds to microseconds
}

/* -----------------------------------------------------------------------
Func: clearScreen()
What: This function clears the command line screen
In:   void
Out:  void
----------------------------------------------------------------------- */
void clearScreen()
{
#ifdef _WIN32
    system("cls"); // Windows
#else
    system("clear"); // Unix/Linux/MacOS
#endif
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
Func: printMessage()
What: This function prints an error message based on input
In:   char array
Out:  void
----------------------------------------------------------------------- */
void printMessage(const char *strMsg1, const char *strMsg2, const int clr)
{
    int msgLen = strlen(strMsg1) > strlen(strMsg2) ? strlen(strMsg1) : strlen(strMsg2);
    int totalWidth = msgLen + 8;

    if (clr == 1)
    {
        clearScreen();
    }

    printf("\n");
    printStars(totalWidth);

    // Center and print strMsg1
    int padding1 = (msgLen - strlen(strMsg1)) / 2;
    printf("**  %*s%-*s  **\n", padding1, "", msgLen - padding1, strMsg1);

    if (strlen(strMsg2) > 0)
    {
        // Center and print strMsg2
        int padding2 = (msgLen - strlen(strMsg2)) / 2;
        printf("**  %*s%-*s  **\n", padding2, "", msgLen - padding2, strMsg2);
    }

    printStars(totalWidth);
    printf("\n");
}

/* -----------------------------------------------------------------------
Func: isNumber()
What: This function check if the string is a number
In:   String
Out:  Int
----------------------------------------------------------------------- */
int isNumber(const char *str)
{
    // Check if each character in the string is a digit
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!isdigit((unsigned char)str[i]))
        {
            return 0; // Return 0 if any character is not a digit
        }
    }
    return 1; // Return 1 if all characters are digits
}

/* -----------------------------------------------------------------------
Func: sendPayload()
What: This function writes to and FD
In: - (int) File Descriptor
    - (char *) Payload to send
Out:  void
----------------------------------------------------------------------- */
void sendPayload(int fd, char *payload)
{
    // sending the message received from the user to the server
    ssize_t bytesSent = 0, bytesLeft = strlen(payload);
    while (bytesSent < bytesLeft)
    {
        ssize_t n = write(fd, payload + bytesSent, bytesLeft - bytesSent);
        if (n < 0)
        {
            printError("Write Error!!");
            return;
        }
        bytesSent += n;
    }
    printf("Payload (%s) with size = %ld Sent!\n", payload, bytesSent);
}

/* -----------------------------------------------------------------------
Func: readPayload()
What: This function read data from FD
In:   (int) File Descriptor
Out:  (char *) - Payload sent
----------------------------------------------------------------------- */
void readPayload(int fd, char *payload)
{
    char buffer[MAX_BUFFER];           // Temporary buffer to store incoming data
    memset(buffer, 0, sizeof(buffer)); // Clear the buffer

    // Reading data from the server
    int n = read(fd, buffer, MAX_BUFFER);
    if (n < 0)
    {
        printError("Read Error!!");
        return; // Return -1 on error
    }

    // Ensuring we do not exceed the size of the provided payload buffer
    if (n >= MAX_BUFFER)
    {
        printError("Buffer overflow: Received data exceeds buffer size.");
        return; // Return error if data exceeds buffer size
    }

    // Copying data into the provided payload buffer
    strncpy(payload, buffer, n);
    payload[n] = '\0'; // Null-terminate the payload to ensure it is a valid string

    return; // Return the number of bytes read
}
