

#ifndef _SortTools_ShellSortOfReal_OCWrappers_HeaderFile
#define _SortTools_ShellSortOfReal_OCWrappers_HeaderFile


#include <SortTools_ShellSortOfReal.hxx>
#include "../Converter.h"




namespace OCNaroWrappers
{

ref class OCTColStd_Array1OfReal;
ref class OCTCollection_CompareOfReal;



public ref class OCSortTools_ShellSortOfReal  {

protected:
  SortTools_ShellSortOfReal* nativeHandle;
  OCSortTools_ShellSortOfReal(OCDummy^) {};

public:
  property SortTools_ShellSortOfReal* Handle
  {
    SortTools_ShellSortOfReal* get()
    {
      return nativeHandle;
    }
  }



OCSortTools_ShellSortOfReal(SortTools_ShellSortOfReal* nativeHandle);




static   void Sort(OCNaroWrappers::OCTColStd_Array1OfReal^ TheArray, OCNaroWrappers::OCTCollection_CompareOfReal^ Comp) ;

~OCSortTools_ShellSortOfReal()
{
  delete nativeHandle;
}

};

}; 

#endif
