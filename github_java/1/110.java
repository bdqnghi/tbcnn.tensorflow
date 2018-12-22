package org.patika.mada.algorithm;

import org.patika.mada.graph.Node;
import org.patika.mada.graph.GraphObject;
import java.util.Set;
import java.util.Map;
import java.util.HashMap;
import java.util.HashSet;

/**
 * Finds the paths from a specified source set of states or entities to a
 * specified target set of states or entities within the boundaries of a
 * specified length limit. Takes source set, target set, type of distance
 * limit, distance limit and strict value. Based on these parameters, the
 * interactions within source set and within target set may be omitted and/or
 * "shortest+k" may be used as length limit.
 *
 * @author Ozgun Babur
 * @author Merve Cakir
 */
public class LocalPoIQuery
{
    /**
     * The set of nodes from which the paths of interests should start.
     */
    private Set<Node> sourceSet;

    /**
     * The set of nodes to which the paths of interests should arrive.
     */
    private Set<Node> targetSet;

    /**
     * True if length limit is used, false if shortes+k is used.
     */
    private boolean limitType;

    /**
     * Based on the limitType, given integer may be used directly as stop
     * distance or may be added up with the shortest path's length and used as
     * stop distance.
     */
    private int stopDistance;

    /**
     * When true, the interactions within source set and within target set are
     * not involved in result set.
     */
    private boolean strict;

    /**
     * Constructor
     */
    public LocalPoIQuery(Set<Node> sourceSet,
        Set<Node> targetSet,
        boolean limitType,
        int stopDistance,
        boolean strict)
    {
        this.sourceSet = sourceSet;
        this.targetSet = targetSet;
        this.limitType = limitType;
        this.stopDistance = stopDistance;
        this.strict = strict;
    }

    public Set<GraphObject> run()
    {
        /**
         * Candidate contains all the graph objects that are the results of BFS.
         * Eliminating nodes from candidate according to their labels will
         * yield result.
         */
        Map<GraphObject, Integer> candidate =
                new HashMap<GraphObject, Integer>();
        Set<GraphObject> result = new HashSet<GraphObject>();

        BFS bfsFwd = null;
        BFS bfsRev = null;

        if (limitType == NORMAL_LIMIT && !strict)
        {
            bfsFwd = new BFS(sourceSet, null, true, stopDistance);
            bfsRev = new BFS(targetSet, null, false, stopDistance);
        }
        else if (limitType == NORMAL_LIMIT && strict)
        {
            bfsFwd = new BFS(sourceSet, targetSet, true, stopDistance);
            bfsRev = new BFS(targetSet, sourceSet, false, stopDistance);
        }
        else if (limitType == SHORTEST_PLUS_K && !strict)
        {
            bfsFwd = new BFS(sourceSet, null, true, 25);
            bfsRev = new BFS(targetSet, null, false, 25);
        }
        else if (limitType == SHORTEST_PLUS_K && strict)
        {
            bfsFwd = new BFS(sourceSet, targetSet, true, 25);
            bfsRev = new BFS(targetSet, sourceSet, false, 25);
        }

        candidate.putAll(bfsFwd.run());
        candidate.putAll(bfsRev.run());

        if(limitType)
        {
            /**
             * Only the graph objects whose sum of two search labels being
             * smaller than or equal to the distance limit will be in the result.
             */
            for (GraphObject go : candidate.keySet())
            {
                if ((bfsFwd.getLabel(go) + bfsRev.getLabel(go)) <= stopDistance)
                {
                    result.add(go);
                }
            }
        }
        else
        {
            int shortestPath = Integer.MAX_VALUE;

            /**
             * Summing up the labels of two search will give the length of the
             * path that passes through that particular graph object and the
             * minimum of those lengths will be the length of the shortest path.
             */
            for (GraphObject go : candidate.keySet())
            {
                if ((bfsFwd.getLabel(go) + bfsRev.getLabel(go)) <= shortestPath)
                {
                    shortestPath = (bfsFwd.getLabel(go) + bfsRev.getLabel(go));
                }
            }

	        // Proceed only if there is a shortest path found

	        if (shortestPath < Integer.MAX_VALUE / 2)
	        {
				/**
				 * Only the graph objects whose sum of two search labels being
				 * smaller than or equal to the "shortest + limit" will be in the
				 * result.
				 */
				for (GraphObject go : candidate.keySet())
				{
					if ((bfsFwd.getLabel(go) + bfsRev.getLabel(go)) <=
						(shortestPath + stopDistance))
					{
						result.add(go);
					}
				}
	        }
        }
        
        return result;
    }

	/**
	 * Limit types
	 */

	public static final boolean SHORTEST_PLUS_K = false;
	public static final boolean NORMAL_LIMIT = true;
}
