

package tilt.image.convexhull;
import tilt.image.geometry.Point;
import java.util.Iterator;
import java.util.Stack;
import java.util.ArrayList;



import java.util.Arrays;
import tilt.image.geometry.Polygon;

public class GrahamScan {
    private Stack<Point2D> hull = new Stack<>();

    public GrahamScan(Point2D[] pts) {
        if ( pts.length > 1 )
        {
            
            int N = pts.length;
            Point2D[] points = new Point2D[N];
            for (int i = 0; i < N; i++)
                points[i] = pts[i];

            
            
            
            
            Arrays.sort(points);

            
            
            Arrays.sort(points, 1, N, points[0].POLAR_ORDER);

            hull.push(points[0]);       

            
            int k1;
            for (k1 = 1; k1 < N; k1++)
                if (!points[0].equals(points[k1])) break;
            if (k1 == N) return;        

            
            int k2;
            for (k2 = k1 + 1; k2 < N; k2++)
                if (Point2D.ccw(points[0], points[k1], points[k2]) != 0) break;
            hull.push(points[k2-1]);    

            
            for (int i = k2; i < N; i++) {
                Point2D top = hull.pop();
                while (Point2D.ccw(hull.peek(), top, points[i]) <= 0) {
                    top = hull.pop();
                }
                hull.push(top);
                hull.push(points[i]);
            }
            
        }
        
    }
    int comp( Point2D a, Point2D b, Point2D centroid )
    {
        double res1 = Math.atan2(a.y-centroid.y,a.x-centroid.x);
        double res2 = Math.atan2(b.y-centroid.y,b.x-centroid.x);
        return (res1<res2)?-1:(res1==res2)?0:1;
    }
    
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


        return pg;
    }
    











































}
