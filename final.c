//SE 185: Final Project Template//
/////////////////////////
/* 
Team xx (please insert your team number instead of xx)
Team member 1 "Samuel Schroeder" | "50"
Team member 2 "Eli Newland" | "50"
*/

////////////////////
#include<stdio.h>//
//add more here////
#include <math.h>
#include <ncurses/ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "pieces.h"

//////////////////////
//Struct Definition//
////////////////////

#define WALL 'X'

//create board array
char* board[30];
char* row = NULL;

int linesCleared = 0;

/////////////////////////////////////
//User Defined Functions Prototype//
//List prototypes here and define//
//them below the main function////
/////////////////////////////////
void draw_character(int x, int y, char use, int color);

void draw_box(void);

void make_box(void);

void delAndShift(int line, char* newRow, char* board[]);

void printPiece(int xloc, int yloc, piece* p, int space);

int main(){
    srand(time(NULL));
    //create random piece
    int shape = rand() % 7;
    piece* p = (piece*)malloc(sizeof(piece));
    shapePiece(p, shape);

    int t, temp, xloc, yloc, xprev, yprev;
    int rx, ry, lx, ly, i;
    int linecount = 0;
    int line = 0;
    int lose = 0;
    xloc = 13;
    yloc = 5;
    xprev = 13;

    scanf("%d, %d, %d, %d, %d", &t, &rx, &ry, &lx, &ly);
    temp = t;

    //initialize ncurses
    initscr();
    start_color();

    //define color pairs
    init_pair(7, COLOR_YELLOW, COLOR_BLACK);
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(4, COLOR_WHITE, COLOR_BLACK);
    init_pair(5, COLOR_BLUE, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);

    refresh();

    //draw border
    make_box();
    draw_box();

    while(1){
        scanf("%d, %d, %d, %d, %d", &t, &rx, &ry, &lx, &ly);
    
        //horizontal movement
        if(t > temp + 100){
            //print blank piece and increment x
            if (rx > 100){
                printPiece(xloc, yloc, p, 1);
                xloc += 1;
            }
            if (rx < -100){
                printPiece(xloc, yloc, p, 1);
                xloc -=1;
            }
        }

        //horizontal collision
        int moveSide = 0;
        for (int i = 0; i < 4; i++){
            for (int j = 3; j >= 0; j--){
                //if piece is block
                if (p->shape[j][i] != '*'){
                    //if there is a wall on right or left set flag
                    if (*(board[yloc-(3-j)]+(xloc)) == WALL || *(board[yloc-(3-j)]+(xloc+i)) == WALL){
                        moveSide = 1;
                    }
                }
            }
        }
        //if flag is set don't increase x
        if(moveSide){	
            xloc = xprev;
        }

        //vertical collision
        int moveDown = 1;
        for (int i = 0; i < 4; i++){
            for (int j = 3; j >= 0; j--){
                //if piece is block
                if (p->shape[j][i] != '*'){
                    //if there is a wall below the piece set flag
                    if (*(board[yloc-(2-j)] + (xloc+i)) == WALL){
                        moveDown = 0;
                    }
                }
            }
        }
        //vertical movement
        if(t > temp + 100 && moveDown){  
            //print blank piece and increment y
            printPiece(xloc, yloc, p, 1);
            yprev = yloc;
            yloc+=1;
            temp = t;
        }

        //print piece at new location
        printPiece(xloc, yloc, p, 0);
        xprev = xloc;

        //piece has stopped
        if(!moveDown){
            //add piece into the board as walls
            for (int i = 0; i < 4; i++){
                for (int j = 0; j < 4; j++){
                    if (p->shape[i][j] != '*'){
                        //check lose case where y is one below spawn
                        if ((yloc+i-3) == 6){
                            lose = 1;
                        }
                        //add wall
                        *(board[yloc+i-3] + (xloc + j)) = WALL;
                    }
                }
            }
            //reset x and y
            xloc = 13;
            yloc = 5;

            //update box on screen
            draw_box();
            
            if (lose){
                break;
            }

            //free previous piece
            free(p);
            //create new random piece
            shape = rand() % 7;
            p = (piece*)malloc(sizeof(piece));
            shapePiece(p, shape);

            temp = t;

            //check for completed line
            line = 0;
            linecount = 0;
            for(int i = 5; i <= 28; i++){
                for(int j = 1; j < 30; j++){
                    //count number of walls in row
                    if(*(board[i] + j) == WALL){
                        linecount = linecount + 1; 
                    }
                }
                //if the row is full mark row complete
                if(linecount > 27){
                    line = i;
                    break;
                }
                linecount = 0;
            }
            //if a line is marked complete
            if(line != 0){
                //create new row
                strncpy(row, "X                            X", 30);
                //update board
                delAndShift(line, row, board);
            }

            //win condition: clear 1 line
            if (linesCleared >= 1){
                lose = 2;
                break;
            }

        }
        fflush(stdout);
    }
    endwin();

    //print message
    if (lose == 1){
        printf("You lose!");
    } else if (lose == 2){
       printf("You win!"); 
    }

    //free everything
    for (int i = 0; i < 30; i++) {
        free(board[i]);
    }
}

///////////////////////////////////////
//User Defined Functions' Definition//
/////////////////////////////////////
void draw_character(int x, int y, char use, int color)
{
    mvaddch(y,x,use | COLOR_PAIR(color));
    refresh();
}

void draw_box(void){
    int i, j;
    for(i = 0; i < 30; ++i){
        for(j = 0; j < 30; ++j){
            //if it should be a wall print 254 so it is a block else space
            if (*(board[i] + j) == WALL){
                draw_character(j,i,254,4);
            } else {
                draw_character(j,i,*(board[i] + j), 4);
            }
        }  
    }
}

void make_box(void){
    for(int i = 0; i < 30; ++i){
        //allocate new row
        row = (char*)malloc(30*sizeof(char));

        if(row == NULL){
            exit(0);
        }

        //populate row
        if (i==0||i==29){
            //board ends
            strncpy(row, "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", 30);
        } else {
            strncpy(row, "X                            X", 30);
        }

        //add row to board
        board[i] = row;
    }
    //create new row for updating board
    row = (char*)malloc(30*sizeof(char));
}

void delAndShift(int line, char* newRow, char* board[]){
    //delete complete line
    free(board[line]);
    //shift rows down
    for (int i = line; i > 1; i--){
        //move pointers to the row above
        board[i] = board[i - 1];
    }
    //add new row to top
    board[1] = newRow;
    //update score
    linesCleared++;
    draw_box();
}

void printPiece(int xloc, int yloc, piece* p, int space){
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            //print the next character - blank if in space mode
			if (space && p->shape[i][j] != '*'){
				draw_character(xloc+j,yloc + i - 3, ' ', p->useColor);
			} else if (p->shape[i][j] != '*'){
				draw_character(xloc+j,yloc + i - 3, p->shape[i][j], p->useColor);
			}
        }
    }
}