#include <iostream>

using namespace std;

struct Node
{
	int data;
	Node *next;
};

class Stack
{
private:
	Node *head;
public:
	Stack();
	void Push(int d);
	int Pop();
	int Peek();
	bool IsEmpty();
};

Stack::Stack()
{
	head = NULL;
}

void Stack::Push(int d)
{
	Node *newNode = new Node();
	newNode->data = d;
	newNode->next = NULL;

	if (head != NULL)
	{
		newNode->next = head;
	}

	head = newNode;
}

int Stack::Pop()
{
	if (!IsEmpty())
	{
		int d = head->data;
		head = head->next;
		return d;
	}
	else
	{
		return INT_MAX;
	}
}

bool Stack::IsEmpty()
{
	return head == NULL;
}

int Stack::Peek()
{
	if (!IsEmpty())
	{
		return head->data;
	}
	else
	{
		return INT_MAX;
	}
}

class TowerOfHanoi : public Stack
{
private:
	Stack *s[3];
	int size;
public:
	TowerOfHanoi();
	void Insert(int d);
	void Execute();
	void Move(Stack *s1, Stack *s2);
	void PrintC();
};

TowerOfHanoi::TowerOfHanoi()
{
	for (int i = 0; i < 3; i++)
	{
		s[i] = new Stack();
	}
}

void TowerOfHanoi::Insert(int d)
{
	if (s[0]->IsEmpty() || s[0]->Peek() > d)
	{
		s[0]->Push(d);
		size++;
	}
	else
	{
		cout << "Top value: " << s[0]->Peek() << " is lesser than or equal to input: " << d << endl;
	}
}

void TowerOfHanoi::Execute()
{
	int counter = 0;

	while (!s[0]->IsEmpty() || !s[1]->IsEmpty())
	{
		
		if (size % 2 == 0)
		{
			if(!s[0]->IsEmpty() || !s[1]->IsEmpty()) { Move(s[0], s[1]); } else { break;}
			counter++;
			if(!s[0]->IsEmpty() || !s[1]->IsEmpty()) { Move(s[0], s[2]); } else { break;}
			counter++;
			if(!s[0]->IsEmpty() || !s[1]->IsEmpty()) { Move(s[1], s[2]); } else { break;}
			counter++;
		}
		else
		{
			if(!s[0]->IsEmpty() || !s[1]->IsEmpty()) { Move(s[0], s[2]); } else { break;}
			counter++;
			if(!s[0]->IsEmpty() || !s[1]->IsEmpty()) { Move(s[0], s[1]); } else { break;}
			counter++;
			if(!s[0]->IsEmpty() || !s[1]->IsEmpty()) { Move(s[2], s[1]); } else { break;}		}
			counter++;
	}

	cout << "Iteration Count: " << counter << endl;
	PrintC();
}

void TowerOfHanoi::PrintC()
{
	while (!s[2]->IsEmpty())
	{
		cout << "Pop: " << s[2]->Pop() << endl;
	}
}

void TowerOfHanoi::Move(Stack *s1, Stack *s2)
{
	int d;

	if ((s1->IsEmpty() && !s2->IsEmpty()) || (s2->Peek() <= s1->Peek()))
	{
		d = s2->Pop();
		s1->Push(d);
	}
	else if((s2->IsEmpty() && !s1->IsEmpty()) || (s1->Peek() <= s2->Peek()))
	{
		d = s1->Pop();
		s2->Push(d);
	}
	else
	{
		return;
	}
}

int main()
{
	TowerOfHanoi t;

	t.Insert(10);
	t.Insert(9);
	t.Insert(8);
	t.Insert(7);
	t.Insert(6);
	t.Insert(5);
	t.Insert(4);
	t.Insert(3);
	t.Insert(2);
	t.Insert(1);

	t.Execute();

	return 0;
}