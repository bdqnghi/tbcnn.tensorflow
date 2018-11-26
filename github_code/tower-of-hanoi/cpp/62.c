#include <iostream>
#include <stack>

using namespace std;

class HanoiTower
{
  private:
	stack<int> disks;
	int index;
  public:
	HanoiTower(int num):index(num){}
	void addToTop(int value);
	void moveTopTo(HanoiTower& t);
	void moveToDest(int num, HanoiTower& destnation, HanoiTower& buffer);
	int getIndex() {return index;}
};

void HanoiTower::addToTop(int value)
{
	if(disks.empty() || disks.top() > value)   //remember the case when stack is empty, otherwise will segmentation fault.
	{
		disks.push(value);
	}else{
		cout<<"Error : can't put "<<value<<" on the top of "<<disks.top()<<endl;
	}
}

void HanoiTower::moveTopTo(HanoiTower& t)
{
	if(disks.empty())
	{
		return;
	}
	int top = disks.top();
	t.addToTop(top);
	disks.pop();
	cout<<"move "<<top<<" from "<<index<<" to "<<t.getIndex()<<endl;
}

//move num of disks from current tower to destination by using buffer.
void HanoiTower::moveToDest(int num, HanoiTower& destination, HanoiTower& buffer)
{
	if(num > 0)
	{
		moveToDest(num-1, buffer, destination);
		moveTopTo(destination);
		buffer.moveToDest(num-1, destination, *this);
	}
}

int main()
{
	int n = 5;
	HanoiTower* tow[3];
	for(int i=0; i<n; i++)
	{
		tow[i] = new HanoiTower(i);
	}
	for(int i=n; i>=0; i--)
	{
		tow[0]->addToTop(i);
	}
	tow[0]->moveToDest(n, *tow[2], *tow[1]);
}

