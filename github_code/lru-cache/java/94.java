package datastructure.linear;

import java.util.HashMap;
import java.util.Map;

/**
 * LRU Cache implementation
 * Created by Bikash on 4/13/2017.
 */

class LRUNode {
    String key;
    int value;
    LRUNode back;
    LRUNode next;

    public LRUNode(String key, int value) {
        this.key = key;
        this.value = value;
    }

    @Override
    public String toString() {
        return "LRUNode{" +
                "key='" + key + '\'' +
                ", value=" + value +
                '}';
    }
}

public class LRUCache {
    private Map<String, LRUNode> cache;
    private LRUNode head;
    private LRUNode tail;

    private int capacity;

    public LRUCache(int capacity) {
        cache = new HashMap<>(capacity);
        this.capacity = capacity;

    }

    public LRUNode get(String key) {
        return cache.get(key);
    }

    public LRUNode put(String key, int value) {
        LRUNode lruNode;
        if (cache.size() < capacity) { //cache is not full
            if (cache.isEmpty()){
                lruNode = new LRUNode(key, value);
                lruNode.back = null;
                lruNode.next = null;
                head = lruNode;
                tail = lruNode;
                cache.put(key, lruNode);
            } else if (head == tail) { //only one lruNode
                if (cache.containsKey(key)){ //same key
                    lruNode = cache.get(key);
                    lruNode.value = value;
                } else { //new key
                    lruNode = new LRUNode(key, value);
                    lruNode.back = null;
                    lruNode.next = tail;
                    head = lruNode;
                    tail.back = head;
                    cache.put(key,lruNode);
                }
            } else { // multiple nodes
                if (cache.containsKey(key)) { //key already in cache
                    lruNode = cache.get(key);
                    if(lruNode == head) { //if key belongs to head lruNode
                        lruNode.value = value;
                    } else if (lruNode == tail) { // if key belongs to tail lruNode
                        moveTailToHead(value, lruNode);
                    } else { // if key belongs to any other lruNode
                        movedToHead(value, lruNode);
                    }
                } else { // new key
                    lruNode = new LRUNode(key, value);
                    lruNode.back = null;
                    lruNode.next = head;
                    head.back = lruNode;
                    head = lruNode;

                    cache.put(key,lruNode);

                }
            }
        } else { //Cache is full
            if(cache.containsKey(key)) {
                lruNode = cache.get(key);
                if(lruNode == head) {
                    lruNode.value = value;
                } else if(lruNode == tail) {
                    moveTailToHead(value, lruNode);
                } else {
                    movedToHead(value, lruNode);
                }

            } else { //Evict
                LRUNode newTail = tail.back;
                lruNode = new LRUNode(key, value);
                lruNode.back = null;
                lruNode.next = head;
                head.back = lruNode;
                head = lruNode;
                cache.remove(tail.key);
                tail = newTail;
                tail.next = null;
                cache.put(key, lruNode);
            }

        }
        return lruNode;
    }

    private void moveTailToHead(int value, LRUNode node) {
        node.value = value;
        LRUNode newTail = tail.back;
        node.next = head;
        head = node;
        head.back = null;
        tail = newTail;
        tail.next = null;
        if(tail.back == null) {
            tail.back = head;
        }
    }

    private void movedToHead(int value, LRUNode node) {
        node.value = value;
        LRUNode next = node.next;
        LRUNode back = node.back;
        back.next = next;
        next.back = back;
        node.next = head;
        node.back = null;
        head = node;
    }

    private void printAll() {
        LRUNode temp = this.head;

        while (temp != null) {
            System.out.print(temp + " ");
            temp = temp.next;
        }
        System.out.println();
    }



    public static void main(String[] args) {
        LRUCache lruCache = new LRUCache(4);
        lruCache.put("A", 1);
        lruCache.printAll(); //1
        lruCache.put("B", 2);
        lruCache.printAll(); //2
        lruCache.put("A", 3);
        lruCache.printAll(); //2
        lruCache.put("C", 4);
        lruCache.printAll(); //3
        lruCache.put("D", 5);
        lruCache.printAll(); //4
        lruCache.put("C", 6);
        lruCache.printAll(); //4
        lruCache.put("E", 7);
        lruCache.printAll(); //4
        lruCache.put("F", 8);
        lruCache.printAll();  //4
    }
}
