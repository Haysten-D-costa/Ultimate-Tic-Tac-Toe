# <p align="center">`THE ULTIMATE TIC-TAC-TOE GAME`</p>

This C++ program implements the `"Ultimate"` Tic-Tac-Toe game, a variation of the classic Tic-Tac-Toe on a larger grid. The game includes features such as switching between subgrids and displaying game statistics.

## DEMO : 

- ` NEW : ` UI is now updated !! with best text animations and a loading animation as well !
- ` NEW : ` Documentation displayed and rules of the game explained before you play....

![UltimateTTToe](/DemoImages/U2_2.png)

![UltimateTTToe](/DemoImages/U2_3.png)
![UltimateTTToe](/DemoImages/U2_4.png)

![UltimateTTToe](/DemoImages/01.png)

![UltimateTTToe](/DemoImages/02.png)

![UltimateTTToe](/DemoImages/03.png)

![UltimateTTToe](/DemoImages/04.png)

![UltimateTTToe](/DemoImages/05.png)

![UltimateTTToe](/DemoImages/06.png)

![UltimateTTToe](/DemoImages/07.png)

![UltimateTTToe](/DemoImages/08.png)


## DEPENDENCIES : 

- `util.h`: Header file containing utility functions.
- `textstyling.h`: Header file for text styling.
- `console_utils.h`: Header file for console utility functions.

## OVERVIEW : 

The Ultimate Tic-Tac-Toe game is an extended version of the classic Tic-Tac-Toe, played on a 9x9 grid of smaller Tic-Tac-Toe boards. Players take turns making moves within the smaller grids, and winning a smaller grid grants control of the corresponding larger grid. The goal is to win three smaller grids in a row, either horizontally, vertically, or diagonally.

## FEATURES : 

### 1. `Player Initialization`
- Players can enter their names at the beginning of the game.
- Player 1 is represented by 'X', and Player 2 is represented by 'O'.

### 2. `Game Display`
- The game provides a `dynamic and colorful console display`.
- The larger 9x9 grid is presented, along with statistics and player information.

### 3. `Moving and Placing`
- Players use `arrow keys` (Up, Down, Left, Right) to navigate within the grid.
- The `'Tab'` key allows switching between smaller grids.
- Pressing `'Enter'` places the player's symbol ('X' or 'O') in the selected cell.

### 4. `Switching Grids`
- Players are constrained to move in the smaller grid indicated by the last move of the opponent.
- If a player wins a smaller grid, they force the opponent to move in the corresponding larger grid.

### 5. `Winning Conditions`
- The game checks for wins in smaller grids after each move.
- If a player wins three smaller grids in a row, they are declared the overall winner.

### 6. `Draw Conditions`
- If all smaller grids are filled, and there is no winner, the game ends in a draw.

### 7. `Escape Key`
- Pressing the `'Esc'` key prompts the player to confirm whether they want to exit the game.

### 8. `Game Over Messages`
- Messages are displayed when the game ends, indicating the winner or a draw.

## HOW TO PLAY ??
1. Enter names for Player 1 and Player 2.
2. Use arrow keys to navigate and 'Enter' to make a move.
3. 'Tab' allows switching between smaller grids. (only initially, -i.e- before making a move)...
4. The game ends when a player wins, it's a draw, or the player chooses to exit.

## INSTALLATION : 

1. Go To the `Releases section`,<br>
CLICK https://github.com/Haysten-D-costa/Ultimate-Tic-Tac-Toe-Game-C-plus-plus/releases ....

2. Scroll Down to the `Assets section` and download the Files Required....

3. Download 
https://github.com/Haysten-D-costa/Ultimate-Tic-Tac-Toe-Game-C-plus-plus/releases/download/v1.0.0/UltimateTTToe.exe <br>
and run the `UltimateTTToe.exe` file....

4. `OR` Download https://github.com/Haysten-D-costa/Ultimate-Tic-Tac-Toe-Game-C-plus-plus/releases/download/v1.0.0/UltimateTTToe_Installer.zip <br>
`UltimateTTToe_Installer.zip` and extract and run the `UltimateTTToe.exe` file....


## COMPILATION : 

To enable static linking : 
```bash

//? TO COMPILE :
g++ -c console_utils.cpp -o console_utils.o
g++ -c UltimateTTToe.cpp -o UltimateTTToe.o
g++ -static-libgcc console_utils.o UltimateTTToe.o -o UltimateTTToe

//? TO RUN : 
UltimateTTToe