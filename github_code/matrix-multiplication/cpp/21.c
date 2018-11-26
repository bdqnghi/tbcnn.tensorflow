#ifndef ARRAYS_NBULECTURE_2D_MATRIXMULTIPLICATION_H
#define ARRAYS_NBULECTURE_2D_MATRIXMULTIPLICATION_H

/**
 *  @brief
 *  @date 03.11.18
 *  @author Stoyan Lupov
 */

//Corresponding header

//C system headers

//C++ system headers

//Other libraries headers

//Own components headers
#include "arrays/TwoDimensionArrayProblem.h"

class MatrixMultiplication : public TwoDimensionArrayProblem
{
public:
    MatrixMultiplication();

    virtual ~MatrixMultiplication();

    virtual void solve() override;

private:

    void initDataForProblem();

    void initRandomDataForProblem();

    void printSolution();

    std::string getMatrixRowAsString(int32_t ** matrix, const int32_t rowIdx,
                        const int32_t rowSize);

    int32_t getCellValue(const int32_t rowIdx, const int32_t colIdx);

    int32_t ** _matrixA;
    int32_t _matrixARows;
    int32_t _matrixACols;

    int32_t ** _matrixB;
    int32_t _matrixBRows;
    int32_t _matrixBCols;
};


#endif //ARRAYS_NBULECTURE_2D_MATRIXMULTIPLICATION_H
