/**
 * B-树
 * Created by Silocean on 2016-03-18.
 */
public class BTree {

    private static int T = 3; // B树的最小度数

    public Node root; // 根节点

    public BTree() {
        root = new Node();
        root.isLeaf = true;
        root.n = 0;
    }

    /**
     * 节点类
     */
    private class Node {
        private int n; // 关键字个数
        private boolean isLeaf; // 是否是叶子节点
        private String[] keys = new String[2 * T]; // 关键字数组
        private Student[] values = new Student[2 * T]; // 值数组
        private Node[] childs = new Node[2 * T + 1]; // 子节点数组
    }

    /**
     * 查找方法的可调用接口
     *
     * @param key
     * @return
     */
    public Student search(String key) {
        return this.search(root, key);
    }

    /**
     * 查询key对应的value
     *
     * @param node
     * @param key
     * @return
     */
    private Student search(Node node, String key) {
        int i = 1;
        while (i <= node.n && key.compareTo(node.keys[i]) > 0) { // 找出最小下标i
            i = i + 1;
        }
        if (i <= node.n && key.compareTo(node.keys[i]) == 0) { // 检查是否已经找到关键字
            return node.values[i];
        } else if (node.isLeaf) { // 碰到叶子节点结束本次查找
            return null;
        } else { // 递归搜索node的子节点
            return search(node.childs[i], key);
        }
    }

    /**
     * 插入key和value
     *
     * @param key
     * @param student
     */
    public void insert(String key, Student student) {
        Node r = this.root;
        if (r.n == 2 * T - 1) { // 如果根节点r为满，原来的根节点分裂，一个新的节点S成为根
            Node s = new Node();
            this.root = s;
            s.isLeaf = false;
            s.n = 0;
            s.childs[1] = r;
            splitChild(s, 1);
            insertNotFull(s, key, student);
        } else {
            insertNotFull(r, key, student);
        }
    }

    /**
     * 向非满子节点插入key和value
     *
     * @param node
     * @param key
     * @param student
     */
    private void insertNotFull(Node node, String key, Student student) {
        int i = node.n;
        if (node.isLeaf) { // 如果node是叶结点，直接将key和value插入node
            while (i >= 1 && key.compareTo(node.keys[i]) < 0) {
                node.keys[i + 1] = node.keys[i];
                node.values[i + 1] = node.values[i];
                i = i - 1;
            }
            node.keys[i + 1] = key;
            node.values[i + 1] = student;
            node.n += 1;

            System.out.println("slave:A student has been inserted into btree!");

        } else { // 不是的话，要将key插入以内部节点node为根的子树中适当的叶结点中去
            while (i >= 1 && key.compareTo(node.keys[i]) < 0) { // 决定向node的那个子节点递归下降
                i = i - 1;
            }
            i = i + 1;
            if (node.childs[i].n == 2 * T - 1) { // 检查是否递归将至一个满子节点上
                splitChild(node, i); // 将该子节点分裂为两个非满孩子
                if (key.compareTo(node.keys[i]) > 0) { // 决定向两个孩子中的哪一个下降是正确的
                    i = i + 1;
                }
            } else {
                insertNotFull(node.childs[i], key, student); // 递归地将key和value插入到合适的子树中
            }
        }
    }

    /**
     * 拆分满子节点
     *
     * @param node
     * @param i
     */
    private void splitChild(Node node, int i) {
        Node right = new Node();
        Node left = node.childs[i];
        right.isLeaf = left.isLeaf;
        right.n = T - 1;
        for (int j = 1; j <= T - 1; j++) { // 把left的T-1个key和value赋给right
            right.keys[j] = left.keys[j + T];
            right.values[j] = left.values[j + T];
        }
        if (!left.isLeaf) { // 把left的T个孩子赋给right
            for (int j = 1; j <= T; j++) {
                right.childs[j] = left.childs[j + T];
            }
        }
        left.n = T - 1;
        for (int j = node.n + 1; j >= i + 1; j--) { // 把right插入为node的一个孩子
            node.childs[j + 1] = node.childs[j];
        }
        node.childs[i + 1] = right;
        for (int j = node.n; j >= i; j--) { // 把left的中间key和value提升到node来分隔left和right
            node.keys[j + 1] = node.keys[j];
            node.values[j + 1] = node.values[j];
        }
        node.keys[i] = left.keys[T];
        node.values[i] = left.values[T];
        node.n += 1; // 调整node关键字个数
    }


}
