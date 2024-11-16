#include <omp.h>
#include <stdio.h>
#include<stdlib.h>
#include <time.h>
#include <sys/time.h>

long getMicrotime(){
	struct timeval currentTime;
	gettimeofday(&currentTime, NULL);
	return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}

int main(void)
{
       
int N = 1670000000 / 4;
    float *x, *y,*result, *d_x, *d_y,*d_result;

    x = (float *)malloc(N * sizeof(float));
    y = (float *)malloc(N * sizeof(float));
    result = (float *)malloc(N * sizeof(float));

    for (int i = 0; i < N; i++)
    {
        x[i] = i;
        y[i] = i;
    }
    printf("start\n");
    unsigned long int t1 =  getMicrotime();
    #pragma omp parallel for
    for (int i = 0; i < N; i++)
        result[i] = 2.0f * x[i] + y[i];

    /* Get the time taken by program to execute in seconds */
     
    unsigned long int t2 =  getMicrotime();
    float t =  ((t2-t1) % 1000000) +  ((float)(t2-t1) / 1000000);
     printf("end\n");
    printf("milliseconds: %f\n",t);
    printf("last: %f\n",result[N-1]);


    free(x);
    free(y);
    free(result);
}


//nvcc array_summation.c -o run -ccbin "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Tools\MSVC\14.29.30133\bin\Hostx64\x64"