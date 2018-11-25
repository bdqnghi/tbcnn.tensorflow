#include "open-addressing-hash-table.hpp"
#include "separate-chaining-hash-table.hpp"
#include "list-stack.hpp"
#include "array-stack.hpp"
#include "list-queue.hpp"
#include "array-queue.hpp"
#include "binary-search-tree.hpp"
#include "red-black-tree.hpp"
#include "min-heap.hpp"
#include "max-heap.hpp"
#include "heap-filter.hpp"
#include "trie.hpp"
#include "list-graph.hpp"
#include "matrix-graph.hpp"

#include <iostream>

void print()
{
	std::cout << std::endl;
}

template<typename Head, typename... Tail>
void print(Head&& head, Tail&&... tail)
{
	std::cout << std::forward<Head>(head) << " ";
	
	print(std::forward<Tail>(tail)...);
}

template<typename Sequence>
void printall(const Sequence& sequence)
{
	using std::begin;
	using std::end;
	
	for (auto i = begin(sequence), stop = end(sequence); i != stop; )
	{
		std::cout << *i;
		
		if (++i != stop)
		{
			std::cout << ", ";
		}
	}
	
	std::cout << std::endl;
}

int main(int argc, const char* argv[])
{
	
}