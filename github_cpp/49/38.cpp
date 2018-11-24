#include "LinearRegression.h"

LinearRegression::LinearRegression() 
{

}

void LinearRegression::addPoints(double x, double y) 
{
    this->points.push_back(Point2d(x, y));
}

int LinearRegression::getNumberOfPoints() 
{
    return this->points.size();
}


void LinearRegression::clearListOfPoints() 
{
    this->points.clear();
}


void LinearRegression::removeOldestPoint() 
{
    this->points.pop_front();
}

double LinearRegression::getValueA() 
{
    if(this->points.size() < 3)
        throw -1;

    double s20 = this->getSum(2, 0);
    double s10 = this->getSum(1, 0);
    double s00 = this->points.size();

    double s11 = this->getSum(1, 1);
    double s01 = this->getSum(0, 1);

    return (s11 * s00 - s10 * s01) / (s20 * s00 - s10 * s10);
}

double LinearRegression::getValueB() 
{
    if (this->points.size() < 3)
        throw -1;

    double s20 = this->getSum(2, 0);
    double s10 = this->getSum(1, 0);
    double s00 = this->points.size();

    double s11 = this->getSum(1, 1);
    double s01 = this->getSum(0, 1);

    return (s20 * s01 - s11 * s10) / (s20 * s00 - s10 * s10);
}


double LinearRegression::getSum(int x, int y) 
{
    double Sum = 0;
    for(Point2f point : this->points) 
    {
        Sum += pow(point.x, x) * pow(point.y, y);
    }

    return Sum;
}

LinearRegression::~LinearRegression() 
{
	
}
