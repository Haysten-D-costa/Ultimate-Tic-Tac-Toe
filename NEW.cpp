#include <iostream>
#include <vector>
#include <conio.h>
#include "textstyling.h"
#include "util.h"
#include <unistd.h>
#define MAX 9

int x = 0;
int y = 0;
bool tabEnable = true;

char grid[MAX][MAX] = {
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
};
void display() {
    system("cls");
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
    // char(* ptr)[MAX]; // character pointer created, to access specific grids....
    
    // if(control == 0) { ptr = grid01; } // point to specific grids, as per the control....
    // else if(control == 1) { ptr = grid02; }
    // else if(control == 2) { ptr = grid03; }
    // else if(control == 3) { ptr = grid04; }
    // else if(control == 4) { ptr = grid05; }
    // else if(control == 5) { ptr = grid06; }
    // else if(control == 6) { ptr = grid07; }
    // else if(control == 7) { ptr = grid08; }
    // else if(control == 8) { ptr = grid09; }

    if(player == 'X') {
        if(grid[x][y] == ' ') {
            grid[x][y] = 'X';
            
            //! PLACING 'X'...
            util::gotoXY(util::getXCoordinates(x), util::getYCoordinates(y));
            std::cout << "X";

            // if(checkWinner(ptr)) { // if this current move is a winning move, then store the (x,y), 
            //                        // so that next time if any player selects the already won grid, then will go to the grid, got by last selected coordinates....
            //     winGrids[control+1] = 'X';
            //     status[control+1].second = true;
            //     status[control+1].first.first = x;
            //     status[control+1].first.second = y;
            // } 
            // else if(checkTie(ptr)) {
            //     winGrids[control+1] = '-';
            // }
            // storeControl();
        }
    } else { 
        if(grid[x][y] == ' ') { 
            grid[x][y] = 'O'; 

            //! PLACING 'O'...
            util::gotoXY(util::getXCoordinates(x), util::getYCoordinates(y));
            std::cout << "O";

            // if(checkWinner(ptr)) {
            //     winGrids[control+1] = 'O';
            //     status[control+1].second = true;
            //     status[control+1].first.first = x;
            //     status[control+1].first.second = y;
            // }
            //  else if(checkTie(ptr)) {
            //     winGrids[control+1] = '-';
            // }
            // storeControl();
        }
    }
}

void move(char key) {
    if(key == 72 && y > 0) { y--; } // Up arrow key...
    else if(key == 80 && y < MAX-1) { y++; } // Down arrow key...
    else if(key == 75 && x > 0) { x--; } // Left arrow key...
    else if(key == 77 && x <MAX-1) { x++; } // Right arrow key...
}
void playerMove(char player) { 
    int key;
    while(true) {
        key = _getch();
        if (key == 27) { system("cls"); exit(1); } // escape key, to exit....
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
        util::gotoXY(util::getXCoordinates(x), util::getYCoordinates(y));
    }
}

int main() {
    while(true) {
        system("cls");
        display();
        playerMove('X');
        playerMove('O');
        playerMove('X');
        playerMove('O');
        playerMove('X');
        playerMove('O');
        playerMove('X');
        playerMove('O');
        system("pause");
        for(int i=0; i<MAX; i++) { // just to check the i/p to array(inverted)....
            for(int j=0; j<MAX; j++) {
                std::cout << grid[i][j] << "  ";
            }
            std::cout << std::endl;
        }
        system("pause");
    }
    return 0;
}