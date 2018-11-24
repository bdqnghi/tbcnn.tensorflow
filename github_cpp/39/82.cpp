#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

const int MAXN=0;

struct point
{
    double x, y;
    point operator-(const point &p) const
    {
        return {x-p.x, y-p.y};
    }
    bool operator<(const point &p) const
    {
        if(x!=p.x)
            return x<p.x;
        return y<p.y;
    }
};

int points, hullSize;

point pList[MAXN+5];
point upHull[MAXN+5], downHull[MAXN+5], convexHull[MAXN+5];

double zcross(point i, point j)
{
    return i.x*j.y-i.y*j.x;
}

void getHull(int b, int e, int inc, point hull[])
{
    for(int i=b; i!=e; i+=inc)
    {
        while(hullSize>=2 && zcross(hull[hullSize-1]-hull[hullSize], pList[i]-hull[hullSize])<=0)
            hullSize--;
        hull[++hullSize]=pList[i];
    }
}

int main()
{
    scanf("%d", &points);
    for(int i=1; i<=points; i++)
        scanf("%lf%lf", &pList[i].x, &pList[i].y);

    sort(pList+1, pList+1+points);
    getHull(1, points, 1, convexHull);
    getHull(points, 0, -1, convexHull);
    hullSize--;
}
