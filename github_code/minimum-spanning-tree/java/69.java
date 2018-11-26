package graphy;

import graphy.GraphElements.MyEdge;
import graphy.GraphElements.MyVertex;
import graphy.GraphElements.MyVertexFactory;

import java.util.Comparator;
import java.util.HashSet;
import java.util.Set;
import org.apache.commons.collections15.buffer.PriorityBuffer;

/**
 *
 * @author pingu
 */

public class PrimsVisualizer extends AlgorithmVisualizer {
    
    Set<MyVertex> S;
    private PriorityBuffer edgeBuffer;          /* Heap for all the edges */
    private Set<MyEdge> minimumSpanningTree;    /* The set containing the edges of the minimum spanning tree */

    private int minimumWeight;
    private boolean onlyMinEdgeMarked = true;
    
    /* Constructor */
    public PrimsVisualizer(MyGraphVisualizer graphy) {
        super(graphy);
    }

    @Override
    protected void initialize() {

        if (MyVertexFactory.sourceVertex == null) {
            MyGraphVisualizer.informationPanel.info.append("You'll need to select a source vertex first; choose one by right-clicking on the vertex");
            return;
        }
        
        super.initialize();

        MyGraphVisualizer.informationPanel.info.append("\nInitializing Prim's algorithm: ");

        vv.getRenderContext().getPickedVertexState().clear();   /* Clear all picked vertices */
        vv.getRenderContext().getPickedEdgeState().clear(); /* Clear all picked edges */

        /* Initialize the minimum spanning tree edge set */
        minimumSpanningTree = new HashSet<MyEdge>(graph.getEdgeCount());
        MyGraphVisualizer.informationPanel.info.append("MST Edge Set: " + minimumSpanningTree);

        /* Create a priority buffer to hold the current edge set */
        edgeBuffer = new PriorityBuffer(graph.getEdgeCount(), true, new Comparator<MyEdge>() {
            public int compare (MyEdge o1, MyEdge o2) {
                    if (o1.getWeight() < o2.getWeight()) {
                            return -1;
                    }

                    if (o1.getWeight() > o2.getWeight()) {
                            return 1;
                    }
                    return 0;
            }
        });

        MyGraphVisualizer.informationPanel.info.append("Graph Edge Set: " + edgeBuffer);

        /* Initialize the vertex set S */
        S = new HashSet<MyVertex>(graph.getVertexCount());
        S.add(MyVertexFactory.sourceVertex);
        MyGraphVisualizer.informationPanel.info.append("Vertex Set S: " + S);
        vv.getRenderContext().getPickedVertexState().pick(MyVertexFactory.sourceVertex, true);

        minimumWeight = 0;
        running = true;
    }

    @Override
    public void step() {

        if (!running) {
            initialize();
        }

        else {            
           if (!(S.containsAll(graph.getVertices()))) {

                if (onlyMinEdgeMarked) {

                   edgeBuffer.clear();

                   /* First mark all the vertices in S */
                   for (MyVertex v : S) {
                       vv.getRenderContext().getPickedVertexState().pick(v, true);

                       /* Then mark all the edges incident from all the vertices in S */
                       /* Only add those edges which have one vertex in S and the other outside */
                       for (MyEdge e : graph.getIncidentEdges(v)) {

                            if ( !(S.contains(graph.getOpposite(v, e))) )
                                edgeBuffer.add(e);

                            vv.getRenderContext().getPickedEdgeState().pick(e, true);
                        }
                    }

                    MyGraphVisualizer.informationPanel.info.append("\nLooking at vertex set " + S + " and edge set " + edgeBuffer);
                    onlyMinEdgeMarked = false;

               } else {

                    /* Now mark only the minimum edge and the new vertex to be pushed */
                    vv.getRenderContext().getPickedEdgeState().clear();

                    MyEdge minEdge = (MyEdge) edgeBuffer.get();
                    minimumSpanningTree.add(minEdge);
                    minimumWeight = minimumWeight + minEdge.getWeight();

                    MyVertex u;     /* The vertex that is not in S, incident on the minimum edge */
                    if ( S.contains(graph.getEndpoints(minEdge).getFirst()) )
                        u = graph.getEndpoints(minEdge).getSecond();
                    else
                        u = graph.getEndpoints(minEdge).getFirst();

                    S.add(u);

                    for (MyVertex v : S)
                        vv.getRenderContext().getPickedVertexState().pick(v, true);

                    for (MyEdge e : minimumSpanningTree)
                        vv.getRenderContext().getPickedEdgeState().pick(e, true);

                    MyGraphVisualizer.informationPanel.info.append("Added minimum edge " + minEdge
                                                                    + " to the MST, and its opposite vertex " + u + " to S");
                    MyGraphVisualizer.informationPanel.info.append("MST Edge Set: " + minimumSpanningTree
                                                                    + "\nS: " + S);
                    onlyMinEdgeMarked = true;
               }
                
            } else {
                 MyGraphVisualizer.informationPanel.info.append("\nS contains all the vertices of the graph; algorithm terminated");
                 MyGraphVisualizer.informationPanel.info.append("Minimum weight: " + minimumWeight);
                 running = false;
                 terminate();
            }
        }
    }

    @Override
    public void reset() {
        super.reset();
        if (running) {
            minimumSpanningTree.clear();
            S.clear();
            edgeBuffer.clear();
            running = false;
            onlyMinEdgeMarked = true;
        }
    }

}
