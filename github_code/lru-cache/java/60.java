ass Node{
    int key;
    int value;
    Node next;
    Node prev;
    public Node(int a, int b){
        key = a;
        value = b;
    }
}
public class Solution {
    HashMap<Integer, Node> map;
    int capacity;
    Node head = new Node(-1, -1);
    Node tail = new Node(-1, -1);
    // @param capacity, an integer
    public Solution(int capacity) {
        // write your code here
        map = new HashMap<Integer, Node>();
        this.capacity = capacity;
        head.next = tail;
        tail.prev = head;
    }

    // @return an integer
    public int get(int key) {
        // write your code here
        if(!map.containsKey(key)){
            return -1;
        }
        Node crt = map.get(key);
        //remove crt
        crt.prev.next = crt.next;
        crt.next.prev = crt.prev;
        moveToTail(crt);
        return crt.value;
    }

    // @param key, an integer
    // @param value, an integer
    // @return nothing
    public void set(int key, int value) {
        // write your code here
        if(get(key) != -1){//这里为什么不能直接用hashmap来弄？？？
            map.get(key).value = value;
            return;
        }
        //exceed the capacity
        if(map.size() == capacity){
            map.remove(head.next.key);
            head.next = head.next.next;
            head.next.prev = head;
        }
        map.put(key, new Node(key, value));
        moveToTail(map.get(key));
    }
    public void moveToTail(Node crt){
        crt.prev = tail.prev;
        tail.prev = crt;
        crt.prev.next = crt;
        crt.next = tail;
    }
}
