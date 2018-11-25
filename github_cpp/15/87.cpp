#pragma once

#include "mdkObject.h"
#include "mdkLinearAlgebraConfig.h"


namespace mdk
{



template<typename ElementType>
class DenseMatrix;

template<typename ElementType>
class DenseShadowMatrix;

template<typename ElementType>
class DenseGlueMatrixForLinearCombination;

struct MatrixSize;





#define MDK_DenseGlueMatrixForMultiplication_ReservedCapacity  10


template<typename ElementType>
class DenseGlueMatrixForMultiplication : public Object
{
private:

    int_max m_RowCount;

    int_max m_ColCount;

    std::vector<DenseMatrix<ElementType>> m_SourceMatrixSharedCopyList;

    ElementType m_Element_Coef;

    bool m_Is_m_Element_Coef_Equal_to_One;

    
private:
    inline DenseGlueMatrixForMultiplication();

public:
    inline ~DenseGlueMatrixForMultiplication();

private:
    inline DenseGlueMatrixForMultiplication(const DenseGlueMatrixForMultiplication<ElementType>& DenseGlueMatrix) = delete;

public:
    inline DenseGlueMatrixForMultiplication(DenseGlueMatrixForMultiplication<ElementType>&& DenseGlueMatrix);

    
private:

    inline int_max GetRowCount() const;

    inline int_max GetColCount() const;

    inline int_max GetElementCount() const;

    inline MatrixSize GetSize() const;

	inline int_max GetMatrixCount() const;

    inline bool IsEmpty() const;

    inline DenseMatrix<ElementType> CreateDenseMatrix() const;

    inline bool CreateDenseMatrix(DenseMatrix<ElementType>& OutputMatrix) const;

public:

    inline DenseMatrix<ElementType> ElementMultiply(const DenseMatrix<ElementType>& targetMatrix);

    inline DenseMatrix<ElementType> ElementMultiply(const ElementType& Element);

    inline DenseMatrix<ElementType> ElementMultiply(const DenseShadowMatrix<ElementType>& ShadowMatrix);

    inline DenseMatrix<ElementType> ElementMultiply(const DenseGlueMatrixForLinearCombination<ElementType>& DenseGlueMatrix);

    inline DenseMatrix<ElementType> ElementMultiply(const DenseGlueMatrixForMultiplication<ElementType>& DenseGlueMatrix);

private:
    

    void operator=(const DenseGlueMatrixForMultiplication<ElementType>& DenseGlueMatrix) = delete;
    void operator=(DenseGlueMatrixForMultiplication<ElementType>&& DenseGlueMatrix) = delete;

    

    template<typename E_TYPE>
    friend class DenseMatrix;

    template<typename E_TYPE>
    friend class DenseShadowMatrix;

    

    

    template<typename E_TYPE>
    friend DenseGlueMatrixForMultiplication<E_TYPE> operator*(const DenseMatrix<E_TYPE>& MatrixA, const DenseMatrix<E_TYPE>& MatrixB);

    

    template<typename E_TYPE>
    friend DenseGlueMatrixForMultiplication<E_TYPE> operator*(const DenseMatrix<E_TYPE>& MatrixA, const E_TYPE& ElementB);

    template<typename E_TYPE>
    friend DenseGlueMatrixForMultiplication<E_TYPE> operator/(const DenseMatrix<E_TYPE>& MatrixA, const E_TYPE& ElementB);

    

    template<typename E_TYPE>
    friend DenseGlueMatrixForMultiplication<E_TYPE> operator*(const E_TYPE& ElementA, const DenseMatrix<E_TYPE>& MatrixB);

    

    template<typename E_TYPE>
    friend DenseGlueMatrixForMultiplication<E_TYPE> operator*(const DenseMatrix<E_TYPE>& MatrixA, const DenseShadowMatrix<E_TYPE>& ShadowMatrixB);

    

    template<typename E_TYPE>
    friend DenseGlueMatrixForMultiplication<E_TYPE> operator*(const DenseShadowMatrix<E_TYPE>& ShadowMatrixA, const DenseMatrix<E_TYPE>& MatrixB);

    

    template<typename E_TYPE>
    friend DenseGlueMatrixForMultiplication<E_TYPE> operator*(const DenseShadowMatrix<E_TYPE>& ShadowMatrixA, const DenseShadowMatrix<E_TYPE>& ShadowMatrixB);

    

    template<typename E_TYPE>
    friend DenseGlueMatrixForMultiplication<E_TYPE> operator*(const DenseMatrix<E_TYPE>& MatrixA, const DenseGlueMatrixForLinearCombination<E_TYPE>& GlueMatrixB);


    

    template<typename E_TYPE>
    friend DenseGlueMatrixForMultiplication<E_TYPE> operator*(const DenseGlueMatrixForLinearCombination<E_TYPE>& GlueMatrixA, const DenseMatrix<E_TYPE>& MatrixB);


    

    template<typename E_TYPE>
    friend DenseGlueMatrixForMultiplication<E_TYPE> operator*(const DenseShadowMatrix<E_TYPE>& ShadowMatrixA, const DenseGlueMatrixForLinearCombination<E_TYPE>& GlueMatrixB);

    

    template<typename E_TYPE>
    friend DenseGlueMatrixForMultiplication<E_TYPE> operator*(const DenseGlueMatrixForLinearCombination<E_TYPE>& GlueMatrixA, const DenseShadowMatrix<E_TYPE>& ShadowMatrixB);

    

    template<typename E_TYPE>
    friend DenseGlueMatrixForMultiplication<E_TYPE> operator*(const DenseGlueMatrixForLinearCombination<E_TYPE>& GlueMatrixA, const DenseGlueMatrixForLinearCombination<E_TYPE>& GlueMatrixB);

    

    template<typename E_TYPE>
    friend DenseGlueMatrixForLinearCombination<E_TYPE> operator+(DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixA, const DenseMatrix<E_TYPE>& MatrixB);

    template<typename E_TYPE>
    friend DenseGlueMatrixForLinearCombination<E_TYPE> operator-(DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixA, const DenseMatrix<E_TYPE>& MatrixB);

    template<typename E_TYPE>
    friend DenseGlueMatrixForMultiplication<E_TYPE> operator*(DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixA, const DenseMatrix<E_TYPE>& MatrixB);

    template<typename E_TYPE>
    friend DenseMatrix<E_TYPE> operator/(const DenseGlueMatrixForMultiplication<E_TYPE>& GlueMatrixA, const DenseMatrix<E_TYPE>& MatrixB);

    

    template<typename E_TYPE>
    friend DenseGlueMatrixForLinearCombination<E_TYPE> operator+(const DenseMatrix<E_TYPE>& MatrixA, DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixB);

    template<typename E_TYPE>
    friend DenseGlueMatrixForLinearCombination<E_TYPE> operator-(const DenseMatrix<E_TYPE>& MatrixA, DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixB);

    template<typename E_TYPE>
    friend DenseGlueMatrixForMultiplication<E_TYPE> operator*(const DenseMatrix<E_TYPE>& MatrixA, DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixB);

    template<typename E_TYPE>
    friend DenseMatrix<E_TYPE> operator/(const DenseMatrix<E_TYPE>& MatrixA, const DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixB);

    

    template<typename E_TYPE>
    friend DenseGlueMatrixForLinearCombination<E_TYPE> operator+(DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixA, const E_TYPE& ElementB);

    template<typename E_TYPE>
    friend DenseGlueMatrixForLinearCombination<E_TYPE> operator-(DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixA, const E_TYPE& ElementB);

    template<typename E_TYPE>
    friend DenseGlueMatrixForMultiplication<E_TYPE> operator*(DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixA, const E_TYPE& ElementB);

    template<typename E_TYPE>
    friend DenseGlueMatrixForMultiplication<E_TYPE> operator/(DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixA, const E_TYPE& ElementB);

    

    template<typename E_TYPE>
    friend DenseGlueMatrixForLinearCombination<E_TYPE> operator+(const E_TYPE& ElementA, DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixB);

    template<typename E_TYPE>
    friend DenseGlueMatrixForLinearCombination<E_TYPE> operator-(const E_TYPE& ElementA, DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixB);

    template<typename E_TYPE>
    friend DenseGlueMatrixForMultiplication<E_TYPE> operator*(const E_TYPE& ElementA, DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixB);

    template<typename E_TYPE>
    friend DenseMatrix<E_TYPE> operator/(const E_TYPE& ElementA, const DenseGlueMatrixForMultiplication<E_TYPE>& GlueMatrixB);

    

    template<typename E_TYPE>
    friend DenseGlueMatrixForLinearCombination<E_TYPE> operator+(DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixA, const DenseShadowMatrix<E_TYPE>& ShadowMatrixB);

    template<typename E_TYPE>
    friend DenseGlueMatrixForLinearCombination<E_TYPE> operator-(DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixA, const DenseShadowMatrix<E_TYPE>& ShadowMatrixB);

    template<typename E_TYPE>
    friend DenseGlueMatrixForMultiplication<E_TYPE> operator*(DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixA, const DenseShadowMatrix<E_TYPE>& ShadowMatrixB);

    template<typename E_TYPE>
    friend DenseMatrix<E_TYPE> operator/(const DenseGlueMatrixForMultiplication<E_TYPE>& GlueMatrixA, const DenseShadowMatrix<E_TYPE>& ShadowMatrixB);

    

    template<typename E_TYPE>
    friend DenseGlueMatrixForLinearCombination<E_TYPE> operator+(const DenseShadowMatrix<E_TYPE>& ShadowMatrixA, DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixB);

    template<typename E_TYPE>
    friend DenseGlueMatrixForLinearCombination<E_TYPE> operator-(const DenseShadowMatrix<E_TYPE>& ShadowMatrixA, DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixB);

    template<typename E_TYPE>
    friend DenseGlueMatrixForMultiplication<E_TYPE> operator*(const DenseShadowMatrix<E_TYPE>& ShadowMatrixA, DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixB);

    template<typename E_TYPE>
    friend DenseMatrix<E_TYPE> operator/(const DenseShadowMatrix<E_TYPE>& ShadowMatrixA, const DenseGlueMatrixForMultiplication<E_TYPE>& GlueMatrixB);

    

    template<typename E_TYPE>
    friend DenseGlueMatrixForLinearCombination<E_TYPE> operator+(DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixA_M, DenseGlueMatrixForLinearCombination<E_TYPE> GlueMatrixB_L);

    template<typename E_TYPE>
    friend DenseGlueMatrixForLinearCombination<E_TYPE> operator-(DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixA_M, DenseGlueMatrixForLinearCombination<E_TYPE> GlueMatrixB_L);

    template<typename E_TYPE>
    friend DenseGlueMatrixForMultiplication<E_TYPE> operator*(DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixA_M, const DenseGlueMatrixForLinearCombination<E_TYPE>& GlueMatrixB_L);

    template<typename E_TYPE>
    friend DenseMatrix<E_TYPE> operator/(const DenseGlueMatrixForMultiplication<E_TYPE>& GlueMatrixA_M, const DenseGlueMatrixForLinearCombination<E_TYPE>& GlueMatrixB_L);

    

    template<typename E_TYPE>
    friend DenseGlueMatrixForLinearCombination<E_TYPE> operator+(DenseGlueMatrixForLinearCombination<E_TYPE> GlueMatrixA_L, DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixB_M);

    template<typename E_TYPE>
    friend DenseGlueMatrixForLinearCombination<E_TYPE> operator-(DenseGlueMatrixForLinearCombination<E_TYPE> GlueMatrixA_L, DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixB_M);

    template<typename E_TYPE>
    friend DenseGlueMatrixForMultiplication<E_TYPE> operator*(const DenseGlueMatrixForLinearCombination<E_TYPE>& GlueMatrixA_L, DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixB_M);

    template<typename E_TYPE>
    friend DenseMatrix<E_TYPE> operator/(const DenseGlueMatrixForLinearCombination<E_TYPE>& GlueMatrixA_L, const DenseGlueMatrixForMultiplication<E_TYPE>& GlueMatrixB_M);

    

    template<typename E_TYPE>
    friend DenseGlueMatrixForLinearCombination<E_TYPE> operator+(DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixA, DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixB);

    template<typename E_TYPE>
    friend DenseGlueMatrixForLinearCombination<E_TYPE> operator-(DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixA, DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixB);

    template<typename E_TYPE>
    friend DenseGlueMatrixForMultiplication<E_TYPE> operator*(DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixA, const DenseGlueMatrixForMultiplication<E_TYPE>& GlueMatrixB);

    template<typename E_TYPE>
    friend DenseMatrix<E_TYPE> operator/(const DenseGlueMatrixForMultiplication<E_TYPE>& GlueMatrixA, const DenseGlueMatrixForMultiplication<E_TYPE>& GlueMatrixB);

};


}

#include "mdkDenseGlueMatrixForMultiplication.hpp"
