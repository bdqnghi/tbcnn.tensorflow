/**
 * $Id: SearchBreadthFirst.java 3658 2007-10-15 16:29:11Z schapira $
 *
 * Part of the open-source Proximity system
 *   (see LICENSE for copyright and license information).
 *
 */

package kdl.prox.nsi2.search;

import kdl.prox.nsi2.graph.Graph;
import kdl.prox.nsi2.graph.Node;
import kdl.prox.nsi2.util.ConversionUtils;
import org.apache.log4j.Logger;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;

/**
 * Performs a bidirectional breadth-first search.  The returned SearchResults instance does not contain
 * the found path, only the path length.
 */

public class SearchBreadthFirst implements Search {
    private static Logger log = Logger.getLogger(SearchBreadthFirst.class);
    private static final int BREADTH_FIRST_MAX = 1000;
    private Graph graph;

    public SearchBreadthFirst(Graph graph) {
        this.graph = graph;
    }

    public PathlessSearchResults search(int source, int target) {
        PathlessSearchResults psr = new PathlessSearchResults();
        psr.startTimer();

        if (source == target) {
            psr.setPathlength(0);
            psr.addExplored(source);
            psr.stopTimer();
            return psr;
        }

        List<Integer> frontier1 = new ArrayList<Integer>();
        List<Integer> frontier2 = new ArrayList<Integer>();
        frontier1.add(source);
        frontier2.add(target);

        List<Integer> expanded = new ArrayList<Integer>();

        int pathLength = 0;

        while (true) {
            if (++pathLength > BREADTH_FIRST_MAX) {
                log.debug("Bailing on bidir search for " + source + " - " + target);
                pathLength = -1;
                break;
            }

            List<Integer> frontierNeighbors1 = new ArrayList<Integer>(ConversionUtils.nodesToIntegers(graph.getNeighbors(frontier1)));
            expanded.addAll(frontier1);

            frontier1 = frontierNeighbors1;

            if (frontier1.size() == 0) {
                log.debug("unreachable search: source " + source + ",  target " + target + ", empty frontier1");
                log.debug("frontier2: " + frontier2.size());
                log.debug("pathLength: " + pathLength);
                pathLength = -1;
                break;
            }

            List<Integer> intersection = new ArrayList<Integer>(frontier1);
            intersection.retainAll(frontier2);
            if (intersection.size() > 0) {
                break;
            }

            if (++pathLength > BREADTH_FIRST_MAX) {
                log.debug("Bailing on bidir search for " + source + " - " + target);
                pathLength = -1;
                break;
            }

            List<Integer> frontierNeighbors2 = new ArrayList<Integer>(ConversionUtils.nodesToIntegers(graph.getNeighbors(frontier2)));
            expanded.addAll(frontier2);

            frontier2 = frontierNeighbors2;

            if (frontier2.size() == 0) {
                log.debug("unreachable search: source " + source + ",  target " + target + ", empty frontier1");
                log.debug("frontier1: " + frontier1.size());
                log.debug("pathLength: " + pathLength);
                pathLength = -1;
                break;
            }

            intersection = new ArrayList<Integer>(frontier1);
            intersection.retainAll(frontier2);
            if (intersection.size() > 0) {
                break;
            }

            frontier1.removeAll(expanded);
            frontier2.removeAll(expanded);
        }

        psr.setPathlength(pathLength);
        psr.addExplored(new HashSet<Integer>(expanded));
        psr.stopTimer();
        return psr;

    }

    private class PathlessSearchResults extends SearchResults {
        private int pathlength;

        public PathlessSearchResults() {
            super();
            this.pathlength = -1;
            this.path = null;
        }

        public double pathlength() {
            return this.pathlength;
        }

        public void setPathlength(int pathlength) {
            this.pathlength = pathlength;
        }

        public List<Node> pathList() {
            log.warn("Cannot return path for breadth-first search!");
            return null;
        }
    }

    public void setGraph(Graph graph) {
        this.graph = graph;
    }

}
