/*
 * JGraLab - The Java Graph Laboratory
 *
 * Copyright (C) 2006-2014 Institute for Software Technology
 *                         University of Koblenz-Landau, Germany
 *                         ist@uni-koblenz.de
 *
 * For bug reports, documentation and further information, visit
 *
 *                         https://github.com/jgralab/jgralab
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, see <http://www.gnu.org/licenses>.
 *
 * Additional permission under GNU GPL version 3 section 7
 *
 * If you modify this Program, or any covered work, by linking or combining
 * it with Eclipse (or a modified version of that program or an Eclipse
 * plugin), containing parts covered by the terms of the Eclipse Public
 * License (EPL), the licensors of this Program grant you additional
 * permission to convey the resulting work.  Corresponding Source for a
 * non-source form of such a combination shall include the source code for
 * the parts of JGraLab used as well as that of the covered work.
 */
package de.uni_koblenz.jgralab.algolib.algorithms.search;

import de.uni_koblenz.jgralab.Edge;
import de.uni_koblenz.jgralab.Graph;
import de.uni_koblenz.jgralab.TraversalContext;
import de.uni_koblenz.jgralab.Vertex;
import de.uni_koblenz.jgralab.algolib.algorithms.AlgorithmTerminatedException;
import de.uni_koblenz.jgralab.algolib.algorithms.search.visitors.SearchVisitorList;
import de.uni_koblenz.jgralab.algolib.functions.BooleanFunction;
import de.uni_koblenz.jgralab.algolib.problems.TraversalFromVertexSolver;
import de.uni_koblenz.jgralab.algolib.visitors.Visitor;

/**
 * This class is the implementation of the breadth first search. This
 * implementation uses the array that computes the vertex order as queue buffer.
 * 
 * @author strauss@uni-koblenz.de
 * 
 */
public class BreadthFirstSearch extends SearchAlgorithm implements
		TraversalFromVertexSolver {

	private SearchVisitorList visitors;
	private int firstV;

	public BreadthFirstSearch(Graph graph, BooleanFunction<Edge> navigable) {
		super(graph, navigable);
	}

	public BreadthFirstSearch(Graph graph) {
		this(graph, null);
	}

	@Override
	public BreadthFirstSearch withLevel() {
		super.withLevel();
		return this;
	}

	@Override
	public BreadthFirstSearch withNumber() {
		super.withNumber();
		return this;
	}

	@Override
	public BreadthFirstSearch withENumber() {
		super.withENumber();
		return this;
	}

	@Override
	public BreadthFirstSearch withParent() {
		super.withParent();
		return this;
	}

	@Override
	public BreadthFirstSearch withoutLevel() {
		super.withoutLevel();
		return this;
	}

	@Override
	public BreadthFirstSearch withoutNumber() {
		super.withoutNumber();
		return this;
	}

	@Override
	public BreadthFirstSearch withoutENumber() {
		super.withoutENumber();
		return this;
	}

	@Override
	public BreadthFirstSearch withoutParent() {
		super.withoutParent();
		return this;
	}

	@Override
	public BreadthFirstSearch normal() {
		super.normal();
		return this;
	}

	@Override
	public BreadthFirstSearch reversed() {
		super.reversed();
		return this;
	}

	@Override
	public BreadthFirstSearch undirected() {
		super.undirected();
		return this;
	}

	@Override
	public void reset() {
		super.reset();
		firstV = 1;
		visitors.reset();
	}

	@Override
	public void resetParameters() {
		super.resetParameters();
		visitors = new SearchVisitorList();
	}

	public int getFirstV() {
		return firstV;
	}

	@Override
	public void addVisitor(Visitor visitor) {
		checkStateForSettingVisitors();
		visitor.setAlgorithm(this);
		visitors.addVisitor(visitor);
	}

	@Override
	public void removeVisitor(Visitor visitor) {
		checkStateForSettingVisitors();
		visitors.removeVisitor(visitor);
	}

	@Override
	public BreadthFirstSearch execute(Vertex root)
			throws AlgorithmTerminatedException {
		TraversalContext subgraph = graph.getTraversalContext();
		if (subgraph != null && !subgraph.containsVertex(root)
				|| visitedVertices.get(root)) {
			return this;
		}
		startRunning();
		vertexOrder[num] = root;

		if (level != null) {
			level.set(root, 0);
		}
		visitors.visitRoot(root);

		if (number != null) {
			number.set(root, num);
		}
		visitors.visitVertex(root);

		visitedVertices.set(root, true);
		num++;
		// main loop
		while (firstV < num && vertexOrder[firstV] != null) {
			Vertex currentVertex = vertexOrder[firstV++]; // pop
			for (Edge currentEdge : currentVertex
					.incidences(traversalDirection)) {
				cancelIfInterrupted();
				if (visitedEdges.get(currentEdge) || navigable != null
						&& !navigable.get(currentEdge)) {
					continue;
				}
				Vertex nextVertex = currentEdge.getThat();

				edgeOrder[eNum] = currentEdge;
				if (enumber != null) {
					enumber.set(currentEdge, eNum);
				}
				visitors.visitEdge(currentEdge);
				visitedEdges.set(currentEdge, true);
				eNum++;

				if (visitedVertices.get(nextVertex)) {
					visitors.visitFrond(currentEdge);
				} else {
					visitors.visitTreeEdge(currentEdge);
					vertexOrder[num] = nextVertex;
					if (level != null) {
						level.set(nextVertex, level.get(currentVertex) + 1);
					}
					if (parent != null) {
						parent.set(currentEdge.getThat(), currentEdge);
					}
					if (number != null) {
						number.set(nextVertex, num);
					}
					visitors.visitVertex(nextVertex);
					visitedVertices.set(nextVertex, true);
					num++;

				}
			}
		}
		done();
		return this;
	}

	@Override
	public BreadthFirstSearch execute() throws AlgorithmTerminatedException {
		super.execute();
		return this;
	}
}
