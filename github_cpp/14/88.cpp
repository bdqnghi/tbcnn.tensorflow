typedef unsigned long long UI64;
typedef unsigned long long *PUI64;

PUI64 RadixSort(PUI64 pData, PUI64 pTemp, size_t count)
{
    size_t mIndex[8][256] = {0};            
    PUI64 pDst, pSrc, pTmp;
    size_t i,j,m,n;
    UI64 u;

    for(i = 0; i < count; i++){         
        u = pData[i];
        for(j = 0; j < 8; j++){
            mIndex[j][(size_t)(u & 0xff)]++;
            u >>= 8;
        }
    }
    for(j = 0; j < 8; j++){             
        n = 0;
        for(i = 0; i < 256; i++){
            m = mIndex[j][i];
            mIndex[j][i] = n;
            n += m;
        }
    }
    pDst = pTemp;                       
    pSrc = pData;
    for(j = 0; j < 8; j++){
        for(i = 0; i < count; i++){
            u = pSrc[i];
            m = (size_t)(u >> (j<<3)) & 0xff;
            pDst[mIndex[j][m]++] = u;
        }
        pTmp = pSrc;
        pSrc = pDst;
        pDst = pTmp;
    }
    return(pSrc);
}