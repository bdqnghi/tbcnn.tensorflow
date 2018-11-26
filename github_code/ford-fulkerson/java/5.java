/**
 * TCSS543 Winter 2015 Empirical Study Project
 * Ford-Fulkerson algorithm Implementation
 * @author Xavier Xu
 */

import java.util.Iterator;
public class Ford_Fulkerson {
    /**
     * Find the maximum flow using Ford-Fulkerson algorithm
     * @param graph input graph
     * @param s source
     * @param t sink
     * @return the max flow of the graph
     * @throws Exception
     */
    @SuppressWarnings("rawtypes")
    public static int maxFlow(SimpleGraph graph, Vertex s, Vertex t) throws Exception{

        int flow = 0;
        int current = 0;
        int maxcap = 0;
        SimpleGraph risidualGraph;
        Iterator itr;
        Edge edge;
        Vertex vert;
        Vertex prev;
        FFVertexInfo vertInfo = new FFVertexInfo();
        FFEdgeInfo edgeInfo;

        itr = graph.edges();
        while (itr.hasNext()) {
            edge = (Edge) itr.next();
            int edgeData = ((Double)edge.getData()).intValue();
            edgeInfo = new FFEdgeInfo(edgeData, 0);
            edge.setData(edgeInfo);
            maxcap = Math.max(maxcap, edgeInfo.getCapacity());
        }
        
        itr = graph.vertices();
        while (itr.hasNext()) {
            vert = (Vertex) itr.next();
            vertInfo.setVisited(false);
            vert.setData(vertInfo);   
        }
        
        risidualGraph = FFAugPath.findAngPath(graph, s, t, new SimpleGraph(), 0);     

        while (risidualGraph.numEdges() > 0) {

            current = maxcap;
            prev = s;
            itr = risidualGraph.edges();
            
            while (itr.hasNext() ) {
                edge = (Edge) itr.next();
                edgeInfo = (FFEdgeInfo) edge.getData();
                if (edge.getFirstEndpoint() == prev) {
                    current = Math.min(current, edgeInfo.getAvailable());
                    prev = edge.getSecondEndpoint();
                } else {
                    current = Math.min(current, edgeInfo.getFlow());
                    prev = edge.getFirstEndpoint();
                }
            }

            prev = s;
            itr = risidualGraph.edges();
            while (itr.hasNext()) {
                edge = (Edge) itr.next();
                edgeInfo = (FFEdgeInfo) edge.getData();
                if (edge.getFirstEndpoint() == prev){
                    edgeInfo.setFlow(edgeInfo.getFlow()+ current);
                    prev = edge.getSecondEndpoint();
                } else {
                    edgeInfo.setFlow(edgeInfo.getFlow() - current);
                    prev = edge.getFirstEndpoint();
                }
            }
            
            flow = flow + current;
            itr = graph.vertices();
            
            while (itr.hasNext()) {
                vert = (Vertex) itr.next();
                vertInfo = (FFVertexInfo) vert.getData();
                vertInfo.setVisited(false);            
            }
            
            risidualGraph = FFAugPath.findAngPath(graph, s, t, new SimpleGraph(),0);
        }

        return flow;
    }

    @SuppressWarnings("rawtypes")
    public static void main(String[] args) throws Exception{
        SimpleGraph G = new SimpleGraph();
        Vertex s = null;
        Vertex t = null;
        Iterator itr;

        System.out.print("Please enter the full path of input graph: ");
        String userinput;
        userinput = KeyboardReader.readString();
        GraphInput.LoadSimpleGraph(G,userinput);

        itr= G.vertices();
        while (itr.hasNext()) {
            Vertex vert = (Vertex) itr.next();
            if (vert.getName().equals("s")) {
                s = vert;
            }else if (vert.getName().equals("t")) {
                t = vert;
            }
        }

        long startTime=System.currentTimeMillis();
        int flow = maxFlow(G, s, t);
        long endTime=System.currentTimeMillis();

        System.out.println("The max flow of this graph is " + flow);
        System.out.println("FF's running time is " + (endTime - startTime) + "ms");

    }
}
