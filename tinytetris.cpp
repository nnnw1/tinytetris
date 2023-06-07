#include <ctime>
#include <curses.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

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