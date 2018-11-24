// Convex-Hull.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Convex-Hull.h"

#include <algorithm>


Coordinate::Coordinate()
{
}

Coordinate::Coordinate(double x, double y):
	m_x(x),
	m_y(y)
{}

double Coordinate::GetX() const
{
	return m_x;
}

double Coordinate::GetY() const
{
	return m_y;
}

void Coordinate::SetX(const double x)
{
	m_x = x;
}

void Coordinate::SetY(const double y)
{
	m_y = y;
}


Polygon::Polygon(std::vector<Coordinate>&& polygon) :
	m_polygon(std::move(polygon))
{
}

Polygon::Polygon(const std::vector<Coordinate>& polygon) :
	m_polygon(polygon)
{
}

Polygon::Polygon()
{}

bool Polygon::CrossProduct(const Coordinate& pointA, const Coordinate& pointB, const Coordinate& pointC)
{
	auto orientation = (pointC.GetX() - pointA.GetX()) * (pointB.GetY() - pointA.GetY()) -
		(pointC.GetY() - pointA.GetY()) * (pointB.GetX() - pointA.GetX());

	return orientation > 0;
}

void Polygon::SetConvexHull(std::vector<Coordinate>&& convexPolygon)
{
	m_convexHull = std::move(convexPolygon);
}

void Polygon::SetConvexHull(std::vector<Coordinate> convexPolygon)
{
	m_convexHull = convexPolygon;
}

std::vector<Coordinate> Polygon::GetConvexHull()
{
	return m_convexHull;
}


// When sorting the GPS coordinates, we want to give x precidence. We also handle the case where the x coordinate is the same,
// which we then check the y coordinate.
bool Polygon::SortPoints(const Coordinate& pointA, const Coordinate& pointB)
{
	return (pointA.GetX() < pointB.GetX()) || (pointA.GetX() == pointB.GetX() && pointA.GetY() < pointB.GetY());
}

std::vector<Coordinate> Polygon::ComputeConvexHull()
{
	// The polygon needs to have at least three points
	if (m_polygon.size() < 3)
	{
		return std::vector<Coordinate>();
	}

	std::vector<Coordinate> upperHull;
	std::vector<Coordinate> lowerHull;
	upperHull.push_back(m_polygon[0]);
	upperHull.push_back(m_polygon[1]);

	/*
	We piecewise construct the convex hull and combine them at the end of the method. Note that this could be
	optimized by combing the while loops.
	*/
	for (size_t i = 2; i < m_polygon.size(); i++)
	{
		while (upperHull.size() > 1 && !CrossProduct(upperHull[upperHull.size() - 2], upperHull[upperHull.size() - 1], m_polygon[i]))
		{
			upperHull.pop_back();
		}
		upperHull.push_back(m_polygon[i]);

		while (lowerHull.size() > 1 && !CrossProduct(lowerHull[lowerHull.size() - 2], lowerHull[lowerHull.size() - 1], m_polygon[m_polygon.size() - i - 1]))
		{
			lowerHull.pop_back();
		}
		lowerHull.push_back(m_polygon[m_polygon.size() - i - 1]);
	}
	upperHull.insert(upperHull.end(), lowerHull.begin(), lowerHull.end());

	return upperHull;
}

int main()
{
	std::vector<Coordinate> polygonPoints = { {1,2}, {0,0} };
	Polygon polygon(std::move(polygonPoints));

	auto convexHull = polygon.ComputeConvexHull();

	return 0;
}


