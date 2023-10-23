#include <iostream>
#include <vector>
#include <conio.h>
#include "textstyling.h"
#include <unistd.h>
#define MAX 3

int x = 0;
int y = 0;
int control = 0;
bool count = true;
std::vector <std::pair<std::pair <int, int>, bool>> status;

char plyr; // to check which player made the winning move...
char winGrids[10] = {' ', ' ', ' ', ' ', ' ', ' ', ' ',' ', ' ', ' '}; // the bigger grid....
char grid01[MAX][MAX] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
char grid02[MAX][MAX] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
char grid03[MAX][MAX] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
char grid04[MAX][MAX] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
char grid05[MAX][MAX] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
char grid06[MAX][MAX] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
char grid07[MAX][MAX] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
char grid08[MAX][MAX] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
char grid09[MAX][MAX] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};

bool finalWinner();
void display(); // Function to display the grids....
void storeControl(); // Function to auto transfer control on player move....
void place(char player); // Function to place 'X' or 'O' on respective grid respectively....
void playerMove(char player); // Function to enable player 1 to make a move....
bool checkTie(char grid[MAX][MAX]);
bool checkWinner(char grid[MAX][MAX]);

void clearScreen() {
    std::cout << "\033[2J\033[H"; // Clear screen and move cursor to (0,0)
}
void storeControl() {
    if ((x == 0) && (y == 0)) { control = 0; }
    else if ((x == 0) && (y == 1)) { control = 1; }
    else if ((x == 0) && (y == 2)) { control = 2; }
    else if ((x == 1) && (y == 0)) { control = 3; }
    else if ((x == 1) && (y == 1)) { control = 4; }
    else if ((x == 1) && (y == 2)) { control = 5; }
    else if ((x == 2) && (y == 0)) { control = 6; }
    else if ((x == 2) && (y == 1)) { control = 7; }
    else if ((x == 2) && (y == 2)) { control = 8; }
    
    if(status[control+1].second) { // if that grid is already won....
        x = status[control+1].first.first;
        y = status[control+1].first.second;
    }
    if ((x == 0) && (y == 0)) { control = 0; }
    else if ((x == 0) && (y == 1)) { control = 1; }
    else if ((x == 0) && (y == 2)) { control = 2; }
    else if ((x == 1) && (y == 0)) { control = 3; }
    else if ((x == 1) && (y == 1)) { control = 4; }
    else if ((x == 1) && (y == 2)) { control = 5; }
    else if ((x == 2) && (y == 0)) { control = 6; }
    else if ((x == 2) && (y == 1)) { control = 7; }
    else if ((x == 2) && (y == 2)) { control = 8; }
}
void place(char player) {
    
    count = false; // to disable the 'tab' functionality, after player plays his first move....
    char(* ptr)[MAX]; // character pointer created, to access specific grids....
    if(control == 0) { ptr = grid01; } // point to specific grids, as per the control....
    else if(control == 1) { ptr = grid02; }
    else if(control == 2) { ptr = grid03; }
    else if(control == 3) { ptr = grid04; }
    else if(control == 4) { ptr = grid05; }
    else if(control == 5) { ptr = grid06; }
    else if(control == 6) { ptr = grid07; }
    else if(control == 7) { ptr = grid08; }
    else if(control == 8) { ptr = grid09; }

    if(player == 'X') {
        if(ptr[x][y] == ' ') {
            ptr[x][y] = 'X';
            if(checkWinner(ptr)) { // if this current move is a winning move, then store the (x,y), 
                                   //so that next time if any player selects the already won grid, then will go to the grid, got by last selected coordinates....
                winGrids[control+1] = 'X';
                status[control+1].second = true;
                status[control+1].first.first = x;
                status[control+1].first.second = y;
                // std::cout << "X : " << x << " and Y : " << y;
                // system("pause");
            } 
            else if(checkTie(ptr)) {
                winGrids[control+1] = '-';
            }
            storeControl();
        }
    } else { 
        if(ptr[x][y] == ' ') { 
            ptr[x][y] = 'O'; 
            if(checkWinner(ptr)) {
                winGrids[control+1] = 'O';
                status[control+1].second = true;
                status[control+1].first.first = x;
                status[control+1].first.second = y;
                // std::cout << "X : " << x << " and Y : " << y;
                // system("pause");
            }
             else if(checkTie(ptr)) {
                winGrids[control+1] = '-';
            }
            storeControl();
        }
    }
}
void move(char key) {
    if(key == 72 && x > 0) { x--; }
    else if(key == 80 && x < MAX-1) { x++; }
    else if(key == 75 && y > 0) { y--; }
    else if(key == 77 && y <MAX-1) { y++; }
    // display();
}
void playerMove(char player) { 
    int key;
    while(true) {
        display();
        key = _getch();
        if (key == 27) { system("cls"); exit(1); } // escape key, to exit....
        else if (count == true && key == 9) { // tab key, to switch table....
            control++;
            if(control == 9) { control = 0; } 
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
        // system("pause");
    }
}
void display() {
    clearScreen(); // system("cls");
    std::cout << GREEN_TEXT << "+----+----+----+  " << RED_TEXT << "|" << GREEN_TEXT << "  +----+----+----+  " <<RED_TEXT << "|" << GREEN_TEXT << "  +----+----+----+" << RESET << std::endl;
    for(int i=0; i<MAX; i++) {
        for(int j=0; j<MAX; j++) {
            if(status[1].second) { std::cout << GREEN_TEXT << "| " << HIGHLIGHT << BLACK_TEXT << YELLOW_BACKGROUND << grid01[i][j] << " " << RESET << " "; }
            else if(i == x && j == y && control == 0) { std::cout << GREEN_TEXT << "| " << HIGHLIGHT << BLACK_TEXT << WHITE_BACKGROUND << grid01[i][j] << " " RESET << " "; } 
            else { std::cout << GREEN_TEXT << "| " << RESET << grid01[i][j] << "  "; }
        }
        std::cout << GREEN_TEXT << "|  " << RED_TEXT << "|" << RED_TEXT << "  " << RESET;
        for(int j=0; j<MAX; j++) {
            if(status[2].second) { std::cout << GREEN_TEXT << "| " << HIGHLIGHT << BLACK_TEXT << YELLOW_BACKGROUND << grid02[i][j] << " " << RESET << " "; }
            else if(i == x && j == y && control == 1) { std::cout << GREEN_TEXT << "| " << HIGHLIGHT << BLACK_TEXT << WHITE_BACKGROUND << grid02[i][j] << " " RESET << " "; } 
            else { std::cout << GREEN_TEXT << "| " << RESET << grid02[i][j] << "  "; }
        }
        std::cout << GREEN_TEXT << "|  " << RED_TEXT << "|" << RED_TEXT << "  " << RESET;
        for(int j=0; j<MAX; j++) {
            if(status[3].second) { std::cout << GREEN_TEXT << "| " << HIGHLIGHT << BLACK_TEXT << YELLOW_BACKGROUND << grid03[i][j] << " " << RESET << " "; }
            else if(i == x && j == y && control == 2) { std::cout << GREEN_TEXT << "| " << HIGHLIGHT << BLACK_TEXT << WHITE_BACKGROUND << grid03[i][j] << " " RESET << " "; } 
            else { std::cout << GREEN_TEXT << "| " << RESET << grid03[i][j] << "  "; }
        }
        std::cout << GREEN_TEXT << "|" << RESET << std::endl;
        std::cout << GREEN_TEXT << "+----+----+----+  " << RED_TEXT << "|" << GREEN_TEXT << "  +----+----+----+  " <<RED_TEXT << "|" << GREEN_TEXT << "  +----+----+----+" << RESET << std::endl;
    }
    std::cout << RED_TEXT << "------------------+--------------------+------------------" << std::endl;
    std::cout << GREEN_TEXT << "+----+----+----+  " << RED_TEXT << "|" << GREEN_TEXT << "  +----+----+----+  " <<RED_TEXT << "|" << GREEN_TEXT << "  +----+----+----+" << RESET << std::endl;
    for(int i=0; i<MAX; i++) {
        for(int j=0; j<MAX; j++) {
            if(status[4].second) { std::cout << GREEN_TEXT << "| " << HIGHLIGHT << BLACK_TEXT << YELLOW_BACKGROUND << grid04[i][j] << " " << RESET << " "; }
            else if(i == x && j == y && control == 3) { std::cout << GREEN_TEXT << "| " << HIGHLIGHT << BLACK_TEXT << WHITE_BACKGROUND << grid04[i][j] << " " RESET << " "; } 
            else { std::cout << GREEN_TEXT << "| " << RESET << grid04[i][j] << "  "; }
        }
        std::cout << GREEN_TEXT << "|  " << RED_TEXT << "|" << RED_TEXT << "  " << RESET;
        for(int j=0; j<MAX; j++) {
            if(status[5].second) { std::cout << GREEN_TEXT << "| " << HIGHLIGHT << BLACK_TEXT << YELLOW_BACKGROUND << grid05[i][j] << " " << RESET << " "; }
            else if(i == x && j == y && control == 4) { std::cout << GREEN_TEXT << "| " << HIGHLIGHT << BLACK_TEXT << WHITE_BACKGROUND << grid05[i][j] << " " RESET << " "; } 
            else { std::cout << GREEN_TEXT << "| " << RESET << grid05[i][j] << "  "; }
        }
        std::cout << GREEN_TEXT << "|  " << RED_TEXT << "|" << RED_TEXT << "  " << RESET;
        for(int j=0; j<MAX; j++) {
            if(status[6].second) { std::cout << GREEN_TEXT << "| " << HIGHLIGHT << BLACK_TEXT << YELLOW_BACKGROUND << grid06[i][j] << " " << RESET << " "; }
            else if(i == x && j == y && control == 5) { std::cout << GREEN_TEXT << "| " << HIGHLIGHT << BLACK_TEXT << WHITE_BACKGROUND << grid06[i][j] << " " RESET << " "; } 
            else { std::cout << GREEN_TEXT << "| " << RESET << grid06[i][j] << "  "; }
        }
        std::cout << GREEN_TEXT << "|" << RESET << std::endl;
        std::cout << GREEN_TEXT << "+----+----+----+  " << RED_TEXT << "|" << GREEN_TEXT << "  +----+----+----+  " <<RED_TEXT << "|" << GREEN_TEXT << "  +----+----+----+" << RESET << std::endl;
    }
    std::cout << RED_TEXT << "------------------+--------------------+------------------" << std::endl;
    std::cout << GREEN_TEXT << "+----+----+----+  " << RED_TEXT << "|" << GREEN_TEXT << "  +----+----+----+  " <<RED_TEXT << "|" << GREEN_TEXT << "  +----+----+----+" << RESET << std::endl;
    for(int i=0; i<MAX; i++) {
        for(int j=0; j<MAX; j++) {
            if(status[7].second) { std::cout << GREEN_TEXT << "| " << HIGHLIGHT << BLACK_TEXT << YELLOW_BACKGROUND << grid07[i][j] << " " << RESET << " "; }
            else if(i == x && j == y && control == 6) { std::cout << GREEN_TEXT << "| " << HIGHLIGHT << BLACK_TEXT << WHITE_BACKGROUND << grid07[i][j] << " " RESET << " "; } 
            else { std::cout << GREEN_TEXT << "| " << RESET << grid07[i][j] << "  "; }
        }
        std::cout << GREEN_TEXT << "|  " << RED_TEXT << "|" << RED_TEXT << "  " << RESET;
        for(int j=0; j<MAX; j++) {
            if(status[8].second) { std::cout << GREEN_TEXT << "| " << HIGHLIGHT << BLACK_TEXT << YELLOW_BACKGROUND << grid08[i][j] << " " << RESET << " "; }
            else if(i == x && j == y && control == 7) { std::cout << GREEN_TEXT << "| " << HIGHLIGHT << BLACK_TEXT << WHITE_BACKGROUND << grid08[i][j] << " " RESET << " "; } 
            else { std::cout << GREEN_TEXT << "| " << RESET << grid08[i][j] << "  "; }
        }
        std::cout << GREEN_TEXT << "|  " << RED_TEXT << "|" << RED_TEXT << "  " << RESET;
        for(int j=0; j<MAX; j++) {
            if(status[9].second) { std::cout << GREEN_TEXT << "| " << HIGHLIGHT << BLACK_TEXT << YELLOW_BACKGROUND << grid09[i][j] << " " << RESET << " "; }
            else if(i == x && j == y && control == 8) { std::cout << GREEN_TEXT << "| " << HIGHLIGHT << BLACK_TEXT << WHITE_BACKGROUND << grid09[i][j] << " " RESET << " "; } 
            else { std::cout << GREEN_TEXT << "| " << RESET << grid09[i][j] << "  "; }
        }
        std::cout << GREEN_TEXT << "|" << RESET << std::endl;
        std::cout << GREEN_TEXT << "+----+----+----+  " << RED_TEXT << "|" << GREEN_TEXT << "  +----+----+----+  " <<RED_TEXT << "|" << GREEN_TEXT << "  +----+----+----+" << RESET << std::endl;
    }
}
bool finalTie() {
    for(int i=1; i<=9; i++) {
        if(winGrids[i] == ' ') {
            return false; // more spaces remaining....
        }
    }
    std::cout << "It's a TIE !\n";
    return true;
}
bool finalWinner() {
    if ((winGrids[1] != ' ') && (winGrids[1] == winGrids[2]) && (winGrids[2] == winGrids[3])) {
        (winGrids[1] == 'X')? std::cout << "YOU WIN !\n" : std::cout << "YOU LOSE !\n";
    } else if ((winGrids[4] != ' ') && (winGrids[4] == winGrids[5]) && (winGrids[5] == winGrids[6])) {
        (winGrids[4] == 'X')? std::cout << "YOU WIN !\n" : std::cout << "YOU LOSE !\n";
    } else if ((winGrids[7] != ' ') && (winGrids[7] == winGrids[8]) && (winGrids[8] == winGrids[9])) {
        (winGrids[7] == 'X')? std::cout << "YOU WIN !\n" : std::cout << "YOU LOSE !\n";
    } else if ((winGrids[1] != ' ') && (winGrids[1] == winGrids[4]) && (winGrids[4] == winGrids[7])) {
        (winGrids[1] == 'X')? std::cout << "YOU WIN !\n" : std::cout << "YOU LOSE !\n";
    } else if ((winGrids[2] != ' ') && (winGrids[2] == winGrids[5]) && (winGrids[5] == winGrids[8])) {
        (winGrids[2] == 'X')? std::cout << "YOU WIN !\n" : std::cout << "YOU LOSE !\n";
    } else if ((winGrids[3] != ' ') && (winGrids[3] == winGrids[6]) && (winGrids[6] == winGrids[9])) {
        (winGrids[3] == 'X')? std::cout << "YOU WIN !\n" : std::cout << "YOU LOSE !\n";
    } else if ((winGrids[1] != ' ') && (winGrids[1] == winGrids[5]) && (winGrids[5] == winGrids[9])) {
        (winGrids[1] == 'X')? std::cout << "YOU WIN !\n" : std::cout << "YOU LOSE !\n";
    } else if ((winGrids[3] != ' ') && (winGrids[3] == winGrids[5]) && (winGrids[5] == winGrids[7])) {
        (winGrids[3] == 'X')? std::cout << "YOU WIN !\n" : std::cout << "YOU LOSE !\n";
    } else {
        return false;
    }
    return true;
    std::cout << std::endl;
    // system("pause");
}
bool checkWinner(char grid[MAX][MAX]) {
    if ((grid[0][0] != ' ') && (grid[0][0] == grid[0][1]) && (grid[0][1] == grid[0][2])) { } 
    else if ((grid[1][0] != ' ') && (grid[1][0] == grid[1][1]) && (grid[1][1] == grid[1][2])) { } 
    else if ((grid[2][0] != ' ') && (grid[2][0] == grid[2][1]) && (grid[2][1] == grid[2][2])) { } 
    else if ((grid[0][0] != ' ') && (grid[0][0] == grid[1][0]) && (grid[1][0] == grid[2][0])) { } 
    else if ((grid[0][1] != ' ') && (grid[0][1] == grid[1][1]) && (grid[1][1] == grid[2][1])) { } 
    else if ((grid[0][2] != ' ') && (grid[0][2] == grid[1][2]) && (grid[1][2] == grid[2][2])) { } 
    else if ((grid[0][0] != ' ') && (grid[0][0] == grid[1][1]) && (grid[1][1] == grid[2][2])) { } 
    else if ((grid[0][2] != ' ') && (grid[0][2] == grid[1][1]) && (grid[1][1] == grid[2][0])) { } 
    else { return false; }
    return true;
}
bool checkTie(char grid[MAX][MAX]) {
    for(int i=0; i<MAX; i++) {
        for(int j=0; j<MAX; j++) {
            if(grid[i][j] == ' ') {
                return false; // more spaces remaining....
            }
        }
    }
    std::cout << "It's a TIE !\n";
    return true;
}
int main() {

    for(int i=0; i<=9; i++) { 
        status.push_back(std::make_pair(std::make_pair(0, 0), false)); 
    }
    while(true) {
        playerMove('X');
        if(finalWinner()) { break; }
        else if(finalTie()) {
            break;
        }
        playerMove('O');
        if(finalWinner()) { break; }
        else if(finalTie()) {
            break;
        }
    }
    system("pause");
    // display();
    return 0;
}
