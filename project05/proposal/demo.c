/*

Name:  Richard Hoehn
Class: CSCI-6050
Proj:  01
Date:  2024-09-09
Desc:  Hex Creater App - Similar to the xxd command.

Links: https://c-for-dummies.com/ncurses/source_code/index.php
*/

// Setup Includes & Libs
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <ncurses.h>


// Start Program
int main(int argc, char* argv[]){

    

    // Initialize ncurses
    initscr();            // Start curses mode
    cbreak();             // Disable line buffering
    keypad(stdscr, TRUE); // Enable function keys and arrow keys
    noecho();             // Don't echo user input

    // Display a message
    //printw("Hello, ncurses!\nPress any key to exit...");
    move(5,5);
    addch('*');
    move(4,4);
    addch('*');

    refresh();           // Print to the screen

    // Wait for user input
    getch();
    flash();
    beep();
    refresh();

    WINDOW *win = newwin(5, 10, 2, 2);
    WINDOW *win2 = newwin(5, 10, 2, 12);
    WINDOW *win3 = newwin(5, 10, 12, 2);
    refresh();

    // making box border with default border styles
    box(win, 0, 0);
    box(win2, 0, 0);
    box(win3, 0, 0);


    mvwprintw(win, 0, 0, "1");
    mvwprintw(win2, 0, 1, "2");
    mvwprintw(win3, 0, 1, "3");

    wrefresh(win);
    wrefresh(win2);
    wrefresh(win3);

    getch();

    printw("Window is %d rows, %d columns.\n",            LINES,COLS);
    refresh();
    getch();

    // End ncurses mode
    endwin();


    return 0;
}