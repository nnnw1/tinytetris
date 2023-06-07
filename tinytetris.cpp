#include <ctime>
#include <curses.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

//block layout
int x = 431424,      //x coordinate of piece
    y = 598356,      //y coordinate of piece
    r = 427089,      //the form of piece (rotation)
    px = 247872,     //previous x
    py = 799248,     //previous y
    pr,              //previous r
    c = 348480,
    p = 615696,
    tick,            //falling speed
    board[20][10],   //whole map
    block[7][4] = {{x, y, x, y},     //seven kinds of pieces, each has 4 forms
                   {r, p, r, p},
                   {c, c, c, c},
                   {599636, 431376, 598336, 432192},
                   {411985, 610832, 415808, 595540},
                   {px, py, px, py},
                   {614928, 399424, 615744, 428369}},
    score = 0;

/*
@param x     the form of piece
@param y     the bit
return       extract a 2-bit number from a block entry
*/
int NUM(int x, int y) { return 3 & block[p][x] >> y; }

/*
@func   create a new piece
*/
void new_piece() {
    y = py = 0;
    p = rand() % 7;
    r = pr = rand() % 4;
    x = px = rand() % (10 - NUM(r, 16));
}

/*
@func   retrieve through board, draw the board and score 
*/
void frame() {
    for(int i=0; i < 20; ++i) {
        move(1 + i, 1);
        for(int j=0; j < 10; ++j) {
            board[i][j] && attron(262176 | board[i][j] << 8);
            printw("  ");
            attroff(262176 | board[i][j] << 8);
        }
    }
    move(21, 1);
    printw("Score: %d", score);
    refresh();
}

/*
@param x     x coordinate
@param y     y coordinate
@param r     the form of piece
@param v     the color, 0 means to wipe the piece
@func   set the value of the board for a particular (x,y,r) piece
*/
void set_piece(int x, int y, int r, int v) {
    for(int i=0; i < 8; i += 2) {
        board[NUM(r, i * 2) + y][NUM(r, (i * 2) + 2) + x] = v;
    }
}

/*
@func   move a piece from old coords to new
*/
int update_piece() {
    set_piece(px, py, pr, 0);
    set_piece(px = x, py = y, pr = r, p + 1);
}
/*
@func   if a line is full, then remove the line and update the score
*/
void remove_line() {
    for(int row = y; row <= y + NUM(r, 18); ++row) {
        c = 1;
        for(int i=0; i < 10; ++i) {
            c *= board[row][i];
        }
        if(!c) {
            continue;
        }
        for(int i = row-1; i > 0; --i) {
            memcpy(&board[i+1][0], &board[i][0], 40);
        }
        memset(&board[0][0], 0, 10);
        score++;
    }
}