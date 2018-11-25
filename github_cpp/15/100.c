#ifndef mdk_SparseMatrixOperator_SparseMatrix_h
#define mdk_SparseMatrixOperator_SparseMatrix_h

namespace mdk
{



struct mdkMatrixSize;

template<typename ElementType>
class mdkDenseMatrix;

template<typename ElementType>
class mdkSparseMatrix;

template<typename ElementType>
class mdkSparseShadowMatrix;

template<typename ElementType>
class mdkSparseGlueMatrixForLinearCombination;

template<typename ElementType>
class mdkSparseGlueMatrixForMultiplication;
















template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator+(const mdkSparseMatrix<ElementType>& MatrixA, const mdkSparseMatrix<ElementType>& MatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator-(const mdkSparseMatrix<ElementType>& MatrixA, const mdkSparseMatrix<ElementType>& MatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForMultiplication<ElementType> operator*(const mdkSparseMatrix<ElementType>& MatrixA, const mdkSparseMatrix<ElementType>& MatrixB);






template<typename ElementType>
inline mdkDenseMatrix<ElementType> operator+(const mdkSparseMatrix<ElementType>& MatrixA, const ElementType& ElementB);

template<typename ElementType>
inline mdkDenseMatrix<ElementType> operator-(const mdkSparseMatrix<ElementType>& MatrixA, const ElementType& ElementB);

template<typename ElementType>
inline mdkSparseGlueMatrixForMultiplication<ElementType> operator*(const mdkSparseMatrix<ElementType>& MatrixA, const ElementType& ElementB);

template<typename ElementType>
inline mdkSparseGlueMatrixForMultiplication<ElementType> operator/(const mdkSparseMatrix<ElementType>& MatrixA, const ElementType& ElementB);







template<typename ElementType>
inline mdkDenseMatrix<ElementType> operator+(const ElementType& ElementA, const mdkSparseMatrix<ElementType>& MatrixB);

template<typename ElementType>
inline mdkDenseMatrix<ElementType> operator-(const ElementType& ElementA, const mdkSparseMatrix<ElementType>& MatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForMultiplication<ElementType> operator*(const ElementType& ElementA, const mdkSparseMatrix<ElementType>& MatrixB);













template<typename ElementType>
inline mdkSparseMatrix<ElementType> operator+(const mdkSparseShadowMatrix<ElementType>& ShadowMatrixA, const mdkSparseMatrix<ElementType>& MatrixB);

template<typename ElementType>
inline mdkSparseMatrix<ElementType> operator-(const mdkSparseShadowMatrix<ElementType>& ShadowMatrixA, const mdkSparseMatrix<ElementType>& MatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForMultiplication<ElementType> operator*(const mdkSparseShadowMatrix<ElementType>& ShadowMatrixA, const mdkSparseMatrix<ElementType>& MatrixB);







template<typename ElementType>
inline mdkSparseMatrix<ElementType> operator+(const mdkSparseMatrix<ElementType>& MatrixA, const mdkSparseShadowMatrix<ElementType>& ShadowMatrixB);

template<typename ElementType>
inline mdkSparseMatrix<ElementType> operator-(const mdkSparseMatrix<ElementType>& MatrixA, const mdkSparseShadowMatrix<ElementType>& ShadowMatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForMultiplication<ElementType> operator*(const mdkSparseMatrix<ElementType>& MatrixA, const mdkSparseShadowMatrix<ElementType>& ShadowMatrixB);

template<typename ElementType>
inline mdkSparseMatrix<ElementType> operator/(const mdkSparseMatrix<ElementType>& MatrixA, const mdkSparseShadowMatrix<ElementType>& ShadowMatrixB);






template<typename ElementType>
inline mdkDenseMatrix<ElementType> operator+(const mdkSparseShadowMatrix<ElementType>& ShadowMatrixA, const ElementType& ElementB);

template<typename ElementType>
inline mdkDenseMatrix<ElementType> operator-(const mdkSparseShadowMatrix<ElementType>& ShadowMatrixA, const ElementType& ElementB);

template<typename ElementType>
inline mdkSparseMatrix<ElementType> operator*(const mdkSparseShadowMatrix<ElementType>& ShadowMatrixA, const ElementType& ElementB);

template<typename ElementType>
inline mdkSparseMatrix<ElementType> operator/(const mdkSparseShadowMatrix<ElementType>& ShadowMatrixA, const ElementType& ElementB);







template<typename ElementType>
inline mdkDenseMatrix<ElementType> operator+(const ElementType& ElementA, const mdkSparseShadowMatrix<ElementType>& ShadowMatrixB);

template<typename ElementType>
inline mdkDenseMatrix<ElementType> operator-(const ElementType& ElementA, const mdkSparseShadowMatrix<ElementType>& ShadowMatrixB);

template<typename ElementType>
inline mdkSparseMatrix<ElementType> operator*(const ElementType& ElementA, const mdkSparseShadowMatrix<ElementType>& ShadowMatrixB);







template<typename ElementType>
inline mdkSparseMatrix<ElementType> operator+(const mdkSparseShadowMatrix<ElementType>& ShadowMatrixA, const mdkSparseShadowMatrix<ElementType>& ShadowMatrixB);

template<typename ElementType>
inline mdkSparseMatrix<ElementType> operator-(const mdkSparseShadowMatrix<ElementType>& ShadowMatrixA, const mdkSparseShadowMatrix<ElementType>& ShadowMatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForMultiplication<ElementType> operator*(const mdkSparseShadowMatrix<ElementType>& ShadowMatrixA, const mdkSparseShadowMatrix<ElementType>& ShadowMatrixB);













template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator+(mdkSparseGlueMatrixForLinearCombination<ElementType> GlueMatrixA, const mdkSparseMatrix<ElementType>& MatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator-(mdkSparseGlueMatrixForLinearCombination<ElementType> GlueMatrixA, const mdkSparseMatrix<ElementType>& MatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForMultiplication<ElementType> operator*(const mdkSparseGlueMatrixForLinearCombination<ElementType>& GlueMatrixA, const mdkSparseMatrix<ElementType>& MatrixB);







template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator+(const mdkSparseMatrix<ElementType>& MatrixA, mdkSparseGlueMatrixForLinearCombination<ElementType> GlueMatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator-(const mdkSparseMatrix<ElementType>& MatrixA, mdkSparseGlueMatrixForLinearCombination<ElementType> GlueMatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForMultiplication<ElementType> operator*(const mdkSparseMatrix<ElementType>& MatrixA, const mdkSparseGlueMatrixForLinearCombination<ElementType>& GlueMatrixB);





template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator+(mdkSparseGlueMatrixForLinearCombination<ElementType> GlueMatrixA, const ElementType& ElementB);

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator-(mdkSparseGlueMatrixForLinearCombination<ElementType> GlueMatrixA, const ElementType& ElementB);

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator*(mdkSparseGlueMatrixForLinearCombination<ElementType> GlueMatrixA, const ElementType& ElementB);

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator/(mdkSparseGlueMatrixForLinearCombination<ElementType> GlueMatrixA, const ElementType& ElementB);






template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator+(const ElementType& ElementA, mdkSparseGlueMatrixForLinearCombination<ElementType> GlueMatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator-(const ElementType& ElementA, mdkSparseGlueMatrixForLinearCombination<ElementType> GlueMatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator*(const ElementType& ElementA, mdkSparseGlueMatrixForLinearCombination<ElementType> GlueMatrixB);







template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator+(mdkSparseGlueMatrixForLinearCombination<ElementType> GlueMatrixA, const mdkSparseShadowMatrix<ElementType>& ShadowMatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator-(mdkSparseGlueMatrixForLinearCombination<ElementType> GlueMatrixA, const mdkSparseShadowMatrix<ElementType>& ShadowMatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForMultiplication<ElementType> operator*(const mdkSparseGlueMatrixForLinearCombination<ElementType>& GlueMatrixA, const mdkSparseShadowMatrix<ElementType>& ShadowMatrixB);







template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator+(const mdkSparseShadowMatrix<ElementType>& ShadowMatrixA, mdkSparseGlueMatrixForLinearCombination<ElementType> GlueMatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator-(const mdkSparseShadowMatrix<ElementType>& ShadowMatrixA, mdkSparseGlueMatrixForLinearCombination<ElementType> GlueMatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForMultiplication<ElementType> operator*(const mdkSparseShadowMatrix<ElementType>& ShadowMatrixA, const mdkSparseGlueMatrixForLinearCombination<ElementType>& GlueMatrixB);







template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator+(mdkSparseGlueMatrixForLinearCombination<ElementType> GlueMatrixA, mdkSparseGlueMatrixForLinearCombination<ElementType> GlueMatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator-(mdkSparseGlueMatrixForLinearCombination<ElementType> GlueMatrixA, mdkSparseGlueMatrixForLinearCombination<ElementType> GlueMatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForMultiplication<ElementType> operator*(const mdkSparseGlueMatrixForLinearCombination<ElementType>& GlueMatrixA, const mdkSparseGlueMatrixForLinearCombination<ElementType>& GlueMatrixB);













template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator+(mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixA, const mdkSparseMatrix<ElementType>& MatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator-(mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixA, const mdkSparseMatrix<ElementType>& MatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForMultiplication<ElementType> operator*(mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixA, const mdkSparseMatrix<ElementType>& MatrixB);







template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator+(const mdkSparseMatrix<ElementType>& MatrixA, mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator-(const mdkSparseMatrix<ElementType>& MatrixA, mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForMultiplication<ElementType> operator*(const mdkSparseMatrix<ElementType>& MatrixA, mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixB);






template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator+(mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixA, const ElementType& ElementB);

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator-(mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixA, const ElementType& ElementB);

template<typename ElementType>
inline mdkSparseGlueMatrixForMultiplication<ElementType> operator*(mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixA, const ElementType& ElementB);

template<typename ElementType>
inline mdkSparseGlueMatrixForMultiplication<ElementType> operator/(mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixA, const ElementType& ElementB);







template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator+(const ElementType& ElementA, mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator-(const ElementType& ElementA, mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForMultiplication<ElementType> operator*(const ElementType& ElementA, mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixB);







template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator+(mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixA, const mdkSparseShadowMatrix<ElementType>& ShadowMatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator-(mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixA, const mdkSparseShadowMatrix<ElementType>& ShadowMatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForMultiplication<ElementType> operator*(mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixA, const mdkSparseShadowMatrix<ElementType>& ShadowMatrixB);







template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator+(const mdkSparseShadowMatrix<ElementType>& ShadowMatrixA, mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator-(const mdkSparseShadowMatrix<ElementType>& ShadowMatrixA, mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForMultiplication<ElementType> operator*(const mdkSparseShadowMatrix<ElementType>& ShadowMatrixA, mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixB);







template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator+(mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixA_M, mdkSparseGlueMatrixForLinearCombination<ElementType> GlueMatrixB_L);

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator-(mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixA_M, mdkSparseGlueMatrixForLinearCombination<ElementType> GlueMatrixB_L);

template<typename ElementType>
inline mdkSparseGlueMatrixForMultiplication<ElementType> operator*(mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixA_M, const mdkSparseGlueMatrixForLinearCombination<ElementType>& GlueMatrixB_L);







template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator+(mdkSparseGlueMatrixForLinearCombination<ElementType> GlueMatrixA_L, mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixB_M);

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator-(mdkSparseGlueMatrixForLinearCombination<ElementType> GlueMatrixA_L, mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixB_M);

template<typename ElementType>
inline mdkSparseGlueMatrixForMultiplication<ElementType> operator*(const mdkSparseGlueMatrixForLinearCombination<ElementType>& GlueMatrixA_L, mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixB_M);







template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator+(mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixA, mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator-(mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixA, mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForMultiplication<ElementType> operator*(mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixA, mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixB);

} 

#include "mdkSparseMatrixOperator_SparseMatrix.hpp"
#include "mdkSparseMatrixOperator_SparseShadowMatrix.hpp"
#include "mdkSparseMatrixOperator_SparseGlueMatrixForLinearCombination.hpp"
#include "mdkSparseMatrixOperator_SparseGlueMatrixForMultiplication.hpp"

#endif 