















#include "common.h"


profile_t timers[NUM_TIMERS];






int main(int argc, char* argv[]) {

    
    printf("\n##\n");
    srand(time(NULL));

    
    double peak = GPU_CLOCK * GPU_CORES * GPU_MOD;

    
    printf("## --- Configurations ---\n");
    for (int c=0; c<=3; c++) {
        #ifndef ENABLE_CUDA
            if (c == 0 || c == 2) { continue; }
        #endif
        switch(c) {
            case 0: printf("##    cuBLAS on '%s', peak: %.1lf GFLOPS\n", GPU_NAME, peak); break;
            case 1: printf("##    clBlas on '%s', peak: %.1lf GFLOPS\n", GPU_NAME, peak); break;
            case 2: printf("## myGEMM.cu on '%s', peak: %.1lf GFLOPS\n", GPU_NAME, peak); break;
            case 3: printf("## myGEMM.cl on '%s', peak: %.1lf GFLOPS\n", GPU_NAME, peak); break;
        }
    }

    
    for (int size=MINSIZE; size<=MAXSIZE; size=size*2) {

        
        for (int t=0; t<NUM_TIMERS; t++) {
            timers[t].t = 0.0;
            timers[t].kf = 0;
        }

        
        const int k = size;
        const int m = size;
        const int n = size;
        printf("##\n");
        printf("## --- %dx%dx%d ---\n", k, m, n);

        
        float* A = (float*)malloc(m*k*sizeof(float*));
        float* B = (float*)malloc(k*n*sizeof(float*));
        float* C = (float*)malloc(m*n*sizeof(float*));
        float* goldC = (float*)malloc(MAXSIZE*MAXSIZE*sizeof(float*));
        for (int i=0; i<m*k; i++) {
            A[i] = (float)rand() / (float)RAND_MAX;
        }
        for (int i=0; i<k*n; i++) {
            B[i] = (float)rand() / (float)RAND_MAX;
        }

        
        
        
        
	printf ("## Before running libclblas.\n");
        libclblas(A, B, goldC, k, m, n, NUM_TIMERS-1);
        

	printf ("Looping over configuration.\n");
        
        for (int c=0; c<=3; c++) {

            
            
                if (c == 0 || c == 2) { continue; }
            

            
            for (int i=0; i<m*n; i++) {
                C[i] = 0.0f;
            }

            
            char name[100];
            switch(c) {
                case 0: sprintf(name, "cuBLAS"); break;
                case 1: sprintf(name, "clBlas"); break;
                case 2: sprintf(name, "myGEMM.cu"); break;
                case 3: sprintf(name, "myGEMM.cl"); break;
            }

            
            switch(c) {
                
                
                
                case 1: libclblas(A, B, C, k, m, n, c); break;
                
                
                
                case 3: myclblas(A, B, C, k, m, n, c); break;
            }

            
            double L2norm = 0.0;
            for (int i=0; i<m*n; i++) {
                double val = C[i] - goldC[i];
                L2norm += val*val;
            }
            L2norm = sqrt(L2norm);

            
            double seconds = wtime(timers[c]);
            double performance = gflops(timers[c]);
            double fraction = 100.0 * performance / peak;
            printf("## [%9s] %6.3lf s --> %6.1lf GFLOPS (%2.0lf%%), L2 norm: %.2e\n",
                   name, seconds, performance, fraction, L2norm);
        }

        
        free(A);
        free(B);
        free(C);
        free(goldC);
    }

    
    printf("##\n");
    printf("\n");
    return 0;
}




double timer(void) {
    struct timeval Tvalue;
    struct timezone dummy;
    gettimeofday(&Tvalue, &dummy);
    double etime = (double)Tvalue.tv_sec + 1.0e-6*((double)Tvalue.tv_usec);
    return etime;
    
}


double wtime(profile_t timer) {
    return (timer.t);
}


double gflops(profile_t timer) {
    return ((double)timer.kf/(1000.0*1000.0)) / (timer.t);
}




char* readKernelFile(const char* filename, long* _size) {

    
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("-- Error opening file %s\n", filename);
        exit(1);
    }

    
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    
    char* source = (char *)malloc((size+1)*sizeof(char));
    fread(source, 1, size*sizeof(char), file);
    source[size] = '\0';
    fclose(file);

    
    *_size = (size+1);
    return source;
}


