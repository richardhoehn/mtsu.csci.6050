#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "csapp.h"
#include "helper.h"

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


void drawBoard(char * board){
    printf("Board: %s", board);
    return;
}

// Function to encode the 2D board into a string
char *encodeBoard(int *board)
{
    char *encoded = malloc(MAX_BUFFER);
    if (!encoded)
    {
        printf("Memory allocation failed\n");
        return NULL;
    }
    encoded[0] = '\0'; // Initialize as empty string

    // Add Command
    strcat(encoded, "3,");

    for (int i = 0; i < BOARD_ROWS * BOARD_COLS; i++)
    {
        char temp[2]; // Temporary buffer for each number
        sprintf(temp, "%d", board[i]);
        strcat(encoded, temp);

        // Add delimiter
        strcat(encoded, BOARD_DEL);
    }

    return encoded;
}

// Function to decode the string back into a 2D board
int *decodeBoard(char *encoded)
{
    static int board[BOARD_ROWS * BOARD_COLS]; // Static to return pointer safely
    char *token = strtok(encoded, BOARD_DEL);
    int i = 0;

    while (token != NULL)
    {
        board[i] = atoi(token);
        token = strtok(NULL, BOARD_DEL);
        i++;
    }

    return &board[0]; // Return pointer to the first element
}

// Function to check board for winner
int checkBoard(int *board)
{
    int winner = 9;

    // Check Horizontal
    if(board[0] == board[1] == board[2] || board[3] == board[4] == board[5] || board[6] == board[7] == board[8]){
        winner = board[0];
    } 

    // Check Veritcal
    if(board[0] == board[3] == board[6] || board[1] == board[4] == board[7] || board[2] == board[5] == board[8]){
        winner = board[0];
    }  

    // Diagonal "\" & "/"
    if(board[0] == board[4] == board[8] || board[6] == board[4] == board[2]){
        winner = board[4];
    } 

    return winner;
}