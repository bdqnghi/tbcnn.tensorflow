/*
 * Decompiled with CFR 0_115.
 * 
 * Could not load the following classes:
 *  javax.annotation.Nullable
 */
package com.google.common.collect;

import com.google.common.base.MoreObjects;
import com.google.common.base.Preconditions;
import com.google.common.collect.Multisets;
import com.google.common.collect.Multisets$AbstractEntry;
import com.google.common.collect.TreeMultiset;
import java.util.Comparator;
import javax.annotation.Nullable;

final class TreeMultiset$AvlNode
extends Multisets$AbstractEntry {
    @Nullable
    private final Object elem;
    private int elemCount;
    private int distinctElements;
    private long totalCount;
    private int height;
    private TreeMultiset$AvlNode left;
    private TreeMultiset$AvlNode right;
    private TreeMultiset$AvlNode pred;
    private TreeMultiset$AvlNode succ;

    TreeMultiset$AvlNode(@Nullable Object object, int n2) {
        Preconditions.checkArgument(n2 > 0);
        this.elem = object;
        this.elemCount = n2;
        this.totalCount = n2;
        this.distinctElements = 1;
        this.height = 1;
        this.left = null;
        this.right = null;
    }

    public int count(Comparator comparator, Object object) {
        int n2 = comparator.compare(object, this.elem);
        if (n2 < 0) {
            if (this.left == null) {
                return 0;
            }
            int n3 = this.left.count(comparator, object);
            return n3;
        }
        if (n2 <= 0) return this.elemCount;
        if (this.right == null) {
            return 0;
        }
        int n4 = this.right.count(comparator, object);
        return n4;
    }

    private TreeMultiset$AvlNode addRightChild(Object object, int n2) {
        this.right = new TreeMultiset$AvlNode(object, n2);
        TreeMultiset.access$1700(this, this.right, this.succ);
        this.height = Math.max(2, this.height);
        ++this.distinctElements;
        this.totalCount += (long)n2;
        return this;
    }

    private TreeMultiset$AvlNode addLeftChild(Object object, int n2) {
        this.left = new TreeMultiset$AvlNode(object, n2);
        TreeMultiset.access$1700(this.pred, this.left, this);
        this.height = Math.max(2, this.height);
        ++this.distinctElements;
        this.totalCount += (long)n2;
        return this;
    }

    TreeMultiset$AvlNode add(Comparator comparator, @Nullable Object object, int n2, int[] arrn) {
        int n3 = comparator.compare(object, this.elem);
        if (n3 < 0) {
            TreeMultiset$AvlNode treeMultiset$AvlNode;
            TreeMultiset$AvlNode treeMultiset$AvlNode2 = this.left;
            if (treeMultiset$AvlNode2 == null) {
                arrn[0] = 0;
                return this.addLeftChild(object, n2);
            }
            int n4 = treeMultiset$AvlNode2.height;
            this.left = treeMultiset$AvlNode2.add(comparator, object, n2, arrn);
            if (arrn[0] == 0) {
                ++this.distinctElements;
            }
            this.totalCount += (long)n2;
            if (this.left.height == n4) {
                treeMultiset$AvlNode = this;
                return treeMultiset$AvlNode;
            }
            treeMultiset$AvlNode = this.rebalance();
            return treeMultiset$AvlNode;
        }
        if (n3 > 0) {
            TreeMultiset$AvlNode treeMultiset$AvlNode;
            TreeMultiset$AvlNode treeMultiset$AvlNode3 = this.right;
            if (treeMultiset$AvlNode3 == null) {
                arrn[0] = 0;
                return this.addRightChild(object, n2);
            }
            int n5 = treeMultiset$AvlNode3.height;
            this.right = treeMultiset$AvlNode3.add(comparator, object, n2, arrn);
            if (arrn[0] == 0) {
                ++this.distinctElements;
            }
            this.totalCount += (long)n2;
            if (this.right.height == n5) {
                treeMultiset$AvlNode = this;
                return treeMultiset$AvlNode;
            }
            treeMultiset$AvlNode = this.rebalance();
            return treeMultiset$AvlNode;
        }
        arrn[0] = this.elemCount;
        long l2 = (long)this.elemCount + (long)n2;
        Preconditions.checkArgument(l2 <= Integer.MAX_VALUE);
        this.elemCount += n2;
        this.totalCount += (long)n2;
        return this;
    }

    TreeMultiset$AvlNode remove(Comparator comparator, @Nullable Object object, int n2, int[] arrn) {
        int n3 = comparator.compare(object, this.elem);
        if (n3 < 0) {
            TreeMultiset$AvlNode treeMultiset$AvlNode;
            TreeMultiset$AvlNode treeMultiset$AvlNode2 = this.left;
            if (treeMultiset$AvlNode2 == null) {
                arrn[0] = 0;
                return this;
            }
            this.left = treeMultiset$AvlNode2.remove(comparator, object, n2, arrn);
            if (arrn[0] > 0) {
                if (n2 >= arrn[0]) {
                    --this.distinctElements;
                    this.totalCount -= (long)arrn[0];
                } else {
                    this.totalCount -= (long)n2;
                }
            }
            if (arrn[0] == 0) {
                treeMultiset$AvlNode = this;
                return treeMultiset$AvlNode;
            }
            treeMultiset$AvlNode = this.rebalance();
            return treeMultiset$AvlNode;
        }
        if (n3 > 0) {
            TreeMultiset$AvlNode treeMultiset$AvlNode = this.right;
            if (treeMultiset$AvlNode == null) {
                arrn[0] = 0;
                return this;
            }
            this.right = treeMultiset$AvlNode.remove(comparator, object, n2, arrn);
            if (arrn[0] <= 0) return this.rebalance();
            if (n2 >= arrn[0]) {
                --this.distinctElements;
                this.totalCount -= (long)arrn[0];
                return this.rebalance();
            }
            this.totalCount -= (long)n2;
            return this.rebalance();
        }
        arrn[0] = this.elemCount;
        if (n2 >= this.elemCount) {
            return this.deleteMe();
        }
        this.elemCount -= n2;
        this.totalCount -= (long)n2;
        return this;
    }

    TreeMultiset$AvlNode setCount(Comparator comparator, @Nullable Object object, int n2, int[] arrn) {
        int n3 = comparator.compare(object, this.elem);
        if (n3 < 0) {
            TreeMultiset$AvlNode treeMultiset$AvlNode = this.left;
            if (treeMultiset$AvlNode == null) {
                TreeMultiset$AvlNode treeMultiset$AvlNode2;
                arrn[0] = 0;
                if (n2 > 0) {
                    treeMultiset$AvlNode2 = this.addLeftChild(object, n2);
                    return treeMultiset$AvlNode2;
                }
                treeMultiset$AvlNode2 = this;
                return treeMultiset$AvlNode2;
            }
            this.left = treeMultiset$AvlNode.setCount(comparator, object, n2, arrn);
            if (n2 == 0 && arrn[0] != 0) {
                --this.distinctElements;
            } else if (n2 > 0 && arrn[0] == 0) {
                ++this.distinctElements;
            }
            this.totalCount += (long)(n2 - arrn[0]);
            return this.rebalance();
        }
        if (n3 > 0) {
            TreeMultiset$AvlNode treeMultiset$AvlNode = this.right;
            if (treeMultiset$AvlNode == null) {
                TreeMultiset$AvlNode treeMultiset$AvlNode3;
                arrn[0] = 0;
                if (n2 > 0) {
                    treeMultiset$AvlNode3 = this.addRightChild(object, n2);
                    return treeMultiset$AvlNode3;
                }
                treeMultiset$AvlNode3 = this;
                return treeMultiset$AvlNode3;
            }
            this.right = treeMultiset$AvlNode.setCount(comparator, object, n2, arrn);
            if (n2 == 0 && arrn[0] != 0) {
                --this.distinctElements;
            } else if (n2 > 0 && arrn[0] == 0) {
                ++this.distinctElements;
            }
            this.totalCount += (long)(n2 - arrn[0]);
            return this.rebalance();
        }
        arrn[0] = this.elemCount;
        if (n2 == 0) {
            return this.deleteMe();
        }
        this.totalCount += (long)(n2 - this.elemCount);
        this.elemCount = n2;
        return this;
    }

    TreeMultiset$AvlNode setCount(Comparator comparator, @Nullable Object object, int n2, int n3, int[] arrn) {
        int n4 = comparator.compare(object, this.elem);
        if (n4 < 0) {
            TreeMultiset$AvlNode treeMultiset$AvlNode = this.left;
            if (treeMultiset$AvlNode == null) {
                arrn[0] = 0;
                if (n2 != 0) return this;
                if (n3 <= 0) return this;
                return this.addLeftChild(object, n3);
            }
            this.left = treeMultiset$AvlNode.setCount(comparator, object, n2, n3, arrn);
            if (arrn[0] != n2) return this.rebalance();
            if (n3 == 0 && arrn[0] != 0) {
                --this.distinctElements;
            } else if (n3 > 0 && arrn[0] == 0) {
                ++this.distinctElements;
            }
            this.totalCount += (long)(n3 - arrn[0]);
            return this.rebalance();
        }
        if (n4 > 0) {
            TreeMultiset$AvlNode treeMultiset$AvlNode = this.right;
            if (treeMultiset$AvlNode == null) {
                arrn[0] = 0;
                if (n2 != 0) return this;
                if (n3 <= 0) return this;
                return this.addRightChild(object, n3);
            }
            this.right = treeMultiset$AvlNode.setCount(comparator, object, n2, n3, arrn);
            if (arrn[0] != n2) return this.rebalance();
            if (n3 == 0 && arrn[0] != 0) {
                --this.distinctElements;
            } else if (n3 > 0 && arrn[0] == 0) {
                ++this.distinctElements;
            }
            this.totalCount += (long)(n3 - arrn[0]);
            return this.rebalance();
        }
        arrn[0] = this.elemCount;
        if (n2 != this.elemCount) return this;
        if (n3 == 0) {
            return this.deleteMe();
        }
        this.totalCount += (long)(n3 - this.elemCount);
        this.elemCount = n3;
        return this;
    }

    private TreeMultiset$AvlNode deleteMe() {
        int n2 = this.elemCount;
        this.elemCount = 0;
        TreeMultiset.access$1800(this.pred, this.succ);
        if (this.left == null) {
            return this.right;
        }
        if (this.right == null) {
            return this.left;
        }
        if (this.left.height >= this.right.height) {
            TreeMultiset$AvlNode treeMultiset$AvlNode = this.pred;
            treeMultiset$AvlNode.left = this.left.removeMax(treeMultiset$AvlNode);
            treeMultiset$AvlNode.right = this.right;
            treeMultiset$AvlNode.distinctElements = this.distinctElements - 1;
            treeMultiset$AvlNode.totalCount = this.totalCount - (long)n2;
            return treeMultiset$AvlNode.rebalance();
        }
        TreeMultiset$AvlNode treeMultiset$AvlNode = this.succ;
        treeMultiset$AvlNode.right = this.right.removeMin(treeMultiset$AvlNode);
        treeMultiset$AvlNode.left = this.left;
        treeMultiset$AvlNode.distinctElements = this.distinctElements - 1;
        treeMultiset$AvlNode.totalCount = this.totalCount - (long)n2;
        return treeMultiset$AvlNode.rebalance();
    }

    private TreeMultiset$AvlNode removeMin(TreeMultiset$AvlNode treeMultiset$AvlNode) {
        if (this.left == null) {
            return this.right;
        }
        this.left = this.left.removeMin(treeMultiset$AvlNode);
        --this.distinctElements;
        this.totalCount -= (long)treeMultiset$AvlNode.elemCount;
        return this.rebalance();
    }

    private TreeMultiset$AvlNode removeMax(TreeMultiset$AvlNode treeMultiset$AvlNode) {
        if (this.right == null) {
            return this.left;
        }
        this.right = this.right.removeMax(treeMultiset$AvlNode);
        --this.distinctElements;
        this.totalCount -= (long)treeMultiset$AvlNode.elemCount;
        return this.rebalance();
    }

    private void recomputeMultiset() {
        this.distinctElements = 1 + TreeMultiset.distinctElements(this.left) + TreeMultiset.distinctElements(this.right);
        this.totalCount = (long)this.elemCount + TreeMultiset$AvlNode.totalCount(this.left) + TreeMultiset$AvlNode.totalCount(this.right);
    }

    private void recomputeHeight() {
        this.height = 1 + Math.max(TreeMultiset$AvlNode.height(this.left), TreeMultiset$AvlNode.height(this.right));
    }

    private void recompute() {
        this.recomputeMultiset();
        this.recomputeHeight();
    }

    private TreeMultiset$AvlNode rebalance() {
        switch (this.balanceFactor()) {
            case -2: {
                if (this.right.balanceFactor() <= 0) return this.rotateLeft();
                this.right = this.right.rotateRight();
                return this.rotateLeft();
            }
            case 2: {
                if (this.left.balanceFactor() >= 0) return this.rotateRight();
                this.left = this.left.rotateLeft();
                return this.rotateRight();
            }
        }
        this.recomputeHeight();
        return this;
    }

    private int balanceFactor() {
        return TreeMultiset$AvlNode.height(this.left) - TreeMultiset$AvlNode.height(this.right);
    }

    private TreeMultiset$AvlNode rotateLeft() {
        Preconditions.checkState(this.right != null);
        TreeMultiset$AvlNode treeMultiset$AvlNode = this.right;
        this.right = treeMultiset$AvlNode.left;
        treeMultiset$AvlNode.left = this;
        treeMultiset$AvlNode.totalCount = this.totalCount;
        treeMultiset$AvlNode.distinctElements = this.distinctElements;
        this.recompute();
        treeMultiset$AvlNode.recomputeHeight();
        return treeMultiset$AvlNode;
    }

    private TreeMultiset$AvlNode rotateRight() {
        Preconditions.checkState(this.left != null);
        TreeMultiset$AvlNode treeMultiset$AvlNode = this.left;
        this.left = treeMultiset$AvlNode.right;
        treeMultiset$AvlNode.right = this;
        treeMultiset$AvlNode.totalCount = this.totalCount;
        treeMultiset$AvlNode.distinctElements = this.distinctElements;
        this.recompute();
        treeMultiset$AvlNode.recomputeHeight();
        return treeMultiset$AvlNode;
    }

    private static long totalCount(@Nullable TreeMultiset$AvlNode treeMultiset$AvlNode) {
        if (treeMultiset$AvlNode == null) {
            return 0;
        }
        long l2 = treeMultiset$AvlNode.totalCount;
        return l2;
    }

    private static int height(@Nullable TreeMultiset$AvlNode treeMultiset$AvlNode) {
        if (treeMultiset$AvlNode == null) {
            return 0;
        }
        int n2 = treeMultiset$AvlNode.height;
        return n2;
    }

    @Nullable
    private TreeMultiset$AvlNode ceiling(Comparator comparator, Object object) {
        int n2 = comparator.compare(object, this.elem);
        if (n2 < 0) {
            TreeMultiset$AvlNode treeMultiset$AvlNode;
            if (this.left == null) {
                treeMultiset$AvlNode = this;
                return treeMultiset$AvlNode;
            }
            treeMultiset$AvlNode = (TreeMultiset$AvlNode)MoreObjects.firstNonNull(this.left.ceiling(comparator, object), this);
            return treeMultiset$AvlNode;
        }
        if (n2 == 0) {
            return this;
        }
        if (this.right == null) {
            return null;
        }
        TreeMultiset$AvlNode treeMultiset$AvlNode = this.right.ceiling(comparator, object);
        return treeMultiset$AvlNode;
    }

    @Nullable
    private TreeMultiset$AvlNode floor(Comparator comparator, Object object) {
        int n2 = comparator.compare(object, this.elem);
        if (n2 > 0) {
            TreeMultiset$AvlNode treeMultiset$AvlNode;
            if (this.right == null) {
                treeMultiset$AvlNode = this;
                return treeMultiset$AvlNode;
            }
            treeMultiset$AvlNode = (TreeMultiset$AvlNode)MoreObjects.firstNonNull(this.right.floor(comparator, object), this);
            return treeMultiset$AvlNode;
        }
        if (n2 == 0) {
            return this;
        }
        if (this.left == null) {
            return null;
        }
        TreeMultiset$AvlNode treeMultiset$AvlNode = this.left.floor(comparator, object);
        return treeMultiset$AvlNode;
    }

    @Override
    public Object getElement() {
        return this.elem;
    }

    @Override
    public int getCount() {
        return this.elemCount;
    }

    @Override
    public String toString() {
        return Multisets.immutableEntry(this.getElement(), this.getCount()).toString();
    }

    static /* synthetic */ int access$200(TreeMultiset$AvlNode treeMultiset$AvlNode) {
        return treeMultiset$AvlNode.elemCount;
    }

    static /* synthetic */ long access$300(TreeMultiset$AvlNode treeMultiset$AvlNode) {
        return treeMultiset$AvlNode.totalCount;
    }

    static /* synthetic */ int access$400(TreeMultiset$AvlNode treeMultiset$AvlNode) {
        return treeMultiset$AvlNode.distinctElements;
    }

    static /* synthetic */ Object access$500(TreeMultiset$AvlNode treeMultiset$AvlNode) {
        return treeMultiset$AvlNode.elem;
    }

    static /* synthetic */ TreeMultiset$AvlNode access$600(TreeMultiset$AvlNode treeMultiset$AvlNode) {
        return treeMultiset$AvlNode.left;
    }

    static /* synthetic */ TreeMultiset$AvlNode access$700(TreeMultiset$AvlNode treeMultiset$AvlNode) {
        return treeMultiset$AvlNode.right;
    }

    static /* synthetic */ TreeMultiset$AvlNode access$800(TreeMultiset$AvlNode treeMultiset$AvlNode, Comparator comparator, Object object) {
        return treeMultiset$AvlNode.ceiling(comparator, object);
    }

    static /* synthetic */ TreeMultiset$AvlNode access$900(TreeMultiset$AvlNode treeMultiset$AvlNode) {
        return treeMultiset$AvlNode.succ;
    }

    static /* synthetic */ TreeMultiset$AvlNode access$1000(TreeMultiset$AvlNode treeMultiset$AvlNode, Comparator comparator, Object object) {
        return treeMultiset$AvlNode.floor(comparator, object);
    }

    static /* synthetic */ TreeMultiset$AvlNode access$1100(TreeMultiset$AvlNode treeMultiset$AvlNode) {
        return treeMultiset$AvlNode.pred;
    }

    static /* synthetic */ TreeMultiset$AvlNode access$902(TreeMultiset$AvlNode treeMultiset$AvlNode, TreeMultiset$AvlNode treeMultiset$AvlNode2) {
        treeMultiset$AvlNode.succ = treeMultiset$AvlNode2;
        return treeMultiset$AvlNode.succ;
    }

    static /* synthetic */ TreeMultiset$AvlNode access$1102(TreeMultiset$AvlNode treeMultiset$AvlNode, TreeMultiset$AvlNode treeMultiset$AvlNode2) {
        treeMultiset$AvlNode.pred = treeMultiset$AvlNode2;
        return treeMultiset$AvlNode.pred;
    }
}

