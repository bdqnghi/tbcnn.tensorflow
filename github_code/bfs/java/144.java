/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package practise;

import java.util.Scanner;

/**
 *
 * @author Prajval
 */
public class BreadthFirstSearch {
    
    int n,e;
    int[] visited;
    QueueNode front;
    QueueNode rear;
    
     public BreadthFirstSearch()
     {
         front = null;
         rear = null;
         visited = new int[10];
     }
    
     void push(int d,BreadthFirstSearch b)
     {
         if(b.front == null)
         {
             b.front = new QueueNode(d);
             b.rear = b.front;
         }
         else
         {
             b.rear.next = new QueueNode(d);
             b.rear = b.rear.next;
         }
     }
     
     int pop(BreadthFirstSearch b)
     {
         int t = b.front.data;
         b.front = b.front.next;
         return t;
     }
     
     boolean is_empty(BreadthFirstSearch b)
     {
         if(b.front == null)
             return true;
         return false;
     }
    
     void bfs(int source,BreadthFirstSearch b,AdjListNode[] a)
     {
         b.push(source,b);
         while(is_empty(b) == false)
         {
             int t = b.pop(b);
             if(b.visited[t] == 0)
             {
                b.visited[t] = 1;
                System.out.printf("%d\n",t);
                AdjListNode current = a[t];
                while(current!=null)
                {
                    int d = current.data;
                    if(b.visited[d] == 0)
                        b.push(d,b);
                    current = current.next;
                }
             }
         }
         
     }
    
     void insert(int v1,int v2,AdjListNode[] a)
     {
         if(a[v1] == null)
         {
             a[v1] = new AdjListNode(v2);
         }
         else
         {
             AdjListNode current = a[v1];
             while(current.next!= null)
                 current = current.next;
             current.next = new AdjListNode(v2);
         }
     }
     
     void print_list_graph(AdjListNode[] a,BreadthFirstSearch b)
     {
         for(int i=0;i<b.n;i++)
         {
             AdjListNode current = a[i];
             System.out.printf("%d->",i);
             while(current!= null)
             {
                 System.out.printf("%d ",current.data);
                 current = current.next;
             }
             System.out.printf("\n");
         }
     }
     
     public static void main(String[] args)
     {
         Scanner sc = new Scanner(System.in);
         System.out.printf("Enter the number of vertices and edges\n");
         BreadthFirstSearch b = new BreadthFirstSearch();
         b.n = sc.nextInt();
         b.e = sc.nextInt();
         System.out.printf("Enter the edges\n");
         
         AdjListNode[] a = new AdjListNode[10];
         
         for(int i=0;i<b.e;i++)
         {
             int v1,v2;
             v1 = sc.nextInt();
             v2 = sc.nextInt(); 
             b.insert(v1, v2, a);
         }
         
         //b.print_list_graph(a,b);
         b.bfs(2,b,a);
         
     }
    
}
