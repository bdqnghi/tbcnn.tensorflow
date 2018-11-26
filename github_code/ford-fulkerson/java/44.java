package de.futjikato.gka.streams;

import de.futjikato.gka.Vertex;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

public class FordFulkersonVertex extends Vertex<FordFulkersonVertex> {

    public static final int DIRECTION_OUT = 1;
    public static final int DIRECTION_IN = 2;
    public static final int DIRECTION_UNDEF = 0;

    private boolean marked = false;

    private int markingDirection;

    private FordFulkersonVertex markedPartner;

    private double delta;

    private boolean inspected = false;

    private List<FordFulkersonVertex> reverseNeighbors = new LinkedList<FordFulkersonVertex>();

    public FordFulkersonVertex(String name) {
        super(name);
    }

    public boolean isMarked() {
        return marked;
    }

    public void setMarked(int direction, double delta, FordFulkersonVertex partner) {
        this.marked = true;
        this.markingDirection = direction;
        this.delta = delta;
        this.markedPartner = partner;
    }

    public boolean isInspected() {
        return inspected;
    }

    public void setInspected(boolean inspected) {
        this.inspected = inspected;
    }

    public void reverseConnect(FordFulkersonVertex vertex) {
        if(!reverseNeighbors.contains(vertex)) {
            reverseNeighbors.add(vertex);
        }
    }

    public List<FordFulkersonVertex> getReverseVertices() {
        return new ArrayList<FordFulkersonVertex>(reverseNeighbors);
    }

    public double getDelta() {
        return delta;
    }

    public int getMarkingDirection() {
        return markingDirection;
    }

    public FordFulkersonVertex getMarkedPartner() {
        return markedPartner;
    }

    public void resetMarking() {
        markedPartner = null;
        delta = 0d;
        marked = false;
    }
}
