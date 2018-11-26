package lru_cache;

import org.junit.Test;

import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.Map;

import static org.junit.jupiter.api.Assertions.assertEquals;


public class LRUCache {
    /*
        LRU Cache naive double linked list + hashmap approach
        Leetcode #146
        https://leetcode.com/problems/lru-cache/
        Difficulty: Hard
        Double Linked List
     */
    public class LRUCache_1 {
        private HashMap<Integer, DoubleLinkedListNode> map;
        private DoubleLinkedListNode head;
        private DoubleLinkedListNode tail;
        private int capacity;

        public LRUCache_1(int capacity) {
            map = new HashMap<>();
            this.capacity = capacity;
        }

        public int get(int key) {
            if (!map.containsKey(key)) {
                return -1;
            }
            DoubleLinkedListNode node = map.get(key);
            removeNode(node);
            setHead(node);
            return node.val;
        }

        public void set(int key, int value) {
            if (map.containsKey(key)) {
                DoubleLinkedListNode node = map.get(key);
                removeNode(node);
                node.val = value;
                setHead(node);
            } else {
                DoubleLinkedListNode node = new DoubleLinkedListNode(key, value);
                setHead(node);
                map.put(key, node);
                if (map.size() >= capacity) {
                    map.remove(tail.key);
                    tail = tail.pre;
                    if (tail != null) {
                        tail.next = null;
                    }
                }
            }
        }

        private void removeNode(DoubleLinkedListNode node) {
            if (node.pre != null) {
                node.pre.next = node.next;
            } else {
                head = node.next;
            }
            if (node.next != null) {
                node.next.pre = node.pre;
            } else {
                tail = node.pre;
            }
        }

        private void setHead(DoubleLinkedListNode node) {
            node.next = head;
            node.pre = null;
            if (head != null) {
                head.pre = node;
            }
            head = node;
            if (tail == null) {
                tail = node;
            }
        }
    }

    class DoubleLinkedListNode {
        public int val;
        public int key;
        public DoubleLinkedListNode pre;
        public DoubleLinkedListNode next;

        public DoubleLinkedListNode(int key, int val) {
            this.val = val;
            this.key = key;
        }
    }

    /*
        LRU Cache using - Using LinkedHashMap
        Leetcode #146
        https://leetcode.com/problems/lru-cache/
        Difficulty: Hard
        LinkedHashMap
     */
    public class LRUCache_2 {
        private Map<Integer, Integer> map;
        private int capacity;

        public LRUCache_2(int capacity) {
            this.capacity = capacity;
            map = new LinkedHashMap<>(capacity + 1);
        }

        public int get(int key) {
            Integer val = map.get(key);
            if (val == null) {
                return -1;
            }
            map.remove(key);
            map.put(key, val);
            return val;
        }

        public void set(int key, int value) {
            map.remove(key);
            map.put(key, value);
            if (map.size() > capacity) {
                map.remove(map.keySet().iterator().next());
            }
        }
    }

    public static class UnitTest {
        @Test
        public void test1() {
            LRUCache_1 lru = new LRUCache().new LRUCache_1(5);
            lru.set(1, 1);
            lru.set(2, 2);
            lru.set(3, 3);
            lru.set(4, 4);
            assertEquals(lru.get(4), 4);
            assertEquals(lru.get(6), -1);
            lru.set(5, 5);
            lru.set(6, 6);
            assertEquals(lru.get(6), 6);
            assertEquals(lru.get(1), -1);
        }

        @Test
        public void test2() {
            LRUCache_2 lru = new LRUCache().new LRUCache_2(5);
            lru.set(4, 4);
            lru.set(3, 3);
            lru.set(2, 2);
            lru.set(1, 1);
            assertEquals(lru.get(4), 4);
            assertEquals(lru.get(6), -1);
            lru.set(6, 6);
            lru.set(5, 5);
            assertEquals(lru.get(6), 6);
            assertEquals(lru.get(3), -1);
        }
    }
}



