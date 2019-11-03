#include "resize_cpu.hpp"

void resizeBilinear_cpu(uchar* src, uchar* out, int w, int h, int c, int w2, int h2){
    int numberPixel = w2*h2;
    float x_ratio = float(w)/w2;
    float y_ratio = float(h)/h2;
    for(int i=0; i<numberPixel; i++){
        int xx = i/w2;
        int yy = i%h2;

        float fx = (float(xx) + 0.5) * x_ratio - 0.5;
        float fy = (float(yy) + 0.5) * y_ratio - 0.5;

        int ix = floor(fx);
        int iy = floor(fy);

        fy -= iy;
        iy = std::min(iy, w - 1);
        iy = std::max(0, iy);

        fx -= ix;
        if (ix < 0) {
            fx = 0, ix = 0;
        }
        if (ix > h - 1) {
            fx = 0, ix = h - 1;
        }

        short cbufx[2];
        cbufx[0] = (1.f - fx) * 2048;
        cbufx[1] = 2048 - cbufx[0];

        short cbufy[2];
        cbufy[0] = (1.f - fy) * 2048;
        cbufy[1] = 2048 - cbufy[0];
        
        int stepOut = w2*c;
        int stepSrc = w*c;

        for (int k = 0; k < c; ++k)
        {
            *(out+ yy*stepOut + 3*xx + k) = (*(src + iy*stepSrc + 3*ix + k) * cbufx[0] * cbufy[0] + 
                *(src + (iy+1)*stepSrc + 3*ix + k) * cbufx[0] * cbufy[1] + 
                *(src + iy*stepSrc + 3*(ix+1) + k) * cbufx[1] * cbufy[0] + 
                *(src + (iy+1)*stepSrc + 3*(ix+1) + k) * cbufx[1] * cbufy[1]) >> 22;
        }

    }
}

