package Search;

import java.util.ArrayList;

/**
 * Created by Andrew Cho on 11/10/2015.
 *
 * super simple implementation of breadth first search
 */
public class Breadth {
    private Node mHead;

    public Boolean search(Node head, Node n) {
        Node start = head;
        head.setCovered(true);
        int value = n.getmValue();

        if (start.getmValue() == value) {
            return true;
        }

        while(start.getmValue() != value) {
            ArrayList<Node> temp = start.getmChildren();
            for (int i = 0; i < temp.size(); i++) {
                if (head.getCovered() != false) {
                    if (search(temp.get(i), n)) {
                        return true;
                    }
                }
            }
        }

        return false;
    }
}
