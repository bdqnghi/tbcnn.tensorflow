
#pragma once

#if !defined(__HEAP_SORT_COPY_COUNTER_H__)
#define __HEAP_SORT_COPY_COUNTER_H__

#ifndef _IOSTREAM_
    #include <iostream>
#endif


class CHeapSortCopyCounter
{
    int m_iData;                
    static int m_iCopyCounter;  

public:

    
    constexpr CHeapSortCopyCounter() noexcept
        : m_iData(0)
    { };

    
    constexpr CHeapSortCopyCounter(const CHeapSortCopyCounter& rhs) noexcept
        : m_iData(rhs.m_iData)
    { m_iCopyCounter++; };

    
    CHeapSortCopyCounter& operator= (const CHeapSortCopyCounter& rhs) noexcept
    {
        if (this != &rhs)
        {
            m_iData = rhs.m_iData;
            m_iCopyCounter++;
        }
        return *this;
    }

    
    
    
    constexpr bool operator == (const CHeapSortCopyCounter& rhs) const noexcept
    { return m_iData == rhs.m_iData; };

    constexpr bool operator > (const CHeapSortCopyCounter& rhs) const noexcept
    { return m_iData > rhs.m_iData; };

    constexpr bool operator < (const CHeapSortCopyCounter& rhs) const noexcept
    { return m_iData < rhs.m_iData; };

    
    constexpr int  GetData(void) const noexcept
    { return m_iData; };

    void SetData(int iSet) noexcept
    { m_iData = iSet; };

   static int GetCopyCounter(void) noexcept
   { return m_iCopyCounter; };

   
    friend std::ostream& operator <<(std::ostream& os, const CHeapSortCopyCounter& rhs);
    friend std::istream& operator >>(std::istream& is, CHeapSortCopyCounter& rhs);
};

_declspec(selectany) int CHeapSortCopyCounter::m_iCopyCounter = 0;



#endif