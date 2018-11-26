public class LRUCache {
    //双向链表，自己设计的
    private class DLinkedNode{
        int key;
        int value;
        DLinkedNode pre;
        DLinkedNode next;
        DLinkedNode(int key,int value){
            this.key = key;
            this.value = value;
            this.next = null;
            this.pre = null;
        }
    }
    
    DLinkedNode head;
    DLinkedNode tail;
    Map<Integer,DLinkedNode> lru;
    int capacity;
    int count;//用于判定链表是否容量已满
    public LRUCache(int capacity) {
        lru = new HashMap<Integer,DLinkedNode>(capacity);
        this.capacity = capacity;
        head = new DLinkedNode(-1,-1);
        tail = new DLinkedNode(-1,-1);
        head.next = tail;
        tail.pre = head;
        count = 0;
    }
    
    public int get(int key) {
        if(!lru.containsKey(key))
            return -1;
        DLinkedNode node = (DLinkedNode)lru.get(key);
        putFirst(node);
        return node.value;
    }
    
    public void put(int key, int value) {
        if(!lru.containsKey(key)){
            count++;
            DLinkedNode node = new DLinkedNode(key,value);
            node.pre = head;
            node.next = head.next;
            head.next = node;
            node.next.pre = node;
            lru.put(key,node);
            if(count > capacity){
                DLinkedNode toBeDeletedNode = tail.pre;
                toBeDeletedNode.pre.next = tail;
                tail.pre = toBeDeletedNode.pre;
                toBeDeletedNode.pre = null;
                toBeDeletedNode.next = null;
                lru.remove(toBeDeletedNode.key);
            }
        }
        else{
            DLinkedNode node = (DLinkedNode)lru.get(key);
            lru.put(key,node);
            node.value = value;
            putFirst(node);
        }
    }
    //斩断和原来节点的联系，置于链表之首
    private void putFirst(DLinkedNode node){
        node.pre.next = node.next;
        node.next.pre = node.pre;
        node.pre = head;
        node.next = head.next;
        head.next = node;
        node.next.pre = node;
    }
}
//["LRUCache","get","put","get","put","put","get","get"]
//[[2],         [2],[2,6], [1],  [1,5],[1,2],[1],  [2]]
//Expected: [null,-1,null,-1,null,      null, 2,    6]


//["LRUCache","put","put","put","put","get","get"]
//[[2],       [2,1],[1,1],[2,3],[4,1],[1],   [2]]
//e[null,null,null,null,         null, 1,    -1]
//[null,       null, null, null,null, -1,     3]

/*["LRUCache","put","put","get","put","get","put","get","get","get"]
[    [2],     [1,1],[2,2], [1],  [3,3],[2], [4,4], [1],  [3],  [4]]
[    null,     null, null, 1,     null,-1,  null,  -1,   3,    4]*/
/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache obj = new LRUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */