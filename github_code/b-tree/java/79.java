import lib.TreeNode;

/**
 * https://leetcode.com/problems/symmetric-tree
 *
 * Recursive colution.
 *
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode(int x) { val = x; }
 * }
 */
public class SymmetricTreeB {
    public boolean isSymmetric(TreeNode root) {
        return check(root, root);
    }
    
    private boolean check(TreeNode n1, TreeNode n2) {
        if (n1 == null && n2 == null)
            return true;
        if (n1 == null || n2 == null)
            return false;
        
        return (n1.val == n2.val) && check(n1.left, n2.right) && check(n1.right, n2.left);
    }
}
