package com.robin4;

import java.util.HashMap;

/**
 * Created by robinmac on 15-9-14.
 */
public class LRUCache {
    class Entry{
        Entry left,right;
        Integer key;
        Integer value;
        public Entry(Integer key,Integer value){
            this.key=key;
            this.value=value;
        }
        public void setValue(Integer value){
            this.value=value;
        }
    }

    HashMap<Integer,Entry> map=new HashMap<Integer,Entry>();

    int size=0;
    int maxSize=-1;

    Entry dhead=new Entry(-1,-1);
    Entry tail=new Entry(-1,-1);

    public LRUCache(int capacity) {
        maxSize=capacity;
        dhead.right=tail;
        tail.left=dhead;
    }

    public int get(int key) {
        Entry ent=map.get(key);
        if(ent==null)
            return -1;
        int returnValue=ent.value;
        add2Head(ent);
        checkSize();
        return returnValue;
    }

    public void set(int key, int value) {
        Entry ent=map.get(key);
        if(ent==null){
            ent=new Entry(key,value);
            map.put(key,ent);
            size++;
        }
        ent.setValue(value);
        add2Head(ent);
        checkSize();
    }

    private void add2Head(Entry ent){
        //break old
        if(ent.left!=null)
            ent.left.right=ent.right;
        if(ent.right!=null)
            ent.right.left=ent.left;
        //add to dhead
        dhead.right.left=ent;
        ent.right=dhead.right;
        dhead.right=ent;
        ent.left=dhead;
    }
    private void checkSize(){
        if(size<=maxSize)
            return;
        Entry re=tail.left;
        tail.left=re.left;
        re.left.right=tail;
        map.remove(re.key);
        size--;
    }

    private void showEntry(){
        Entry p=dhead;
        while(p!=null) {
            System.out.print(p.key + ":" + p.value+"\t");
            p=p.right;
        }
        System.out.println();
    }
    public static void main(String[] args) {
        LRUCache lru=new LRUCache(2);
        lru.showEntry();
        lru.set(2, 1);
        lru.set(3,2);
        lru.showEntry();
        lru.get(3);
        lru.get(2);
        lru.showEntry();
        lru.set(4, 3);
        lru.showEntry();
        lru.get(2);
        lru.showEntry();
        lru.get(3);
        lru.get(4);


    }
}
