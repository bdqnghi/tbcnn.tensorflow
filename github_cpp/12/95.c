

#ifndef MINIMUMSPANNINGTREE_H_
#define MINIMUMSPANNINGTREE_H_

#include <vector>

namespace dgl {
template<typename Weight = int>
class MinimumSpanningTree {
public:
	
	struct NullStatus {
		void setMinimumSpanningTree(Weight& min_weight, bool connected) {
			
		}
		
		void inMinimumSpanningTree(int edge, bool in_tree) {
			
		}
	};
	static NullStatus nullStatus;

	virtual ~MinimumSpanningTree() {
	}
	;

	virtual void printStats() {
		
	}
	virtual int numUpdates() const=0;
	virtual void update()=0;

	virtual bool dbg_uptodate()=0;
	virtual bool dbg_mst()=0;
	
	virtual Weight& weight()=0;
	
	virtual Weight& forestWeight()=0;
	virtual std::vector<int> & getSpanningTree()=0;
	virtual int getParent(int node)=0;
	virtual int getParentEdge(int node)=0;
	virtual bool edgeInTree(int edgeid)=0;
	virtual int numComponents()=0;
	virtual int getComponent(int node)=0;
	virtual int getRoot(int component = 0)=0;
};
template<typename Weight>
typename MinimumSpanningTree<Weight>::NullStatus MinimumSpanningTree<Weight>::nullStatus;
}
;

#endif 
