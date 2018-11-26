
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class LRU 
{
	private Trace trace;
	private long cacheSize;
	private List<Long> cacheList;
	private Set<Long> cacheListH;
	private long numHits;
	private long numMisses;
	
	public LRU (String traceFileName, long size)
	{
		cacheSize = size;
		trace = new Trace (traceFileName);
		cacheList = new ArrayList<Long>();
		cacheListH = new HashSet<Long>();
		numHits=0;
		numMisses=0;
		
		for(long address: trace.getAddresses())
		{
			request(address);
		}
		
		System.out.println("\n\nPolicy = LRU Cache Size = " + cacheSize + "  Tracefile = " + traceFileName);
		System.out.println("Num Hits = " + numHits);
		System.out.println("Num Misses = " + numMisses);
		System.out.println("Num Access = " + (numHits + numMisses));
		System.out.println("Hit Ratio = " + (double) numHits/(numHits + numMisses));

	}
	
	private void request (long address)
	{
		if(cacheListH.contains(address))
		{
			numHits++;
			cacheList.remove(address);
			cacheList.add(0, address);
		}
		
		else
		{
			numMisses++;
			if(cacheList.size() == cacheSize)
			{
				long l = cacheList.remove(cacheList.size() -1);
				cacheListH.remove(l);
				
			}
			cacheList.add(0, address);
			cacheListH.add(address);
		}
		
	}
	
	public static void main (String args[])
	{
		try
		{
			if (args.length < 2)
			{
				System.out.println("Invalid arguments");
			}
			int cacheSize = Integer.parseInt(args[0]);
			String fileName = args[1] + ".lis";
			new LRU (fileName, cacheSize);
		}
		catch (Exception e)
		{
			System.out.println(e);
			System.exit(1);
		}
	}
}

