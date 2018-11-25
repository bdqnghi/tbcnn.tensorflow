


#include "stdafx.h"

#include <iomanip>
#include <fstream>
#include <vector>
#include <stdlib.h>

#include "HeapSortCopyCounter.h"
#include "HeapSort.h"

const TCHAR g_szDataFileName[] = _T("datheap.txt");


template <class _Cont>
size_t LoadData(const TCHAR* szFileName, _Cont& vArray)
{
    size_t nReturn = 0;

    std::ifstream infile;
    
    infile.open(szFileName);

    if (infile.bad() || infile.fail())
    {
        tcout << _T("Error opening data file:") << szFileName << std::endl;
    }
    else
    {
        CHeapSortCopyCounter heapData;

        while (infile >> heapData)
        {
            vArray.push_back(heapData);
            nReturn ++;
        }

        infile.close();
    }

    return nReturn;
};


template<class _FwdIt>
void printMembers( _FwdIt _itBegin, _FwdIt _itEnd)
{
    tcout << _T("{ ");

    int iNewLineCtr = 0;
    for (_FwdIt it = _itBegin; it != _itEnd; ++it)
    {
        tcout << std::setw(4) << it->GetData() << ' ';

        iNewLineCtr++;
        if ((iNewLineCtr % 10) == 0)
            tcout << std::endl << _T("  ");
    }

    tcout << _T("}") << std::endl;
}



int _tmain(int argc, _TCHAR* argv[])
{
    std::vector<CHeapSortCopyCounter> vData;

    
    
    vData.reserve(100);

    
    if (LoadData(g_szDataFileName, vData))
    {
        
        int iInitialCopyCount = CHeapSortCopyCounter::GetCopyCounter ();

        
        
        tcout << _T ("Original array after loading input data") << std::endl;
        tcout << _T ("-----------------------------------------------------") << std::endl;

        printMembers (vData.begin (), vData.end ());
        tcout << std::endl;

        
        
        HeapSort (&vData[0], vData.size ());

        int iFinalCopyCount = CHeapSortCopyCounter::GetCopyCounter ();

        
        
        tcout << _T ("Final array after performing 'HeapSort'") << std::endl;
        tcout << _T ("-----------------------------------------------------") << std::endl;

        printMembers (vData.begin (), vData.end ());

        tcout << _T ("------------------------------------------------------") << std::endl;
        tcout << _T ("The heap-sort algorithm required a total of [")
              << iFinalCopyCount - iInitialCopyCount << _T ("]") << std::endl
              << _T (" data item copies to be made during its sorting of [")
              << vData.size () << _T ("]") << std::endl
              << _T (" data items") << std::endl;
    }

    return 0;
}

