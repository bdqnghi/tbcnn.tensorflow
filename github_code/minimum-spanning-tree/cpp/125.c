#include "MinimumSpanningTree.h"
#include "Game.h"
#include "RandomGenerator.h"

#include <glm/gtc/constants.hpp>

extern "C" PLUGINDECL IPlugin* CreatePlugin()
{
	return new MinimumSpanningTree();
}

MinimumSpanningTree::MinimumSpanningTree() : m_pGraph(nullptr), m_bEnableMST(false)
{

}

MinimumSpanningTree::~MinimumSpanningTree()
{
	delete m_pGraph;
}

void MinimumSpanningTree::Init(Game& game)
{
	BuildCamera(game);
	BuildGraph(game);

	game.EnableEventWaiting(true);
}

void MinimumSpanningTree::Destroy(Game& game)
{
	IRenderer& renderer = game.GetRenderer();
	renderer.SetCamera(nullptr);
}

void MinimumSpanningTree::Update(Game& game)
{
	IInput& input = game.GetInput();
	if (input.KeyPress(KEY_ENTER))
	{
		BuildGraph(game);
	}
	else if (input.KeyPress(KEY_SPACE))
	{
		m_bEnableMST = !m_bEnableMST;

		m_pGraph->EnableMST(m_bEnableMST);
	}
}

void MinimumSpanningTree::Draw(Game& game)
{
	IRenderer& renderer = game.GetRenderer();

	int width, height;
	renderer.GetDisplayMode(&width, &height);

	// Render the graph in world space
	renderer.SetRenderSpace(RenderSpace::World);
	m_pGraph->Render(renderer);

	renderer.SetRenderSpace(RenderSpace::Screen);
	renderer.DrawString("spacebar: toggle drawing MST\tenter: generate a new MST", glm::vec3(width / 2.0f, height, -1.0f), glm::vec4(1.0f), 40.0f,nullptr,FontAlignment::Center);
}

void MinimumSpanningTree::BuildCamera(Game& game)
{
	IRenderer& renderer = game.GetRenderer();
	int width, height;

	// Build the world space camera
	renderer.GetDisplayMode(&width, &height);
	m_camera.SetLens(glm::pi<float>() / 2.0f, (float)width, (float)height, 0.0f, 50.0f);
	m_camera.LookAt(glm::vec3(0.0f, 0.0f, 200.0f));
	m_camera.Update();

	// Give our camera to the renderer
	renderer.SetCamera(&m_camera);
}

void MinimumSpanningTree::BuildGraph(Game& game)
{
	delete m_pGraph;
	m_pGraph = new Graph();

	Node* pNode = new Node(glm::vec2(-300,0.0f)); // left
	Node* pNode2 = new Node(glm::vec2(300.0f,0.0f)); // right
	Node* pNode3 = new Node(glm::vec2(0.0f)); // center
	Node* pNode4 = new Node(glm::vec2(0.0f,150.0f)); // up
	Node* pNode5 = new Node(glm::vec2(0.0f, -150.0f)); // down
	Node* pNode6 = new Node(glm::vec2(-150.0f,20.0f)); // left center
	Node* pNode7 = new Node(glm::vec2(150.0f, 20.0f)); // right center

	m_pGraph->AddNode(pNode);
	m_pGraph->AddNode(pNode2);
	m_pGraph->AddNode(pNode3);
	m_pGraph->AddNode(pNode4);
	m_pGraph->AddNode(pNode5);
	m_pGraph->AddNode(pNode6);
	m_pGraph->AddNode(pNode7);

	RandomGenerator& random = RandomGenerator::Instance();

	m_pGraph->CreateEdge(pNode, pNode6, random.Generate(0.0f,100.0f));
	m_pGraph->CreateEdge(pNode6, pNode3, random.Generate(0.0f, 100.0f));
	m_pGraph->CreateEdge(pNode6, pNode4, random.Generate(0.0f, 100.0f));
	m_pGraph->CreateEdge(pNode3, pNode7, random.Generate(0.0f, 100.0f));
	m_pGraph->CreateEdge(pNode7, pNode2, random.Generate(0.0f, 100.0f));
	m_pGraph->CreateEdge(pNode, pNode4, random.Generate(0.0f, 100.0f));
	m_pGraph->CreateEdge(pNode, pNode5, random.Generate(0.0f, 100.0f));
	m_pGraph->CreateEdge(pNode3, pNode4, random.Generate(0.0f, 100.0f));
	m_pGraph->CreateEdge(pNode2, pNode4, random.Generate(0.0f, 100.0f));
	m_pGraph->CreateEdge(pNode3, pNode5, random.Generate(0.0f, 100.0f));
	m_pGraph->CreateEdge(pNode2, pNode5, random.Generate(0.0f, 100.0f));

	m_pGraph->GenerateMST();
	m_pGraph->EnableMST(m_bEnableMST);
}
