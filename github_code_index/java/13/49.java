/*
 * This file is part of TILT.
 *
 *  TILT is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  TILT is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with TILT.  If not, see <http://www.gnu.org/licenses/>.
 *  (c) copyright Desmond Schmidt 2014
 */

package tilt.image.convexhull;
import tilt.image.geometry.Point;
import java.util.Iterator;
import java.util.Stack;
import java.util.ArrayList;

/*************************************************************************
 *  Compilation:  javac GrahamaScan.java
 *  Execution:    java GrahamScan < input.txt
 *  Dependencies: Point2D.java
 * 
 *  Create points from standard input and compute the convex hull using
 *  Graham scan algorithm.
 *
 *  May be floating-point issues if x- and y-coordinates are not integers.
 *
 *************************************************************************/

import java.util.Arrays;
import tilt.image.geometry.Polygon;

public class GrahamScan {
    private Stack<Point2D> hull = new Stack<>();

    public GrahamScan(Point2D[] pts) {
        if ( pts.length > 1 )
        {
            // defensive copy
            int N = pts.length;
            Point2D[] points = new Point2D[N];
            for (int i = 0; i < N; i++)
                points[i] = pts[i];

            // preprocess so that points[0] has lowest y-coordinate; 
            // break ties by x-coordinate
            // points[0] is an extreme point of the convex hull
            // (alternatively, could do easily in linear time)
            Arrays.sort(points);

            // sort by polar angle with respect to base point points[0],
            // breaking ties by distance to points[0]
            Arrays.sort(points, 1, N, points[0].POLAR_ORDER);

            hull.push(points[0]);       // p[0] is first extreme point

            // find index k1 of first point not equal to points[0]
            int k1;
            for (k1 = 1; k1 < N; k1++)
                if (!points[0].equals(points[k1])) break;
            if (k1 == N) return;        // all points equal

            // find index k2 of first point not collinear with points[0] and points[k1]
            int k2;
            for (k2 = k1 + 1; k2 < N; k2++)
                if (Point2D.ccw(points[0], points[k1], points[k2]) != 0) break;
            hull.push(points[k2-1]);    // points[k2-1] is second extreme point

            // Graham scan; note that points[N-1] is extreme point different from points[0]
            for (int i = k2; i < N; i++) {
                Point2D top = hull.pop();
                while (Point2D.ccw(hull.peek(), top, points[i]) <= 0) {
                    top = hull.pop();
                }
                hull.push(top);
                hull.push(points[i]);
            }
            //assert isConvex();
        }
        
    }
    int comp( Point2D a, Point2D b, Point2D centroid )
    {
        double res1 = Math.atan2(a.y-centroid.y,a.x-centroid.x);
        double res2 = Math.atan2(b.y-centroid.y,b.x-centroid.x);
        return (res1<res2)?-1:(res1==res2)?0:1;
    }
    /**
     * Return convex hull in counterclockwise order as an Iterable
     * (author's original routine didn't return a CCW list - modified)
     * @return an iterable list of CCW points
     */
    public Iterable<Point2D> hull() {
        ArrayList<Point2D> s = new ArrayList<>();
        double totalX = 0.0;
        double totalY = 0.0;
        for ( int i=0;i<hull.size();i++ )
        {
            Point2D pt = hull.get(i);
            totalX += pt.x;
            totalY += pt.y;
            s.add(pt);
        }
        Point2D centroid = new Point2D( totalX/s.size(), totalY/s.size());
        // shell-sort points ccw
        int h = s.size()/2;
	while (h > 0) 
        {
            for (int i = h; i < s.size(); i++) 
            {
                int j = i;
                Point2D temp = s.get(i);
                while ( j >= h && comp(s.get(j-h),temp,centroid) > 0 ) 
                {
                    s.set(j, s.get(j-h));
                    j = j - h;
                }
                s.set(j,temp);
            }
            if (h == 2) 
                h = 1;
            else 
                h *= (5.0 / 11);
	}
        return s;
    }
    boolean isCounterClockwise( Polygon pg )
    {
        int total = 0;
        for ( int i=1;i<pg.npoints;i++ )
        {
            total += (pg.xpoints[i]-pg.xpoints[i-1])*(pg.ypoints[i]+pg.ypoints[i-1]); 
        }
        return total < 0;
    }
    /**
     * Convert the hull to a polygon with CCW points and closed at the end
     * @return 
     */
    public Polygon toPolygon()
    {
        Iterable<Point2D> pts = hull();
        Iterator<Point2D> iter = pts.iterator();
        Polygon pg = new Polygon();
        while ( iter.hasNext() )
        {
            Point2D pt = iter.next();
            pg.addPoint( (int)Math.round(pt.x),(int)Math.round(pt.y) );
        }
        Point first = pg.firstPoint();
        Point last = pg.lastPoint();
        if ( pg.npoints > 1 && !first.equals(last) )
            pg.addPoint(Math.round(first.x),Math.round(first.y));
//        if ( !isCounterClockwise(pg) && pg.npoints > 3 )
//            System.out.println("not counter-clockwise!");
        return pg;
    }
    // check that boundary of hull is strictly convex
//    private boolean isConvex() {
//        int N = hull.size();
//        if (N <= 2) return true;
//
//        Point2D[] points = new Point2D[N];
//        int n = 0;
//        for (Point2D p : hull()) {
//            points[n++] = p;
//        }
//
//        for (int i = 0; i < N; i++) {
//            if (Point2D.ccw(points[i], points[(i+1) % N], points[(i+2) % N]) <= 0) {
//                return false;
//            }
//        }
//        return true;
//    }

//    // test client
//    public static void main(String[] args) {
//        int N = StdIn.readInt();
//        Point2D[] points = new Point2D[N];
//        for (int i = 0; i < N; i++) {
//            int x = StdIn.readInt();
//            int y = StdIn.readInt();
//            points[i] = new Point2D(x, y);
//        }
//        GrahamScan graham = new GrahamScan(points);
//        for (Point2D p : graham.hull())
//            StdOut.println(p);
//    }
//    public static void main( String[] args )
//    {
//        Point2D[] pts = new Point2D[5];
//        pts[0] = new Point2D(10.0,10.0);
//        pts[1] = new Point2D(20.0,10.0);
//        pts[2] = new Point2D(20.0,20.0);
//        pts[3] = new Point2D(10.0,20.0);
//        pts[4] = new Point2D(10.0,10.0);
//        GrahamScan gs = new GrahamScan(pts);
//        Polygon pg = gs.toPolygon();
//        System.out.println(pg.toString());
//    }
}
