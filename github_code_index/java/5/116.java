/*
 * Copyright (c) 2013 Game Salutes.
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the GNU Lesser Public License v3
 * which accompanies this distribution, and is available at
 * http://www.gnu.org/licenses/lgpl.html
 * 
 * Contributors:
 *     Game Salutes - Repackaging and modifications of original work under University of Chicago and Apache License 2.0 shown below
 * 
 * Repackaging from edu.uchicago.nsit.iteco.utils to com.gamesalutes.utils
 * 
 * Copyright 2008 - 2011 University of Chicago
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ******************************************************************************/
package com.gamesalutes.utils.graph;

import java.util.*;

/**
 * Depth-first search traversal on a graph.
 * 
 * @author Justin Montgomery
 * @version $Id: DFS.java 1946 2010-02-26 17:55:34Z jmontgomery $
 *
 * @param <V> vertex type of the graph
 * @Parma <E> edge type of the graph
 */
public final class DFS<V,E> extends AbstractGraphTraversal<V,E> 
{	
	/**
	 * Constructor.
	 * 
	 * @param g the {@link Graph} to traverse
	 * @param source source {@link Vertex} for traversal
	 */
	public DFS(Graph<V,E> g, Vertex<V> source)
	{
		super(g, source);
	}
	
	/**
	 * Constructor.
	 * 
	 * @param g the {@link Graph} to traverse
	 * @param source source {@link Vertex} for traversal
	 * @param cb a {@link GraphTraversalCallback} for this traversal
	 */
	public DFS(Graph<V,E> g,Vertex<V> source,GraphTraversalCallback<V,E> cb)
	{
		super(g,source,cb);
	}

	public DFS<V,E> execute() 
	{
		traversal = new ArrayList<Vertex<V>>(graph.numVerts());
		Set<Vertex<V>> visited = new HashSet<Vertex<V>>();
		source.setLevel(0);
		visited.add(source);
		traversal.add(source);
		
		callback.onBegin(this);
		callback.onTraverse(new GraphTraversalElement<V,E>(this,source,null,0,0));
		
		execute(0,source,visited);
		
		callback.onFinish(this);
		
		return this;
	}
	
	private void execute(int pathId,Vertex<V> vertex,Set<Vertex<V>> visited)
	{
		int numEdges = graph.numEdges(vertex);
		int newPathId;
		
		if(numEdges > 1)
			newPathId = pathId + 1;
		else
			newPathId = pathId;
		
		for(Iterator<Edge<V,E>> it = graph.edgeIterator(vertex);it.hasNext();)
		{
			Edge<V,E> edge = it.next();
			Vertex<V> next = edge.getTo();
			// only considering outgoing edges
			// and don't want to pop back up to parent either
			if(!next.equals(vertex) && !next.equals(vertex.getParent()))
			{
				// must make copy of vertex
				next = next.clone();
				next.setParent(vertex);
				next.setLevel(vertex.getLevel() + 1);
				
				boolean traverse = callback.onTraverse(new GraphTraversalElement<V,E>(this,next,edge,
						Integer.valueOf(pathId),Integer.valueOf(newPathId)));
				if(traverse)
					traversal.add(next);
				//call recursively down the graph
				if(traverse && visited.add(next))
				{
					execute(newPathId,next,visited);
				}
			}
		} //end for
	}

} //end DFS
