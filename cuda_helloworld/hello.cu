#include <stdio.h>
#include <cuda_runtime.h>

__global__ void hello(void)
{
    printf("Hello World!\n");
}

extern "C" int func()
{
    hello <<<1,10>>>();
    cudaDeviceReset();
}

