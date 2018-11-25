







#include <iostream>
#include <stack>

using namespace std;

class Tower{
private:
	stack<int> disks;
	int index;

public:

	Tower(int i){
		index = i;
	}

	int Index(){
		return index;
	}

	void add(int d){
		if(!disks.empty() && disks.top()<=d){
			cout<<"Error placing disk "<<d<<endl;
		}else{
			disks.push(d);
		}
	}

	void moveTopTo(Tower& t){
		int top = disks.top();
		disks.pop();
		t.add(top);
		cout<<"Move disk "<<top<<" from  "<<Index()<<" to "<<t.Index()<<endl;
	}

	void moveDisks(int n, Tower& dest,Tower& buffer){
		if(n>0)
		{
			moveDisks(n-1,buffer,dest);
			moveTopTo(dest);
			buffer.moveDisks(n-1,dest,*this);
		}
	}
};

int main(){

	int n = 3;
	Tower* towers[n];

	for(int i=0;i<n;i++){
		towers[i] = new Tower(i);
	}

	int noDisks;
	cout<<"Enter the number of disks to add to TOWER 0"<<endl;
	cin>>noDisks;

	for(int i=noDisks-1;i>=0;i--){
		towers[0]->add(i);
	}

	int noDisksMoved;
	cout<<"Enter the number of disks to move from TOWER 0 to TOWER 2 via TOWER 1"<<endl;
	cin>>noDisksMoved;

	if(noDisksMoved>noDisks)
		noDisksMoved = noDisks;
	towers[0]->moveDisks(noDisksMoved,*towers[2],*towers[1]);

	return 0;
}


