// http://www.lintcode.com/en/problem/lru-cache/#
// 链接：https://www.nowcoder.com/questionTerminal/8006ac33cb964c54bad92ab7b6391fad

// 利用链表和hashmap。当需要插入新的数据项的时候，如果新数据项在链表中存在（一般称为命中），则把该节点移到链表头部，如果不存在，则新建一个节点，放到链表头部，若缓存满了，则把链表最后一个节点删除即可。在访问数据的时候，如果数据项在链表中存在，则把该节点移到链表头部，否则返回-1。这样一来在链表尾部的节点就是最近最久未访问的数据项。 

//   总结一下：根据题目的要求，LRU Cache具备的操作： 

//   1）set(key,value)：如果key在hashmap中存在，则先重置对应的value值，然后获取对应的节点cur，将cur节点从链表删除，并移动到链表的头部；若果key在hashmap不存在，则新建一个节点，并将节点放到链表的头部。当Cache存满的时候，将链表最后一个节点删除即可。 

//   2）get(key)：如果key在hashmap中存在，则把对应的节点放到链表头部，并返回对应的value值；如果不存在，则返回-1。

// public class Solution {

//     // @param capacity, an integer
//     public Solution(int capacity) {
//         // write your code here
//     }

//     // @return an integer
//     public int get(int key) {
//         // write your code here
//     }

//     // @param key, an integer
//     // @param value, an integer
//     // @return nothing
//     public void set(int key, int value) {
//         // write your code here
//     }
// }

// http://www.jiuzhang.com/solutions/lru-cache/
public class Solution {
    
    // 定义一个双向链表的数据接口，并且存储key，value值。
    private class Node{
        Node prev;
        Node next;
        int key;
        int value;

        public Node(int key, int value) {
            this.key = key;
            this.value = value;
            this.prev = null;
            this.next = null;
        }
    }

    // 初始化容量
    private int capacity;
    // 记录访问次数
    private HashMap<Integer, Node> hs = new HashMap<Integer, Node>();
    // 初始化头尾节点。
    private Node head = new Node(-1, -1);
    private Node tail = new Node(-1, -1);

    public Solution(int capacity) {
        this.capacity = capacity;
        tail.prev = head;
        head.next = tail;
    }

    public int get(int key) {
        // get 某个值，如果node存在
        // 首先处理这个node附近的指针，然后在最后插入这个node
        if( !hs.containsKey(key)) {
            return -1;
        }

        // remove current
        Node current = hs.get(key);
        current.prev.next = current.next;
        current.next.prev = current.prev;

        // move current to tail
        move_to_tail(current);

        return hs.get(key).value;
    }

    public void set(int key, int value) {
        // 检查key是否存在，存在直接返回。
        // 检查容量是否超出。
        // 插入新的key，value节点到最后。
        // this internal `get` method will update the key's position in the linked list.
        if (get(key) != -1) {
            hs.get(key).value = value;
            return;
        }

        if (hs.size() == capacity) {
            hs.remove(head.next.key);
            head.next = head.next.next;
            head.next.prev = head;
        }

        Node insert = new Node(key, value);
        hs.put(key, insert);
        move_to_tail(insert);
    }

    private void move_to_tail(Node current) {
        current.prev = tail.prev;
        tail.prev = current;
        current.prev.next = current;
        current.next = tail;
    }
}