#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
using namespace std;

double randf(double a, double b)
{
    return a + (b-a) * static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
}

int regression(double *x, double *y, int n, double &a, double &b, double &r2)
{
    double Sx=0, Sy=0, Sx2=0, Sy2=0, Sxy=0, tmp;

    if (n <= 0)
        return -1;

    for (int i=0; i<n; ++i) {
        Sx += x[i];
        Sy += y[i];
        Sx2 += x[i]*x[i];
        Sy2 += y[i]*y[i];
        Sxy += x[i]*y[i];
    }
    
    tmp = Sx2 - Sx*Sx/n;
    if (tmp == 0.0)
        return -1;

    a = (Sxy - Sx*Sy/n) / tmp;
    b = (Sy - a*Sx) / n;
    r2 = pow(Sxy - Sx*Sy/n, 2) / ((Sx2 - Sx*Sx/n) * (Sy2 - Sy*Sy/n));

    return 0;
}

int main()
{
    const int n=20;
    double *x, *y, a, b, r2;

    x = new double[n];
    y = new double[n];

    srand(static_cast <unsigned> (time(0)));

    double set_a =  2.0;
    double set_b = -1.0;
    double noise =  0.5;

    for (int i=0; i<n; ++i) {
        x[i] = static_cast <double> (i) / static_cast <double> (n-1);
        y[i] = set_a*x[i] + set_b + randf(-noise, noise);
    }

    regression(x, y, n, a, b, r2);

    cout << fixed << setprecision(4);
    cout << "a: " << a << ", b: " << b << ", R^2: " << r2 << endl;

    return 0;
}
