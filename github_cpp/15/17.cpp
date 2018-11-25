#ifndef __MATRIX__
#define __MATRIX__

#include "../../SimpleJust.h"

namespace linalg 
    {    
    
    
    
    class OutOfBounds: public std::exception { virtual const char* what() const throw(); };

    class LeastSquare: public std::exception { virtual const char* what() const throw(); };

    class Multiplication: public std::exception { virtual const char* what() const throw(); };

    
    
    
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
        
        
        void row_scalar_multiplication(int row, double value);
        void row_addition_multilpum(int rowA, int rowB, int times, char isAddition);
        void row_move(int fromRow, int toRow);

        
        void fill(double value);
        void transpose();
        
        
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

    
    
    

    
    Matrix lup_solve(Matrix &A, Matrix &b);
    std::vector<Matrix> lu_decomposition(Matrix &A);
    Matrix ly_b_solve(Matrix &L, Matrix &b);
    Matrix ux_y_solve(Matrix &U, Matrix &Y);

    
    
    

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