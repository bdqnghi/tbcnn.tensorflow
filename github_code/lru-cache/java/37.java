package others.hard;

import java.util.HashMap;
import java.util.Map;

/**
 * <p>
 * 背景描述：
 * <a href="https://leetcode.com/problems/lru-cache/description/" />
 * 146. LRU Cache
 * Design and implement a data structure for Least Recently Used (LRU) cache. It should support the following operations: get and put.

 get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
 put(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.

 Follow up:
 Could you do both operations in O(1) time complexity?

 Example:

 LRUCache cache = new LRUCache( 2 /* capacity  );

        cache.put(1, 1);
        cache.put(2, 2);
        cache.get(1);       // returns 1
        cache.put(3, 3);    // evicts key 2
        cache.get(2);       // returns -1 (not found)
        cache.put(4, 4);    // evicts key 1
        cache.get(1);       // returns -1 (not found)
        cache.get(3);       // returns 3
        cache.get(4);       // returns 4
 * <p>
 * 0. 本质：
 * 集合、序列
 * 1. 建模：
 * LRU是Least Recently Used的缩写，即最近最少使用页面置换算法，是为虚拟页式存储管理服务的，是根据页面调入内存后的使用情况进行决策了。
 * 由于无法预测各页面将来的使用情况，只能利用“最近的过去”作为“最近的将来”的近似，因此，LRU算法就是将最近最久未使用的页面予以淘汰。
 * 参考https://leetcode.com/problems/lru-cache/discuss/
 *
 * 2. 算法范式：
 * 3. 算法：
 * 4. 数据结构：
 * hashMap+doubly-linked list=LinkedHashMap
 * 双端队列优点：一个节点的删除很容易做到
 *
 * 双端队列，注意使用头尾哨兵
 * 5. 改进：
 * 6. 启发：
 * 7. jdk知识：
 * <p>
 * <a href="dhshenchanggan@163.com" />
 *
 * @author changgan on 19/09/2017
 * @see
 * @since cgs-leetcode on  19/09/2017
 */
public class LRUCache {
    DoubleLinkedNode head;
    DoubleLinkedNode tail;
    Map<Integer, DoubleLinkedNode> cache;
    int capacity;
    public LRUCache(int capacity) {
        this.head = new DoubleLinkedNode(-1, -1);
        this.tail = new DoubleLinkedNode(-1, -1);
        this.cache = new HashMap();
        this.capacity = capacity;

        head.next = tail;
        tail.pre = head;
    }

    public int get(int key) {
        if(!cache.containsKey(key)) {
            return -1;
        } else {
            DoubleLinkedNode node = cache.get(key);
            updatePosition(node);
            return node.value;
        }
    }

    private void updatePosition(DoubleLinkedNode node) {
        node.pre.next = node.next;
        node.next.pre = node.pre;

        node.pre = head;
        node.next = head.next;

        head.next.pre = node;
        head.next = node;
    }

    // add
    private void add(DoubleLinkedNode node) {
        node.next = head.next;
        node.pre = head;

        head.next.pre = node;
        head.next = node;
        cache.put(node.key, node);
    }

    private void deleteLast() {
        DoubleLinkedNode preNode = tail.pre;
        cache.remove(preNode.key);

        tail.pre = preNode.pre;
        preNode.pre.next = tail;

        preNode.pre = null;
        preNode.next = null;
    }

    public void put(int key, int value) {
        if(cache.containsKey(key)) {
            DoubleLinkedNode node = cache.get(key);
            node.value = value;
            updatePosition(node);
        } else {
            if(cache.size() >= capacity) {
                // delete
                deleteLast();
            }
            // add
            DoubleLinkedNode node = new DoubleLinkedNode(key, value);
            add(node);
        }
    }

    class DoubleLinkedNode {
        int key;
        int value;
        DoubleLinkedNode pre;
        DoubleLinkedNode next;
        DoubleLinkedNode(int key, int value) {
            this.key = key;
            this.value = value;
        }
    }
}
