package net.coderodde.libid.support;

import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Deque;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import net.coderodde.libid.NodeExpander;

public final class BidirectionalIterativeDeepeningDepthFirstSearch<N> {

    private final N source;
    private final Deque<N> backwardSearchStack;
    private final Set<N> frontier;
    private final NodeExpander<N> forwardExpander;
    private final NodeExpander<N> backwardExpander;
    
    public BidirectionalIterativeDeepeningDepthFirstSearch() {
        this.source              = null;
        this.backwardSearchStack = null;
        this.frontier            = null;
        this.forwardExpander     = null;
        this.backwardExpander    = null;
    }
    
    private BidirectionalIterativeDeepeningDepthFirstSearch(
        N source,
        NodeExpander<N> forwardExpander,
        NodeExpander<N> backwardExpander) {
        this.source              = source;
        this.backwardSearchStack = new ArrayDeque<>();
        this.frontier            = new HashSet<>();
        this.forwardExpander     = forwardExpander;
        this.backwardExpander    = backwardExpander;
    }
    
    public List<N> search(N source, 
                          N target, 
                          NodeExpander<N> forwardExpander,
                          NodeExpander<N> backwardExpander) {
        // Handle the easy case. We need this in order to terminate the 
        // recursion in buildPath.
        if (source.equals(target)) {
            return new ArrayList<>(Arrays.asList(source));
        }
        
        BidirectionalIterativeDeepeningDepthFirstSearch<N> state = 
                new BidirectionalIterativeDeepeningDepthFirstSearch<>(
                        source,
                        forwardExpander,
                        backwardExpander);
        
        for (int depth = 0;; ++depth) {
            // Do a depth limited search in forward direction. Put all nodes at 
            // depth == 0 to the frontier.
            state.depthLimitedSearchForward(source, depth);
            
            // Perform a reversed search starting from the target node and 
            // recurring to the depth 'depth'.
            N meetingNode = state.depthLimitedSearchBackward(target, depth);
            
            if (meetingNode != null) {
                return state.buildPath(meetingNode);
            }
            
            state.backwardSearchStack.clear();
            
            // Perform a reversed search once again with depth = 'depth + 1'.
            // We need this in case the shortest path has odd number of arcs.
            meetingNode = state.depthLimitedSearchBackward(target, depth + 1);
            
            if (meetingNode != null) {
                return state.buildPath(meetingNode);
            }
            
            state.backwardSearchStack.clear();
            // Wipe out the frontier.
            state.frontier.clear();
        }
    }
    
    private void depthLimitedSearchForward(N node, int depth) {
        if (depth == 0) {
            frontier.add(node);
            return;
        }
        
        for (N child : forwardExpander.expand(node)) {
            depthLimitedSearchForward(child, depth - 1);
        }
    }
    
    private N depthLimitedSearchBackward(N node, int depth) {
        backwardSearchStack.addFirst(node);
        
        if (depth == 0) {
            if (frontier.contains(node)) {
                return node;
            }
            
            backwardSearchStack.removeFirst();
            return null;
        }
        
        for (N parent : backwardExpander.expand(node)) {
            N meetingNode = depthLimitedSearchBackward(parent, depth - 1);
            
            if (meetingNode != null) {
                return meetingNode;
            } 
        }
        
        backwardSearchStack.removeFirst();
        return null;
    }
    
    private List<N> buildPath(N meetingNode) {
        List<N> path = new ArrayList<>();
        List<N> prefixPath = 
                new BidirectionalIterativeDeepeningDepthFirstSearch<N>()
                        .search(source, 
                                meetingNode, 
                                forwardExpander, 
                                backwardExpander);
        path.addAll(prefixPath);
        path.remove(path.size() - 1);
        path.addAll(backwardSearchStack);
        return path;
    }
}
