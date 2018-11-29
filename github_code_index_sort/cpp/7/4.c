#ifndef SHELL_CPP
#define SHELL_CPP
#include "shell.h"

const Point zeroPoint(0,0);
Point Shell::basePoint = zeroPoint;

// constructor without parameters
Shell::Shell() : lsPoints(0)//, basePoint(0,0)
{

}// end

// constructor, that takes as parameter list of points
// and initializes attribute of class
Shell::Shell(const list<Point> _points)
{
    this->lsPoints = _points;
}// end

//copy constructor
Shell::Shell(const Shell &_shell)
{
    this->lsPoints = _shell.lsPoints;
}// end

//destructor
Shell::~Shell()
{

}// end

// method sets list of points
void Shell::setShell(const list<Point> &_shell)
{
    this->lsPoints = _shell;
}// end

// method returns list of points
list<Point> Shell::getShell() const
{
    return this->lsPoints;
}// end

// method sets base point
void Shell::setBasePoint(const Point &_base)
{
    Shell::basePoint = _base;
}// end

// method returns base point
Point Shell::getBasePoint()
{
    return Shell::basePoint;
}// end

list<Point> Shell::sort()
{
   lsPoints.sort();
   return lsPoints;
}

list<Point> Shell::erase()
{
    std::cout<<"Erase function: \n" << "Base: "<<Shell::getBasePoint();
    lsPoints.push_front(Shell::getBasePoint());
    list<Point>::iterator it = lsPoints.begin();
    list<Point>::iterator first = it;
    list<Point>::iterator second = ++it;
    list<Point>::iterator third = ++it;
    for(; third != lsPoints.end(); ){
        cout<<"\nFirst "<<*first<<"\nSecond "<<*second<<"\nThird "<<*third<<std::endl;
        if(turn(*first, *second, *third)<0){
            list<Point>::iterator temp = first;
            lsPoints.erase(second);
            second = temp;
            first--;
        }else{
            first++; second++; third++;
        }
    }
    return lsPoints;
}

list<Point>::iterator Shell::findPlace(const Point &_point)   // return iterator on the previous element
{
    //Point copyBase = Shell::getBasePoint();
    int iMiddle = lsPoints.size()/2, iBegin = 0, iEnd = lsPoints.size(), i = 0;
    list<Point>::iterator it = lsPoints.begin(), itBegin = lsPoints.begin();
    while(iEnd - iBegin > 1){
         while(i != iMiddle){
            ++it; ++i;
        }
         if(turn(Shell::basePoint, *it, _point)>0){

             iBegin = iMiddle;
             itBegin = it;
             iMiddle += iMiddle/2;
             cout<<"Left part\n";
         }else{

             iEnd = iMiddle;
             iMiddle -= iMiddle/2;
             it = itBegin;
             i = 0;
             cout<<"Right part\n";
         }
         cout << *it;
    }
    return it;
}

bool Shell::belongShell(const Point &_point)
{
    Point copyBase = Shell::getBasePoint();
    list<Point>::iterator right = ++lsPoints.begin();
    list<Point>::iterator left = --lsPoints.end();
    if(turn(copyBase, *left, _point)>0 || turn(copyBase, *right, _point)<0)
        return false;

    list<Point>::iterator it = findPlace(_point);
    Point A = *it;
    Point B = *(++it); cout << A << B;
    if(turn(A, B, _point)>=0 && turn(B, A, _point)<=0){

        return true;
    }
    return false;
}

bool Shell::addPoint(const Point &_point)
{
    if(this->belongShell(_point))
        return false;
    list<Point>::iterator it = findPlace(_point);
    lsPoints.insert(++it, _point);
    this->findBase();
    this->sort();
    this->erase();
    return true;
}

Point Shell::findBase()
{
    list<Point>::iterator it = lsPoints.begin(), itBasePoint = lsPoints.begin();
    for(;it != lsPoints.end(); it++){
        if(*itBasePoint > *it)
            itBasePoint = it;
    }
    Shell::basePoint = *itBasePoint;
    std::cout<<"Base: "<<*itBasePoint<<std::endl;
    lsPoints.erase(itBasePoint);
    return Shell::basePoint;
}// end

#endif // !SHELL_CPP
