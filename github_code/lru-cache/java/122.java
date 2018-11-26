package cacheReplacementTest;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;

@SuppressWarnings({"unused"})
public class LRU {

	//cache
	ArrayList<CacheItem> cache ;

	private int numTotalQueries = 0;
	private int numCacheHits = 0;

	private int cacheSize = 0;
	private int cacheUsed = 0;

	private TestSettings ts;

	public LRU(TestSettings ts)
	{
		this.ts = new TestSettings(ts);
		cache = new ArrayList<CacheItem>(ts.getCacheSize());
		this.cacheSize = ts.getCacheSize();
	}

	public void readQuery(Pair<Integer, Integer> query)
	{
		checkAndUpdateCache(query);
		numTotalQueries++;
	}

	public void readQueryList(ArrayList<Pair<Integer, Integer>> queryList)
	{
		for(Pair<Integer, Integer> q : queryList)
		{
			readQuery(q);
		}
	}

	public void checkAndUpdateCache(Pair<Integer, Integer> query)
	{
		boolean cacheHit = false;

		if(ts.isUseOptimalSubstructure()){
			for(CacheItem ci : cache)
			{
				if(ci.item.contains(query.s) && ci.item.contains(query.t))
				{
					numCacheHits++;
					ci.updateKey(numTotalQueries);
					Collections.sort(cache);
					cacheHit = true;
					break;
				}
			}
		}else{
			for(CacheItem ci : cache)
			{
				if(ci.s == query.s && ci.t == query.t)
				{
					numCacheHits++;
					ci.updateKey(numTotalQueries);
					Collections.sort(cache);
					cacheHit = true;
					break;
				}
			}
		}

		if(!cacheHit)
		{
			ArrayList<Integer> spResult = RoadGraph.getMapObject().dijkstraSSSP(query.s, query.t);
			int querySize = spResult.size();

			if(cache.size()!= 0 )
				insertItem(querySize, spResult, query.s, query.t);
			else
			{
				CacheItem e = new CacheItem(numTotalQueries, spResult, query.s, query.t);
				cache.add(e);
			}
		}
	}

	private void insertItem(int querySize, ArrayList<Integer> nodesInQueryResult, int startNode, int targetNode)
	{
		boolean notEnoughSpace = true;

		//inserts query into cache, will repeatedly remove items until there is enough space for
		do{
			if((cacheSize - cacheUsed) > querySize)
			{
				CacheItem e = new CacheItem(numTotalQueries, nodesInQueryResult, startNode, targetNode);
				cache.add(e);
				cacheUsed = cacheUsed + e.size;
				notEnoughSpace = false;
			}
			else if(querySize < cacheSize)
			{
				int itemSize = cache.remove(0).size; 
				cacheUsed = cacheUsed - itemSize;
			}
			else
				break;
		}while(notEnoughSpace);
	}

	public int getCacheHits(){return numCacheHits;}

	public int getTotalQueries(){return numTotalQueries;}
}
