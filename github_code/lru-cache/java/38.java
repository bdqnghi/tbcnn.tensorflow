package com.robin3;

import java.util.HashMap;

public class LRUCache {
	class Point{
        Point left;
        Point right;
        Integer key;
        Integer value;
        public Point(int key,int value){
        		this.key=key;
            this.value=value;
        }
    }
    HashMap<Integer,Point> map=new HashMap<Integer,Point>();
    Point start;
    Point end;
    int cap=0;
    public LRUCache(int capacity) {
        cap=capacity;
        Point dhead=new Point(0,0);
        Point dend=new Point(0,0);
        start=dhead;
        end=dend;
        start.right=end;
        end.left=start;
    }
    
    public int get(int key) {
        if(map.containsKey(key)){
            Point tp=map.get(key);
            liftFront(tp);
            //showLink();
            return map.get(key).value;
        }
        else
            return -1;
    }
    
    public void set(int key, int value) {
    		if(cap==0)
    				return;
    		//System.out.println("setting "+key+","+value+" size:"+map.size());
        if(map.containsKey(key)){
            Point tp=map.get(key);
            liftFront(tp);
            tp.value=value;
        }
        else{
            //check size
            int size=map.size();
            if(size>=cap){
            		Integer endkey=end.left.key;
            		end.left.left.right=end;
            		//System.out.println("end key="+endkey);
            		end.left=end.left.left;
            		map.remove(endkey);
            }
            Point newp=new Point(key,value);
            map.put(key,newp);
            liftFront(newp);
        }
       // showLink();
    }
    private void liftFront(Point p){
        if(p.left!=null)
            p.left.right=p.right;
        if(p.right!=null)
            p.right.left=p.left;
        p.right=start.right;
        if(start.right!=null)
            start.right.left=p;
        start.right=p;
        p.left=start;
    }
    private void showLink(){
    		Point tmp=start;
    		System.out.println("Showing linke");
    		while(tmp!=null){
    			System.out.print(tmp.key+":"+tmp.value+"\t");
    			tmp=tmp.right;
    		}
    		System.out.println();
    }
	public static void main(String[] args) {
		LRUCache lru=new LRUCache(3);
		lru.set(1, 1);
		lru.set(2, 2);
		lru.set(3, 3);
		lru.get(1);
		lru.set(4, 4);
		System.out.println("\n\n");
		System.out.println(lru.get(1));
		System.out.println(lru.get(2));
		System.out.println(lru.get(3));
		System.out.println(lru.get(4));
		
	}

}
