public class LRUCache {
    private class ListNode {
        int key;
        int value;
        ListNode prev;
        ListNode next;

        public ListNode(int key, int value) {
            this.key = key;
            this.value = value;
        }
    }

    private ListNode head;
    private ListNode tail;
    private HashMap<Integer, ListNode> map;
    private int count;
    private int capacity;

    public LRUCache(int capacity) {
        count = 0;
        this.capacity = capacity;
        map = new HashMap<Integer, ListNode>();
    }

    private ListNode moveToLast(ListNode node) {
        if (node.next == null) {
            return node;
        }

        if (node.prev != null) {
            node.prev.next = node.next;
        } else {
            head = node.next;
        }

        node.next.prev = node.prev;
        node.prev = tail;
        node.next = null;
        tail.next = node;
        tail = node;

        return node;
    }

    public int get(int key) {
        if (map.containsKey(key)) {
            return moveToLast(map.get(key)).value;
        } else {
            return -1;
        }
    }

    public void set(int key, int value) {
        if (capacity == 0) {
            return;
        }

        if (map.containsKey(key)) {
            moveToLast(map.get(key)).value = value;
            return;
        }

        ListNode newNode = new ListNode(key, value);
        if (count == 0) {
            head = newNode;
            tail = newNode;
            count = 1;
            map.put(key, newNode);
            return;
        }

        if (count == capacity) {
            ListNode newHead = head.next;
            head.next = null;
            map.remove(head.key);
            if (newHead != null) {
                newHead.prev = null;
            }

            head = newHead;
            if (head == null) {
                tail = null;
            }
            count--;
        }

        if (tail == null) {
            set(key, value);
            return;
        }

        count++;
        tail.next = newNode;
        newNode.prev = tail;
        tail = newNode;
        map.put(key, newNode);
    }
}