
#include <Base/Util/RadixSort.h>

#include <Base/IO/TextStream.h>
#include <Base/Util/Bits.h>
#include <Base/Util/CPU.h>


USING_NAMESPACE


UNNAMESPACE_BEGIN

template< typename T >
inline void swap( T& a, T& b )
{
   T tmp = a;
   a = b;
   b = tmp;
}

UNNAMESPACE_END





RadixSort::RadixSort():
   _sortedIndices( NULL )
{
}



RadixSort::~RadixSort()
{
}



void
RadixSort::initializeIndices( const uint nValues, uint* indices )
{
   for( uint i = 0; i < nValues; ++i )
   {
      indices[i] = i;
   }
}



RadixSort&
RadixSort::sort( const uint nValues, const uint* inputValues )
{
   guaranteeIndices( nValues, 0 );
   return sort( nValues, inputValues, _indices[0]->data() );
}



RadixSort&
RadixSort::sort( const uint nValues, const uint* inputValues, uint* sortedIndices )
{
   guaranteeIndices( nValues, 1 );
   return sort( nValues, inputValues, sortedIndices, _indices[1]->data() );
}



RadixSort&
RadixSort::sort( const uint nValues, const uint* inputValues, uint* sortedIndices, uint* tempIndices )
{
   createHistograms( nValues, inputValues );
   return commonSort( nValues, inputValues, true, sortedIndices, tempIndices );
}



RadixSort&
RadixSort::sort( const uint nValues, const float* inputValues )
{
   guaranteeIndices( nValues, 0 );
   return sort( nValues, inputValues, _indices[0]->data() );
}



RadixSort&
RadixSort::sort( const uint nValues, const float* inputValues, uint* sortedIndices )
{
   guaranteeIndices( nValues, 1 );
   return sort( nValues, inputValues, sortedIndices, _indices[1]->data() );
}



RadixSort&
RadixSort::sort( const uint nValues, const float* inputValues, uint* sortedIndices, uint* tempIndices )
{
   createHistograms( nValues, inputValues );
   return commonSort( nValues, (const uint*)inputValues, false, sortedIndices, tempIndices );
}



void
RadixSort::createHistograms( const uint nValues, const void* inputValues )
{
   
   memset( _histograms, 0, sizeof(_histograms) );
   uint* h0 = _histograms[0];
   uint* h1 = _histograms[1];
   uint* h2 = _histograms[2];
   uint* h3 = _histograms[3];
   const uchar* cur = (const uchar*)inputValues;
   const uchar* end = cur + 4*nValues;
   while( cur != end )
   {
      
      ++h0[*cur++]; ++h1[*cur++]; ++h2[*cur++]; ++h3[*cur++];
   }
}



void
RadixSort::guaranteeIndices( const uint nValues, const uint id )
{
   if( _indices[id].isNull() )
   {
      _indices[id] = new RCVector<uint>( nValues );
      if( id == 0 )
      {
         
         initializeIndices( nValues, _indices[id]->data() );
      }
   }
   else
   if( _indices[id]->size() != nValues )
   {
      _indices[id]->resize( nValues );
      if( id == 0 )
      {
         
         initializeIndices( nValues, _indices[id]->data() );
      }
   }
   
}



RadixSort&
RadixSort::commonSort( const uint nValues, const uint* inputValues, const bool allUnsigned, uint* sortedIndices, uint* tempIndices )
{
   

   
#if CPU_ENDIANNESS == CPU_ENDIAN_BIG
   
   const uint byteOrder[] = { 3, 2, 1, 0 };
#else
   
   const uint byteOrder[] = { 0, 1, 2, 3 };
#endif

   
   uint*  radixPtr[256];

   for( uint b = 0; b < 4; ++b )
   {
      const uint* radixCounts = _histograms[byteOrder[b]];

      if( b != 3 || allUnsigned )
      {
         
         radixPtr[0] = tempIndices - 1; 
         for( uint i = 1; i < 256; ++i )
         {
            
            radixPtr[i] = radixPtr[i-1] + radixCounts[i-1];
         }

         
         const uchar* inputRadix = (const uchar*)inputValues;
         inputRadix += byteOrder[b]; 

         const uint* cur = sortedIndices;
         const uint* end = cur + nValues;
         while( cur != end )
         {
            
            const uint curIdx = *cur++;
            
            
            const uchar radix = inputRadix[curIdx<<2];
            
            *(++radixPtr[radix]) = curIdx;
         }
      }
      else
      {
         
         
         
         
         
         
         radixPtr[255] = tempIndices + radixCounts[255];
         for( uint i = 254; i >= 128; --i )
         {
            radixPtr[i] = radixPtr[i+1] + radixCounts[i];
         }
         
         radixPtr[0] = radixPtr[128] - 1;  
         for( uint i = 1; i < 128; ++i )
         {
            radixPtr[i] = radixPtr[i-1] + radixCounts[i-1];
         }

         
         const uchar* inputRadix = (const uchar*)inputValues;
         inputRadix += byteOrder[b]; 

         const uint* cur = sortedIndices;
         const uint* end = cur + nValues;
         if( (radixPtr[0]+1) != tempIndices )
         {
            
            while( cur != end )
            {
               
               const uint curIdx = *cur++;
               
               
               const uchar radix = inputRadix[curIdx<<2];
               
               switch( (radix >> 7) & 0x01 )
               {
                  case 0: 
                     *(++radixPtr[radix]) = curIdx;
                     break;
                  case 1: 
                     *(--radixPtr[radix]) = curIdx;
                     break;
               }
            }
         }
         else
         {
            
            while( cur != end )
            {
               
               const uint curIdx = *cur++;
               
               
               const uchar radix = inputRadix[curIdx<<2];
               
               *(++radixPtr[radix]) = curIdx;
            }
         }
      }

      
      swap( tempIndices, sortedIndices );
   }

   _sortedIndices = sortedIndices;

   return *this;
}
