/**
The LRU cache is a hash table of keys and double linked nodes. 
The hash table makes the time of get() to be O(1). 
The list of double linked nodes make the nodes adding/removal operations O(1).

*/

import java.util.HashMap;

class Node{
    int key;
    int value;
    Node pre;
    Node next;

    public Node(int key, int value){
        this.key = key;
        this.value = value;
    }
}

public class LRUCache {

    int capacity;

    HashMap<Integer, Node> map = new HashMap<Integer, Node>();
    Node head=null;
    Node tail=null;

    public LRUCache(int capacity) {
        this.capacity = capacity;
    }
    //Check if the key exists in the map, if yes, move the node to the begining of the list
    public int get(int key) {

        if(map.containsKey(key)){
            Node n = map.get(key);
            remove(n);
            setHead(n);
            return n.value;
        }

        return -1;

    }

    //if the key exists in the map, update the value of the node, else create new node and push to begining of list and add to map
    public void set(int key, int value) {

        if(map.containsKey(key)){
            Node old = map.get(key);
            old.value = value;
            remove(old);
            setHead(old);
        }else{
            Node created = new Node(key, value);
            if(map.size()>=capacity){
                map.remove(tail.key);
                remove(tail);
                setHead(created);

            }else{
                setHead(created);
            }

            map.put(key, created);
        }

    }


    public void remove(Node n){
        if(n.pre!=null){
            n.pre.next = n.next;
        }else{
            head = n.next; // If n is the head node 
        }

        if(n.next!=null){
            n.next.pre = n.pre;
        }else{
            tail = n.pre;  // If n is the tail node 
        }

    }

    public void setHead(Node n){
        n.next = head;
        n.pre = null;

        if(head!=null)
            head.pre = n;

        head = n;

        if(tail ==null)
            tail = head;
    }
}
