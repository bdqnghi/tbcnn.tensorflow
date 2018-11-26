#pragma once

#include "mdkObject.h"
#include "mdkLinearAlgebraConfig.h"
//#include "mdkDenseMatrix.h"

namespace mdk
{

//------------------------------ forward-declare -----------//

template<typename ElementType>
class DenseMatrix;

template<typename ElementType>
class DenseShadowMatrix;

template<typename ElementType>
class DenseGlueMatrixForLinearCombination;

struct MatrixSize;
//--------------------------- end of forward-declare -------//

//---------------------------------------------------------------------------------------------------//
// 10 matrix should be OK
// reserve the capacity of std::vector<mdkDenseMatrix<ElementType>>
#define MDK_DenseGlueMatrixForMultiplication_ReservedCapacity  10
//--------------------------------------------------------------------------------------------------//

template<typename ElementType>
class DenseGlueMatrixForMultiplication : public Object
{
private:

    int_max m_RowCount;

    int_max m_ColCount;

    std::vector<DenseMatrix<ElementType>> m_SourceMatrixSharedCopyList;

    ElementType m_Element_Coef;

    bool m_Is_m_Element_Coef_Equal_to_One;

    //------------------- constructor and destructor ------------------------------------//
private:
    inline DenseGlueMatrixForMultiplication();

public:
    inline ~DenseGlueMatrixForMultiplication();

private:
    inline DenseGlueMatrixForMultiplication(const DenseGlueMatrixForMultiplication<ElementType>& DenseGlueMatrix) = delete;

public:
    inline DenseGlueMatrixForMultiplication(DenseGlueMatrixForMultiplication<ElementType>&& DenseGlueMatrix);

    //---------------------- Other ----------------------------------------//
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
    //--------------------------- deleted ----------------------------------------//

    void operator=(const DenseGlueMatrixForMultiplication<ElementType>& DenseGlueMatrix) = delete;
    void operator=(DenseGlueMatrixForMultiplication<ElementType>&& DenseGlueMatrix) = delete;

    //--------------------------- friend class ----------------------------------------------------------------------------------//

    template<typename E_TYPE>
    friend class DenseMatrix;

    template<typename E_TYPE>
    friend class DenseShadowMatrix;

    //--------------------------- friend function ----------------------------------------------------------------------------------//

    // ----------------------------------------------------- Matrix  {*}  Matrix ---------------------------------------------------------//

    template<typename E_TYPE>
    friend DenseGlueMatrixForMultiplication<E_TYPE> operator*(const DenseMatrix<E_TYPE>& MatrixA, const DenseMatrix<E_TYPE>& MatrixB);

    // ---------------------------------------------------- Matrix  {* /}  Element ------------------------------------------------------//

    template<typename E_TYPE>
    friend DenseGlueMatrixForMultiplication<E_TYPE> operator*(const DenseMatrix<E_TYPE>& MatrixA, const E_TYPE& ElementB);

    template<typename E_TYPE>
    friend DenseGlueMatrixForMultiplication<E_TYPE> operator/(const DenseMatrix<E_TYPE>& MatrixA, const E_TYPE& ElementB);

    // --------------------------------------------------- Element {*} Matrix  ---------------------------------------------------------//

    template<typename E_TYPE>
    friend DenseGlueMatrixForMultiplication<E_TYPE> operator*(const E_TYPE& ElementA, const DenseMatrix<E_TYPE>& MatrixB);

    // ------------------------------------------ Matrix {*}  ShadowMatrix -----------------------------------------------------//

    template<typename E_TYPE>
    friend DenseGlueMatrixForMultiplication<E_TYPE> operator*(const DenseMatrix<E_TYPE>& MatrixA, const DenseShadowMatrix<E_TYPE>& ShadowMatrixB);

    // ------------------------------------------ ShadowMatrix {*}  Matrix ----------------------------------------------------------//

    template<typename E_TYPE>
    friend DenseGlueMatrixForMultiplication<E_TYPE> operator*(const DenseShadowMatrix<E_TYPE>& ShadowMatrixA, const DenseMatrix<E_TYPE>& MatrixB);

    // ---------------------------------------- ShadowMatrix {*}  ShadowMatrix -------------------------------------------------------//

    template<typename E_TYPE>
    friend DenseGlueMatrixForMultiplication<E_TYPE> operator*(const DenseShadowMatrix<E_TYPE>& ShadowMatrixA, const DenseShadowMatrix<E_TYPE>& ShadowMatrixB);

    // ---------------------------------------- Matrix or {*} DenseGlueMatrixForLinearCombination -------------------------------------------------------//

    template<typename E_TYPE>
    friend DenseGlueMatrixForMultiplication<E_TYPE> operator*(const DenseMatrix<E_TYPE>& MatrixA, const DenseGlueMatrixForLinearCombination<E_TYPE>& GlueMatrixB);


    // --------------------------------------- DenseGlueMatrixForLinearCombination {*}  Matrix ---------------------------------------------------------//

    template<typename E_TYPE>
    friend DenseGlueMatrixForMultiplication<E_TYPE> operator*(const DenseGlueMatrixForLinearCombination<E_TYPE>& GlueMatrixA, const DenseMatrix<E_TYPE>& MatrixB);


    // -------------------------------------- ShadowMatrix {*} DenseGlueMatrixForLinearCombination -------------------------------------------------------//

    template<typename E_TYPE>
    friend DenseGlueMatrixForMultiplication<E_TYPE> operator*(const DenseShadowMatrix<E_TYPE>& ShadowMatrixA, const DenseGlueMatrixForLinearCombination<E_TYPE>& GlueMatrixB);

    // ------------------------------------- DenseGlueMatrixForLinearCombination {*}  ShadowMatrix -----------------------------------------------------//

    template<typename E_TYPE>
    friend DenseGlueMatrixForMultiplication<E_TYPE> operator*(const DenseGlueMatrixForLinearCombination<E_TYPE>& GlueMatrixA, const DenseShadowMatrix<E_TYPE>& ShadowMatrixB);

    // ------------------------------------- DenseGlueMatrixForLinearCombination {*}  DenseGlueMatrixForLinearCombination ---------------------------------------//

    template<typename E_TYPE>
    friend DenseGlueMatrixForMultiplication<E_TYPE> operator*(const DenseGlueMatrixForLinearCombination<E_TYPE>& GlueMatrixA, const DenseGlueMatrixForLinearCombination<E_TYPE>& GlueMatrixB);

    // --------------------------------------------- DenseGlueMatrixForMultiplication {+ - * /}  Matrix ---------------------------------------------------------//

    template<typename E_TYPE>
    friend DenseGlueMatrixForLinearCombination<E_TYPE> operator+(DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixA, const DenseMatrix<E_TYPE>& MatrixB);

    template<typename E_TYPE>
    friend DenseGlueMatrixForLinearCombination<E_TYPE> operator-(DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixA, const DenseMatrix<E_TYPE>& MatrixB);

    template<typename E_TYPE>
    friend DenseGlueMatrixForMultiplication<E_TYPE> operator*(DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixA, const DenseMatrix<E_TYPE>& MatrixB);

    template<typename E_TYPE>
    friend DenseMatrix<E_TYPE> operator/(const DenseGlueMatrixForMultiplication<E_TYPE>& GlueMatrixA, const DenseMatrix<E_TYPE>& MatrixB);

    // --------------------------------------------- Matrix or {+ - * /} DenseGlueMatrixForMultiplication -------------------------------------------------------//

    template<typename E_TYPE>
    friend DenseGlueMatrixForLinearCombination<E_TYPE> operator+(const DenseMatrix<E_TYPE>& MatrixA, DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixB);

    template<typename E_TYPE>
    friend DenseGlueMatrixForLinearCombination<E_TYPE> operator-(const DenseMatrix<E_TYPE>& MatrixA, DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixB);

    template<typename E_TYPE>
    friend DenseGlueMatrixForMultiplication<E_TYPE> operator*(const DenseMatrix<E_TYPE>& MatrixA, DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixB);

    template<typename E_TYPE>
    friend DenseMatrix<E_TYPE> operator/(const DenseMatrix<E_TYPE>& MatrixA, const DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixB);

    // -------------------------------------------- DenseGlueMatrixForMultiplication  {+ - * /}  Element ------------------------------------------------------//

    template<typename E_TYPE>
    friend DenseGlueMatrixForLinearCombination<E_TYPE> operator+(DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixA, const E_TYPE& ElementB);

    template<typename E_TYPE>
    friend DenseGlueMatrixForLinearCombination<E_TYPE> operator-(DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixA, const E_TYPE& ElementB);

    template<typename E_TYPE>
    friend DenseGlueMatrixForMultiplication<E_TYPE> operator*(DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixA, const E_TYPE& ElementB);

    template<typename E_TYPE>
    friend DenseGlueMatrixForMultiplication<E_TYPE> operator/(DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixA, const E_TYPE& ElementB);

    // ---------------------------------------------- Element {+ - * /} DenseGlueMatrixForMultiplication -----------------------------------------------------//

    template<typename E_TYPE>
    friend DenseGlueMatrixForLinearCombination<E_TYPE> operator+(const E_TYPE& ElementA, DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixB);

    template<typename E_TYPE>
    friend DenseGlueMatrixForLinearCombination<E_TYPE> operator-(const E_TYPE& ElementA, DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixB);

    template<typename E_TYPE>
    friend DenseGlueMatrixForMultiplication<E_TYPE> operator*(const E_TYPE& ElementA, DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixB);

    template<typename E_TYPE>
    friend DenseMatrix<E_TYPE> operator/(const E_TYPE& ElementA, const DenseGlueMatrixForMultiplication<E_TYPE>& GlueMatrixB);

    // -------------------------------------------- DenseGlueMatrixForMultiplication {+ - /}  ShadowMatrix -----------------------------------------------------//

    template<typename E_TYPE>
    friend DenseGlueMatrixForLinearCombination<E_TYPE> operator+(DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixA, const DenseShadowMatrix<E_TYPE>& ShadowMatrixB);

    template<typename E_TYPE>
    friend DenseGlueMatrixForLinearCombination<E_TYPE> operator-(DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixA, const DenseShadowMatrix<E_TYPE>& ShadowMatrixB);

    template<typename E_TYPE>
    friend DenseGlueMatrixForMultiplication<E_TYPE> operator*(DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixA, const DenseShadowMatrix<E_TYPE>& ShadowMatrixB);

    template<typename E_TYPE>
    friend DenseMatrix<E_TYPE> operator/(const DenseGlueMatrixForMultiplication<E_TYPE>& GlueMatrixA, const DenseShadowMatrix<E_TYPE>& ShadowMatrixB);

    // ------------------------------------------ ShadowMatrix {+ - * /} DenseGlueMatrixForMultiplication -------------------------------------------------------//

    template<typename E_TYPE>
    friend DenseGlueMatrixForLinearCombination<E_TYPE> operator+(const DenseShadowMatrix<E_TYPE>& ShadowMatrixA, DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixB);

    template<typename E_TYPE>
    friend DenseGlueMatrixForLinearCombination<E_TYPE> operator-(const DenseShadowMatrix<E_TYPE>& ShadowMatrixA, DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixB);

    template<typename E_TYPE>
    friend DenseGlueMatrixForMultiplication<E_TYPE> operator*(const DenseShadowMatrix<E_TYPE>& ShadowMatrixA, DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixB);

    template<typename E_TYPE>
    friend DenseMatrix<E_TYPE> operator/(const DenseShadowMatrix<E_TYPE>& ShadowMatrixA, const DenseGlueMatrixForMultiplication<E_TYPE>& GlueMatrixB);

    // -------------------------------------------- DenseGlueMatrixForMultiplication {+ - * /}  DenseGlueMatrixForLinearCombination -----------------------------------------//

    template<typename E_TYPE>
    friend DenseGlueMatrixForLinearCombination<E_TYPE> operator+(DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixA_M, DenseGlueMatrixForLinearCombination<E_TYPE> GlueMatrixB_L);

    template<typename E_TYPE>
    friend DenseGlueMatrixForLinearCombination<E_TYPE> operator-(DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixA_M, DenseGlueMatrixForLinearCombination<E_TYPE> GlueMatrixB_L);

    template<typename E_TYPE>
    friend DenseGlueMatrixForMultiplication<E_TYPE> operator*(DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixA_M, const DenseGlueMatrixForLinearCombination<E_TYPE>& GlueMatrixB_L);

    template<typename E_TYPE>
    friend DenseMatrix<E_TYPE> operator/(const DenseGlueMatrixForMultiplication<E_TYPE>& GlueMatrixA_M, const DenseGlueMatrixForLinearCombination<E_TYPE>& GlueMatrixB_L);

    // ------------------------------------------ DenseGlueMatrixForLinearCombination {+ - * /} DenseGlueMatrixForMultiplication -------------------------------------------//

    template<typename E_TYPE>
    friend DenseGlueMatrixForLinearCombination<E_TYPE> operator+(DenseGlueMatrixForLinearCombination<E_TYPE> GlueMatrixA_L, DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixB_M);

    template<typename E_TYPE>
    friend DenseGlueMatrixForLinearCombination<E_TYPE> operator-(DenseGlueMatrixForLinearCombination<E_TYPE> GlueMatrixA_L, DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixB_M);

    template<typename E_TYPE>
    friend DenseGlueMatrixForMultiplication<E_TYPE> operator*(const DenseGlueMatrixForLinearCombination<E_TYPE>& GlueMatrixA_L, DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixB_M);

    template<typename E_TYPE>
    friend DenseMatrix<E_TYPE> operator/(const DenseGlueMatrixForLinearCombination<E_TYPE>& GlueMatrixA_L, const DenseGlueMatrixForMultiplication<E_TYPE>& GlueMatrixB_M);

    // --------------------------------------------- DenseGlueMatrixForMultiplication {+ - * /}  DenseGlueMatrixForMultiplication ---------------------------------------//

    template<typename E_TYPE>
    friend DenseGlueMatrixForLinearCombination<E_TYPE> operator+(DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixA, DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixB);

    template<typename E_TYPE>
    friend DenseGlueMatrixForLinearCombination<E_TYPE> operator-(DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixA, DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixB);

    template<typename E_TYPE>
    friend DenseGlueMatrixForMultiplication<E_TYPE> operator*(DenseGlueMatrixForMultiplication<E_TYPE> GlueMatrixA, const DenseGlueMatrixForMultiplication<E_TYPE>& GlueMatrixB);

    template<typename E_TYPE>
    friend DenseMatrix<E_TYPE> operator/(const DenseGlueMatrixForMultiplication<E_TYPE>& GlueMatrixA, const DenseGlueMatrixForMultiplication<E_TYPE>& GlueMatrixB);

};


}// end namespace mdk

#include "mdkDenseGlueMatrixForMultiplication.hpp"
