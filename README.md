# bilinearResize_cuda
requirements:  
  CUDA and OpenCV library(tested on CUDA 10.0 and OpenCV 4.1)  
  cmake 3.15  
  
usage:  
  $ cd bilinearResize_cuda/  
  $ mkdir build && cd build  
  $ cmake .. && make  
  $ ./example

input:  
  test.jpg 464*240*3  
output:  
  test_cpu.jpg 1856*960*3 (107.138715 ms)  
  test_gpu.jpg 1856*960*3 (1.887202 ms)  
  test_opencv.jpg 1856*960*3 (7.711177 ms)  
