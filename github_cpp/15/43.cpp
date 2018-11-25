#pragma once

namespace mdk
{



template<typename ElementType>
class DenseMatrix;

struct mdkMatrixSize;

template<typename ElementType>
class DenseShadowMatrix;

template<typename ElementType>
class DenseGlueMatrixForLinearCombination;

template<typename ElementType>
class DenseGlueMatrixForMultiplication;
















template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator+(const DenseMatrix<ElementType>& MatrixA, const DenseMatrix<ElementType>& MatrixB);

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator-(const DenseMatrix<ElementType>& MatrixA, const DenseMatrix<ElementType>& MatrixB);

template<typename ElementType>
inline DenseGlueMatrixForMultiplication<ElementType> operator*(const DenseMatrix<ElementType>& MatrixA, const DenseMatrix<ElementType>& MatrixB);

template<typename ElementType>
inline DenseMatrix<ElementType> operator/(const DenseMatrix<ElementType>& MatrixA, const DenseMatrix<ElementType>& MatrixB);






template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator+(const DenseMatrix<ElementType>& MatrixA, const ElementType& ElementB);

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator-(const DenseMatrix<ElementType>& MatrixA, const ElementType& ElementB);

template<typename ElementType>
inline DenseGlueMatrixForMultiplication<ElementType> operator*(const DenseMatrix<ElementType>& MatrixA, const ElementType& ElementB);

template<typename ElementType>
inline DenseGlueMatrixForMultiplication<ElementType> operator/(const DenseMatrix<ElementType>& MatrixA, const ElementType& ElementB);







template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator+(const ElementType& ElementA, const DenseMatrix<ElementType>& MatrixB);

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator-(const ElementType& ElementA, const DenseMatrix<ElementType>& MatrixB);

template<typename ElementType>
inline DenseGlueMatrixForMultiplication<ElementType> operator*(const ElementType& ElementA, const DenseMatrix<ElementType>& MatrixB);

template<typename ElementType>
inline DenseMatrix<ElementType> operator/(const ElementType& ElementA, const DenseMatrix<ElementType>& MatrixB);












template<typename ElementType>
inline DenseMatrix<ElementType> operator+(const DenseShadowMatrix<ElementType>& ShadowMatrixA, const DenseMatrix<ElementType>& MatrixB);

template<typename ElementType>
inline DenseMatrix<ElementType> operator-(const DenseShadowMatrix<ElementType>& ShadowMatrixA, const DenseMatrix<ElementType>& MatrixB);

template<typename ElementType>
inline DenseGlueMatrixForMultiplication<ElementType> operator*(const DenseShadowMatrix<ElementType>& ShadowMatrixA, const DenseMatrix<ElementType>& MatrixB);

template<typename ElementType>
inline DenseMatrix<ElementType> operator/(const DenseShadowMatrix<ElementType>& ShadowMatrixA, const DenseMatrix<ElementType>& MatrixB);







template<typename ElementType>
inline DenseMatrix<ElementType> operator+(const DenseMatrix<ElementType>& MatrixA, const DenseShadowMatrix<ElementType>& ShadowMatrixB);

template<typename ElementType>
inline DenseMatrix<ElementType> operator-(const DenseMatrix<ElementType>& MatrixA, const DenseShadowMatrix<ElementType>& ShadowMatrixB);

template<typename ElementType>
inline DenseGlueMatrixForMultiplication<ElementType> operator*(const DenseMatrix<ElementType>& MatrixA, const DenseShadowMatrix<ElementType>& ShadowMatrixB);

template<typename ElementType>
inline DenseMatrix<ElementType> operator/(const DenseMatrix<ElementType>& MatrixA, const DenseShadowMatrix<ElementType>& ShadowMatrixB);





template<typename ElementType>
inline DenseMatrix<ElementType> operator+(const DenseShadowMatrix<ElementType>& ShadowMatrixA, const ElementType& ElementB);

template<typename ElementType>
inline DenseMatrix<ElementType> operator-(const DenseShadowMatrix<ElementType>& ShadowMatrixA, const ElementType& ElementB);

template<typename ElementType>
inline DenseMatrix<ElementType> operator*(const DenseShadowMatrix<ElementType>& ShadowMatrixA, const ElementType& ElementB);

template<typename ElementType>
inline DenseMatrix<ElementType> operator/(const DenseShadowMatrix<ElementType>& ShadowMatrixA, const ElementType& ElementB);





template<typename ElementType>
inline DenseMatrix<ElementType> operator+(const ElementType& ElementA, const DenseShadowMatrix<ElementType>& ShadowMatrixB);

template<typename ElementType>
inline DenseMatrix<ElementType> operator-(const ElementType& ElementA, const DenseShadowMatrix<ElementType>& ShadowMatrixB);

template<typename ElementType>
inline DenseMatrix<ElementType> operator*(const ElementType& ElementA, const DenseShadowMatrix<ElementType>& ShadowMatrixB);

template<typename ElementType>
inline DenseMatrix<ElementType> operator/(const ElementType& ElementA, const DenseShadowMatrix<ElementType>& ShadowMatrixB);







template<typename ElementType>
inline DenseMatrix<ElementType> operator+(const DenseShadowMatrix<ElementType>& ShadowMatrixA, const DenseShadowMatrix<ElementType>& ShadowMatrixB);

template<typename ElementType>
inline DenseMatrix<ElementType> operator-(const DenseShadowMatrix<ElementType>& ShadowMatrixA, const DenseShadowMatrix<ElementType>& ShadowMatrixB);

template<typename ElementType>
inline DenseGlueMatrixForMultiplication<ElementType> operator*(const DenseShadowMatrix<ElementType>& ShadowMatrixA, const DenseShadowMatrix<ElementType>& ShadowMatrixB);

template<typename ElementType>
inline DenseMatrix<ElementType> operator/(const DenseShadowMatrix<ElementType>& ShadowMatrixA, const DenseShadowMatrix<ElementType>& ShadowMatrixB);













template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator+(DenseGlueMatrixForLinearCombination<ElementType> GlueMatrixA, const DenseMatrix<ElementType>& MatrixB);

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator-(DenseGlueMatrixForLinearCombination<ElementType> GlueMatrixA, const DenseMatrix<ElementType>& MatrixB);

template<typename ElementType>
inline DenseGlueMatrixForMultiplication<ElementType> operator*(const DenseGlueMatrixForLinearCombination<ElementType>& GlueMatrixA, const DenseMatrix<ElementType>& MatrixB);

template<typename ElementType>
inline DenseMatrix<ElementType> operator/(const DenseGlueMatrixForLinearCombination<ElementType>& GlueMatrixA, const DenseMatrix<ElementType>& MatrixB);







template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator+(const DenseMatrix<ElementType>& MatrixA, DenseGlueMatrixForLinearCombination<ElementType> GlueMatrixB);

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator-(const DenseMatrix<ElementType>& MatrixA, DenseGlueMatrixForLinearCombination<ElementType> GlueMatrixB);

template<typename ElementType>
inline DenseGlueMatrixForMultiplication<ElementType> operator*(const DenseMatrix<ElementType>& MatrixA, const DenseGlueMatrixForLinearCombination<ElementType>& GlueMatrixB);

template<typename ElementType>
inline DenseMatrix<ElementType> operator/(const DenseMatrix<ElementType>& MatrixA, const DenseGlueMatrixForLinearCombination<ElementType>& GlueMatrixB);





template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator+(DenseGlueMatrixForLinearCombination<ElementType> GlueMatrixA, const ElementType& ElementB);

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator-(DenseGlueMatrixForLinearCombination<ElementType> GlueMatrixA, const ElementType& ElementB);

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator*(DenseGlueMatrixForLinearCombination<ElementType> GlueMatrixA, const ElementType& ElementB);

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator/(DenseGlueMatrixForLinearCombination<ElementType> GlueMatrixA, const ElementType& ElementB);






template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator+(const ElementType& ElementA, DenseGlueMatrixForLinearCombination<ElementType> GlueMatrixB);

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator-(const ElementType& ElementA, DenseGlueMatrixForLinearCombination<ElementType> GlueMatrixB);

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator*(const ElementType& ElementA, DenseGlueMatrixForLinearCombination<ElementType> GlueMatrixB);

template<typename ElementType>
inline DenseMatrix<ElementType> operator/(const ElementType& ElementA, const DenseGlueMatrixForLinearCombination<ElementType>& GlueMatrixB);







template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator+(DenseGlueMatrixForLinearCombination<ElementType> GlueMatrixA, const DenseShadowMatrix<ElementType>& ShadowMatrixB);

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator-(DenseGlueMatrixForLinearCombination<ElementType> GlueMatrixA, const DenseShadowMatrix<ElementType>& ShadowMatrixB);

template<typename ElementType>
inline DenseGlueMatrixForMultiplication<ElementType> operator*(const DenseGlueMatrixForLinearCombination<ElementType>& GlueMatrixA, const DenseShadowMatrix<ElementType>& ShadowMatrixB);

template<typename ElementType>
inline DenseMatrix<ElementType> operator/(const DenseGlueMatrixForLinearCombination<ElementType>& GlueMatrixA, const DenseShadowMatrix<ElementType>& ShadowMatrixB);







template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator+(const DenseShadowMatrix<ElementType>& ShadowMatrixA, DenseGlueMatrixForLinearCombination<ElementType> GlueMatrixB);

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator-(const DenseShadowMatrix<ElementType>& ShadowMatrixA, DenseGlueMatrixForLinearCombination<ElementType> GlueMatrixB);

template<typename ElementType>
inline DenseGlueMatrixForMultiplication<ElementType> operator*(const DenseShadowMatrix<ElementType>& ShadowMatrixA, const DenseGlueMatrixForLinearCombination<ElementType>& GlueMatrixB);

template<typename ElementType>
inline DenseMatrix<ElementType> operator/(const DenseShadowMatrix<ElementType>& ShadowMatrixA, const DenseGlueMatrixForLinearCombination<ElementType>& GlueMatrixB);







template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator+(DenseGlueMatrixForLinearCombination<ElementType> GlueMatrixA, DenseGlueMatrixForLinearCombination<ElementType> GlueMatrixB);

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator-(DenseGlueMatrixForLinearCombination<ElementType> GlueMatrixA, DenseGlueMatrixForLinearCombination<ElementType> GlueMatrixB);

template<typename ElementType>
inline DenseGlueMatrixForMultiplication<ElementType> operator*(const DenseGlueMatrixForLinearCombination<ElementType>& GlueMatrixA, const DenseGlueMatrixForLinearCombination<ElementType>& GlueMatrixB);

template<typename ElementType>
inline DenseMatrix<ElementType> operator/(const DenseGlueMatrixForLinearCombination<ElementType>& GlueMatrixA, const DenseGlueMatrixForLinearCombination<ElementType>& GlueMatrixB);













template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator+(DenseGlueMatrixForMultiplication<ElementType> GlueMatrixA, const DenseMatrix<ElementType>& MatrixB);

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator-(DenseGlueMatrixForMultiplication<ElementType> GlueMatrixA, const DenseMatrix<ElementType>& MatrixB);

template<typename ElementType>
inline DenseGlueMatrixForMultiplication<ElementType> operator*(DenseGlueMatrixForMultiplication<ElementType> GlueMatrixA, const DenseMatrix<ElementType>& MatrixB);

template<typename ElementType>
inline DenseMatrix<ElementType> operator/(const DenseGlueMatrixForMultiplication<ElementType>& GlueMatrixA, const DenseMatrix<ElementType>& MatrixB);







template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator+(const DenseMatrix<ElementType>& MatrixA, DenseGlueMatrixForMultiplication<ElementType> GlueMatrixB);

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator-(const DenseMatrix<ElementType>& MatrixA, DenseGlueMatrixForMultiplication<ElementType> GlueMatrixB);

template<typename ElementType>
inline DenseGlueMatrixForMultiplication<ElementType> operator*(const DenseMatrix<ElementType>& MatrixA, DenseGlueMatrixForMultiplication<ElementType> GlueMatrixB);

template<typename ElementType>
inline DenseMatrix<ElementType> operator/(const DenseMatrix<ElementType>& MatrixA, const DenseGlueMatrixForMultiplication<ElementType> GlueMatrixB);






template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator+(DenseGlueMatrixForMultiplication<ElementType> GlueMatrixA, const ElementType& ElementB);

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator-(DenseGlueMatrixForMultiplication<ElementType> GlueMatrixA, const ElementType& ElementB);

template<typename ElementType>
inline DenseGlueMatrixForMultiplication<ElementType> operator*(DenseGlueMatrixForMultiplication<ElementType> GlueMatrixA, const ElementType& ElementB);

template<typename ElementType>
inline DenseGlueMatrixForMultiplication<ElementType> operator/(DenseGlueMatrixForMultiplication<ElementType> GlueMatrixA, const ElementType& ElementB);







template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator+(const ElementType& ElementA, DenseGlueMatrixForMultiplication<ElementType> GlueMatrixB);

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator-(const ElementType& ElementA, DenseGlueMatrixForMultiplication<ElementType> GlueMatrixB);

template<typename ElementType>
inline DenseGlueMatrixForMultiplication<ElementType> operator*(const ElementType& ElementA, DenseGlueMatrixForMultiplication<ElementType> GlueMatrixB);

template<typename ElementType>
inline DenseMatrix<ElementType> operator/(const ElementType& ElementA, const DenseGlueMatrixForMultiplication<ElementType>& GlueMatrixB);







template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator+(DenseGlueMatrixForMultiplication<ElementType> GlueMatrixA, const DenseShadowMatrix<ElementType>& ShadowMatrixB);

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator-(DenseGlueMatrixForMultiplication<ElementType> GlueMatrixA, const DenseShadowMatrix<ElementType>& ShadowMatrixB);

template<typename ElementType>
inline DenseGlueMatrixForMultiplication<ElementType> operator*(DenseGlueMatrixForMultiplication<ElementType> GlueMatrixA, const DenseShadowMatrix<ElementType>& ShadowMatrixB);

template<typename ElementType>
inline DenseMatrix<ElementType> operator/(const DenseGlueMatrixForMultiplication<ElementType>& GlueMatrixA, const DenseShadowMatrix<ElementType>& ShadowMatrixB);







template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator+(const DenseShadowMatrix<ElementType>& ShadowMatrixA, DenseGlueMatrixForMultiplication<ElementType> GlueMatrixB);

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator-(const DenseShadowMatrix<ElementType>& ShadowMatrixA, DenseGlueMatrixForMultiplication<ElementType> GlueMatrixB);

template<typename ElementType>
inline DenseGlueMatrixForMultiplication<ElementType> operator*(const DenseShadowMatrix<ElementType>& ShadowMatrixA, DenseGlueMatrixForMultiplication<ElementType> GlueMatrixB);

template<typename ElementType>
inline DenseMatrix<ElementType> operator/(const DenseShadowMatrix<ElementType>& ShadowMatrixA, const DenseGlueMatrixForMultiplication<ElementType>& GlueMatrixB);







template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator+(DenseGlueMatrixForMultiplication<ElementType> GlueMatrixA_M, DenseGlueMatrixForLinearCombination<ElementType> GlueMatrixB_L);

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator-(DenseGlueMatrixForMultiplication<ElementType> GlueMatrixA_M, DenseGlueMatrixForLinearCombination<ElementType> GlueMatrixB_L);

template<typename ElementType>
inline DenseGlueMatrixForMultiplication<ElementType> operator*(DenseGlueMatrixForMultiplication<ElementType> GlueMatrixA_M, const DenseGlueMatrixForLinearCombination<ElementType>& GlueMatrixB_L);

template<typename ElementType>
inline DenseMatrix<ElementType> operator/(const DenseGlueMatrixForMultiplication<ElementType>& GlueMatrixA_M, const DenseGlueMatrixForLinearCombination<ElementType>& GlueMatrixB_L);







template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator+(DenseGlueMatrixForLinearCombination<ElementType> GlueMatrixA_L, DenseGlueMatrixForMultiplication<ElementType> GlueMatrixB_M);

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator-(DenseGlueMatrixForLinearCombination<ElementType> GlueMatrixA_L, DenseGlueMatrixForMultiplication<ElementType> GlueMatrixB_M);

template<typename ElementType>
inline DenseGlueMatrixForMultiplication<ElementType> operator*(const DenseGlueMatrixForLinearCombination<ElementType>& GlueMatrixA_L, DenseGlueMatrixForMultiplication<ElementType> GlueMatrixB_M);

template<typename ElementType>
inline DenseMatrix<ElementType> operator/(const DenseGlueMatrixForLinearCombination<ElementType>& GlueMatrixA_L, const DenseGlueMatrixForMultiplication<ElementType>& GlueMatrixB_M);







template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator+(DenseGlueMatrixForMultiplication<ElementType> GlueMatrixA, DenseGlueMatrixForMultiplication<ElementType> GlueMatrixB);

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator-(DenseGlueMatrixForMultiplication<ElementType> GlueMatrixA, DenseGlueMatrixForMultiplication<ElementType> GlueMatrixB);

template<typename ElementType>
inline DenseGlueMatrixForMultiplication<ElementType> operator*(DenseGlueMatrixForMultiplication<ElementType> GlueMatrixA, DenseGlueMatrixForMultiplication<ElementType> GlueMatrixB);

template<typename ElementType>
inline DenseMatrix<ElementType> operator/(const DenseGlueMatrixForMultiplication<ElementType>& GlueMatrixA, const DenseGlueMatrixForMultiplication<ElementType>& GlueMatrixB);

} 

#include "mdkDenseMatrixOperator_DenseMatrix.hpp"
#include "mdkDenseMatrixOperator_DenseShadowMatrix.hpp"
#include "mdkDenseMatrixOperator_DenseGlueMatrixForLinearCombination.hpp"
#include "mdkDenseMatrixOperator_DenseGlueMatrixForMultiplication.hpp"
