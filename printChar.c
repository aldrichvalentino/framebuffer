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

    // Gets from external file
    FILE *file;
    int buffer = 171;
    char A[buffer][buffer]; 
    file = fopen("characters/test.txt", "r");
    if(file){
        for(x = 0; x < buffer; x++){
            for(y = 0; y < buffer; y++){
                A[x][y] = getc(file);
            }
            getc(file); // delete enter
        }
    }

    // for(x = 0; x < buffer; x++){
    //         for(y = 0; y < buffer; y++){
    //             printf("%c", A[x][y]);
    //         }
    //         printf("\n");
    //     }

    // Figure out where in memory to put the pixel
    for (y = ordinat; y < ordinat+buffer; y++)
        for (x = axis; x < axis+buffer; x++) {

            location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (y+vinfo.yoffset) * finfo.line_length;

                // vinfo.bits_per_pixel == 32 && 
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

                // int b = 0;
                // int g = 0;     // A little green
                // int r = 0;    // A lot of red
                // unsigned short int t = r<<11 | g << 5 | b;
                // *((unsigned short int*)(fbp + location)) = t;
                }

            
        }
	
    // //delay
    // for(timer = 0; timer < 10000000; timer++);

    // //clear the screen
    // for (y = ordinat; y < ordinat+buffer; y++)
    //     for (x = axis; x < axis+buffer; x++) {

    //         location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
    //                    (y+vinfo.yoffset) * finfo.line_length;
                       
    //         if (vinfo.bits_per_pixel == 32) {
    //             *(fbp + location) = 0;        //Blue
    //             *(fbp + location + 1) = 0;    //Green
    //             *(fbp + location + 2) = 0;    //Red
    //             *(fbp + location + 3) = 0;    //transparency
    //     //location += 4;
    //         } else  { //assume 16bpp
    //             int b = 0;
    //             int g = 0;   
    //             int r = 0;   
    //             unsigned short int t = r<<11 | g << 5 | b;
    //             *((unsigned short int*)(fbp + location)) = t;
    //         }

    //     }

    munmap(fbp, screensize);
    close(fbfd);
}
