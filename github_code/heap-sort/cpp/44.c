/**
* @file       HeapSort_Main.cpp
* @brief      Main entry for Heap Sort Project
* @mainpage
* @author     Mark L. Short
* @date       October 19, 2014
*
* Purpose: Algorithm Analysis assignment -
*
*    Write a program to implement a heapsort. For convenience, you may assume that 
*    the input has no more than 100 numbers.  Print out the original input data, 
*    the array after build_heap has been accomplished, and then print out the array 
*    together with the value of heap_size after each 10 elements have been removed 
*    from the heap.  Print out the final array.  I will provide an input set next week. 
*    It will consist of a list of numbers.
*
* Overall Implementation:
*    While there are plenty of 'heap-sort' implementations available online, the attached
*    source code was developed based on the text's author's algorithm implementations as 
*    closely as possible.
*
*    Accordingly, the following methods were developed and performed the necessary
*    operations as outlined in "chapter 6 - Heapsort":
*
*       - MaxHeapify    : corresponds to MAX-HEAPIFY(A,i) (6.2) 
*       - BuildMaxHeap  : corresponds to BUILD-MAX_HEAP(A) (6.3)
*       - HeapSort      : corresponds to HEAPSORT(A) (6.4)
*
* Enhancement:
*    Additionally, the program also keeps a running total of all of the in-place data 
*    item copying involved through the 'heap-sort' algorithm implementation, for further 
*    analysis.
*
*    The amount of 'in-place' data item copying involved in the actual algorithm implementation
*    is an important factor in considering an algorithm's impact on scalability, multi-threaded 
*    performance, and system-level data cache awareness.
*/


#include "stdafx.h"

#include <iomanip>
#include <fstream>
#include <vector>
#include <stdlib.h>

#include "HeapSortCopyCounter.h"
#include "HeapSort.h"

const TCHAR g_szDataFileName[] = _T("datheap.txt");

/**
 *  @brief Loads input data from file and stores contents in an stl vector
 *
 *  @param [in]  szFileName   name of the data file to be loaded
 *  @param [out] vArray       a container of CHeapSortCopyCounter
 *
 *  @retval size_t            the number of elements read into the array
 */
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

/**
 *  @brief printMembers formats and prints the contents of
 *         a STL container conditioned on the 'GetData' function 
 *         implementation
 *
 *  @param [in] _itBegin        STL iterator to the begin item
 *  @param [in] _itEnd          STL iterator to the end item
 *
 */
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


///////////////////////////////////////////////////////////////////////////////
int _tmain(int argc, _TCHAR* argv[])
{
    std::vector<CHeapSortCopyCounter> vData;

    // have the vector pre-allocate enough storage for 100 elements
    // in order to minimize any reallocations needed as we add in items
    vData.reserve(100);

    // lets read in the program data from the text file
    if (LoadData(g_szDataFileName, vData))
    {
        // determine number of pre-search data copies that have been made
        int iInitialCopyCount = CHeapSortCopyCounter::GetCopyCounter ();

        // print content of original array
        ///////////////////////////////////////////////////////////////////////////
        tcout << _T ("Original array after loading input data") << std::endl;
        tcout << _T ("-----------------------------------------------------") << std::endl;

        printMembers (vData.begin (), vData.end ());
        tcout << std::endl;

        // perform the heap-sort
        ///////////////////////////////////////////////////////////////////////////
        HeapSort (&vData[0], vData.size ());

        int iFinalCopyCount = CHeapSortCopyCounter::GetCopyCounter ();

        // print content of final array
        ///////////////////////////////////////////////////////////////////////////
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

