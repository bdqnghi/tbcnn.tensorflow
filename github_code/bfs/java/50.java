package me.codebase.algorithm.search;

import me.codebase.algorithm.structure.TreeNode;

import java.util.ArrayDeque;
import java.util.Queue;

/**
 * Created by chendong on 2017/10/9.
 */
public class BinaryTreeBFS {

    //Breadth-First-Search
    public static void bfs(TreeNode root) {
        if (root != null) {
            Queue<TreeNode> queue = new ArrayDeque<>();
            queue.add(root);

            while (!queue.isEmpty()) {
                TreeNode tmp = queue.poll();
                System.out.print(tmp.value);
                if (tmp.left != null) {
                    queue.add(tmp.left);
                }

                if (tmp.right != null) {
                    queue.add(tmp.right);
                }
            }
        }
    }
}
