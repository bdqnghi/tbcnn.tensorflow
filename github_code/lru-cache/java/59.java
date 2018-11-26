package imageCache;

import java.io.BufferedInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.URL;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Scanner;

/**
 * LRU cache
 *
 */
public class LRU {
	HashMap<Object, Node> map;
	double cacheSizeLimit;
	Node head;
	Node end;
	
	public LRU(double cacheSizeLimit) {
		this.cacheSizeLimit = cacheSizeLimit;
		this.head = this.end = null;
		map = new HashMap<Object, Node>();
	}
	
	/**
	 * get(key) - Get the value of the key if the key exists in the cache,
	 * otherwise return null.
	 * 
	 * @param key
	 * @return
	 */
	public Object getKey(Object key) {
		if (map.containsKey(key)) {
			Node node = map.get(key);
			remove(node);
			setHead(node);
			return node;
		}		
		return null;
	}
	
	private void remove(Node node) {
		if (node.pre != null) {
			node.pre.next = node.next;
		} else {
			head = node.next;
		}
		
		if (node.next != null) {
			node.next.pre = node.pre;
		} else {
			end = node.pre;
		}
	}
	
	private void setHead(Node node) {
		node.next = head;
		node.pre = null;
		
		if (head != null) {
			head.pre = node;
		}
		
		head = node;
		
		if (end == null) {
			end = head;
		}
	}
	
	/**
	 * set(key, value) - Set or insert the value if the key is not already present.
	 * When the cache reached its capacity, it should invalidate the least recently
	 * used item before inserting a new item.
	 * 
	 * @param key
	 * @param value
	 */
	public void setKey(Object key, Object value, double size) {
		if (map.containsKey(key)) {
			Node old = map.get(key);
			old.value = value;
			remove(old);
			setHead(old);
		} else {		
			Node created = new Node(key, value, size);
			cacheSizeLimit -= size;
			while(cacheSizeLimit < 0) {
				map.remove(end.key);
				cacheSizeLimit += end.size;
				remove(end);
			}
			setHead(created);
			map.put(key, created);
		}
	}
	
	public void processUrls(List<String> urls) throws IOException {
		for (int i = 0; i < urls.size(); i++) {
			String urlStr = urls.get(i);
			Node node = (Node)getKey(urlStr);
			if ( node != null) {
				System.out.println(urlStr + " " + "IN_CACHE" + " " + node.size);
			} else {
				URL url = new URL(urlStr);
				InputStream in = new BufferedInputStream(url.openStream());
				ByteArrayOutputStream out = new ByteArrayOutputStream();
				byte[] buf = new byte[1024];
				int n = 0;
				while (-1 != (n = in.read(buf))) {
					out.write(buf, 0, n);
				}
				out.close();
				in.close();
				byte[] response = out.toByteArray();
				setKey(urlStr, response, response.length);
				System.out.println(urlStr + " " + "DOWNLOADED" + " " + response.length);
			}		
		}
	}
	
	public static void main(String[] args) throws IOException {
		// To read from stdin:
        InputStream source = System.in; 
        Scanner in = new Scanner(source);
        
        LRU cache = null;
        if (in.hasNext()) {
        	double cacheCapacity = Double.parseDouble(in.nextLine());
            cache = new LRU(cacheCapacity);
        }
        
        int urlSize = 0;
        if (in.hasNext()) {
        	urlSize = Integer.parseInt(in.nextLine());
        }
        
        List<String> urls = new ArrayList<>();
        int urlCount = 0;
        while(urlCount < urlSize){
            urls.add(in.nextLine());
            urlCount++;
        }
        
        cache.processUrls(urls);      
	}
}
