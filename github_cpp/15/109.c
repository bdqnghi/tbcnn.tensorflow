#include <iostream>
#include <Eigen/Dense>

#include "Typedef.h"

using namespace Eigen;
using namespace std;

int main()
{
    mat22 m;
    m << 1, 2,
         3, 4;
    cout << "m =\n" << m << endl;

    vec2 u(-1, 1);
    cout << "u =\n" << u << endl;

    vec2 v(2, 0);
    cout << "v =\n" << v << endl;

    cout << "m * m =\n" << m * m << endl;

    cout << "m * u =\n" << m * u << endl;

    cout << "uT * m =\n" << u.transpose() * m << endl;

    cout << "uT * v =\n" << u.transpose() * v << endl;

    cout << "u * vT =\n" << u * v.transpose() << endl;

    return 0;
}
