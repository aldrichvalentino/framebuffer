#include "printName.h"

void printName(char* Name, int Length, int Red, int Green, int Blue, int Y) {
    int i;

    // print the characters
    for(i = 0; i < Length; i++){
        printChar(Name[i], Red, Green, Blue, 173*(i), Y);
    }

    //delay
    for(i = 0; i < 2500000; i++);

    // clear screen
    for(i = 0; i < Length; i++){
        printChar(' ', 0, 0, 0, 173*(i), Y);
    }
}
