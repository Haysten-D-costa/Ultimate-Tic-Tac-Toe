#ifndef CONSOLE_UTILS_H
#define CONSOLE_UTILS_H

#ifdef _WIN32
    // Windows-specific clear screen and pause commands....
    #define CLEAR_SCREEN "cls"
    #define PAUSE_COMMAND "pause"
#else
    // Assume other operating systems use ANSI escape codes for clearing the screen....
    #define CLEAR_SCREEN "clear"
    #define PAUSE_COMMAND "read -p 'Press Enter to continue...' -n 1 -r"
#endif

// Function to clear + pause the console screen....
void clearConsole();
void pauseConsole();

#endif // CONSOLE_UTILS_H