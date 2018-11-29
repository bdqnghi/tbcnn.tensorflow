package DataStruct;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.util.LinkedList;
import java.util.Queue;

/**
 * 红黑树操作 插入(完成) 删除(待续....)
 * 记录一下红黑树的特性:
 * 1.每个节点或是红色的，或是黑色的
 * 2.根节点是黑色的
 * 3.每个叶节点（NIL）是黑色的
 * 4.如果一个节点是红色的，则它的两个子节点都是黑色的
 * 5.对于每个几点，从该节点到其所有后代叶节点的简单路径上，均包含相同数目的黑色节点。
 *
 * @param <T> 传入的数据类型
 */
public class R_B_Tree<T> {
    private static final Logger logger = LoggerFactory.getLogger(R_B_Tree.class);
    private TreeNode<T> root = null;

    class TreeNode<T> {
        TreeNode rchild;
        TreeNode lchild;
        TreeNode parent;
        int color; // 0: 黑色 1: 红色
        T data;

        public TreeNode(T data) {
            this.data = data;
        }

        public TreeNode(T data, int color) {
            this.data = data;
            this.color = color;
        }

        public int compareTo(TreeNode<T> o) {
            int x = Integer.parseInt(String.valueOf(data));
            int y = Integer.parseInt(String.valueOf(o.data));
            return x - y;
        }
    }

    public void insert(T key) { // 正常插入 找到要插入的地方, 然后把树修正一下, 保持红黑树的特性
        TreeNode<T> n = new TreeNode<>(key, 1);// 插入的节点默认是红色 1
        if (root == null) {
            root = n;
        } else {
            TreeNode<T> t = root;
            while (t != null) {
                if (t.compareTo(n) > 0) {
                    if (t.lchild == null) {
                        t.lchild = n;
                        n.parent = t;
                        break;
                    }
                    t = t.lchild;
                } else {
                    if (t.rchild == null) {
                        t.rchild = n;
                        n.parent = t;
                        break;
                    }
                    t = t.rchild;
                }
            }
        }
        insertFix(n);
    }

    private void insertFix(TreeNode<T> node) {
        if (node == root) {
            node.color = 0;
            return;
        }
        if (node.parent.color == 1) {
            TreeNode<T> P = node.parent;
            TreeNode<T> G = node.parent.parent;
            TreeNode<T> U = G.lchild == P ? G.rchild : G.lchild;
            if (U != null && U.color == 1) { // 第一种情况 当Uncle是红色
                U.color = 0;
                P.color = 0;
                G.color = 1;
                insertFix(G);
            } else if (U == null || U.color == 0) { // 如果Uncle不存在或者是Uncle是黑的
                if (P == G.lchild && node == P.lchild) { // node是左孩子
                    P.color = 0;
                    G.color = 1;
                    rightRotate(G);
                } else if (P == G.rchild && node == P.rchild) {
                    P.color = 0;
                    G.color = 1;
                    leftRotate(G);
                } else if (P == G.lchild && node == P.rchild) {
                    leftRotate(P);
                    insertFix(P);
                } else if (P == G.rchild && node == P.lchild) {
                    rightRotate(P);
                    insertFix(P);
                }
            }
        }
    }

    // 删除
    public void delete(T key) {
        TreeNode<T> node = root;
        TreeNode<T> n = new TreeNode<T>(key);
        while (node != null) {
            int flag = node.compareTo(n);
            if (flag == 0) {
                if (node.lchild == null && node.rchild == null) {
                    if (node.parent == null) {// 如果要删除的这个就是根节点
                        root = null;
                    } else {
                        deleteFix(node);
                        if (node.parent.lchild == node) {
                            node.parent.lchild = null;
                        } else {
                            node.parent.rchild = null;
                        }
                        node.parent = null;
                    }
                } else if (node.lchild == null || node.rchild == null) {
                    if (node.lchild == null) {
                        node.data = (T) node.rchild.data;
                        node.lchild = node.rchild.lchild;
                        node.lchild.parent = node;
                        node.rchild = node.rchild.rchild;
                        node.rchild.parent = node;
                    } else {
                        node.data = (T) node.lchild.data;
                        node.rchild = node.lchild.rchild;
                        node.rchild.parent = node;
                        node.lchild = node.lchild.lchild;
                        node.lchild.parent = node;
                    }
                    deleteFix(node);
                } else {
                    TreeNode<T> min = node.rchild;
                    while (min.lchild != null) {
                        min = min.lchild;
                    }
                    node.data = min.data;
                    deleteFix(min);
                    if (min.parent.lchild == min) {
                        min.parent.lchild = null;
                    } else {
                        min.parent.rchild = null;
                    }
                    min.parent = null;
                }
                return;
            }
            if (flag < 0) {
                node = node.rchild;
            }
            if (flag > 0) {
                node = node.lchild;
            }
        }
    }

    // 删除调整
    public void deleteFix(TreeNode<T> node) { //
        if (node == root || node.color == 1) {
            return;
        }
        TreeNode<T> P = node.parent;
        TreeNode<T> U = P.lchild == node ? P.rchild : P.lchild;
        if (P.lchild == node) {
            if (U.color == 1) { // 如果叔叔是红的
                U.color = 0;
                P.color = 1;
                leftRotate(P);
                U = node.parent.rchild;
            }

            if ((U.lchild == null || U.lchild.color == 0) && (U.rchild == null || U.rchild.color == 0)) {
                U.color = 1;
                deleteFix(P);
            } else {
                if(U.rchild == null || U.rchild.color == 0) {
                    U.lchild.color = 0;
                    U.color = 1;
                    rightRotate(U);
                    U = U.parent;
                }
                U.color= P.color;
                P.color = 0;
                U.rchild.color = 0;
                leftRotate(P);
                deleteFix(root);
            }
        } else {
            if(U.color == 1) {
                U.color = 0;
                P.color = 1;
                rightRotate(P);
            }

            if ((U.lchild == null || U.lchild.color == 0) && (U.rchild == null || U.rchild.color == 0)) {
                U.color = 1;
                deleteFix(P);
            } else {
                if(U.lchild == null || U.lchild.color == 0) {
                    U.rchild.color = 0;
                    U.color = 1;
                    leftRotate(U);
                    U = U.parent;
                }
                U.color= P.color;
                P.color = 0;
                U.lchild.color = 0;
                rightRotate(P);
                deleteFix(root);
            }
        }
    }

    private void leftRotate(TreeNode<T> node) {
        TreeNode<T> right = node.rchild;
        node.rchild = right.lchild; // 因为考虑到不会有node的rchild == null 的情况这里就不进行边界判定

        if (node.parent == null) { // 这种情况就是要旋转的节点就是根节点
            root = right;
            right.parent = null;
        } else {
            right.parent = node.parent;
            if (node.parent.lchild == node) { // 如果node是父亲的左儿子
                right.parent.lchild = right;
            } else if (node.parent.rchild == node) { // 如果node是父亲的右儿子
                right.parent.rchild = right;
            }
        }
        node.parent = right;
        right.lchild = node;
    }

    private void rightRotate(TreeNode<T> node) { // 右旋基本同左旋
        TreeNode<T> left = node.lchild;
        node.lchild = left.rchild;

        if (node.parent == null) {
            root = left;
            left.parent = null;
        } else {
            left.parent = node.parent;
            if (node.parent.lchild == node) {
                left.parent.lchild = left;
            } else if (node.parent.rchild == node) {
                left.parent.rchild = left;
            }
        }
        node.parent = left;
        left.rchild = node;
    }

    public void previsit() {
        if(root == null) {
            System.out.println("null tree");
            return;
        }
        Queue<TreeNode<T>> queue = new LinkedList<>();
        queue.add(root);
        while (!queue.isEmpty()) {
            TreeNode<T> t = queue.poll();
            System.out.print("(" + t.data + "," + t.color + ")");
            if (t.parent != null) System.out.print("父:" + t.parent.data);
            if (t.lchild != null) {
                System.out.print(" 左:" + t.lchild.data);
                queue.add(t.lchild);
            }
            if (t.rchild != null) {
                System.out.print(" 右:" + t.rchild.data);
                queue.add(t.rchild);
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        R_B_Tree<Integer> tree = new R_B_Tree<>();
//        tree.insert(2);
//        tree.insert(7);
//        tree.insert(5);
        tree.insert(4);
//        tree.insert(3);
//        tree.insert(1);
        tree.previsit();
        System.out.println("------------------------------------------------" + "此处分隔");
        tree.delete(4);
//        tree.insert(4);
//        tree.insert(6);
//        tree.insert(8);
//        tree.insert(9);
//        tree.delete(5);
        tree.previsit();
    }
}
