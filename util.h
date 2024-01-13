#ifndef UTIL_H
#define UTIL_H

    #include <iostream>
    #include <windows.h>
    #include "textstyling.h"
    namespace util { /* Utility namespace */

        int getXCoordinates(int index) {
            return 4 * index + (2 + 4 * int(index / 3)) + 4;
        }
        int getYCoordinates(int index) {
            return (2 * (index + 1) + (2 * int(index / 3))) + 2;
        }
        void gotoXY(int x, int y) {
            printf("%c[%d;%df", 0x1B, y, x);
        }
        void clearXY(int x, int y, int length) {
            gotoXY(x, y);
            for(int i=0; i<length; i++) {
                printf(" ");
            }
        }
        void loading() {/* FUNCTION TO DISPLAY LOADING PROCESS IN ANY PAGE.... */
            char x = 219;
            std::cout << "Loading ";
            for(int i=0; i< 55; i++) 
            {
                std::cout << GREEN_TEXT << x;
                if(i < 10) { Sleep(150); }
                if(i>=10 && i<20) { Sleep(50); }
                if(i >= 10) { Sleep(25); }
            }
            system("cls");
            std::cout << RESET;
        }
    }

#endif // UTIL_H