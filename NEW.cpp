#include <iostream>
#include <vector>
#include <conio.h>
#include <unistd.h>
#include "textstyling.h"
#include "util.h"
#define MAX_outer 9
#define MAX_inner 3

int x = 0;
int y = 0;
bool tabEnable = true;

std::vector <std::pair<std::pair <int, int>, bool>> status;

void display();
void switchTable();
void move(char key);
void place(char player);
void playerMove(char player);

char grid[MAX_outer][MAX_outer] = {
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
};

void display() {
    system("cls");
    std::cout << CYAN_TEXT << "            'ULTIMATE' TIC-TAC-TOE" << RESET << std::endl << std::endl;
    // std::cout << "ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ" << std::endl;
    std::cout << "ÚÄÄÄÂÄÄÄÂÄÄÄ¿ º ÚÄÄÄÂÄÄÄÂÄÄÄ¿ º ÚÄÄÄÂÄÄÄÂÄÄÄ¿" << std::endl;
    std::cout << "³   ³   ³   ³ º ³   ³   ³   ³ º ³   ³   ³   ³" << std::endl;
    std::cout << "ÃÄÄÄÅÄÄÄÅÄÄÄ´ º ÃÄÄÄÅÄÄÄÅÄÄÄ´ º ÃÄÄÄÅÄÄÄÅÄÄÄ´" << std::endl;
    std::cout << "³   ³   ³   ³ º ³   ³   ³   ³ º ³   ³   ³   ³" << std::endl;
    std::cout << "ÃÄÄÄÅÄÄÄÅÄÄÄ´ º ÃÄÄÄÅÄÄÄÅÄÄÄ´ º ÃÄÄÄÅÄÄÄÅÄÄÄ´" << std::endl;
    std::cout << "³   ³   ³   ³ º ³   ³   ³   ³ º ³   ³   ³   ³" << std::endl;
    std::cout << "ÀÄÄÄÁÄÄÄÁÄÄÄÙ º ÀÄÄÄÁÄÄÄÁÄÄÄÙ º ÀÄÄÄÁÄÄÄÁÄÄÄÙ" << std::endl;
    std::cout << "ÍÍÍÍÍÍÍÍÍÍÍÍÍÍÎÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÎÍÍÍÍÍÍÍÍÍÍÍÍÍÍ" << std::endl;
    std::cout << "ÚÄÄÄÂÄÄÄÂÄÄÄ¿ º ÚÄÄÄÂÄÄÄÂÄÄÄ¿ º ÚÄÄÄÂÄÄÄÂÄÄÄ¿" << std::endl;
    std::cout << "³   ³   ³   ³ º ³   ³   ³   ³ º ³   ³   ³   ³" << std::endl;
    std::cout << "ÃÄÄÄÅÄÄÄÅÄÄÄ´ º ÃÄÄÄÅÄÄÄÅÄÄÄ´ º ÃÄÄÄÅÄÄÄÅÄÄÄ´" << std::endl;
    std::cout << "³   ³   ³   ³ º ³   ³   ³   ³ º ³   ³   ³   ³" << std::endl;
    std::cout << "ÃÄÄÄÅÄÄÄÅÄÄÄ´ º ÃÄÄÄÅÄÄÄÅÄÄÄ´ º ÃÄÄÄÅÄÄÄÅÄÄÄ´" << std::endl;
    std::cout << "³   ³   ³   ³ º ³   ³   ³   ³ º ³   ³   ³   ³" << std::endl;
    std::cout << "ÀÄÄÄÁÄÄÄÁÄÄÄÙ º ÀÄÄÄÁÄÄÄÁÄÄÄÙ º ÀÄÄÄÁÄÄÄÁÄÄÄÙ" << std::endl;
    std::cout << "ÍÍÍÍÍÍÍÍÍÍÍÍÍÍÎÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÎÍÍÍÍÍÍÍÍÍÍÍÍÍÍ" << std::endl;
    std::cout << "ÚÄÄÄÂÄÄÄÂÄÄÄ¿ º ÚÄÄÄÂÄÄÄÂÄÄÄ¿ º ÚÄÄÄÂÄÄÄÂÄÄÄ¿" << std::endl;
    std::cout << "³   ³   ³   ³ º ³   ³   ³   ³ º ³   ³   ³   ³" << std::endl;
    std::cout << "ÃÄÄÄÅÄÄÄÅÄÄÄ´ º ÃÄÄÄÅÄÄÄÅÄÄÄ´ º ÃÄÄÄÅÄÄÄÅÄÄÄ´" << std::endl;
    std::cout << "³   ³   ³   ³ º ³   ³   ³   ³ º ³   ³   ³   ³" << std::endl;
    std::cout << "ÃÄÄÄÅÄÄÄÅÄÄÄ´ º ÃÄÄÄÅÄÄÄÅÄÄÄ´ º ÃÄÄÄÅÄÄÄÅÄÄÄ´" << std::endl;
    std::cout << "³   ³   ³   ³ º ³   ³   ³   ³ º ³   ³   ³   ³" << std::endl;
    std::cout << "ÀÄÄÄÁÄÄÄÁÄÄÄÙ º ÀÄÄÄÁÄÄÄÁÄÄÄÙ º ÀÄÄÄÁÄÄÄÁÄÄÄÙ" << std::endl;
}
void place(char player) {
    tabEnable = false; // to disable the 'tab' functionality, after player plays his first move....
    
    // char(* ptr)[MAX]; // for separate grids logic....
    // ptr = grid01;

    if(player == 'X') {
        if(grid[y][x] == ' ') { // (y,x) since, arrow keys (x,y) == grid (y,x).
            grid[y][x] = 'X';

            // placing on the display grid....
            util::gotoXY(util::getXCoordinates(x), util::getYCoordinates(y)); // goto coordinate position (x,y),
            std::cout << "X"; // place character.
        } else { 
            util::gotoXY(50, 4); // goto coordinate position (x,y),
            std::cout << "ERROR : Invalid move !"; 
            playerMove('X'); // allow player to play correct move again...
        }
    } else { 
        if(grid[y][x] == ' ') { 
            grid[y][x] = 'O'; 

            // placing on the display grid....
            util::gotoXY(util::getXCoordinates(x), util::getYCoordinates(y)); // goto coordinate position (x,y),
            std::cout << "O"; // place character.
        } else { 
            util::gotoXY(50, 4); // goto coordinate position (x,y),
            std::cout << "ERROR : Invalid move !"; 
            playerMove('O');
        }
    }
}

void move(char key) {
    if(key == 72 && y > 0) { y--; } // Up arrow key...
    else if(key == 80 && y < MAX_outer-1) { y++; } // Down arrow key...
    else if(key == 75 && x > 0) { x--; } // Left arrow key...
    else if(key == 77 && x <MAX_outer-1) { x++; } // Right arrow key...
}

void playerMove(char player) { 
    int key;
    while(true) {
        key = _getch();
        if (key == 27) { system("cls"); exit(1); } // escape key, to exit....//=> Escape logic here.
        else if(key == 9) { // tab key, to change tables....
            switchTable();
        }
        else if ((key == 72) || (key == 80) || (key == 75) || (key == 77)) { move(key); }
        else if (key == 13) {  // enter key, to make a move....
            if(player == 'X') { 
                place('X');
                break; // after player makes a move, exit the while loop....
            }
            else { 
                place('O');
                break; // after player makes a move, exit the while loop....
            }
        }
        util::gotoXY(util::getXCoordinates(x), util::getYCoordinates(y)); // to indicate current position....        
    }
}   
void switchTable() {
    x = 4;
    y = 3;
    util::gotoXY(util::getXCoordinates(4), util::getYCoordinates(3));
    
}

int main() {
    display();
    while(true) {
        playerMove('X');
        playerMove('O');
        playerMove('X');
        playerMove('O');
        playerMove('X');
        playerMove('O');
        playerMove('X');
        playerMove('O');
        system("pause");
        util::gotoXY(0,28);
        for(int i=0; i<MAX_outer; i++) { // just to check the i/p to array(inverted)....
            for(int j=0; j<MAX_outer; j++) {
                std::cout << " | " << grid[i][j];
            }
            std::cout << std::endl;
        }
        system("pause");
    }
    return 0;
}
