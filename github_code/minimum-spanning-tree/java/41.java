import java.io.*;
import java.util.*;

public class Solution {

    public static int sumOfEdges = 0;
    
    public static void main(String[] args) throws Exception{
        Scanner scan = new Scanner(System.in);
        int numberOfNodes = scan.nextInt();
      
        ArrayList<ArrayList<Integer>> disjointedSets = new ArrayList<ArrayList<Integer>>();
        for (int i = 1; i<=numberOfNodes; i++){
            ArrayList<Integer> set = new ArrayList<Integer>();
            set.add(i);
            disjointedSets.add(set);
        }
       
        
        int numberOfEdges = scan.nextInt();
         
        ArrayList<ArrayList<Integer>> list = new ArrayList<ArrayList<Integer>>();
        
        for(int i=0; i<numberOfEdges; i++){
            ArrayList<Integer> edge = new ArrayList<Integer>();
            edge.addAll(Arrays.asList(scan.nextInt(),scan.nextInt(),scan.nextInt()));
            list.add(edge);
        }
        
 
        sort(list);


        for(int j=0; j<numberOfEdges; j++){

            int nodeA = list.get(j).get(0);
            int nodeB = list.get(j).get(1);
            int currentEdge = list.get(j).get(2);
                    
            checkIfInSameSet(disjointedSets, nodeA, nodeB, currentEdge);

        }
        System.out.println(sumOfEdges);
        //System.out.println(disjointedSets);
    }
    
    
    public static void sort(ArrayList<ArrayList<Integer>> list){
    		list.sort(Comparator.comparing(l -> l.get(2)));
    }

    
    public static void checkIfInSameSet(ArrayList<ArrayList<Integer>> disjointedSets, int nodeA, int nodeB, int currentEdge){
		
		//find which set contains nodeA
		int indexOfNodeA  = 0;
		for(int i =0; i<disjointedSets.size(); i++){
			if(disjointedSets.get(i).contains(nodeA)){
				indexOfNodeA = i;
			}
		}
		
		//check if this set contains nodeB as well
	//	int indexOfNodeB =0;
			if(disjointedSets.get(indexOfNodeA).contains(nodeB)){
		//		indexOfNodeB = indexOfNodeA;
				//System.out.println("They are in the same set");
				
			}else{
				joinSets(disjointedSets, nodeA, nodeB);
				sumOfEdges = sumOfEdges + currentEdge;
			}
			
		
		
	}
    
    public static ArrayList<ArrayList<Integer>> joinSets(ArrayList<ArrayList<Integer>> disjointedSets, int nodeA, int nodeB){
		//find which set contains nodeA
		int indexOfNodeA  = 0;
		for(int i =0; i<disjointedSets.size(); i++){
			if(disjointedSets.get(i).contains(nodeA)){
				indexOfNodeA = i;
			}
		}
		//find which set contains nodeB
		int indexOfNodeB  = 0;
		for(int j =0; j<disjointedSets.size(); j++){
			if(disjointedSets.get(j).contains(nodeB)){
				indexOfNodeB = j;
			}
		}
		disjointedSets.get(indexOfNodeA).addAll(disjointedSets.get(indexOfNodeB));
		disjointedSets.remove(indexOfNodeB);
		return disjointedSets;
	}
    

    
}
