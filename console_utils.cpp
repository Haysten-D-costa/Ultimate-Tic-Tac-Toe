#include "console_utils.h"
#include <cstdlib>

void clearConsole() {
    system(CLEAR_SCREEN);
}

void pauseConsole() {
    system(PAUSE_COMMAND);
}