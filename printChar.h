#ifndef PRINTCHAR_H
#define PRINTCHAR_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

void printChar(char Character, int Red, int Green, int Blue, int axis, int ordinat);

#endif
