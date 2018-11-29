/*
 * RedBlackTreeInsertCorrectionAlgorithm.java v0.10 03/04/10
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
 * This class defines the red black tree insert correction algorithm. It is
 * composed by the red black tree on which the algorithm is applied and the node
 * from which the correction is made. This class is not designed for
 * inheritance.
 *
 * @author Damien Rigoni
 * @version 0.10 03/04/10
 * @see IBinaryTreeAlgorithm
 */
public final class RedBlackTreeInsertCorrectionAlgorithm implements IBinaryTreeAlgorithm {

    private RedBlackTree tree;

    private RedBlackNode node;

    /**
     * Builds the red black tree insert correction algorithm.
     *
     * @param t the red black tree on which the algorithm is applied
     * @param n the red black node from which the correction is made
     */
    public RedBlackTreeInsertCorrectionAlgorithm(RedBlackTree t, RedBlackNode n) {
        tree = t;
        node = n;
    }

    @Override
    public final Object applyAlgorithm() {
        RedBlackNode y;

        while ((node.getFather() != null) && (node.getFather().isRed())) {
            if (node.getFather().getFather() != null) {
                if (node.getFather() == node.getFather().getFather().getLeft()) {
                    y = node.getFather().getFather().getRight();

                    if ((y != null) && y.isRed()) {
                        node.getFather().setColor(RedBlackNode.RedBlackNodeColor.BLACK);
                        y.setColor(RedBlackNode.RedBlackNodeColor.BLACK);
                        node.getFather().getFather().setColor(RedBlackNode.RedBlackNodeColor.RED);
                        node = node.getFather().getFather();
                    } else {
                        if (node == node.getFather().getRight()) {
                            node = node.getFather();
                            new RedBlackTreeLeftRotationAlgorithm(tree, node).applyAlgorithm();
                        }
                        node.getFather().setColor(RedBlackNode.RedBlackNodeColor.BLACK);
                        node.getFather().getFather().setColor(RedBlackNode.RedBlackNodeColor.RED);
                        new RedBlackTreeRightRotationAlgorithm(tree, node.getFather().getFather()).applyAlgorithm();
                    }
                } else {
                    y = node.getFather().getFather().getLeft();

                    if ((y != null) && y.isRed()) {
                        node.getFather().setColor(RedBlackNode.RedBlackNodeColor.BLACK);
                        y.setColor(RedBlackNode.RedBlackNodeColor.BLACK);
                        node.getFather().getFather().setColor(RedBlackNode.RedBlackNodeColor.RED);
                        node = node.getFather().getFather();
                    } else {
                        if (node == node.getFather().getLeft()) {
                            node = node.getFather();
                            new RedBlackTreeRightRotationAlgorithm(tree, node).applyAlgorithm();
                        }
                        node.getFather().setColor(RedBlackNode.RedBlackNodeColor.BLACK);
                        node.getFather().getFather().setColor(RedBlackNode.RedBlackNodeColor.RED);
                        new RedBlackTreeLeftRotationAlgorithm(tree, node.getFather().getFather()).applyAlgorithm();
                    }
                }
            }
        }
        tree.getRoot().setColor(RedBlackNode.RedBlackNodeColor.BLACK);

        return tree.getRoot();
    }
}
