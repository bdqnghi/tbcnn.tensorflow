// =========================================================================
//                       Copyright 2017 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#include "breath/metric/damerau_levenshtein_distance.hpp"
#include "breath/idiom/declare_non_copyable.hpp"
#include <algorithm>
#include <cstddef>

namespace breath {
namespace        {

class matrix
{
public:
    BREATH_DECLARE_NON_COPYABLE( matrix )

    typedef std::size_t T ;
                        matrix( std::size_t rows, std::size_t columns )
                            :   m_columns( columns ),
                                m_data( new T[ rows * columns ] )
                        {
                        }

    T *                operator[]( std::size_t i ) noexcept
    {
        return m_data + i * m_columns ;
    }

                        ~matrix() noexcept
                        {
                            delete[] m_data ;
                        }
private:
    std::size_t         m_columns ;
    T * const           m_data ;
} ;

}

//      I could not find any algorithm with a space complexity below
//      O( n^2 ). If you know of one, please drop me a mail.
// -------------------------------------------------------------------------
std::size_t
damerau_levenshtein_distance( std::string const & first,
                              std::string const & second )
{
    std::size_t const   height = 1 + first.length() ;
    std::size_t const   width  = 1 + second.length() ;

    matrix              m( height, width ) ;
    for ( std::size_t i = 0 ; i < height ; ++ i ) {
        m[ i ][ 0 ] = i ;
    }
    for ( std::size_t j = 0 ; j < width ; ++ j ) {
        m[ 0 ][ j ] = j ;
    }
    for ( std::size_t i = 1 ; i < height ; ++ i ) {
        for ( std::size_t j = 1 ; j < width ; ++ j ) {
            int const           cost = first[ i - 1 ] == second[ j - 1 ]
                                            ? 0
                                            : 1
                                            ;
            std::size_t const   insertion    = m[ i ][ j - 1 ] + 1 ;
            std::size_t const   deletion     = m[ i - 1 ][ j ] + 1 ;
            std::size_t const   substitution = m[ i - 1 ][ j - 1 ] + cost ;
            std::size_t         distance     = (std::min)( { insertion, deletion,
                                                           substitution } ) ;
            if ( i > 1 && j > 1  && first[ i - 1 ] == second[ j - 2 ] &&
                first[ i - 2 ] == second[ j - 1 ] ) {
                distance = (std::min)( distance, m[ i - 2 ][ j - 2 ] + cost ) ;
            }
            m[ i ][ j ] = distance ;
        }
    }
    return m[ height - 1 ][ width - 1 ] ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
