















#include "cl_radix_sort_param.h"
#ifndef _cl_radix_sort
#define _cl_radix_sort




#if defined (__APPLE__) || defined(MACOSX)
#include <OpenCL/opencl.h>
#else
#include <CL/opencl.h>
#endif

typedef cl_uint uint;




#include<stdio.h>
#include<assert.h>
#include<math.h>
#include <stdlib.h>


void build_cl_radix_sort();

void init_cl_radix_sort(int nkeys);


void cl_radix_resize(int nn);



void cl_radix_sort();


void cl_radix_recup_gpu(void);


void cl_radix_host2gpu();


void cl_radix_check(void);


void cl_radix_pic_sorting(void);



void cl_radix_transpose(int nbrow,int nbcol);


void cl_radix_display();


void cl_radix_histogram(uint pass);

void cl_radix_scan_histogram(void);

void cl_radix_reorder(uint pass);






cl_device_id num_device;

cl_program program;                
uint h_Histograms[_RADIX * _GROUPS * _ITEMS]; 
cl_mem d_Histograms;                   


cl_command_queue command_que;
cl_context context;




uint h_globsum[_HISTOSPLIT];
cl_mem d_globsum;
cl_mem d_temp;  


uint nkeys; 
uint nkeys_rounded; 
uint *h_checkKeys; 
uint *h_keys;
cl_mem d_inKeys;
cl_mem d_outKeys;



uint *h_Permut;
cl_mem d_inPermut;
cl_mem d_outPermut;


cl_kernel ckTranspose; 
cl_kernel ckHistogram;  
cl_kernel ckScanHistogram; 
cl_kernel ckPasteHistogram; 
cl_kernel ckReorder; 


float histo_time,scan_time,reorder_time,sort_time,transpose_time;



float corput(int n,int k1,int k2);

#endif
