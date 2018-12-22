package com.vaibhavsahu.BFS;

import java.util.LinkedList;
import java.util.Queue;

/**
 * Created by vaibhavsahu on 12/25/16.
 */

//BFS Implementation

public class BreadthFirstSearch {

    public void doDFS(vertex source){
        Queue<vertex> queue = new LinkedList<>();

        //mark the source as visited
        source.setVisited(true);

        //add the visited vertex to the queue
        queue.add(source);

        //check if queue is not empty
        while(!queue.isEmpty()){
            //remove the vertex from the queue

            vertex actualVertex = queue.remove();

            //print the information of removed node from the queue to the console
            System.out.println(actualVertex.getData());

            //visit neighbors of the removed vertex
            for (vertex v: actualVertex.getNeighborList()){
                //check if it is visited or not
                if(!v.isVisited()){
                    v.setVisited(true);
                    queue.add(v);
                }
            }
        }

    }
}
