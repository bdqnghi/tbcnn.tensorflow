import java.lang.Math;
import java.util.*;

/*

In Docker, building an image has dependencies. An image can only be built once 
its dependency is built (If the dependency is from outside, then the image can 
be built immediately). 

Sometimes, engineers make mistakes by forming a cycle dependency of local images. 
In this case, ignore the cycle and all the images depending on this cycle. 

Input is vector of pair of images (image, its dependency). 

Output the order of images to be built in order. 

##Example: 
``` 
Example 1: 
{{"master", "ubuntu"}, {"numpy", "master"}, {"tensorflow", "numpy"}} 
Output: master, numpy, tensorflow 

Example 2: 
{{"python", "numpy"}, {"numpy", "python"}, {"tensorflow", "ubuntu"}} 
Output: tensorflow 

Example 3: 
{{"b", "c"}, {"c", "d"}, {"a", "b"}, {"d", "e"}, {"e","c"}, {"f", "g"}} 
Ouput: f

Qs
==========
 * multiple right answers? return any right ans
 * cyclic & deps to itself
 deps: multiple or always single? Always single


1) BF -> MAP
 - ignoring cyclic deps
 create map
 iterate map
    resolve external deps
    accumulate resolved deps
    remove resolved imgs from map

iterate until map is empty

n.(n-1).(n-2)
TC: n!


 {{"master", "ubuntu"}, {"numpy", "master"}, {"tensorflow", "numpy"}} 
 Map{
    img1: deps1
    img2: deps2
    deps2: deps3
 }

----------
 Map{
    deps1: img1, img2
    deps2: img3, deps1
 }

 img1 deps2 img2

 2) BF -> Sort

img dep1, img2 dep1 , dep1 dep2


 {{"master", "ubuntu"}, {"numpy", "master"}, {"tensorflow", "numpy"}} 


 3) graph

reverse order of depth first traversal
 a - b - c - d
 x - y - z
 m - n

 1) figure external deps
 Map img -> dep helps


 2) traverse up from ext deps
 Map dep -> imgs
 skip cyclics (track of visited nodes)
 reverse order of this traversel is the ans

 TC:n SC:n overall

*/

class Solution {


    public static void main(String[] args) {
        Stack<String> st = resolveDepsWithTopSort(new String[][]{});

        while(st.isEmpty() == false) {
            System.out.print(st.pop() + " - ");
        }
        System.out.println();
    }

//TOPOLOGICAL SORT APPROACH:

    public static Stack<String> resolveDepsWithTopSort(String[][] deps) {
        HashMap<String, String[]> graph = createGraph(deps);        

        Set<String> visited = new HashSet<>();
        Stack<String> st = new Stack<>();

        // wrap in for loop 
        // String root = deps[0][0];
        String root = "A";
        topologicalSort(root, graph, st, visited);

        return st;
    }

    private static HashMap<String, String[]> createGraph(String[][] deps) {
        HashMap<String, String[]> g = new HashMap<>();
        String[] aDeps = new String[]{"B", "C"};
        g.put("A", aDeps);
        String[] cDeps = new String[]{"B"};
        g.put("C", cDeps);

        return g;
    }

    /*
    A:  B C
    C: B

    a
    |    |
    b <- c
    */

    private static void topologicalSort(String root, HashMap<String, String[]> graph, Stack<String> st, Set<String> visited) {

        Stack<String> traverseStack = new Stack<>();
        traverseStack.push(root);

        while(traverseStack.isEmpty() == false) {

            String current = traverseStack.peek();
            
            if(visited.contains(current)) {
                traverseStack.pop();
                continue;
            }

            if(graph.containsKey(current)) {

                String[] children = graph.get(current);
                ArrayList<String> unvisitedChildren = new ArrayList<>();
                
                // filter visited children
                for(int i=0; i<children.length; i++ ){
                    String child= children[i];
                    
                    if(visited.contains(child) == false) {
                        unvisitedChildren.add(child);
                    }
                }


                if(unvisitedChildren.size() == 0){
                    st.push(current); 
                    traverseStack.pop();   
                    visited.add(current);
                } else {
                    for(int i = 0; i<unvisitedChildren.size(); i++) {
                        traverseStack.push(unvisitedChildren.get(i));
                    }
                }
            } else {
                st.push(current);
                traverseStack.pop();
                visited.add(current);
            }
        }
    }
}



//  DFS APPROACH: LONG WAY
/*
    public static String[] resolveDeps(String[][] deps) {
       String[] extDeps = getExternalDeps(deps);

       HashMap<String, String[]> depToImgs = createDepToImgs(deps);

       ArrayList<String> resp = new ArrayList<>();

       for(int i = 0; i<extDeps.length; i++){
            String extDep = extDeps[i];

            Set<String> visited = new HashSet<>();
            String[] path = depthFirstTraverse(extDep, depToImgs, visited);

            resp.addAll(path);
       }

       return resp.toArray();
    }

    //TODO:
    // getExternalDeps
    // createDepToImgs

     /// TEST TEST TEST TEST 
     // happy path a-b
     // edge cases
        // cyclic deps
        // multiple independent branches
        // orphan nodes
        // linked list graph

    
    root: a
    // graph
    // a
    // a1
    // b c
    // e d
    a: a1
    a1: b c
    b: e
    d: c

    
    visited () (a) (a, a1) (a, a1, b) (a, a1, b, c)
    st () (a) () (a1) () (b) (b, c) (b)
    resp () (a) (a, a1, b) (a, a1, b, c)
    curr: a a1 c
    children (a1) (b, c)

    

    private static String[] depthFirstTraverse(String root, HashMap<String, String[]> graph, Set<String> visited){

        Stack st = new Stack();
        ArrayList<String> resp = new ArrayList<String>();

        st.push(root);
        visited.add(root);
        resp.add(root);

        while(st.isEmpty() == false) {

            String current = st.pop();

            if(graph.containsKey(current)){
                String[] children = graph.get(current);

                for(int i=0; i<children.length; i++) {

                    if(visited.contains(children[i])) {
                        return new String[]{}; // CYCLIC DEP
                    }

                    st.push(children[i]);
                    visited.add(children[i]);
                    resp.add(children[i]);
                }
            }
        }

        resp.toArray();
    }
    */




