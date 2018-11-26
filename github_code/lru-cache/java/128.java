package edu.umb.cs.cs681;
import java.io.File;
import java.io.FileNotFoundException;
import java.nio.file.Path;
import java.util.LinkedHashMap;
import java.util.Set;

public class LRU extends FileCache 
{

	private static LRU instance = null;
	private LRU(){}

	public static LRU getInstance()
	{
		if(instance == null)
		{
			instance = new LRU();
		}
		return instance;
	}
	
	
	@Override
	public void replace(LinkedHashMap<Path, String> cache, File targetFile) 
	{
		Path path = targetFile.toPath();
		String file = targetFile.toString();
		cache.remove(cache.get(4));
		cache.put(path, file);
		System.out.println("Cache Replaced by LRU");
		System.out.println(cache);
		
	}

	@Override
	public String fileFetch(String targetFile) throws FileNotFoundException {
		super.fetch(targetFile);
		return targetFile;
	}

}
