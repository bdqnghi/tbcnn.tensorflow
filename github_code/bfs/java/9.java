package search.algorithms;

import search.Explorable;
import search.Status;

import java.util.*;

/**
 * Created by alde on 5/28/18.
 */
public class BFS<T> implements ISearch {

    @Override public Status search(Explorable initial) {
        long iniTime = System.currentTimeMillis();
        Queue<Explorable> nodes = new LinkedList<Explorable>();
        nodes.add(initial);
        Explorable currentSol = initial;
        Map<String, String> statuses = new HashMap<String, String>();
        statuses.put(initial.getKey(), initial.getKey());
        while (!nodes.isEmpty()) {
            Explorable currentNode = nodes.poll();

            if (currentNode.isFinal()) {
                currentSol = currentNode;
                break;
            }
            if(currentNode.isBetter(currentSol)){
                currentSol = currentNode;
            }

            List<Explorable<T>> childs = currentNode.expand();
            for (Explorable<T> newNode : childs) {
                if (statuses.get(newNode.getKey()) != null) {
                    continue;
                }
                statuses.put(newNode.getKey(), newNode.getKey());
                nodes.add(newNode);
            }

        }
        System.err.println("Time : "+(System.currentTimeMillis() - iniTime));
        return currentSol;
    }
}
