package com.pranesh.revision;

/**
 * Created by sai pranesh on 6/6/2017.
 */
public class RevisionMain {
    public static void main(String args[]){


        PassByValue passByValue = new PassByValue();

        SampleClass sampleClass = new SampleClass(2 , 3 );

        System.out.println(sampleClass);

        passByValue.changeSampleClass(sampleClass, 50 , 45);

        System.out.println(sampleClass);

       /* BreadthFirstSearch breadthFirstSearch = new BreadthFirstSearch(20);
        DepthFirstSearch depthFirstSearch = new DepthFirstSearch(20);

        breadthFirstSearch.addVertex('A');
        breadthFirstSearch.addVertex('B');
        breadthFirstSearch.addVertex('C');
        breadthFirstSearch.addVertex('D');
        breadthFirstSearch.addVertex('E');
        breadthFirstSearch.addVertex('F');
        breadthFirstSearch.addVertex('G');
        breadthFirstSearch.addVertex('H');

        breadthFirstSearch.addEdge(0 ,1 );
        breadthFirstSearch.addEdge(1 ,2 );
        breadthFirstSearch.addEdge(0 ,3 );
        breadthFirstSearch.addEdge(3 ,4 );
        breadthFirstSearch.addEdge(4 ,5 );
        breadthFirstSearch.addEdge(4 ,6 );

        breadthFirstSearch.bfs();

        System.out.println();

        depthFirstSearch.addVertex('A');
        depthFirstSearch.addVertex('B');
        depthFirstSearch.addVertex('C');
        depthFirstSearch.addVertex('D');
        depthFirstSearch.addVertex('E');
        depthFirstSearch.addVertex('F');
        depthFirstSearch.addVertex('G');
        depthFirstSearch.addVertex('H');

        depthFirstSearch.addEdge(0 ,1 );
        depthFirstSearch.addEdge(1 ,2 );
        depthFirstSearch.addEdge(0 ,3 );
        depthFirstSearch.addEdge(3 ,4 );
        depthFirstSearch.addEdge(4 ,5 );
        depthFirstSearch.addEdge(4 ,6 );

        depthFirstSearch.dfs();*/




    }
}
