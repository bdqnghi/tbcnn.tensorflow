#include "CrackingTheCodingInterviewAlgorithms.h"
#include <queue>
#include <fstream>

// trie -----------------------------------------------------

Trie::Trie(const std::string& prefixInput)
	: prefix(prefixInput)
{

}

Trie::~Trie()
{
	for (std::pair<const char, Trie*> child : children)
	{
		delete child.second;
	}
}

int Trie::FindWords(const char* prefix, Trie* root, int numRequired, std::vector<std::string>& outWords)
{
	Trie* node = FindNode(prefix, root);
	int outWordsSize = 0;
	if (node)
	{
		std::queue<Trie*> breadthFirstSearchQueue;		
		breadthFirstSearchQueue.push(node);

		while (!breadthFirstSearchQueue.empty())
		{
			Trie* trie = breadthFirstSearchQueue.front();
			breadthFirstSearchQueue.pop();

			if (trie->isInDictionary)
			{
				outWords.push_back(trie->prefix);
				if (++outWordsSize >= numRequired)
				{
					return outWordsSize;
				}
			}

			for (std::pair<const char, Trie*> child : trie->children)
			{
				breadthFirstSearchQueue.push(child.second);
			}
		}
	}
	return outWordsSize;
}

Trie* Trie::Create()
{
	std::ifstream ifs("englishDictionary.txt", std::ifstream::in);

	Trie* myTrie = new Trie("");

	std::string word;
	while (ifs.good())
	{
		ifs >> word;
		AddPrefixToTrie(word.c_str(), myTrie);
	}

	ifs.close();

	return myTrie;
}

Trie* Trie::FindNode(const char* prefix, Trie* root)
{
	if (!root)
	{
		return nullptr;
	}

	for (; '\0' != *prefix; ++prefix)
	{
		auto iter = root->children.find(*prefix);
		if (root->children.end() != iter) // it's in there
		{
			root = iter->second;
		}
		else
		{
			break; // word prefix does not exist
		}
	}
	return root;
}

void Trie::AddPrefixToTrie(const char* prefix, Trie* root)
{
	if (!root)
	{
		return;
	}

	for (; '\0' != *prefix; ++prefix)
	{
		auto iter = root->children.find(*prefix);
		if (root->children.end() != iter) // it's in there already
		{
			root = iter->second;
		}
		else
		{
			Trie* newNode = new Trie(root->prefix + *prefix);
			root->children.insert(std::make_pair(*prefix, newNode));
			root = newNode;
		}
	}
	root->isInDictionary = true;
}

// topological sort --------------------------------------------------------------------------------
struct TopologicalSortNode
{
	TopologicalSortNode(char inChar)
		: character(inChar)
	{}

	enum Status // NOTE!!!! only used in Depth first search topological sort
	{
		unexplored = 0,
		exploring,
		closed,
		max
	};
	Status status = Status::unexplored;

	char character;
	int numInboundEdges = 0; // NOTE!!!! only used in Breadth first search topological sort
	std::vector<TopologicalSortNode*> outboundEdges;
};

bool CreateGraph(const std::vector<char>& input, const std::vector<std::pair<char, char>>& depend, std::unordered_map<char, TopologicalSortNode*>& graph)
{
	for (auto inputNode : input)
	{
		TopologicalSortNode* newNode = new TopologicalSortNode(inputNode);
		if (!newNode)
		{
			return false;
		}
		graph.insert(std::make_pair(inputNode, newNode));
	}

	for (auto link : depend)
	{
		++graph[link.second]->numInboundEdges; // NOTE! only used in breadth first search topological sort
		graph[link.first]->outboundEdges.push_back(graph[link.second]);
	}
	return true;
}

void DestroyGraph(std::unordered_map<char, TopologicalSortNode*>& graph)
{
	for (std::pair<char, TopologicalSortNode*> entry : graph)
	{
		if (entry.second)
		{
			delete entry.second;
		}
	}
}

bool TopologicalSortBreadthFirstSearch(const std::vector<char>& input, const std::vector<std::pair<char, char>>& depend, std::vector<char>& output)
{
	bool allGood = false;
	std::unordered_map<char, TopologicalSortNode*> graph;
	if (CreateGraph(input, depend, graph))
	{
		std::queue<TopologicalSortNode*> processNext;
		for (auto node : graph)
		{
			if (0 == node.second->numInboundEdges)
			{
				processNext.push(node.second);
			}
		}

		while (!processNext.empty())
		{
			TopologicalSortNode* next = processNext.front();
			processNext.pop();

			for (auto node : next->outboundEdges)
			{
				--node->numInboundEdges;
				if (0 == node->numInboundEdges)
				{
					processNext.push(node);
				}
			}
			output.push_back(next->character);
		}
		allGood = input.size() == output.size();
	}
	DestroyGraph(graph);
	return allGood;
}

bool TopologicalSortDepthFirstSearch(TopologicalSortNode* node, std::vector<char>& result)
{
	if (!node || TopologicalSortNode::Status::exploring == node->status)
	{
		return false;
	}

	if (TopologicalSortNode::Status::closed != node->status) // will be unexplored
	{
		node->status = TopologicalSortNode::Status::exploring;

		for (TopologicalSortNode* child : node->outboundEdges)
		{
			if (!TopologicalSortDepthFirstSearch(child, result))
			{
				return false;
			}
		}
		result.push_back(node->character);
		node->status = TopologicalSortNode::Status::closed;
	}
	return true;
}

bool TopologicalSortDepthFirstSearch(const std::vector<char>& input, const std::vector<std::pair<char, char>>& depend, std::vector<char>& output)
{
	bool allGood = false;
	std::unordered_map<char, TopologicalSortNode*> graph;
	if (CreateGraph(input, depend, graph))
	{
		allGood = true;
		for (std::pair<char, TopologicalSortNode*> entry : graph)
		{
			if (!TopologicalSortDepthFirstSearch(entry.second, output))
			{
				allGood = false; // probably don't need this as 'result.size() == inputNodes.size()' (further down) would be false
				break;
			}
		}
		if (allGood)
		{
			std::reverse(output.begin(), output.end());
			allGood = output.size() == input.size();
		}
	}
	DestroyGraph(graph);
	return allGood;
}