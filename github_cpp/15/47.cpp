#ifndef MATRIXMULTIPLICATION_H
#define MATRIXMULTIPLICATION_H

#include <algorithm>
#include "matrixleftmultiplieradaptor.h"

template <class> class Matrix;
template <class> struct matrix_traits;

template <class R, class T, class D, typename std::enable_if<matrix_traits<T>::is_matrix && matrix_traits<D>::is_matrix>::type* = nullptr>
R multiply(const T& lhs, const D& rhs);

template <class R, class T, class D, typename std::enable_if<matrix_traits<T>::is_matrix && !matrix_traits<D>::is_matrix>::type* = nullptr>
R multiply(const T& lhs, const D rhs);

template <class R, class T, class D, typename std::enable_if<!matrix_traits<T>::is_matrix && matrix_traits<D>::is_matrix>::type* = nullptr>
R multiply(const T lhs, const D& rhs);

template <class M, class N>
class MatrixMultiplication {
public:
    MatrixMultiplication(const M& lhs, const N& rhs):
        m_lhs(lhs),
        m_rhs(rhs)
    {}

    template <class R>
    operator R()
    {
        return multiply<R>(m_lhs, m_rhs);
    }

private:
    const M& m_lhs;
    const N& m_rhs;
};

template <class T, class D, typename std::enable_if<matrix_traits<T>::is_matrix || matrix_traits<D>::is_matrix>::type* = nullptr>
MatrixMultiplication<T, D> operator*(const T& lhs, const D& rhs)
{
    return MatrixMultiplication<T, D>(lhs, rhs);
}

template <class R, class T, class D, typename std::enable_if<matrix_traits<T>::is_matrix && matrix_traits<D>::is_matrix>::type*>
R multiply(const T& lhs, const D& rhs)
{
    typedef typename R::size_type size_type;
    typedef typename R::value_type value_type;

    assert(lhs.columns() == rhs.rows());
    R result(lhs.rows(), rhs.columns());

    MatrixLeftMultiplierAdaptor<T> lhsH(*static_cast<const T*>(&lhs));

    for (size_type i = size_type(); i < lhs.rows(); ++i)
    {
        for (size_type j = size_type(); j < rhs.columns(); ++j)
        {
            lhsH.beginRow(i);
            value_type sum = value_type();
            while (!lhsH.endRow())
            {
                sum += lhsH.value() * rhs[lhsH.column()][j];
                lhsH.nextColumn();
            }
            result[i][j] = sum;
        }
    }

    return result;
}

template <class R, class T, class D, typename std::enable_if<matrix_traits<T>::is_matrix && !matrix_traits<D>::is_matrix>::type*>
R multiply(const T& lhs, const D rhs)
{
    R result(lhs.rows(), lhs.columns());

    if(rhs == D())
    {
        return result;
    }

    typename T::const_iterator itL = lhs.begin();
    typename T::const_iterator endL = lhs.end();

    while(itL != endL)
    {
        result[itL.row()][itL.column()] = *itL * rhs;
        ++itL;
    }

    return result;
}

template <class R, class T, class D, typename std::enable_if<!matrix_traits<T>::is_matrix && matrix_traits<D>::is_matrix>::type*>
R multiply(const T lhs, const D& rhs)
{
    return rhs * lhs;
}

#endif
