#include <iostream>
#include <deque>
#include <queue>

class Stack {
public:
    // Push element x onto stack.
	void push(int x) {
		m_q1.push(x);
	}

    // Removes the element on top of the stack.
	void pop() {
		while (m_q1.size() != 1)
		{
			m_q2.push(m_q1.front());
			m_q1.pop();
		}
		m_q1.pop();
		while (!m_q2.empty())
		{
			m_q1.push(m_q2.front());
			m_q2.pop();
		}
	}

    // Get the top element.
	int top() {
		while (m_q1.size() != 1)
		{
			m_q2.push(m_q1.front());
			m_q1.pop();
		}
		int ret = m_q1.front();
		m_q2.push(ret);
		m_q1.pop();
		while (!m_q2.empty())
		{
			m_q1.push(m_q2.front());
			m_q2.pop();
		}
		return ret;
	}

    // Return whether the stack is empty.
	bool empty() {
		return m_q1.empty();
	}

private:
	//std::deque<int> m_q1;
	std::queue<int> m_q1;
	std::queue<int> m_q2;
};

int main(void)
{
	Stack stk;
	stk.push(1);
	stk.push(2);
	stk.push(3);
	stk.push(4);
	stk.push(5);
	std::cout << stk.top() << std::endl;
	stk.pop();
	stk.pop();
	stk.pop();
	std::cout << stk.top() << std::endl;
	return 0;
}