#include <opencv2/opencv.hpp>
#include <math.h>
#include <iostream>

#include "resize_cpu.hpp"

int main(){

    cv::Mat matSrc, matDst1, matDst2;  

    matSrc = cv::imread("test.jpg", 2 | 4);  
    matDst1 = cv::Mat(cv::Size(800, 800), matSrc.type(), cv::Scalar::all(0));  
    matDst2 = cv::Mat(matDst1.size(), matSrc.type(), cv::Scalar::all(0));  

    double scale_x = (double)matSrc.cols / matDst1.cols;  
    double scale_y = (double)matSrc.rows / matDst1.rows;  

    uchar* dataDst = matDst1.data;
    int stepDst = matDst1.step;
    uchar* dataSrc = matSrc.data;
    int stepSrc = matSrc.step;
    int iWidthSrc = matSrc.cols;
    int iHiehgtSrc = matSrc.rows;
    std::cout<<"stepDst is "<<stepDst<<std::endl;
    std::cout<<"stepSrc is "<<stepSrc<<std::endl;
/*
    for (int j = 0; j < matDst1.rows; ++j)
    {
        float fy = (float)((j + 0.5) * scale_y - 0.5);
        int sy = cvFloor(fy);
        fy -= sy;
        sy = std::min(sy, iHiehgtSrc - 2);
        sy = std::max(0, sy);

        short cbufy[2];
        //cbufy[0] = cv::saturate_cast<short>((1.f - fy) * 2048);
        cbufy[0] = (1.f - fy) * 2048;
        cbufy[1] = 2048 - cbufy[0];

        for (int i = 0; i < matDst1.cols; ++i)
        {
            float fx = (float)((i + 0.5) * scale_x - 0.5);
            int sx = cvFloor(fx);
            fx -= sx;

            if (sx < 0) {
                fx = 0, sx = 0;
            }
            if (sx >= iWidthSrc - 1) {
                fx = 0, sx = iWidthSrc - 2;
            }

            short cbufx[2];
            cbufx[0] = (1.f - fx) * 2048;
            cbufx[1] = 2048 - cbufx[0];

            for (int k = 0; k < matSrc.channels(); ++k)
            {
                *(dataDst+ j*matDst1.cols*matDst1.channels() + 3*i + k) = (*(dataSrc + sy*stepSrc + 3*sx + k) * cbufx[0] * cbufy[0] + 
                    *(dataSrc + (sy+1)*stepSrc + 3*sx + k) * cbufx[0] * cbufy[1] + 
                    *(dataSrc + sy*stepSrc + 3*(sx+1) + k) * cbufx[1] * cbufy[0] + 
                    *(dataSrc + (sy+1)*stepSrc + 3*(sx+1) + k) * cbufx[1] * cbufy[1]) >> 22;
            }
        }
    }
    */
   /*
    int numberPixel = matDst1.rows*matDst1.cols;
    float x_ratio = float(matSrc.cols)/matDst1.cols;
    float y_ratio = float(matSrc.rows)/matDst1.rows;
    for(int i=0; i<numberPixel; i++){
        int xx = i/matDst1.cols;
        int yy = i%matDst1.rows;

        float fx = (float(xx) + 0.5) * x_ratio - 0.5;
        float fy = (float(yy) + 0.5) * y_ratio - 0.5;

        int ix = floor(fx);
        int iy = floor(fy);

        fy -= iy;
        iy = std::min(iy, iHiehgtSrc - 1);
        iy = std::max(0, iy);

        fx -= ix;
        if (ix < 0) {
            fx = 0, ix = 0;
        }
        if (ix > iWidthSrc - 1) {
            fx = 0, ix = iWidthSrc - 1;
        }

        short cbufx[2];
        cbufx[0] = (1.f - fx) * 2048;
        cbufx[1] = 2048 - cbufx[0];

        short cbufy[2];
        cbufy[0] = (1.f - fy) * 2048;
        cbufy[1] = 2048 - cbufy[0];

        for (int k = 0; k < matSrc.channels(); ++k)
        {
            *(dataDst+ yy*matDst1.cols*matDst1.channels() + 3*xx + k) = (*(dataSrc + iy*stepSrc + 3*ix + k) * cbufx[0] * cbufy[0] + 
                *(dataSrc + (iy+1)*stepSrc + 3*ix + k) * cbufx[0] * cbufy[1] + 
                *(dataSrc + iy*stepSrc + 3*(ix+1) + k) * cbufx[1] * cbufy[0] + 
                *(dataSrc + (iy+1)*stepSrc + 3*(ix+1) + k) * cbufx[1] * cbufy[1]) >> 22;
        }

    }
    */
    resizeBilinear_cpu(dataSrc, dataDst, matSrc.cols, matSrc.rows, matSrc.channels(), matDst1.cols, matDst1.rows);

    cv::imwrite("linear_1.jpg", matDst1);
    printf("everything is ok!");
    cv::resize(matSrc, matDst2, matDst1.size(), 0, 0, 1);
    cv::imwrite("linear_2.jpg", matDst2);
}