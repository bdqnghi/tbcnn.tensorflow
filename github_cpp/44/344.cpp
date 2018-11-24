#include <iostream>
#include "node.cpp"
#include <memory>

template<class T>
using sNode = std::shared_ptr<Node<T>>;

template<class T>
class Stack{
	public:
	Stack() : top(0) {};
	virtual void push(sNode<T> node) {
		if(top != 0) {
			sNode<T> old = top->getNext();
			top = node;
			node->setNext(old);
		} else {
			top = node;
			node->setNext(0);
		}
	}

	virtual sNode<T> pop() {
		if(top == 0) return 0;
		sNode<T> oldNode = top;
		top = oldNode->getNext();
		return top;
	}

	std::ostream& show(std::ostream& out) const {
		sNode<T> it = top;
		while (it != 0) {
			out << *it << " -> ";
			it = it->getNext();
		}
		return out;
	}
	private:
	sNode<T> top;
};

template<class T>
std::ostream& operator<<(std::ostream& out, const Stack<T>& stack) {
	return stack.show(out);	
}
