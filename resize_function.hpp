#include <stdio.h>
#include <iostream>
#include <math.h>
#include <cuda.h>
#define uchar unsigned char


//cpu resize
void resizeBilinear_cpu(uchar* src, uchar* out, int w, int h, int c, int w2, int h2);

//gpu resize
void reAllocPinned(unsigned int lengthSrc, unsigned int lengthResize, uchar* dataSource);

void freePinned();

uchar* resizeBilinear_gpu(int w, int h, int c, int w2, int h2);

void initGPU(int w, int h, int c, uchar dtype = sizeof(uchar));

void deinitGPU();
