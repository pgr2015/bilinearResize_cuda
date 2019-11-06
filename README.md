# bilinearResize_cuda
**requirements:**  
  CUDA and OpenCV library(tested on CUDA 10.0 and OpenCV 4.1)  
  cmake 3.15  
  
**usage:**  
  $ cd bilinearResize_cuda/  
  $ mkdir build && cd build  
  $ cmake .. && make  
  $ ./example

**input:**  
  test.jpg *resolution: 464&#215;240&#215;3*  
    
**output:**  
  test_cpu.jpg *resolution: 1856&#215;960&#215;3  run time: 107.138715 ms*  
  test_gpu.jpg *resolution: 1856&#215;960&#215;3  run time: 1.887202 ms*  
  test_opencv.jpg *resolution: 1856&#215;960&#215;3  run time: 7.711177 ms*  
