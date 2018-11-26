//stack34.cpp

#include<iostream>

struct Node {
	Node* next = NULL;
	int data;
};
struct BaseNode{
	Node* top = NULL;
};

class Hanoi{
	private:
		const int num_of_towers;
		BaseNode* tower = NULL;
		int disks;
		bool win;
	public:
		Hanoi(int n_disks);
		~Hanoi();
		void push(int number);
		void move(int from, int to);
		void check();
		void test();
};

Hanoi::Hanoi(int n_disks): disks(n_disks), win(false),num_of_towers(3) {
	tower = new BaseNode[num_of_towers];
	int i;
	for (i = num_of_towers; i > 0; --i)	{
		tower[i].top = NULL;
	}
	for (i = disks; i > 0; --i){
		push(i);
	}
}
Hanoi::~Hanoi(){
	delete tower;
}
void Hanoi::push(int number){
	Node* temp = new Node;
	temp -> data = number;
	temp -> next = tower[0].top;
	tower[0].top = temp;
}
void Hanoi::move(int from, int to){
	if(tower[from].top == NULL){
		std::cout << std::endl <<"Cannot move!" << std::endl;
		return;
	}
	if(tower[from].top != NULL && tower[to].top != NULL){
		if (tower[from].top -> data > tower[to].top -> data){
		std::cout << std::endl << "Cannot move!" << std::endl;
		return;
		}
	}
	Node* temp = tower[from].top;
	tower[from].top = tower[from].top -> next;
	temp -> next = tower[to].top;
	tower[to].top = temp;
}
void Hanoi::check(){
	Node* current = NULL;
	int i;
	std::cout << std::endl;
	for (i = 0; i < num_of_towers; ++i)	{
		current = tower[i].top;
		std::cout << std::endl << i << ": ";
		while(current != NULL){
			std::cout << current -> data << ' ';
			current = current -> next;
		}
	}
}
void Hanoi::test(){
	check();
	move(0,1);	check();
	move(0,2);	check();
	move(1,2);	check();
	move(0,1);  check();
	move(2,0);  check();
	move(2,1);  check();
	move(0,1);  check();

}

int main(int argc, char const *argv[])
{
	Hanoi myHanoi(3);
	myHanoi.test();

	return 0;
}