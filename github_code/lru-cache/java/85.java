public class Solution {

    // @param capacity, an integer
    public class ListNode {
        int key, val;
        ListNode next;
        ListNode prev;
        ListNode(int key, int val) {
            this.key = key;
            this.val = val;
            this.next = null;
            this.prev = null;
        }
    }
    public int capacity;
    public int len;
    public ListNode head;
    public ListNode tail;
    public HashMap<Integer, ListNode> hash;
    public Solution(int capacity) {
        // write your code here
        this.capacity = capacity;
        len = 0;
        head = new ListNode(0, 0);
        tail = new ListNode(0, 0);
        head.next = tail;
        tail.prev = head;
        hash = new HashMap<Integer, ListNode>();
    }
    void delete(ListNode cur) {
        ListNode lastp = cur.prev;
        ListNode nextp = cur.next;
        lastp.next = nextp;
        nextp.prev = lastp;
    }
    void add(ListNode cur) {
        ListNode lastp = tail.prev;
        lastp.next = cur;
        cur.next = tail;
        tail.prev = cur;
        cur.prev = lastp;
    }
    // @return an integer
    public int get(int key) {
        // write your code here
        if (!hash.containsKey(key)) return -1;
        ListNode cur = hash.get(key);
        delete(cur);
        add(cur);
        return cur.val;
    }
    // @param key, an integer
    // @param value, an integer
    // @return nothing
    public void set(int key, int value) {
        // write your code here
        if (hash.containsKey(key)) {
            hash.get(key).val = value;
            get(key);
        } else {
            ListNode cur = new ListNode(key, value);
            if (len == capacity) {
                ListNode temp = head.next;
                delete(temp);
                hash.remove(temp.key);
                hash.put(key, cur);
                add(cur);
            } else {
                add(cur);
                hash.put(key, cur);
                len ++;
            }
        }
    }
}
