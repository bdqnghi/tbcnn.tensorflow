package util;

import java.io.IOException;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

public class StringStringCSVFileCache extends CSVFileCache {
	
	private Map<String, String> strings;
	
	private Map<String, Set<String>> reverseStrings;
	
	public StringStringCSVFileCache(String fileLocation) throws IOException {
		super(fileLocation, Format.STRING, Format.STRING);
	}

	@Override
	protected void preParseInit() {
		strings = new HashMap<>();
		reverseStrings = new HashMap<>();
	}

	@Override
	protected final void processLine(CSVLine line) {
		processLine(line.getString(0), line.getString(1));
	}
	
	protected void processLine(String key, String value) {
		strings.put(key, value);
		if (!reverseStrings.containsKey(value))
			reverseStrings.put(value, new HashSet<String>());
		reverseStrings.get(value).add(key);
	}
	
	public boolean hasKey(String key) {
		return strings.containsKey(key);
	}
	
	public String get(String key) {
		return strings.get(key);
	}
	
	/**
	 * Returns a non-null set (can be empty) that is guaranteed to be unmodifiable.
	 */
	public Set<String> getKeys(String value) {
		if (!reverseStrings.containsKey(value)) {
			return Collections.emptySet();
		} else {
			return Collections.unmodifiableSet(reverseStrings.get(value));
		}
	}
	
	protected void put(String key, String val) {
		processLine(key, val);
		
		CSVLine line = new CSVLine();
		line.setString(0, key);
		line.setString(1, val);
		
		addLine(line);
	}

}
