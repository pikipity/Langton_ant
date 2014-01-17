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
char black[]="+";
char ant_u[]="A";
char ant_r[]=">";
char ant_d[]="V";
char ant_l[]="<";
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
bool color;

void init_game(){
    while (button!=' ') {
        clear();
        getmaxyx(stdscr,row,col);
        if (color) {
            attron(COLOR_PAIR(1));
        }
        mvprintw(row/2, col/2-11, "Now, press \"Space\" to start.");
        mvprintw(row/2+1, col/2-12, "Press \"Space\" to stop in game.");
        if (color) {
            attroff(COLOR_PAIR(1));
        }
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
            if (color) {
                attron(COLOR_PAIR(3));
                mvprintw(i, j, white);
                attroff(COLOR_PAIR(3));
            }else{
                mvprintw(i, j, white);
            }
        }
    }
    if (color) {
        attron(COLOR_PAIR(5));
        mvprintw(current_y,current_x,ant[current_state-1]);
        attroff(COLOR_PAIR(5));
    }else{
        mvprintw(current_y,current_x,ant[current_state-1]);
    }
    refresh();
}



int main()
{
    initscr();
    curs_set(0);
    noecho();
    cbreak();
    halfdelay(delay_10th);
    color=has_colors();
    if (color) {
        start_color();
        init_pair(1, COLOR_WHITE, COLOR_BLACK);//normal
        init_pair(2, COLOR_BLUE, COLOR_BLUE);//black
        init_pair(3, COLOR_CYAN, COLOR_CYAN);//white
        init_pair(4, COLOR_MAGENTA, COLOR_BLUE);//ant and black
        init_pair(5, COLOR_MAGENTA, COLOR_CYAN);//ant and white
    }
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
            if (color) {
                attron(COLOR_PAIR(3));
                mvprintw(current_y, current_x, white);
                attroff(COLOR_PAIR(3));
            }else{
                mvprintw(current_y, current_x, white);
            }
        }else{
            if (color) {
                attron(COLOR_PAIR(2));
                mvprintw(current_y, current_x, black);
                attroff(COLOR_PAIR(2));
            }else{
                mvprintw(current_y, current_x, black);
            }
        }
        current_y=next_y;
        current_x=next_x;
        current_grid=next_grid;
        current_state=next_state;
        if (color) {
            if (current_grid==-1) {
                attron(COLOR_PAIR(4));
            }else{
                attron(COLOR_PAIR(5));
            }
            mvprintw(current_y,current_x,ant[current_state-1]);
            if (current_grid==-1) {
                attroff(COLOR_PAIR(4));
            }else{
                attroff(COLOR_PAIR(5));
            }
        }else{
            mvprintw(current_y,current_x,ant[current_state-1]);
        }
        refresh();
    }
    //finish game
    button=0;
    while (button!=' ') {
        clear();
        getmaxyx(stdscr,row,col);
        if (color) {
            attron(COLOR_PAIR(1));
        }
        mvprintw(row/2, col/2-10, "Thank you -- pikipity");
        mvprintw(row/2+1, col/2-12, "Press \"Space\" to finish");
        refresh();
        if (color) {
            attroff(COLOR_PAIR(1));
        }
        button=getch();
    }
    endwin();
}

