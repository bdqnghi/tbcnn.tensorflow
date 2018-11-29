import javax.sound.midi.Soundbank;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

/**
 * Created by Helga on 11/16/2017.
 */
public class Main {
   public static void main(String...args) throws FileNotFoundException{
        Scanner in = new Scanner(new File("Data.txt"));
        int n = in.nextInt();
         int[][] matrixOfAdj = new int[n][n];
         for(int i = 0; i < n; i++){ //filling the matrix of adjacencies
             for(int j = 0; j < n; j++){
                 matrixOfAdj[i][j] = in.nextInt();
             }
         }

         ArrayList<ArrayList<Integer>> adj = new ArrayList<>();
        int index = 0;
        in.nextLine();
         while(in.hasNextLine()){
             StringTokenizer stringTokenizer = new StringTokenizer(in.nextLine());
             adj.add(new ArrayList<>());
             while(stringTokenizer.hasMoreTokens()){
                 adj.get(index).add(Integer.valueOf(stringTokenizer.nextToken()));
             }
             index++;
         }
        System.out.println("Breadth-First-Search");

         //here comes Breadth-First-Search
        ArrayList<ArrayList<Integer>> layers = breadthFirstSearch(adj,0);
        for(int i = 0 ; i< layers.size();i++){
            System.out.print("Layer # "+ i+ " : ");
            for(int j = 0 ; j< layers.get(i).size(); j++){
                System.out.print(layers.get(i).get(j)+" ");
            }
            System.out.println();
        }
        ArrayList<Integer> vertecies = depthFirstSearch(adj,0);
        for (Integer i: vertecies
             ) {
            System.out.print(i+ " ");
        }
        System.out.println();
    }


    public static ArrayList<ArrayList<Integer>>  breadthFirstSearch(ArrayList<ArrayList<Integer>> adj, int vertex){
        boolean[] isExplored = new boolean[adj.size()];
        for(int i =0 ; i < adj.size() ; i++){
            isExplored[i] = false;
        }
        ArrayList<ArrayList<Integer>> layers = new ArrayList<>();
        layers.add(new ArrayList<>());
        int indexLayers = 0;
        layers.get(indexLayers++).add(vertex);
        Queue<Integer> queue = new ArrayDeque<>();
        queue.add(vertex);
        isExplored[vertex] = true;

        while(!queue.isEmpty()){
            boolean somethingIsExplored = false;
            int index = 0;
            int v = queue.poll();
            while(index < adj.get(v).size()){
                if(!isExplored[adj.get(v).get(index)]){
                    somethingIsExplored = true;
                    queue.add(adj.get(v).get(index));
                    isExplored[adj.get(v).get(index)] = true;
                    layers.add(new ArrayList<>());
                    layers.get(indexLayers).add(adj.get(v).get(index));
                }
                index++;
            }
             if (somethingIsExplored) indexLayers++;
        }
        return  layers;
    }
    public static ArrayList<Integer> depthFirstSearch(ArrayList<ArrayList<Integer>> adj, int vertex){
        ArrayList<Integer> vertecies = new ArrayList<>();
        vertecies.add(vertex);
        Stack<Integer> stack = new Stack<>();
        stack.push(vertex);
        boolean[] isExplored = new boolean[adj.size()];
        for(int i = 0; i< isExplored.length; i++){
            isExplored[i] = false;
        }
        isExplored[vertex] = true;
        while(!stack.isEmpty()) {
            Integer current = stack.pop();
            for (Integer child: adj.get(current)
                 ) {
                if (!isExplored[child]) {
                    stack.push(child);
                    isExplored[child] = true;
                    vertecies.add(child);
                }
            }
        }

        return vertecies;
    }
}
