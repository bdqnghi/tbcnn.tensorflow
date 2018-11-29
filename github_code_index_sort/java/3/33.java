/**
 * ACS Component Code Generator - http://code.google.com/p/acsccg/
 * Copyright (C) 2010  Alexis Tejeda, alexis.tejeda@gmail.com
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * who     		when      		what
 * --------		--------		----------------------------------------------
 * atejeda 		2010-00-00  	Created
 * 
 * $Id$
 */

package comodo.cg.util.xtend;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Queue;
import java.util.Set;
import java.util.Vector;

import org.eclipse.uml2.uml.Classifier;
import org.eclipse.uml2.uml.Property;

/**
 * This class do the topological sort
 * @author atejeda
 */
public class TopologicalSort {

	/**
	 * Get the ETopic Sorted
	 * @param elementList
	 */
	public static final List<Classifier> getETopicSorted(List<Classifier> elementList)
	{
		Vector<ENodeElement> toSort = new Vector<ENodeElement>();
		List<Classifier>  eSortedList = new ArrayList<Classifier> (elementList);
		eSortedList.removeAll(eSortedList);
		
		for(Classifier eElement : elementList)
		{
			String nodeName = eElement.getName();
			Vector<String> edge  = new Vector<String>();
			
			for(Property eProperty : eElement.getAllAttributes() )
			{
				String dataTypeName = eProperty.getType().getName();
				
				if(isCustomType(elementList, dataTypeName))
				{
					edge.add(dataTypeName);
				}
			}
			
			ENodeElement node = new ENodeElement(nodeName, stringVectorToArray(edge));
			toSort.add(node);
		}
		
		try 
		{
			String[] sorted =  TopologicalSort.topologicalSort(eElementVectorToArray(toSort));
			for(int i =0; i< sorted.length; i++)
			{
				eSortedList.add(i, getElement(elementList, sorted[i]));
			}
			return eSortedList;
		} 
		catch (Exception e) 
		{
			//should never return null
			return null;
		}
	}
	
	/**
	 * Return a classifier element in the list by the name
	 * @param elementList
	 * @return Classifier
	 */
	public static final Classifier getElement(List<Classifier> elementList, String elementName)
	{
		for(Classifier eElement : elementList)
			if(eElement.getName().equals(elementName))
				return eElement;
		//should never return a null. - @warning
		return null;
	}
	
	/**
	 * Check if exists any circular dependency
	 * @param elementList
	 */
	public static final boolean hasCircularETopicDependencies(List<Classifier> elementList)
	{
		Vector<ENodeElement> toSort = new Vector<ENodeElement>();
		
		for(Classifier eElement : elementList)
		{
			String nodeName = eElement.getName();
			Vector<String> edge  = new Vector<String>();
			
			for(Property eProperty : eElement.getAllAttributes() )
			{
				String dataTypeName = eProperty.getType().getName();
				
				if(isCustomType(elementList, dataTypeName))
				{
					edge.add(dataTypeName);
				}
			}
			
			ENodeElement node = new ENodeElement(nodeName, stringVectorToArray(edge));
			toSort.add(node);
		}
		
		try {
			String[] sorted =  TopologicalSort.topologicalSort(eElementVectorToArray(toSort));
			
			for(String eElementName : sorted)
			{
				System.out.println(eElementName);
			}
			return true;
		} 
		catch (Exception e) 
		{
			//e.printStackTrace();
			return true;
		}
	}
	
	/**
	 * Converts a vector string to an array, cast doesn't work
	 * @param vectorString
	 * @return String[]
	 */
	public static final String[] stringVectorToArray(Vector<String> vectorString)
	{
		String[] arrayString = new String[vectorString.size()];
		
		for(int i=0; i < vectorString.size(); i++)
				arrayString[i] = vectorString.get(i); 
		
		return arrayString;
	}
	
	/**
	 * Converts a vector string to an array, cast doesn't work
	 * @param vectorString
	 * @return String[]
	 */
	public static final ENodeElement[] eElementVectorToArray(Vector<ENodeElement> vectoreElement)
	{
		ENodeElement[] elementString = new ENodeElement[vectoreElement.size()];
		
		for(int i=0; i < vectoreElement.size(); i++)
				elementString[i] = vectoreElement.get(i); 
		
		return elementString;
	}
	
	/**
	 * Check if the type is a custom type or belong to the model
	 * @param elementList
	 * @param typeName
	 * @return
	 */
	public static final boolean isCustomType(List<Classifier> elementList, String typeName)
	{
		for(Classifier eElement : elementList)
			if(eElement.getName().equals(typeName)) return true;
		return false;
	}
	
	/**
	 * This function sort a common topological order of structs,
	 * sequences and hierarchical in IDL's order to compile.
	 * If the relations has a circular dependency 
	 * @param eNode
	 * @return String
	 * @throws Exception
	 */
	@SuppressWarnings({ "unchecked", "rawtypes" })
	public static final String[] topologicalSort(ENodeElement[] eNode) throws Exception {
		/*
		 * Q ? Set of all nodes with no incoming edges while Q is non-empty do
		 * remove a node n from Q output n for each node m with an edge e from n
		 * to m do remove edge e from the graph if m has no other incoming edges
		 * then insert m into Q if graph has edges then output error message
		 * (graph has a cycle)
		 */
		int n = eNode.length;
		int index = 0;
		Map graph = new HashMap();
		Queue q = new LinkedList();
		
		String[] sorted = new String[n];
		
		// Graph construction
		for (int i = 0; i < eNode.length; i++) 
		{
			// for each statistic name s
			graph.put(eNode[i].job, new HashSet());
			String[] requiredJobs = eNode[i].others;
			for (int j = 0; j < requiredJobs.length; j++) 
			{
				// for each String si in requiredStats
				((Set) graph.get(eNode[i].job)).add(requiredJobs[j]);
			}
			// Initial nodes in q
			if (((Set) graph.get(eNode[i].job)).size() == 0)
				q.add(eNode[i].job);
		}

		// Getting the nodes in sorted order
		
		while (q.size() > 0) 
		{
			String s = (String) q.remove();
			sorted[index++] = s;
			Iterator iter = graph.keySet().iterator();
			
			while (iter.hasNext()) 
			{
				// for each key in graph
				// check if node is not already removed
				Object key = iter.next();
				if (((Set) graph.get(key)).size() != 0) {
					((Set) graph.get(key)).remove(s);
					// if this node now has zero incoming edges
					if (((Set) graph.get(key)).size() == 0) {
						q.add(key);
					}
				}
			}
		}

		if (index < n)
			throw new Exception();

		return sorted;
	}
}
