/*
To test that the Linux framebuffer is set up correctly, and that the device permissions
are correct, use the program below which opens the frame buffer and draws a gradient-
filled red square:
retrieved from:
Testing the Linux Framebuffer for Qtopia Core (qt4-x11-4.2.2)
http://cep.xor.aps.anl.gov/software/qt4-x11-4.2.2/qtopiacore-testingframebuffer.html
*/

#include "printChar.h"

void printChar(char Character, int Red, int Green, int Blue, int axis, int ordinat)
{
    int fbfd = 0;
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;
    long int screensize = 0;
    char *fbp = 0;
    int x = 0, y = 0, timer = 0;
    long int location = 0;
    FILE *file;
    const int buffer = 79; // 80 x 80
    char A[buffer][buffer]; 
    int maxY;

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

    // Open file according to character, a little brute force
    switch (Character) {
        case 'a':
            file = fopen("characters/a.txt", "r");
            break;
        case 'b':
            file = fopen("characters/b.txt", "r");
            break;
        case 'c':
            file = fopen("characters/c.txt", "r");
            break;
        case 'd':
            file = fopen("characters/d.txt", "r");
            break;
        case 'e':
            file = fopen("characters/e.txt", "r");
            break;
        case 'f':
            file = fopen("characters/f.txt", "r");
            break;
    }

    if(file){
        for(x = 0; x < buffer; x++){
            for(y = 0; y < buffer; y++){
                A[x][y] = getc(file);
            }
            getc(file); // delete enter
        }
    }

    fclose(file);

    // Figure out where in memory to put the pixel
    // Fade in if vinfo.yres - (buffer) < ordinat
    // Fade out if ordinat < 0; maks ordinat = -buffer
    // Asumsi: X selalu cukup pada layar, tidak keluar layar
    if((int)vinfo.yres - buffer < ordinat){
        maxY = vinfo.yres - ordinat - 10; // toleransi layar -10
    } else if(ordinat <= 0) {
        maxY = buffer + ordinat;
    } else {
        maxY = buffer;
    }

    //printf("this is maxY %d\n", maxY);
    if(ordinat <= 0){
        ordinat = 0;
    }
    //printf("this is ordinat %d\n", ordinat);

    for (y = ordinat; y < ordinat+maxY; y++) {
        for (x = axis; x < axis+buffer; x++) {

            location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (y+vinfo.yoffset) * finfo.line_length;

            if (A[y-ordinat][x-axis] != ' ' && A[y-ordinat][x-axis] != '\10') {
                *(fbp + location) = Blue;        // Some blue
                *(fbp + location + 1) = Green;     // A little green
                *(fbp + location + 2) = Red;    // A lot of red
                *(fbp + location + 3) = 0;      // No transparency
            } else  {     
                *(fbp + location) = 0;        // Some blue
                *(fbp + location + 1) = 0;     // A little green
                *(fbp + location + 2) = 0;    // A lot of red
                *(fbp + location + 3) = 0;      // No transparency
            }
        }
    }
	
    //delay
    // for(timer = 0; timer < 10000000; timer++);

    munmap(fbp, screensize);
    close(fbfd);
}

void clearScreen() {
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

    // Figure out the size of the screen in bytes
    screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;

    // Map the device to memory
    fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
    if (*fbp == -1) {
        perror("Error: failed to map framebuffer device to memory");
        exit(4);
    }

    for (y = 0; y < vinfo.yres - 5; y++) {
        for (x = 0; x < vinfo.xres - 10; x++) {
            location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (y+vinfo.yoffset) * finfo.line_length;

            *(fbp + location) = 0;        // Some blue
            *(fbp + location + 1) = 0;     // A little green
            *(fbp + location + 2) = 0;    // A lot of red
            *(fbp + location + 3) = 0;      // No transparency
        }
    }

    munmap(fbp, screensize);
    close(fbfd);
}
