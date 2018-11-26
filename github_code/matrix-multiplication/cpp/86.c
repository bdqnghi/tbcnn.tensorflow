#ifndef mdk_SparseVectorOperator_h
#define mdk_SparseVectorOperator_h

namespace mdk
{

//forward-declare -------------------------//

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

// end of forward-declare------------------//


//============================================================================================================================================//
//
//                                                    {SparseMatrix} v.s {SparseMatrix, Element}
//
//============================================================================================================================================//

// ----------------------------------------------------- SparseMatrix  {+ - *}  SparseMatrix ---------------------------------------------------------//

// note: SparseMatrix {+ -} SparseMatrix return SparseGlueMatrixForLinearCombination
// note: SparseMatrix {*}   SparseMatrix return SparseGlueMatrixForMultiplication
// note: SparseMatrix {/}   SparseMatrix is 0/0

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator+(const mdkSparseMatrix<ElementType>& MatrixA, const mdkSparseMatrix<ElementType>& MatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator-(const mdkSparseMatrix<ElementType>& MatrixA, const mdkSparseMatrix<ElementType>& MatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForMultiplication<ElementType> operator*(const mdkSparseMatrix<ElementType>& MatrixA, const mdkSparseMatrix<ElementType>& MatrixB);

// ---------------------------------------------------- SparseMatrix  {+ - * /}  Element ------------------------------------------------------//

// note: SparseMatrix {+ -}  Element return DenseMatrix
// note: SparseMatrix {* /}  Element return SparseGlueMatrixForMultiplication

template<typename ElementType>
inline mdkDenseMatrix<ElementType> operator+(const mdkSparseMatrix<ElementType>& MatrixA, const ElementType& ElementB);

template<typename ElementType>
inline mdkDenseMatrix<ElementType> operator-(const mdkSparseMatrix<ElementType>& MatrixA, const ElementType& ElementB);

template<typename ElementType>
inline mdkSparseGlueMatrixForMultiplication<ElementType> operator*(const mdkSparseMatrix<ElementType>& MatrixA, const ElementType& ElementB);

template<typename ElementType>
inline mdkSparseGlueMatrixForMultiplication<ElementType> operator/(const mdkSparseMatrix<ElementType>& MatrixA, const ElementType& ElementB);

// --------------------------------------------------- Element {+ - *} SparseMatrix  ---------------------------------------------------------//

// note: Element {+ -} SparseMatrix return DenseMatrix
// note: Element {*}   SparseMatrix return SparseGlueMatrixForMultiplication
// note: Element {/}   SparseMatrix is x/0

template<typename ElementType>
inline mdkDenseMatrix<ElementType> operator+(const ElementType& ElementA, const mdkSparseMatrix<ElementType>& MatrixB);

template<typename ElementType>
inline mdkDenseMatrix<ElementType> operator-(const ElementType& ElementA, const mdkSparseMatrix<ElementType>& MatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForMultiplication<ElementType> operator*(const ElementType& ElementA, const mdkSparseMatrix<ElementType>& MatrixB);

//============================================================================================================================================//
//
//                                          {SparseShadowMatrix} v.s {SparseMatrix, Element, SparseShadowMatrix}
//
//============================================================================================================================================//

// ------------------------------------------ SparseShadowMatrix {+ - *}  SparseMatrix ----------------------------------------------------------//

// note: SparseShadowMatrix {+ -} SparseMatrix return SparseMatrix
// note: SparseShadowMatrix {*}   SparseMatrix return SparseGlueMatrixForMultiplication
// note: ShadowMatrix       {/}   SparseMatrix is 0/0

template<typename ElementType>
inline mdkSparseMatrix<ElementType> operator+(const mdkSparseShadowMatrix<ElementType>& ShadowMatrixA, const mdkSparseMatrix<ElementType>& MatrixB);

template<typename ElementType>
inline mdkSparseMatrix<ElementType> operator-(const mdkSparseShadowMatrix<ElementType>& ShadowMatrixA, const mdkSparseMatrix<ElementType>& MatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForMultiplication<ElementType> operator*(const mdkSparseShadowMatrix<ElementType>& ShadowMatrixA, const mdkSparseMatrix<ElementType>& MatrixB);

// ---------------------------------------------- SparseMatrix {+ - *}  SparseShadowMatrix -----------------------------------------------------//

// note: SparseMatrix {+ -} SparseShadowMatrix return SparseMatrix
// note: SparseMatrix {*}   SparseShadowMatrix return SparseGlueMatrixForMultiplication
// note: SparseMatrix {/}   SparseShadowMatrix 0/0

template<typename ElementType>
inline mdkSparseMatrix<ElementType> operator+(const mdkSparseMatrix<ElementType>& MatrixA, const mdkSparseShadowMatrix<ElementType>& ShadowMatrixB);

template<typename ElementType>
inline mdkSparseMatrix<ElementType> operator-(const mdkSparseMatrix<ElementType>& MatrixA, const mdkSparseShadowMatrix<ElementType>& ShadowMatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForMultiplication<ElementType> operator*(const mdkSparseMatrix<ElementType>& MatrixA, const mdkSparseShadowMatrix<ElementType>& ShadowMatrixB);

template<typename ElementType>
inline mdkSparseMatrix<ElementType> operator/(const mdkSparseMatrix<ElementType>& MatrixA, const mdkSparseShadowMatrix<ElementType>& ShadowMatrixB);

// ------------------------------------------ SparseShadowMatrix {+ - * /}  Element ------------------------------------------------------------//

// note: SparseShadowMatrix {+ -} Element return DenseMatrix
// note: SparseShadowMatrix {* /} Element return SparseMatrix

template<typename ElementType>
inline mdkDenseMatrix<ElementType> operator+(const mdkSparseShadowMatrix<ElementType>& ShadowMatrixA, const ElementType& ElementB);

template<typename ElementType>
inline mdkDenseMatrix<ElementType> operator-(const mdkSparseShadowMatrix<ElementType>& ShadowMatrixA, const ElementType& ElementB);

template<typename ElementType>
inline mdkSparseMatrix<ElementType> operator*(const mdkSparseShadowMatrix<ElementType>& ShadowMatrixA, const ElementType& ElementB);

template<typename ElementType>
inline mdkSparseMatrix<ElementType> operator/(const mdkSparseShadowMatrix<ElementType>& ShadowMatrixA, const ElementType& ElementB);

// ----------------------------------------- Element {+ - * /} SparseShadowMatrix --------------------------------------------------------------//

// note: Element {+ -} SparseShadowMatrix return DenseMatrix
// note: Element {*} SparseShadowMatrix return SparseMatrix
// note: Element {/} SparseShadowMatrix is x/0

template<typename ElementType>
inline mdkDenseMatrix<ElementType> operator+(const ElementType& ElementA, const mdkSparseShadowMatrix<ElementType>& ShadowMatrixB);

template<typename ElementType>
inline mdkDenseMatrix<ElementType> operator-(const ElementType& ElementA, const mdkSparseShadowMatrix<ElementType>& ShadowMatrixB);

template<typename ElementType>
inline mdkSparseMatrix<ElementType> operator*(const ElementType& ElementA, const mdkSparseShadowMatrix<ElementType>& ShadowMatrixB);

// ---------------------------------------- SparseShadowMatrix {+ - *}  SparseShadowMatrix -------------------------------------------------------//

// note: SparseShadowMatrix {+ -} SparseShadowMatrix return SparseMatrix
// note: SparseShadowMatrix {*}   SparseShadowMatrix return SparseGlueMatrixForMultiplication
// note: SparseShadowMatrix {/}   SparseShadowMatrix is 0/0

template<typename ElementType>
inline mdkSparseMatrix<ElementType> operator+(const mdkSparseShadowMatrix<ElementType>& ShadowMatrixA, const mdkSparseShadowMatrix<ElementType>& ShadowMatrixB);

template<typename ElementType>
inline mdkSparseMatrix<ElementType> operator-(const mdkSparseShadowMatrix<ElementType>& ShadowMatrixA, const mdkSparseShadowMatrix<ElementType>& ShadowMatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForMultiplication<ElementType> operator*(const mdkSparseShadowMatrix<ElementType>& ShadowMatrixA, const mdkSparseShadowMatrix<ElementType>& ShadowMatrixB);

//============================================================================================================================================//
//
//                          {SparseGlueMatrixForLinearCombination} vs {SparseMatrix, Element, SparseShadowMatrix, SparseGlueMatrixForLinearCombination}
//
//============================================================================================================================================//

// --------------------------------------------- SparseGlueMatrixForLinearCombination {+ - *}  SparseMatrix ---------------------------------------------------------//

// note: SparseGlueMatrixForLinearCombination {+ -} SparseMatrix return SparseGlueMatrixForLinearCombination
// note: SparseGlueMatrixForLinearCombination {*}   SparseMatrix return SparseGlueMatrixForMultiplication
// note: SparseGlueMatrixForLinearCombination {/}   SparseMatrix is 0/0

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator+(mdkSparseGlueMatrixForLinearCombination<ElementType> GlueMatrixA, const mdkSparseMatrix<ElementType>& MatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator-(mdkSparseGlueMatrixForLinearCombination<ElementType> GlueMatrixA, const mdkSparseMatrix<ElementType>& MatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForMultiplication<ElementType> operator*(const mdkSparseGlueMatrixForLinearCombination<ElementType>& GlueMatrixA, const mdkSparseMatrix<ElementType>& MatrixB);

// --------------------------------------------- SparseMatrix or {+ - *} SparseGlueMatrixForLinearCombination -------------------------------------------------------//

// note: SparseMatrix {+ -} SparseGlueMatrixForLinearCombination return SparseGlueMatrixForLinearCombination
// note: SparseMatrix {*}   SparseGlueMatrixForLinearCombination return SparseGlueMatrixForMultiplication
// note: SparseMatrix {/}   SparseGlueMatrixForLinearCombination is 0/0

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator+(const mdkSparseMatrix<ElementType>& MatrixA, mdkSparseGlueMatrixForLinearCombination<ElementType> GlueMatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator-(const mdkSparseMatrix<ElementType>& MatrixA, mdkSparseGlueMatrixForLinearCombination<ElementType> GlueMatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForMultiplication<ElementType> operator*(const mdkSparseMatrix<ElementType>& MatrixA, const mdkSparseGlueMatrixForLinearCombination<ElementType>& GlueMatrixB);

// ------------------------------------------------- SparseGlueMatrixForLinearCombination  {+ - * /}  Element -----------------------------------------//

// note: SparseGlueMatrixForLinearCombination {+ - * /}  Element return SparseGlueMatrixForLinearCombination

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator+(mdkSparseGlueMatrixForLinearCombination<ElementType> GlueMatrixA, const ElementType& ElementB);

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator-(mdkSparseGlueMatrixForLinearCombination<ElementType> GlueMatrixA, const ElementType& ElementB);

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator*(mdkSparseGlueMatrixForLinearCombination<ElementType> GlueMatrixA, const ElementType& ElementB);

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator/(mdkSparseGlueMatrixForLinearCombination<ElementType> GlueMatrixA, const ElementType& ElementB);

// ----------------------------------------------- Element {+ - *} SparseGlueMatrixForLinearCombination ----------------------------------------------//

// note: Element {+ - *} SparseGlueMatrixForLinearCombination return SparseGlueMatrixForLinearCombination
// note: Element {/}     SparseGlueMatrixForLinearCombination is x/0

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator+(const ElementType& ElementA, mdkSparseGlueMatrixForLinearCombination<ElementType> GlueMatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator-(const ElementType& ElementA, mdkSparseGlueMatrixForLinearCombination<ElementType> GlueMatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator*(const ElementType& ElementA, mdkSparseGlueMatrixForLinearCombination<ElementType> GlueMatrixB);

// -------------------------------------------- SparseGlueMatrixForLinearCombination {+ - *}  SparseShadowMatrix -----------------------------------------------------//

// note: SparseGlueMatrixForLinearCombination {+ -} SparseShadowMatrix return SparseGlueMatrixForLinearCombination
// note: SparseGlueMatrixForLinearCombination {*}   SparseShadowMatrix return SparseGlueMatrixForMultiplication
// note: SparseGlueMatrixForLinearCombination {/}   SparseShadowMatrix is 0/0

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator+(mdkSparseGlueMatrixForLinearCombination<ElementType> GlueMatrixA, const mdkSparseShadowMatrix<ElementType>& ShadowMatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator-(mdkSparseGlueMatrixForLinearCombination<ElementType> GlueMatrixA, const mdkSparseShadowMatrix<ElementType>& ShadowMatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForMultiplication<ElementType> operator*(const mdkSparseGlueMatrixForLinearCombination<ElementType>& GlueMatrixA, const mdkSparseShadowMatrix<ElementType>& ShadowMatrixB);

// ------------------------------------------ SparseShadowMatrix {+ - *} SparseGlueMatrixForLinearCombination -------------------------------------------------------//

// note: SparseShadowMatrix {+ -} SparseGlueMatrixForLinearCombination return SparseGlueMatrixForLinearCombination
// note: SparseShadowMatrix {*}   SparseGlueMatrixForLinearCombination return SparseGlueMatrixForMultiplication
// note: SparseShadowMatrix {/}   SparseGlueMatrixForLinearCombination is 0/0

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator+(const mdkSparseShadowMatrix<ElementType>& ShadowMatrixA, mdkSparseGlueMatrixForLinearCombination<ElementType> GlueMatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator-(const mdkSparseShadowMatrix<ElementType>& ShadowMatrixA, mdkSparseGlueMatrixForLinearCombination<ElementType> GlueMatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForMultiplication<ElementType> operator*(const mdkSparseShadowMatrix<ElementType>& ShadowMatrixA, const mdkSparseGlueMatrixForLinearCombination<ElementType>& GlueMatrixB);

// --------------------------------------------- GlueMatrixForLinearCombination {+ - *}  GlueMatrixForLinearCombination ---------------------------------------//

// note: SparseGlueMatrixForLinearCombination {+ -} SparseGlueMatrixForLinearCombination return SparseGlueMatrixForLinearCombination
// note: SparseGlueMatrixForLinearCombination {*}   SparseGlueMatrixForLinearCombination return SparseGlueMatrixForMultiplication
// note: SparseGlueMatrixForLinearCombination {/}   SparseGlueMatrixForLinearCombination is 0/0

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator+(mdkSparseGlueMatrixForLinearCombination<ElementType> GlueMatrixA, mdkSparseGlueMatrixForLinearCombination<ElementType> GlueMatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator-(mdkSparseGlueMatrixForLinearCombination<ElementType> GlueMatrixA, mdkSparseGlueMatrixForLinearCombination<ElementType> GlueMatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForMultiplication<ElementType> operator*(const mdkSparseGlueMatrixForLinearCombination<ElementType>& GlueMatrixA, const mdkSparseGlueMatrixForLinearCombination<ElementType>& GlueMatrixB);

//====================================================================================================================================================//
//
//  {SparseGlueMatrixForMultiplication} vs {SparseMatrix, Element, SparseShadowMatrix, SparseGlueMatrixForLinearCombination, SparseGlueMatrixForMultiplication}
//
//====================================================================================================================================================//

// --------------------------------------------- SparseGlueMatrixForMultiplication {+ - *}  SparseMatrix ---------------------------------------------------------//

// note: SparseGlueMatrixForMultiplication {+ -} SparseMatrix return SparseGlueMatrixForLinearCombination
// note: SparseGlueMatrixForMultiplication {*}   SparseMatrix return SparseGlueMatrixForMultiplication
// note: SparseGlueMatrixForMultiplication {/}   SparseMatrix is 0/0

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator+(mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixA, const mdkSparseMatrix<ElementType>& MatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator-(mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixA, const mdkSparseMatrix<ElementType>& MatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForMultiplication<ElementType> operator*(mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixA, const mdkSparseMatrix<ElementType>& MatrixB);

// --------------------------------------------- SparseMatrix or {+ - *} SparseGlueMatrixForMultiplication -------------------------------------------------------//

// note: SparseMatrix {+ -} SparseGlueMatrixForMultiplication return SparseGlueMatrixForLinearCombination
// note: SparseMatrix {*}   SparseGlueMatrixForMultiplication return SparseGlueMatrixForMultiplication
// note: SparseMatrix {/}   SparseGlueMatrixForMultiplication is 0/0

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator+(const mdkSparseMatrix<ElementType>& MatrixA, mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator-(const mdkSparseMatrix<ElementType>& MatrixA, mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForMultiplication<ElementType> operator*(const mdkSparseMatrix<ElementType>& MatrixA, mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixB);

// -------------------------------------------- SparseGlueMatrixForMultiplication  {+ - * /}  Element ------------------------------------------------------//

// note: SparseGlueMatrixForMultiplication {+ -}  Element return SparseGlueMatrixForLinearCombination
// note: SparseGlueMatrixForMultiplication {* /}  Element return SparseGlueMatrixForMultiplication

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator+(mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixA, const ElementType& ElementB);

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator-(mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixA, const ElementType& ElementB);

template<typename ElementType>
inline mdkSparseGlueMatrixForMultiplication<ElementType> operator*(mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixA, const ElementType& ElementB);

template<typename ElementType>
inline mdkSparseGlueMatrixForMultiplication<ElementType> operator/(mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixA, const ElementType& ElementB);

// ---------------------------------------------- Element {+ - *} SparseGlueMatrixForMultiplication -----------------------------------------------------//

// note: Element {+ -} SparseGlueMatrixForMultiplication return SparseGlueMatrixForLinearCombination
// note: Element {*}   SparseGlueMatrixForMultiplication return SparseGlueMatrixForMultiplication
// note: Element {/}   SparseGlueMatrixForMultiplication is x/0

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator+(const ElementType& ElementA, mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator-(const ElementType& ElementA, mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForMultiplication<ElementType> operator*(const ElementType& ElementA, mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixB);

// -------------------------------------------- SparseGlueMatrixForMultiplication {+ - *}  SparseShadowMatrix -----------------------------------------------------//

// note: SparseGlueMatrixForMultiplication {+ -} SparseShadowMatrix return SparseGlueMatrixForLinearCombination
// note: SparseGlueMatrixForMultiplication {*}   SparseShadowMatrix return SparseGlueMatrixForMultiplication
// note: SparseGlueMatrixForMultiplication {/}   SparseShadowMatrix is 0/0

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator+(mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixA, const mdkSparseShadowMatrix<ElementType>& ShadowMatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator-(mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixA, const mdkSparseShadowMatrix<ElementType>& ShadowMatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForMultiplication<ElementType> operator*(mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixA, const mdkSparseShadowMatrix<ElementType>& ShadowMatrixB);

// ------------------------------------------ SparseShadowMatrix {+ - *} SparseGlueMatrixForMultiplication -------------------------------------------------------//

// note: SparseShadowMatrix {+ -} SparseGlueMatrixForMultiplication return SparseGlueMatrixForLinearCombination
// note: SparseShadowMatrix {*}   SparseGlueMatrixForMultiplication return SparseGlueMatrixForMultiplication
// note: SparseShadowMatrix {/}   SparseGlueMatrixForMultiplication is 0/0

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator+(const mdkSparseShadowMatrix<ElementType>& ShadowMatrixA, mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator-(const mdkSparseShadowMatrix<ElementType>& ShadowMatrixA, mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForMultiplication<ElementType> operator*(const mdkSparseShadowMatrix<ElementType>& ShadowMatrixA, mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixB);

// --------------------------------------- SparseGlueMatrixForMultiplication {+ - *}  SparseGlueMatrixForLinearCombination -----------------------------------------//

// note: SparseGlueMatrixForMultiplication {+ -} SparseGlueMatrixForLinearCombination return SparseGlueMatrixForLinearCombination
// note: SparseGlueMatrixForMultiplication {*}   SparseGlueMatrixForLinearCombination return SparseGlueMatrixForMultiplication
// note: SparseGlueMatrixForMultiplication {/}   SparseGlueMatrixForLinearCombination is 0/0

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator+(mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixA_M, mdkSparseGlueMatrixForLinearCombination<ElementType> GlueMatrixB_L);

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator-(mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixA_M, mdkSparseGlueMatrixForLinearCombination<ElementType> GlueMatrixB_L);

template<typename ElementType>
inline mdkSparseGlueMatrixForMultiplication<ElementType> operator*(mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixA_M, const mdkSparseGlueMatrixForLinearCombination<ElementType>& GlueMatrixB_L);

// ------------------------------------------ SparseGlueMatrixForLinearCombination {+ - *} SparseGlueMatrixForMultiplication -------------------------------------------//

// note: SparseGlueMatrixForLinearCombination {+ -} SparseGlueMatrixForMultiplication return SparseGlueMatrixForLinearCombination
// note: SparseGlueMatrixForLinearCombination {*}   SparseGlueMatrixForMultiplication return SparseGlueMatrixForMultiplication
// note: SparseGlueMatrixForLinearCombination {/}   SparseGlueMatrixForMultiplication is 0/0

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator+(mdkSparseGlueMatrixForLinearCombination<ElementType> GlueMatrixA_L, mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixB_M);

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator-(mdkSparseGlueMatrixForLinearCombination<ElementType> GlueMatrixA_L, mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixB_M);

template<typename ElementType>
inline mdkSparseGlueMatrixForMultiplication<ElementType> operator*(const mdkSparseGlueMatrixForLinearCombination<ElementType>& GlueMatrixA_L, mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixB_M);

// --------------------------------------------- SparseGlueMatrixForMultiplication {+ - *}  SparseGlueMatrixForMultiplication ---------------------------------------//

// note: SparseGlueMatrixForMultiplication {+ -} SparseGlueMatrixForMultiplication return SparseGlueMatrixForLinearCombination
// note: SparseGlueMatrixForMultiplication {*}   SparseGlueMatrixForMultiplication return SparseGlueMatrixForMultiplication
// note: SparseGlueMatrixForMultiplication {/}   SparseGlueMatrixForMultiplication is 0/0

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator+(mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixA, mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForLinearCombination<ElementType> operator-(mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixA, mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixB);

template<typename ElementType>
inline mdkSparseGlueMatrixForMultiplication<ElementType> operator*(mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixA, mdkSparseGlueMatrixForMultiplication<ElementType> GlueMatrixB);

} // namespace mdk

#include "mdkSparseMatrixOperator_SparseMatrix.hpp"
#include "mdkSparseMatrixOperator_SparseShadowMatrix.hpp"
#include "mdkSparseMatrixOperator_SparseGlueMatrixForLinearCombination.hpp"
#include "mdkSparseMatrixOperator_SparseGlueMatrixForMultiplication.hpp"

#endif 