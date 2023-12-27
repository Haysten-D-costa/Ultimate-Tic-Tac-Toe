// *  THE ULTIMATE TIC-TAC-TOE GAME !  

#include <vector>
#include <conio.h>
#include <utility>
#include <unistd.h>
#include <iostream>
#include <algorithm>
#include "util.h"
#include "textstyling.h"
#define MAX_outer 9
#define MAX_inner 3

static int x = 0;
static int y = 0;
static int X_Min = 0;
static int Y_Min = 0;
static int X_Max = 3;
static int Y_Max = 3;
std::string player_1;
std::string player_2;
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
std::vector<std::vector<std::pair<int, int>>> goto_coordinates_grid = {
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
std::vector<std::vector<char>> finalWin = {{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};
std::vector<std::pair<int, bool>> status(9, std::make_pair(0, false)); // initially, all 0, and false....

void display();
void move(char key);
void place(char player);
void playerMove(char player);
void switchGrid(int i_x, int i_y);
int getGridNumber(int curr_x, int curr_y);
void displayMsg(int x, int y, std::string msg, const char* color);
char checkWinInSubMatrix(const std::vector<std::vector<char>>& subMatrix);
std::vector<std::vector<char>> extractSubMatrix(std::vector<std::vector<char>>& mainMatrix, int startRow, int startCol);

int getSubgridNumber(int i, int j) { // returns the grid in which current player played (1, 2, 3, 4, 5, 6, 7, 8 or 9)....
    int subgridRow = j / 3;
    int subgridCol = i / 3;
    int subgridNumber = subgridRow * 3 + subgridCol + 1;
    return subgridNumber;
}

int getGridNumber(int curr_x, int curr_y) { // returns the grid in which next player can play.... 
    std::vector<std::pair<int, int>> currCoordinates = {{curr_x, curr_y}};
    for (int i=0; i<9; i++) {
        const auto& grid = goto_coordinates_grid[i];
        if (std::find(grid.begin(), grid.end(), currCoordinates[0]) != grid.end()) {
            return i + 1;
        }
    }
    return -1;
}

void switchGrid(int i_x, int i_y) {
    int visitedGrids = 0;
    int gridNo = getGridNumber(i_x, i_y);

    while (gridNo >= 1 && gridNo <= 9 && status[gridNo].second) {
        // If the current grid is won, move to the next grid indicated by status[gridNo].first....
        gridNo = status[gridNo].first;

        ++visitedGrids;
        if ((visitedGrids > 9) && (!checkWinInSubMatrix(extractSubMatrix(grid, Y_Min, X_Min)) != ' ')) {
            tabEnable = true; // if deadlock, allow the player to tab to any board required....
            util::gotoXY(68, 14); std::cout << RED_TEXT << "No more valid moves possible...." << RESET;
            displayMsg(69, 17, "***** GAME OVER ! *****", RED_TEXT);
            util::clearXY(68, 14, 32);
        }
    }
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
    std::cout << CYAN_TEXT << "              'ULTIMATE' TIC-TAC-TOE" << RESET << std::endl
              << "ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿  ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿" << std::endl
              << "³  ÚÄÄÄÂÄÄÄÂÄÄÄ¿ º ÚÄÄÄÂÄÄÄÂÄÄÄ¿ º ÚÄÄÄÂÄÄÄÂÄÄÄ¿  ³  ³ " << CYAN_BACKGROUND << "               " << RESET << CYAN_TEXT << " GAME STATISTICS " << RESET << CYAN_BACKGROUND << "               " << RESET << " ³" << std::endl
              << "³  ³   ³   ³   ³ º ³   ³   ³   ³ º ³   ³   ³   ³  ³  ÃÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ´" << std::endl
              << "³  ÃÄÄÄÅÄÄÄÅÄÄÄ´ º ÃÄÄÄÅÄÄÄÅÄÄÄ´ º ÃÄÄÄÅÄÄÄÅÄÄÄ´  ³  ³                                                 ³" << std::endl
              << "³  ³   ³   ³   ³ º ³   ³   ³   ³ º ³   ³   ³   ³  ³  ³     " << CYAN_TEXT << "PLAYER 1  : " << RESET << "                                ³" << std::endl
              << "³  ÃÄÄÄÅÄÄÄÅÄÄÄ´ º ÃÄÄÄÅÄÄÄÅÄÄÄ´ º ÃÄÄÄÅÄÄÄÅÄÄÄ´  ³  ³     Name   :                                    ³" << std::endl
              << "³  ³   ³   ³   ³ º ³   ³   ³   ³ º ³   ³   ³   ³  ³  ³     Symbol : " << RED_TEXT << "'X'"<< RESET << "                                |" << std::endl
              << "³  ÀÄÄÄÁÄÄÄÁÄÄÄÙ º ÀÄÄÄÁÄÄÄÁÄÄÄÙ º ÀÄÄÄÁÄÄÄÁÄÄÄÙ  ³  ³                                                 ³" << std::endl
              << "³  ÍÍÍÍÍÍÍÍÍÍÍÍÍÍÎÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÎÍÍÍÍÍÍÍÍÍÍÍÍÍÍ  ³  ³     " << CYAN_TEXT << "PLAYER 2  : " << RESET << "                                ³" << std::endl
              << "³  ÚÄÄÄÂÄÄÄÂÄÄÄ¿ º ÚÄÄÄÂÄÄÄÂÄÄÄ¿ º ÚÄÄÄÂÄÄÄÂÄÄÄ¿  ³  ³     Name   :                                    ³" << std::endl
              << "³  ³   ³   ³   ³ º ³   ³   ³   ³ º ³   ³   ³   ³  ³  ³     Symbol : " << RED_TEXT << "'O'"<< RESET << "                                |" << std::endl
              << "³  ÃÄÄÄÅÄÄÄÅÄÄÄ´ º ÃÄÄÄÅÄÄÄÅÄÄÄ´ º ÃÄÄÄÅÄÄÄÅÄÄÄ´  ³  ³                                                 ³" << std::endl
              << "³  ³   ³   ³   ³ º ³   ³   ³   ³ º ³   ³   ³   ³  ³  ³     " << CYAN_TEXT << "ERROR : " << RESET << "                                    ³" << std::endl
              << "³  ÃÄÄÄÅÄÄÄÅÄÄÄ´ º ÃÄÄÄÅÄÄÄÅÄÄÄ´ º ÃÄÄÄÅÄÄÄÅÄÄÄ´  ³  ³                                                 ³" << std::endl
              << "³  ³   ³   ³   ³ º ³   ³   ³   ³ º ³   ³   ³   ³  ³  ³                                                 ³" << std::endl
              << "³  ÀÄÄÄÁÄÄÄÁÄÄÄÙ º ÀÄÄÄÁÄÄÄÁÄÄÄÙ º ÀÄÄÄÁÄÄÄÁÄÄÄÙ  ³  ³                                                 ³" << std::endl
              << "³  ÍÍÍÍÍÍÍÍÍÍÍÍÍÍÎÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÎÍÍÍÍÍÍÍÍÍÍÍÍÍÍ  ³  ³                                                 ³" << std::endl
              << "³  ÚÄÄÄÂÄÄÄÂÄÄÄ¿ º ÚÄÄÄÂÄÄÄÂÄÄÄ¿ º ÚÄÄÄÂÄÄÄÂÄÄÄ¿  ³  ³                                                 ³" << std::endl
              << "³  ³   ³   ³   ³ º ³   ³   ³   ³ º ³   ³   ³   ³  ³  ³                                                 ³" << std::endl
              << "³  ÃÄÄÄÅÄÄÄÅÄÄÄ´ º ÃÄÄÄÅÄÄÄÅÄÄÄ´ º ÃÄÄÄÅÄÄÄÅÄÄÄ´  ³  ³                                                 ³" << std::endl
              << "³  ³   ³   ³   ³ º ³   ³   ³   ³ º ³   ³   ³   ³  ³  ³                                                 ³" << std::endl
              << "³  ÃÄÄÄÅÄÄÄÅÄÄÄ´ º ÃÄÄÄÅÄÄÄÅÄÄÄ´ º ÃÄÄÄÅÄÄÄÅÄÄÄ´  ³  ³                                                 ³" << std::endl
              << "³  ³   ³   ³   ³ º ³   ³   ³   ³ º ³   ³   ³   ³  ³  ³                                                 ³" << std::endl
              << "³  ÀÄÄÄÁÄÄÄÁÄÄÄÙ º ÀÄÄÄÁÄÄÄÁÄÄÄÙ º ÀÄÄÄÁÄÄÄÁÄÄÄÙ  ³  ³                                                 ³" << std::endl
          << "ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ  ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ" << std::endl;
}

std::vector<std::vector<char>> extractSubMatrix(std::vector<std::vector<char>>& mainMatrix, int startRow, int startCol) { // function to extract sub-goto_coordinates_grid(3x3 goto_coordinates_grid) from the main 9x9 matrix grid.....
    std::vector<std::vector<char>> subMatrix(3, std::vector<char>(3, ' '));
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            subMatrix[i][j] = mainMatrix[startRow + i][startCol + j];
        }
    }
    return subMatrix;
}
char checkWinInSubMatrix(const std::vector<std::vector<char>>& subMatrix) {
    // Check rows and columns for a win....
    for (int i = 0; i < 3; ++i) {
        if (subMatrix[i][0] == subMatrix[i][1] && subMatrix[i][1] == subMatrix[i][2] && subMatrix[i][0] != ' ') { return subMatrix[i][0]; } // returns winning symbol....
        if (subMatrix[0][i] == subMatrix[1][i] && subMatrix[1][i] == subMatrix[2][i] && subMatrix[0][i] != ' ') { return subMatrix[0][i]; }
    }
    // Check diagonals for a win....
    if (subMatrix[0][0] == subMatrix[1][1] && subMatrix[1][1] == subMatrix[2][2] && subMatrix[0][0] != ' ') { return subMatrix[0][0]; }
    if (subMatrix[0][2] == subMatrix[1][1] && subMatrix[1][1] == subMatrix[2][0] && subMatrix[0][2] != ' ') { return subMatrix[0][2]; }

    // Check for a draw
    bool isDraw = true;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (subMatrix[i][j] == ' ') {
                isDraw = false;
                break;
            }
        }
    }
    if (isDraw) { return 'D'; }
    return ' '; // No win or draw....
}

void clearWonGrid() {
    util::clearXY(util::getXCoordinates(X_Min)-1, util::getYCoordinates(Y_Min), 11);
    util::clearXY(util::getXCoordinates(X_Min)-1, util::getYCoordinates(Y_Min+1), 11);
    util::clearXY(util::getXCoordinates(X_Min)-1, util::getYCoordinates(Y_Min+1)-1, 11);
    util::clearXY(util::getXCoordinates(X_Min)-1, util::getYCoordinates(Y_Min+2), 11);
    util::clearXY(util::getXCoordinates(X_Min)-1, util::getYCoordinates(Y_Min+2)-1, 11);
}


void place(char player) {
   tabEnable = false; // to disable the 'tab' functionality, after player makes his first move....

    if(player == 'X') {
        if(grid[y][x] == ' ') { // (y,x) since, arrow keys (x,y) == grid (y,x).
            grid[y][x] = 'X';

            if(checkWinInSubMatrix(extractSubMatrix(grid, Y_Min, X_Min)) != ' ') {
                int gNo = getSubgridNumber(x, y);
                int row = (gNo - 1) / 3;
                int col = (gNo - 1) % 3;
                finalWin[row][col] = 'X'; // updates the finalWin matrix....
                
                status[gNo].first = getGridNumber(x, y);
                status[gNo].second = true;
            }
            
            // placing on the display grid....
            util::gotoXY(util::getXCoordinates(x), util::getYCoordinates(y)); // goto coordinate position (x,y),
            std::cout << "X"; // place character....
            switchGrid(x, y);
        } else { 
            displayMsg(68, 14, "Invalid move ! Try again....", RED_TEXT);
            playerMove('X'); // allow player to play correct move again....
        }
    } else { 
        if(grid[y][x] == ' ') { 
            grid[y][x] = 'O'; 

            if(checkWinInSubMatrix(extractSubMatrix(grid, Y_Min, X_Min)) != ' ') {
                int gNo = getSubgridNumber(x, y);
                int row = (gNo - 1) / 3;
                int col = (gNo - 1) % 3;
                finalWin[row][col] = 'O'; // updates the finalWin matrix....
                
                status[gNo].first = getGridNumber(x, y);
                status[gNo].second = true;
            }

            // placing on the display grid....
            util::gotoXY(util::getXCoordinates(x), util::getYCoordinates(y)); // goto coordinate position (x,y),
            std::cout << "O"; // place character....
            switchGrid(x, y);
        } else {
            displayMsg(68, 14, "Invalid move ! Try again....", RED_TEXT);
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
            displayMsg(68, 14, "Current Progress will be lost....", RED_TEXT);
            util::gotoXY(68, 14);
            std::string msg = "";
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
                displayMsg(68, 14, "Cannot switch grids after move....", RED_TEXT);
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
    display();
    util::gotoXY(60, 17);
    std::cout << GREEN_TEXT << "Enter Player 1 name : " << RESET; 
    getline(std::cin, player_1);
    util::gotoXY(69, 7);
    std::cout << player_1;
    util::clearXY(82, 17, player_1.length());
    
    util::gotoXY(60, 17);
    std::cout << GREEN_TEXT << "Enter Player 2 name : " << RESET; getline(std::cin, player_2);
    util::gotoXY(69, 11);
    std::cout << player_2;
    util::gotoXY(60, 17);
    util::clearXY(60, 17, (22+player_2.length()));
    displayMsg(69, 17, "***** GAME BEGINS *****", RED_TEXT);
}

int main() {
    
    char result;
    initPlayers();
    while(true) {
        util::gotoXY(58, 10); std::cout<< "  "; util::gotoXY(58, 6); std::cout << GREEN_TEXT << "> " << RESET; playerMove('X');
        result = checkWinInSubMatrix(finalWin);
        if(result == 'D') { 
            util::gotoXY(67, 17); 
            std::cout << GREEN_TEXT << "ITS A DRAW !" << RESET;
            util::gotoXY(0, 28);
            exit(1);
        } else if(result == 'X') {
            util::gotoXY(67, 17); 
            std::cout << GREEN_TEXT << player_1 << " is the WINNER !" << RESET;
            util::gotoXY(0, 28);
            exit(1);
        } else if(result == 'O') {
            util::gotoXY(67, 17); 
            std::cout << GREEN_TEXT << player_2 << " is the WINNER !" << RESET;
            util::gotoXY(0, 28);
            exit(1);
        } else {
            // do nothing....
        }

        util::gotoXY(58, 6); std::cout << "  "; util::gotoXY(58, 10); std::cout << GREEN_TEXT << "> " << RESET; playerMove('O');
        result = checkWinInSubMatrix(finalWin);
        if(result == 'D') { 
            util::gotoXY(67, 17); 
            std::cout << GREEN_TEXT << "ITS A DRAW !" << RESET;
            util::gotoXY(0, 28);
            exit(1);
        } else if(result == 'X') {
            util::gotoXY(67, 17); 
            std::cout << GREEN_TEXT << player_1 << " is the WINNER !" << RESET;
            util::gotoXY(0, 28);
            exit(1);
        } else if(result == 'O') {
            util::gotoXY(67, 17); 
            std::cout << GREEN_TEXT << player_2 << " is the WINNER !" << RESET;
            util::gotoXY(0, 28);
            exit(1);
        } else {
            // do nothing....
        }
        util::gotoXY(0,35);
    }
    return 0;
}
