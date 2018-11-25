















#include "common.h"


#include <clBLAS.h>


extern void checkError(cl_int error, int line);


void libclblas(float* A, float* B, float* C,
               int K, int M, int N,
               int timerID) {
    cl_int err;

    
    cl_platform_id platform = 0;
    cl_device_id device = 0;
    cl_device_id devices[MAX_NUM_DEVICES];
    cl_uint numDevices = 0;
    cl_context_properties props[3] = {CL_CONTEXT_PLATFORM, 0, 0};
    cl_context ctx = 0;
    cl_command_queue queue = 0;
    cl_event event = NULL;
    char deviceName[MAX_DEVICE_NAME];

    
    err = clGetPlatformIDs(1, &platform, NULL);
    checkError (err, 45);
    err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 0, NULL, &numDevices);
    checkError (err, 47);
    err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, numDevices, devices, NULL);
    checkError (err, 49);
    device = devices[CURRENT_DEVICE];
    props[1] = (cl_context_properties)platform;
    ctx = clCreateContext(props, 1, &device, NULL, NULL, &err);
    queue = clCreateCommandQueue(ctx, device, 0, &err);
    err = clGetDeviceInfo(device, CL_DEVICE_NAME, MAX_DEVICE_NAME, deviceName, NULL);
    

    
    err = clblasSetup();

    
    cl_mem bufA = clCreateBuffer(ctx, CL_MEM_READ_ONLY, M*K*sizeof(*A), NULL, &err);
    cl_mem bufB = clCreateBuffer(ctx, CL_MEM_READ_ONLY, K*N*sizeof(*B), NULL, &err);
    cl_mem bufC = clCreateBuffer(ctx, CL_MEM_READ_WRITE, M*N*sizeof(*C), NULL, &err);

    
    err = clEnqueueWriteBuffer(queue, bufA, CL_TRUE, 0, M*K*sizeof(*A), A, 0, NULL, NULL);
    err = clEnqueueWriteBuffer(queue, bufB, CL_TRUE, 0, K*N*sizeof(*B), B, 0, NULL, NULL);
    err = clEnqueueWriteBuffer(queue, bufC, CL_TRUE, 0, M*N*sizeof(*C), C, 0, NULL, NULL);

    
    err = clblasSgemm(clblasColumnMajor, clblasNoTrans, clblasNoTrans,
                      128, 128, 128, ALPHA,
                      bufA, 0, 128,
                      bufB, 0, 128, BETA,
                      bufC, 0, 128,
                      1, &queue, 0, NULL, &event);
    err = clWaitForEvents(1, &event);

    
    double startTime = timer();
    for (int r=0; r<NUM_RUNS; r++) {

        
        err = clblasSgemm(clblasColumnMajor, clblasNoTrans, clblasNoTrans,
                          M, N, K, ALPHA,
                          bufA, 0, M,
                          bufB, 0, K, BETA,
                          bufC, 0, M,
                          1, &queue, 0, NULL, &event);

        
        err = clWaitForEvents(1, &event);
    }

    
    timers[timerID].t += (timer() - startTime) / (double)NUM_RUNS;
    timers[timerID].kf += ((long)K * (long)M * (long)N * 2) / 1000;

    
    err = clEnqueueReadBuffer(queue, bufC, CL_TRUE, 0, M*N*sizeof(*C), C, 0, NULL, NULL);

    
    clReleaseMemObject(bufA);
    clReleaseMemObject(bufB);
    clReleaseMemObject(bufC);

    
    clReleaseCommandQueue(queue);
    clReleaseContext(ctx);
}



