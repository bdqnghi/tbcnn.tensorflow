

#include <cassert>
#include <cmath>
#include <cstdint>
#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include    "matrix_double.h"

int32_t main(int32_t argn, char *argv[]){
	double s[] = {1.0, 0.0,
                  0.0, 1.0};

    std::cout << "Matrix id (2u, 2u, s, \"identity\");\n";
	Matrix identity (2u, 2u, s, "id");

    identity.show();

    double r[] = {+cos(M_PI/6.0), sin(M_PI/6.0),
                  -sin(M_PI/6.0), cos(M_PI/6.0)};

    std::cout << "Matrix rotation (2u, 2u, r, \"rot\");\n";
    Matrix rotation (2u, 2u, r, "rot");
    identity.show();
    rotation.show();

    std::cout << "Matrix sum(identity + rotation);\n";
    Matrix sum(identity + rotation);
    identity.show();
    rotation.show();
    sum.show();

    
    for (uint32_t i=0; 2u > i; ++i){
        for (uint32_t j=0; 2u > j; ++j){
            assert(sum[i][j] == (identity[i][j] + rotation[i][j]));
        }
    }

    std::cout << "Matrix twice(identity * 2.0);\n";
    Matrix twice(identity * 2.0);

    
    assert(twice[0][0] == 2.0);
    assert(twice[0][1] == 0.0);
    assert(twice[1][0] == 0.0);
    assert(twice[1][1] == 2.0);

    std::cout << "Matrix new_axis(twice * rotation);\n";
    Matrix new_axis(twice * rotation);

    
    for (uint32_t i=0; 2u > i; ++i){
        for (uint32_t j=0; 2u > j; ++j){
            assert(new_axis[i][j] == (2.0 * rotation[i][j]));
        }
    }

    Matrix ninety_degrees(rotation * rotation * rotation);

    
    assert(abs(ninety_degrees[0][0] - ( 0.0)) < 1e-12);
    assert(abs(ninety_degrees[0][1] - ( 1.0)) < 1e-12);
    assert(abs(ninety_degrees[1][0] - (-1.0)) < 1e-12);
    assert(abs(ninety_degrees[1][1] - ( 0.0)) < 1e-12);

    
    double xi_d[] = {1.0, 0.0};
    double ones_d[] = {1.0, 1.0};

    Matrix xi(2, 1, xi_d, "xi");
    Matrix B(2, 1, ones_d, "B");

    double u = 0.75;

    Matrix xj;
    
    xj = rotation * xi + B * u;

    xj.show();

    assert(abs(xj[0][0] - ( 0.75 + cos(M_PI/6.0))) < 1e-12);
    assert(abs(xj[1][0] - ( 0.75 - sin(M_PI/6.0))) < 1e-12);

}



