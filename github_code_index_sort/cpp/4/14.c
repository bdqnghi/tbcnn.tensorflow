/**
 * @file       HeapSortCopyCounter.h
 * @brief      Heap Sort Copy Counter class
 *
 * @author     Mark L. Short
 * @date       October 19, 2014
 */
#pragma once

#if !defined(__HEAP_SORT_COPY_COUNTER_H__)
#define __HEAP_SORT_COPY_COUNTER_H__

#ifndef _IOSTREAM_
    #include <iostream>
#endif

/**
    The CHeapSortCopyCounter class is used to keep a running total of every 
    instance of a data item copy through its implementation of 
    the copy constructor and assignment operator.
*/
class CHeapSortCopyCounter
{
    int m_iData;                ///< the actual data getting sorted by the 'heap-sort' algorithm
    static int m_iCopyCounter;  ///< using this to keep track of every call to each copy constructor or assignment operator

public:

    /// Default constructor
    constexpr CHeapSortCopyCounter() noexcept
        : m_iData(0)
    { };

    /// Copy constructor
    constexpr CHeapSortCopyCounter(const CHeapSortCopyCounter& rhs) noexcept
        : m_iData(rhs.m_iData)
    { m_iCopyCounter++; };

    /// Assignment operator
    CHeapSortCopyCounter& operator= (const CHeapSortCopyCounter& rhs) noexcept
    {
        if (this != &rhs)
        {
            m_iData = rhs.m_iData;
            m_iCopyCounter++;
        }
        return *this;
    }

    /// comparison operators
    // we need to define them in order for the 'heap-sort' mechanics
    // to properly work against this class as the data-type to be sorted.
    constexpr bool operator == (const CHeapSortCopyCounter& rhs) const noexcept
    { return m_iData == rhs.m_iData; };

    constexpr bool operator > (const CHeapSortCopyCounter& rhs) const noexcept
    { return m_iData > rhs.m_iData; };

    constexpr bool operator < (const CHeapSortCopyCounter& rhs) const noexcept
    { return m_iData < rhs.m_iData; };

    /// data accessors
    constexpr int  GetData(void) const noexcept
    { return m_iData; };

    void SetData(int iSet) noexcept
    { m_iData = iSet; };

   static int GetCopyCounter(void) noexcept
   { return m_iCopyCounter; };

   /// overloaded stream insertion / extraction methods
    friend std::ostream& operator <<(std::ostream& os, const CHeapSortCopyCounter& rhs);
    friend std::istream& operator >>(std::istream& is, CHeapSortCopyCounter& rhs);
};

_declspec(selectany) int CHeapSortCopyCounter::m_iCopyCounter = 0;



#endif