#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


__global__ void saxpy(int n, float a, float *x, float *y,float *result)
{
     int t_id = threadIdx.x + blockDim.x * blockIdx.x;
     int stride = blockDim.x * gridDim.x;
     for (int i = t_id; i < n; i += stride)
     {
          result[i] = a * x[i] + y[i];
     }

    // int i = blockIdx.x * blockDim.x + threadIdx.x;
    // if (i < n)
    //     result[i] = a * x[i] + y[i];
}

int main(void)
{
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    cudaDeviceSynchronize();
    int N = 1670000000 / 4;
    //N:1 048 576

    float *x, *y,*result, *d_x, *d_y,*d_result;

    x = (float *)malloc(N * sizeof(float));
    y = (float *)malloc(N * sizeof(float));
    result = (float *)malloc(N * sizeof(float));

    cudaMalloc(&d_x, N * sizeof(float));
    cudaMalloc(&d_y, N * sizeof(float));
    cudaMalloc(&d_result, N * sizeof(float));

    for (int i = 0; i < N; i++)
    {
        x[i] = i;
        y[i] = i;
    }

    cudaMemcpy(d_x, x, N * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_y, y, N * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_result, result, N * sizeof(float), cudaMemcpyHostToDevice);
     printf("start\n");
    cudaEventRecord(start);

    // Perform SAXPY on 1M elements
    //saxpy<<<(N + 255) / 256, 256>>>(N, 2.0f, d_x, d_y,d_result);
    saxpy<<<65535, 1024>>>(N, 2.0f, d_x, d_y,d_result);
    //saxpy<<<100, 100>>>(N, 2.0f, d_x, d_y,d_result);
    // saxpy<<<(N + 255) / 256, 256>>>(N, 2.0f, d_x, d_y,d_result);
    //Single-Precision A·X Plus Y
    //z = ax + y
    cudaEventRecord(stop);
     printf("end\n");
    cudaMemcpy(result, d_result, N * sizeof(float), cudaMemcpyDeviceToHost);

    cudaEventSynchronize(stop);
    float milliseconds = 0;
    cudaEventElapsedTime(&milliseconds, start, stop);

    //That is CUDA C in a nutshell. 
    // As you can see, the SAXPY kernel contains the same computation as the sequential C version, 
    //but instead of looping over the N elements, we launch a single thread for each of the N elements, 
    //and each thread computes its array index using blockIdx.x*blockDim.x + threadIdx.x.

    printf("milliseconds: %f\n",milliseconds);
    printf("last: %f\n",result[N-1]);

    // float maxError = 0.0f,tmp;
    // for (int i = 0; i < N; i++)
    // {
    //     tmp = 2.0f * x[i] + y[i];
    //     // printf("%f\n",result[i]);
    //     // printf("%f\n",tmp);
    //     // printf("\n");
    //     maxError = max(maxError, abs(result[i] - tmp));
    // }
    // printf("Max error: %f\n", maxError);

    cudaFree(d_x);
    cudaFree(d_y);
    cudaFree(d_result);
    free(x);
    free(y);
    free(result);
}
// nvcc array_summation.cu -o run -ccbin "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Tools\MSVC\14.29.30133\bin\Hostx64\x64"