package nl.eur.ese.pbouman.towerbloxx;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.PriorityQueue;
import java.util.Set;
import java.util.stream.Collectors;

import com.carrotsearch.hppc.LongHashSet;
import com.carrotsearch.hppc.LongLongHashMap;
import com.carrotsearch.hppc.LongLongMap;
import com.carrotsearch.hppc.LongSet;
import com.carrotsearch.hppc.cursors.LongCursor;

public class TBSearch
{
	private TowerBloxx tb;
		
	// We use these 'special' collections from the hppc library as this saves memory
	private LongLongMap pred;
	private LongSet queue, expanded;
	
	private int depth;
	private long best;
	private long bestScore;
	private int bestCount;
	private long start;
	
	private List<Long> bestStates;

/**
 * Constructor for a TowerBloxx state search, assuming we start with an empty board
 * @param tb the TowerBloxx instance that will be used to search
 */
	
	public TBSearch(TowerBloxx tb)
	{
		this(tb,0l);
	}
	
	
	/**
	 * Constructor of a TowerBloxx state search where the starting state can be specified
	 * @param tb the TowerBloxx instance that will be searched
	 * @param start the starting state encoded as long
	 */
	public TBSearch(TowerBloxx tb, long start)
	{
		this.tb = tb;
		
		this.pred = new LongLongHashMap();
		this.queue = new LongHashSet();
		this.expanded = new LongHashSet();
		
		this.start = start;
		this.queue.add(start);
		this.bestScore = tb.computeScore(start);
		this.bestStates = new ArrayList<>();
	}
	
	/**
	 * Obtain the current size of the queue
	 * @return the current size of the queue
	 */
	public int getQueueSize()
	{
		return queue.size();
	}
	
	/**
	 * Performs a best first search, expanding unexplored states with the
	 * highest score first. Note that may not yield shortest paths to the
	 * best states found, and also provides no guarantee the optimal solution
	 * is found.
	 * @param iters The maximum number of iterations before stopping the algorithm
	 * @param maxQueue the maximum size of the queue of states that are considered for expansion
	 */
	public void doBestFirst(int iters, int maxQueue)
	{
		// Comparator that puts the state with the best score first
		Comparator<Long> comp = (l1,l2) -> (int)(tb.computeScore(l2) - tb.computeScore(l1));
		PriorityQueue<Long> pq = new PriorityQueue<Long>(comp);
		
		for (LongCursor lc : queue)
		{
			pq.add(lc.value);
		}
		
		long time = System.currentTimeMillis();
		for (int i=0; i < iters && !pq.isEmpty(); i++)
		{
			long state = pq.remove();
			for (long newState : tb.expand(state))
			{
				if (!pred.containsKey(newState))
				{
					pred.put(newState, state);
					pq.add(newState);
					long newScore = tb.computeScore(newState);
					if (newScore > bestScore)
					{
						best = newState;
						bestScore = newScore;
						bestCount = 1;
						bestStates.clear();
						bestStates.add(newState);
					}
					else if (newScore == bestScore)
					{
						bestCount++;
						bestStates.add(newState);
					}
				}				
			}
			if (System.currentTimeMillis() - time > 10000)
			{
				time = System.currentTimeMillis();
				System.out.println("Finished "+i+" iterations out of "+iters);
				System.out.println("Best score until now: "+bestScore);
				
			}
			if (maxQueue > 0 && pq.size() > maxQueue)
			{
				PriorityQueue<Long> newQ = new PriorityQueue<>(comp);
				for (int t=0; t < maxQueue; t++)
				{
					newQ.add(pq.remove());
				}
			}
		}
	}
	
	/**
	 * Performs a single step of a breadth-first-search algorithm
	 * @return Whether there are states left in the queue after this step
	 */
	public boolean stepBFS()
	{
		LongSet newQueue = new LongHashSet();
		// We iterate over all states currently in the queue
		for (LongCursor lc : queue)
		{
			long state = lc.value;
			Set<Long> expand = tb.expand(state);
			expanded.add(state);
			// We consider all states that can be reached from the current state in one step
			for (long newState : expand)
			{
				// If don't have a path to this state yet, it is new
				if (!pred.containsKey(newState))
				{
					pred.put(newState, state);
					newQueue.add(newState);
					// If the new state has a better solution than we currently have, perform an update
					long newScore = tb.computeScore(newState);
					if (newScore > bestScore)
					{
						best = newState;
						bestScore = newScore;
						bestCount = 1;
						bestStates.clear();
						bestStates.add(newState);
					}
					else if (newScore == bestScore)
					{
						bestStates.add(newState);
						bestCount++;
					}
				}
			}
		}
		depth++;
		queue = newQueue;
		System.out.println("Queue size at depth "+depth+" : "+queue.size());
		return !newQueue.isEmpty();
	}
	
	/**
	 * Repeats performing breadth-first-search steps until the depth is reached
	 * @param maxDepth the maximum depth of the breadth-first-search
	 */
	public void runBFS(int maxDepth)
	{
		while (depth < maxDepth && stepBFS()) {}
	}
	
	/**
	 * Obtain the path from the initial state to the state with the best score found.
	 * Note that states one this path may flip or rotate as a consequence of the way
	 * symmetric states are mapped to a canonical state.
	 * @return A list of step-by-step states 
	 */
	public List<String> getBestPath() {
		List<String> result = new ArrayList<>();
		long cur = best;
		while (cur != start)
		{
			result.add(tb.toGrid(cur));
			cur = pred.get(cur);
		}
		result.add(tb.toGrid(cur));
		Collections.reverse(result);
		return result;
	}
	
	/**
	 * Gets a list of all state that had the same score as the best state found
	 * @return a list of all best states found
	 */
	public List<String> getBestStates() {
		return bestStates.stream()
						 .map(l -> tb.toGrid(l))
						 .collect(Collectors.toList());
	}
	
	/**
	 * Returns the number of best states found
	 * @return the number of states found with a score equal to the best state found.
	 */
	public int getBestCount() {
		return bestCount;
	}
	
}
