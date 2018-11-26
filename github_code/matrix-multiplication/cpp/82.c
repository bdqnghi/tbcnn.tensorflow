#include <iostream>
#include <utility>
#include <chrono>
#include "Matrix.hpp"
#include "Rand.hpp"

using namespace std;
using Clock = std::chrono::high_resolution_clock;
using TimePoint = std::chrono::time_point<Clock>;

std::mt19937 Rand::sBase( time(nullptr) );
std::uniform_real_distribution<float> Rand::sFloatGen;
char sectionBreak[81];
const int iterations = 300;

template <class T> Matrix<T> generateMatrix();

template <class T>
void profileMatrixMultiplication();
template<class T>
void profileMatrixTranspose();

int main() {
    std::fill(sectionBreak, sectionBreak + 79, '=');
    sectionBreak[79] = '\n';
    sectionBreak[80] = '\0';


	cout << "This program measures the execution time of my Matrix class." << endl;
    cout << "All matrices in this suite are 100x100" << endl;
    cout << "For each data type, the op is run " << iterations;
    cout << " times and the average run time is calculated." << endl;
	cout << sectionBreak;
    
    cout << "Profiling FLOAT matrix multiplication" << endl;
	profileMatrixMultiplication<float>();
	cout << sectionBreak;
    
    cout << "Profiling DOUBLE matrix multiplication" << endl;
    profileMatrixMultiplication<double>();
    cout << sectionBreak;
    
    cout << "Profiling INT matrix multiplication" << endl;
    profileMatrixMultiplication<int>();
    cout << sectionBreak;
    
    cout << "Profiling UNSIGNED INT matrix multiplication" << endl;
    profileMatrixMultiplication<unsigned int>();
    cout << sectionBreak;
    
    cout << "Profiling SHORT matrix multiplication" << endl;
    profileMatrixMultiplication<short>();
    cout << sectionBreak;
    
    cout << "Profiling LONG matrix multiplication" << endl;
    profileMatrixMultiplication<long>();
    cout << sectionBreak;
    
    //------------------------------------------------
    
    cout << "Profiling FLOAT matrix transpose" << endl;
    profileMatrixTranspose<float>();
	cout << sectionBreak;
    
    cout << "Profiling DOUBLE matrix transpose" << endl;
    profileMatrixTranspose<double>();
    cout << sectionBreak;
    
    cout << "Profiling INT matrix transpose" << endl;
    profileMatrixTranspose<int>();
    cout << sectionBreak;
    
    cout << "Profiling UNSIGNED INT matrix transpose" << endl;
    profileMatrixTranspose<unsigned int>();
    cout << sectionBreak;
    
    cout << "Profiling SHORT matrix transpose" << endl;
    profileMatrixTranspose<short>();
    cout << sectionBreak;
    
    cout << "Profiling LONG matrix transpose" << endl;
    profileMatrixTranspose<long>();
    cout << sectionBreak;
    
    
	return 0;
}

template <class T>
void profileMatrixMultiplication() {
    Clock::duration total(0);
    for (int i = 0; i < iterations; i++) {
        auto A = generateMatrix<T>();
        auto B = generateMatrix<T>();
        
        auto begin = Clock::now();
        A * B;
        auto end = Clock::now();
        total += (end - begin);
    }


	cout << endl;
	cout << "On average, multiplication takes "
		<< chrono::duration_cast<chrono::microseconds>(total).count() / (1000.f * (float)iterations)
		<< " ms" << endl; 
}

template <class T>
void profileMatrixTranspose() {
    Clock::duration total(0);
    for (int i = 0; i < iterations; i++) {
        auto A = generateMatrix<T>();

        auto begin = Clock::now();
        auto B = A.Transpose();
        auto end = Clock::now();
        total += (end - begin);
    }
    
	cout << endl;
	cout << "On average, transpose takes " << chrono::duration_cast<chrono::microseconds>(total).count() / (1000.f * (float)iterations)
		<< " ms" << endl;
}

template <class T> Matrix<T> generateMatrix() {
    static int rows = 100;
    static int columns = 100;
    Matrix<T> A(rows, columns);

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < columns; j++) {
            A(i,j) = static_cast<T>(Rand::randInt(100));
        }
    }

    return A;
}
