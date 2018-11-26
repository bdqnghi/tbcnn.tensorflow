#ifndef __MATRIX__
#define __MATRIX__

#include "../../SimpleJust.h"

namespace linalg 
    {    
    /* ******************************************************** */
    /* Exceptions */
    /* ******************************************************** */
    class OutOfBounds: public std::exception { virtual const char* what() const throw(); };

    class LeastSquare: public std::exception { virtual const char* what() const throw(); };

    class Multiplication: public std::exception { virtual const char* what() const throw(); };

    /* ******************************************************** */
    /* CLASS Matrix */
    /* ******************************************************** */
    class Matrix
        {
    public:

        Matrix(int rows, int cols);
        Matrix(const Matrix &m);
        Matrix(std::vector<std::vector<double> > t_data);
        Matrix(std::vector<std::vector<int> > t_data);

        operator*(double v);
        operator+(double v);
        operator%(double v);
        operator*(const Matrix &m) throw();
        operator-(const Matrix &m);
        operator+(const Matrix &m);
        operator=(const Matrix &m);
        
        /**
         * Row operations
         */
        void row_scalar_multiplication(int row, double value);
        void row_addition_multilpum(int rowA, int rowB, int times, char isAddition);
        void row_move(int fromRow, int toRow);

        /**
         * Helper functions
         */
        void fill(double value);
        void transpose();
        
        /**
         * set or get value by row & col index
         * Ex. 
         * double v1[2][3] = {{2, 3, 1}, {4, -1, -2} };
         * Matrix A(linalg::MatrixFactory<2,3>(v1));
         * 
         * get_value(1, 2) is refering to v1[0][1] = 3.
         * set_value(2, 1, 2.0) is refering to v1[1][0], replacing 4 with 2.0
         */
        double get_value(int row, int col) throw();
        void set_value(int row, int col, double value) throw();
        
        
        void pretty_print();

        std::vector<std::vector<double> > data;
        int rows; int cols;

    private:
        const OutOfBounds outofbounds;
        const LeastSquare leastsquare;
        const Multiplication multiplication;
        };
    
    /* ******************************************************** */
    /* Matrix factory */
    /* ******************************************************** */

    template <int rows, int cols>
    Matrix MatrixFactory(double (&data)[rows][cols])
        {
        Matrix m(rows, cols);
        for(int i = 0; i < rows; i++)
            {
            m.data.push_back(std::vector<double>());
            m.data[m.data.size()-1].assign(data[i], data[i]+cols);
            }
        return m;
        };

    /* ******************************************************** */
    /* Solving linear equations with LUP Solve  */
    /* ******************************************************** */

    /**
     * Solving linear equations with LUP Solve
     * Introduction to algorithms 3. edition.
     * By Thomas H. Corman, Charles E. Leisersion, Ronald L. Rivest & Clifford Stein 
     * Pg. 817-824 
     */
    Matrix lup_solve(Matrix &A, Matrix &b);
    std::vector<Matrix> lu_decomposition(Matrix &A);
    Matrix ly_b_solve(Matrix &L, Matrix &b);
    Matrix ux_y_solve(Matrix &U, Matrix &Y);

    /* ******************************************************** */
    /* Exceptions */
    /* ******************************************************** */

    inline const char* OutOfBounds::what() const throw()
        {
        return "Matrix.cpp: Out of bounds";
        };

    inline const char* LeastSquare::what() const throw()
        {
        return "Matrix.cpp: Any matrix should atleast be 1 by 1";
        };

    inline const char* Multiplication::what() const throw()
        {
        return "Matrix.cpp: (Matrix A) columnsize == (Matrix B) rowsize.";
        };
    };



#endif