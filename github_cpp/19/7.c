


























#ifndef TCT_QSORT_H
#define TCT_QSORT_H

typedef int ( *TC_PFX_QSortCompare_t )( const void*, const void* );








template< class T > void TCT_QSort( T* padata, size_t len, 
                                    TC_PFX_QSortCompare_t pfxCompare );
template< class T > void TCT_QSort( T* padata, long len, 
                                    TC_PFX_QSortCompare_t pfxCompare );

template< class T > void TCT_QSortRecurse( T* padata, 
                                           long i, long j,
                                           TC_PFX_QSortCompare_t pfxCompare );
template< class T > long TCT_QSortPartition( T* padata, 
                                             long i, long j,
                                             TC_PFX_QSortCompare_t pfxCompare );

template< class T > int  TCT_QSortCompare( const T& dataA, 
                                           const T& dataB,
                                           TC_PFX_QSortCompare_t pfxCompare );











template< class T > void TCT_QSort( 
      T*     padata, 
      size_t len,
      TC_PFX_QSortCompare_t pfxCompare )
{
   TCT_QSort( padata, static_cast< long >( len ), pfxCompare );
}


template< class T > void TCT_QSort( 
      T*   padata, 
      long len,
      TC_PFX_QSortCompare_t pfxCompare )
{
   TCT_QSortRecurse( padata, 0, len - 1, pfxCompare );
}











template< class T > void TCT_QSortRecurse( 
      T*   padata, 
      long i, 
      long j,
      TC_PFX_QSortCompare_t pfxCompare )
{
   
   long pivot = TCT_QSortPartition( padata, i, j, pfxCompare );

   
   if( i < pivot )
   {
      TCT_QSortRecurse( padata, i, pivot - 1, pfxCompare );
   }

   
   if( j > pivot )
   {
      TCT_QSortRecurse( padata, pivot + 1, j, pfxCompare );
   }
}











template< class T > long TCT_QSortPartition( 
      T*   padata, 
      long i, 
      long j,
      TC_PFX_QSortCompare_t pfxCompare )
{
   
   T data = *( padata + i );

   
   if( j - i > 2 )
   {
      long r = TCT_Rand( i, j );

      *( padata + i ) = *( padata + r );
      *( padata + r ) = data;
      data = *( padata + i );
   }

   while( i < j )
   {
      
      while(( i < j ) && 
            ( TCT_QSortCompare( padata + j, &data, pfxCompare ) > 0 ))
      {
         --j;
      }

      if( i != j )
      {
         
         *( padata + i ) = *( padata + j );
         ++i;
      }

      
      while(( i < j ) && 
            ( TCT_QSortCompare( padata + i, &data, pfxCompare ) < 0 ))
      {
         ++i;
      }

      if( i != j )
      {
         
         *( padata + j ) = *( padata + i );
         --j;
      }
   }

   
   *( padata + i ) = data;

   return( i );
}













template< class T > int TCT_QSortCompare( 
      const T& dataA, 
      const T& dataB,
      TC_PFX_QSortCompare_t pfxCompare )
{
   const void* pvoidA = static_cast< const void* >( dataA->GetCompare( ));
   const void* pvoidB = static_cast< const void* >( dataB->GetCompare( ));

   return(( *pfxCompare )( pvoidA, pvoidB ));
}

#endif
