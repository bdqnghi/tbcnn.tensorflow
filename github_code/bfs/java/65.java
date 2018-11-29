package com.algorithms;

import java.util.LinkedList;

public class BFS {

    static int[] getDistsFromStart(LinkedList[] graph, Vertex start) {
        LinkedList<Vertex> q = new LinkedList<>();
        q.push(start);
        int[] dists = new int[graph.length];
        for (int j = 0; j < dists.length; j++) {
            dists[j] = -1;
        }
        dists[start.num] = 0;
        while (!q.isEmpty()) {
            Vertex u = q.pop();
            for (int j = 0; j < graph[u.num].size(); j++) {
                Vertex v = (Vertex) graph[u.num].get(j);
                if (v.pre == null || dists[v.num] > (u.dist + 1)) {
                    v.color = 1;
                    v.pre = u;
                    q.push(v);
                    v.dist = dists[v.num] != -1 ? Math.min(dists[v.num], u.dist + 1) : u.dist + 1;
                    dists[v.num] = v.dist;
                }
            }
            u.color = 2;
        }
        return dists;
    }
}
