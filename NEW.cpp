// *  THE ULTIMATE TIC-TAC-TOE GAME !  

#include <vector>
#include <conio.h>
#include <unistd.h>
#include <iostream>
#include <algorithm>
#include "textstyling.h"
#include "util.h"
#define MAX_outer 9
#define MAX_inner 3

static int x = 0;
static int y = 0;
static int X_Min = 0;
static int Y_Min = 0;
static int X_Max = 3;
static int Y_Max = 3;
std::string msg = "";

bool tabEnable = true;
std::vector<std::vector<char>> grid = {
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
//? status(((x-coordinate, y-coordinate), won), who ) : 
std::vector <std::pair<std::pair<std::pair<int, int>, bool>, char>> status;

void display();
void move(char key);
void place(char player);
void playerMove(char player);
void switchGrid(int i_x, int i_y);
int getGridNumber(int curr_x, int curr_y);
void displayMsg(int x, int y, std::string msg, const char* color);

std::vector<std::vector<char>> extractSubMatrix(std::vector<std::vector<char>>& mainMatrix, int startRow, int startCol) {
    std::vector<std::vector<char>> subMatrix(3, std::vector<char>(3, ' '));
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            subMatrix[i][j] = mainMatrix[startRow + i][startCol + j];
        }
    }
    return subMatrix;
}

bool checkWin() {
    for(int i=0; i<9; i+=3) {
        for(int j=0; j<9; j+=3) {
            std::vector<std::vector<char>> subMatrix = extractSubMatrix(grid, i, j);

            // Process the 3x3 submatrix (for demonstration, just printing it)....
            std::cout << "Submatrix at (" << i << ", " << j << "):\n";
            for (auto& row : subMatrix) {
                for (char cell : row) {
                    std::cout << cell << ' ';
                }
                std::cout << '\n';
            }
        }
    }
    // LOGIC REMAINING.....
}

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
    int gridNo = getGridNumber(i_x, i_y);
    // add a condition....if status is true (already visited), then dont call getGridNumber, directly get coordinates from status....
    // if(status[gridNo].first.second) { // means, grid already won....
    //     gridNo = getGridNumber(status[gridNo].first.first.first, status[gridNo].first.first.second);
    // }
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

void displayMsg(int x, int y, std::string msg, const char* color) {
    util::gotoXY(x, y);
    std::cout << color << msg << RESET;
    sleep(2);
    util::clearXY(x, y, msg.length());
}
void display() {
    system("cls");
    std::cout << CYAN_TEXT << "              'ULTIMATE' TIC-TAC-TOE" << RESET << std::endl;
    std::cout << "ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿  ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿" << std::endl;
    std::cout << "³  ÚÄÄÄÂÄÄÄÂÄÄÄ¿ º ÚÄÄÄÂÄÄÄÂÄÄÄ¿ º ÚÄÄÄÂÄÄÄÂÄÄÄ¿  ³  ³ GAME STATISTICS :                                ³" << std::endl;
    std::cout << "³  ³   ³   ³   ³ º ³   ³   ³   ³ º ³   ³   ³   ³  ³  ³                                                  ³" << std::endl;
    std::cout << "³  ÃÄÄÄÅÄÄÄÅÄÄÄ´ º ÃÄÄÄÅÄÄÄÅÄÄÄ´ º ÃÄÄÄÅÄÄÄÅÄÄÄ´  ³  ³                                                  ³" << std::endl;
    std::cout << "³  ³   ³   ³   ³ º ³   ³   ³   ³ º ³   ³   ³   ³  ³  ³     PLAYER 1  :                                  ³" << std::endl;
    std::cout << "³  ÃÄÄÄÅÄÄÄÅÄÄÄ´ º ÃÄÄÄÅÄÄÄÅÄÄÄ´ º ÃÄÄÄÅÄÄÄÅÄÄÄ´  ³  ³     Name   :                                     ³" << std::endl;
    std::cout << "³  ³   ³   ³   ³ º ³   ³   ³   ³ º ³   ³   ³   ³  ³  ³     Symbol : X                                   ³" << std::endl;
    std::cout << "³  ÀÄÄÄÁÄÄÄÁÄÄÄÙ º ÀÄÄÄÁÄÄÄÁÄÄÄÙ º ÀÄÄÄÁÄÄÄÁÄÄÄÙ  ³  ³                                                  ³" << std::endl;
    std::cout << "³  ÍÍÍÍÍÍÍÍÍÍÍÍÍÍÎÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÎÍÍÍÍÍÍÍÍÍÍÍÍÍÍ  ³  ³     PLAYER 2  :                                  ³" << std::endl;
    std::cout << "³  ÚÄÄÄÂÄÄÄÂÄÄÄ¿ º ÚÄÄÄÂÄÄÄÂÄÄÄ¿ º ÚÄÄÄÂÄÄÄÂÄÄÄ¿  ³  ³     Name   :                                     ³" << std::endl;
    std::cout << "³  ³   ³   ³   ³ º ³   ³   ³   ³ º ³   ³   ³   ³  ³  ³     Symbol : O                                   ³" << std::endl;
    std::cout << "³  ÃÄÄÄÅÄÄÄÅÄÄÄ´ º ÃÄÄÄÅÄÄÄÅÄÄÄ´ º ÃÄÄÄÅÄÄÄÅÄÄÄ´  ³  ³                                                  ³" << std::endl;   
    std::cout << "³  ³   ³   ³   ³ º ³   ³   ³   ³ º ³   ³   ³   ³  ³  ³     ERROR :                                      ³" << std::endl;
    std::cout << "³  ÃÄÄÄÅÄÄÄÅÄÄÄ´ º ÃÄÄÄÅÄÄÄÅÄÄÄ´ º ÃÄÄÄÅÄÄÄÅÄÄÄ´  ³  ³                                                  ³" << std::endl;
    std::cout << "³  ³   ³   ³   ³ º ³   ³   ³   ³ º ³   ³   ³   ³  ³  ³                                                  ³" << std::endl;
    std::cout << "³  ÀÄÄÄÁÄÄÄÁÄÄÄÙ º ÀÄÄÄÁÄÄÄÁÄÄÄÙ º ÀÄÄÄÁÄÄÄÁÄÄÄÙ  ³  ³                                                  ³" << std::endl;
    std::cout << "³  ÍÍÍÍÍÍÍÍÍÍÍÍÍÍÎÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÎÍÍÍÍÍÍÍÍÍÍÍÍÍÍ  ³  ³                                                  ³" << std::endl;
    std::cout << "³  ÚÄÄÄÂÄÄÄÂÄÄÄ¿ º ÚÄÄÄÂÄÄÄÂÄÄÄ¿ º ÚÄÄÄÂÄÄÄÂÄÄÄ¿  ³  ³                                                  ³" << std::endl;
    std::cout << "³  ³   ³   ³   ³ º ³   ³   ³   ³ º ³   ³   ³   ³  ³  ³                                                  ³" << std::endl;
    std::cout << "³  ÃÄÄÄÅÄÄÄÅÄÄÄ´ º ÃÄÄÄÅÄÄÄÅÄÄÄ´ º ÃÄÄÄÅÄÄÄÅÄÄÄ´  ³  ³                                                  ³" << std::endl;
    std::cout << "³  ³   ³   ³   ³ º ³   ³   ³   ³ º ³   ³   ³   ³  ³  ³                                                  ³" << std::endl;
    std::cout << "³  ÃÄÄÄÅÄÄÄÅÄÄÄ´ º ÃÄÄÄÅÄÄÄÅÄÄÄ´ º ÃÄÄÄÅÄÄÄÅÄÄÄ´  ³  ³                                                  ³" << std::endl;
    std::cout << "³  ³   ³   ³   ³ º ³   ³   ³   ³ º ³   ³   ³   ³  ³  ³                                                  ³" << std::endl;
    std::cout << "³  ÀÄÄÄÁÄÄÄÁÄÄÄÙ º ÀÄÄÄÁÄÄÄÁÄÄÄÙ º ÀÄÄÄÁÄÄÄÁÄÄÄÙ  ³  ³                                                  ³" << std::endl; 
    std::cout << "ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ  ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ" << std::endl;  
}
void place(char player) {
    tabEnable = false; // to disable the 'tab' functionality, after player makes his first move....

    if(player == 'X') {
        if(grid[y][x] == ' ') { // (y,x) since, arrow keys (x,y) == grid (y,x).
            grid[y][x] = 'X';

            // placing on the display grid....
            util::gotoXY(util::getXCoordinates(x), util::getYCoordinates(y)); // goto coordinate position (x,y),
            std::cout << "X"; // place character.
            switchGrid(x, y);
        } else { 
            msg = "Invalid move ! Try again....";
            displayMsg(68, 14, msg, RED_TEXT);
            playerMove('X'); // allow player to play correct move again...
        }
    } else { 
        if(grid[y][x] == ' ') { 
            grid[y][x] = 'O'; 

            // placing on the display grid....
            util::gotoXY(util::getXCoordinates(x), util::getYCoordinates(y)); // goto coordinate position (x,y),
            std::cout << "O"; // place character.
            switchGrid(x, y);
        } else { 
            msg = "Invalid move ! Try again....";
            displayMsg(68, 14, msg, RED_TEXT);
            playerMove('O');
        }
    }
}

void move(char key) {
    if(key == 72 && y > Y_Min) { y--; } // Up arrow key...
    else if(key == 80 && y < Y_Max-1) { y++; } // Down arrow key...
    else if(key == 75 && x > X_Min) { x--; } // Left arrow key...
    else if(key == 77 && x < X_Max-1) { x++; } // Right arrow key...
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
        if (key == 27) { // escape key, to exit....
            msg = "Current Progress will be lost...."; displayMsg(68, 14, msg, RED_TEXT);
            util::gotoXY(68, 14);
            msg = "Do you wish to continue ? "; std::cout << RED_TEXT << msg << GREEN_TEXT;
            char confirm;
            std::cin >> confirm;
            std::cout << RESET; 
            util::clearXY(68, 14, msg.length() + 11);
            if(confirm == 'Y' || confirm == 'y') { 
                displayMsg(68, 14, "Exiting !....", RED_TEXT);
                system("cls");
                exit(1);
            } else {
                // continue the game....
            }
        }
        else if(key == 9) { // tab key, to change tables....
            if(tabEnable) {
                generateCoordinatesTab();
            } else {
                msg = "Cannot switch grids after move....";
                displayMsg(68, 14, msg, RED_TEXT);
            }
        }
        else if ((key == 72) || (key == 80) || (key == 75) || (key == 77)) {  // arrow keys....
            move(key); 
        }
        else if (key == 13) {  // enter key, to make a move....
            if(player == 'X') { 
                place('X');
                break; // after player makes a move, exit the while loop....
            }
            else { 
                place('O');
                break;
            }
        }
        char highlight = 219;
        util::gotoXY(util::getXCoordinates(x), util::getYCoordinates(y)); // to indicate current position....
    }
}
void initPlayers() { // sets the player details....
    std::string player_1;
    std::string player_2;

    display();
    util::gotoXY(60, 17);
    std::cout << CYAN_TEXT << "Enter Player 1 name : " << RESET; 
    getline(std::cin, player_1);
    util::gotoXY(69, 7);
    std::cout << player_1;
    util::clearXY(82, 17, player_1.length());
    
    util::gotoXY(60, 17);
    std::cout << CYAN_TEXT << "Enter Player 2 name : " << RESET; getline(std::cin, player_2);
    util::gotoXY(69, 11);
    std::cout << player_2;
    util::gotoXY(60, 17);
    util::clearXY(60, 17, (22+player_2.length()));
    displayMsg(69, 17, "***** GAME BEGINS *****", CYAN_TEXT);
}

int main() {
    
    initPlayers();
    while(true) {
        util::gotoXY(58, 10); std::cout << "  ";util::gotoXY(58, 6); std::cout << GREEN_TEXT << "> " << RESET; playerMove('X');
        util::gotoXY(58, 6); std::cout << "  ";util::gotoXY(58, 10); std::cout << GREEN_TEXT << "> " << RESET; playerMove('O');
        
        //? DEBUGGING PURPOSE....

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
        // checkWin();
    }
    return 0;
}
