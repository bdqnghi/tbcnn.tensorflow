// C++ class for sorting integer list in OpenCL
// copyright Philippe Helluy, Université de Strasbourg, France, 2011, helluy@math.unistra.fr
// licensed under the GNU Lesser General Public License see http://www.gnu.org/copyleft/lesser.html
// if you find this software usefull you can cite the following work in your reports or articles:
// Philippe HELLUY, A portable implementation of the radix sort algorithm in OpenCL, HAL 2011.
// The algorithm is the radix sort algorithm
// Marcho Zagha and Guy E. Blelloch. “Radix Sort For Vector Multiprocessor.”
// in: Conference on High Performance Networking and Computing, pp. 712-721, 1991.
// each integer is made of _TOTALBITS bits. The radix is made of _BITS bits. The sort is made of
// several passes, each consisting in sorting against a group of bits corresponding to the radix.
// _TOTALBITS/_BITS passes are needed.
// The sorting parameters can be changed in "cl_radix_sortParam.hpp"
// compilation for Mac:
//g++ cl_radix_sort.cpp cl_radix_sortMain.cpp -framework opencl -Wall
// compilation for Linux:
//g++ cl_radix_sort.cpp cl_radix_sortMain.cpp -lOpenCL -Wall
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
//extern "C" {

void build_cl_radix_sort();

void init_cl_radix_sort(int nkeys);

// this function allows to change the size of the sorted vector
void cl_radix_resize(int nn);

// this function treats the array d_Keys on the GPU
// and return the sorting permutation in the array d_Permut
void cl_radix_sort();

// get the data from the GPU (for debugging)
void cl_radix_recup_gpu(void);

// put the data on the host in the GPU
void cl_radix_host2gpu();

// check that the sort is successfull (for debugging)
void cl_radix_check(void);

// sort a set of particles (for debugging)
void cl_radix_pic_sorting(void);

// transpose the list for faster memeory access
// (improve coalescence)
void cl_radix_transpose(int nbrow,int nbcol);


void cl_radix_display();

// compute the histograms for one pass
void cl_radix_histogram(uint pass);
// scan the histograms
void cl_radix_scan_histogram(void);
// scan the histograms
void cl_radix_reorder(uint pass);
//}


//cl_context Context;             // OpenCL context
//cl_device_id NumDevice;         // OpenCL Device

cl_device_id num_device;

cl_program program;                // OpenCL program
uint h_Histograms[_RADIX * _GROUPS * _ITEMS]; // histograms on the cpu
cl_mem d_Histograms;                   // histograms on the GPU


cl_command_queue command_que;
cl_context context;



// sum of the local histograms
uint h_globsum[_HISTOSPLIT];
cl_mem d_globsum;
cl_mem d_temp;  // in case where the sum is not needed

// list of keys
uint nkeys; // actual number of keys
uint nkeys_rounded; // next multiple of _ITEMS*_GROUPS
uint *h_checkKeys; // a copy for check
uint *h_keys;
cl_mem d_inKeys;
cl_mem d_outKeys;


// permutation
uint *h_Permut;
cl_mem d_inPermut;
cl_mem d_outPermut;

// OpenCL kernels
cl_kernel ckTranspose; // transpose the initial list
cl_kernel ckHistogram;  // compute histograms
cl_kernel ckScanHistogram; // scan local histogram
cl_kernel ckPasteHistogram; // paste local histograms
cl_kernel ckReorder; // final reordering

// timers
float histo_time,scan_time,reorder_time,sort_time,transpose_time;



float corput(int n,int k1,int k2);

#endif
