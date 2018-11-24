/*
 * Copyright (C) 2017-2018  Christopher J. Howard
 *
 * This file is part of Emergent.
 *
 * Emergent is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Emergent is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Emergent.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <emergent/geometry/convex-hull.hpp>
#include <emergent/geometry/sphere.hpp>
#include <emergent/geometry/aabb.hpp>

namespace Emergent
{

ConvexHull::ConvexHull(std::size_t planeCount):
	planeCount(planeCount)
{
	planes = new Plane[planeCount]();
}

ConvexHull::~ConvexHull()
{
	delete[] planes;
}

bool ConvexHull::intersects(const Sphere& sphere) const
{
	const Vector3& center = sphere.getCenter();
	float radius = -sphere.getRadius();
	
	for (std::size_t i = 0; i < planeCount; ++i)
	{
		if (planes[i].distance(center) < radius)
			return false;
	}
	
	return true;
}

bool ConvexHull::intersects(const AABB& aabb) const
{
	const Vector3& min = aabb.getMin();
	const Vector3& max = aabb.getMax();
	
	for (std::size_t i = 0; i < planeCount; ++i)
	{
		const Vector3& normal = planes[i].getNormal();
		
		Vector3 pv;
		pv.x = (normal.x > 0.0f) ? max.x : min.x;
		pv.y = (normal.y > 0.0f) ? max.y : min.y;
		pv.z = (normal.z > 0.0f) ? max.z : min.z;
		
		if (planes[i].distance(pv) < 0.0f)
		{
			return false;
		}
	}
	
	return true;
}

bool ConvexHull::contains(const Vector3& point) const
{
	for (std::size_t i = 0; i < planeCount; ++i)
	{
		if (planes[i].distance(point) < 0.0f)
			return false;
	}
	
	return true;
}

bool ConvexHull::contains(const Sphere& sphere) const
{
	for (std::size_t i = 0; i < planeCount; ++i)
	{
		if (planes[i].distance(sphere.getCenter()) < sphere.getRadius())
			return false;
	}
	
	return true;
}

bool ConvexHull::contains(const AABB& aabb) const
{
	const Vector3& min = aabb.getMin();
	const Vector3& max = aabb.getMax();
	
	for (std::size_t i = 0; i < planeCount; ++i)
	{
		const Vector3& normal = planes[i].getNormal();
		
		Vector3 pv;
		Vector3 nv;
		
		pv.x = (normal.x > 0.0f) ? max.x : min.x;
		pv.y = (normal.y > 0.0f) ? max.y : min.y;
		pv.z = (normal.z > 0.0f) ? max.z : min.z;
		nv.x = (normal.x < 0.0f) ? max.x : min.x;
		nv.y = (normal.y < 0.0f) ? max.y : min.y;
		nv.z = (normal.z < 0.0f) ? max.z : min.z;
		
		if (planes[i].distance(pv) < 0.0f || planes[i].distance(nv) < 0.0f)
		{
			return false;
		}
	}
	
	return true;
}

} // namespace Emergent
