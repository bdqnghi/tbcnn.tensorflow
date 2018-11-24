#include <iostream>
#include <stack>
class Queue {
public:
    // Push element x to the back of queue.
	void push(int x) {
		m_stk1.push(x);
	}

    // Removes the element from in front of queue.
	void pop(void) {
		while (m_stk1.size() != 1)
		{
			m_stk2.push(m_stk1.top());
			m_stk1.pop();
		}
		m_stk1.pop();
		while (!m_stk2.empty())
		{
			m_stk1.push(m_stk2.top());
			m_stk2.pop();
		}
	}

    // Get the front element.
	int peek(void) {
		while (m_stk1.size() != 1)
		{
			m_stk2.push(m_stk1.top());
			m_stk1.pop();
		}
		int ret = m_stk1.top();
		m_stk1.pop();
		m_stk2.push(ret);
		while (!m_stk2.empty())
		{
			m_stk1.push(m_stk2.top());
			m_stk2.pop();
		}
		return ret;
	}

    // Return whether the queue is empty.
	bool empty(void) {
		return m_stk1.empty();
	}
private:
	std::stack<int> m_stk1;
	std::stack<int> m_stk2;
};

using namespace std;

int main(void)
{
	Queue q;
	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);
	q.push(5);
	q.push(6);
	q.push(7);
	q.push(8);

	cout << q.peek() << endl;
	q.pop();
	cout << q.peek() << endl;
	q.pop();
	cout << q.peek() << endl;
	q.pop();
	cout << q.peek() << endl;
	q.pop();
	cout << q.peek() << endl;
	q.pop();
	cout << q.peek() << endl;
	q.pop();
	cout << q.peek() << endl;
	q.pop();
	return 0;
}