/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 - 2018 Norwegian Defence Research Establishment / NTNU
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

package no.ntnu.okse.core.topic;

import no.ntnu.okse.exceptions.TopicExceptions;

import java.util.Collection;
import java.util.HashSet;
import java.util.Stack;

public class TopicTools {

  /**
   * Iterative implementation of Depth-First-Search to discover all Topic nodes from a root node.
   *
   * @param root The root node from which the Depth-First-Search is to be performed.
   * @return A HashSet of all the discovered topic nodes.
   */
  private static HashSet<Topic> DFS(Topic root) {

    HashSet<Topic> discovered = new HashSet<>();
    Stack<Topic> queue = new Stack<>();
    queue.push(root);

    while (!queue.empty()) {
      Topic t = queue.pop();
      if (!discovered.contains(t)) {
        discovered.add(t);
        t.getChildren().forEach(queue::push);
      }
    }

    return discovered;
  }

  /**
   * Returns all topic nodes discovered from a collection of root nodes (including the root nodes).
   *
   * @param rootNodes A collection of root nodes that are to be explored.
   * @return A HashSet of the discovered topic nodes from the DFS searches.
   * @throws TopicExceptions.NonRootNodeException If a node in the collection was in fact not a root
   * node.
   */
  public static HashSet<Topic> getAllTopicNodesFromRootNodeSet(Collection<Topic> rootNodes)
      throws TopicExceptions.NonRootNodeException {
    HashSet<Topic> returnSet = new HashSet<>();

    // Iterate over all the nodes in the argument collection
    for (Topic rootNode : rootNodes) {
      // If we have a non-root node we throw an exception, because this method expects root nodes.
      if (!rootNode.isRoot()) {
        throw new TopicExceptions.NonRootNodeException(
            "Expected rootNode, but was " + rootNode);
      }

      // Perform a Depth-First-Search from the root node and add the results to the return set.
      returnSet.addAll(DFS(rootNode));
    }

    return returnSet;
  }

  /**
   * Returns a HashSet of all the topics discovered from a collection of topic nodes (including the
   * start nodes).
   *
   * @param nodes A collection of topic nodes.
   * @return A HasSet with the discovered nodes.
   */
  public static HashSet<Topic> getAllTopicNodesFromNodeSet(Collection<Topic> nodes) {
    HashSet<Topic> returnSet = new HashSet<>();

    // Iterate over all the nodes in the set, and add discovered nodes to the return set.
    for (Topic node : nodes) {
      returnSet.addAll(DFS(node));
    }

    return returnSet;
  }

  /**
   * Retrieves all children from but (but not including) a Topic
   *
   * @param t The Topic node from which to start the child discovery
   * @return A HashSet of the discovered children.
   */
  public static HashSet<Topic> getAllChildrenFromNode(Topic t) {
    HashSet<Topic> returnSet = DFS(t);
    returnSet.remove(t);

    return returnSet;
  }

  /**
   * Retrieves all leaf nodes discovered from (but not including) a Topic
   *
   * @param t The Topic node from which to start the leaf node discovery
   * @return A HashSet of the discovered leaf nodes.
   */
  public static HashSet<Topic> getAllLeafNodesFromNode(Topic t) {
    HashSet<Topic> returnSet = getAllChildrenFromNode(t);

    returnSet.removeIf(current -> !current.isLeaf());

    return returnSet;
  }
}
