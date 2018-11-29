import java.io.IOException;
import java.util.LinkedList;
import java.util.Queue;

public class BFS extends Search {
	Queue<Node> queue = new LinkedList<Node>();
	public static void main(String[] args) throws IOException {
		BFS bfs= new BFS();
		bfs.readInput();
		bfs.queue.add(bfs.startNode);
		Node end = bfs.search();
		bfs.findPath(end);
		System.out.println("Path Cost: "+bfs.pathCost);
		System.out.println("Nodes Expanded: "+bfs.nodesExpanded);
		System.out.println("Max Depth: "+bfs.maxDepth);
		System.out.println("Maximum size of the frontier: "+bfs.maxFrontierSize);
		bfs.printMaze();
		//System.out.println(end.xPos+":"+end.yPos);
	}

	private Node search() {
		while(!queue.isEmpty()){
			if(queue.size()>maxFrontierSize)
				maxFrontierSize = queue.size();
			Node node = queue.remove();
			nodesExpanded++;
			int xPos = node.xPos, yPos = node.yPos;
			//System.out.println(xPos+";"+yPos);
			if(maze.get(yPos).charAt(xPos)=='.')
				return node;
			if(maze.get(yPos).charAt(xPos+1)!='%'){
				Node child = new Node(xPos+1,yPos,node,node.depth+1);
				if(node.depth+1>maxDepth)
					maxDepth = node.depth+1;
				if(visited[xPos+1][yPos]!=1){
					visited[xPos+1][yPos]=1;
					queue.add(child);
				}
			}
			if(maze.get(yPos-1).charAt(xPos)!='%'){
				Node child = new Node(xPos,yPos-1,node,node.depth+1);
				if(node.depth+1>maxDepth)
					maxDepth = node.depth+1;
				if(visited[xPos][yPos-1]!=1){
					visited[xPos][yPos-1]=1;
					queue.add(child);
				}
			}
			if(maze.get(yPos+1).charAt(xPos)!='%'){
				Node child = new Node(xPos,yPos+1,node,node.depth+1);
				if(node.depth+1>maxDepth)
					maxDepth = node.depth+1;
				if(visited[xPos][yPos+1]!=1){
					visited[xPos][yPos+1]=1;
					queue.add(child);
				}
			}
			if(maze.get(yPos).charAt(xPos-1)!='%'){
				Node child = new Node(xPos-1,yPos,node,node.depth+1);
				if(node.depth+1>maxDepth)
					maxDepth = node.depth+1;
				if(visited[xPos-1][yPos]!=1){
					visited[xPos-1][yPos]=1;
					queue.add(child);
				}
			}
		}
		return null;
	}

}
