public class LRUCache {
    class ListNode {
        int key;
        int val;
        ListNode next;
        ListNode(int k,int x) {
            key = k;
            val = x;
            next = null;
        }
        ListNode() {
            key = 0;
            val = 0;
            next = null;
        }
    }
    ListNode head;
    ListNode tail;
    int capacity;
    int size;
    public LRUCache(int capacity) {
        head = new ListNode();
        this.capacity = capacity;
        size=0;
    }

    public int get(int key) {
        ListNode p = head;
        while(p.next!=null){
            if(p.next.key==key){
                //operate
                ListNode cur=p.next;
                tail.next=cur;
                tail=cur;
                p.next=cur.next;
                tail.next=null;
                return cur.val;
            }
            p=p.next;
        }
        return -1;
    }

    public void set(int key, int value) {
        //first set
        if(size==0){
            head.next=new ListNode(key,value);
            tail=head.next;
            size++;
            return;
        }
        //if existed
        ListNode p = head;
        while(p.next!=null){
            if(p.next.key==key){
                //operate
                ListNode cur=p.next;
                tail.next=cur;
                tail=cur;
                p.next=cur.next;
                tail.next=null;
                cur.val=value;
                return;
            }
            p=p.next;
        }
        //not existed
        if(size<capacity){
            tail.next=new ListNode(key, value);
            tail=tail.next;
            size++;
            return;
        }
        //size==capacity
        tail.next=new ListNode(key, value);
        tail=tail.next;
        head.next=head.next.next;
    }
}