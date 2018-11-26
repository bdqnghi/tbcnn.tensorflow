import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

public class Main03
{
    public static void main(String args[])
    {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder out = new StringBuilder();
        try
        {
            int testCases = Integer.parseInt(br.readLine());

            for (int testCase = 1; testCase <= testCases; ++testCase)
            {
                StringTokenizer st = new StringTokenizer(br.readLine());
                int n = Integer.parseInt(st.nextToken()); // number of intersections
                int m = Integer.parseInt(st.nextToken()); // number of roads

                ArrayList<Edge> adj = new ArrayList<>();
                // Reads in edge information
                for (int i = 0; i < m; ++i)
                {
                    StringTokenizer line = new StringTokenizer(br.readLine());
                    int intersection1 = Integer.parseInt(line.nextToken());
                    int intersection2 = Integer.parseInt(line.nextToken());
                    // We negate the weight and run kruskal's algorithm normally to find a max-spanning tree
                    int weight = Integer.parseInt(line.nextToken()) * -1;
                    adj.add(new Edge(intersection1, intersection2, weight, i));
                }

                int maxiumCapacity = kruskal(adj, n);

                // Output
                String output = "Case #" + testCase + ": " + maxiumCapacity + "\n";
                out.append(output);
            } // End of the test cases
			System.out.print(out);
        }
        catch (IOException e)
        {e.printStackTrace();}

    } // End of the main method

    private static int kruskal(ArrayList<Edge> adj, int n)
    {
        PriorityQueue<Edge> pq = new PriorityQueue<>();
        for (Edge edge : adj)
            pq.add(edge);

        // Sets up which set each one is in
        HashMap<Integer, Integer> map = new HashMap<>();
        for (int i = 0; i < n; ++i)
            map.put(i,i);

        int [] setSize = new int[n];
        Arrays.fill(setSize, 1);

        // Runs through kruskals
        ArrayList<Edge> minimumSpanningTree = new ArrayList<>();
        while ((pq.size() != 0) && (minimumSpanningTree.size() != n))
        {
//            //TODO remove after
//            System.out.println("#########START#########");
//            for (int i = 0; i < n; ++i)
//                System.out.print(" " + map.get(i));
//            System.out.println("\n#########END#########");

            Edge minEdge = pq.remove();
            if (map.get(minEdge.city1).compareTo(map.get(minEdge.city2)) != 0)
            {
                minimumSpanningTree.add(minEdge);

                // Chooses which set to subsume to
                int biggerSet;
                int littleSet;
                if (setSize[map.get(minEdge.city1)] >= setSize[map.get(minEdge.city2)])
                {
                    biggerSet = map.get(minEdge.city1);
                    littleSet = map.get(minEdge.city2);
                }
                else
                {
                    biggerSet = map.get(minEdge.city2);
                    littleSet = map.get(minEdge.city1);
                }

                // Updates all to the new set value
                for (Map.Entry<Integer, Integer> entry : map.entrySet())
                {
                    int city = entry.getKey();
                    int set = entry.getValue();

                    if (set == littleSet)
                    {
//                        System.out.println("Subsuming to city set: " + biggerSet);
                        map.put(city, biggerSet);
                    }


                    // TODO remove old implementation
//                    if ((set == minEdge.city1) || (set == minEdge.city2))
//                    {
//                        if (setSize[map.get(minEdge.city1)] > setSize[map.get(minEdge.city2)])
//                        {
//                            System.out.println("Subsuming to city " + minEdge.city1 + "'s set: " + map.get(minEdge.city1));
//                            map.put(city, map.get(minEdge.city1));
//                            setSize[minEdge.city1] +=1;
//                        }
//                        else
//                        {
//                            System.out.println("Subsuming to city " + minEdge.city2 +  "'s set: " + map.get(minEdge.city2));
//                            map.put(city, map.get(minEdge.city2));
//                            setSize[minEdge.city2] += 1;
//                        }
//                    }
                }
            }
        }

        //TODO test remove after
//        System.out.println("--------------------------------");
//        for (int i = 0; i < minimumSpanningTree.size(); ++i)
//            System.out.println(minimumSpanningTree.get(i).city1 + " " +
//                    minimumSpanningTree.get(i).city2 + " " +
//                    minimumSpanningTree.get(i).weight);
//        System.out.println("--------------------------------");

        // Finds the max
        int max = minimumSpanningTree.get(0).weight;
        for (Edge edge : minimumSpanningTree)
            if (edge.weight > max)
                max = edge.weight;

        // Flips the max and returns the minimum capacity
        max *= -1;
        return max;
    } // End of kruskal's algorithm

    public static class Edge implements Comparable<Edge>
    {
        int city1;
        int city2;
        int weight;
        int set;

        public Edge(int city1, int city2, int weight, int set) {
            this.city1 = city1;
            this.city2 = city2;
            this.weight = weight;
            this.set = set;
        }

        @Override
        public int compareTo(Edge o) {
            if (weight < o.weight)
                return -1;
            else if (weight > o.weight)
                return 1;
            else
                return 0;
        }
    }

} // End of the main class
