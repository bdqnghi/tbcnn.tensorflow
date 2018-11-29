package com.samsung.android.multidisplay.common.datastructure;

import android.util.Log;
import com.samsung.android.multidisplay.common.ContextRelationManager;
import com.samsung.android.multidisplay.common.datastructure.graph.Edge;
import com.samsung.android.multidisplay.common.datastructure.graph.Graph;
import com.samsung.android.multidisplay.common.datastructure.graph.Vertex;
import java.util.ArrayList;
import java.util.Iterator;

public class DepthFirstSearch<E> {
    private static final boolean DEBUG = ContextRelationManager.DEBUG;
    private static final String TAG = "DepthFirstSearch";
    private final Graph<E> mGraph;

    public DepthFirstSearch(Graph<E> graph) {
        if (graph == null) {
            throw new NullPointerException("graph is null");
        }
        this.mGraph = graph;
    }

    public boolean marked(Vertex<E> v) {
        return v.marked;
    }

    public ArrayList<Vertex<E>> doDfsForAllVertices() {
        if (DEBUG) {
            Log.d(TAG, "doDfsForAllVertices");
        }
        ArrayList<Vertex<E>> traversedVertices = new ArrayList();
        if (this.mGraph.vertices().size() > 0) {
            Iterator i$ = getRootVertices().iterator();
            while (i$.hasNext()) {
                Vertex<E> v = (Vertex) i$.next();
                if (!v.marked) {
                    doDfs(v, traversedVertices);
                }
            }
            reinitializeVertices();
        }
        return traversedVertices;
    }

    private void reinitializeVertices() {
        Iterator i$ = this.mGraph.vertices().iterator();
        while (i$.hasNext()) {
            ((Vertex) i$.next()).marked = false;
        }
    }

    public ArrayList<Vertex<E>> getRootVertices() {
        ArrayList<Vertex<E>> rootVertices = new ArrayList();
        for (int i = 0; i < this.mGraph.vertices().size(); i++) {
            Vertex<E> vertex = (Vertex) this.mGraph.vertices().get(i);
            if (this.mGraph.parentVertex(vertex) == null) {
                rootVertices.add(vertex);
            }
        }
        return rootVertices;
    }

    private ArrayList<Vertex<E>> doDfs(Vertex<E> v, ArrayList<Vertex<E>> outTraversedVertices) {
        if (!v.marked) {
            outTraversedVertices.add(v);
            v.marked = true;
        }
        for (int i = 0; i < v.incidenceList.size(); i++) {
            Vertex<E> vertex = this.mGraph.destination((Edge) v.incidenceList.get(i));
            if (!vertex.marked) {
                doDfs(vertex, outTraversedVertices);
            }
        }
        return outTraversedVertices;
    }

    public void getDescendantsOf(Vertex<E> v, ArrayList<Vertex<E>> outDescendantList) {
        if (DEBUG) {
            Log.d(TAG, "getDescendantsOf " + v);
        }
        addDescendants(v, outDescendantList);
        outDescendantList.remove(0);
        reinitializeVertices();
    }

    private void addDescendants(Vertex<E> v, ArrayList<Vertex<E>> outDescendantList) {
        if (!v.marked) {
            if (DEBUG) {
                Log.d(TAG, "Adding descendant " + v);
            }
            v.marked = true;
            outDescendantList.add(v);
        }
        for (int i = 0; i < this.mGraph.childVertices(v).size(); i++) {
            addDescendants((Vertex) this.mGraph.childVertices(v).get(i), outDescendantList);
        }
    }

    public Vertex<E> getLeaf(Vertex<E> v) {
        Vertex<E> leaf = null;
        Log.d(TAG, "Finding leaf of subgraph " + v);
        if (!v.marked && this.mGraph.childVertices(v).size() == 0) {
            return v;
        }
        v.marked = true;
        for (int i = 0; i < this.mGraph.childVertices(v).size(); i++) {
            Vertex<E> childVertex = (Vertex) this.mGraph.childVertices(v).get(i);
            if (!childVertex.marked) {
                leaf = getLeaf(childVertex);
                if (leaf != null) {
                    break;
                }
            }
        }
        reinitializeVertices();
        return leaf;
    }
}
