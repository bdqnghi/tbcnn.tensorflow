package ds.learning.search;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

public class BreadthFirstSearch {

	public boolean search(Node head, String searchItem) {
		LinkedList<Node> queue = new LinkedList<Node>();
		
		if(head.getData().equals(searchItem)) {
			return true;
		} else {
			queue.add(head);
			for(Node node : queue) {
				if(node.getData().equals(searchItem)) {
					return true;
				} else {
					queue.addAll(node.getChild());
				}
			}
			return false;
		}
	}
}

class Node {
	
	private String data;
	private List<Node> child = new ArrayList<Node>();
	private boolean visit;
	
	public String getData() {
		return data;
	}
	public void setData(String data) {
		this.data = data;
	}
	public List<Node> getChild() {
		return child;
	}
	public void setChild(List<Node> child) {
		this.child = child;
	}
	public boolean isVisit() {
		return visit;
	}
	public void setVisit(boolean visit) {
		this.visit = visit;
	}
	
	
}
