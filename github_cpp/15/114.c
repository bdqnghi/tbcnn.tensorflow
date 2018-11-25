





#ifndef ISPC_D____________________18S_MULTI_CORE_PROJECT1_MATRIXMULTIPLICATION_ISPC_MATRIXMULTIPLICATION_MATRIXMULTIPLICATION_MATRIXMULTIPLICATION_ISPC_SSE4_H
#define ISPC_D____________________18S_MULTI_CORE_PROJECT1_MATRIXMULTIPLICATION_ISPC_MATRIXMULTIPLICATION_MATRIXMULTIPLICATION_MATRIXMULTIPLICATION_ISPC_SSE4_H

#include <stdint.h>



#ifdef __cplusplus
namespace ispc { 
#endif 

#ifndef __ISPC_ALIGN__
#if defined(__clang__) || !defined(_MSC_VER)

#define __ISPC_ALIGN__(s) __attribute__((aligned(s)))
#define __ISPC_ALIGNED_STRUCT__(s) struct __ISPC_ALIGN__(s)
#else

#define __ISPC_ALIGN__(s) __declspec(align(s))
#define __ISPC_ALIGNED_STRUCT__(s) __ISPC_ALIGN__(s) struct
#endif
#endif





#if defined(__cplusplus) && (! defined(__ISPC_NO_EXTERN_C) || !__ISPC_NO_EXTERN_C )
extern "C" {
#endif 
    extern void multiply(int32_t a[][2000], int32_t b[][2000], int32_t r[][2000], int32_t n);
#if defined(__cplusplus) && (! defined(__ISPC_NO_EXTERN_C) || !__ISPC_NO_EXTERN_C )
} 
#endif 


#ifdef __cplusplus
} 
#endif 

#endif 
