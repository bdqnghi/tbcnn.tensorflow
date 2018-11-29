package AI;

import Graph.BreadthFirst;

import java.awt.*;
import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;

/**
 * Created by h3dg3wytch on 1/24/17.
 */
public class BreadthFirstSearch {

    BreadthFirstSearchNode startNode;
    BreadthFirstSearchNode goalNode;

    public BreadthFirstSearch(BreadthFirstSearchNode startNode, BreadthFirstSearchNode goalNode) {
        this.startNode = startNode;
        this.goalNode = goalNode;
    }


    public boolean compute(){

        if(startNode.data == goalNode.data) {
            System.out.println("Found!");
            return  true;
        }

        Queue<BreadthFirstSearchNode> queue = new LinkedList<>();
        ArrayList<BreadthFirstSearchNode> explored = new ArrayList<>();

        queue.add(this.startNode);
        explored.add(startNode);

        while(!queue.isEmpty()) {
            BreadthFirstSearchNode current = queue.remove();
            if (current.data == goalNode.data) {
                System.out.println(explored);
                return true;
            } else {
                if (current.getChildren().isEmpty())
                    return false;
                else
                    queue.addAll(current.getChildren());
            }

            explored.add(current);
        }
        return false;
    }


    public class BreadthFirstSearchNode{

        private int data;

        private BreadthFirstSearchNode rightChild;
        private BreadthFirstSearchNode leftChild;


        public BreadthFirstSearchNode(int data, BreadthFirstSearchNode rightChild, BreadthFirstSearchNode leftChild) {
            this.data = data;
            this.rightChild = rightChild;
            this.leftChild = leftChild;
        }


        public BreadthFirstSearchNode(BreadthFirstSearchNode rightChild, BreadthFirstSearchNode leftChild) {
            this.rightChild = rightChild;
            this.leftChild = leftChild;
        }

        public int getData() {
            return data;
        }

        public void setData(int data) {
            this.data = data;
        }

        public BreadthFirstSearchNode getRightChild() {
            return rightChild;
        }

        public void setRightChild(BreadthFirstSearchNode rightChild) {
            this.rightChild = rightChild;
        }

        public BreadthFirstSearchNode getLeftChild() {
            return leftChild;
        }

        public void setLeftChild(BreadthFirstSearchNode leftChild) {
            this.leftChild = leftChild;
        }

        public ArrayList<BreadthFirstSearchNode> getChildren(){
            ArrayList<BreadthFirstSearchNode> result = new ArrayList<>();
            if(this.leftChild != null)
            {
                result.add(leftChild);
            }
            if(this.rightChild != null) {
                result.add(rightChild);
            }
            return result;
        }
    }

}
