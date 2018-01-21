#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "printChar.h"
#include "printName.h"

int main()
{
    int i, timer;
    char *Aldrich, *Aggi, *Mico, *Bobby, *Royyan, *Amuz, *Icha, *Fajar;
    int fbfd = 0;
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;
    long int screensize = 0;
    char *fbp = 0;
    int x = 0, y = 0;
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
    
    Aldrich = (char*) malloc(7);
    Aldrich[0] = 'a';
    Aldrich[1] = 'l';
    Aldrich[2] = 'd';
    Aldrich[3] = 'r';
    Aldrich[4] = 'i';
    Aldrich[5] = 'c';
    Aldrich[6] = 'h';

    Aggi = (char*) malloc(4);
    Aggi[0] = 'a';
    Aggi[1] = 'g';
    Aggi[2] = 'g';
    Aggi[3] = 'i';

    Mico = (char*) malloc(4);
    Mico[0] = 'm';
    Mico[1] = 'i';
    Mico[2] = 'c';
    Mico[3] = 'o';
    
    Bobby = (char*) malloc(5);
    Bobby[0] = 'b';
    Bobby[1] = 'o';
    Bobby[2] = 'b';
    Bobby[3] = 'b';
    Bobby[4] = 'y';

    Royyan = (char*) malloc(6);
    Royyan[0] = 'r';
    Royyan[1] = 'o';
    Royyan[2] = 'y';
    Royyan[3] = 'y';
    Royyan[4] = 'a';
    Royyan[5] = 'n';

    Amuz = (char*) malloc(4);
    Amuz[0] = 'a';
    Amuz[1] = 'm';
    Amuz[2] = 'u';
    Amuz[3] = 'z';

    Icha = (char*) malloc(4);
    Icha[0] = 'i';
    Icha[1] = 'c';
    Icha[2] = 'h';
    Icha[3] = 'a';

    Fajar = (char*) malloc(5);
    Fajar[0] = 'f';
    Fajar[1] = 'a';
    Fajar[2] = 'j';
    Fajar[3] = 'a';
    Fajar[4] = 'r';
    
    for(y = vinfo.yres - 10; y >= -720; y--){
        printName(Aldrich, 7, 198, 40, 40, y);
        printName(Royyan, 6, 255, 87, 34, y + 90);
        printName(Mico, 4, 255, 255, 0, y + 180);
        printName(Amuz, 4, 50, 203, 0, y + 270);
        printName(Aggi, 4, 41, 121, 255, y + 360);
        printName(Bobby, 5, 98, 0, 234, y + 450); 
        printName(Fajar, 5, 123, 31, 162, y + 540);
        printName(Icha, 4, 183, 110, 121, y + 630);
        //printChar('a', 255, 255, 255, 550, y);
        
        for(timer = 0; timer < 2500000; timer++);
        clearScreen();
    }

    // maks y 763
    // char 50 x 50
    free(Aldrich);
    free(Aggi);
    free(Mico);
    free(Bobby);
    free(Fajar);
    free(Amuz);
    free(Royyan);
    free(Icha);

    return 0;
}
