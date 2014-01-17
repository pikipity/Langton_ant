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
#include <stdio.h>

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
char button='a';
int delay_10th=3;

void init_game(){
    while (button!=' ') {
        clear();
        getmaxyx(stdscr,row,col);
        mvprintw(row/2, col/2-11, "Now, press \"Space\" to start.");
        mvprintw(row/2+1, col/2-12, "Press \"Space\" to stop in game.");
        refresh();
        button=getch();
    }
    clear();
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
}



int main()
{
    initscr();
    curs_set(0);
    noecho();
    cbreak();
    halfdelay(delay_10th);
    while (1) {
        //check screen (whether need init_game)
        int new_row=1;
        int new_col=1;
        getmaxyx(stdscr,new_row,new_col);
        if (new_row!=row || new_col!=col) {
            init_game();
        }
        //check keyboard
        button=getch();
        if(button==' '){
            break;
        }
        //calculate next_grid, next_state, next_x, next_y
        next_y=current_y+(current_state%2)*(current_state-2);
        if (next_y<0) {
            next_y=row-1;
        }else if (next_y>row-1) {
            next_y=0;
        }
        next_x=current_x+(current_state%2-1)*(current_state-3);
        if (next_x<0) {
            next_x=col-1;
        }else if(next_x>col-1){
            next_x=0;
        }
        //
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
    }
    //finish game
    button=0;
    while (button!=' ') {
        clear();
        getmaxyx(stdscr,row,col);
        mvprintw(row/2, col/2-10, "Thank you -- pikipity");
        mvprintw(row/2+1, col/2-12, "Press \"Space\" to finish");
        refresh();
        button=getch();
    }
    endwin();
}

