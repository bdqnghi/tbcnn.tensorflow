#ifndef mdk_GlueMatrixForMultiplication_h
#define mdk_GlueMatrixForMultiplication_h

#include "mdkObject.h"
#include "mdkLinearAlgebraConfig.h"
//#include "mdkMatrix.h"


namespace mdk
{

//------------------------------ forward-declare -----------//

template<typename ElementType>
class mdkMatrix;

template<typename ElementType>
class mdkShadowMatrix;

template<typename ElementType>
class mdkGlueMatrixForLinearCombination;

struct mdkMatrixSize;
//--------------------------- end of forward-declare -------//

//---------------------------------------------------------------------------------------------------//
// 10 matrix should be OK
// reserve the capacity of std::vector<mdkMatrix<ElementType>>
#define MDK_GlueMatrixForMultiplication_ReservedCapacity  10
//--------------------------------------------------------------------------------------------------//

template<typename ElementType>
class mdkGlueMatrixForMultiplication : public mdkObject
{
private:

    int64 m_RowNumber;

    int64 m_ColNumber;

    std::vector<mdkMatrix<ElementType>> m_SourceMatrixSharedCopyList;

    ElementType m_Element_Coef;

    bool m_Is_m_Element_Coef_Equal_to_One;

    //------------------- constructor and destructor ------------------------------------//
private:
    inline mdkGlueMatrixForMultiplication();

public:
    inline ~mdkGlueMatrixForMultiplication();

private:
    inline mdkGlueMatrixForMultiplication(const mdkGlueMatrixForMultiplication<ElementType>& GlueMatrix) = delete;

public:
    inline mdkGlueMatrixForMultiplication(mdkGlueMatrixForMultiplication<ElementType>&& GlueMatrix);

    //---------------------- Other ----------------------------------------//
private:
    inline void Reset();

    inline int64 GetRowNumber() const;

    inline int64 GetColNumber() const;

    inline int64 GetElementNumber() const;

    inline mdkMatrixSize GetSize() const;

    inline int64 GetMatrixNumber() const;

    inline bool IsEmpty() const;

    inline mdkMatrix<ElementType> CreateMatrix() const;

    inline bool CreateMatrix(mdkMatrix<ElementType>& OutputMatrix) const;

public:

    inline mdkMatrix<ElementType> ElementMultiply(const mdkMatrix<ElementType>& targetMatrix);

    inline mdkMatrix<ElementType> ElementMultiply(const ElementType& Element);

    inline mdkMatrix<ElementType> ElementMultiply(const mdkShadowMatrix<ElementType>& ShadowMatrix);

    inline mdkMatrix<ElementType> ElementMultiply(const mdkLinearCombineGlueMatrix<ElementType>& GlueMatrix);

    inline mdkMatrix<ElementType> ElementMultiply(const mdkGlueMatrixForMultiplication<ElementType>& GlueMatrix);

private:
    //--------------------------- deleted ----------------------------------------//

    void operator=(const mdkGlueMatrixForMultiplication<ElementType>& GlueMatrix) = delete;
    void operator=(mdkGlueMatrixForMultiplication<ElementType>&& GlueMatrix) = delete;

    //--------------------------- friend class ----------------------------------------------------------------------------------//

    template<typename E_TYPE>
    friend class mdkMatrix;

    template<typename E_TYPE>
    friend class mdkShadowMatrix;

    //--------------------------- friend function ----------------------------------------------------------------------------------//

    // ----------------------------------------------------- Matrix  {*}  Matrix ---------------------------------------------------------//

    template<typename E_TYPE>
    friend mdkGlueMatrixForMultiplication<E_TYPE> operator*(const mdkMatrix<E_TYPE>& MatrixA, const mdkMatrix<E_TYPE>& MatrixB);

    // ---------------------------------------------------- Matrix  {* /}  Element ------------------------------------------------------//

    template<typename E_TYPE>
    friend mdkGlueMatrixForMultiplication<E_TYPE> operator*(const mdkMatrix<E_TYPE>& MatrixA, const E_TYPE& ElementB);

    template<typename E_TYPE>
    friend mdkGlueMatrixForMultiplication<E_TYPE> operator/(const mdkMatrix<E_TYPE>& MatrixA, const E_TYPE& ElementB);

    // --------------------------------------------------- Element {*} Matrix  ---------------------------------------------------------//

    template<typename E_TYPE>
    friend mdkGlueMatrixForMultiplication<E_TYPE> operator*(const E_TYPE& ElementA, const mdkMatrix<E_TYPE>& MatrixB);

    // ------------------------------------------ Matrix {*}  ShadowMatrix -----------------------------------------------------//

    template<typename E_TYPE>
    friend mdkGlueMatrixForMultiplication<E_TYPE> operator*(const mdkMatrix<E_TYPE>& MatrixA, const mdkShadowMatrix<E_TYPE>& ShadowMatrixB);

    // ------------------------------------------ ShadowMatrix {*}  Matrix ----------------------------------------------------------//

    template<typename E_TYPE>
    friend mdkGlueMatrixForMultiplication<E_TYPE> operator*(const mdkShadowMatrix<E_TYPE>& ShadowMatrixA, const mdkMatrix<E_TYPE>& MatrixB);

    // ---------------------------------------- ShadowMatrix {*}  ShadowMatrix -------------------------------------------------------//

    template<typename E_TYPE>
    friend mdkGlueMatrixForMultiplication<E_TYPE> operator*(const mdkShadowMatrix<E_TYPE>& ShadowMatrixA, const mdkShadowMatrix<E_TYPE>& ShadowMatrixB);

    // ---------------------------------------- Matrix or {*} GlueMatrixForLinearCombination -------------------------------------------------------//

    template<typename E_TYPE>
    friend mdkGlueMatrixForMultiplication<E_TYPE> operator*(const mdkMatrix<E_TYPE>& MatrixA, const mdkGlueMatrixForLinearCombination<E_TYPE>& GlueMatrixB);


    // --------------------------------------- GlueMatrixForLinearCombination {*}  Matrix ---------------------------------------------------------//

    template<typename E_TYPE>
    friend mdkGlueMatrixForMultiplication<E_TYPE> operator*(const mdkGlueMatrixForLinearCombination<E_TYPE>& GlueMatrixA, const mdkMatrix<E_TYPE>& MatrixB);


    // -------------------------------------- ShadowMatrix {*} GlueMatrixForLinearCombination -------------------------------------------------------//

    template<typename E_TYPE>
    friend mdkGlueMatrixForMultiplication<E_TYPE> operator*(const mdkShadowMatrix<E_TYPE>& ShadowMatrixA, const mdkGlueMatrixForLinearCombination<E_TYPE>& GlueMatrixB);

    // ------------------------------------- GlueMatrixForLinearCombination {*}  ShadowMatrix -----------------------------------------------------//

    template<typename E_TYPE>
    friend mdkGlueMatrixForMultiplication<E_TYPE> operator*(const mdkGlueMatrixForLinearCombination<E_TYPE>& GlueMatrixA, const mdkShadowMatrix<E_TYPE>& ShadowMatrixB);

    // ------------------------------------- GlueMatrixForLinearCombination {*}  GlueMatrixForLinearCombination ---------------------------------------//

    template<typename E_TYPE>
    friend mdkGlueMatrixForMultiplication<E_TYPE> operator*(const mdkGlueMatrixForLinearCombination<E_TYPE>& GlueMatrixA, const mdkGlueMatrixForLinearCombination<E_TYPE>& GlueMatrixB);

    // --------------------------------------------- GlueMatrixForMultiplication {+ - * /}  Matrix ---------------------------------------------------------//

    template<typename E_TYPE>
    friend mdkGlueMatrixForLinearCombination<E_TYPE> operator+(mdkGlueMatrixForMultiplication<E_TYPE> GlueMatrixA, const mdkMatrix<E_TYPE>& MatrixB);

    template<typename E_TYPE>
    friend mdkGlueMatrixForLinearCombination<E_TYPE> operator-(mdkGlueMatrixForMultiplication<E_TYPE> GlueMatrixA, const mdkMatrix<E_TYPE>& MatrixB);

    template<typename E_TYPE>
    friend mdkGlueMatrixForMultiplication<E_TYPE> operator*(mdkGlueMatrixForMultiplication<E_TYPE> GlueMatrixA, const mdkMatrix<E_TYPE>& MatrixB);

    template<typename E_TYPE>
    friend mdkMatrix<E_TYPE> operator/(const mdkGlueMatrixForMultiplication<E_TYPE>& GlueMatrixA, const mdkMatrix<E_TYPE>& MatrixB);

    // --------------------------------------------- Matrix or {+ - * /} GlueMatrixForMultiplication -------------------------------------------------------//

    template<typename E_TYPE>
    friend mdkGlueMatrixForLinearCombination<E_TYPE> operator+(const mdkMatrix<E_TYPE>& MatrixA, mdkGlueMatrixForMultiplication<E_TYPE> GlueMatrixB);

    template<typename E_TYPE>
    friend mdkGlueMatrixForLinearCombination<E_TYPE> operator-(const mdkMatrix<E_TYPE>& MatrixA, mdkGlueMatrixForMultiplication<E_TYPE> GlueMatrixB);

    template<typename E_TYPE>
    friend mdkGlueMatrixForMultiplication<E_TYPE> operator*(const mdkMatrix<E_TYPE>& MatrixA, mdkGlueMatrixForMultiplication<E_TYPE> GlueMatrixB);

    template<typename E_TYPE>
    friend mdkMatrix<E_TYPE> operator/(const mdkMatrix<E_TYPE>& MatrixA, const mdkGlueMatrixForMultiplication<E_TYPE> GlueMatrixB);

    // -------------------------------------------- GlueMatrixForMultiplication  {+ - * /}  Element ------------------------------------------------------//

    template<typename E_TYPE>
    friend mdkGlueMatrixForLinearCombination<E_TYPE> operator+(mdkGlueMatrixForMultiplication<E_TYPE> GlueMatrixA, const E_TYPE& ElementB);

    template<typename E_TYPE>
    friend mdkGlueMatrixForLinearCombination<E_TYPE> operator-(mdkGlueMatrixForMultiplication<E_TYPE> GlueMatrixA, const E_TYPE& ElementB);

    template<typename E_TYPE>
    friend mdkGlueMatrixForMultiplication<E_TYPE> operator*(mdkGlueMatrixForMultiplication<E_TYPE> GlueMatrixA, const E_TYPE& ElementB);

    template<typename E_TYPE>
    friend mdkGlueMatrixForMultiplication<E_TYPE> operator/(mdkGlueMatrixForMultiplication<E_TYPE> GlueMatrixA, const E_TYPE& ElementB);

    // ---------------------------------------------- Element {+ - * /} GlueMatrixForMultiplication -----------------------------------------------------//

    template<typename E_TYPE>
    friend mdkGlueMatrixForLinearCombination<E_TYPE> operator+(const E_TYPE& ElementA, mdkGlueMatrixForMultiplication<E_TYPE> GlueMatrixB);

    template<typename E_TYPE>
    friend mdkGlueMatrixForLinearCombination<E_TYPE> operator-(const E_TYPE& ElementA, mdkGlueMatrixForMultiplication<E_TYPE> GlueMatrixB);

    template<typename E_TYPE>
    friend mdkGlueMatrixForMultiplication<E_TYPE> operator*(const E_TYPE& ElementA, mdkGlueMatrixForMultiplication<E_TYPE> GlueMatrixB);

    template<typename E_TYPE>
    friend mdkMatrix<E_TYPE> operator/(const E_TYPE& ElementA, const mdkGlueMatrixForMultiplication<E_TYPE>& GlueMatrixB);

    // -------------------------------------------- GlueMatrixForMultiplication {+ - /}  ShadowMatrix -----------------------------------------------------//

    template<typename E_TYPE>
    friend mdkGlueMatrixForLinearCombination<E_TYPE> operator+(mdkGlueMatrixForMultiplication<E_TYPE> GlueMatrixA, const mdkShadowMatrix<E_TYPE>& ShadowMatrixB);

    template<typename E_TYPE>
    friend mdkGlueMatrixForLinearCombination<E_TYPE> operator-(mdkGlueMatrixForMultiplication<E_TYPE> GlueMatrixA, const mdkShadowMatrix<E_TYPE>& ShadowMatrixB);

    template<typename E_TYPE>
    friend mdkGlueMatrixForMultiplication<E_TYPE> operator*(mdkGlueMatrixForMultiplication<E_TYPE> GlueMatrixA, const mdkShadowMatrix<E_TYPE>& ShadowMatrixB);

    template<typename E_TYPE>
    friend mdkMatrix<E_TYPE> operator/(const mdkGlueMatrixForMultiplication<E_TYPE>& GlueMatrixA, const mdkShadowMatrix<E_TYPE>& ShadowMatrixB);

    // ------------------------------------------ ShadowMatrix {+ - * /} GlueMatrixForMultiplication -------------------------------------------------------//

    template<typename E_TYPE>
    friend mdkGlueMatrixForLinearCombination<E_TYPE> operator+(const mdkShadowMatrix<E_TYPE>& ShadowMatrixA, mdkGlueMatrixForMultiplication<E_TYPE> GlueMatrixB);

    template<typename E_TYPE>
    friend mdkGlueMatrixForLinearCombination<E_TYPE> operator-(const mdkShadowMatrix<E_TYPE>& ShadowMatrixA, mdkGlueMatrixForMultiplication<E_TYPE> GlueMatrixB);

    template<typename E_TYPE>
    friend mdkGlueMatrixForMultiplication<E_TYPE> operator*(const mdkShadowMatrix<E_TYPE>& ShadowMatrixA, mdkGlueMatrixForMultiplication<E_TYPE> GlueMatrixB);

    template<typename E_TYPE>
    friend mdkMatrix<E_TYPE> operator/(const mdkShadowMatrix<E_TYPE>& ShadowMatrixA, const mdkGlueMatrixForMultiplication<E_TYPE>& GlueMatrixB);

    // -------------------------------------------- GlueMatrixForMultiplication {+ - * /}  GlueMatrixForLinearCombination -----------------------------------------//

    template<typename E_TYPE>
    friend mdkGlueMatrixForLinearCombination<E_TYPE> operator+(mdkGlueMatrixForMultiplication<E_TYPE> GlueMatrixA_M, mdkGlueMatrixForLinearCombination<E_TYPE> GlueMatrixB_L);

    template<typename E_TYPE>
    friend mdkGlueMatrixForLinearCombination<E_TYPE> operator-(mdkGlueMatrixForMultiplication<E_TYPE> GlueMatrixA_M, mdkGlueMatrixForLinearCombination<E_TYPE> GlueMatrixB_L);

    template<typename E_TYPE>
    friend mdkGlueMatrixForMultiplication<E_TYPE> operator*(mdkGlueMatrixForMultiplication<E_TYPE> GlueMatrixA_M, const mdkGlueMatrixForLinearCombination<E_TYPE>& GlueMatrixB_L);

    template<typename E_TYPE>
    friend mdkMatrix<E_TYPE> operator/(const mdkGlueMatrixForMultiplication<E_TYPE>& GlueMatrixA_M, const mdkGlueMatrixForLinearCombination<E_TYPE>& GlueMatrixB_L);

    // ------------------------------------------ GlueMatrixForLinearCombination {+ - * /} GlueMatrixForMultiplication -------------------------------------------//

    template<typename E_TYPE>
    friend mdkGlueMatrixForLinearCombination<E_TYPE> operator+(mdkGlueMatrixForLinearCombination<E_TYPE> GlueMatrixA_L, mdkGlueMatrixForMultiplication<E_TYPE> GlueMatrixB_M);

    template<typename E_TYPE>
    friend mdkGlueMatrixForLinearCombination<E_TYPE> operator-(mdkGlueMatrixForLinearCombination<E_TYPE> GlueMatrixA_L, mdkGlueMatrixForMultiplication<E_TYPE> GlueMatrixB_M);

    template<typename E_TYPE>
    friend mdkGlueMatrixForMultiplication<E_TYPE> operator*(const mdkGlueMatrixForLinearCombination<E_TYPE>& GlueMatrixA_L, mdkGlueMatrixForMultiplication<E_TYPE> GlueMatrixB_M);

    template<typename E_TYPE>
    friend mdkMatrix<E_TYPE> operator/(const mdkGlueMatrixForLinearCombination<E_TYPE>& GlueMatrixA_L, const mdkGlueMatrixForMultiplication<E_TYPE>& GlueMatrixB_M);

    // --------------------------------------------- GlueMatrixForMultiplication {+ - * /}  GlueMatrixForMultiplication ---------------------------------------//

    template<typename E_TYPE>
    friend mdkGlueMatrixForLinearCombination<E_TYPE> operator+(mdkGlueMatrixForMultiplication<E_TYPE> GlueMatrixA, mdkGlueMatrixForMultiplication<E_TYPE> GlueMatrixB);

    template<typename E_TYPE>
    friend mdkGlueMatrixForLinearCombination<E_TYPE> operator-(mdkGlueMatrixForMultiplication<E_TYPE> GlueMatrixA, mdkGlueMatrixForMultiplication<E_TYPE> GlueMatrixB);

    template<typename E_TYPE>
    friend mdkGlueMatrixForMultiplication<E_TYPE> operator*(mdkGlueMatrixForMultiplication<E_TYPE> GlueMatrixA, const mdkGlueMatrixForMultiplication<E_TYPE>& GlueMatrixB);

    template<typename E_TYPE>
    friend mdkMatrix<E_TYPE> operator/(const mdkGlueMatrixForMultiplication<E_TYPE>& GlueMatrixA, const mdkGlueMatrixForMultiplication<E_TYPE>& GlueMatrixB);

};


}// end namespace mdk

#include "mdkGlueMatrixForMultiplication.hpp"

#endif
