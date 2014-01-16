//
//  main.cpp
//  Langton's ant
//
//  Created by pikipity.
//  Copyright (c) 2014 pikipity. All rights reserved.
//

#include <ncurses.h>
#include <string.h>
#include <unistd.h>

//grid
char white[]=" ";
char black[]="#";
char ant_u[]="U";
char ant_r[]="R";
char ant_d[]="D";
char ant_l[]="L";
char* ant[]={ant_u,ant_r,ant_d,ant_l};
//white:-1. black:1
int current_grid,next_grid;
//        up:1
//left:4        right:2
//        down:3
int current_state,next_state;
//
int current_x,current_y,next_x,next_y;
//
int row=0;
int col=0;
int sleep_time=1000000/30;

void init_game(){
    clear();
    getmaxyx(stdscr,row,col);
    mvprintw(row/2, col/2-9, "Press any key to start");
    refresh();
    getchar();
    //init value
    current_grid=-1;
    current_state=2;
    current_y=row/2;
    current_x=col/2;
    //init first frame
    for (int i=0; i<row; i++) {
        for (int j=0; j<col; j++) {
            mvprintw(i, j, white);
        }
    }
    mvprintw(current_y,current_x,ant[current_state-1]);
    refresh();
    usleep(sleep_time);
}



int main()
{
    initscr();
    curs_set(0);
    while (1) {
        int new_row,new_col;
        getmaxyx(stdscr,new_row,new_col);
        if (new_row!=row || new_col!=col) {
            init_game();
        }
        //calculate next_grid, next_state, next_x, next_y
        switch (current_state) {
            case 1:
                next_y=current_y-1;
                if (next_y<0) {
                    next_y=row-1;
                }
                next_x=current_x;
                break;
            case 2:
                next_x=current_x+1;
                if(next_x>col-1){
                    next_x=0;
                }
                next_y=current_y;
                break;
            case 3:
                next_y=current_y+1;
                if (next_y>row-1) {
                    next_y=0;
                }
                next_x=current_x;
                break;
            case 4:
                next_x=current_x-1;
                if (next_x<0) {
                    next_x=col-1;
                }
                next_y=current_y;
                break;
            default:
                break;
        }
        char test=(char)mvinch(next_y, next_x);
        if (test==white[0]) {
            next_grid=-1;
        }else if(test==black[0]){
            next_grid=1;
        }
        next_state=current_state+next_grid;
        if (next_state<1) {
            next_state=4;
        }else if (next_state>4){
            next_state=1;
        }
        //draw current grid
        current_grid*=-1;
        if (current_grid==-1) {
            mvprintw(current_y, current_x, white);
        }else{
            mvprintw(current_y , current_x, black);
        }
        current_y=next_y;
        current_x=next_x;
        current_grid=next_grid;
        current_state=next_state;
        mvprintw(current_y,current_x,ant[current_state-1]);
        refresh();
        usleep(sleep_time);
    }
}

