package mx.ia.algorithms;

import java.util.HashMap;
import java.util.Map;
import java.util.Vector;

import mx.ia.graph.Edge;
import mx.ia.graph.Graph;
import mx.ia.graph.Vertex;

public class BreadthFirstSearch {
	private Graph graphG;
	private Graph graphT = new Graph();
	private Map<String, Vertex> vElements = new HashMap<String, Vertex>();
	private Vector<String> rules = null;// {"270","0","90","180"};
	private Vector<BreadthFirstSearchElement> bfsOpened = new Vector<BreadthFirstSearchElement>();
	private Vector<BreadthFirstSearchElement> bfsClosed = new Vector<BreadthFirstSearchElement>();
	
	public BreadthFirstSearch(Graph g){
		System.out.println("BreadthFirstSearch Controller - Started");
		graphG = g;
		System.out.println("G: {\n" + g.toString() + "\n}\n"
				+ " Vertices: " + graphG.getV().size() + "\n"
				+ " Edges: " + graphG.getE().size());
	}
	
	public void setRules(Vector<String> rul){
		this.rules = rul;
	}
	
	public Graph resolve(String from, String to){
		boolean fail = true;
		NewString newFrom = new NewString(), newTo = new NewString();
		BreadthFirstSearchElement element = null;
		BreadthFirstSearchElement elementToAdd;
		newFrom.str = from;
		newTo.str = to;
		System.out.println("Resolve: from " + newFrom + " to " + newTo);
		
		if (!graphG.getV().contains(newFrom)){
			System.out.println("Can not find the vertex: " + newFrom);
			return null;
//			throw new IllegalArgumentException("Can not find the vertex: " + newFrom);
		}
		if (!graphG.getV().contains(newTo)){
			System.out.println("Can not find the vertex: " + newTo);
			return null;
//			throw new IllegalArgumentException("Can not find the vertex: " + newTo);
		}
		
		for (Vertex s : graphG.getV())
			vElements.put(s.getCode(), s);

		System.out.println(vElements.toString());

		elementToAdd = new BreadthFirstSearchElement(vElements.get(from), 1, 0.0);
		elementToAdd.setPrevious(elementToAdd);
		putNeighbors(elementToAdd);
		
		bfsOpened.add(elementToAdd);
		
		while(!bfsOpened.isEmpty()){
			
			element = bfsOpened.firstElement();
			System.out.println("Level: " + element.getLevel());
			if(element.equalsStr(to)){
				fail = false;
				break;
			}
			
			if(rules != null){
				bfsOpened.addAll(ruledNeighbors(rules, element));
			}else{
				for (String neighborCode : element.getNeighbors().keySet()) {
					if(!contains(bfsClosed, neighborCode) && !containsRoute(bfsOpened, neighborCode, element.getVertex().getCode())){
						elementToAdd = new BreadthFirstSearchElement(vElements.get(neighborCode), element.getLevel() + 1, element.getNeighbors().get(neighborCode) + element.getWeight());
						elementToAdd.setPrevious(element);
						putNeighbors(elementToAdd);
						bfsOpened.add(elementToAdd);
					}
				}
			}
			
			
			bfsOpened.remove(element);
			bfsClosed.add(element);
			System.out.println("\n-");
			System.out.println("O:=(" + bfsOpened.size() + ")" + bfsOpened.toString());
			System.out.println("C:=(" + bfsClosed.size() + ")" + bfsClosed.toString());
		}
		if (fail) {
			System.out.println("Failed to resolve");
			return null;
		}
		System.out.println(element.printTrace());
		do{
			graphT.getV().add(element.getVertex());
			graphT.getE().add(new Edge(element.getPrevious().getVertex().getCode(), element.getVertex().getCode(), element.getWeight() - element.getPrevious().getWeight()));
			element = element.getPrevious();
		}while(element.getPrevious() != element);
		graphT.getV().add(element.getVertex());
		
		System.out.println(graphT.toString());
//		System.out.save();
		return graphT;
	}
	
	void putNeighbors(BreadthFirstSearchElement elementToAdd){
		Map<String, Double> neighbors = new HashMap<String, Double>();
		for (Edge e : graphG.getE())
			if(elementToAdd.equalsStr(e.getFrom()))
				neighbors.put(e.getTo(), e.getDistance());
		elementToAdd.getNeighbors().putAll(neighbors);
	}
	
	private Vector<BreadthFirstSearchElement> ruledNeighbors (Vector<String> rules, BreadthFirstSearchElement bfsElement){
		
		Vector<BreadthFirstSearchElement> res = new Vector<BreadthFirstSearchElement>();
		System.out.println("All neighbors: " + bfsElement.getNeighbors().size());
		System.out.println(rules);
		System.out.println(rules.size());
		System.out.print("Ruled neighbors: [");
		BreadthFirstSearchElement elementToAdd;
		for (String strRule : rules) {
			for(String neighborCode : bfsElement.getNeighbors().keySet()){
				for(Edge edge : graphG.getE()){
					if(bfsElement.equalsStr(edge.getFrom()) && neighborCode.equals(edge.getTo()) && strRule.equals(edge.getOrderCode())){
						if(!contains(bfsClosed, neighborCode) && !containsRoute(bfsOpened, neighborCode, bfsElement.getVertex().getCode())){
							elementToAdd = new BreadthFirstSearchElement(vElements.get(neighborCode), bfsElement.getLevel() + 1, bfsElement.getNeighbors().get(neighborCode) + bfsElement.getWeight());
							elementToAdd.setPrevious(bfsElement);
							putNeighbors(elementToAdd);
							res.add(elementToAdd);
							System.out.print(strRule + ": " + neighborCode + "  ");
						}
					}
				}
			}
		}
		System.out.println("]\n");
		return res;
	}
	
	private boolean contains(Vector<BreadthFirstSearchElement> bfsClosed2, String str){
		for (BreadthFirstSearchElement breadthFirstSearchElement : bfsClosed2)
			if(breadthFirstSearchElement.equalsStr(str))
				return true;
		return false;
	}
	
	private boolean containsRoute(Vector<BreadthFirstSearchElement> v, String strActual, String strPrev){
		for (BreadthFirstSearchElement breadthFirstSearchElement : v)
			if(breadthFirstSearchElement.equalsStr(strActual) && breadthFirstSearchElement.getPrevious().equalsStr(strPrev))
				return true;
		return false;
	}
	
}

class BreadthFirstSearchElement{
	private Vertex vertex;
	private Map<String, Double> neighbors = new HashMap<String, Double>();
	private BreadthFirstSearchElement previous = null;
	private int level;
	private double weight;
	
	public Vertex getVertex(){
		return vertex;
	}
	
	public Map<String, Double> getNeighbors(){
		return neighbors;
	}
	
	public int getLevel(){
		return level;
	}
	
	public void setPrevious(BreadthFirstSearchElement bfsElement){
		this.previous = bfsElement;
	}
	
	public BreadthFirstSearchElement getPrevious(){
		return previous;
	}
	
	BreadthFirstSearchElement(Vertex vertex, int level, double weight){
		this.vertex = vertex;
		this.level = level;
		this.weight = weight;
	}
	
	void setWeight(double w){
		this.weight = w;
	}
	
	double getWeight(){
		return weight;
	}
	
	void setNeighbors(Map<String, Double> neighbors){
		this.neighbors = neighbors;
	}
	
	public String toString(){
		String res = "";
		String previosName = previous != null ? previous.vertex.getCode() : "-";
		return res + vertex.getCode() + "[" + previosName + "," + level + "]";
	}
	
	String printTrace(){
		String res = this != this.previous ? previous.printTrace() + " > " : "";
		return res + this.toString();
	}
	
	public boolean equalsStr(String str){
		return this.vertex.getCode().equals(str);
	}
}