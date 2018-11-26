package tree;

import java.util.LinkedList;
import java.util.NoSuchElementException;
import java.util.Queue;
import java.util.TreeMap;

/**
 * @author Zhang
 * @date 2018/8/3
 * @Description      摘自https://blog.csdn.net/nmgrd/article/details/52843480
 */
public class RedBlackTree<K extends Comparable<K>, V> {

    private static final boolean RED = true;
    private static final boolean BLACK = false;

    private Node root;

    private class Node {
        private K key;
        private V value;
        private Node left, right;
        private boolean color;
        private int N;

        public Node(K key, V value, boolean color, int N) {
            this.key = key;
            this.value = value;
            this.color = color;
            this.N = N;
        }

    }

    public RedBlackTree() {

    }

    /**
     * 空节点默认都是黑色节点
     *
     * @param x
     * @return
     */
    private boolean isRed(Node x) {
        if (x == null)
            return false;
        return x.color == RED;
    }

    /**
     * 返回以X为根的子树的节点数目
     *
     * @param x
     * @return
     */
    private int size(Node x) {
        if (x == null)
            return 0;
        return x.N;
    }

    /**
     * 返回整棵树的节点数目
     *
     * @return
     */
    public int size() {
        return size(root);
    }

    public boolean isEmpty() {
        return root == null;
    }

    /**
     * 根据key进行查找
     *
     * @param key
     * @return
     */
    public V get(K key) {
        if (key == null) {
            throw new NullPointerException("key不能为空");
        }
        return get(root, key);
    }

    private V get(Node x, K key) {
        while (x != null) {
            int cmp = key.compareTo(x.key);
            if (cmp < 0) {
                x = x.left;
            } else if (cmp > 0) {
                x = x.right;
            } else {
                return x.value;
            }
        }
        return null;
    }

    /**
     * 判断树中是否包含名字为key的键
     *
     * @param key
     * @return
     */
    public boolean contains(K key) {
        return get(key) != null;
    }

    /**
     * 右旋转， 将向左倾斜的红链接变为向右倾斜
     *
     * @param h
     * @return
     */
    private Node rotateRight(Node h) {
        // assert (h != null) && isRed(h.left);
        Node x = h.left;
        h.left = x.right;
        x.right = h;
        x.color = h.color;
        h.color = RED;
        x.N = h.N;
        h.N = size(h.left) + size(h.right) + 1;
        return x;
    }

    /**
     * 左旋转，与右旋转相反
     *
     * @param h
     * @return
     */
    private Node rotateLeft(Node h) {
        // assert (h != null) && isRed(h.right);
        Node x = h.right;
        h.right = x.left;
        x.left = h;
        x.color = h.color;
        h.color = RED;
        x.N = h.N;
        h.N = size(h.left) + size(h.right) + 1;
        return x;
    }

    /**
     * 颜色反转，注意：h必须与其两个子节点颜色相反
     *
     * @param h
     */
    private void flipColors(Node h) {
        // assert (h != null) && (h.left != null) && (h.right != null);
        // assert (!isRed(h) && isRed(h.left) && isRed(h.right))
        // || (isRed(h) && !isRed(h.left) && !isRed(h.right));
        h.color = !h.color;
        h.left.color = !h.left.color;
        h.right.color = !h.right.color;
    }

    /**
     * 如果h节点是红色节点， 并且 h.right和h.right.left是黑色。将h.right或者其某个子节点变为红色
     *
     * @param h
     * @return
     */
    private Node moveRedRight(Node h) {
        // assert (h != null);
        // assert isRed(h) && !isRed(h.right) && !isRed(h.right.left);
        flipColors(h);
        if (isRed(h.left.left)) {
            h = rotateRight(h);
            flipColors(h);
        }
        return h;
    }

    /**
     * 如果h节点是红色节点，并且 h.left和h.left.left是黑色。将 h.left或者其某个子节点变为红色
     *
     * @param h
     * @return
     */
    private Node moveRedLeft(Node h) {
        // assert (h != null);
        // assert isRed(h) && !isRed(h.left) && !isRed(h.left.left);

        flipColors(h);
        if (isRed(h.right.left)) {
            h.right = rotateRight(h.right);
            h = rotateLeft(h);
            flipColors(h);
        }
        return h;
    }

    private Node balance(Node h) {
        // assert (h != null);

        if (isRed(h.right)) {
            h = rotateLeft(h);
        }
        if (isRed(h.left) && isRed(h.left.left)) {
            h = rotateRight(h);
        }
        if (isRed(h.left) && isRed(h.right)) {
            flipColors(h);
        }

        h.N = size(h.left) + size(h.right) + 1;
        return h;
    }

    /**
     * 插入键值对
     *
     * @param key
     * @param value
     */
    public void put(K key, V value) {
        if (key == null) {
            throw new NullPointerException("key不能为空");
        }
        if (value == null) {
            delete(key);
            return;
        }

        root = put(root, key, value);
        root.color = BLACK;
        assert check();
    }

    /**
     * 在以h为根节点的子树中插入键值对
     *
     * @param h
     * @param key
     * @param value
     * @return
     */
    private Node put(Node h, K key, V value) {
        if (h == null) {
            return new Node(key, value, RED, 1);
        }

        int cmp = key.compareTo(h.key);
        if (cmp < 0) {
            h.left = put(h.left, key, value);
        } else if (cmp > 0) {
            h.right = put(h.right, key, value);
        } else {
            h.value = value;
        }

        // 修正任意向右倾斜的红链接
        if (isRed(h.right) && !isRed(h.left)) {
            h = rotateLeft(h);
        }
        if (isRed(h.left) && isRed(h.left.left)) {
            h = rotateRight(h);
        }
        if (isRed(h.left) && isRed(h.right)) {
            flipColors(h);
        }
        h.N = size(h.left) + size(h.right) + 1;

        return h;
    }

    public void deleteMin() {
        if (isEmpty()) {
            throw new NoSuchElementException("该红黑树为空, 删毛线！！！");
        }

        if (!isRed(root.left) && !isRed(root.right)) {
            root.color = RED;
        }

        root = deleteMin(root);
        if (!isEmpty()) {
            root.color = BLACK;
        }
        assert check();
    }

    private Node deleteMin(Node h) {
        if (h.left == null) {
            return null;
        }

        if (!isRed(h.left) && !isRed(h.left.left)) {
            h = moveRedLeft(h);
        }

        h.left = deleteMin(h.left);
        return balance(h);
    }

    public void deleteMax() {
        if (isEmpty()) {
            throw new NoSuchElementException("该红黑树为空, 删毛线！！！");
        }

        // if both children of root are black, set root to red
        if (!isRed(root.left) && !isRed(root.right)) {
            root.color = RED;
        }

        root = deleteMax(root);
        if (!isEmpty()) {
            root.color = BLACK;
        }
        assert check();
    }

    private Node deleteMax(Node h) {
        if (isRed(h.left)) {
            h = rotateRight(h);
        }

        if (h.right == null) {
            return null;
        }

        if (!isRed(h.right) && !isRed(h.right.left)) {
            h = moveRedRight(h);
        }

        h.right = deleteMax(h.right);

        return balance(h);
    }

    public void delete(K key) {
        if (key == null) {
            throw new NullPointerException("key不能为空");
        }
        if (!contains(key)) {
            return;
        }

        // 如果两个子节点的颜色都为黑色，设置root节点为红色
        if (!isRed(root.left) && !isRed(root.right)) {
            root.color = RED;
        }

        root = delete(root, key);
        if (!isEmpty()) {
            root.color = BLACK;
        }
        assert check();
    }

    private Node delete(Node h, K key) {
        // assert get(h, key) != null;

        if (key.compareTo(h.key) < 0) {
            if (!isRed(h.left) && !isRed(h.left.left)) {
                h = moveRedLeft(h);
            }
            h.left = delete(h.left, key);
        } else {
            if (isRed(h.left)) {
                h = rotateRight(h);
            }
            if (key.compareTo(h.key) == 0 && (h.right == null)) {
                return null;
            }
            if (!isRed(h.right) && !isRed(h.right.left)) {
                h = moveRedRight(h);
            }
            if (key.compareTo(h.key) == 0) {
                Node x = min(h.right);
                h.key = x.key;
                h.value = x.value;
                // h.val = get(h.right, min(h.right).key);
                // h.key = min(h.right).key;
                h.right = deleteMin(h.right);
            } else {
                h.right = delete(h.right, key);
            }
        }
        return balance(h);
    }

    /**
     * 求红黑树的高度
     *
     * @return
     */
    public int height() {
        return height(root);
    }

    private int height(Node x) {
        if (x == null) {
            return -1;
        }
        return 1 + Math.max(height(x.left), height(x.right));
    }

    /**
     * 返回最小键
     *
     * @return
     */
    public K min() {
        if (isEmpty()) {
            throw new NoSuchElementException("该红黑树为空，没有任何节点");
        }
        return min(root).key;
    }

    private Node min(Node x) {
        // assert x != null;
        if (x.left == null) {
            return x;
        } else {
            return min(x.left);
        }
    }

    public K max() {
        if (isEmpty()) {
            throw new NoSuchElementException("该红黑树为空，没有任何节点");
        }
        return max(root).key;
    }

    /**
     * 返回以x为根节点的子树中的最大的key
     *
     * @param x
     * @return
     */
    private Node max(Node x) {
        // assert x != null;
        if (x.right == null) {
            return x;
        } else {
            return max(x.right);
        }
    }

    public K floor(K key) {
        if (key == null) {
            throw new NullPointerException("key不能为空");
        }
        if (isEmpty()) {
            throw new NoSuchElementException("该红黑树为空，没有任何节点");
        }
        Node x = floor(root, key);
        if (x == null) {
            return null;
        } else {
            return x.key;
        }
    }

    /**
     * 返回存在于以x为根节点的子树中的， 键的值小于或等于key的最大键
     *
     * @param x
     * @param key
     * @return
     */
    private Node floor(Node x, K key) {
        if (x == null) {
            return null;
        }
        int cmp = key.compareTo(x.key);
        if (cmp == 0) {
            return x;
        }
        if (cmp < 0) {
            return floor(x.left, key);
        }
        Node t = floor(x.right, key);
        if (t != null) {
            return t;
        } else {
            return x;
        }
    }

    public K ceiling(K key) {
        if (key == null) {
            throw new NullPointerException("key不能为空");
        }
        if (isEmpty()) {
            throw new NoSuchElementException("该红黑树为空，没有任何节点");
        }
        Node x = ceiling(root, key);
        if (x == null) {
            return null;
        } else {
            return x.key;
        }
    }

/**
 * 返回以x为根节点的子树中， 大于或等于key的最小键
 *
 * @param x
 * @param key
 * @return
 */
private Node ceiling(Node x, K key) {
    if (x == null) {
        return null;
    }
    int cmp = key.compareTo(x.key);
    if (cmp == 0) {
        return x;
    }
    if (cmp > 0) {
        return ceiling(x.right, key);
    }
    Node t = ceiling(x.left, key);
    if (t != null) {
        return t;
    } else {
        return x;
    }
}

    public K select(int k) {
        if (k < 0 || k >= size()) {
            throw new IllegalArgumentException();
        }
        Node x = select(root, k);
        return x.key;
    }

    /**
     * 返回以x为根节点的子树中， 大小排名（从小到大的排序，也即升序排序）为k的节点
     *
     * @param x
     * @param k
     * @return
     */
    private Node select(Node x, int k) {
        // assert x != null;
        // assert k >= 0 && k < size(x);
        int t = size(x.left);
        if (t > k) {
            return select(x.left, k);
        } else if (t < k) {
            return select(x.right, k - t - 1);
        } else {
            return x;
        }
    }

    public int rank(K key) {
        if (key == null) {
            throw new NullPointerException("key不能为空");
        }
        return rank(key, root);
    }

    private int rank(K key, Node x) {
        if (x == null) {
            return 0;
        }
        int cmp = key.compareTo(x.key);
        if (cmp < 0) {
            return rank(key, x.left);
        } else if (cmp > 0) {
            return 1 + size(x.left) + rank(key, x.right);
        } else {
            return size(x.left);
        }
    }

    /**
     * 迭代整棵红黑树中的所有键
     *
     * @return
     */
    public Iterable<K> keys() {
        if (isEmpty()) {
            return new LinkedList<K>();
        }
        return keys(min(), max());
    }

    /**
     * 迭代low~high范围内的键
     *
     * @param low
     * @param high
     * @return
     */
    public Iterable<K> keys(K low, K high) {
        if (low == null)
            throw new NullPointerException("low不能为空");
        if (high == null)
            throw new NullPointerException("high不能为空");

        Queue<K> queue = new LinkedList<K>();
        // if (isEmpty() || lo.compareTo(hi) > 0) return queue;
        keys(root, queue, low, high);
        return queue;
    }

    /**
     * 将以x为根节点的子树中的， 范围在low~high之间的所有键添加到队列中。
     * 过程是：首先判断节点x对应的key在不在low~high范围内，在则添加到队列中
     * ，不在则不添加。然后递归调用，判断其左节点和右节点在不在low~high指定的范围内。
     *
     * @param x
     * @param queue
     * @param low
     * @param high
     */
    private void keys(Node x, Queue<K> queue, K low, K high) {
        if (x == null) {
            return;
        }
        int cmplo = low.compareTo(x.key);
        int cmphi = high.compareTo(x.key);
        if (cmplo < 0) {
            keys(x.left, queue, low, high);
        }
        if (cmplo <= 0 && cmphi >= 0) {
            queue.add(x.key);
        }
        if (cmphi > 0) {
            keys(x.right, queue, low, high);
        }
    }

    private boolean check() {
        if (!isBST()) {
            System.out.println("不满足二叉树的定义");
        }
        if (!isSizeConsistent()) {
            System.out.println("节点数目不一致");
        }
        if (!isRankConsistent()) {
            System.out.println("排名不一致");
        }
        if (!is23()) {
            System.out.println("不满足2-3树的定义");
        }
        if (!isBalanced()) {
            System.out.println("不满足红黑树的完美黑色平衡");
        }
        return isBST() && isSizeConsistent() && isRankConsistent() && is23() && isBalanced();
    }

    /**
     * 判断红黑树是否满足二叉树（二叉搜索树）的定义（左节点比当前节点小， 右节点比当前节点大）
     *
     * @return
     */
    private boolean isBST() {
        return isBST(root, null, null);
    }

    private boolean isBST(Node x, K min, K max) {
        if (x == null) {
            return true;
        }
        if (min != null && x.key.compareTo(min) <= 0) {
            return false;
        }
        if (max != null && x.key.compareTo(max) >= 0) {
            return false;
        }
        return isBST(x.left, min, x.key) && isBST(x.right, x.key, max);
    }

    /**
     * 递归判断每一个节点的大小是不是等于： size(x.left) + 1 + size(x.right)
     *
     * @return
     */
    private boolean isSizeConsistent() {
        return isSizeConsistent(root);
    }

    private boolean isSizeConsistent(Node x) {
        if (x == null) {
            return true;
        }
        if (x.N != size(x.left) + size(x.right) + 1) {
            return false;
        }
        return isSizeConsistent(x.left) && isSizeConsistent(x.right);
    }

    /**
     * 通过select与rank方法验证二叉树（此处的二叉树就是指红黑树）
     *
     * @return
     */
    private boolean isRankConsistent() {
        for (int i = 0; i < size(); i++)
            if (i != rank(select(i))) {
                return false;
            }
        for (K key : keys()) {
            if (key.compareTo(select(rank(key))) != 0) {
                return false;
            }
        }
        return true;
    }

    /**
     * 判断是否满足二三树（或者红黑树）的定义。注意：红黑树是二三树的一种具体实现。二三树的定义大家自己查询咯
     *
     * @return
     */
    private boolean is23() {
        return is23(root);
    }

    private boolean is23(Node x) {
        if (x == null) {
            return true;
        }
        if (isRed(x.right)) {
            return false;
        }
        if (x != root && isRed(x) && isRed(x.left)) {
            return false;
        }
        return is23(x.left) && is23(x.right);
    }

    /**
     * 判断从根节点到叶节点的任意一条路径上的黒链接的数量是否相等（也即判断23树是否满足完美黑色平衡）
     *
     * @return
     */
    private boolean isBalanced() {
        int black = 0; // number of black links on path from root to min
        Node x = root;
        // while循环结束的时候，可以计算得出任意空链接到根节点的路径上的黒链接的数量
        while (x != null) {
            if (!isRed(x)) {
                black++;
            }
            x = x.left;
        }
        return isBalanced(root, black);
    }

    /**
     * @param x
     * @param black
     * @return
     */
    private boolean isBalanced(Node x, int black) {
        if (x == null) {
            return black == 0;
        }
        if (!isRed(x)) {
            black--;
        }
        return isBalanced(x.left, black) && isBalanced(x.right, black);
    }

    public void recursiveInorder() {
        recursiveInorder(root);
    }

    /** 递归实现中序遍历 */
    private void recursiveInorder(Node node) {
        if (node != null) {
            recursiveInorder(node.left);
            visit(node);
            recursiveInorder(node.right);
        }
    }

    public void visit(Node node) {
        StringBuffer buff = new StringBuffer();
        if (node != null) {
            buff.append(" " + node.key + "[");
            String left = node.left != null ? node.left.key + "" : "null";
            String right = node.right != null ? node.right.key + "" : "null";
            String color = node.color == RED ? "红" : "黑";
            buff.append(left).append(" : ").append(right).append(" - ").append(color).append("] ");
        }
        System.out.print(buff.toString());
    }


    public static void main(String... args) {
        RedBlackTree<Integer, String> st = new RedBlackTree<Integer, String>();
        st.put(1, "yi");
        st.put(2, "er");
        st.put(3, "san");
        st.put(4, "si");
        st.put(5, "wu");
        st.put(6, "liu");
        st.put(7, "qi");
        st.put(8, "ba");
        st.put(9, "jiu");
        st.put(10, "shi");
        st.put(11, "shiyi");
        st.put(21, "eryi");
        st.put(31, "sanyi");

// 添加后得到的红黑树入下图：标有*号的节点是红色节点 。添加后红黑树是完美黑色平衡的
//                          8
//                        /   \
//                       /     \
//                      /       \
//                     4*        21
//                    / \       / \
//                   2   6     10* 31
//                  /\   /\    /\
//                 /  \ 5  7  /  \
//                1    3     9   11

        System.out.println("插入值后的大小是" + st.size());
        for (Integer s : st.keys()) {
            System.out.print(st.get(s) + "  ");
        }
        System.out.println();


        st.recursiveInorder();
        System.out.println();


        st.delete(8);
        st.delete(10);
        st.delete(5);
        st.delete(3);
        st.delete(4);
        System.out.println("删除后的大小是:" + st.size());
        System.out.println();

// 删除后得到的红黑树入下图：标有*号的节点是红色节点 。删除后红黑树依然是完美黑色平衡的
//                 9
//              /    \
//             /      \
//            6       21
//           / \     /  \
//          2   7   11  31
//         /
//        1*


        st.recursiveInorder();
    }


}

