package LinkedList;

import java.util.Set;

/**
 * Created by dheeraj on 6/1/15.
 */
public class MergeSort {

    private int size = 0;
    private Node root;
    private Node sortedRoot;

    private Node sort(Node start,int size){
        if(size == 1){
            return start;
        }

        int k = size/2;
        Node temp = start;
        for(int x=0;x<k;x++){

            if(x == k-1){
                Node p = temp.next;
                temp.next = null;
                temp = p;
            }else{
                temp = temp.next;

            }
        }

        Node first = sort(start,k);
        Node second = sort(temp,size-k);

        //System.out.println("two nodes");
        //print(first);
        //print(second);

        Node sortedRoot = null;
        Node sortedRootTemp = null;

        while(first!= null && second!=null){
            //System.out.println("first = " + first.value + " + second = " + second.value);
            if(first.value < second.value){
                if(sortedRoot == null){
                    sortedRoot = first;
                    sortedRootTemp = first;
                }else{
                    sortedRootTemp.next = first;
                    sortedRootTemp = sortedRootTemp.next;
                }
                first = first.next;
            }else{
                if(sortedRoot == null){
                    sortedRoot = second;
                    sortedRootTemp = second;
                }else{
                    sortedRootTemp.next = second;
                    sortedRootTemp = sortedRootTemp.next;
                }
                second = second.next;
            }
        }

        if(first == null){
            //System.out.println("first = null" + second.value);
            sortedRootTemp.next =second;
        }

        if(second == null){
            //System.out.println("second = null" + first.value);
            sortedRootTemp.next = first;
        }
        //print(sortedRoot);
        return sortedRoot;
    }

    private static class Node{
        int value;
        Node next;
        private Node(int data){
            this.value = data;
            this.next = null;
        }
    }

    private void addNode(int value){
        if(root == null){
            root = new Node(value);
        }else{
            Node temp = new Node(value);
            temp.next = root;
            root = temp;
        }
        size++;
    }

    private void print(Node node){
        while(node != null){
            System.out.print(node.value+" ");
            node = node.next;
        }
        System.out.println();
    }

    public static void main(String[] args){
        MergeSort mergeSort  = new MergeSort();
        mergeSort.addNode(2);
        mergeSort.addNode(1);
        mergeSort.addNode(6);
        mergeSort.addNode(0);
        mergeSort.addNode(5);


        mergeSort.print(mergeSort.root);
        mergeSort.sortedRoot = mergeSort.sort(mergeSort.root,mergeSort.size);
        mergeSort.print(mergeSort.sortedRoot);

    }

}
