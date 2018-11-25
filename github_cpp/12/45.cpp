#ifndef _MINIMUMSPANNINGTREE_
#define _MINIMUMSPANNINGTREE_

#include "IGameState.h"
#include "Camera.h"
#include "Graph.h"


class MinimumSpanningTree : public IGameState
{
public:

	MinimumSpanningTree();
	~MinimumSpanningTree(); 

	

	
	virtual DLLType GetPluginType() const { return DLLType::Game; }

	
	virtual const char* GetName() const { return "MinimumSpanningTree"; }

	
	virtual int GetVersion() const { return 0; }

	

	
	virtual void Init(class Game& game);

	
	virtual void Destroy(class Game& game);

	
	virtual void Update(class Game& game);

	
	virtual void Draw(class Game& game);

private:

	void BuildCamera(class Game& game);
	void BuildGraph(class Game& game);

	Graph* m_pGraph;
	PerspectiveCamera m_camera;
	bool m_bEnableMST;
	
};

#endif 
