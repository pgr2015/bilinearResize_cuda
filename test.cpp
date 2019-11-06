#include <opencv2/opencv.hpp>
#include <math.h>
#include <stdio.h>
#include <chrono>

#include "resize_function.hpp"

#define RESIZE_CALL_NUM 1000

int main(){

    char testFile[] = "../test.jpg";
    cv::Mat matSrc, matDst_cpu, matDst_gpu, matDst2;  

    matSrc = cv::imread(testFile, 2 | 4);  
    if(matSrc.empty()){
        printf("can't read image %s", testFile);
        exit(1);
    }
    matDst_cpu = cv::Mat(cv::Size(1856, 960), matSrc.type(), cv::Scalar::all(0));  
    matDst_gpu = cv::Mat(cv::Size(1856, 960), matSrc.type(), cv::Scalar::all(0));  
    matDst2 = cv::Mat(matDst_cpu.size(), matSrc.type(), cv::Scalar::all(0));  

    double scale_x = (double)matSrc.cols / matDst_cpu.cols;  
    double scale_y = (double)matSrc.rows / matDst_cpu.rows;  

    uchar* dataDst = matDst_cpu.data;
    int stepDst = matDst_cpu.step;
    uchar* dataSrc = matSrc.data;
    int stepSrc = matSrc.step;
    int iWidthSrc = matSrc.cols;
    int iHiehgtSrc = matSrc.rows;
    clock_t cpu_startTime, cpu_endTime;
    double cpu_ElapseTime = 0;
    cpu_startTime = clock();

    // cpu version
    printf("bilinear upsampling cpu version starts:\n");
    for(int i=0; i<RESIZE_CALL_NUM; i++){
        resizeBilinear_cpu(dataSrc, dataDst, matSrc.cols, matSrc.rows, matSrc.channels(), matDst_cpu.cols, matDst_cpu.rows);
    }
    cpu_endTime = clock();
    cpu_ElapseTime = ((double)(cpu_endTime - cpu_startTime) / (double)CLOCKS_PER_SEC);
    printf("Time CPU: %f ms\n", cpu_ElapseTime);
    cv::imwrite("test_cpu.jpg", matDst_cpu);

    // gpu version
    printf("bilinear upsampling gpu version starts:\n");
    uchar* dataGpu = NULL;
    unsigned int lengthSrc= matSrc.cols* matSrc.rows* matSrc.channels() * sizeof(uchar);
    unsigned int lengthResize= matDst_gpu.cols* matDst_gpu.rows* matDst_gpu.channels() * sizeof(uchar);
    reAllocPinned(lengthSrc, lengthResize, dataSrc); //allocate pinned host memory for fast cuda memcpy 

    initGPU(matDst_gpu.cols, matDst_gpu.rows, matDst_gpu.channels());
    dataGpu = resizeBilinear_gpu(matSrc.cols, matSrc.rows, matSrc.channels(), matDst2.cols, matDst2.rows); //init device
    cpu_startTime = clock();
    for (int i = 0; i < RESIZE_CALL_NUM; i++){
        dataGpu = resizeBilinear_gpu(matSrc.cols, matSrc.rows, matSrc.channels(), matDst2.cols, matDst2.rows);
    }
    cpu_endTime = clock();
    cpu_ElapseTime = ((double)(cpu_endTime - cpu_startTime) / (double)CLOCKS_PER_SEC);
    printf("Time GPU: %f ms\n", cpu_ElapseTime);
    memcpy(matDst_gpu.data, dataGpu,lengthResize);
    deinitGPU();
    freePinned();

    // opencv version
    printf("bilinear upsampling gpu version starts:\n");
    cpu_startTime = clock();
    for (int i = 0; i < RESIZE_CALL_NUM; i++){
        cv::resize(matSrc, matDst2, matDst_cpu.size(), 0, 0, 1);
    }
    cpu_endTime = clock();
    cpu_ElapseTime = ((double)(cpu_endTime - cpu_startTime) / (double)CLOCKS_PER_SEC);
    printf("Time OpenCV: %f ms\n", cpu_ElapseTime);

    cv::imwrite("test_gpu.jpg", matDst_gpu);
    cv::imwrite("test_opencv.jpg", matDst2);
}
