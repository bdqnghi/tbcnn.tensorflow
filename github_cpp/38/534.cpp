#include <iostream>
template<class T>
class Que {
	public:
	Que(const size_t& size) : size(size) {
		arr = new T[size]();
		begin = 0;
		end = 0;
	}

	void push(const T element) {
		if(arr[end] != 0) begin = (begin + 1) % size;
		arr[end] = element;
		end = (end + 1) % size;
	}

	T front() const {
		return arr[begin];
	}

	T pop() {
		T ret = arr[begin];
		begin = (begin + 1) % size;
		return ret;
	}

	virtual ~Que() {
		delete[] arr;
	}

	std::ostream& show(std::ostream & out) const {
		for(size_t i = begin; i % size != end; i++) {
			out << *arr[i % size] << "->";
		}
		return out;
	}

	private:
	const size_t size;
	size_t begin, end;
	T* arr;
};

template<class T>
std::ostream& operator <<(std::ostream& osObject, const Que<T>& queue)
{
    return queue.show(osObject);
}
