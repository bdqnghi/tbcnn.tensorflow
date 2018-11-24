/* Biomedical Image Analysis Library */
/* See README file in the root instalation directory for more information. */

/* Date: 2012/Jun/27 */
/* Content: Test file. */
/* Description: Test with Matrix class. */

#include "Common.hpp"
#include "Matrix.hpp"

using namespace std;
using namespace Bial;

int main( int, char** ) {

  Common::Randomize( false );

  Matrix< double > m1( 10, 8 );
  Matrix< double > m2( 8, 5 );
  Matrix< double > m3( 5, 2 );
  for( size_t elm = 0; elm < m1.size( ); ++elm ) {
    m1[ elm ] = rand( ) / static_cast< float >( RAND_MAX ) * 10.0;
  }
  for( size_t elm = 0; elm < m2.size( ); ++elm ) {
    m2[ elm ] = rand( ) / static_cast< float >( RAND_MAX ) * 10.0;
  }
  for( size_t elm = 0; elm < m3.size( ); ++elm ) {
    m3[ elm ] = rand( ) / static_cast< float >( RAND_MAX ) * 10.0;
  }
  cout << "m1." << endl << m1 << endl;
  cout << "m2." << endl << m2 << endl;
  cout << "m3." << endl << m3 << endl;

  Matrix< double > m4 = m2 * m1;
  cout << "m4 = m2 * m1." << endl << m4 << endl;

  m4 = m3 * m2;
  cout << "m4 = m3 * m2." << endl << m4 << endl;

  return( 0 );
}
