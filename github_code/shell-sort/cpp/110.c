#include <vector>
#include <functional>
#include <iostream>
#include <ostream>

template <typename Comparable>
void ShellSort( std::vector<Comparable>& a )
{
    for( int gap = a.size() / 2; gap > 0; gap /= 2)
    {
        for( int p = gap; p < a.size(); ++p )
        {
            Comparable temp = std::move( a[p] );

            int j;
            for( j = p; j >= gap && temp < a[j - gap]; j -= gap )
                a[j] = std::move( a[j - gap] );

            a[j] = std::move( temp );
        }
    }
}

template <typename RandomIterator, typename Comparator>
void ShellSort( const RandomIterator & begin, const RandomIterator & end, Comparator lessThan )
{
    if( begin == end )
        return;

    RandomIterator j;

    int gap = ( end - begin ) / 2;
    for( ; gap > 0; gap /= 2 )
    {
        for( RandomIterator p = begin + gap; p < end; ++p )
        {
            auto temp = std::move( *p );
            for( j = p; j - begin >= gap && lessThan( *j, *(j - gap) ); j -= gap )
                // std::swap(*j, *(j-1));
                *j = std::move( *(j - gap) );
            *j = std::move( temp );
        }
    }
}

template <typename RandomIterator>
void  ShellSort( const RandomIterator & begin, const RandomIterator & end)
{
    ShellSort( begin, end, std::less<decltype( *begin )>{ } );
}

template <typename T>
std::ostream& operator << ( std::ostream& out, const std::vector<T>& obj )
{
    typename std::vector<T>::const_iterator it;
    for( it = obj.begin(); it != obj.end(); ++it )
        out << *it << " ";

    return out;
}

int main()
{
    std::vector<char> a { 'l','a','q','e','o','q','v','i' };

    ShellSort( a.begin(), a.end() );
    // ShellSort( a );

    std::cout << a;
    return 0;
}
