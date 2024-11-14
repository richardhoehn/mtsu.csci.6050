/*

Name:  Richard Hoehn
Class: CSCI-6050
Proj:  Final
Date:  2024-11-07
Desc:  Server App - Final Project

*/

// Libs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>

// Includes
#include "csapp.h"
#include "helper.h"

// Function Declarations
void *clientHandler(void *);
void *gameHandler(void *);

// Constants
#define PORT 4320
#define MAX_SIZE 1000
#define MAX_LENGTH 25
#define MAX_CLIENTS 10

// Global Vars!
Game game = {0}; // Initialize game instance
int client_fds[MAX_CLIENTS];
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

// Main Server Application!
int main(int argc, char *argv[])
{
    int listenfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    pthread_t tid;

    if (argc != 2)
    {
        printError("Incorrect Arguments Sent!");
        exit(0);
    }

    listenfd = Open_listenfd(argv[1]); // wrapper function that calls getadderinfo, socket, bind, and listen functions in the server side

    printError("Server Is Running");

    // Create Game Hanlder
    pthread_create(&tid, NULL, gameHandler, NULL);
    pthread_detach(tid);

    // Server runs in the infinite loop.
    // To stop the server process, it needs to be killed using the Ctrl+C key.
    while (1)
    {
        clientlen = sizeof(struct sockaddr_storage);
        int *connfdp = malloc(sizeof(int)); // Allocate memory for new client fd
        if (connfdp == NULL)
        {
            printError("Memory allocation failed");
            continue; // Skip this iteration on memory allocation failure
        }

        *connfdp = Accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen);
        if (*connfdp < 0)
        {
            free(connfdp); // Free allocated memory on failed accept
            printError("Connection acceptance failed");
            continue;
        }

        // Lock the creation of the client
        pthread_mutex_lock(&clients_mutex);

        // Player index holder
        int assigned = 0;
        for (int idx = 0; idx < 2; idx++)
        {
            printf("Checking %d\n", idx);
            if (game.player[idx].fd == 0)
            {
                game.player[idx].fd = *connfdp;
                int *idx_ptr = malloc(sizeof(int));
                if (idx_ptr == NULL)
                {
                    printError("Memory allocation failed");
                    Close(*connfdp);
                    free(connfdp);
                    pthread_mutex_unlock(&clients_mutex);
                    continue;
                }
                *idx_ptr = idx;
                pthread_create(&tid, NULL, clientHandler, idx_ptr);
                pthread_detach(tid);
                assigned = 1;
                break;
            }
        }

        if (!assigned)
        {
            printError("Sorry! Maximum players connected. Connection rejected.");
            Close(*connfdp);
            free(connfdp);
        }

        // Release lock
        pthread_mutex_unlock(&clients_mutex);
    }

    printError("Server Shutdown");
    exit(0);
}

// Game Handler Function (Thread)
void *gameHandler(void *vargp)
{
    // Setup Game Board
    for (int i = 0; i < BOARD_ROWS * BOARD_COLS; i++) {
        game.board[i] = 9;
    }


    while (1)
    {
        // Wait 1second
        sleep(1);

        if(game.player[0].ready == 1 && game.player[1].ready == 1){
            break;
        }
    }

    // Start Game Loop
    while (1)
    {
        int idx = game.moveCnt % 2;
        printf("Asking %d\n", idx);
        sendPayload(game.player[idx].fd, encodeBoard(game.board));
        sleep(1);
        sendPayload(game.player[idx].fd, "2");

        // Wait For Response
        char buffer[MAXLINE];
        bzero(buffer, MAXLINE); // Reset the buffer

        // Read and Set Board
        readPayload(game.player[idx].fd, buffer);
        
        // 
        game.moveCnt += 1;
        printf("Message received (%d): %s\n", game.moveCnt, buffer);

        int playIdx = atoi(buffer);
        game.board[playIdx-1] = idx; // Note: -1 is becasue I am asking users to work on 1...9 instead of indexs!

        int winner = checkBoard(game.board);
        if(winner == idx){
            
        }
        
        // Wait...
        sleep(1);
        printf("Loop Again!\n");
        if(game.moveCnt == 9){
            // Send Disconnect
            game.player[0].disconnect = 1;
            game.player[1].disconnect = 1;
            break;
        }
    }
    return NULL;
}

// Client Handler Function (Thread)
void *clientHandler(void *vargp)
{
    // Get Index of Player
    int idx = *((int *)vargp);
    free(vargp); // Free the dynamically allocated index memory

    printf("Client '%d' Connected (fd = %d)\n", idx, game.player[idx].fd);

    // Send Command (1) to request Name from Client
    sendPayload(game.player[idx].fd, "1");
    printf("Waiting for Client '%d' to send name.\n", idx);

    // Allocate memory for name
    char name[MAX_NAME];
    bzero(name, MAX_NAME); // Ensure buffer is zeroed out

    // Read Response
    readPayload(game.player[idx].fd, name);
    
    strncpy(game.player[idx].name, name, MAX_NAME - 1);
    game.player[idx].name[MAX_NAME - 1] = '\0'; // Ensure null-termination

    printf("Player >> %s << Ready\n", game.player[idx].name);
    game.player[idx].ready = 1;

    // Main loop to handle Client
    while (1)
    {
        // Wait 2second and check for Disconnet
        sleep(2);
        if(game.player[idx].disconnect == 1){
            sendPayload(game.player[idx].fd, "99");
            break;
        }
    }

    // Remove client from list and close connection
    printf("Player (%s) disconnected (FD = %d)\n", game.player[idx].name, game.player[idx].fd);

    // Release
    game.player[idx].fd = 0;

    return NULL;
}
