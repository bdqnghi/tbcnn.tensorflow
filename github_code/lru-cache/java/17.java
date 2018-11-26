package cache;

import java.util.HashMap;
import java.util.LinkedList;
import java.util.Map;

/**
 * Simple implementation of an LRU cache that uses a double linked list for
 * eviction scheduling and a hashmap for guaranteeing O(1) get/put
 * @param <K> type of the keys
 * @param <V> type of the values
 */
public class LRU<K,V> {
  private int capacity;

  private class Node {
    public K key;
    public V value;

    public Node(K key, V value) {
      this.key = key;
      this.value = value;
    }
  }

  private LinkedList<Node> cache = new LinkedList<Node>();
  private Map<K, Node> mapping = new HashMap<K, Node>();

  public LRU(int capacity) {
    this.capacity = capacity;
  }

  public void clear() {
    cache.clear();
    mapping.clear();
  }

  public void put(K key, V value) {
    Node node;
    if (!mapping.containsKey(key)) {
      node = new Node(key, value);
    } else {
      node = mapping.get(key);
      node.value = value;

      // remove the node and push it at the beginning of the list
      // this isn't O(n) because we pass the reference to the node
      // and since this is a doubly linked list we can update the
      // prev and next pointers in O(1)
      cache.remove(node);
    }

    cache.addFirst(node);
    mapping.put(key, node);

    if (cache.size() > capacity) {
      // this is O(1) because we do not need to traverse the list in order to
      // find the pointers that need to be updated since the java's LinkedList
      // implementation is a double linked list.
      Node removal = cache.getLast();
      cache.remove(removal);
      mapping.remove(removal.key);
    }
  }

  public V get(K item) {
    if (!mapping.containsKey(item)) return null;
    Node node = mapping.get(item);

    // this is O(1) for the same reasons as put() (see above)
    cache.remove(node);
    cache.addFirst(node);
    return node.value;
  }

  public static void main(String[] args) {
    LRU<String, Integer> cache = new LRU<String, Integer>(5);
    cache.put("item 1", 1);
    cache.put("item 2", 2);
    cache.put("item 3", 3);
    cache.put("item 4", 4);
    cache.put("item 5", 5);
    cache.put("item 6", 6);
    cache.put("item 7", 7);

    test(cache.get("item 7") == 7);
    test(cache.get("item 6") == 6);
    test(cache.get("item 5") == 5);
    test(cache.get("item 4") == 4);
    test(cache.get("item 3") == 3);
    test(cache.get("item 2") == null);
    test(cache.get("item 1") == null);

    cache.clear();

    cache.put("item 1", 1);
    cache.put("item 2", 2);
    cache.put("item 3", 3);
    cache.put("item 4", 4);
    cache.put("item 5", 5);
    cache.get("item 1");
    cache.put("item 6", 6);
    cache.put("item 7", 7);
    test(cache.get("item 7") == 7);
    test(cache.get("item 6") == 6);
    test(cache.get("item 5") == 5);
    test(cache.get("item 4") == 4);
    test(cache.get("item 3") == null);
    test(cache.get("item 2") == null);
    test(cache.get("item 1") == 1);

    cache.clear();

    // same as above, but test that 'put' moves things up in the cache
    cache.put("item 1", 1);
    cache.put("item 2", 2);
    cache.put("item 3", 3);
    cache.put("item 4", 4);
    cache.put("item 5", 5);
    cache.put("item 1", 1);  // this will move item 1 to the top of the queue
    cache.put("item 6", 6);
    cache.put("item 7", 7);
    test(cache.get("item 7") == 7);
    test(cache.get("item 6") == 6);
    test(cache.get("item 5") == 5);
    test(cache.get("item 4") == 4);
    test(cache.get("item 3") == null);
    test(cache.get("item 2") == null);
    test(cache.get("item 1") == 1);
  }

  public static void test(boolean condition) {
    // assertions are disabled by default in java, mimic their behaviour here
    if (!condition) {
      throw new AssertionError("invalid test");
    }
  }
}
