/*
LeetCode: https://leetcode.com/problems/lru-cache/
LintCode: http://www.lintcode.com/problem/lru-cache/
JiuZhang: http://www.jiuzhang.com/solutions/lru-cache/
ProgramCreek: http://www.programcreek.com/2013/03/leetcode-lru-cache-java/

Analysis: 
Two key points to design a LRU cache:
    1.Get,Set,Remove in O(1) (Use HashMap)
    2.Maintain the order from latest and oldest (Use Double Linked List)
Use HashMap to search,delete,set: O(1)
List to keep order(like a queue, FILO)

Be carefully, every get, set operation, will cause operated node to the head of list.
Every set operation will affect both List and HashMap.

*/
public class LRUCache {
    private class Node{
        int key;
        int value;
        Node prev;
        Node next;
        
        public Node(int key, int value){
            this.key = key;
            this.value = value;
        }
    }
    
    HashMap<Integer, Node> map = new HashMap<Integer, Node>();
    Node head;
    Node tail;
    int capacity;
    
    public LRUCache(int capacity) {
        this.capacity = capacity;
    }
    
    public int get(int key) {
        if(map.containsKey(key)){
            Node curr = map.get(key);
            int value = curr.value;
            removeNode(curr);
            addToHead(curr);
            return value;
        }
        return -1;
    }
    
    public void set(int key, int value) {
        if(map.containsKey(key)){
            Node curr = map.get(key);
            curr.value = value;
            removeNode(curr);
            addToHead(curr);
            return;
        }
        
        // we need to add a new node to hashmap and List
        Node curr = new Node(key, value);
        if(map.size() == capacity){
            Node oldTail = tail;
            tail = tail.prev;
            
            removeNode(oldTail);     //remove in List
            map.remove(oldTail.key); //don't forget to remove in HashMap
        }
        
        addToHead(curr);            //add in list
        map.put(curr.key, curr);    //don't forget to operate in HashMap
    }
    
    //Move to the head of List (Have nothing to do with HashMap operation)
    private void addToHead(Node node){
        // removeNode(node);
        node.next = head;
        node.prev = null;
        
        if(head != null) head.prev = node;
        if(tail == null) tail = node;       //don't forget the tail is null
        
        head = node;
    }
    
    //Remove node from List(Have nothing to do with HashMap operation)
    private void removeNode(Node node){
        if(node == head) head = head.next;
        if(node == tail) tail = tail.prev;
        if(node.next != null) node.next.prev = node.prev;
        if(node.prev != null) node.prev.next = node.next;
        node.next = null;
        node.prev = null;
    }
}