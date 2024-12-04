#ifndef TICTACTOE_H
#define TICTACTOE_H

#define BOARD_BUFFER 128

// Board Setup
#define BOARD_ROWS 3
#define BOARD_COLS 3
#define BOARD_DEL "|" // Define the delimiter here
#define SQUARE_HEIGHT 5
#define SQUARE_WIDTH 10

// Board / Game Functions
void drawBoard(char *);
char *encodeBoard(int *);
int *decodeBoard(char *);
int checkBoard(int *);

#endif // TICTACTOE_H