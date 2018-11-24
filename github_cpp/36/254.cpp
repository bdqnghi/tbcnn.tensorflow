/**
 * 2-3-4-tree
 */
#include <iostream>

#include <vector>
#include <queue>
#include <limits>


template<typename T>
class BTree
{
	struct Node
	{
		std::vector<T> Vals;
		std::vector<Node*> Ch;

		Node(const T& x): Vals(1, x), Ch(2) {}
		Node(const T& x, Node* l, Node* r):
			Vals(1, x),
			Ch(2)
		{
			Ch[0] = l;
			Ch[1] = r;
		}
		bool split4()
		{
			if(Ch.size() != 4)
				return false;
			// 2 new nodes
			Node* l = new Node(Vals[0], Ch[0], Ch[1]);
			Node* r = new Node(Vals[2], Ch[2], Ch[3]);
			// Update children pointers
			Ch.resize(2);
			Ch[0] = l;
			Ch[1] = r;
			// Update data
			Vals[0] = Vals[1];
			Vals.resize(1);
			return true;
		}
	};

public:
	BTree(): m_root(nullptr), m_count(0), m_levels(0) {}

	size_t size() const { return m_count; }
	unsigned levels() const { return m_levels; }

	bool insert(const T& x)
	{
		if(!m_root)
		{
			m_root = new Node(x);
			++m_levels;
			return true;
		}

		if( m_root->split4() )
			++m_levels;
		if( !insert(m_root, x) )
			return false;
		++m_count;
		return true;
	}

private:
	bool insert(Node* cur, const T& x)
	{
		// Search for the insert point
		size_t i, n = cur->Vals.size();
		for(i = 0; i < n; ++i)
		{
			if(x == cur->Vals[i])
				return false;
			if(x < cur->Vals[i])
				break;
		}
		// Follow child if present
		if(Node* next = cur->Ch[i])
		{
			// Always split 4-nodes
			if(next->split4())
			{
				// Merge top-node after split
				cur->Vals.insert(cur->Vals.begin() + i, next->Vals[0]);
				cur->Ch[i] = next->Ch[0];
				cur->Ch.insert(cur->Ch.begin() + i + 1, next->Ch[1]);
				delete next;

				// Re-check insert point
				if(x == cur->Vals[i])
					return false;
				if(x < cur->Vals[i])
					next = cur->Ch[i];
				else
					next = cur->Ch[i + 1];
			}
			return insert(next, x);
		}

		// Upgrade node if no child at the found position
		// (the node is guaranteed to be non-4-node)
		cur->Vals.insert(cur->Vals.begin() + i, x);
		cur->Ch.insert(cur->Ch.begin() + i, nullptr);
		return true;
	}

private:
	Node* m_root;

	size_t m_count;
	unsigned m_levels;

	// Debugging Routines
public:
	friend std::ostream& operator<<(std::ostream& os, const BTree& t)
	{
		if(!t.m_root)
		{
			os << "(empty)" << std::endl;
			return os;
		}

		std::queue<Node*> q;
		for(q.push(t.m_root); !q.empty(); )
		{
			std::queue<Node*> qq;
			do
			{
				qq.push(q.front());
				q.pop();
			}
			while( !q.empty() );

			while( !qq.empty() )
			{
				Node* v = qq.front();
				qq.pop();

				os << '(';
				size_t i, n;
				for(i = 0, n = v->Vals.size(); i < n; ++i)
				{
					os << v->Vals[i];
					if(i != n - 1)
						os << ' ';
					if(Node* next = v->Ch[i])
						q.push(next);
				}
				if(Node* next = v->Ch[i])
					q.push(next);
				os << ") ";
			}
			os << std::endl;
		}

		return os;
	}

	bool isValid() const
	{
		T prev = std::numeric_limits<T>::min();
		return isValid(m_root, prev);
		
	}

private:
	bool isValid(const Node* p, T& prev) const
	{
		if(!p)
			return true;
		size_t i, n;
		for(i = 0, n = p->Vals.size(); i < n; ++i)
		{
			if( !isValid(p->Ch[i], prev) )
				return false;
			if(prev >= p->Vals[i])
				return false;
			prev = p->Vals[i];
		}
		return isValid(p->Ch[i], prev);
	}
};

// ====================================
static int irand()
{
	return ((rand() & 0x7FFF) << 17) | ((rand() & 0x7FFF) << 2) | (rand() & 0x3) - 0x7FFFFFFF;
}

int main(int, char**)
{
	constexpr unsigned N = 1024 * 1024;
	srand(time(nullptr));

	// Init a 2-3-4-tree
	BTree<int> t;
	for(unsigned i = 0; i < N; i++)
	{
		//std::cout << t << std::endl;
		t.insert( irand() );
	}

	// Stat
	std::cout << "2-3-4-Tree\n"
				 "Size: " << t.size() << "\n"
				 "Levels: " << t.levels() << "\n"
				 "Valid: " << (t.isValid() ? "yes" : "NO" ) << std::endl;
	//std::cout << t;

	return 0;
}

