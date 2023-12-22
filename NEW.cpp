#include <iostream>
#include <vector>
#include <conio.h>
#include <unistd.h>
#include <stdexcept>
#include <algorithm>

#include "textstyling.h"
#include "util.h"
#define MAX_outer 9
#define MAX_inner 3

int x = 0;
int y = 0;
static int X_Min = 0;
static int Y_Min = 0;
static int X_Max = 3;
static int Y_Max = 3;

bool tabEnable = true;
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
std::vector <std::pair<std::pair <int, int>, bool>> status;

void display();
void move(char key);
void place(char player);
void playerMove(char player);
void switchGrid(int i_x, int i_y);
int getGridNumber(int curr_x, int curr_y);

int getGridNumber(int curr_x, int curr_y) {
    std::vector<std::vector<std::pair<int, int>>> grids = {
        {{0,0},{3,0},{6,0},{0,3},{3,3},{6,3},{0,6},{3,6},{6,6}},
        {{1,0},{4,0},{7,0},{1,3},{4,3},{7,3},{1,6},{4,6},{7,6}},
        {{2,0},{5,0},{8,0},{2,3},{5,3},{8,3},{2,6},{5,6},{8,6}},
        {{0,1},{3,1},{6,1},{0,4},{3,4},{6,4},{0,7},{3,7},{6,7}},
        {{1,1},{4,1},{7,1},{1,4},{4,4},{7,4},{1,7},{4,7},{7,7}},
        {{2,1},{5,1},{8,1},{2,4},{5,4},{8,4},{2,7},{5,7},{8,7}},
        {{0,2},{3,2},{6,2},{0,5},{3,5},{6,5},{0,8},{3,8},{6,8}},
        {{1,2},{4,2},{7,2},{1,5},{4,5},{7,5},{1,8},{4,8},{7,8}},
        {{2,2},{5,2},{8,2},{2,5},{5,5},{8,5},{2,8},{5,8},{8,8}}
    };
    std::vector<std::pair<int, int>> currCoordinates = {{curr_x, curr_y}};
    for (int i=0; i<9; i++) {
        const auto& grid = grids[i];
        if (std::find(grid.begin(), grid.end(), currCoordinates[0]) != grid.end()) {
            return i + 1;
        }
    }
    return -1;
}

void switchGrid(int i_x, int i_y) {
    // std::cout << "HERE\t";
    int gridNo = getGridNumber(i_x, i_y);
    if (gridNo >= 1 && gridNo <= 9) {
        int row = (gridNo - 1) / 3;
        int col = (gridNo - 1) % 3;
        x = col * 3;
        y = row * 3;
        X_Min = x;
        Y_Min = y;
        X_Max = x + 3;
        Y_Max = y + 3;
    }
}

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

    if(player == 'X') {
        if(grid[y][x] == ' ') { // (y,x) since, arrow keys (x,y) == grid (y,x).
            grid[y][x] = 'X';

            // placing on the display grid....
            util::gotoXY(util::getXCoordinates(x), util::getYCoordinates(y)); // goto coordinate position (x,y),
            std::cout << "X"; // place character.
        } else { 
            []() {
                util::gotoXY(50, 4);
                std::string ERROR = "ERROR : Invalid move ! Try again....";
                std::cout << ERROR;
                sleep(2);
                util::clearAtXY(50, 4, ERROR.length());
            }();
            playerMove('X'); // allow player to play correct move again...
        }
    } else { 
        if(grid[y][x] == ' ') { 
            grid[y][x] = 'O'; 

            // placing on the display grid....
            util::gotoXY(util::getXCoordinates(x), util::getYCoordinates(y)); // goto coordinate position (x,y),
            std::cout << "O"; // place character.
        } else { 
            []() {
                util::gotoXY(50, 4);
                std::string ERROR = "ERROR : Invalid move ! Try again....";
                std::cout << ERROR;
                sleep(2);
                util::clearAtXY(50, 4, ERROR.length());
            }();
            playerMove('O');
        }
    }
}

void move(char key) {
    if(key == 72 && y > Y_Min) { y--; } // Up arrow key...
    else if(key == 80 && y < Y_Max-1) { y++; } // Down arrow key...
    else if(key == 75 && x > X_Min) { x--; } // Left arrow key...
    else if(key == 77 && x <X_Max-1) { x++; } // Right arrow key...
}

void playerMove(char player) { 
    int key;
    util::gotoXY(util::getXCoordinates(x), util::getYCoordinates(y)); // to indicate current position....

    auto generateCoordinatesTab = [&]() { // lambda function to generate coordinates on tab clicks....
        static int tabCounter = 1;
        const int coordinates[][2] = { {0,0},{1,0},{2,0},{0,1},{1,1},{2,1},{0,2},{1,2},{2,2} };
        switchGrid(coordinates[tabCounter][0], coordinates[tabCounter][1]);
        tabCounter = (tabCounter + 1) % 9;
    };
    while(true) {
        key = _getch();
        if (key == 27) { system("cls"); exit(1); } // escape key, to exit....//=> Escape logic here.
        else if(key == 9) { // tab key, to change tables....
            if(tabEnable) {
                generateCoordinatesTab();
            } else {
                []() {
                    util::gotoXY(50, 4);
                    std::string ERROR = "ERROR : Cannot switch grids after move....";
                    std::cout << ERROR;
                    sleep(2);
                    util::clearAtXY(50, 4, ERROR.length());
                }();
            }
        }
        else if ((key == 72) || (key == 80) || (key == 75) || (key == 77)) { 
            move(key); 
        }
        else if (key == 13) {  // enter key, to make a move....
            if(player == 'X') { 
                place('X');
                switchGrid(x, y); // to automatically switch tables based on the move made by player....
                break; // after player makes a move, exit the while loop....
            }
            else { 
                place('O');
                switchGrid(x, y);
                break; // after player makes a move, exit the while loop....
            }
        }
        util::gotoXY(util::getXCoordinates(x), util::getYCoordinates(y)); // to indicate current position....        
    }
}

int main() {
    display();
    while(true) {
        playerMove('X');
        playerMove('O');
        // playerMove('X');
        // playerMove('O');
        // playerMove('X');
        // playerMove('O');
        // playerMove('X');
        // playerMove('O');
        // system("pause");
        // util::gotoXY(0,28);
        // for(int i=0; i<MAX_outer; i++) { // just to check the i/p to array(inverted)....
        //     for(int j=0; j<MAX_outer; j++) {
        //         std::cout << " | " << grid[i][j];
        //     }
        //     std::cout << std::endl;
        // }
        // system("pause");
    }
    
    return 0;
}
