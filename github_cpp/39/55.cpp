#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<vector>
#include<stack>
using namespace std;

struct Point
{
	int x,y,id;
}p0;


int orientation(Point p0,Point p1,Point p2)
{
	//Slope difference = m1-m2
	int val = (p1.y-p0.y)*(p2.x-p1.x)-(p2.y-p1.y)*(p1.x-p0.x);
	return val;
}

int orientation(Point p1,Point p2)
{
	//Slope difference = m1-m2
	int val = (p1.y-p0.y)*(p2.x-p1.x)-(p2.y-p1.y)*(p1.x-p0.x);
	return val;
}


double distancex(Point a,Point b)
{
	return sqrt(((double)(a.x-b.x)*(a.x-b.x)+(double)(a.y-b.y)*(a.y-b.y)));
}

int dist(const Point &a,const Point &b)
{
	return ((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

bool compare(const Point &p1,const Point &p2)
{
	int orient = orientation(p1,p2);
	if(orient==0)
		return (dist(p0,p1)<=dist(p0,p2));
	else if(orient<0)
		return true;
	else
		return false;
}

int find_bottom_most_left_point(std::vector<Point> v)
{
	int index=0;
	for (int i = 0; i < v.size(); ++i)
	{
		if(v[i].y<v[index].y||(v[i].y==v[index].y&&v[i].x<v[index].x))
			index=i;
	}
	return index;
}

Point SecondFromTop(stack <Point> s)
{
	Point sTop = s.top();
	s.pop();
	Point secondTop = s.top();
	s.push(sTop);
	return secondTop;  
}


void convex_hull_helper(std::vector<Point> finalPoints)
{
	if(finalPoints.size()<3)
	{
		if(finalPoints.size()==2)
		{
			printf("%lf\n",2*distancex(finalPoints[0],finalPoints[1]));
			printf("%d %d\n",finalPoints[0].id,finalPoints[1].id);
		}
		else
		{
			printf("0.0\n");
			printf("%d\n",finalPoints[0].id);
		}
		return;
	}
	stack <Point> S;
	S.push(finalPoints[0]);
	S.push(finalPoints[1]);
	
	for(int i=2;i<finalPoints.size();++i)
	{
		while(S.size()>1&&orientation(SecondFromTop(S),S.top(),finalPoints[i])>0)
		{
			S.pop();
		}
		S.push(finalPoints[i]);
	}

	double fenceLength=0.0;

	std::vector<Point> convexHullPoints(S.size());

	for(int i=S.size()-1;i>=0;--i)
	{
		convexHullPoints[i]=S.top();
		S.pop();
	}

	for(int i=0;i<convexHullPoints.size()-1;++i)
	{
		fenceLength+=(distancex(convexHullPoints[i],convexHullPoints[i+1]));
	}
	fenceLength+=(distancex(convexHullPoints[0],convexHullPoints[convexHullPoints.size()-1]));
	printf("%lf\n", fenceLength);
	for (int i = 0; i < convexHullPoints.size()-1; ++i)
	{
		printf("%d ",convexHullPoints[i].id);
	}
	printf("%d\n", convexHullPoints[convexHullPoints.size()-1].id);
	printf("\n");
}

void printvector(vector<Point> p)
{
	for(int i=0;i<p.size();++i)
	{
		cout<<p[i].id<<" "<<p[i].x<<" "<<p[i].y<<endl;
	}
}

int main()
{
	std::vector<Point> p,finalPoints;
	int no_of_points,index,t;
	Point point;
	scanf("%d",&t);
	while(t--)
	{
		p.clear();
		finalPoints.clear();
		scanf("%d",&no_of_points);
		for(int i=0;i<no_of_points;++i)
		{
			cin>>point.x>>point.y;
			point.id = i+1;
			p.push_back(point);
		}
	
		index = find_bottom_most_left_point(p);
		p0=p[index];
		swap(p[0],p[index]);
		if(p.size()>1)
		sort(p.begin()+1,p.end(),compare);
		//printvector(p);
		
		
		finalPoints.push_back(p0);
		for(int i=1;i<no_of_points;++i)
		{
			while(i<no_of_points-1&&orientation(p[i],p[i+1])==0)
			{
				++i;
			}
			finalPoints.push_back(p[i]);
		}
	//	printvector(finalPoints);
		
		convex_hull_helper(finalPoints);
		printf("\n");
	}
	return 0;
}