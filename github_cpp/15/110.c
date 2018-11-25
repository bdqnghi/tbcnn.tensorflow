#ifndef mdk_SparseGlueMatrixForMultiplication_h
#define mdk_SparseGlueMatrixForMultiplication_h

#include "mdkObject.h"
#include "mdkLinearAlgebraConfig.h"



namespace mdk
{



struct MatrixSize;

template<typename ElementType>
class SparseMatrix;

template<typename ElementType>
class SparseShadowMatrix;

template<typename ElementType>
class SparseGlueMatrixForLinearCombination;






#define MDK_SparseGlueMatrixForMultiplication_ReservedCapacity  10


template<typename ElementType>
class SparseGlueMatrixForMultiplication : public Object
{
private:

    int64 m_RowNumber;

    int64 m_ColNumber;

    std::vector<SparseMatrix<ElementType>> m_SourceMatrixSharedCopyList;

    ElementType m_Element_Coef;

    bool m_Is_m_Element_Coef_Equal_to_One;

    
private:
    inline SparseGlueMatrixForMultiplication();

public:
    inline ~SparseGlueMatrixForMultiplication();

private:
    inline SparseGlueMatrixForMultiplication(const SparseGlueMatrixForMultiplication<ElementType>& SparseGlueMatrix) = delete;

public:
    inline SparseGlueMatrixForMultiplication(SparseGlueMatrixForMultiplication<ElementType>&& SparseGlueMatrix);

    
private:
    inline void Reset();

    inline int64 GetRowNumber() const;

    inline int64 GetColNumber() const;

    inline int64 GetElementNumber() const;

    inline MatrixSize GetSize() const;

    inline int64 GetMatrixNumber() const;

    inline bool IsEmpty() const;

    inline SparseMatrix<ElementType> CreateSparseMatrix() const;

    inline bool CreateSparseMatrix(SparseMatrix<ElementType>& OutputMatrix) const;

    inline DenseMatrix<ElementType> CreateDenseMatrix() const;

    inline bool CreateDenseMatrix(DenseMatrix<ElementType>& OutputMatrix) const;

public:

    inline SparseMatrix<ElementType> ElementMultiply(const SparseMatrix<ElementType>& targetMatrix);

    inline SparseMatrix<ElementType> ElementMultiply(const ElementType& Element);

    inline SparseMatrix<ElementType> ElementMultiply(const SparseShadowMatrix<ElementType>& ShadowMatrix);

    inline SparseMatrix<ElementType> ElementMultiply(const SparseGlueMatrixForLinearCombination<ElementType>& SparseGlueMatrix);

    inline SparseMatrix<ElementType> ElementMultiply(const SparseGlueMatrixForMultiplication<ElementType>& SparseGlueMatrix);

private:
    

    void operator=(const SparseGlueMatrixForMultiplication<ElementType>& SparseGlueMatrix) = delete;
    void operator=(SparseGlueMatrixForMultiplication<ElementType>&& SparseGlueMatrix) = delete;

    

    template<typename E_TYPE>
    friend class SparseMatrix;

    template<typename E_TYPE>
    friend class SparseShadowMatrix;

    

    

    template<typename E_TYPE>
    friend SparseGlueMatrixForMultiplication<E_TYPE> operator*(const SparseMatrix<E_TYPE>& MatrixA, const SparseMatrix<E_TYPE>& MatrixB);

    

    template<typename E_TYPE>
    friend SparseGlueMatrixForMultiplication<E_TYPE> operator*(const SparseMatrix<E_TYPE>& MatrixA, const E_TYPE& ElementB);

    template<typename E_TYPE>
    friend SparseGlueMatrixForMultiplication<E_TYPE> operator/(const SparseMatrix<E_TYPE>& MatrixA, const E_TYPE& ElementB);

    

    template<typename E_TYPE>
    friend SparseGlueMatrixForMultiplication<E_TYPE> operator*(const E_TYPE& ElementA, const SparseMatrix<E_TYPE>& MatrixB);

    

    template<typename E_TYPE>
    friend SparseGlueMatrixForMultiplication<E_TYPE> operator*(const SparseMatrix<E_TYPE>& MatrixA, const SparseShadowMatrix<E_TYPE>& ShadowMatrixB);

    

    template<typename E_TYPE>
    friend SparseGlueMatrixForMultiplication<E_TYPE> operator*(const SparseShadowMatrix<E_TYPE>& ShadowMatrixA, const SparseMatrix<E_TYPE>& MatrixB);

    

    template<typename E_TYPE>
    friend SparseGlueMatrixForMultiplication<E_TYPE> operator*(const SparseShadowMatrix<E_TYPE>& ShadowMatrixA, const SparseShadowMatrix<E_TYPE>& ShadowMatrixB);

    

    template<typename E_TYPE>
    friend SparseGlueMatrixForMultiplication<E_TYPE> operator*(const SparseMatrix<E_TYPE>& MatrixA, const SparseGlueMatrixForLinearCombination<E_TYPE>& GlueMatrixB);


    

    template<typename E_TYPE>
    friend SparseGlueMatrixForMultiplication<E_TYPE> operator*(const SparseGlueMatrixForLinearCombination<E_TYPE>& GlueMatrixA, const SparseMatrix<E_TYPE>& MatrixB);


    

    template<typename E_TYPE>
    friend SparseGlueMatrixForMultiplication<E_TYPE> operator*(const SparseShadowMatrix<E_TYPE>& ShadowMatrixA, const SparseGlueMatrixForLinearCombination<E_TYPE>& GlueMatrixB);

    

    template<typename E_TYPE>
    friend SparseGlueMatrixForMultiplication<E_TYPE> operator*(const SparseGlueMatrixForLinearCombination<E_TYPE>& GlueMatrixA, const SparseShadowMatrix<E_TYPE>& ShadowMatrixB);

    

    template<typename E_TYPE>
    friend SparseGlueMatrixForMultiplication<E_TYPE> operator*(const SparseGlueMatrixForLinearCombination<E_TYPE>& GlueMatrixA, const SparseGlueMatrixForLinearCombination<E_TYPE>& GlueMatrixB);

    

    template<typename E_TYPE>
    friend SparseGlueMatrixForLinearCombination<E_TYPE> operator+(SparseGlueMatrixForMultiplication<E_TYPE> GlueMatrixA, const SparseMatrix<E_TYPE>& MatrixB);

    template<typename E_TYPE>
    friend SparseGlueMatrixForLinearCombination<E_TYPE> operator-(SparseGlueMatrixForMultiplication<E_TYPE> GlueMatrixA, const SparseMatrix<E_TYPE>& MatrixB);

    template<typename E_TYPE>
    friend SparseGlueMatrixForMultiplication<E_TYPE> operator*(SparseGlueMatrixForMultiplication<E_TYPE> GlueMatrixA, const SparseMatrix<E_TYPE>& MatrixB);

    template<typename E_TYPE>
    friend SparseMatrix<E_TYPE> operator/(const SparseGlueMatrixForMultiplication<E_TYPE>& GlueMatrixA, const SparseMatrix<E_TYPE>& MatrixB);

    

    template<typename E_TYPE>
    friend SparseGlueMatrixForLinearCombination<E_TYPE> operator+(const SparseMatrix<E_TYPE>& MatrixA, SparseGlueMatrixForMultiplication<E_TYPE> GlueMatrixB);

    template<typename E_TYPE>
    friend SparseGlueMatrixForLinearCombination<E_TYPE> operator-(const SparseMatrix<E_TYPE>& MatrixA, SparseGlueMatrixForMultiplication<E_TYPE> GlueMatrixB);

    template<typename E_TYPE>
    friend SparseGlueMatrixForMultiplication<E_TYPE> operator*(const SparseMatrix<E_TYPE>& MatrixA, SparseGlueMatrixForMultiplication<E_TYPE> GlueMatrixB);

    template<typename E_TYPE>
    friend SparseMatrix<E_TYPE> operator/(const SparseMatrix<E_TYPE>& MatrixA, const SparseGlueMatrixForMultiplication<E_TYPE> GlueMatrixB);

    

    template<typename E_TYPE>
    friend SparseGlueMatrixForLinearCombination<E_TYPE> operator+(SparseGlueMatrixForMultiplication<E_TYPE> GlueMatrixA, const E_TYPE& ElementB);

    template<typename E_TYPE>
    friend SparseGlueMatrixForLinearCombination<E_TYPE> operator-(SparseGlueMatrixForMultiplication<E_TYPE> GlueMatrixA, const E_TYPE& ElementB);

    template<typename E_TYPE>
    friend SparseGlueMatrixForMultiplication<E_TYPE> operator*(SparseGlueMatrixForMultiplication<E_TYPE> GlueMatrixA, const E_TYPE& ElementB);

    template<typename E_TYPE>
    friend SparseGlueMatrixForMultiplication<E_TYPE> operator/(SparseGlueMatrixForMultiplication<E_TYPE> GlueMatrixA, const E_TYPE& ElementB);

    

    template<typename E_TYPE>
    friend SparseGlueMatrixForLinearCombination<E_TYPE> operator+(const E_TYPE& ElementA, SparseGlueMatrixForMultiplication<E_TYPE> GlueMatrixB);

    template<typename E_TYPE>
    friend SparseGlueMatrixForLinearCombination<E_TYPE> operator-(const E_TYPE& ElementA, SparseGlueMatrixForMultiplication<E_TYPE> GlueMatrixB);

    template<typename E_TYPE>
    friend SparseGlueMatrixForMultiplication<E_TYPE> operator*(const E_TYPE& ElementA, SparseGlueMatrixForMultiplication<E_TYPE> GlueMatrixB);

    template<typename E_TYPE>
    friend SparseMatrix<E_TYPE> operator/(const E_TYPE& ElementA, const SparseGlueMatrixForMultiplication<E_TYPE>& GlueMatrixB);

    

    template<typename E_TYPE>
    friend SparseGlueMatrixForLinearCombination<E_TYPE> operator+(SparseGlueMatrixForMultiplication<E_TYPE> GlueMatrixA, const SparseShadowMatrix<E_TYPE>& ShadowMatrixB);

    template<typename E_TYPE>
    friend SparseGlueMatrixForLinearCombination<E_TYPE> operator-(SparseGlueMatrixForMultiplication<E_TYPE> GlueMatrixA, const SparseShadowMatrix<E_TYPE>& ShadowMatrixB);

    template<typename E_TYPE>
    friend SparseGlueMatrixForMultiplication<E_TYPE> operator*(SparseGlueMatrixForMultiplication<E_TYPE> GlueMatrixA, const SparseShadowMatrix<E_TYPE>& ShadowMatrixB);

    template<typename E_TYPE>
    friend SparseMatrix<E_TYPE> operator/(const SparseGlueMatrixForMultiplication<E_TYPE>& GlueMatrixA, const SparseShadowMatrix<E_TYPE>& ShadowMatrixB);

    

    template<typename E_TYPE>
    friend SparseGlueMatrixForLinearCombination<E_TYPE> operator+(const SparseShadowMatrix<E_TYPE>& ShadowMatrixA, SparseGlueMatrixForMultiplication<E_TYPE> GlueMatrixB);

    template<typename E_TYPE>
    friend SparseGlueMatrixForLinearCombination<E_TYPE> operator-(const SparseShadowMatrix<E_TYPE>& ShadowMatrixA, SparseGlueMatrixForMultiplication<E_TYPE> GlueMatrixB);

    template<typename E_TYPE>
    friend SparseGlueMatrixForMultiplication<E_TYPE> operator*(const SparseShadowMatrix<E_TYPE>& ShadowMatrixA, SparseGlueMatrixForMultiplication<E_TYPE> GlueMatrixB);

    template<typename E_TYPE>
    friend SparseMatrix<E_TYPE> operator/(const SparseShadowMatrix<E_TYPE>& ShadowMatrixA, const SparseGlueMatrixForMultiplication<E_TYPE>& GlueMatrixB);

    

    template<typename E_TYPE>
    friend SparseGlueMatrixForLinearCombination<E_TYPE> operator+(SparseGlueMatrixForMultiplication<E_TYPE> GlueMatrixA_M, SparseGlueMatrixForLinearCombination<E_TYPE> GlueMatrixB_L);

    template<typename E_TYPE>
    friend SparseGlueMatrixForLinearCombination<E_TYPE> operator-(SparseGlueMatrixForMultiplication<E_TYPE> GlueMatrixA_M, SparseGlueMatrixForLinearCombination<E_TYPE> GlueMatrixB_L);

    template<typename E_TYPE>
    friend SparseGlueMatrixForMultiplication<E_TYPE> operator*(SparseGlueMatrixForMultiplication<E_TYPE> GlueMatrixA_M, const SparseGlueMatrixForLinearCombination<E_TYPE>& GlueMatrixB_L);

    template<typename E_TYPE>
    friend SparseMatrix<E_TYPE> operator/(const SparseGlueMatrixForMultiplication<E_TYPE>& GlueMatrixA_M, const SparseGlueMatrixForLinearCombination<E_TYPE>& GlueMatrixB_L);

    

    template<typename E_TYPE>
    friend SparseGlueMatrixForLinearCombination<E_TYPE> operator+(SparseGlueMatrixForLinearCombination<E_TYPE> GlueMatrixA_L, SparseGlueMatrixForMultiplication<E_TYPE> GlueMatrixB_M);

    template<typename E_TYPE>
    friend SparseGlueMatrixForLinearCombination<E_TYPE> operator-(SparseGlueMatrixForLinearCombination<E_TYPE> GlueMatrixA_L, SparseGlueMatrixForMultiplication<E_TYPE> GlueMatrixB_M);

    template<typename E_TYPE>
    friend SparseGlueMatrixForMultiplication<E_TYPE> operator*(const SparseGlueMatrixForLinearCombination<E_TYPE>& GlueMatrixA_L, SparseGlueMatrixForMultiplication<E_TYPE> GlueMatrixB_M);

    template<typename E_TYPE>
    friend SparseMatrix<E_TYPE> operator/(const SparseGlueMatrixForLinearCombination<E_TYPE>& GlueMatrixA_L, const SparseGlueMatrixForMultiplication<E_TYPE>& GlueMatrixB_M);

    

    template<typename E_TYPE>
    friend SparseGlueMatrixForLinearCombination<E_TYPE> operator+(SparseGlueMatrixForMultiplication<E_TYPE> GlueMatrixA, SparseGlueMatrixForMultiplication<E_TYPE> GlueMatrixB);

    template<typename E_TYPE>
    friend SparseGlueMatrixForLinearCombination<E_TYPE> operator-(SparseGlueMatrixForMultiplication<E_TYPE> GlueMatrixA, SparseGlueMatrixForMultiplication<E_TYPE> GlueMatrixB);

    template<typename E_TYPE>
    friend SparseGlueMatrixForMultiplication<E_TYPE> operator*(SparseGlueMatrixForMultiplication<E_TYPE> GlueMatrixA, const SparseGlueMatrixForMultiplication<E_TYPE>& GlueMatrixB);

    template<typename E_TYPE>
    friend SparseMatrix<E_TYPE> operator/(const SparseGlueMatrixForMultiplication<E_TYPE>& GlueMatrixA, const SparseGlueMatrixForMultiplication<E_TYPE>& GlueMatrixB);

};


}

#include "mdkSparseGlueMatrixForMultiplication.hpp"

#endif
