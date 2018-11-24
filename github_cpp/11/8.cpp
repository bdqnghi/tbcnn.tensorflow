// C++ Implementation of Quad Tree
#include <iostream>
#include <cmath>
using namespace std;
#include "util.h"
#include "Tracer.h"

struct Pair {
	uint32_t a;
	uint32_t b;
};

static void fillPairArray(uint8_t* seedIn, int seedSize, Pair arr[], int n) {
	uint32_t* rand1024=new uint32_t[1024]; //1024 32-b values 
	expandRand4KB(seedIn, seedSize, (uint8_t*)rand1024);
	int counter=0;
	for(int i=0; i<1024; i++) {
		for(int j=0; j<1024; j+=2) {
			if(j==i) continue;
			arr[counter].a=mulxor(rand1024[i],rand1024[j]);
			arr[counter].b=mulxor(rand1024[i],rand1024[j+1]);
			//printf("%d-%d: a:%08x b:%08x %08x %08x \n",i,j,
			//		arr[counter].a,arr[counter].b,
			//		rand1024[i],rand1024[j]);
			counter++;
			if(counter==n) {
				delete[] rand1024;
				return;
			}
		}
	}
	assert(false);
}
 
 
// Used to hold details of a point
struct Point
{
    int x;
    int y;
    Point(int _x, int _y)
    {
        x = _x;
        y = _y;
    }
    Point()
    {
        x = 0;
        y = 0;
    }
};
 
// The objects that we want stored in the quadtree
struct Node
{
    Point pos;
    int data;
    Node(Point _pos, int _data)
    {
        pos = _pos;
        data = _data;
    }
    Node()
    {
        data = 0;
    }
};
 
// The main quadtree class
class Quad
{
    // Hold details of the boundary of this node
    Point topLeft;
    Point botRight;
 
    // Contains details of node
    Node *n;
 
    // Children of this tree
    Quad *topLeftTree;
    Quad *topRightTree;
    Quad *botLeftTree;
    Quad *botRightTree;
 
public:
    Quad()
    {
        topLeft = Point(0, 0);
        botRight = Point(0, 0);
        n = NULL;
        topLeftTree  = NULL;
        topRightTree = NULL;
        botLeftTree  = NULL;
        botRightTree = NULL;
    }
    ~Quad()
    {
        if(topLeftTree  != NULL) delete topLeftTree ;
        if(topRightTree != NULL) delete topRightTree;
        if(botLeftTree  != NULL) delete botLeftTree ;
        if(botRightTree != NULL) delete botRightTree;
        if(n != NULL) delete n;
    }
    Quad(Point topL, Point botR)
    {
        n = NULL;
        topLeftTree  = NULL;
        topRightTree = NULL;
        botLeftTree  = NULL;
        botRightTree = NULL;
        topLeft = topL;
        botRight = botR;
    }
    void insert(Node*);
    Node* search(Point);
    bool inBoundary(Point);
};
 
// Insert a node into the quadtree
void Quad::insert(Node *node)
{
    if (node == NULL)
        return;
 
    // Current quad cannot contain it
    if (!inBoundary(node->pos))
        return;
 
    // We are at a quad of unit area
    // We cannot subdivide this quad further
    if (abs(topLeft.x - botRight.x) <= 1 &&
        abs(topLeft.y - botRight.y) <= 1)
    {
        if (n == NULL)
            n = node;
        return;
    }
 
    if ((topLeft.x + botRight.x) / 2 >= node->pos.x)
    {
        // Indicates topLeftTree
        if ((topLeft.y + botRight.y) / 2 >= node->pos.y)
        {
            if (topLeftTree == NULL)
                topLeftTree = new Quad(
                    Point(topLeft.x, topLeft.y),
                    Point((topLeft.x + botRight.x) / 2,
                        (topLeft.y + botRight.y) / 2));
            topLeftTree->insert(node);
        }
 
        // Indicates botLeftTree
        else
        {
            if (botLeftTree == NULL)
                botLeftTree = new Quad(
                    Point(topLeft.x,
                        (topLeft.y + botRight.y) / 2),
                    Point((topLeft.x + botRight.x) / 2,
                        botRight.y));
            botLeftTree->insert(node);
        }
    }
    else
    {
        // Indicates topRightTree
        if ((topLeft.y + botRight.y) / 2 >= node->pos.y)
        {
            if (topRightTree == NULL)
                topRightTree = new Quad(
                    Point((topLeft.x + botRight.x) / 2,
                        topLeft.y),
                    Point(botRight.x,
                        (topLeft.y + botRight.y) / 2));
            topRightTree->insert(node);
        }
 
        // Indicates botRightTree
        else
        {
            if (botRightTree == NULL)
                botRightTree = new Quad(
                    Point((topLeft.x + botRight.x) / 2,
                        (topLeft.y + botRight.y) / 2),
                    Point(botRight.x, botRight.y));
            botRightTree->insert(node);
        }
    }
}
 
// Find a node in a quadtree
Node* Quad::search(Point p)
{
    // Current quad cannot contain it
    if (!inBoundary(p))
        return NULL;
 
    // We are at a quad of unit length
    // We cannot subdivide this quad further
    if (n != NULL)
        return n;
 
    if ((topLeft.x + botRight.x) / 2 >= p.x)
    {
        // Indicates topLeftTree
        if ((topLeft.y + botRight.y) / 2 >= p.y)
        {
			Tracer::I()->meet(p.x^p.y);
            if (topLeftTree == NULL)
                return NULL;
            return topLeftTree->search(p);
        }
 
        // Indicates botLeftTree
        else
        {
            if (botLeftTree == NULL)
                return NULL;
            return botLeftTree->search(p);
        }
    }
    else
    {
        // Indicates topRightTree
        if ((topLeft.y + botRight.y) / 2 >= p.y)
        {
            if (topRightTree == NULL)
                return NULL;
            return topRightTree->search(p);
        }
 
        // Indicates botRightTree
        else
        {
            if (botRightTree == NULL)
                return NULL;
            return botRightTree->search(p);
        }
    }
};
 
// Check if current quadtree contains the point
bool Quad::inBoundary(Point p)
{
    return (p.x >= topLeft.x &&
        p.x <= botRight.x &&
        p.y >= topLeft.y &&
        p.y <= botRight.y);
}
 
//// Driver program
//int main()
//{
//    Quad center(Point(0, 0), Point(8, 8));
//    Node a(Point(1, 1), 1);
//    Node b(Point(2, 5), 2);
//    Node c(Point(7, 6), 3);
//    center.insert(&a);
//    center.insert(&b);
//    center.insert(&c);
//    cout << "Node a: " <<
//        center.search(Point(1, 1))->data << "\n";
//    cout << "Node b: " <<
//        center.search(Point(2, 5))->data << "\n";
//    cout << "Node c: " <<
//        center.search(Point(7, 6))->data << "\n";
//    cout << "Non-existing node: "
//        << center.search(Point(5, 5));
//    return 0;
//}


void run_QuadTree(uint8_t* seedIn, int seedSize) {
	const int Count=16*1024;
	Pair* tmp=new Pair[Count/4];
	fillPairArray(seedIn, seedSize, tmp, Count/4);
	int16_t* arr=(int16_t*)tmp;
    Quad center(Point(0, 0), Point(1<<15, 1<<15));
	for(int i=0; i<Count; i+=4) {
	    Node* n=new Node(Point(arr[i], arr[i+1]), (int(arr[i+2])<<16)|arr[i+3]);
	    center.insert(n);
	}
	for(int i=0; i<Count; i+=2) {
	    Point p(arr[i], arr[i+1]);
	    center.search(p);
	}
	delete[] tmp;
}

#ifdef SELF_TEST
int main() {
	char hello[100]="aer39invqbj43to;5j46354q34534999!@#%@#$%^&$&ADGSGWREF";
	int len=strlen(hello);
	for(int i=0; i<50; i++) {
		run_QuadTree((uint8_t*)hello,len);
	}
	return 0;
}
#endif
