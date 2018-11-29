package arrayQuestions;

import java.util.*;

/**
 * Created by Rajiv on 1/5/2017.
 */
public class MazeSolverUsingBFS {
    public static void main(String[] args){
        // multidimensional array
        int[][] input = new int[][]{{1,0,1,1,0},
                                    {1,0,0,1,1},
                                    {1,1,1,0,1},
                                    {1,0,1,0,1},
                                    {0,1,1,1,1}};
        // in this program we can travel to a position if it contains value 1.
        // if 0 then the path is blocked.
        int i = 0;  // target position x
        int j = 2;  // target position y
        // this target position means that the program will search the path from
        // position 00 to reach the position 02 of the array.
        maze(input,i,j);
    }

    // a method to find the path from position 00 of an array to target position given.
    // It is based upon breadth-first-search using queue. each position of the array is represented as a node in tree
    // all positions are based on the array positioning system - start from 0.
    public static void maze(int[][] input,int finalXpos,int finalYpos){
        Map<String,Boolean> checkedNode = new HashMap<>();
        Queue<String> queue = new LinkedList<>();
        queue.add("00");
        checkedNode.put("00",true);
        int len = input[0].length;
        // holds the positions in the sequence in which array has been visited
        List<String> path = new ArrayList<>();
        Boolean isPathExists = false;
        while(!queue.isEmpty()){
            // check if final x and y position matches with current position of input array. if this happens
            // then we can say that path exists to the given final position
            if(checkedNode.get(finalXpos+""+finalYpos)!=null && checkedNode.get(finalXpos+""+finalYpos)){
                printContent(finalXpos,finalYpos,len,input);
                isPathExists = true;
                break;
            }
            String currPosition = queue.poll();
            int i = Integer.parseInt("" + currPosition.charAt(0));
            int j = Integer.parseInt("" + currPosition.charAt(1));
            // check for down neighbour
            if(i+1 < len) {
                int tempi = i+1;
                String tempVal = tempi + "" + j;
                if ((checkedNode.get(tempVal)==null || !checkedNode.get(tempVal)) && input[i + 1][j] == 1) {
                    queue.add(tempVal);
                    checkedNode.put(tempVal,true);
                    path.add(tempVal);
                }
            }
            // check for right neighbour
            if(j+1 < len) {
                int tempj = j + 1;
                String tempVal = i + "" + tempj;
                if ((checkedNode.get(tempVal)==null || !checkedNode.get(tempVal)) && input[i][j + 1] == 1) {
                    queue.add(tempVal);
                    checkedNode.put(tempVal, true);
                    path.add(tempVal);
                }
            }
            // check for upper neighbour
            if(i-1>=0) {
                int tempi = i - 1;
                String tempVal = tempi + "" + j;
                if ((checkedNode.get(tempVal)==null || !checkedNode.get(tempVal)) && input[i - 1][j] == 1) {
                    queue.add(tempVal);
                    checkedNode.put(tempVal, true);
                    path.add(tempVal);
                }
            }
            // check for left neighbour
            if(j-1>=0){
                int tempj = j - 1;
                String tempVal = i + "" + tempj;
                if((checkedNode.get(tempVal)==null || !checkedNode.get(tempVal)) && input[i][j-1] == 1) {
                    queue.add(tempVal);
                    checkedNode.put(tempVal, true);
                    path.add(tempVal);
                }
            }
            printContent(i,j,len,input);
            try {
                Thread.sleep(2000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        if(isPathExists) System.out.println("Path exists to target position");
        else System.out.println("Path not found to target position");

        // print all the positions visited in the sequence of breadth-first-search
        System.out.println();
        System.out.println("Path (positions) visited in sequence of Breadth-First-Search");
        for(String s:path){
            System.out.print(s + " ");
        }
    }

    // print the array along with the current position.
    public static void printContent(int i,int j,int len,int[][] input){
        System.out.println("Currently at position : "+i+""+j);
        for(int k = 0;k<len;k++){
            for(int l=0;l<len;l++){
                if(i==k && j==l) {
                    System.out.print("" + i + "" + j + "   ");
                }
                else System.out.print(input[k][l] + "    ");
            }
            System.out.println("");
        }
    }
}