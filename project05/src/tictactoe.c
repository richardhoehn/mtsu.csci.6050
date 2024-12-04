#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "tictactoe.h"

void drawBoard(char *charBoard)
{

    int *intBoard = decodeBoard(charBoard);

    printf("\n");
    printf("-------------\n");

    for (int row = 0; row < 3; row++)
    {
        // Print the row's cells
        for (int col = 0; col < 3; col++)
        {
            int idx = row * 3 + col;

            printf("|");

            if (intBoard[idx] == 0)
            {
                printf(" X ");
            }
            else if (intBoard[idx] == 1)
            {
                printf(" O ");
            }
            else
            {
                printf("   ");
            }
        }
        printf("|");
        printf("\n");

        // Print horizontal separator after each row, except the last
        if (row < 2)
        {
            printf("|---|---|---|\n");
        }
    }

    printf("-------------\n");
    printf("\n");

    return;
}

// Function to encode the 2D board into a string
char *encodeBoard(int *board)
{
    char *encoded = malloc(BOARD_BUFFER);
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

    // Horizontal checks
    if (board[0] == board[1] && board[1] == board[2] && board[0] != 9)
    {
        winner = board[0];
    }
    if (board[3] == board[4] && board[4] == board[5] && board[3] != 9)
    {
        winner = board[3];
    }
    if (board[6] == board[7] && board[7] == board[8] && board[6] != 9)
    {
        winner = board[6];
    }

    // Vertical checks
    if (board[0] == board[3] && board[3] == board[6] && board[0] != 9)
    {
        winner = board[0];
    }
    if (board[1] == board[4] && board[4] == board[7] && board[1] != 9)
    {
        winner = board[1];
    }
    if (board[2] == board[5] && board[5] == board[8] && board[2] != 9)
    {
        winner = board[2];
    }

    // Diagonal checks
    if (board[0] == board[4] && board[4] == board[8] && board[0] != 9)
    { // Top-left to bottom-right
        winner = board[0];
    }
    if (board[2] == board[4] && board[4] == board[6] && board[2] != 9)
    { // Top-right to bottom-left
        winner = board[2];
    }

    return winner;
}