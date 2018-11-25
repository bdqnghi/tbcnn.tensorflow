/******************************************************************************
Copyright (c) 2015 Teardrop Games

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
******************************************************************************/

#if !defined(TASKGRAPH_INCLUDED)
#define TASKGRAPH_INCLUDED

#include <map>
#include <list>
#include "Thread/TaskTypes.h"

namespace Teardrop
{
	struct TaskGraphNode;

	class TaskGraph
	{
	public:
		TaskGraph();
		~TaskGraph();

		// add a task to the graph, with its dependencies and products
		void addTask(Task* pTask);
		// remove a task from the graph
		void removeTask(Task* pTask);
		// return immediate task predecessors (not recursive)
		void findPredecessors(Task *pTask, /*inout*/TaskList& predecessors);
		// return immediate task dependents (not recursive)
		void findDependents(Task *pTask, /*inout*/TaskList& dependents);
		// reset the graph to empty state
		void reset();
		// topological-sort the graph into the provided list; list will be emptied first
		void topologicalSort(TaskList& taskList);
		// topological-sort the graph into our cached list, and return a const ref to it; list will be emptied first
		const TaskList& topologicalSort();

	private:
		typedef std::list<TaskGraphNode*> TaskGraphNodeList;
		typedef std::map<TaskProductType*, TaskGraphNodeList> DependentLUT;
		DependentLUT m_dependentLUT;
		typedef std::map<TaskProductType*, TaskGraphNode*> ProducerLUT;
		ProducerLUT m_producerLUT;
		typedef std::map<Task*, TaskGraphNode*> GraphNodeLUT;
		GraphNodeLUT m_graphNodeLUT;

		// so that we don't have to do a sort every time one is asked for, unless needed
		bool m_bSortNeeded;
		// and the corresponding cached list for when we don't need to do a sort
		TaskList m_sortedTaskList;

		// clear all tables and graph structures
		void clear();
	};
}

#endif // TASKGRAPH_INCLUDED
