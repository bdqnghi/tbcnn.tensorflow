/*
 * MinimumSpanningTrees.cpp - Main entry point for the program
 *
 * Built for EECS2510 - Nonlinear Data Structures
 *	at The University of Toledo, Spring 2016
 *
 * Copyright (c) 2016 Nathan Lowe
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "stdafx.h"
#include <cassert>
#include <iostream>
#include <fstream>

#include "LinkedList.h"
#include "Options.h"
#include "WeightedGraph.h"
#include "SpanningTree.h"
#include "Verbose.h"
#include "PrimVertex.h"

using namespace std;

// Since the verbose namespace is used multiple times in different files,
// we need to define an implementation of the enable flag in exactly one
// translation unit so that it is shared between all units
namespace verbose
{
	bool enable = false;
}

// Forward-declare these functions so main can be at the top as required by the project spec
void printHelp();
void Kruskal(WeightedGraph& graph);
void Prim(WeightedGraph& graph);

int main(int argc, char* argv[])
{
	// parse the command-line arguments
	auto opts = Options(argc, argv);

	if (opts.help)
	{
		printHelp();
		return 0;
	}
	
	if(opts.errors)
	{
		cout << "One or more errors occurred while parsing arguments: " << endl;
		cout << opts.errorMessage;
		cout << endl;
		cout << "Call with --help for help" << endl;

		return -1;
	}

	if (opts.verboseEnable) verbose::enable = true;

	ifstream reader;
	reader.open(opts.TestFilePath, std::ios::in);

	if(!reader.good())
	{
		reader.close();
		cout << "Unable to open graph for read: '" << opts.TestFilePath << "'" << endl;
		return -1;
	}

	// Load the graph
	WeightedGraph g(reader);
	reader.close();

	cout << "Finding minimum spanning tree using Kruskal's algorithm..." << endl;
	try
	{
		Kruskal(g);
	}
	catch (exception ex)
	{
		cout << "Unable to calculate minimum spanning tree: " << ex.what() << endl;
	}

	cout << endl << "Finding minimum spanning tree using Prim's algorithm..." << endl;
	try
	{
		Prim(g);
	}
	catch (exception ex)
	{
		cout << "Unable to calculate minimum spanning tree: " << ex.what() << endl;
	}

    return 0;
}

void printHelp()
{
	cout << "MinimumSpanningTrees <-f path> [-v]" << endl;
	cout << "Parameters:" << endl;
	cout << "\t-f, --file\t\tThe input file to test" << endl;
	cout << "\t-v, --verbose\t\tEnable verbose output" << endl;

	cout << endl;

	cout << "At the end of each algorithm, the generated minimum spanning tree in addition to its total" << endl;
	cout << "weight is printed to standard out. To suppress the printing of the tree, specify the -q flag" << endl;
}

// Calculate and print out a minimum weight spanning tree of the specified graph using
// Kruskal's algorithm:
//
// For each edge sorted by edge weight ascending
//    If the edge connects two verticies that are not already in the same group
//        add them to the tree
void Kruskal(WeightedGraph& graph)
{
	auto sets = new LinkedList<Vertex>*[graph.VertexCount]{nullptr};

	for(auto i = 0; i < graph.VertexCount; i++)
	{
		sets[i] = new LinkedList<Vertex>();
		sets[i]->add(graph.Vertices[i]);
	}

	verbose::write("[Kruskal] Obtaining edges...");
	// Get the edges from the graph
	// This is a minimum priority queue sorted on edge weight
	auto edges = graph.Edges();
	auto tree = new SpanningTree();

	while (!edges->isEmpty())
	{
		// Find the set containing A and B from this edge
		LinkedList<Vertex> *a = nullptr, *b = nullptr;
		auto edge = edges->dequeue();

		// Locate the vertex sets that contain the vertices of this edge
		size_t aIndex = 0;
		size_t bIndex = 0;
		for(auto index = 0; index < graph.VertexCount; index++)
		{
			if(sets[index] != nullptr)
			{
				if (sets[index]->Contains(const_cast<Vertex*>(edge->A)))
				{
					a = sets[index];
					aIndex = index;
				}
				if (sets[index]->Contains(const_cast<Vertex*>(edge->B)))
				{
					b = sets[index];
					bIndex = index;
				}

				// If we found the sets that contain this vertex, we can break early
				if (a != nullptr && b != nullptr) break;
			}
		}

		assert(a != nullptr && b != nullptr && edge != nullptr);

		if (aIndex != bIndex)
		{
			// If the edges belong to different sets, take it
			verbose::write("[Kruskal] Picking edge " + edge->A->Name + "-" + edge->B->Name + ": " + std::to_string(edge->EdgeWeight));
			a->addAll(*b);
			sets[bIndex] = nullptr;
			tree->accept(edge);
		}
		else
		{
			// Otherwise, the edge is redundant
			verbose::write("[Kruskal] Edge " + edge->A->Name + "-" + edge->B->Name + ": " + std::to_string(edge->EdgeWeight) + " is redundant");
		}
	}

	// Done! Print out the tree
	verbose::write("[Kruskal] Done");
	tree->print();
}

// Calculate and print out a minimum weight spanning tree of the specified graph using
// Prim's algorithm:
//
// Start at any vertex
// Until all vertices have been considered
//     Take the lowest edge connecting the tree to any unconnected vertex
void Prim(WeightedGraph& graph)
{
	verbose::write("[Prim] Initializing vertices...");
	
	// We need a queue on a property that gets updated frequently
	// Wrap the vertices in PrimVertex structures and create a queue for this structure
	auto pvs = new PrimVertex*[graph.VertexCount]{ nullptr };
	auto Q = new MinPriorityQueue<PrimVertex>([](PrimVertex* lhs, PrimVertex* rhs) { return lhs->QKey - rhs->QKey; }, graph.VertexCount);

	// Initialize all vertices
	for(auto i = 0; i < graph.VertexCount; i++)
	{
		auto pv = new PrimVertex(graph.Vertices[i]);
		if (i == 0) pv->QKey = 0;
		pvs[i] = pv;
		Q->enqueue(pv);
	}

	auto tree = new SpanningTree();

	// And start taking edges
	while(!Q->isEmpty())
	{
		auto u = Q->dequeue();
		verbose::write("[Prim] Now analyzing connections from " + u->Name + " (local weight: " + to_string(u->QKey) + ")");

		// Look at all vertices reachable from the specified vertex
		for(auto c = 0; c < graph.VertexCount; c++)
		{
			auto w = graph.GetWeight(u->ID, c);
			if (w == 0) continue;
			auto v = pvs[c];

			// Check to see if this is a better way to reach this vertex
			if(Q->contains(v) && w < v->QKey)
			{
				verbose::write(
					"[Prim]     Discovered a better way to get to " + v->Name +
					" (via " + u->Name + " with weight " + to_string(w) +
					(v->QKey == INT64_MAX ? "" : ", previous best was " + to_string(v->QKey) +
					(v->pi == nullptr ? "" : " via " + v->pi->Name)) + ")"
				);

				v->pi = u;
				v->QKey = w;
				Q->notifyPriorityUpdated(v);
			}
		}
	}

	// Now simply work backwards taking the vertex and its parent as an edge
	for(int i = graph.VertexCount - 1; i >= 0; i--)
	{
		auto v = pvs[i];
		if (v->pi != nullptr) tree->accept(new VertexPair(v->pi, v, v->QKey));
	}

	// Done! Print the tree
	verbose::write("[Prim] Done");
	tree->print();
}
