#pragma once

namespace mdk
{

//forward-declare -------------------------//

template<typename ElementType>
class DenseMatrix;

struct mdkMatrixSize;

template<typename ElementType>
class DenseShadowMatrix;

template<typename ElementType>
class DenseGlueMatrixForLinearCombination;

template<typename ElementType>
class DenseGlueMatrixForMultiplication;

// end of forward-declare------------------//


//============================================================================================================================================//
//
//                                                    {Matrix} v.s {Matrix, Element}
//
//============================================================================================================================================//

// ----------------------------------------------------- Matrix  {+ - * /}  Matrix ---------------------------------------------------------//

// note: Matrix {+ -} Matrix return GlueMatrixForLinearCombination
// note: Matrix {*}   Matrix return MultiplyGlueMatrix
// note: Matrix {/}   Matrix return Matrix

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator+(const DenseMatrix<ElementType>& MatrixA, const DenseMatrix<ElementType>& MatrixB);

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator-(const DenseMatrix<ElementType>& MatrixA, const DenseMatrix<ElementType>& MatrixB);

template<typename ElementType>
inline DenseGlueMatrixForMultiplication<ElementType> operator*(const DenseMatrix<ElementType>& MatrixA, const DenseMatrix<ElementType>& MatrixB);

template<typename ElementType>
inline DenseMatrix<ElementType> operator/(const DenseMatrix<ElementType>& MatrixA, const DenseMatrix<ElementType>& MatrixB);

// ---------------------------------------------------- Matrix  {+ - * /}  Element ------------------------------------------------------//

// note: Matrix {+ -}  Element return GlueMatrixForLinearCombination
// note: Matrix {* /}  Element return GlueMatrixForMultiplication

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator+(const DenseMatrix<ElementType>& MatrixA, const ElementType& ElementB);

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator-(const DenseMatrix<ElementType>& MatrixA, const ElementType& ElementB);

template<typename ElementType>
inline DenseGlueMatrixForMultiplication<ElementType> operator*(const DenseMatrix<ElementType>& MatrixA, const ElementType& ElementB);

template<typename ElementType>
inline DenseGlueMatrixForMultiplication<ElementType> operator/(const DenseMatrix<ElementType>& MatrixA, const ElementType& ElementB);

// --------------------------------------------------- Element {+ - * /} Matrix  ---------------------------------------------------------//

// note: Element {+ -} Matrix return GlueMatrixForLinearCombination
// note: Element {*}   Matrix return GlueMatrixForMultiplication
// note: Element {/}   Matrix return Matrix

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator+(const ElementType& ElementA, const DenseMatrix<ElementType>& MatrixB);

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator-(const ElementType& ElementA, const DenseMatrix<ElementType>& MatrixB);

template<typename ElementType>
inline DenseGlueMatrixForMultiplication<ElementType> operator*(const ElementType& ElementA, const DenseMatrix<ElementType>& MatrixB);

template<typename ElementType>
inline DenseMatrix<ElementType> operator/(const ElementType& ElementA, const DenseMatrix<ElementType>& MatrixB);
//============================================================================================================================================//
//
//                                          {ShadowMatrix} v.s {Matrix, Element, ShadowMatrix}
//
//============================================================================================================================================//

// ------------------------------------------ ShadowMatrix {+ - * /}  Matrix ----------------------------------------------------------//

// note: ShadowMatrix {+ -} Matrix return Matrix
// note: ShadowMatrix {*}   Matrix return GlueMatrixForMultiplication
// note: ShadowMatrix {/}   Matrix return Matrix

template<typename ElementType>
inline DenseMatrix<ElementType> operator+(const DenseShadowMatrix<ElementType>& ShadowMatrixA, const DenseMatrix<ElementType>& MatrixB);

template<typename ElementType>
inline DenseMatrix<ElementType> operator-(const DenseShadowMatrix<ElementType>& ShadowMatrixA, const DenseMatrix<ElementType>& MatrixB);

template<typename ElementType>
inline DenseGlueMatrixForMultiplication<ElementType> operator*(const DenseShadowMatrix<ElementType>& ShadowMatrixA, const DenseMatrix<ElementType>& MatrixB);

template<typename ElementType>
inline DenseMatrix<ElementType> operator/(const DenseShadowMatrix<ElementType>& ShadowMatrixA, const DenseMatrix<ElementType>& MatrixB);

// ---------------------------------------------- Matrix {+ - * /}  ShadowMatrix -----------------------------------------------------//

// note: Matrix {+ -} ShadowMatrix return Matrix
// note: Matrix {*}   ShadowMatrix return GlueMatrixForMultiplication
// note: Matrix {/}   ShadowMatrix return Matrix

template<typename ElementType>
inline DenseMatrix<ElementType> operator+(const DenseMatrix<ElementType>& MatrixA, const DenseShadowMatrix<ElementType>& ShadowMatrixB);

template<typename ElementType>
inline DenseMatrix<ElementType> operator-(const DenseMatrix<ElementType>& MatrixA, const DenseShadowMatrix<ElementType>& ShadowMatrixB);

template<typename ElementType>
inline DenseGlueMatrixForMultiplication<ElementType> operator*(const DenseMatrix<ElementType>& MatrixA, const DenseShadowMatrix<ElementType>& ShadowMatrixB);

template<typename ElementType>
inline DenseMatrix<ElementType> operator/(const DenseMatrix<ElementType>& MatrixA, const DenseShadowMatrix<ElementType>& ShadowMatrixB);

// ------------------------------------------ ShadowMatrix {+ - * /}  Element ------------------------------------------------------------//

// note: ShadowMatrix {+ - * /} Element return Matrix

template<typename ElementType>
inline DenseMatrix<ElementType> operator+(const DenseShadowMatrix<ElementType>& ShadowMatrixA, const ElementType& ElementB);

template<typename ElementType>
inline DenseMatrix<ElementType> operator-(const DenseShadowMatrix<ElementType>& ShadowMatrixA, const ElementType& ElementB);

template<typename ElementType>
inline DenseMatrix<ElementType> operator*(const DenseShadowMatrix<ElementType>& ShadowMatrixA, const ElementType& ElementB);

template<typename ElementType>
inline DenseMatrix<ElementType> operator/(const DenseShadowMatrix<ElementType>& ShadowMatrixA, const ElementType& ElementB);

// ----------------------------------------- Element {+ - * /} ShadowMatrix --------------------------------------------------------------//

// note: Element {+ - * /} ShadowMatrix return Matrix

template<typename ElementType>
inline DenseMatrix<ElementType> operator+(const ElementType& ElementA, const DenseShadowMatrix<ElementType>& ShadowMatrixB);

template<typename ElementType>
inline DenseMatrix<ElementType> operator-(const ElementType& ElementA, const DenseShadowMatrix<ElementType>& ShadowMatrixB);

template<typename ElementType>
inline DenseMatrix<ElementType> operator*(const ElementType& ElementA, const DenseShadowMatrix<ElementType>& ShadowMatrixB);

template<typename ElementType>
inline DenseMatrix<ElementType> operator/(const ElementType& ElementA, const DenseShadowMatrix<ElementType>& ShadowMatrixB);

// ---------------------------------------- ShadowMatrix {+ - * /}  ShadowMatrix -------------------------------------------------------//

// note: Matrix {+ -} Matrix return Matrix
// note: Matrix {*}   Matrix return GlueMatrixForMultiplication
// note: Matrix {/}   Matrix return Matrix

template<typename ElementType>
inline DenseMatrix<ElementType> operator+(const DenseShadowMatrix<ElementType>& ShadowMatrixA, const DenseShadowMatrix<ElementType>& ShadowMatrixB);

template<typename ElementType>
inline DenseMatrix<ElementType> operator-(const DenseShadowMatrix<ElementType>& ShadowMatrixA, const DenseShadowMatrix<ElementType>& ShadowMatrixB);

template<typename ElementType>
inline DenseGlueMatrixForMultiplication<ElementType> operator*(const DenseShadowMatrix<ElementType>& ShadowMatrixA, const DenseShadowMatrix<ElementType>& ShadowMatrixB);

template<typename ElementType>
inline DenseMatrix<ElementType> operator/(const DenseShadowMatrix<ElementType>& ShadowMatrixA, const DenseShadowMatrix<ElementType>& ShadowMatrixB);

//============================================================================================================================================//
//
//                          {GlueMatrixForLinearCombination} vs {Matrix, Element, ShadowMatrix, GlueMatrixForLinearCombination}
//
//============================================================================================================================================//

// --------------------------------------------- GlueMatrixForLinearCombination {+ - * /}  Matrix ---------------------------------------------------------//

// note: GlueMatrixForLinearCombination {+ -} Matrix return GlueMatrixForLinearCombination
// note: GlueMatrixForLinearCombination {*}   Matrix return GlueMatrixForMultiplication
// note: GlueMatrixForLinearCombination {/}   Matrix return Matrix

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator+(DenseGlueMatrixForLinearCombination<ElementType> GlueMatrixA, const DenseMatrix<ElementType>& MatrixB);

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator-(DenseGlueMatrixForLinearCombination<ElementType> GlueMatrixA, const DenseMatrix<ElementType>& MatrixB);

template<typename ElementType>
inline DenseGlueMatrixForMultiplication<ElementType> operator*(const DenseGlueMatrixForLinearCombination<ElementType>& GlueMatrixA, const DenseMatrix<ElementType>& MatrixB);

template<typename ElementType>
inline DenseMatrix<ElementType> operator/(const DenseGlueMatrixForLinearCombination<ElementType>& GlueMatrixA, const DenseMatrix<ElementType>& MatrixB);

// --------------------------------------------- Matrix or {+ - * /} GlueMatrixForLinearCombination -------------------------------------------------------//

// note: Matrix {+ -} GlueMatrixForLinearCombination return GlueMatrixForLinearCombination
// note: Matrix {*}   GlueMatrixForLinearCombination return GlueMatrixForMultiplication (definition in mdkDenseGlueMatrixForMultiplication.h)
// note: Matrix {/}   GlueMatrixForLinearCombination return Matrix

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator+(const DenseMatrix<ElementType>& MatrixA, DenseGlueMatrixForLinearCombination<ElementType> GlueMatrixB);

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator-(const DenseMatrix<ElementType>& MatrixA, DenseGlueMatrixForLinearCombination<ElementType> GlueMatrixB);

template<typename ElementType>
inline DenseGlueMatrixForMultiplication<ElementType> operator*(const DenseMatrix<ElementType>& MatrixA, const DenseGlueMatrixForLinearCombination<ElementType>& GlueMatrixB);

template<typename ElementType>
inline DenseMatrix<ElementType> operator/(const DenseMatrix<ElementType>& MatrixA, const DenseGlueMatrixForLinearCombination<ElementType>& GlueMatrixB);

// ------------------------------------------------- GlueMatrixForLinearCombination  {+ - * /}  Element -----------------------------------------//

// note: GlueMatrixForLinearCombination {+ - * /}  Element return GlueMatrixForLinearCombination

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator+(DenseGlueMatrixForLinearCombination<ElementType> GlueMatrixA, const ElementType& ElementB);

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator-(DenseGlueMatrixForLinearCombination<ElementType> GlueMatrixA, const ElementType& ElementB);

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator*(DenseGlueMatrixForLinearCombination<ElementType> GlueMatrixA, const ElementType& ElementB);

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator/(DenseGlueMatrixForLinearCombination<ElementType> GlueMatrixA, const ElementType& ElementB);

// ----------------------------------------------- Element {+ - * /} GlueMatrixForLinearCombination ----------------------------------------------//

// note: Element {+ - *} GlueMatrixForLinearCombination return GlueMatrixForLinearCombination
// note: Element {/}     GlueMatrixForLinearCombination return Matrix

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator+(const ElementType& ElementA, DenseGlueMatrixForLinearCombination<ElementType> GlueMatrixB);

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator-(const ElementType& ElementA, DenseGlueMatrixForLinearCombination<ElementType> GlueMatrixB);

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator*(const ElementType& ElementA, DenseGlueMatrixForLinearCombination<ElementType> GlueMatrixB);

template<typename ElementType>
inline DenseMatrix<ElementType> operator/(const ElementType& ElementA, const DenseGlueMatrixForLinearCombination<ElementType>& GlueMatrixB);

// -------------------------------------------- GlueMatrixForLinearCombination {+ - * /}  ShadowMatrix -----------------------------------------------------//

// note: GlueMatrixForLinearCombination {+ -} ShadowMatrix return GlueMatrixForLinearCombination
// note: GlueMatrixForLinearCombination {*}   ShadowMatrix return GlueMatrixForMultiplication
// note: GlueMatrixForLinearCombination {/}   ShadowMatrix return Matrix

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator+(DenseGlueMatrixForLinearCombination<ElementType> GlueMatrixA, const DenseShadowMatrix<ElementType>& ShadowMatrixB);

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator-(DenseGlueMatrixForLinearCombination<ElementType> GlueMatrixA, const DenseShadowMatrix<ElementType>& ShadowMatrixB);

template<typename ElementType>
inline DenseGlueMatrixForMultiplication<ElementType> operator*(const DenseGlueMatrixForLinearCombination<ElementType>& GlueMatrixA, const DenseShadowMatrix<ElementType>& ShadowMatrixB);

template<typename ElementType>
inline DenseMatrix<ElementType> operator/(const DenseGlueMatrixForLinearCombination<ElementType>& GlueMatrixA, const DenseShadowMatrix<ElementType>& ShadowMatrixB);

// ------------------------------------------ ShadowMatrix {+ - * /} GlueMatrixForLinearCombination -------------------------------------------------------//

// note: ShadowMatrix {+ -} GlueMatrixForLinearCombination return GlueMatrixForLinearCombination
// note: ShadowMatrix {*}   GlueMatrixForLinearCombination return GlueMatrixForMultiplication
// note: ShadowMatrix {/}   GlueMatrixForLinearCombination return Matrix

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator+(const DenseShadowMatrix<ElementType>& ShadowMatrixA, DenseGlueMatrixForLinearCombination<ElementType> GlueMatrixB);

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator-(const DenseShadowMatrix<ElementType>& ShadowMatrixA, DenseGlueMatrixForLinearCombination<ElementType> GlueMatrixB);

template<typename ElementType>
inline DenseGlueMatrixForMultiplication<ElementType> operator*(const DenseShadowMatrix<ElementType>& ShadowMatrixA, const DenseGlueMatrixForLinearCombination<ElementType>& GlueMatrixB);

template<typename ElementType>
inline DenseMatrix<ElementType> operator/(const DenseShadowMatrix<ElementType>& ShadowMatrixA, const DenseGlueMatrixForLinearCombination<ElementType>& GlueMatrixB);

// --------------------------------------------- GlueMatrixForLinearCombination {+ - * /}  GlueMatrixForLinearCombination ---------------------------------------//

// note: GlueMatrixForLinearCombination {+ -} GlueMatrixForLinearCombination return GlueMatrixForLinearCombination
// note: GlueMatrixForLinearCombination {*}   GlueMatrixForLinearCombination return GlueMatrixForMultiplication
// note: GlueMatrixForLinearCombination {/}   GlueMatrixForLinearCombination return Matrix

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator+(DenseGlueMatrixForLinearCombination<ElementType> GlueMatrixA, DenseGlueMatrixForLinearCombination<ElementType> GlueMatrixB);

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator-(DenseGlueMatrixForLinearCombination<ElementType> GlueMatrixA, DenseGlueMatrixForLinearCombination<ElementType> GlueMatrixB);

template<typename ElementType>
inline DenseGlueMatrixForMultiplication<ElementType> operator*(const DenseGlueMatrixForLinearCombination<ElementType>& GlueMatrixA, const DenseGlueMatrixForLinearCombination<ElementType>& GlueMatrixB);

template<typename ElementType>
inline DenseMatrix<ElementType> operator/(const DenseGlueMatrixForLinearCombination<ElementType>& GlueMatrixA, const DenseGlueMatrixForLinearCombination<ElementType>& GlueMatrixB);

//====================================================================================================================================================//
//
//          {GlueMatrixForMultiplication} vs {Matrix, Element, ShadowMatrix, GlueMatrixForLinearCombination, GlueMatrixForMultiplication}
//
//====================================================================================================================================================//

// --------------------------------------------- GlueMatrixForMultiplication {+ - * /}  Matrix ---------------------------------------------------------//

// note: GlueMatrixForMultiplication {+ -} Matrix return GlueMatrixForLinearCombination
// note: GlueMatrixForMultiplication {*}   Matrix return GlueMatrixForMultiplication
// note: GlueMatrixForMultiplication {/}   Matrix return Matrix

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator+(DenseGlueMatrixForMultiplication<ElementType> GlueMatrixA, const DenseMatrix<ElementType>& MatrixB);

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator-(DenseGlueMatrixForMultiplication<ElementType> GlueMatrixA, const DenseMatrix<ElementType>& MatrixB);

template<typename ElementType>
inline DenseGlueMatrixForMultiplication<ElementType> operator*(DenseGlueMatrixForMultiplication<ElementType> GlueMatrixA, const DenseMatrix<ElementType>& MatrixB);

template<typename ElementType>
inline DenseMatrix<ElementType> operator/(const DenseGlueMatrixForMultiplication<ElementType>& GlueMatrixA, const DenseMatrix<ElementType>& MatrixB);

// --------------------------------------------- Matrix or {+ - * /} GlueMatrixForMultiplication -------------------------------------------------------//

// note: Matrix {+ -} GlueMatrixForMultiplication return GlueMatrixForLinearCombination
// note: Matrix {*}   GlueMatrixForMultiplication return GlueMatrixForMultiplication
// note: Matrix {/}   GlueMatrixForMultiplication return Matrix

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator+(const DenseMatrix<ElementType>& MatrixA, DenseGlueMatrixForMultiplication<ElementType> GlueMatrixB);

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator-(const DenseMatrix<ElementType>& MatrixA, DenseGlueMatrixForMultiplication<ElementType> GlueMatrixB);

template<typename ElementType>
inline DenseGlueMatrixForMultiplication<ElementType> operator*(const DenseMatrix<ElementType>& MatrixA, DenseGlueMatrixForMultiplication<ElementType> GlueMatrixB);

template<typename ElementType>
inline DenseMatrix<ElementType> operator/(const DenseMatrix<ElementType>& MatrixA, const DenseGlueMatrixForMultiplication<ElementType> GlueMatrixB);

// -------------------------------------------- GlueMatrixForMultiplication  {+ - * /}  Element ------------------------------------------------------//

// note: GlueMatrixForMultiplication {+ -}  Element return GlueMatrixForLinearCombination
// note: GlueMatrixForMultiplication {* /}  Element return GlueMatrixForMultiplication

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator+(DenseGlueMatrixForMultiplication<ElementType> GlueMatrixA, const ElementType& ElementB);

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator-(DenseGlueMatrixForMultiplication<ElementType> GlueMatrixA, const ElementType& ElementB);

template<typename ElementType>
inline DenseGlueMatrixForMultiplication<ElementType> operator*(DenseGlueMatrixForMultiplication<ElementType> GlueMatrixA, const ElementType& ElementB);

template<typename ElementType>
inline DenseGlueMatrixForMultiplication<ElementType> operator/(DenseGlueMatrixForMultiplication<ElementType> GlueMatrixA, const ElementType& ElementB);

// ---------------------------------------------- Element {+ - * /} GlueMatrixForMultiplication -----------------------------------------------------//

// note: Element {+ -} GlueMatrixForMultiplication return GlueMatrixForLinearCombination
// note: Element {*}   GlueMatrixForMultiplication return GlueMatrixForMultiplication
// note: Element {/}   GlueMatrixForMultiplication return Matrix

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator+(const ElementType& ElementA, DenseGlueMatrixForMultiplication<ElementType> GlueMatrixB);

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator-(const ElementType& ElementA, DenseGlueMatrixForMultiplication<ElementType> GlueMatrixB);

template<typename ElementType>
inline DenseGlueMatrixForMultiplication<ElementType> operator*(const ElementType& ElementA, DenseGlueMatrixForMultiplication<ElementType> GlueMatrixB);

template<typename ElementType>
inline DenseMatrix<ElementType> operator/(const ElementType& ElementA, const DenseGlueMatrixForMultiplication<ElementType>& GlueMatrixB);

// -------------------------------------------- GlueMatrixForMultiplication {+ - * /}  ShadowMatrix -----------------------------------------------------//

// note: GlueMatrixForMultiplication {+ -} ShadowMatrix return GlueMatrixForLinearCombination
// note: GlueMatrixForMultiplication {*}   ShadowMatrix return GlueMatrixForMultiplication
// note: GlueMatrixForMultiplication {/}   ShadowMatrix return Matrix

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator+(DenseGlueMatrixForMultiplication<ElementType> GlueMatrixA, const DenseShadowMatrix<ElementType>& ShadowMatrixB);

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator-(DenseGlueMatrixForMultiplication<ElementType> GlueMatrixA, const DenseShadowMatrix<ElementType>& ShadowMatrixB);

template<typename ElementType>
inline DenseGlueMatrixForMultiplication<ElementType> operator*(DenseGlueMatrixForMultiplication<ElementType> GlueMatrixA, const DenseShadowMatrix<ElementType>& ShadowMatrixB);

template<typename ElementType>
inline DenseMatrix<ElementType> operator/(const DenseGlueMatrixForMultiplication<ElementType>& GlueMatrixA, const DenseShadowMatrix<ElementType>& ShadowMatrixB);

// ------------------------------------------ ShadowMatrix {+ - * /} GlueMatrixForMultiplication -------------------------------------------------------//

// note: ShadowMatrix {+ -} GlueMatrixForMultiplication return GlueMatrixForLinearCombination
// note: ShadowMatrix {*}   GlueMatrixForMultiplication return GlueMatrixForMultiplication
// note: ShadowMatrix {/}   GlueMatrixForMultiplication return Matrix

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator+(const DenseShadowMatrix<ElementType>& ShadowMatrixA, DenseGlueMatrixForMultiplication<ElementType> GlueMatrixB);

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator-(const DenseShadowMatrix<ElementType>& ShadowMatrixA, DenseGlueMatrixForMultiplication<ElementType> GlueMatrixB);

template<typename ElementType>
inline DenseGlueMatrixForMultiplication<ElementType> operator*(const DenseShadowMatrix<ElementType>& ShadowMatrixA, DenseGlueMatrixForMultiplication<ElementType> GlueMatrixB);

template<typename ElementType>
inline DenseMatrix<ElementType> operator/(const DenseShadowMatrix<ElementType>& ShadowMatrixA, const DenseGlueMatrixForMultiplication<ElementType>& GlueMatrixB);

// -------------------------------------------- GlueMatrixForMultiplication {+ - /}  GlueMatrixForLinearCombination -----------------------------------------//

// note: GlueMatrixForMultiplication {+ -} GlueMatrixForLinearCombination return GlueMatrixForLinearCombination
// note: GlueMatrixForMultiplication {*}   GlueMatrixForLinearCombination return GlueMatrixForMultiplication
// note: GlueMatrixForMultiplication {/}   GlueMatrixForLinearCombination return Matrix

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator+(DenseGlueMatrixForMultiplication<ElementType> GlueMatrixA_M, DenseGlueMatrixForLinearCombination<ElementType> GlueMatrixB_L);

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator-(DenseGlueMatrixForMultiplication<ElementType> GlueMatrixA_M, DenseGlueMatrixForLinearCombination<ElementType> GlueMatrixB_L);

template<typename ElementType>
inline DenseGlueMatrixForMultiplication<ElementType> operator*(DenseGlueMatrixForMultiplication<ElementType> GlueMatrixA_M, const DenseGlueMatrixForLinearCombination<ElementType>& GlueMatrixB_L);

template<typename ElementType>
inline DenseMatrix<ElementType> operator/(const DenseGlueMatrixForMultiplication<ElementType>& GlueMatrixA_M, const DenseGlueMatrixForLinearCombination<ElementType>& GlueMatrixB_L);

// ------------------------------------------ GlueMatrixForLinearCombination {+ - * /} GlueMatrixForMultiplication -------------------------------------------//

// note: GlueMatrixForLinearCombination {+ -} GlueMatrixForMultiplication return GlueMatrixForLinearCombination
// note: GlueMatrixForLinearCombination {*}   GlueMatrixForMultiplication return GlueMatrixForMultiplication
// note: GlueMatrixForLinearCombination {/}   GlueMatrixForMultiplication return Matrix

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator+(DenseGlueMatrixForLinearCombination<ElementType> GlueMatrixA_L, DenseGlueMatrixForMultiplication<ElementType> GlueMatrixB_M);

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator-(DenseGlueMatrixForLinearCombination<ElementType> GlueMatrixA_L, DenseGlueMatrixForMultiplication<ElementType> GlueMatrixB_M);

template<typename ElementType>
inline DenseGlueMatrixForMultiplication<ElementType> operator*(const DenseGlueMatrixForLinearCombination<ElementType>& GlueMatrixA_L, DenseGlueMatrixForMultiplication<ElementType> GlueMatrixB_M);

template<typename ElementType>
inline DenseMatrix<ElementType> operator/(const DenseGlueMatrixForLinearCombination<ElementType>& GlueMatrixA_L, const DenseGlueMatrixForMultiplication<ElementType>& GlueMatrixB_M);

// --------------------------------------------- GlueMatrixForMultiplication {+ - * /}  GlueMatrixForMultiplication ---------------------------------------//

// note: GlueMatrixForMultiplication {+ -} GlueMatrixForMultiplication return GlueMatrixForLinearCombination
// note: GlueMatrixForMultiplication {*}   GlueMatrixForMultiplication return GlueMatrixForMultiplication
// note: GlueMatrixForMultiplication {/}   GlueMatrixForMultiplication return Matrix

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator+(DenseGlueMatrixForMultiplication<ElementType> GlueMatrixA, DenseGlueMatrixForMultiplication<ElementType> GlueMatrixB);

template<typename ElementType>
inline DenseGlueMatrixForLinearCombination<ElementType> operator-(DenseGlueMatrixForMultiplication<ElementType> GlueMatrixA, DenseGlueMatrixForMultiplication<ElementType> GlueMatrixB);

template<typename ElementType>
inline DenseGlueMatrixForMultiplication<ElementType> operator*(DenseGlueMatrixForMultiplication<ElementType> GlueMatrixA, DenseGlueMatrixForMultiplication<ElementType> GlueMatrixB);

template<typename ElementType>
inline DenseMatrix<ElementType> operator/(const DenseGlueMatrixForMultiplication<ElementType>& GlueMatrixA, const DenseGlueMatrixForMultiplication<ElementType>& GlueMatrixB);

} // namespace mdk

#include "mdkDenseMatrixOperator_DenseMatrix.hpp"
#include "mdkDenseMatrixOperator_DenseShadowMatrix.hpp"
#include "mdkDenseMatrixOperator_DenseGlueMatrixForLinearCombination.hpp"
#include "mdkDenseMatrixOperator_DenseGlueMatrixForMultiplication.hpp"
