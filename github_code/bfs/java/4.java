package nl.eur.ese.pbouman.towerbloxx;

import java.io.File;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.Map;
import java.util.PriorityQueue;
import java.util.Set;
import java.util.stream.Collectors;

import org.mapdb.DB;
import org.mapdb.DBMaker;
import org.mapdb.Serializer;

import com.carrotsearch.hppc.LongHashSet;
import com.carrotsearch.hppc.LongLongHashMap;
import com.carrotsearch.hppc.LongLongMap;
import com.carrotsearch.hppc.LongSet;
import com.carrotsearch.hppc.cursors.LongCursor;

public class TBSearchMapDB implements AutoCloseable
{
	
	private final static int BTREE_NODE_SIZE = 1000000;
	private TowerBloxx tb;
		
	// We use these 'special' collections from the hppc library as this saves memory
	private DB db;
	private Map<Long,Long> pred;
	private Set<Long> queue, expanded, tempQueue, bestStates;
	
	private int depth;
	private long best;
	private long bestScore;
	private int bestCount;
	private long start;

/**
 * Constructor for a TowerBloxx state search, assuming we start with an empty board
 * @param tb the TowerBloxx instance that will be used to search
 * @param dbFile the file in which the database of the search process will be stored
 */
	
	public TBSearchMapDB(TowerBloxx tb, File dbFile)
	{
		this(tb,0l,dbFile);
	}
	
	
	/**
	 * Constructor of a TowerBloxx state search where the starting state can be specified
	 * @param tb the TowerBloxx instance that will be searched
	 * @param start the starting state encoded as long
	 * @param dbFile the file in which the database will be stored
	 */
	public TBSearchMapDB(TowerBloxx tb, long start, File dbFile)
	{
		this.tb = tb;
		
		this.db = DBMaker
			      .fileDB(dbFile)
			      .fileMmapEnable()            // Always enable mmap
			      .fileMmapEnableIfSupported() // Only enable mmap on supported platforms
			      .fileMmapPreclearDisable()
			      .make();
		
		this.pred = db.treeMap("predessor", Serializer.LONG, Serializer.LONG).maxNodeSize(BTREE_NODE_SIZE).create();
		this.queue = db.treeSet("queue", Serializer.LONG).maxNodeSize(BTREE_NODE_SIZE).create();
		this.expanded = db.treeSet("expanded", Serializer.LONG).maxNodeSize(BTREE_NODE_SIZE).create();
		this.tempQueue = db.treeSet("queueTemp", Serializer.LONG).maxNodeSize(BTREE_NODE_SIZE).create();
		this.bestStates = db.treeSet("best", Serializer.LONG).maxNodeSize(BTREE_NODE_SIZE).create();
		
		this.start = start;
		this.queue.add(start);
		this.bestScore = tb.computeScore(start);
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
	 * Performs a single step of a breadth-first-search algorithm
	 * @return Whether there are states left in the queue after this step
	 */
	public boolean stepBFS()
	{
		tempQueue.clear();
		// We iterate over all states currently in the queue
		for (Long state : queue)
		{
			Set<Long> expand = tb.expand(state);
			expanded.add(state);
			// We consider all states that can be reached from the current state in one step
			for (long newState : expand)
			{
				// If don't have a path to this state yet, it is new
				if (!pred.containsKey(newState))
				{
					pred.put(newState, state);
					tempQueue.add(newState);
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
						bestCount++;
						bestStates.add(newState);
					}
				}
			}
		}
		depth++;
		Set<Long> tmp = queue;
		queue = tempQueue;
		tempQueue = tmp;
		System.out.println("Queue size at depth "+depth+" : "+queue.size());
		return !queue.isEmpty();
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


	@Override
	public void close()
	{
		db.close();
	}
	
}
