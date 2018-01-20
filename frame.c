#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "printChar.h"
#include "printName.h"

int main()
{
    int i;
    char *Name;
    int fbfd = 0;
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;
    long int screensize = 0;
    char *fbp = 0;
    int x = 0, y = 0, timer = 0;
    long int location = 0;
    
    // Open the file for reading and writing
    fbfd = open("/dev/fb0", O_RDWR);
    if (fbfd == -1) {
        perror("Error: cannot open framebuffer device");
        exit(1);
    }
    //printf("The framebuffer device was opened successfully.\n");

    // Get fixed screen information
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo) == -1) {
        perror("Error reading fixed information");
        exit(2);
    }

    // Get variable screen information
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
        perror("Error reading variable information");
        exit(3);
    }

    //printf("%dx%d, %dbpp\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel);

    // Figure out the size of the screen in bytes
    screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;

    // Map the device to memory
    fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
    if (*fbp == -1) {
        perror("Error: failed to map framebuffer device to memory");
        exit(4);
    }
    
    
    Name = (char*) malloc(4);
    Name[0] = 'a';
    Name[1] = 'a';
    Name[2] = 'a';
    Name[3] = 'a';
    
    
    for(y = vinfo.yres - 10; y >= -75; y--){
        //printName(Name, 4, 016, 253, 150, y);
        printChar('a', 255, 255, 255, 550, y);
        clearScreen();
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
