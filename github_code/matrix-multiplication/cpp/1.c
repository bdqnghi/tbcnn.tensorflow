//
// Created by Zeka on 12/5/2015.
//

#ifndef MATRIXALGORITHMS_MATRIX_H
#define MATRIXALGORITHMS_MATRIX_H
template <typename T>
class Matrix;
template <typename T>
class AugmentedMatrix;

#include "MatrixMultiplication.h"
#include "BaseMatrixMultiplication.h"
#include "StrassenMatrixMultiplication.h"
#include "JordanInverseMatrix.h"
#include "Vector.h"
#include <vector>
#include <istream>
#include <ostream>
#include <string>
#include <sstream>

template <typename T>
class Matrix {
protected:
    int m, n;
    std::vector<std::vector<T> > matrix;
    static MatrixMultiplication<T>* multiplication;
public:
    Matrix(int m=0, int n=0){
        Matrix::n=n;
        Matrix::m=m;
        matrix.assign(m,std::vector<T>(n,0));
    }
    Matrix(const std::vector<std::vector<T> > &matrix) : matrix(matrix) { }
    Matrix(Matrix<T> const& M){
        m=M.getM();
        n=M.getN();
        matrix.assign(M.matrix.cbegin(),M.matrix.cend());
    }

    int getM() const {
        return m;
    }
    void setM(int m) {
        Matrix::m = m;
        matrix.resize(m, std::vector<T>(n, 0));
    }
    int getN() const{
        return n;
    }
    void setN(int n){
        Matrix::n = n;
        for(int i=0; i < m; ++i)
            matrix[i].resize(n, 0);
    }

    void swapRows(int i, int j){
        if(i==j) return;
        T tmp;
        if(i>=0 && j>=0 && i<m && j<m)
            for(int k=0; k<n; ++k){
                tmp=matrix[i][k];
                matrix[i][k]=matrix[j][k];
                matrix[j][k]=tmp;
            }
    }
    void swapColumns(int i, int j){
        if(i==j) return;
        T tmp;
        if(i>=0 && j>=0 && i<n && j<n)
            for(int k=0; k<m; ++k){
                tmp=matrix[k][i];
                matrix[k][i]=matrix[k][j];
                matrix[k][j]=tmp;
            }
    }

    Vector<T> getRow(int i) const{
        Vector<T> v(n);
        for(int j=0; j<n; ++j)
            v(j)=matrix[i][j];
        return v;
    }
    Vector<T> getColumn(int i) const{
        Vector<T> v(m);
        for(int j=0; j<m; ++j)
            v(j)=matrix[j][i];
        return v;
    }

    void setRow(int i, Vector<T> const & V){
        for(int j=0; j<n; ++j)
            matrix[i][j]=V(j);
    }
    void setColumn(int i, Vector<T> const & V){
        for(int j=0; j<m; ++j)
            matrix[j][i]=V(j);
    }

    static void setDefaultMultiplication(MatrixMultiplication<T>* multiplication){
        delete Matrix::multiplication;
        Matrix::multiplication = multiplication;
    }
    Matrix<T> operator*(const Matrix<T>& A) const{
        return multiplication->multiply(*this,A);
    }
    T& operator()(int m, int n){
        return matrix[m][n];
    }
    T operator()(int m, int n) const{
        if(m>=matrix.size()) return 0;
        if(n>=matrix[m].size()) return 0;
        return matrix[m][n];
    }
    Matrix<T> const & operator=(const Matrix<T>& A){
        Matrix::m = A.m;
        Matrix::n = A.n;
        for(auto& item: matrix)
            item.resize(n,0);
        matrix.resize(m,std::vector<T>(n,0));
        for(int i=0; i<m; ++i)
            for(int j=0; j<n; ++j)
                matrix[i][j] = A(i,j);
        return A;
    }
    Matrix<T> operator+(const Matrix<T>& A) const{
        Matrix C;
        if(n!=A.getN() || m!=A.getM()) return C;

        C=*this;
        for(int i=0; i<C.getM(); ++i)
            for(int j =0; j<C.getN(); ++j)
                C(i,j)+=A(i,j);

        return C;
    }
    Matrix<T> operator-(const Matrix<T>& A) const{
        Matrix C;
        if(n!=A.getN() || m!=A.getM()) return C;

        C=*this;
        for(int i=0; i<C.getM(); ++i)
            for(int j =0; j<C.getN(); ++j)
                C(i,j)-=A(i,j);

        return C;
    }
    Matrix<T> operator~() const{
        return getInverseMatrixByJordan(*this);
    }
    template <typename T0>
    friend std::ostream& operator<<(std::ostream& out, Matrix<T0>const &A){
        for(int i=0; i<A.m; ++i){
            for(int j=0; j<A.n; ++j){
                out.width(7);
                out.precision(2);
                out<<std::fixed;
                out<<A.matrix[i][j];
            }
            out<<std::endl;
        }
        return out;
    }
    template <typename T0>
    friend std::istream& operator>>(std::istream& in, Matrix<T0> &A) {
        std::string line;
        std::stringstream ss;
        int n=1,m=0;
        A.setM(0);
        A.setN(0);
        while(n>0) {// while not null line
            std::getline(in, line);
            ss << line;

            T0 tmp;
            n=0;
            if(ss >> tmp) { // if line not null

                A.setM(m+1);
                do{
                    if(A.getN()<=n){
                        A.setN(n+1);
                    }
                    A(m,n)=tmp;
                    ++n;
                } while(ss >> tmp);
                ++m;
            }


            ss.clear();
        }
        return in;
    }

};

template <typename T>
MatrixMultiplication<T>* Matrix<T>::multiplication = new BaseMatrixMultiplication<T>;

template <typename T>
Matrix<T> transpose(Matrix<T> const & A){
    Matrix<T> B(A.getN(),A.getM());
    for(int i=0; i<A.getM(); ++i)
        for(int j=0; j<A.getN(); ++ j)
            B(j,i)=A(i,j);
    return B;
}

template <typename T>
class AugmentedMatrix:public Matrix<T>{
public:
    AugmentedMatrix(Matrix<T> const & A){
        this->n=A.getN();
        this->m=A.getM();
        this->matrix.assign(this->m,std::vector<T>(this->n,0));
        for(int i=0; i<this->m; ++i)
            for(int j=0; j<this->n; ++j)
                this->matrix[i][j]=A(i,j);
    }
    AugmentedMatrix& operator=(Matrix<T> const & A){
        this->n=A.getN();
        this->m=A.getM();
        this->matrix.assign(this->m,std::vector<T>(this->n,0));
        for(int i=0; i<this->m; ++i)
            for(int j=0; j<this->n; ++j)
                this->matrix[i][j]=A(i,j);
        return *this;
    }
    Matrix<T> getA() const{
        Matrix<T> A(*this);
        A.setN(A.getN()-1);
        return A;
    }
    Vector<T> getB() const{
        Vector<T> ans(Matrix<T>::getM());
        for(int i=0; i<Matrix<T>::getM(); ++i)
            ans(i)=this->matrix[i][Matrix<T>::getN()-1];
        return ans;
    }

    template <typename T0>
    friend std::ostream& operator<<(std::ostream& out, AugmentedMatrix<T0>const &A) {
        for(int i=0; i<A.m; ++i){
            for(int j=0; j<A.n; ++j){
                out.width(7);
                out.precision(2);
                out<<std::fixed;
                out<<A.matrix[i][j];
                if(j+2==A.n) printf("|");
            }

            out<<std::endl;
        }
        return out;
    }

    operator Matrix<T>(){ return Matrix<T>(); }
};

#endif //MATRIXALGORITHMS_MATRIX_H
