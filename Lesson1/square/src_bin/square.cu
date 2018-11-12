#include <iostream>
#include <cuda_runtime.h>
using namespace std;

__global__ void square(float * d_out,float * d_in)
{
	int idx=threadIdx.x;
	float f=d_in[idx];
	d_out[idx]=f*f;
}
extern "C" int func()
{
	const int array_size=64;
	const int array_bytes=array_size*sizeof(float);
	float h_in[array_size],h_out[array_size];
	for (int i=0;i<array_size;i++)
	{
		h_in[i]=float(i);	
	}
	
	float * d_in;
	float * d_out;
	cudaMalloc((void **)&d_in,array_bytes);
	cudaMalloc((void **)&d_out,array_bytes);
	
	cudaMemcpy(d_in,h_in,array_bytes,cudaMemcpyHostToDevice);
	square <<<1,array_size >>> (d_out,d_in);
	cudaMemcpy(h_out,d_out,array_bytes,cudaMemcpyDeviceToHost);
	
	for(int i=0;i<array_size;i++)
	{
		cout << h_out[i] << endl;
	}
	
	return 0;
}
