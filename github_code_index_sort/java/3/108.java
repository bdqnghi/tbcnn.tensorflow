package Graph;

import java.util.HashMap;
import java.util.LinkedList;
import java.util.Stack;

/**
 * Created with IntelliJ IDEA.
 * User: dheeraj
 * Date: 7/12/14
 * Time: 8:18 PM
 * To change this template use File | Settings | File Templates.
 */
public class TopologicalSort {
    private HashMap<String, LinkedList<String>> adjListMap = new HashMap<String, LinkedList<String>>();
    private HashMap<String, Boolean> visitedMap = new HashMap<String, Boolean>();

    private LinkedList<String> tempList;

    public void addPair(String name, String value) {
        if (adjListMap.containsKey(name)) {
            tempList = adjListMap.get(name);
            tempList.add(value);
        } else {
            LinkedList<String> linkedList = new LinkedList<String>();
            linkedList.add(value);
            adjListMap.put(name, linkedList);
        }


        if (!adjListMap.containsKey(value)) {
            LinkedList<String> linkedList = new LinkedList<String>();
            adjListMap.put(value, linkedList);
        }

        visitedMap.put(name, false);
        visitedMap.put(value, false);
    }

    public void topologicalSort() {
        System.out.println(adjListMap.toString());
        System.out.println(visitedMap);
        //if(true)return;

        Stack<String> stringStack = new Stack<String>();
        for (String entry : adjListMap.keySet()) {
            if (!visitedMap.get(entry)) {
                tSort(stringStack, entry);
                //System.out.println(entry);
            }
        }

        while (!stringStack.isEmpty()) {
            System.out.println(stringStack.pop());
        }
    }

    private void tSort(Stack<String> stringStack, String name) {
        if (visitedMap.get(name)) {
            return;
        }
        visitedMap.put(name, true);
        for (String value : adjListMap.get(name)) {
            //System.out.println(value);
            tSort(stringStack, value);
        }
        stringStack.add(name);
    }

    public static void main(String[] args) {
        TopologicalSort topologicalSort = new TopologicalSort();
        topologicalSort.addPair("Naveen", "Satish");
        topologicalSort.addPair("Satish", "Anushree");
        topologicalSort.addPair("Satish", "Sandeep");
        topologicalSort.addPair("Gurinder", "Naveen");
        topologicalSort.addPair("Dheeraj","Gurinder");
        topologicalSort.addPair("Dheeraj","Gurinder1");


        topologicalSort.topologicalSort();
    }

}
