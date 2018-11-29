package Visitors;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.TreeMap;

public class B implements Node, Visitable {

	// Data members :
	public static int bCount = 0;

	// Map for current tag attributes: 
	private Map<String, String> hashMap = new HashMap<String, String>();
	private TreeMap<String, String> sortedMap = new TreeMap<String, String>(); // To sort it alphabetically

	// ArrayList for multiple tags under this tag:
	private List<Node> listOfNodes = new ArrayList<Node>();
	private String display;
	private Node node;

	private String startBTag = "<b";
	private String endBTag = "</b>";

	// Getters and Setters:

	public Map<String, String> getHashMap() {
		return hashMap;
	}


	public void setHashMap(Map<String, String> hashMap) {
		this.hashMap = hashMap;
		// convert the attributes HashMap to TreeMap for sorted order:
		this.sortedMap = new TreeMap<String, String>(hashMap);
	}


	public List<Node> getListOfNodes() {
		return listOfNodes;
	}


	public void setListOfNodes(List<Node> listOfNodes) {
		this.listOfNodes = listOfNodes;
	}


	public String getDisplay() {
		return display;
	}


	public void setDisplay(String display) {
		this.display = display;
	}


	public Node getNode() {
		return node;
	}


	public void setNode(Node node) {
		this.node = node;
	}


	// Parameterized constructor with ArrayList for Nodes, Map for attributes and String to display:
	public B(ArrayList<Node> nodes, Map attributesMap, String s) {
		this.listOfNodes = nodes;
		this.hashMap = attributesMap;
		// convert the attributes HashMap to TreeMap for sorted order:
		if(attributesMap != null)
			this.sortedMap = new TreeMap<String, String>(hashMap);
		this.display = s;
	}
//
//	// Parameterized constructor with Map for attributes and String to display:
//	public B(Map attributesMap, String s) {
//		this.hashMap = attributesMap;
//		// convert the HashMap to TreeMap for sorted order: 
//		this.map = new TreeMap<String, String>(hashMap);
//		this.display = s;
//	}
//
//	// Parameterized constructor with map for attributes and Object of concrete classes:
//	public B(ArrayList<Node> nodes, Map attributesMap) {
//		this.listOfNodes = nodes;
//		this.hashMap = attributesMap;
//		// convert the HashMap to TreeMap for sorted order:
//		this.map = new TreeMap<String, String>(hashMap);
//		this.node = node;
//	}
//

	public String textualRepresentation() {

		StringBuffer sb = new StringBuffer();
		String addAttributes = "";
		String addTag = "";
		sb.append(startBTag);

		// check if current tag contains attributes:
		if(this.sortedMap != null) {
			addAttributes = Common.convertMapAttributesToString(this.sortedMap);
			// append the attributes:
			sb.append(addAttributes);
		}



		// check if current includes another tag:
		if(this.node != null) {
			addTag = this.node.textualRepresentation();
			// append the attributes:
			sb.append(addTag);
		}

		if(this.display != null)
			sb.append(this.display);
		sb.append(endBTag);
		return sb.toString();
	}
	
	public int accept(NodeCountVisitor nv) {
		return nv.visitB(this);
	}


	//	public static void main(String args[]) {
	//		Map<String, String> map = new HashMap<String, String>();
	//		map.put("attr1", "value1");
	//		map.put("attr2", "value2");
	//		HTML html = new HTML(map, "Hi There!");
	//		System.out.println(html.textualRepresentation());
	//	}
}


