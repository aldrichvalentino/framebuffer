#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "printChar.h"

int main()
{
    int x = 0, y = 0;
    int i;

    for(y = 500; y >= 0; ){
        //scanf("%d", &y);
        printChar('a',255,255,255,150,y);
        y = y - 2;
    }

    // char character[50][50];
    // for(x = 0; x < 50; x++){
    //     for(y = 0; y < 50; y++){
    //         if(x == 0 || x == 45 || y == 0 || y == 45)
    //             character[x][y] = '*';
    //     }
    // }

    // for(x = 0; x < 20; x++){
    //     for(y = 0; y < 20; y++){
    //        printf("%c", character[x][y]);
    //     }
    //     printf("\n");
    // }


    // maks y 763
    // char 50 x 50

    return 0;
}
