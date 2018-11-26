package cn.jsi.buaa;

import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;

public class LRUCache {
	int n;
	HashMap<Integer, Integer> valuemap = new HashMap<Integer, Integer>();
	LinkedList<Integer> usedlist = new LinkedList<Integer>();
	public LRUCache(int capacity) {
		this.n = capacity;
	}

	public int get(int key) {
		if (valuemap.containsKey(key)) {
			usedlist.addFirst(key);
			return valuemap.get(key);
		} else{
			return -1;
		}
	}
	//clear all the duplicated value in the list
	public void clearlist(){
	    LinkedList<Integer> tlist=new LinkedList<Integer> ();
	    HashSet<Integer> usedset=new HashSet<Integer>();
	    for(Integer i:usedlist){
	        if(!usedset.contains(i)){
	            usedset.add(i);
	            tlist.add(i);
	            if(tlist.size()==n)
	            	break;
	        }
	    }
	    usedlist.clear();
	    usedlist=tlist;
	}

	public void set(int key, int value) {
		if (valuemap.containsKey(key) ||valuemap.size() < n) {
			valuemap.put(key, value);
			usedlist.addFirst(key);
			return;
		}
		//valuemap.size()==n && !valuemap.containsKey(key)
		//you should update the list now
		clearlist();
		int removedkey = usedlist.getLast();
		usedlist.removeLast();
		valuemap.remove(removedkey);
		valuemap.put(key, value);
		return;
	}

	
	public static void main(String[] args) {
		LRUCache lu = new LRUCache(10);
		lu.set(10, 13);
		lu.set(3, 17);
		lu.set(6, 11);
		lu.set(10, 5);
		lu.set(9, 10);
		lu.get(13);
		lu.set(2, 19);
		lu.get(2);
		lu.get(3);
		lu.set(5, 25);
		lu.get(8);
		lu.set(9, 22);
		lu.set(5, 5);
		lu.set(1, 30);
		lu.get(11);
		lu.set(9, 12);
		lu.get(7);
		lu.get(5);
		lu.get(8);
		lu.get(9);
		lu.set(4, 30);
		lu.set(9, 3);
		lu.get(9);
		System.out.println("\n\n\n");
		lu.get(10);
		lu.get(10);
		lu.set(6, 14);
		lu.set(3, 1);
		lu.get(3);
		lu.set(10, 11);
		lu.get(8);
		lu.set(2, 14);
		lu.get(1);
		lu.get(5);
		lu.get(4);
		lu.set(11, 4);
		lu.set(12, 24);
		lu.set(5, 18);
		lu.get(13);
		lu.set(7, 23);
		lu.get(8);
		lu.get(12);
		lu.set(3, 27);
		lu.set(2, 12);
		lu.get(5);
		lu.set(2, 9);
		lu.set(13, 4);
		lu.set(8, 18);
		lu.set(1, 7);
		lu.get(6);
		lu.set(9, 29);
		lu.set(8, 21);
		lu.get(5);
		lu.set(6, 30);
		lu.set(1, 12);
		lu.get(10);
		lu.set(4, 15);
		lu.set(7, 22);
		lu.set(11, 26);
		lu.set(8, 17);
		lu.set(9, 29);
		lu.get(5);
		lu.set(3, 4);
		lu.set(11, 30);
		lu.get(12);
		lu.set(4, 29);
		lu.get(3);
		lu.get(9);
		lu.get(6);
		lu.set(3, 4);
		lu.get(1);
		lu.get(10);
		lu.set(3, 29);
		lu.set(10, 28);
		lu.set(1, 20);
		lu.set(11, 13);
		lu.get(3);
		lu.set(3, 12);
		lu.set(3, 8);
		lu.set(10, 9);
		lu.set(3, 26);
		lu.get(8);
		lu.get(7);
		lu.get(5);
		lu.set(13, 17);
		lu.set(2, 27);
		lu.set(11, 15);
		lu.get(12);
		lu.set(9, 19);
		lu.set(2, 15);
		lu.set(3, 16);
		lu.get(1);
		lu.set(12, 17);
		lu.set(9, 1);
		lu.set(6, 19);
		lu.get(4);
		lu.get(5);
		lu.get(5);
		lu.set(8, 1);
		lu.set(11, 7);
		lu.set(5, 2);
		lu.set(9, 28);
		lu.get(1);
		lu.set(2, 2);
		lu.set(7, 4);
		lu.set(4, 22);
		lu.set(7, 24);
		lu.set(9, 26);
		lu.set(13, 28);
		lu.set(11, 26);
		
	}


}
