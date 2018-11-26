package com.bear.newcoder.ctrip;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.Map;

public class LRU {
	public static void main(String[] args) throws IOException {

		ArrayList<Integer> list = new ArrayList<>();
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		int size = Integer.parseInt(reader.readLine());
		LRUCache<Integer, Integer> cache = init(size);
		String readLine=null;
		while ((readLine = reader.readLine().trim()) != null) {
			String[] split = readLine.split(" ");
			switch (split[0]) {
			case "p":
				put(Integer.parseInt(split[1]), Integer.parseInt(split[2]), cache);
				break;

			case "g":
				get(Integer.parseInt(split[1]), cache, list);
				break;
			}
		}
		for (Integer integer : list) {
			System.out.println(integer);
		}
	}

	public static LRUCache<Integer, Integer> init(int size) {
		return new LRUCache<>(size);
	}

	public static void put(int key, int value, LRUCache<Integer, Integer> cache) {
		cache.put(key, value);
	}

	public static void get(int key, LRUCache<Integer, Integer> cache, ArrayList<Integer> list) {
		if (cache.get(key) == null) {
			list.add(-1);
		} else {
			list.add(cache.get(key));
		}
	}

	private static class LRUCache<K, V> extends LinkedHashMap<K, V> {
		private int cacheSize; // 缓存值大小

		public LRUCache(int cacheSize) {
			super(16, (float) 0.75, true); // true设置按照访问顺序排序
			this.cacheSize = cacheSize;
		}

		protected boolean removeEldestEntry(Map.Entry<K, V> eldest) {
			return size() > cacheSize; // 如果LinkedHashMap的大小超过缓存值，返回true删除最早的数据
		}
	}
}
