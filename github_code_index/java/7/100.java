package companies.apple.experience;

import java.util.*;

/**
 * @author: zhang
 * @date: Mar 24, 2015 12:02:40 AM
 */
public class TopologicalSort {
    /*
    Given file dependencies like A->{B, C}, B->{D}, C->{D, E}, print below
    A->B->D
    A->C->D
    A->C->E

     */
    public static List<List<String>> topSort(Map<String, List<String>> dependencies) {
        Map<String, Integer> inCount = new HashMap<String, Integer>();
        List<List<String>> ret = new ArrayList<List<String>>();
        Set<String> roots = new HashSet<String>();

        for (String n : dependencies.keySet()) {
            if (!inCount.containsKey(n)) {
                roots.add(n);
            }

            for (String s : dependencies.get(n)) {
                if (inCount.containsKey(s)) {
                    inCount.put(s, inCount.get(s) + 1);
                } else {
                    inCount.put(s, 1);
                }

                if (roots.contains(s)) {
                    roots.remove(s);
                }
            }
        }

        ret.add(new ArrayList<String>(roots));
        topSort(inCount, dependencies, ret);

        return ret;
    }

    private static void topSort(Map<String, Integer> inCount, Map<String, List<String>> dependencies, List<List<String>> ret) {
        while (!inCount.isEmpty()) {
            List<String> newNodes = new ArrayList<String>();

            for (String node : ret.get(ret.size() - 1)) {
                if (dependencies.containsKey(node)) {
                    List<String> dependency = dependencies.get(node);
                    for (String n : dependency) {
                        int count = inCount.get(n);
                        inCount.put(n, count - 1);
                        if (count == 1) {
                            newNodes.add(n);
                            inCount.remove(n);
                        }
                    }
                }
            }

            ret.add(newNodes);
        }
    }
}
