package com;

import java.util.ArrayList;
import java.util.Deque;
import java.util.LinkedHashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Set;

class Node13{
	int c;
	Node13 next;
	public Node13(int c) {
		// TODO Auto-generated constructor stub
		this.c=c;
	}
}
public class Test13 {
	static List<Node13> list=new ArrayList<Node13>();
	static boolean[] visited=new boolean[8];
	static Set<Node13> stack=new LinkedHashSet<>();
	static Deque<Node13> set=new LinkedList<>();
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		list.add(new Node13(1));
		list.add(new Node13(2));
		list.add(new Node13(3));
		list.add(new Node13(4));
		list.add(new Node13(5));
		list.add(new Node13(6));
		list.add(new Node13(7));
		list.add(new Node13(8));
		addEdge(1, 3);
		addEdge(2, 3);
		addEdge(2, 4);
		addEdge(3, 5);
		addEdge(4, 6);
		addEdge(5, 7);
		addEdge(5, 6);
		addEdge(6, 8);
		for(Node13 n:list){
			while(n!=null){
				System.out.print(n.c+"-->");
				n=n.next;
			}
			System.out.println();
		}
		topolSort();
		System.out.println("After Topological sort : "+stack.size());
		for(Node13 p:stack){
			System.out.print(p.c+" ");
		}
	}
	static void addEdge(int a,int b){
		Node13 p=list.get(a-1);
		while(p.next!=null)
			p=p.next;
		p.next=new Node13(b);
	}
	static void topolSort(){
		Node13 p=getvertex();
		Node13 q=getAdjVertex(p);
		System.out.println("q : "+q.c);
		set.add(p);
		set.add(q);
		while(!set.isEmpty()){
			q=getAdjVertex(q);
			if(q==null){
				stack.add(set.getLast());
				set.removeLast();
				if(!set.isEmpty()){
					q=set.getLast();
				}
			}else
				set.add(q);
			if(set.isEmpty()){
				q=getvertex();
				set.add(q);
				if(q==null)
					break;
			}
		}
	}
	static Node13 getvertex(){
		Node13 p=null;
		for(Node13 n:list){
			if(!visited[n.c-1]){
				visited[n.c-1]=true;
				p=n;
				break;
			}
		}
		return p;
	}
	static Node13 getAdjVertex(Node13 p){
		p=list.get(p.c-1);
		p=p.next;
		Node13 q=null;
		while(p!=null){
			if(!visited[p.c-1]){
				visited[p.c-1]=true;
				q=p;
				break;
			}
			p=p.next;
		}
		return q;
	}
}
