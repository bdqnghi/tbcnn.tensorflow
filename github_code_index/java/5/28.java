/*
Given a binary tree, find its maximum depth.
The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.
*/

//Recursive
public int maxDepth(TreeNode root) {
    if(root==null)
        return 0;
 
    int leftDepth = maxDepth(root.left);
    int rightDepth = maxDepth(root.right);
 
    int bigger = Math.max(leftDepth, rightDepth);
 
    return bigger+1;
}

/////////////////////////////////////////////////////////
//Iterator
public int maxDepth(TreeNode root) {
    if(root == null) {
        return 0;
    }
    
    Stack<TreeNode> stack = new Stack<>();
    Stack<Integer> value = new Stack<>();
    stack.push(root);
    value.push(1);
    int max = 0;
    while(!stack.isEmpty()) {
        TreeNode node = stack.pop();
        int temp = value.pop();
        max = Math.max(temp, max);
        if(node.left != null) {
            stack.push(node.left);
            value.push(temp+1);
        }
        if(node.right != null) {
            stack.push(node.right);
            value.push(temp+1);
        }
    }
    return max;
}
