import java.util.Queue;
import java.util.Iterator;
import java.util.ArrayList;
import java.util.LinkedList;
/*
Use max 2n keys in one page and so 2n+1 max children
Use the rule to insert a value first and then break the node if more than 2n values
This one uses an ArrayList of values and insert value at the right place
*/
public class B_tree<E extends Comparable<E>> implements Iterable{
  // as it is not static the inner class knows the generic type of its parent
  private class Bt_Iterator implements Iterator{
    private Queue<Node<E>> nodes;
    public Bt_Iterator(){
      nodes = new LinkedList<>();
      //obtained values by dfs
      post_order(root);
      nodes.add(root);
    }
    private void post_order(Node<E> node){
      if(node == null)
        return;
      for(Node<E> child : node.children){
        post_order(child);
        nodes.add(child);
      }
    }
    public boolean hasNext(){
      return nodes.size() != 0;
    }
    public Node<E> next(){
      return nodes.poll();
    }
    public void remove(){
      throw new UnsupportedOperationException();
    }
  }
  private int order;
  private Node<E> root;
  public B_tree(int order){
    this.order = order;
    root = new Node(new ArrayList<Node<E>>(), new TreeSet<Node<E>>(),null);
  }

  public Iterator<Node<E>> iterator(){
    return new Bt_Iterator();
  }

  public void insert(E val){
    Node<E> current = root;
    int pos;
    while(current.children.size() != 0){
      pos = 0;
      Iterator<E> it = current.values.iterator();
      while(it.hasNext() && val.compareTo(it.next()) > 0)
        pos++;
     current = current.children.get(pos);
  }
  current.values.add(val);
  if(current.values.size() > 2*order){
  // no more keys allowed => move key up
    split_node(current);
  }
}

private E getMiddle(Node<E> current){
  E move = null;
  int pos;
  Iterator<E> it = current.values.iterator();
  pos = 0;
  while(it.hasNext() && pos < (2*order + 1)/2 + 1){
    pos++;
    move = it.next();
  }
  return move;
}

private void split_node(Node<E> current){
  // we use get Middle because we need the element at a position in the TreeSet => possible only by iterations
  E move =  getMiddle(current);
  Node<E> parent;
  // check to see for new root
  if(current.parent == null) {
    root = new Node(new ArrayList<>(), new TreeSet<>(),null);
    current.parent = root;
  }
  parent = current.parent;
  parent.values.add(move);
  //current.values.remove(move);
  int insert_pos = (parent.values.headSet(move)).size();
  Node<E> left = new Node<>();
  Node<E> right = new Node<>();

  redistribute_vals(current,left,0,order,insert_pos);
  redistribute_vals(current,right,order + 1 ,2*order + 1 ,insert_pos + 1);
  // recursivly check the up the tree if more splits needed
  if(parent.values.size() > 2*order){
    split_node(parent);
  }
}

  private void redistribute_vals(Node<E> current, Node<E> newNode,int left, int right, int insert_pos){
    int count = 0;
    E val;
    ArrayList<E> new_values = new ArrayList<>();
    ArrayList<Node<E>> new_children = new ArrayList<>();
    Iterator<E> it = current.values.iterator();
    while(it.hasNext() && count < right){
      val = it.next();
      if(count >= left){
        new_values.add(val);
      }
      count++;
    }
    //switch boundaries for children as their number is odd

    count = 0;
    for(Node<E> child : current.children){
      // optimize just for the left new Node as go just half of the children
      // aici ii bug-ul
      if(count > right) break;
        else
      if(count >= left){
      child.parent = newNode;
      new_children.add(child);
    }
    count++;
    }
    newNode.children = new_children;
    newNode.values = new_values;
    newNode.parent = current.parent;
    //insert children in the right position
    current.parent.children.add(insert_pos,newNode);
    //remove the old node that has just been splited
    current.parent.children.remove(current);
  }

  public void delete(E value){

  }
  public E treeMin(Node<E> current){
    if(current.children.size() == 0){

    }
    return null;
  }

  public E successor(E val){
    return null;
  }

  // this should be implemnted in ArrayList to respect the single responsability property
  private void isert_order(ArrayList<E> values, E value){
    //O(n + n) n for the the loop and n for moving all elements in the new array better is log n, which is the TreeSet
    int i;
    for(i = 0; i < values.size() && values.get(i) < value; i++);
    values.add(i,value);
  }

  private void preOrder(Node<E> current){
    if(current == null) return;
      System.out.print("node: ");
      for(E val : current.values){
        System.out.print(val + " ");
      }
      System.out.println();
      for(Node<E> child : current.children)
        preOrder(child);
    }
    public void afis_postOrder(){
      Iterator<Node<E>> it = iterator();
      Node<E> current = null;
      while(it.hasNext()){
        current = it.next();
        System.out.print("node: ");
        for(E val : current.values){
          System.out.print(val + " ");
        }
        System.out.println();
      }
    }

    public void afis_preOrder(){
      preOrder(root);
    }
    private void inOrder(Node<E> current){
      if(current == null){
        return ;
      }
      if(current.children.size() == 0){
        Iterator<E> it = current.values.iterator();
        while(it.hasNext()){
          System.out.print(it.next() + " ");
        }
      }
      else{
        int i;
        for(i = 0; i < current.children.size() - 1; i++){
          inOrder(current.children.get(i));
          System.out.print(current.values.pollFirst() + " ");
        }
        // one extra child in comparison with keys
        inOrder(current.children.get(i));
    }
    }
    public void afis_inOrder(){
      inOrder(root);
    }
  public static void main(String [] args){
    B_tree<Integer> test = new B_tree<Integer>(1);
    test.insert(2);
    test.insert(3);
    test.insert(1);
    test.insert(10);
    test.insert(0);
    test.insert(20);
    test.insert(50);
    test.insert(90);
    test.insert(100);
    test.insert(101);
    test.insert(150);
    test.insert(156);
    test.insert(170);
    test.insert(180);
    test.insert(190);
    test.insert(200);
    test.insert(217);

    test.afis_inOrder();
    System.out.println();
    test.afis_preOrder();
  }
}
