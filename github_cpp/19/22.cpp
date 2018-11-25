#ifndef quicksort_h
#define quicksort_h


VOID PrintNumbers(UINT* pNumbers, UINT numbersCount);




struct SubLists
{
    UINT leftMin;
    UINT leftMax;
    UINT rightMin;
    UINT rightMax;
};




class Quicksort
{
public:
    
    static Quicksort* Create()
    {
        Quicksort* pQuicksort = NEW Quicksort;
        pQuicksort->Initialize();
        
        return pQuicksort;
    }
    
    VOID Destroy()
    {
        DELETE this;
    }
    
    
    VOID Sort(UINT* pNumbers, UINT numbersCount) const;
    
protected:
    
    Quicksort() { };
    virtual ~Quicksort() { }
    
private:
    VOID Initialize() { }
    
    VOID SortSubList(UINT* pNumbers, UINT leftIndex, UINT rightIndex) const;
    
    Quicksort(const Quicksort&) = delete; 
    Quicksort& operator=(const Quicksort&) = delete; 
};

#endif 
