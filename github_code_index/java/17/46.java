package wang.yuchao.algorithm.tree;

import com.sun.org.apache.regexp.internal.RE;

/**
 * Created by wangyuchao on 17/5/10.
 */
public class RedBlackTree<T extends Comparable<T>> {

    private static final boolean BLACK = false;
    private static final boolean RED = true;

    private RedBlackTreeNode<T> root;

    public RedBlackTree() {
    }

    private static <T extends Comparable<T>> RedBlackTreeNode<T> leftOf(RedBlackTreeNode<T> node) {
        return node == null ? null : node.left;
    }

    private static <T extends Comparable<T>> RedBlackTreeNode<T> rightOf(RedBlackTreeNode<T> node) {
        return node == null ? null : node.right;
    }

    private static <T extends Comparable<T>> RedBlackTreeNode<T> parentOf(RedBlackTreeNode<T> node) {
        return node == null ? null : node.parent;
    }

    private static <T extends Comparable<T>> boolean colorOf(RedBlackTreeNode<T> node) {
        return node == null ? BLACK : node.color;
    }

    private static <T extends Comparable<T>> void setColor(RedBlackTreeNode<T> node, boolean color) {
        if (node != null) {
            node.color = color;
        }
    }

    // 被旋转的节点x成为了该节点下右节点y的左节点。x，y两个节点均不为空
    private void rotateLeft(RedBlackTreeNode<T> x) {
        if (x != null) {
            RedBlackTreeNode<T> y = x.right;
            // 重新构建y的左节点为x的右节点
            x.right = y.left;
            if (y.left != null) {
                y.left.parent = x;
            }
            // 重新构建x父节点的孩子是y
            y.parent = x.parent;
            if (x.parent == null) {
                root = y;
            } else {
                if (x.parent.left == x) {
                    x.parent.left = y;
                } else {
                    x.parent.right = y;
                }
            }
            // 重新构建x和y的关系
            y.left = x;
            x.parent = y;
        }
    }

    // 被旋转的节点x成为了该节点下左节点y的右节点。
    private void rotateRight(RedBlackTreeNode<T> x) {
        if (x != null) {
            RedBlackTreeNode<T> y = x.left;
            // 重新构建x的左节点为y的右节点
            x.left = y.right;
            if (y.right != null) {
                x.right.parent = y;
            }
            // 重新构建y的父节点为x的父节点
            y.parent = x.parent;
            if (x.parent == null) {
                root = y;
            } else {
                if (x.parent.left == x) {
                    x.parent.left = y;
                } else {
                    x.parent.right = y;
                }
            }
            // 重新构建x和y的关系
            y.right = x;
            x.parent = y;
        }
    }

    public RedBlackTreeNode<T> get(T t) {
        if (t != null) {
            RedBlackTreeNode<T> head = root;
            while (head != null) {
                int result = t.compareTo(head.data);
                if (result < 0) {
                    head = head.left;
                } else if (result > 0) {
                    head = head.right;
                } else {
                    return head;
                }
            }
        } else {
            throw new NullPointerException("insert node and data can not be null");
        }
        return null;
    }

    public void insert(T t) {
        insert(new RedBlackTreeNode<T>(t));
    }

    private void insert(RedBlackTreeNode<T> x) {
        if (x != null && x.data != null) {
            if (root == null) {
                root = x;
            } else {
                RedBlackTreeNode<T> head = root;
                RedBlackTreeNode<T> headBefore = null;
                while (head != null) {
                    headBefore = head;
                    int result = x.data.compareTo(head.data);
                    if (result < 0) {
                        head = head.left;
                    } else {
                        head = head.right;
                    }
                }
                x.parent = headBefore;
                int result = x.data.compareTo(headBefore.data);
                if (result < 0) {
                    headBefore.left = x;
                } else {
                    headBefore.right = x;
                }
                x.color = RED;
                insertFix(x);
            }
        } else {
            throw new NullPointerException("insert node and data can not be null");
        }
    }

    private void insertFix(RedBlackTreeNode<T> x) {
        while (x != null && x.parent != null && x.parent.color == RED) {
            if (parentOf(x) == leftOf(parentOf(parentOf(x)))) {
                RedBlackTreeNode<T> uncle = rightOf(parentOf(parentOf(x)));
                if (colorOf(uncle) == RED) {
                    setColor(parentOf(x), BLACK);
                    setColor(uncle, BLACK);
                    setColor(parentOf(parentOf(x)), RED);
                    x = parentOf(parentOf(x));
                } else {
                    if (x == rightOf(parentOf(x))) {
                        x = parentOf(x);
                        rotateLeft(x);
                    }
                    setColor(parentOf(x), BLACK);
                    setColor(parentOf(parentOf(x)), RED);
                    rotateRight(parentOf(parentOf(x)));
                }
            } else {
                RedBlackTreeNode<T> uncle = leftOf(parentOf(parentOf(x)));
                if (colorOf(uncle) == RED) {
                    setColor(parentOf(x), BLACK);
                    setColor(uncle, BLACK);
                    setColor(parentOf(parentOf(x)), RED);
                    x = parentOf(parentOf(x));
                } else {
                    if (x == leftOf(parentOf(x))) {
                        x = parentOf(x);
                        rotateRight(x);
                    }
                    setColor(parentOf(x), BLACK);
                    setColor(parentOf(parentOf(x)), RED);
                    rotateLeft(parentOf(parentOf(x)));
                }
            }
        }
        root.color = BLACK;
    }

    public boolean delete(T t) {
        RedBlackTreeNode<T> x = get(t);
        if (x == null) {
            return false;
        } else {
            delete(x);
            return true;
        }
    }

    // 如果删除的节点X最多一个孩子，那么可以直接删除
    // 如果删除的节点X有两个孩子，那么找到他的后继结点，将后继节点的数据赋值给X，然后删除后继节点。
    private void delete(RedBlackTreeNode<T> x) {
        if (x != null && x.data != null) {

            if (x.left != null && x.right != null) {
                RedBlackTreeNode<T> nextNode = successor(x);
                if (nextNode != null) {
                    x.data = nextNode.data;//将数据复制给x，然后就成了删除后继节点的情况了（后继节点最多只有一个孩子）。
                    x = nextNode;// 把要真正删除的节点指针移到后继结点
                }
            }

            // 找到下一个节点：此时x最多只有一个节点。
            RedBlackTreeNode<T> childNode = (x.left != null ? x.left : x.right);

            if (childNode != null) {
                // 删除节点然后修复
                if (x.parent == null) {
                    root = x;
                } else {
                    childNode.parent = x.parent;
                    if (x == x.parent.left) {
                        x.parent.left = childNode;
                    } else {
                        x.parent.right = childNode;
                    }
                }
                x.left = x.right = x.parent = null;
                if (x.color == BLACK) {
                    deleteFix(childNode);
                }
            } else {
                // 如果没有子节点
                if (x.parent == null) {
                    root = null;
                } else {
                    // 红色叶子节点直接删除
                    // 黑色叶子节点的话，先调整再删除（自己作自己的后继节点，这样不为空）
                    if (x.color == BLACK) {
                        deleteFix(x);
                    }
                    if (x == x.parent.left) {
                        x.parent.left = null;
                    } else {
                        x.parent.right = null;
                    }
                    x.parent = null;
                }
            }
        } else {
            throw new NullPointerException("insert node and data can not be null");
        }
    }

    // 找到一个节点的后继节点
    private static <T extends Comparable<T>> RedBlackTreeNode<T> successor(RedBlackTreeNode<T> x) {
        if (x != null) {
            if (x.right != null) {
                // 找到右子树最小的
                RedBlackTreeNode<T> p = x.right;
                while (p.left != null) {
                    p = p.left;
                }
                return p;
            } else {
                // 右子树为空，则只能往上找。要找到是左孩子的祖宗节点。（）
                RedBlackTreeNode<T> p = x.parent;
                RedBlackTreeNode<T> ch = x;
                while (p != null && ch == p.right) {
                    ch = p;
                    p = p.parent;
                }
                return p;
            }
        }
        return null;
    }

    // 修复要删除节点的替代节点
    private void deleteFix(RedBlackTreeNode<T> x) {
        while (x != root && colorOf(x) == BLACK) {
            if (x == leftOf(parentOf(x))) {
                RedBlackTreeNode<T> brother = rightOf(parentOf(x));
                // 情况a
                if (colorOf(brother) == RED) {
                    setColor(brother, BLACK);
                    setColor(parentOf(x), RED);
                    rotateLeft(parentOf(x));
                    brother = rightOf(parentOf(x));
                }
                // 情况b
                if (colorOf(leftOf(brother)) == BLACK &&
                        colorOf(rightOf(brother)) == BLACK) {
                    setColor(brother, RED);
                    x = parentOf(x);
                } else {
                    // 情况c
                    if (colorOf(rightOf(brother)) == BLACK) {
                        setColor(leftOf(brother), BLACK);
                        setColor(brother, RED);
                        rotateRight(brother);
                        brother = rightOf(parentOf(x));
                    }
                    // 情况d
                    setColor(brother, colorOf(parentOf(x)));
                    setColor(parentOf(x), BLACK);
                    setColor(rightOf(x), BLACK);
                    rotateLeft(parentOf(x));
                    x = root;
                }
            } else {
                RedBlackTreeNode<T> brother = leftOf(parentOf(x));
                if (colorOf(brother) == RED) {
                    setColor(brother, BLACK);
                    setColor(parentOf(x), RED);
                    rotateRight(parentOf(x));
                    brother = leftOf(parentOf(x));
                }
                if (colorOf(rightOf(brother)) == BLACK &&
                        colorOf(leftOf(brother)) == BLACK) {
                    setColor(brother, RED);
                    x = parentOf(x);
                } else {
                    if (colorOf(leftOf(brother)) == BLACK) {
                        setColor(rightOf(brother), BLACK);
                        setColor(brother, RED);
                        rotateLeft(brother);
                        brother = leftOf(parentOf(x));
                    }
                    setColor(brother, colorOf(parentOf(x)));
                    setColor(parentOf(x), BLACK);
                    setColor(leftOf(brother), BLACK);
                    rotateRight(parentOf(x));
                    x = root;
                }

            }
        }
        x.color = BLACK;
    }

    // T 是可比较的节点数据对象 小于为-1 等于为0 大于为1
    private static class RedBlackTreeNode<T extends Comparable<T>> {

        T data; // 节点数据,由于要被比较，因此不能为空

        RedBlackTreeNode<T> left; // 左孩子

        RedBlackTreeNode<T> right; // 右孩子

        RedBlackTreeNode<T> parent; // 父节点

        boolean color;// 默认黑色

        RedBlackTreeNode(T data) {
            this.data = data;
        }
    }
}