namespace util { /* Utility namespace */

    int getXCoordinates(int index) {
        return 4 * index + (2 + 4 * int(index / 3)) + 1;
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
}
