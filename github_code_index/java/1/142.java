package com.arithmetic.������Ⱥ͹������;

import java.util.ArrayList;
import java.util.List;

/**
 * �������:�ڽӱ�ʵ��
 * @author yangzuliang
 *
 */
public class Breadth_First_Search_List {
	
	private class HeadNode{
		
		public String value;
		
		public ArcNode firstArcNode;
		
		public boolean isVisited;
	}
	
	private class ArcNode{
		
		public HeadNode headNode;
		
		public ArcNode nextArcNode;
		
		public ArcNode( HeadNode headNode){
			
			this.headNode = headNode;
		}
	}
	
	public void addArc(HeadNode head, HeadNode tail){
		
		if(head.firstArcNode == null){
			
			head.firstArcNode = new ArcNode(tail);
		}else{
			
			ArcNode arcNode = head.firstArcNode;
			
			while(arcNode.nextArcNode != null){
				
				arcNode = arcNode.nextArcNode;
			}
			
			arcNode.nextArcNode = new ArcNode(tail);
		}
	}
	
	public List<HeadNode> headNodes = new ArrayList<HeadNode>();
	
	public void BFSTraverse(){
		
		for(HeadNode headNode : headNodes){
			
			headNode.isVisited = false;
		}
		
		Queue<ArcNode> queue = new Queue<ArcNode>(); 
		
		for(int i=0; i<headNodes.size(); i++){
			
			if(!headNodes.get(i).isVisited){
				
				HeadNode p = headNodes.get(i);
				queue.enqueue(p.firstArcNode);
				p.isVisited = true;
				System.out.print(p.value + "->");
				
				while(!queue.isEmpty()){
					
					ArcNode arcNode = queue.dequeue();
					
					while(arcNode != null){
						
						if(!arcNode.headNode.isVisited){
							
							System.out.print(arcNode.headNode.value + " ");
							arcNode.headNode.isVisited = true;
							queue.enqueue(arcNode);
						}
						
						arcNode = arcNode.nextArcNode;
					}
				}
			}
		}
	}
	
	public static void main(String[] args) {
		
		Breadth_First_Search_List.HeadNode hA = new Breadth_First_Search_List().new HeadNode();
		hA.value = "A";
		Breadth_First_Search_List.HeadNode hB = new Breadth_First_Search_List().new HeadNode();
		hB.value = "B";
		Breadth_First_Search_List.HeadNode hC = new Breadth_First_Search_List().new HeadNode();
		hC.value = "C";
		Breadth_First_Search_List.HeadNode hD = new Breadth_First_Search_List().new HeadNode();
		hD.value = "D";
		Breadth_First_Search_List breadth_First_Search_List = new Breadth_First_Search_List();
		breadth_First_Search_List.headNodes.add(hA);
		breadth_First_Search_List.headNodes.add(hB);
		breadth_First_Search_List.headNodes.add(hC);
		breadth_First_Search_List.headNodes.add(hD);
		breadth_First_Search_List.addArc(hA, hB);
		breadth_First_Search_List.addArc(hB, hC);
		breadth_First_Search_List.addArc(hC, hD);
		breadth_First_Search_List.addArc(hB, hA);
		breadth_First_Search_List.addArc(hA, hC);
		breadth_First_Search_List.addArc(hC, hB);
		breadth_First_Search_List.addArc(hB, hA);
		breadth_First_Search_List.addArc(hA, hD);
		breadth_First_Search_List.addArc(hD, hA);
		breadth_First_Search_List.addArc(hA, hC);
		breadth_First_Search_List.BFSTraverse();
	}

}
