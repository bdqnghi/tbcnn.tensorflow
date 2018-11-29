package leetcode.algorithm;

import leetcode.util.*;

import java.util.Stack;

public class DepthFirstSearch {
    public static void main(String[] args) {

    }

    public void depthFirstSearch(TreeNode root) {
        Stack<TreeNode> stack = new Stack<>();

        TreeNode point = root;
        stack.add(point);

        while (!stack.isEmpty()) {
            point = stack.pop();

            //注意！！！先压的是右子树！！
            if (point.getRight() != null) {
                stack.add(point.getRight());
            }
            if (point.getLeft() != null) {
                stack.add(point.getLeft());
            }
        }
    }
}
