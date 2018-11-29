/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package datastructures.graphs.dfs;

import datastructures.graphs.Vertex;
import datastructures.linkedlist.List;
import datastructures.stack.ArrayStack;
import datastructures.stack.Stack;

/**
 *
 * @author Denny Oommen Mathew <denny@dennymathew.com>
 */
public class DFS<Item> {

    public enum DFS_MODE {
        STACK,
        RECURSIVE
    }

    private Stack<Vertex> vertices;

    public DFS() {
        vertices = new ArrayStack<>();
    }

    public void traverse(List<Vertex<Item>> vertices, DFS_MODE dfsMode) {

        for (Vertex v : vertices) {
            if (!v.isVisted()) {
                v.setVisted(true);
                if (dfsMode == DFS_MODE.STACK) {
                    dfsUsingStack(v);
                } else {
                    dfsUsingRecursion(v);
                }
            }
        }
    }

    private void dfsUsingRecursion(Vertex<Item> vertex) {
        System.out.print(vertex + " ");
        
        for(Vertex<Item> v : vertex.getNeighbourVertices()) {
            if(!v.isVisted()) {
                v.setVisted(true);
                dfsUsingRecursion(v);
            }
        }
    }

    private void dfsUsingStack(Vertex<Item> root) {

        vertices.push(root);
        root.setVisted(true);

        while (!vertices.isEmpty()) {
            Vertex<Item> currentVertex = vertices.pop();
            System.out.print(currentVertex + " ");

            for (Vertex<Item> ne : currentVertex.getNeighbourVertices()) {
                if (!ne.isVisted()) {
                    ne.setVisted(true);
                    vertices.push(ne);
                }
            }
        }

    }

}
