import java.io.File;
import java.util.LinkedList;
import java.util.Map.Entry;
import java.util.concurrent.ConcurrentHashMap;

/**
 * MRU -----------------LRU
 * @author danc
 *
 */
public class LRU {
	public ConcurrentHashMap<String,CacheInfo> cacheMap;
	public LinkedList<String> cacheList;
	public int cacheSize;
	public int cacheSizeLimit;
	
	private void printCache() {
		System.err.println("~~~~~~~IN cache ~~~~~~");
		for(Entry<String, CacheInfo> s:cacheMap.entrySet()) {
			System.err.println("cache in map "+s.getKey()+" cache path: "+s.getValue().cachePathName);
		}
		System.err.println("~~~~~~~end of cache ~~~~~~");
	}
	public ConcurrentHashMap<String,CacheInfo> getMap() {
		return this.cacheMap;
	}
	
	private int evict(int currCacheSize) {
		System.err.println("LRU evict ...");
		int listIndex = cacheList.size() - 1;
		while (currCacheSize > this.cacheSizeLimit) {
			System.err.println("curSize:"+currCacheSize+" limit:"+this.cacheSizeLimit);
			
			if (listIndex < 0) { //cannot make enough space
				System.err.println("Cannot make enough space");
				return -1;
			}
			String lruCache = cacheList.get(listIndex);
			CacheInfo cInfo = cacheMap.get(lruCache);
			System.err.println("Try to evict index " +listIndex + " path" +lruCache);
			if (!cInfo.isUsing.get()) { //not in use we can evict it
				System.err.println("Remove cache path:"+lruCache);
				currCacheSize = currCacheSize - cInfo.size;
				System.err.println("curr size now"+currCacheSize);
				File rmFile = new File(cInfo.cachePathName);
				rmFile.delete();
				cacheList.remove(lruCache);
				cacheMap.remove(lruCache);
			}
			listIndex--;
			
		}
		//printCache();
		return currCacheSize;
	}
	
	//For Open
	public boolean add(String path,CacheInfo cInfo) {
		//isUsing true
		System.err.println("......Adding path to cache:" + path);
		int currCacheSize = this.cacheSize+cInfo.size;
		//Evict to make space for new cache
		if (currCacheSize > this.cacheSizeLimit) {
			int size = evict(currCacheSize);
			if (size == -1) {
				return false; //all cache in use, cannot make enough space
			}
			this.cacheSize = size;
		}
		else {
			this.cacheSize = currCacheSize;
		}
		
		cInfo.isUsing.set(true); 
		this.cacheList.add(path);
		this.cacheMap.put(path, cInfo);
		System.err.println("......size of cache now:" + this.cacheSize);
		//printCache();
		return true;
	}

	//For Close
	public boolean move2MRU(String path, CacheInfo cInfo) {
		System.err.println(".....Move 2 MRU...before");
		for (String s:this.cacheList) {
			System.err.println("cache in list"+s);
		}
		if (cacheList.contains(path)) {
			cInfo.isUsing.set(false);
			cacheList.remove(path);
			cacheMap.remove(path);			
		}
		else {
			System.err.println(" should never get here");
			return false;
		}
		cacheList.addFirst(path);
		cacheMap.put(path, cInfo);
		System.err.println(".....Move 2 MRU...after");
		for (String s:this.cacheList) {
			System.err.println("cache in list"+s);
		}
		//printCache();
		return true;
	}
	
	public LRU(int limit) {
		System.err.println("New LRU");
		this.cacheMap = new ConcurrentHashMap<String,CacheInfo>();
		this.cacheList = new LinkedList<String>();
		this.cacheSize = 0;
		this.cacheSizeLimit = limit;
	}
	public void using(String path) {
		CacheInfo c = this.cacheMap.get(path);
		c.isUsing.set(true); 
		cacheMap.replace(path, c);
		
	}
	public boolean delete(String path) {
		System.err.println("Delete in cache");
		if (cacheList.contains(path)) {
			System.err.println("In cache");
			CacheInfo c = cacheMap.get(path);
			if (!c.isUsing.get()) {
				System.err.println("cachePathName" + c.cachePathName);
				File f = new File(c.cachePathName);
				System.err.println("remove this file:"+c.cachePathName);
				cacheList.remove(path);
				cacheMap.remove(path);
				return f.delete();
			}
			System.err.println("File in use, cannot delete");
			return false;
		}
		System.err.println("Not in cache....");
		return true;
		
	}
	
	/*public static void main(String[] args) {
		LRU l = new LRU(10);

		CacheInfo a = new CacheInfo("ac", 0, false,true,3);
		CacheInfo b = new CacheInfo("bc", 0, false,true,3);
		CacheInfo c = new CacheInfo("cc", 0, false,false,3);
		CacheInfo d = new CacheInfo("dc", 0, false,true,3);
		l.add("a",a);
		//l.move2MRU("a");
		l.add("b",b);
		l.move2MRU("b",b);
		l.add("c",c);
		l.move2MRU("c",c);
		l.add("d",d);	
		l.move2MRU("d",d);
	}*/
	
}
