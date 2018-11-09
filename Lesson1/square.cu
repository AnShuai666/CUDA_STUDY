#include <iostream>
using namespace std;

__global__ void square(float * d_out,float * d_in)
{
	int x=threadIdx.x;
	float f=d_in[x];
	d_out[x] =f*f;
}

int main()
{
	const int array_size=64;
	const int array_bytes=array_size*sizeof(float);
	float h_out[array_size],h_in[array_size];
	for(int i=0; i<array_size;i++)
	{
		h_in[i]=float(i);
	}
	
	float * d_out;
	float * d_in;
	cudaMalloc((void **)&d_in ,array_bytes);
	cudaMalloc((void **)&d_out ,array_bytes);
	
	cudaMemcpy(d_in,h_in,array_bytes,cudaMemcpyHostToDevice);
	square<<<1,array_size>>>(d_out,d_in);
	cudaMemcpy(h_out,d_out,array_bytes,cudaMemcpyDeviceToHost);
	
	for(int i=0;i<array_size;i++)
	{
		cout << h_out[i]<< endl;
	}
	return 0;
}
