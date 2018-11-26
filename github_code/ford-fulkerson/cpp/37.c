#ifndef FORDFULKERSON_HH
#define FORDFULKERSON_HH

#include "edge.h"
#include "flownetwork.h"

using Graph = std::vector <std::vector <Edge*> >;

// helper for saving the path
struct Node
{
	int parent;
	Edge* edge;
};

class FordFulkerson
{
	public:
		static bool augmentingPathExists (int source, int sink, Graph& g, std::vector<Node>& path);
		static int findBottleNeck (int sink, Graph& g, std::vector<Node>& path);
		static void augmentPath (int sink, Graph& g, std::vector<Node>& path, int p_flow);
		// method to call
		static int computeMaxFlow (int source, int sink, FlowNetwork& fn);
	private:
		FordFulkerson();

};


#endif
