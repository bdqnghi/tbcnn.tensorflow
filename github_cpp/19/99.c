









#include <CoreTestPch.h>

using namespace E;
using namespace std;


void SortPerformanceComparison(I32 minValue, I32 maxValue, U32 maxArraySize, U32 iterationCount);



bool Test::Algorithm::Run()
{
  try
  {
    E::Time::Timer t;
    Test::PrintResultTimeAndReset(RunFunctionalityTest(), t, "Test::Algorithm::RunFunctionalityTest");
    Test::PrintResultTimeAndReset(RunPerformanceTest(), t, "Test::Algorithm::RunPerformanceTest");

    return true;
  }
  catch(const Exception& e)
  {
    Test::PrintException(e);
  }

  return false;
}

template <typename T>
void CheckSortedArray(const E::Containers::DynamicArray<T>& a, bool printValuesFlag = false)
{
  T val = E::Math::NumericLimits<T>::Min();
  for (U32 i = 0; i < a.GetSize(); ++i)
  {
    E_ASSERT(val <= a[i]);
    val = a[i];
    if (printValuesFlag)
      std::cout << a[i] << " ";
  }
  if (printValuesFlag)
    std::cout << std::endl;
}

#ifdef E_DEBUG
template <typename T>
void CompareSortedArray(const E::Containers::DynamicArray<T>& a, const std::vector<T>& b)
{
  E_ASSERT(a.GetSize() == b.size());
  for (U32 i = 0; i < a.GetSize(); ++i)
  {
    E_ASSERT(b[i] == a[i]);
  }
}
#else
template <typename T>
void CompareSortedArray(const E::Containers::DynamicArray<T>&, const std::vector<T>&) {}
#endif

bool Test::Algorithm::RunFunctionalityTest()
{
  std::cout << "[Test::Algorithm::RunFunctionalityTest]" << std::endl << std::endl;
  
    

  E::Containers::DynamicArray<I32> a(8), b(8);
  std::vector<I32> v(8);
  a[0] = v[0] = 5;
  a[1] = v[1] = 6;
  a[2] = v[2] = 1;
  a[3] = v[3] = 7;
  a[4] = v[4] = 5;
  a[5] = v[5] = 3;
  a[6] = v[6] = 6;
  a[7] = v[7] = 8;
  
  std::sort(v.begin(), v.end());

  b.Copy(a.GetPtr(), a.GetSize());
  E::Math::Sorting<I32>::HeapSort(&b[0], 4, 5);
  E::Math::Sorting<I32>::HeapSort(&b[0], 2, 4);
  E::Math::Sorting<I32>::HeapSort(&b[0], 0, 2);
  E::Math::Sorting<I32>::HeapSort(&b[0], 2, 4);
  E::Math::Sorting<I32>::HeapSort(&b[0], 1, 5);
  E::Math::Sorting<I32>::HeapSort(b.GetPtr(), b.GetSize());
  CompareSortedArray(b, v);

  b.Copy(a.GetPtr(), a.GetSize());
  E::Math::Sorting<I32>::QuickSort(b.GetPtr(), b.GetSize());
  CompareSortedArray(b, v);


  return true;
}

bool Test::Algorithm::RunPerformanceTest()
{
  std::cout << "[Test::Algorithm::RunPerformanceTest]" << std::endl << std::endl;

  U32 maxArraySize = 1 << 10;   
  U32 iterationCount = 1 << 15; 
  I32 minValue = 0; Math::NumericLimits<I32>::Min();
  I32 maxValue = Math::NumericLimits<I32>::Max();

  E::Math::Global::GetRandom().RandomizeSeed();

  SortPerformanceComparison(minValue, maxValue, maxArraySize, iterationCount);
  
  minValue = 0;
  maxValue = 100;
  
  SortPerformanceComparison(minValue, maxValue, maxArraySize, iterationCount);
 
  return true;
}

I32 compare_ints(const void* a, const void* b)   
{
  I32 arg1 = *reinterpret_cast<const I32*>(a);
  I32 arg2 = *reinterpret_cast<const I32*>(b);
  if(arg1 < arg2) return -1;
  if(arg1 > arg2) return 1;
  return 0;
}

void SortPerformanceComparison(I32 minValue, I32 maxValue, U32 maxArraySize, U32 iterationCount)
{
  
  std::cout << "Parameters: " << std::endl
            << "- Max array size      [" << maxArraySize << "]" << std::endl
            << "- Value range         [" << maxValue - minValue << "]" << std::endl
            << "- Max iteration count [" << iterationCount << "]"  << std::endl << std::endl;

  E::Time::Timer t;
  U32 weightedIterationCount = 0;
  F32 totalSortTimeStd = 0;
  F32 totalQuickSortTime = 0;
  F32 totalQuickSortDPTime = 0;
  F32 totalQuickSort3WTime = 0;
  F32 totalIntroSortTime = 0;

  for (U32 i = 2; i <= maxArraySize; i*=2)
  {
    F32 sortTimeStd = 0;
    F32 quickSortTime = 0;
    F32 quickSortDPTime = 0;
    F32 quickSort3WTime = 0;
    F32 introSortTime = 0;

    weightedIterationCount = iterationCount / i;
    for (U32 j = 0; j < weightedIterationCount; ++j)
    {
      E::Containers::DynamicArray<I32> intArray(i), intArray2(i), intArray3(i), intArray4(i);
      std::vector<I32> intArrayStd(i);
      for (U32 k = 0; k < i; ++k)
      {
        
        I32 value = Math::Global::GetRandom().GetI32(minValue, maxValue);
        intArrayStd[k] = intArray[k] = intArray2[k] = intArray3[k] = intArray4[k] = value;
      }

      t.Reset();
      std::sort(intArrayStd.begin(), intArrayStd.end());
      
      
      
      sortTimeStd += static_cast<F32>(t.GetElapsed().GetMilliseconds());
    
      t.Reset();
      Math::Sorting<I32>::QuickSort(intArray.GetPtr(), intArray.GetSize());
      quickSortTime += static_cast<F32>(t.GetElapsed().GetMilliseconds());
      CheckSortedArray(intArray);
      CompareSortedArray(intArray, intArrayStd);
      
      t.Reset();
      Math::Sorting<I32>::QuickSort3Way(intArray3.GetPtr(), intArray3.GetSize());
      quickSort3WTime += static_cast<F32>(t.GetElapsed().GetMilliseconds());
      CheckSortedArray(intArray3);
      CompareSortedArray(intArray3, intArrayStd);

      t.Reset();
      Math::Sorting<I32>::QuickSortDualPivot(intArray2.GetPtr(), intArray2.GetSize());
      quickSortDPTime += static_cast<F32>(t.GetElapsed().GetMilliseconds());
      CheckSortedArray(intArray2);
      CompareSortedArray(intArray2, intArrayStd);
 
      t.Reset();
      Math::Sorting<I32>::IntroSort(intArray4.GetPtr(), intArray4.GetSize());
      introSortTime += static_cast<F32>(t.GetElapsed().GetMilliseconds());
      CheckSortedArray(intArray4);
      CompareSortedArray(intArray4, intArrayStd);
    }

    if (quickSortTime > sortTimeStd)
    {
      F32 percentage = (sortTimeStd / quickSortTime * 100.0f) - 100.0f;
      std::cout << "!QuickSort - array size " << i << " / " << weightedIterationCount << " iterations\t" << percentage << "% faster (+" << quickSortTime - sortTimeStd << " ms)" << std::endl;
    }
    if (quickSort3WTime > sortTimeStd)
    {
      F32 percentage = (sortTimeStd / quickSort3WTime * 100.0f) - 100.0f;
      std::cout << "!QS 3-Way  - array size " << i << " / " << weightedIterationCount << " iterations\t" << percentage << "% faster (+" << quickSort3WTime - sortTimeStd << " ms)" <<std::endl;
    }
    if (quickSortDPTime > sortTimeStd)
    {
      F32 percentage = (sortTimeStd / quickSortDPTime * 100.0f) - 100.0f;
      std::cout << "!QS DualP  - array size " << i << " / " << weightedIterationCount << " iterations\t" << percentage << "% faster (+" << quickSortDPTime - sortTimeStd << " ms)" <<std::endl;
    }
    if (introSortTime > sortTimeStd)
    {
      F32 percentage = (sortTimeStd / introSortTime * 100.0f) - 100.0f;
      std::cout << "!IntroSort - array size " << i << " / " << weightedIterationCount << " iterations\t" << percentage << "% faster (+" << introSortTime - sortTimeStd << " ms)" <<std::endl;
    }

    totalSortTimeStd += sortTimeStd;
    totalQuickSortTime += quickSortTime;
    totalQuickSortDPTime += quickSortDPTime;
    totalQuickSort3WTime += quickSort3WTime;
    totalIntroSortTime += introSortTime;
  }

  std::cout << std::endl << "Last weighted iterations count: " << weightedIterationCount << std::endl
            << "QuickSort time [" << totalQuickSortTime << " / " << totalSortTimeStd << " ms]\t" << (totalSortTimeStd / totalQuickSortTime * 100.0f) - 100.0f << "% faster" << std::endl
            << "QS 3-Way  time [" << totalQuickSort3WTime << " / " << totalSortTimeStd << " ms]\t" << (totalSortTimeStd / totalQuickSort3WTime * 100.0f) - 100.0f << "% faster" << std::endl
            << "QS DualP  time [" << totalQuickSortDPTime << " / " << totalSortTimeStd << " ms]\t" << (totalSortTimeStd / totalQuickSortDPTime * 100.0f) - 100.0f << "% faster" << std::endl
            << "IntroSort time [" << totalIntroSortTime << " / " << totalSortTimeStd << " ms]\t" << (totalSortTimeStd / totalIntroSortTime * 100.0f) - 100.0f << "% faster" << std::endl
            << std::endl;
  
  
}
