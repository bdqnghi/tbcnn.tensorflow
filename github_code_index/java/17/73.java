package redblacktree;

import static redblacktree.NodeHelper.blackNode;
import static redblacktree.NodeHelper.checkTrees;
import static redblacktree.NodeHelper.empty;
import static redblacktree.NodeHelper.redNode;

import org.junit.Test;

public class Put {

  // Case 1

  @Test
  public void testCaseOne() {
    Node<Integer, String> root = empty();
    RedBlackTree<Integer, String> tree = new RedBlackTree<Integer, String>(root);
    tree.put(1, "1");
    Node<Integer, String> expected = blackNode(1);
    checkTrees(tree, expected);
  }

  // Case 2

  @Test
  public void testCaseTwoL() {
    Node<Integer, String> root = blackNode(1);
    RedBlackTree<Integer, String> tree = new RedBlackTree<Integer, String>(root);
    tree.put(0, "0");

    Node<Integer, String> expected = blackNode(1, redNode(0, empty(), empty()),
        empty());
    checkTrees(tree, expected);
  }

  @Test
  public void testCaseTwoR() {
    Node<Integer, String> root = blackNode(1);
    RedBlackTree<Integer, String> tree = new RedBlackTree<Integer, String>(root);
    tree.put(2, "2");

    Node<Integer, String> expected = blackNode(1, empty(),
        redNode(2, empty(), empty()));
    checkTrees(tree, expected);
  }

  // Case 3 then Case 1

  private RedBlackTree<Integer, String> threeOneTree() {
    Node<Integer, String> root = blackNode(3, redNode(1), redNode(5));
    RedBlackTree<Integer, String> tree = new RedBlackTree<Integer, String>(root);
    return tree;
  }

  @Test
  public void testCaseThreeOne1() {
    RedBlackTree<Integer, String> tree = threeOneTree();
    tree.put(0, "0");

    Node<Integer, String> expected = blackNode(3,
        blackNode(1, redNode(0), empty()), blackNode(5));

    checkTrees(tree, expected);
  }

  @Test
  public void testCaseThreeOne2() {
    RedBlackTree<Integer, String> tree = threeOneTree();
    tree.put(2, "2");
    Node<Integer, String> expected = blackNode(3,
        blackNode(1, empty(), redNode(2)), blackNode(5));
    checkTrees(tree, expected);

  }

  @Test
  public void testCaseThreeOne3() {
    RedBlackTree<Integer, String> tree = threeOneTree();
    tree.put(4, "4");
    Node<Integer, String> expected = blackNode(3, blackNode(1),
        blackNode(5, redNode(4), empty()));
    NodeHelper.checkTrees(tree, expected);

  }

  @Test
  public void testCaseThreeOne4() {
    RedBlackTree<Integer, String> tree = threeOneTree();
    tree.put(6, "6");
    Node<Integer, String> expected = blackNode(3, blackNode(1),
        blackNode(5, empty(), redNode(6)));
    checkTrees(tree, expected);

  }

  // Case 3 then Case 2

  private RedBlackTree<Integer, String> threeTwoTreeL() {
    return new RedBlackTree<Integer, String>(blackNode(7,
        blackNode(3, redNode(1), redNode(5)), blackNode(8)));
  }

  private RedBlackTree<Integer, String> threeTwoTreeR() {
    return new RedBlackTree<Integer, String>(blackNode(1, blackNode(0),
        blackNode(5, redNode(3), redNode(7))));
  }

  @Test
  public void testCaseThreeTwo1() {
    RedBlackTree<Integer, String> tree = threeTwoTreeL();
    tree.put(0, "0");
    Node<Integer, String> expected = blackNode(7,
        redNode(3, blackNode(1, redNode(0), empty()), blackNode(5)),
        blackNode(8));
    checkTrees(tree, expected);
  }

  @Test
  public void testCaseThreeTwo2() {
    RedBlackTree<Integer, String> tree = threeTwoTreeL();
    tree.put(2, "2");
    Node<Integer, String> expected = blackNode(7,
        redNode(3, blackNode(1, empty(), redNode(2)), blackNode(5)),
        blackNode(8));
    checkTrees(tree, expected);
  }

  @Test
  public void testCaseThreeTwo3() {
    RedBlackTree<Integer, String> tree = threeTwoTreeL();
    tree.put(4, "4");
    Node<Integer, String> expected = blackNode(7,
        redNode(3, blackNode(1), blackNode(5, redNode(4), empty())),
        blackNode(8));
    checkTrees(tree, expected);
  }

  @Test
  public void testCaseThreeTwo4() {
    RedBlackTree<Integer, String> tree = threeTwoTreeL();
    tree.put(6, "6");
    Node<Integer, String> expected = blackNode(7,
        redNode(3, blackNode(1), blackNode(5, empty(), redNode(6))),
        blackNode(8));
    checkTrees(tree, expected);
  }

  @Test
  public void testCaseThreeTwo5() {
    RedBlackTree<Integer, String> tree = threeTwoTreeR();
    tree.put(2, "2");
    Node<Integer, String> expected = blackNode(1, blackNode(0),
        redNode(5, blackNode(3, redNode(2), empty()), blackNode(7)));
    checkTrees(tree, expected);
  }

  @Test
  public void testCaseThreeTwo6() {
    RedBlackTree<Integer, String> tree = threeTwoTreeR();
    tree.put(4, "4");
    Node<Integer, String> expected = blackNode(1, blackNode(0),
        redNode(5, blackNode(3, empty(), redNode(4)), blackNode(7)));
    checkTrees(tree, expected);
  }

  @Test
  public void testCaseThreeTwo7() {
    RedBlackTree<Integer, String> tree = threeTwoTreeR();
    tree.put(6, "6");
    Node<Integer, String> expected = blackNode(1, blackNode(0),
        redNode(5, blackNode(3), blackNode(7, redNode(6), empty())));
    checkTrees(tree, expected);
  }

  @Test
  public void testCaseThreeTwo8() {
    RedBlackTree<Integer, String> tree = threeTwoTreeR();
    tree.put(8, "8");
    Node<Integer, String> expected = blackNode(1, blackNode(0),
        redNode(5, blackNode(3), blackNode(7, empty(), redNode(8))));
    checkTrees(tree, expected);
  }

  // Just Case 5

  @Test
  public void testCaseThreeFiveL() {
    RedBlackTree<Integer, String> tree = new RedBlackTree<Integer, String>(
        blackNode(3, blackNode(2, redNode(1), empty()), blackNode(4)));
    tree.put(0, "0");
    Node<Integer, String> expected = blackNode(3,
        blackNode(1, redNode(0), redNode(2)), blackNode(4));
    checkTrees(tree, expected);
  }

  @Test
  public void testCaseThreeFiveR() {
    RedBlackTree<Integer, String> tree = new RedBlackTree<Integer, String>(
        blackNode(2, blackNode(1), blackNode(3, empty(), redNode(4))));
    tree.put(5, "5");
    Node<Integer, String> expected = blackNode(2, blackNode(1),
        blackNode(4, redNode(3), redNode(5)));
    checkTrees(tree,expected);
  }

  // Case 3 then 4 then 5

  @Test
  public void testCaseThreeFourFiveL() {
    RedBlackTree<Integer, String> tree = new RedBlackTree<Integer, String>(
        blackNode(10,
            redNode(2, blackNode(1), blackNode(6, redNode(4), redNode(8))),
            blackNode(11)));

    tree.put(3, "3");

    Node<Integer, String> expected = blackNode(6,
        redNode(2, blackNode(1), blackNode(4, redNode(3), empty())),
        redNode(10, blackNode(8), blackNode(11)));

    checkTrees(tree, expected);
  }

  @Test
  public void testCaseThreeFourFiveR() {
    RedBlackTree<Integer, String> tree = new RedBlackTree<Integer, String>(
        blackNode(2, blackNode(1),
            redNode(7, blackNode(4, redNode(3), redNode(5)), blackNode(8))));

    tree.put(6, "6");

    Node<Integer, String> expected = blackNode(4,
        redNode(2, blackNode(1), blackNode(3)),
        redNode(7, blackNode(5, empty(), redNode(6)), blackNode(8)));

    checkTrees(tree, expected);
  }

}
