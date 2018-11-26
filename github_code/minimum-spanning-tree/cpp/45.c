#ifndef _MINIMUMSPANNINGTREE_
#define _MINIMUMSPANNINGTREE_

#include "IGameState.h"
#include "Camera.h"
#include "Graph.h"

// Minimum Spanning Tree base game plugin implementation
class MinimumSpanningTree : public IGameState
{
public:

	MinimumSpanningTree();
	~MinimumSpanningTree(); 

	// IPlugin

	// returns the type of the plug-in
	virtual DLLType GetPluginType() const { return DLLType::Game; }

	// returns the name of the plug-in
	virtual const char* GetName() const { return "MinimumSpanningTree"; }

	// returns the version number of the plugin
	virtual int GetVersion() const { return 0; }

	// IGameState

	// Called only once when the plugin is created
	virtual void Init(class Game& game);

	// Called only once when the plugin is destroyed
	virtual void Destroy(class Game& game);

	// Called every frame to update the state of the game
	virtual void Update(class Game& game);

	// Called every frame to render the game
	virtual void Draw(class Game& game);

private:

	void BuildCamera(class Game& game);
	void BuildGraph(class Game& game);

	Graph* m_pGraph;
	PerspectiveCamera m_camera;
	bool m_bEnableMST;
	
};

#endif // _MINIMUMSPANNINGTREE_
