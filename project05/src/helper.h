#ifndef HELPER_H
#define HELPER_H

#define MAX_BUFFER 8192
#define MAX_NAME 25

// Board Setup
#define BOARD_ROWS 3
#define BOARD_COLS 3
#define BOARD_DEL "|" // Define the delimiter here

// Setup Game Structs
typedef struct
{
    int fd;
    int ready;
    int disconnect;
    char name[MAX_NAME];
    char marker;
} Player;

// Setup Game Struct
typedef struct
{
    Player player[2];  // Two Players
    int board[BOARD_ROWS * BOARD_COLS]; // Board based on Int(s)
    int moveCnt;
} Game;

// General Simple Functions
void printStars(int n);
void printError(const char *);
int isNumber(const char *);

// Socket Comunications
void sendPayload(int, char *);
void readPayload(int, char *);

// Board / Game Functions
void drawBoard(char *);
char *encodeBoard(int *);
int *decodeBoard(char *);
int checkBoard(int *);

#endif // HELPER_H
