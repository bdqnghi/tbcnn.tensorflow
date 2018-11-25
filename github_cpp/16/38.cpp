






#include "internal/iprt.h"
#include <iprt/sort.h>



RTDECL(void) RTSortApvShell(void **papvArray, size_t cElements, PFNRTSORTCMP pfnCmp, void *pvUser)
{
    
    if (cElements < 2)
        return;

    size_t cGap = (cElements + 1) / 2;
    while (cGap > 0)
    {
        size_t i;
        for (i = cGap; i < cElements; i++)
        {
            void   *pvTmp = papvArray[i];
            size_t  j     = i;
            while (   j >= cGap
                   && pfnCmp(papvArray[j - cGap], pvTmp, pvUser) > 0)
            {
                papvArray[j] = papvArray[j - cGap];
                j -= cGap;
            }
            papvArray[j] = pvTmp;
        }

        
        cGap /= 2;
    }
}

