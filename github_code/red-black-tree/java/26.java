/*
 * RedBlackTreeDeleteCorrectionAlgorithm.java v0.10 03/04/10
 *
 * Visualgorithm
 * Copyright (C) Hannier, Pironin, Rigoni (visualgo@googlegroups.com)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

package algorithm.tree;

import model.tree.RedBlackNode;
import model.tree.RedBlackTree;

/**
 * This class defines the red black tree delete correction algorithm. It is
 * composed by the red black tree on which the algorithm is applied and the node
 * from which the correction is made. This class is not designed for
 * inheritance.
 *
 * @author Damien Rigoni
 * @version 0.10 03/04/10
 * @see IBinaryTreeAlgorithm
 */
public final class RedBlackTreeDeleteCorrectionAlgorithm implements IBinaryTreeAlgorithm {

    private RedBlackTree tree;

    private RedBlackNode node;

    /**
     * Builds the red black tree delete correction algorithm.
     *
     * @param t the red black tree on which the algorithm is applied
     * @param n the red black node from which the correction is made
     */
    public RedBlackTreeDeleteCorrectionAlgorithm(RedBlackTree t, RedBlackNode n) {
        tree = t;
        node = n;
    }

    @Override
    public final Object applyAlgorithm() {
        RedBlackNode y;
        RedBlackNode x;
        boolean noRedChild;

        if (node.getKey() == -1) {
            x = null;
        } else {
            x = node;
        }
        
        while (x != tree.getRoot() && node.isBlack()) {
            if (x == node.getFather().getLeft()) {
                y = node.getFather().getRight();
                
                if (y.isRed()) {
                    y.setColor(RedBlackNode.RedBlackNodeColor.BLACK);
                    node.getFather().setColor(RedBlackNode.RedBlackNodeColor.RED);
                    new RedBlackTreeLeftRotationAlgorithm(tree, node.getFather()).applyAlgorithm();
                    y = node.getFather().getRight();
                }
                noRedChild = !(((y.getLeft() != null) && y.getLeft().isRed()) ||
                        ((y.getRight() != null) && y.getRight().isRed()));
                
                if (noRedChild) {
                    y.setColor(RedBlackNode.RedBlackNodeColor.RED);
                    node = x = node.getFather();
                } else {
                    if ((y.getRight() == null) || ((y.getRight() != null) && y.getRight().isBlack())) {
                        y.getLeft().setColor(RedBlackNode.RedBlackNodeColor.BLACK);
                        y.setColor(RedBlackNode.RedBlackNodeColor.RED);
                        new RedBlackTreeRightRotationAlgorithm(tree, y).applyAlgorithm();
                        y = node.getFather().getRight();
                    }
                    y.setColor(node.getFather().getColor());
                    node.getFather().setColor(RedBlackNode.RedBlackNodeColor.BLACK);

                    if (y.getRight() != null) {
                        y.getRight().setColor(RedBlackNode.RedBlackNodeColor.BLACK);
                    }
                    new RedBlackTreeLeftRotationAlgorithm(tree, node.getFather()).applyAlgorithm();
                    node = x = tree.getRoot();
                }
            } else {
                y = node.getFather().getLeft();

                if (y.isRed()) {
                    y.setColor(RedBlackNode.RedBlackNodeColor.BLACK);
                    node.getFather().setColor(RedBlackNode.RedBlackNodeColor.RED);
                    new RedBlackTreeRightRotationAlgorithm(tree, node.getFather()).applyAlgorithm();
                    y = node.getFather().getLeft();
                }
                noRedChild = !(((y.getLeft() != null) && y.getLeft().isRed()) || ((y.getRight() != null) && y.getRight().isRed()));

                if (noRedChild) {
                    y.setColor(RedBlackNode.RedBlackNodeColor.RED);
                    node = x = node.getFather();
                } else {
                    if ((y.getLeft() == null) || ((y.getLeft() != null) && y.getLeft().isBlack())) {
                        y.getRight().setColor(RedBlackNode.RedBlackNodeColor.BLACK);
                        y.setColor(RedBlackNode.RedBlackNodeColor.RED);
                        new RedBlackTreeLeftRotationAlgorithm(tree, y).applyAlgorithm();
                        y = node.getFather().getLeft();
                    }
                    y.setColor(node.getFather().getColor());
                    node.getFather().setColor(RedBlackNode.RedBlackNodeColor.BLACK);

                    if (y.getLeft() != null) {
                        y.getLeft().setColor(RedBlackNode.RedBlackNodeColor.BLACK);
                    }
                    new RedBlackTreeRightRotationAlgorithm(tree, node.getFather()).applyAlgorithm();
                    node = x = tree.getRoot();
                }
            }
        }
        x = node;
        node.setColor(RedBlackNode.RedBlackNodeColor.BLACK);
        
        return tree.getRoot();
    }
}
