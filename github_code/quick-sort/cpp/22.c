#ifndef quicksort_h
#define quicksort_h

// Print the number array
VOID PrintNumbers(UINT* pNumbers, UINT numbersCount);

// -----------------------------------------
// Structure to save off left/right sublists
// -----------------------------------------
struct SubLists
{
    UINT leftMin;
    UINT leftMax;
    UINT rightMin;
    UINT rightMax;
};

// ---------------
// Quicksort class
// ---------------
class Quicksort
{
public:
    // Object instantiation method
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
    
    // Main entry method to sort
    VOID Sort(UINT* pNumbers, UINT numbersCount) const;
    
protected:
    // Force the client to use the Create() method
    Quicksort() { };
    virtual ~Quicksort() { }
    
private:
    VOID Initialize() { }
    // Method to process one sublist (either left or right)
    VOID SortSubList(UINT* pNumbers, UINT leftIndex, UINT rightIndex) const;
    
    Quicksort(const Quicksort&) = delete; // Disable copy constructor
    Quicksort& operator=(const Quicksort&) = delete; // Disable assignment operator
};

#endif /* quicksort_h */
