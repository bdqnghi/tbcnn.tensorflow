// �Ĳ���������ײ���Ĵ���
#include <iostream>
#include <vector>
#include "quadTree.h"
using namespace std;
QuadTree::QuadTree(int level, Rect bounds)
{
	this->bounds = bounds;
	this->level = level;
	this->nodes.resize(0);
	rectObj.resize(0);
}
//  1  0 
//  2  3
void QuadTree::split()		// ���ֳ��ӽڵ㡣
{
	int subwidth = this->bounds.width / 2;
	int subheight = this->bounds.height / 2;
	int x = bounds.x;
	int y = bounds.y;
	if (this->nodes.size() != 0)
	{
		cout << "err the node has child ,can not to split";
		exit(0);
	}

	nodes.push_back(QuadTree(level + 1, Rect(x + subwidth, y, subwidth, subheight)));
	nodes.push_back(QuadTree(level + 1, Rect(x, y, subwidth, subheight)));
	nodes.push_back(QuadTree(level + 1, Rect(x, y + subheight, subwidth, subheight)));
	nodes.push_back(QuadTree(level + 1, Rect(x + subwidth, y + subheight, subwidth, subheight)));
}
int  QuadTree::getIndex(Rect r)			// ����r�õ�rӦ�������ĸ�����
{
	int index = -1;
	int boundsubx = bounds.x + bounds.width / 2;
	int boundsuby = bounds.y + bounds.height / 2;
	int bottomX = r.x + r.width;
	int bottomY = r.y + r.height;
	if (bottomX<boundsubx)
	{
		if (bottomY<boundsuby)
		{
			index = 1;
		}
		else if (r.y>boundsuby)
		{
			index = 2;
		}
	}
	else if (r.x>boundsubx)
	{
		if (r.y>boundsuby)
		{
			index = 3;
		}
		else if (bottomY<boundsuby)
		{
			index = 0;
		}
	}
	return index;
}
void QuadTree::insert(Rect r)
{
	// 1����ǰû�л��ֵ�ʱ���ʱ��ֱ�Ӳ��룬����MaxOBJ֮����Ҫsplit 2������Ѿ��л����˾͵ݹ顣
	if (nodes.size() != 0)
	{
		int index = getIndex(r);
		if (index != -1)
		{
			nodes[index].insert(r);
			return;
		}
	}
	rectObj.push_back(r);
	if (rectObj.size()>MaxObj && level<MaxLevel)
	{
		if (nodes.size() == 0)
		{
			split();		// ������Ҫע�⣬�������Ѿ����ֹ��˵ġ�
		}
		for (list<Rect>::iterator a = rectObj.begin(); a != rectObj.end();)
		{
			int index = getIndex(*a);
			if (index != -1)
			{
				nodes[index].insert(*a);
				a = rectObj.erase(a);
			}
			else {
				a++;
			}
		}
	}
}
