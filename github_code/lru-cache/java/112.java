package edu.umb.cs.cs680.hw07;

import java.util.HashMap;
import java.util.Iterator;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class LRU implements CacheReplacementPolicy {

	public HashMap<String, File> replace(HashMap<String,File> cache, String targetFile) {
		Iterator<String> iterator = cache.keySet().iterator();
		long lastFoundMin = System.nanoTime();
		String rem = "";
		while(iterator.hasNext()) {
			String str1 = iterator.next();
			if(cache.get(str1).getLastUsed() < lastFoundMin)
			{
				lastFoundMin = cache.get(str1).getLastUsed();
				rem = str1;
			}
		}
		cache.remove(rem);
		String data = "";
		try{
			FileReader fileReader = new FileReader(targetFile);
			BufferedReader bufferedReader = new BufferedReader(fileReader);
			data = bufferedReader.readLine();
		}
			catch (IOException e) {
				e.printStackTrace();
		}
		long ts = System.currentTimeMillis();
		File file= new File(data, ts,ts);
		cache.put(targetFile, file);
		return cache;
	}
}
