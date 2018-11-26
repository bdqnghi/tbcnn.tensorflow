/*=============================================================================
   Copyright (c) 2012, Ludo Sapiens Inc. and contributors.
   See accompanying file LICENSE.txt for details.
=============================================================================*/
#include <Base/Util/RadixSort.h>

#include <Base/IO/TextStream.h>
#include <Base/Util/Bits.h>
#include <Base/Util/CPU.h>


USING_NAMESPACE

/*==============================================================================
  UNNAMED NAMESPACE
==============================================================================*/
UNNAMESPACE_BEGIN

template< typename T >
inline void swap( T& a, T& b )
{
   T tmp = a;
   a = b;
   b = tmp;
}

UNNAMESPACE_END

/*==============================================================================
  CLASS RadixSort
==============================================================================*/

//------------------------------------------------------------------------------
//!
RadixSort::RadixSort():
   _sortedIndices( NULL )
{
}

//------------------------------------------------------------------------------
//!
RadixSort::~RadixSort()
{
}

//------------------------------------------------------------------------------
//!
void
RadixSort::initializeIndices( const uint nValues, uint* indices )
{
   for( uint i = 0; i < nValues; ++i )
   {
      indices[i] = i;
   }
}

//------------------------------------------------------------------------------
//!
RadixSort&
RadixSort::sort( const uint nValues, const uint* inputValues )
{
   guaranteeIndices( nValues, 0 );
   return sort( nValues, inputValues, _indices[0]->data() );
}

//------------------------------------------------------------------------------
//!
RadixSort&
RadixSort::sort( const uint nValues, const uint* inputValues, uint* sortedIndices )
{
   guaranteeIndices( nValues, 1 );
   return sort( nValues, inputValues, sortedIndices, _indices[1]->data() );
}

//------------------------------------------------------------------------------
//!
RadixSort&
RadixSort::sort( const uint nValues, const uint* inputValues, uint* sortedIndices, uint* tempIndices )
{
   createHistograms( nValues, inputValues );
   return commonSort( nValues, inputValues, true, sortedIndices, tempIndices );
}

//------------------------------------------------------------------------------
//!
RadixSort&
RadixSort::sort( const uint nValues, const float* inputValues )
{
   guaranteeIndices( nValues, 0 );
   return sort( nValues, inputValues, _indices[0]->data() );
}

//------------------------------------------------------------------------------
//!
RadixSort&
RadixSort::sort( const uint nValues, const float* inputValues, uint* sortedIndices )
{
   guaranteeIndices( nValues, 1 );
   return sort( nValues, inputValues, sortedIndices, _indices[1]->data() );
}

//------------------------------------------------------------------------------
//!
RadixSort&
RadixSort::sort( const uint nValues, const float* inputValues, uint* sortedIndices, uint* tempIndices )
{
   createHistograms( nValues, inputValues );
   return commonSort( nValues, (const uint*)inputValues, false, sortedIndices, tempIndices );
}

//------------------------------------------------------------------------------
//!
void
RadixSort::createHistograms( const uint nValues, const void* inputValues )
{
   // Create histograms.
   memset( _histograms, 0, sizeof(_histograms) );
   uint* h0 = _histograms[0];
   uint* h1 = _histograms[1];
   uint* h2 = _histograms[2];
   uint* h3 = _histograms[3];
   const uchar* cur = (const uchar*)inputValues;
   const uchar* end = cur + 4*nValues;
   while( cur != end )
   {
      // Update histogram entries.
      ++h0[*cur++]; ++h1[*cur++]; ++h2[*cur++]; ++h3[*cur++];
   }
}

//------------------------------------------------------------------------------
//!
void
RadixSort::guaranteeIndices( const uint nValues, const uint id )
{
   if( _indices[id].isNull() )
   {
      _indices[id] = new RCVector<uint>( nValues );
      if( id == 0 )
      {
         // Only need to initialize if it is the first.
         initializeIndices( nValues, _indices[id]->data() );
      }
   }
   else
   if( _indices[id]->size() != nValues )
   {
      _indices[id]->resize( nValues );
      if( id == 0 )
      {
         // Only need to initialize if it is the first.
         initializeIndices( nValues, _indices[id]->data() );
      }
   }
   // else, assume the previous pass was fine, and keep _indicesA as source for the next pass.
}

//------------------------------------------------------------------------------
//!
RadixSort&
RadixSort::commonSort( const uint nValues, const uint* inputValues, const bool allUnsigned, uint* sortedIndices, uint* tempIndices )
{
   // Sort byte0 in tempIndices, then byte1 in sortedIndices, then byte2 in tempIndices, then byte3 in sortedIndices.

   // The histogram was sorted in increasing byte order, but *using a typecast*.  We need to unwind that on some platforms.
#if CPU_ENDIANNESS == CPU_ENDIAN_BIG
   // Big endian.
   const uint byteOrder[] = { 3, 2, 1, 0 };
#else
   // Little endian.
   const uint byteOrder[] = { 0, 1, 2, 3 };
#endif

   // Prepare a bunch of radix pointers, i.e. direct pointers to the the destination location.
   uint*  radixPtr[256];

   for( uint b = 0; b < 4; ++b )
   {
      const uint* radixCounts = _histograms[byteOrder[b]];

      if( b != 3 || allUnsigned )
      {
         // Unsigned values.
         radixPtr[0] = tempIndices - 1; // The -1 is to have a preincrement in the while loop below.
         for( uint i = 1; i < 256; ++i )
         {
            // Offset the read location of each consecutive chunk by the number of chunks in the previous radix value.
            radixPtr[i] = radixPtr[i-1] + radixCounts[i-1];
         }

         // Sort the current radix.
         const uchar* inputRadix = (const uchar*)inputValues;
         inputRadix += byteOrder[b]; // Need to offset according to endianness to get proper byte.

         const uint* cur = sortedIndices;
         const uint* end = cur + nValues;
         while( cur != end )
         {
            // Retrieve the index from the previously-sorted pass.
            const uint curIdx = *cur++;
            // Extract current radix.
            // Note: We multiply by 4 in order to convert a uint* index into a uchar* one (an offset was already added to inputRadix).
            const uchar radix = inputRadix[curIdx<<2];
            // Assign it at the proper index location, and increment the next location.
            *(++radixPtr[radix]) = curIdx;
         }
      }
      else
      {
         // Pierre Terdiman's trick for handling negative values.
         // In increasing bit patterns, the value are 0, 1, 2, ... +INF, -0, -1, -2, ... -INF (i.e. sign-magnitude)
         // so we order them accordingly.
         // For that, we need to place the pointers at the end of the radix chunk, and count back (when negative).
         // Note: This is cheaper than bit-fiddling every float (the Michael Herf approach).
         // This does not preserve the order of equal negative values (they are in reversed order).
         radixPtr[255] = tempIndices + radixCounts[255];
         for( uint i = 254; i >= 128; --i )
         {
            radixPtr[i] = radixPtr[i+1] + radixCounts[i];
         }
         // Wrap back to positive values.
         radixPtr[0] = radixPtr[128] - 1;  //To have preincrement below.
         for( uint i = 1; i < 128; ++i )
         {
            radixPtr[i] = radixPtr[i-1] + radixCounts[i-1];
         }

         // Sort the current radix (special case on negative values).
         const uchar* inputRadix = (const uchar*)inputValues;
         inputRadix += byteOrder[b]; // Need to offset according to endianness to get proper byte.

         const uint* cur = sortedIndices;
         const uint* end = cur + nValues;
         if( (radixPtr[0]+1) != tempIndices )
         {
            // Special loop to handle negative values through decrement.
            while( cur != end )
            {
               // Retrieve the index from the previously-sorted pass.
               const uint curIdx = *cur++;
               // Extract current radix.
               // Note: We multiply by 4 in order to convert a uint* index into a uchar* one (an offset was already added to inputRadix).
               const uchar radix = inputRadix[curIdx<<2];
               // Assign it at the proper index location, and increment the next location.
               switch( (radix >> 7) & 0x01 )
               {
                  case 0: // Positive.
                     *(++radixPtr[radix]) = curIdx;
                     break;
                  case 1: // Negative.
                     *(--radixPtr[radix]) = curIdx;
                     break;
               }
            }
         }
         else
         {
            // Same loop as the unsigned case.
            while( cur != end )
            {
               // Retrieve the index from the previously-sorted pass.
               const uint curIdx = *cur++;
               // Extract current radix.
               // Note: We multiply by 4 in order to convert a uint* index into a uchar* one (an offset was already added to inputRadix).
               const uchar radix = inputRadix[curIdx<<2];
               // Assign it at the proper index location, and increment the next location.
               *(++radixPtr[radix]) = curIdx;
            }
         }
      }

      // Prepare next loop.
      swap( tempIndices, sortedIndices );
   }

   _sortedIndices = sortedIndices;

   return *this;
}
