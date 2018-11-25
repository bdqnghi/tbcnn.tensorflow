

#include <iostream> 
#include <cstdlib> 
#include <ctime> 
#include "BucketSort.h" 
using namespace std;


BucketSort::BucketSort( int vectorSize )
{
   size = ( vectorSize > 0 ? vectorSize : 10 ); 
   srand( time( 0 ) ); 

   
   for ( int i = 0; i < size; i++ )
      data.push_back( 10 + rand() % 90 ); 

   
   for ( int i = 0; i < 10; i++ )
      bucket.push_back( vector < int >( size ) );
} 


void BucketSort::displayElements() const
{
   for ( int i = 0; i < size; i++ )
      cout << data[ i ] << " ";

   cout << endl; 
} 


void BucketSort::sort()
{
   int totalDigits;
   zeroBucket();

   totalDigits = numberOfDigits();

   
   
   for ( int i = 1; i <= totalDigits; i++ ) 
   {
      distributeElements( i );
      collectElements();

      if ( i != totalDigits )
         zeroBucket(); 
   } 
} 


void BucketSort::distributeElements( int digit )
{
   int divisor = 10;
   int bucketNumber;
   int elementNumber;

   for ( int i = 1; i < digit; ++i ) 
      divisor *= 10; 

   for ( int k = 0; k < size; ++k ) 
   {
      
      
      bucketNumber = ( data[ k ] % divisor - data[ k ] %
         ( divisor / 10 ) ) / ( divisor / 10 );

      
      
      elementNumber = ++bucket[ bucketNumber ][ 0 ];
      bucket[ bucketNumber ][ elementNumber ] = data[ k ];
   } 
} 


void BucketSort::collectElements()
{
   int subscript = 0;

   
   for ( int i = 0; i < 10; i++ )
   {
      for ( int j = 1; j <= bucket[ i ][ 0 ]; j++ )
         data[ subscript++ ] = bucket[ i ][ j ];
   } 
} 


int BucketSort::numberOfDigits()
{
   int largest = data[ 0 ];
   int digits = 0;

   
   for ( int i = 1; i < size; i++ )
   {
      if ( data[ i ] > largest )
         largest = data[ i ];
   } 

   
   while ( largest != 0 ) 
   {
      ++digits;
      largest /= 10;
   } 

   return digits;
} 


void BucketSort::zeroBucket()
{
   
   for ( int i = 0; i < 10; i++ )
   {
      for ( int j = 0; j < size; j++ )
         bucket[ i ][ j ] = 0;
   } 
} 



