#ifndef POINTSVECTOR
#define POINTSVECTOR

#include <QVector>
#include "Point.h"

namespace custom_types{
/*!
    \brief PointsVector provides a wrapper for QVector<point> with some additional functions.

    It provides the following additional functionality:
    - an insertion-sort sort function
    - a function to split the vector into two seperate QVector<double> containing the x- respectively the y-values.
    - a search function to find a Point with an equal x-coordinate
*/
class PointsVector : public QVector<Point>{
   public:

    /*!
        \brief Sorts the vector using an implementation of an insertion-sort algorithm.

    */
    void sort();

    /*!
        \brief Splits the vector into two seperate QVector<double> containing the x- respectively the y-values.
        \param x Output vector containing the x-coordinates
        \param y Output vector containing the y-coordinates

        This function splits each Point in the vector into its x- and y-coordinate and adds them to the corresponding output vector.
    */
    void getPointsAsSeperateVectors(QVector<double> &x, QVector<double> &y);

    /*!
        \brief Search function for a Point with an equal x-coordinate.
        \param x x-Coordinate that will be searched for within the vector.

        The function compares the parameter x to the x-coordinate of each Point in the vector and if it finds a match, then it returns its position, otherwise -1.
    */
    int findEqualX(double x);
};

}


#endif // POINTSVECTOR


