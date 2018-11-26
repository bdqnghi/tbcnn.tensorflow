mport java.util.ArrayList;
import java.util.Comparator;
import java.util.PriorityQueue;

public class MergeKList {
      static class ListNode{
          int value;
          ListNode next;
          ListNode(int value)
          {
              this.value=value;
          }
      }
    public void mergeKLists(ArrayList<ListNode> lists){
        PriorityQueue<ListNode> q=new PriorityQueue<ListNode>(lists.size(),new Comparator<ListNode>(){
            public int compare(ListNode a,ListNode b){
                return a.value-b.value;
            }
        });
    for(ListNode list:lists)
    {
        q.add(list);
    }
    while(q.size()>0){
        ListNode temp = q.poll();
        System.out.println(temp.value);
        if(temp.next!=null)
            q.add(temp.next);
        
    }
    
}
public static void main(String []args){
    ListNode h1 = new ListNode(3);
    h1.next=new ListNode(5);
    h1.next.next=new ListNode(8);
    ListNode h2 = new ListNode(2);
    h2.next=new ListNode(4);
    h2.next.next=new ListNode(9);
    ListNode h3 = new ListNode(4);
    h3.next=new ListNode(5);
    ListNode h4 =new ListNode(5);
    ArrayList<ListNode> lists = new ArrayList();
    lists.add(h1);
    lists.add(h2);
    lists.add(h3);
    lists.add(h4);
    new MergeKList().mergeKLists(lists);
 }
}

