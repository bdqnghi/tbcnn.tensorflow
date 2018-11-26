package avlTree;

import java.util.Stack;

import tree.ITree;
import tree.nodeProviders.ITreeNodeProvider;
import avlTree.helpers.AvlTreeHelpers;
import avlTree.helpers.IRebalancingCounter;
import avlTree.nodes.AvlTreeNode;

public class AvlTree implements IAvlTree {
    private AvlTreeNode root;
    private ITreeNodeProvider<AvlTreeNode> nodeProvider;
    private IAvlTreeManager avlTreeManager;

    public AvlTree(
            AvlTreeNode root,
            ITreeNodeProvider<AvlTreeNode> nodeProvider,
            IAvlTreeManager avlTreeFactory) {
        this.root = root;
        this.nodeProvider = nodeProvider;
        this.avlTreeManager = avlTreeFactory;
    }

    @Override
    public AvlTreeNode getRoot() {
        return root;
    }

    @Override
    public boolean isEmpty() {
        return root == null;
    }

    @Override
    public ITree<AvlTreeNode> getLeftSubTree() {
        return avlTreeManager.createNewTree(nodeProvider.get(root.leftSonNumber));
    }

    @Override
    public ITree<AvlTreeNode> getRightSubTree() {
        return avlTreeManager.createNewTree(nodeProvider.get(root.rightSonNumber));
    }

    @Override
    public void disposeAllButThis() {
        nodeProvider.disposeAllBut(root == null ? -1 : root.number);
    }

    @Override
    public IAvlTree split(long inclusiveStart, long exclusiveEnd, IRebalancingCounter rebalancingCounter) {
        return AvlTreeHelpers.substring(this, inclusiveStart, exclusiveEnd, rebalancingCounter);
    }

    @Override
    public long getHeight() {
        if (isEmpty())
            return 0;
        return getRoot().height;
    }

    @Override
    public long getWidth() {
        if (isEmpty())
            return 0;
        return getRoot().width;
    }

    @Override
    public void dispose() {
        avlTreeManager.dispose();
    }

    @Override
    public IAvlTree merge(IAvlTree right, IRebalancingCounter rebalancingCounter) {
        if (this.isEmpty())
            return right;
        if (right.isEmpty())
            return this;

        if (this.getHeight() >= right.getHeight()) {
            Stack<IAvlTree> path = AvlTreeHelpers.getRightmostPathToNodeOfFixedHeight(this, right.getHeight());
            if (path.isEmpty())
                throw new AssertionError("The path up to node of height " + right.getHeight() + " not found.");
            return rebalanceRight(right, path, rebalancingCounter);
        }

        Stack<IAvlTree> path = AvlTreeHelpers.getLeftmostPathToNodeOfFixedHeight(right, this.getHeight());
        if (path.isEmpty())
            throw new AssertionError("The path up to node of height " + this.getHeight() + " not found.");
        return this.rebalanceLeft(this, path, rebalancingCounter);
    }

    private IAvlTree spinRight(IAvlTree node) {
        IAvlTree bNode = (IAvlTree) node.getLeftSubTree();
        IAvlTree dNode = (IAvlTree) node.getRightSubTree();
        IAvlTree cNode = (IAvlTree) dNode.getLeftSubTree();
        IAvlTree eNode = (IAvlTree) dNode.getRightSubTree();

        if (eNode.getHeight() > cNode.getHeight()) {
            IAvlTree dNewNode = avlTreeManager.concatenate(bNode, cNode);
            return avlTreeManager.concatenate(dNewNode, eNode);
        }

        IAvlTree fNode = (IAvlTree) cNode.getLeftSubTree();
        IAvlTree gNode = (IAvlTree) cNode.getRightSubTree();

        IAvlTree cNewNode = avlTreeManager.concatenate(bNode, fNode);
        IAvlTree dNewNode = avlTreeManager.concatenate(gNode, eNode);
        return avlTreeManager.concatenate(cNewNode, dNewNode);
    }

    private IAvlTree spinLeft(IAvlTree node) {
        IAvlTree dNode = (IAvlTree) node.getLeftSubTree();
        IAvlTree bNode = (IAvlTree) node.getRightSubTree();
        IAvlTree eNode = (IAvlTree) dNode.getLeftSubTree();
        IAvlTree cNode = (IAvlTree) dNode.getRightSubTree();

        if (eNode.getHeight() > cNode.getHeight()) {
            IAvlTree dNewNode = avlTreeManager.concatenate(cNode, bNode);
            return avlTreeManager.concatenate(eNode, dNewNode);
        }

        IAvlTree fNode = (IAvlTree) cNode.getRightSubTree();
        IAvlTree gNode = (IAvlTree) cNode.getLeftSubTree();

        IAvlTree cNewNode = avlTreeManager.concatenate(fNode, bNode);
        IAvlTree dNewNode = avlTreeManager.concatenate(eNode, gNode);

        return avlTreeManager.concatenate(dNewNode, cNewNode);
    }

    private IAvlTree rebalanceLeft(IAvlTree left, Stack<IAvlTree> path, IRebalancingCounter rebalancingCounter) {
        IAvlTree newRoot = avlTreeManager.concatenate(left, path.pop());

        while (!path.empty()) {
            IAvlTree bNode = (IAvlTree) path.pop().getRightSubTree();
            IAvlTree dNode = newRoot;

            IAvlTree newLeftSon = avlTreeManager.concatenate(dNode, bNode);
            if (!newLeftSon.getRoot().isBalanced) {
                rebalancingCounter.inc();
                if (dNode.getHeight() != bNode.getHeight() + 2)
                    throw new AssertionError("Unable to rebelance AVL-tree since the following condition is broken getHeight(D) = getHeight(B) + 2.");

                newRoot = this.spinLeft(newLeftSon);
                if (!newRoot.getRoot().isBalanced)
                    throw new AssertionError("Rebalancing of AVL-tree finished unsuccessfully.");
            } else
                newRoot = newLeftSon;
        }
        return newRoot;
    }

    private IAvlTree rebalanceRight(IAvlTree right, Stack<IAvlTree> path, IRebalancingCounter rebalancingCounter) {
        IAvlTree newRoot = avlTreeManager.concatenate(path.pop(), right);

        while (!path.empty()) {
            IAvlTree bNode = (IAvlTree) path.pop().getLeftSubTree();
            IAvlTree dNode = newRoot;

            IAvlTree newRightSon = avlTreeManager.concatenate(bNode, dNode);

            if (!newRightSon.getRoot().isBalanced) {
                rebalancingCounter.inc();
                if (dNode.getHeight() != bNode.getHeight() + 2)
                    throw new AssertionError("Unable to rebelance AVL-tree since the following condition is broken getHeight(D) = getHeight(B) + 2.");

                newRoot = this.spinRight(newRightSon);
                if (!newRoot.getRoot().isBalanced)
                    throw new AssertionError("Rebalancing of AVL-tree finished unsuccessfully.");
            } else
                newRoot = newRightSon;
        }
        return newRoot;
    }
}
