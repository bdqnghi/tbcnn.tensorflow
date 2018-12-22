/**
 * File: BalancedTree.java
 */
package edu.metrostate.ics240.chapter10;

import java.util.Comparator;

/**
 * A BalancedTree&lt;T&gt; is a binary search tree of T objects stored in a
 * B-tree.
 * <p>
 * <b>Rules of the B-tree:</b>
 * <ol>
 * <li>The root can have as few as one item (or even no items if it has no
 * children); every other node has at least <code>getMinNumberOfItems()</code>.
 * </li>
 * <li>The maximum number of items in a node is twice the value of
 * getMinNumberOfItems(), which is equal to getMaxNumberOfItems().</li>
 * <li>The items of each B-tree node are stored in a partially filled array,
 * sorted from the smallest item (at index 0) to the largest item (at the final
 * used position of the array).</li>
 * <li>The number of children below a non-leaf node is always one more than the
 * number of items in the node.</li>
 * <li>For any non-leaf node:
 * <ul>
 * <li>An item at index <i>i</i> is greater than or equal to all the items in child number
 * <i>i</i> of the node.</li>
 * <li>An item at index <i>i</i> is less than or equal to all the items in child number
 * <i>i</i> + 1 of the node.</li>
 * </ul>
 * </li>
 * <li>Every leaf in a B-tree has the same depth.</li>
 * </ol>
 * 
 * @author Vincent J Palodichuk <a HREF="mailto:hu0011wy@metrostate.edu">
 *         (e-mail me) </a>
 *
 * @version 07/28/2017
 *
 */
public class BalancedTree<T extends Comparable<T>> implements Cloneable {
	protected static final int DEFAULT_MINIMUM_NUMBER_OF_ITEMS = 1;

	// INVARIANT for the BalancedTree<T> ADT:
	// 1. The items of the Tree are stored in a B-tree, satisfying the six
	// B-tree rules.
	// 2. The number of items in the tree's root is in the instance
	// variable numberOfItems, and the number of subtrees of the root is stored
	// stored in the instance variable numberOfChildren.
	// 3. The root's items are stored in items[0] through items[numberOfItems - 1].
	// 4. If the root has subtrees, then children[0] through
	// children[numberOfChildren - 1] are references to these subtrees.
	protected int minNumberOfItems;
	protected int maxNumberOfItems;
	protected Object[] items;
	protected int numberOfItems;
	protected int numberOfChildren;
	protected Object[] children;

	protected Comparator<T> comparator;

	/**
	 * Initialize an empty balanced tree with the default minimum number of items
	 * per node.
	 * <p>
	 * <b>Postcondition:</b>
	 * <ul>
	 * <li>The tree is empty.</li>
	 * </ul>
	 * 
	 * @throws OutOfMemoryError
	 *             Indicates insufficient memory for creating the tree.
	 */
	public BalancedTree() {
		this(DEFAULT_MINIMUM_NUMBER_OF_ITEMS, null);
	}

	/**
	 * Initialize an empty balanced tree with the specified minimum number of items
	 * per node.
	 * <p>
	 * <b>Precondition:</b>
	 * <ul>
	 * <li><code>minimumNumberOfItems</code> must be &gt;= 1.</li>
	 * </ul>
	 * <p>
	 * <b>Postcondition:</b>
	 * <ul>
	 * <li>The tree is empty.</li>
	 * <li>The minimum number of items per node is set to the specified
	 * value.</li>
	 * </ul>
	 * 
	 * @param minimumNumberOfItems
	 *            The minimum number of items in each node.
	 * @throws OutOfMemoryError
	 *             Indicates insufficient memory for creating the tree.
	 */
	public BalancedTree(int minimumNumberOfItems) {
		this(minimumNumberOfItems, null);
	}

	/**
	 * Initialize an empty balanced tree with the specified minimum number of items
	 * per node and using the specified Comparator&lt;T&gt; to compare items.
	 * <p>
	 * <b>Precondition:</b>
	 * <ul>
	 * <li><code>minimumNumberOfItems</code> must be &gt;= 1.</li>
	 * </ul>
	 * <p>
	 * <b>Postcondition:</b>
	 * <ul>
	 * <li>The tree is empty.</li>
	 * <li>The minimum number of items per node is set to the specified
	 * value.</li>
	 * <li>The specified Comparator&lt;T&gt; will be used for comparing items.</li>
	 * </ul>
	 * 
	 * @param minimumNumberOfItems
	 *            The minimum number of items in each node.
	 * @param comparator
	 *            The Comparator&lt;T&gt; to use for comparing items.
	 * @throws OutOfMemoryError
	 *             Indicates insufficient memory for creating the tree.
	 */
	public BalancedTree(int minimumNumberOfItems, Comparator<T> comparator) {
		if (minimumNumberOfItems < 1) {
			throw new IllegalArgumentException(
					"BalancedTree(int minimumNumberOfItems): minimumNumberOfItems must be positive.");
		}

		minNumberOfItems = minimumNumberOfItems;
		maxNumberOfItems = minNumberOfItems * 2;

		numberOfItems = 0;
		numberOfChildren = 0;

		items = new Object[maxNumberOfItems + 1]; // Allow space for one extra node to support lazy add and remove.
		children = new Object[maxNumberOfItems + 2]; // A node with n items has n + 1 children.
		this.comparator = comparator;
	}

	/**
	 * Adds a new item to this B-tree.
	 * 
	 * @param item
	 *            The new item that is being added to this B-tree. If a
	 *            Comparator&lt;T&gt; was not specified, then item cannot be null.
	 * @return True if the new item was added to this B-tree; otherwise false.
	 * 
	 * @throws NullPointerException
	 *             Indicates that <code>item</code> is null and no
	 *             Comparator&lt;T&gt; was specified.
	 * @throws OutOfMemoryError
	 *             Indicates insufficient memory for adding a new item.
	 */
	public boolean add(T item) {
		boolean answer = true;

		if (comparator == null && item == null) {
			throw new NullPointerException("The item cannot be null when a Comparator<T> has not been set.");
		}

		answer = looseAdd(item);

		if (numberOfItems > maxNumberOfItems) {
			// Re-balance the root!
			rebalanceRoot();
		}

		return answer;
	}

	protected void rebalanceRoot() {
		BalancedTree<T> child = new BalancedTree<>(minNumberOfItems, comparator);

		child.items = items;
		child.numberOfItems = numberOfItems;
		child.children = children;
		child.numberOfChildren = numberOfChildren;

		items = new Object[maxNumberOfItems + 1];
		numberOfItems = 0;
		children = new Object[maxNumberOfItems + 2];
		numberOfChildren = 0;

		insertChild(0, child);

		fixExcess(0);
	}
	
	/**
	 * Creates a copy of this B-tree.
	 * 
	 * @return A copy of this B-tree. Subsequent changes to the copy will not affect
	 *         the original, nor vice versa.
	 */
	@SuppressWarnings("unchecked")
	public BalancedTree<T> clone() {
		// Clone a BalancedTree<T> object
		BalancedTree<T> answer;

		try {
			answer = (BalancedTree<T>) super.clone();
		} catch (CloneNotSupportedException exception) {
			// This exception should not occur. But if it does, it would indicate a
			// programming
			// error that made super.clone unavailable. The most common cause would be
			// forgetting the "implements Cloneable" clause at the start of the class.
			throw new RuntimeException("BalancedTree<T>.clone(): This class does not implement Cloneable.");
		}

		// Deep-copy the arrays.
		answer.items = items.clone();
		answer.children = children.clone();

		return answer;
	}

	private int compareT(T a, T b) {
		int answer = -1;

		if (comparator == null) {
			answer = a.compareTo(b);
		} else {
			answer = comparator.compare(a, b);
		}

		return answer;
	}

	/**
	 * Determine whether a particular item is in this B-tree.
	 * 
	 * @param target
	 *            An item that may or may not be in this B-tree. If a
	 *            Comparator&lt;T&gt; was not specified, then <code>target</code>
	 *            cannot be null.
	 * @return <code>true</code> if this B-tree contains <code>target</code>;
	 *         otherwise <code>false</code>.
	 * @throws IllegalArgumentException
	 *             Indicates <code>target</code> is null and no Comparator&lt;T&gt;
	 *             was specified.
	 * 
	 */
	public boolean contains(T target) {
		boolean answer = false;

		if (comparator == null && target == null) {
			throw new IllegalArgumentException("When using natural ordering, target cannot be null.");
		}

		answer = internalContains(target);

		return answer;
	}

	// Precondition: 0 <= removeIndex < numberOfChildren.
	// Postcondition: The item at children[removeIndex] has been removed and
	// subsequent items shifted over to close the gap. Also, numberOfChildren has
	// been decremented by one, and the return value is a copy of the
	// removed item.
	@SuppressWarnings("unchecked")
	private BalancedTree<T> deleteChild(int removeIndex) {
		BalancedTree<T> answer = (BalancedTree<T>) children[removeIndex];
		
		if (removeIndex == --numberOfChildren) {
			children[removeIndex] = null;
		} else {
			for (int i = removeIndex; i < numberOfChildren; i++) {
				children[i] = children[i + 1];
			}
			
			children[numberOfChildren] = null;
		}
		
		return answer;
	}

	// Precondition: 0 <= removeIndex < numberOfItems.
	// Postcondition: The item at items[removeIndex] has been removed and
	// subsequent items shifted over to close the gap. Also, numberOfItems has
	// been decremented by one, and the return value is a copy of the
	// removed item.
	@SuppressWarnings("unchecked")
	private T deleteItem(int removeIndex) {
		T answer = (T) items[removeIndex];
		numberOfItems--;
		
		// Shift all of the items down to the right of insertIndex
		for (int i = removeIndex; i + 1 <= numberOfItems; i++) {
			items[i] = items[i + 1];
		}
		
		items[numberOfItems] = null;
		
		return answer;
	}

	// Postcondition: The return value, x = int[0], is the first location in the
	// root
	// such that items[x] >= target. If there is no such location, then x is
	// numberOfItems. The return value, y = int[1], is the result of the compare
	// operation in terms of target; where y > 0 means items[x] is greater than
	// target,
	// where y == 0 means items[x] equals target, and where y < 0 means that
	// items[x]
	// is less than target.
	@SuppressWarnings("unchecked")
	private int[] firstGreaterThanOrEqualTo(T target) {
		int targetIndex = numberOfItems;
		int compareResult = -1;
		final int THRESHOLD = 3;

		if (numberOfItems < THRESHOLD) {
			for (int i = 0; i < numberOfItems; i++) {
				compareResult = compareT((T) items[i], target);
	
				if (compareResult >= 0) {
					targetIndex = i;
					break;
				}
			}
		} else {
			int left = 0, right = numberOfItems - 1;
			
			while (left <= right) {
				int mid = left + (right - left) / 2;
				compareResult = compareT((T) items[mid], target);

				if (compareResult == 0) {
					targetIndex = mid;
					break;
				} else if (compareResult < 0) {
					left = mid + 1;
				} else {
					targetIndex = mid; // We can't break yet.
					right = mid - 1;
				}
			}
		}

		return new int[] { targetIndex, compareResult };
	}

	// Precondition:
	// (i < numberOfChildren) and the entire B-tree is valid EXCEPT that
	// children[i] has maxNumberOfItems + 1 entries. Also, the root is allowed to
	// have
	// zero entries and one child.
	// Postcondition:
	// The tree has been rearranged so that the entire B-tree is valid EXCEPT
	// that the number of entries in the root of this B-tree might be one more than
	// the allowed maximum.
	@SuppressWarnings("unchecked")
	protected void fixExcess(int index) {
		if (index >= numberOfChildren) {
			throw new ArrayIndexOutOfBoundsException("index must be less than numberOfChildren.");
		}

		BalancedTree<T> child = ((BalancedTree<T>) children[index]);

		if (child.numberOfItems != child.maxNumberOfItems + 1) {
			throw new IllegalStateException("The child at index does not contain maxNumberOfItems + 1 items.");
		}

		BalancedTree<T> right = splitChild(child, index);

		// Add the new node as a child to the right of the one we just fixed.
		insertChild(index + 1, right);
	}

	// Precondition:
	// (i < numberOfChildren) and the entire B-tree is valid EXCEPT that
	// children[i] has only minNumberOfItems - 1 entries.
	// Postcondition:
	// The tree has been rearranged so that the entire B-tree is valid EXCEPT
	// that the number of entries in the root of this B-tree might be one less than
	// the allowed minimum.
	@SuppressWarnings("unchecked")
	private void fixShortage(int index)
	{
		if (index >= numberOfChildren) {
			throw new ArrayIndexOutOfBoundsException("index must be less than numberOfChildren.");
		}
		
		BalancedTree<T> child = (BalancedTree<T>) children[index];

		if (child.numberOfItems != child.minNumberOfItems - 1) {
			throw new IllegalStateException("The child at index does not contain minNumberOfItems - 1 items.");
		}
		
		// There are four cases to consider to fixing the shortage
		// Case 1:
		//    If children[index - 1] has more than the minimum number of items,
		//    then we can transfer an extra element from children[index - 1] to
		//    the front of children[index].
		// Case 2:
		//    Else if children[index + 1] has more than the minimum number of items,
		//    then we can transfer an extra element from children[index + 1] to
		//    the back of children[index].
		// Case 3:
		//    Else if children[index - 1] has exactly the minimum number of items,
		//    then we can combine it with children[index].
		// Case 4:
		//    Else we combine children[index + 1] with children[index].
		int leftSibling = index - 1;
		BalancedTree<T> left = (leftSibling >= 0) ? (BalancedTree<T>)children[leftSibling] : null;
		int rightSibling = index + 1;
		BalancedTree<T> right = (rightSibling >= 0) ? (BalancedTree<T>)children[rightSibling] : null;
		
		if (left != null && left.numberOfItems > left.minNumberOfItems) {
			transferRight(leftSibling);
		} else if (right != null && right.numberOfItems > right.minNumberOfItems) {
			transferLeft(rightSibling);
		} else if (left != null && left.numberOfItems == left.minNumberOfItems) {
			mergeWithNextChild(leftSibling);
		} else if (right != null) {
			mergeWithNextChild(index);
		}
	}

	/**
	 * The maximum number of items that a node may contain.
	 * <p>
	 * <b>Note:</b>
	 * <ul>
	 * <li>This is equal to twice the value of getMinNumberOfItems().</li>
	 * </ul>
	 * 
	 * @return The maximum number of items per node.
	 */
	public int getMaxNumberOfItems() {
		return maxNumberOfItems;
	}

	/**
	 * The minimum number of items that a node, except for the root, contains.
	 * 
	 * @return The minimum number of items per node.
	 */
	public int getMinNumberOfItems() {
		return minNumberOfItems;
	}

	// PRIVATE HELPER METHODS
	// The helper methods are below with precondition/postcondition contracts.

	/**
	 * The number of direct children for this node.
	 * 
	 * @return The number of direct children for this node.
	 */
	public int getNumberOfChildren() {
		return numberOfChildren;
	}

	/**
	 * The actual number of items stored in this node.
	 * 
	 * @return The actual number of items stored in this node.
	 */
	public int getNumberOfItems() {
		return numberOfItems;
	}

	// Precondition: 0 <= insertIndex <= numberOfChildren <= maxNumberOfItems + 1.
	// Postcondition: The B-tree has been inserted at children[insertIndex] with
	// subsequent items shifted right to make room. Also, numberOfChildren has
	// been incremented by one.
	protected void insertChild(int insertIndex, BalancedTree<T> tree)
	{
		if (!(0 <= insertIndex && insertIndex <= numberOfChildren && numberOfChildren <= maxNumberOfItems + 1)) {
			throw new ArrayIndexOutOfBoundsException("insertIndex: " + insertIndex);
		}

		if (numberOfChildren > 0) {
			// Shift all of the items to the right of insertIndex
			for (int i = numberOfChildren; i > insertIndex; i--) {
				children[i] = children[i - 1];
			}
		}

		children[insertIndex] = tree;
		numberOfChildren++;
	}

	// Precondition: 0 <= insertIndex <= numberOfItems <= maxNumberOfItems.
	protected void insertItem(int insertIndex, T entry) {
		if (!(0 <= insertIndex && insertIndex <= numberOfItems && numberOfItems <= maxNumberOfItems)) {
			throw new ArrayIndexOutOfBoundsException("insertIndex: " + insertIndex);
		}

		if (numberOfItems > 0) {
			// Shift all of the items to the right of insertIndex
			for (int i = numberOfItems; i > insertIndex; i--) {
				items[i] = items[i - 1];
			}
		}

		items[insertIndex] = entry;
		numberOfItems++;
	}

	@SuppressWarnings("unchecked")
	private boolean internalContains(T target) {
		boolean answer = false;
		int[] results = firstGreaterThanOrEqualTo(target);
		int targetIndex = results[0];
		int compareResults = results[1];

		if (targetIndex < numberOfItems && compareResults == 0) {
			answer = true;
		} else if (numberOfChildren > 0 && targetIndex < numberOfChildren) {
			answer = ((BalancedTree<T>) children[targetIndex]).internalContains(target);
		}

		return answer;
	}

	// Return value is true if and only if the B-tree has only a root.
	protected boolean isLeaf() {
		return (numberOfChildren == 0);
	}

	// Precondition:
	// The entire B-tree is valid.
	// Postcondition:
	// If entry was already in the tree, it is added again and the entire
	// B-tree is still valid EXCEPT that the number of entries in the
	// root of this B-tree might be one more than the allowed maximum.
	protected boolean looseAdd(T entry) {
		boolean answer = true;
		int[] results = firstGreaterThanOrEqualTo(entry);
		int targetIndex = results[0];
		int compareResults = results[1];

		answer = looseAdd(targetIndex, compareResults, entry);
		
		return answer;
	}

	@SuppressWarnings("unchecked")
	protected boolean looseAdd(int targetIndex, int compareResults, T entry) {
		boolean answer = true;
		
		if (isLeaf() == true) {
			insertItem(targetIndex, entry);
		} else if (targetIndex < numberOfChildren) {
			BalancedTree<T> child = ((BalancedTree<T>) children[targetIndex]);
			answer = child.looseAdd(entry);

			if (child.getNumberOfItems() > child.getMaxNumberOfItems()) {
				fixExcess(targetIndex);
			}
		}
		
		return answer;
	}

	// Precondition:
	// The entire B-tree is valid.
	// Postcondition:
	// If target was in the B-tree, then it has been removed from the B-tree and the
	// method returns true; otherwise the B-tree is unchanged and the method
	// returns false. The entire B-tree is still valid EXCEPT that the
	// number of entries in the root of this B-tree might be one less than the
	// allowed minimum.
	@SuppressWarnings("unchecked")
	private boolean looseRemove(T target) {
		boolean answer = false;
		int[] results = firstGreaterThanOrEqualTo(target);
		int targetIndex = results[0];
		int compareResults = results[1];

		if (isLeaf()) {
			if (compareResults == 0) {
				deleteItem(targetIndex);
				answer = true;
			}
		} else {
			BalancedTree<T> child = ((BalancedTree<T>) children[targetIndex]);
			
			if (compareResults == 0) {
				items[targetIndex] = child.removeBiggest();
				
				answer = true;
			} else {				
				if (targetIndex < numberOfChildren) {
					answer = child.looseRemove(target);
				}
			}
			
			if (child.numberOfItems < child.minNumberOfItems) {
				fixShortage(targetIndex);
			}
		}
		
		return answer;
	}

	// Precondition:
	// (i + 1 < numberOfChildren) and the entire B-tree is valid EXCEPT that the total
	// number of entries in children[i] and children[i + 1] is 2 * minNumberOfItems - 1.
	// Postcondition:
	// children[i] and children[i + 1] have been merged into one child (now at
	// children[i]), and items[i] has been passed down to be the median entry of the
	// new children[i]. As a result, the entire B-tree is valid EXCEPT that the
	// number of entries in the root of this B-tree might be one less than the
	// allowed minimum.
	@SuppressWarnings("unchecked")
	private void mergeWithNextChild(int index) {
		BalancedTree<T> merge = deleteChild(index + 1);
		BalancedTree<T> child = (BalancedTree<T>) children[index];
		child.insertItem(child.numberOfItems, deleteItem(index));
		
		for (int i = 0; i < merge.numberOfItems; i++) {
			child.insertItem(child.numberOfItems, (T) merge.items[i]);
		}
		
		for (int i = 0; i < merge.numberOfChildren; i++) {
			child.insertChild(child.numberOfChildren, (BalancedTree<T>) merge.children[i]);
		}
	}

	// Precondition:
	// child must have count number of items to move from start.
	// Postcondition:
	// count number of items in child, starting from start, have been
	// moved to right, including half the children of child.
	protected void moveRightHalfOfChild(BalancedTree<T> child, BalancedTree<T> right, int start, int count) {
		System.arraycopy(child.items, start, right.items, 0, count);

		right.numberOfItems = right.minNumberOfItems;

		for (int k = count; k <= child.maxNumberOfItems; k++) {
			child.items[k] = null;
		}

		child.numberOfItems = child.minNumberOfItems;
		
		int numChildren = child.numberOfChildren / 2;

		if (numChildren > 0) {
			if (child.numberOfChildren % 2 == 0) {
				System.arraycopy(child.children, numChildren, right.children, 0, numChildren);
				for (int k = numChildren; k <= child.maxNumberOfItems + 1; k++) {
					child.children[k] = null;
				}
			} else {
				numChildren++;
				System.arraycopy(child.children, numChildren - 1, right.items, 0, numChildren);
				for (int k = numChildren - 1; k <= child.maxNumberOfItems + 1; k++) {
					child.children[k] = null;
				}
			}
			
			right.numberOfChildren = numChildren;
			child.numberOfChildren -= numChildren;
		}
	}

	/**
	 * Prints a pre-order representation of the B-tree; useful during debugging.
	 * 
	 * @param indent
	 *            The number of spaces to indent to print this node. Start with 0
	 *            when printing from the root.
	 */
	@SuppressWarnings("unchecked")
	public void print(int indent) {
		final int EXTRA_INDENTATION = 4;
		int i;
		int space;

		// Print the indentation and the items from this node
		for (space = 0; space < indent; space++) {
			System.out.print(" ");
		}
		for (i = 0; i < numberOfItems; i++) {
			System.out.print(items[i] + " ");
		}

		System.out.println();

		// Print the subtrees
		for (i = 0; i < numberOfChildren; i++) {
			((BalancedTree<T>) children[i]).print(indent + EXTRA_INDENTATION);
		}
	}

	/**
	 * Prints an in-order representation of the B-tree; useful during debugging.
	 * 
	 */
	@SuppressWarnings("unchecked")
	public void inorderPrint() {
		int i;
		
		for (i = 0; i < numberOfItems; i++) {
			if (i < numberOfChildren) {
				// Print the subtrees
				((BalancedTree<T>) children[i]).inorderPrint();
				System.out.println();
			}
			
			System.out.print(items[i] + " ");
		}

		if (i < numberOfChildren) {
			((BalancedTree<T>) children[i]).inorderPrint();
		}
	}

	/**
	 * Remove a specified item from this B-tree.
	 * 
	 * @param target
	 *            The item to remove from this B-tree.
	 * @return If <code>target</code> was found in this B-tree, then it has been
	 *         removed and the method returns <code>true</code>; otherwise this
	 *         B-tree remains unchanged and the method returns <code>false</code>.
	 */
	@SuppressWarnings("unchecked")
	public boolean remove(T target) {
		boolean answer = looseRemove(target);

		if (numberOfItems == 0 && numberOfChildren == 1) {
			// Shorten the B-tree one-level!
			BalancedTree<T> child = (BalancedTree<T>) children[0];
			
			numberOfItems = child.numberOfItems;
			numberOfChildren = child.numberOfChildren;
			items = child.items;
			children = child.children;
		}
		
		return answer;
	}

	// Precondition:
	// (numberOfItems > 0) and the entire B-tree is valid.
	// Postcondition:
	// The largest item in the B-tree has been removed, and the value of this
	// item is the return value. The B-tree is still valid EXCEPT
	// that the number of entries in the root of this B-tree might be one less than
	// the allowed minimum.
	@SuppressWarnings("unchecked")
	private T removeBiggest() {
		T answer = null;
		
		if (isLeaf()) {
			answer = (T) items[--numberOfItems];
			items[numberOfItems] = null;
		} else {
			int index = numberOfChildren - 1;
			BalancedTree<T> child = (BalancedTree<T>)children[index]; 
			answer = child.removeBiggest();
			
			if (child.numberOfItems < child.minNumberOfItems) {
				fixShortage(index);
			}
		}
		return answer;
	}

	// Postcondition:
	// The right half of the items and children from child have been moved to a
	// new B-tree. The middle item from child has been moved in to the
	// root of this node.
	// The tree has been rearranged so that the entire B-tree is valid EXCEPT
	// that the number of entries in the root of this B-tree might be one more than
	// the allowed maximum.
	// @returns A new B-tree that contains the right-half of child.
	@SuppressWarnings("unchecked")
	protected BalancedTree<T> splitChild(BalancedTree<T> child, int index) {
		BalancedTree<T> right = new BalancedTree<>(minNumberOfItems, comparator);

		int itemMidpoint = child.numberOfItems / 2;
		T midpoint = (T) child.items[itemMidpoint];
		child.items[itemMidpoint] = null;
		
		// move the items to the node.
		moveRightHalfOfChild(child, right, itemMidpoint + 1, itemMidpoint);

		// Pass the middle child up to the root in the correct spot.
		insertItem(index, midpoint);

		return right;
	}

	// Precondition:
	// (0 < i < numberOfChildren) and (children[i]->numberOfItems >
	// minNumberOfItems)
	// and the entire B-tree is valid EXCEPT that
	// children[i-1] has only minNumberOfItems - 1 entries.
	// Postcondition:
	// One entry has been shifted from the front of children[i] up to
	// items[i-1], and the original items[i-1] has been shifted down to the last
	// entry of children[i-1]. Also, if children[i] is not a leaf, then its first
	// child has been transfered over to be the last child of children[i-1].
	// As a result, the entire B-tree is now valid.
	@SuppressWarnings("unchecked")
	private void transferLeft(int index) {
		BalancedTree<T> left = (BalancedTree<T>) children[index - 1];
		BalancedTree<T> right = (BalancedTree<T>) children[index];
		T parentItem = (T) items[index - 1];
		items[index - 1] = right.deleteItem(0);
		left.insertItem(left.numberOfItems, parentItem);
		
		if (right.numberOfChildren > 0) {
			left.insertChild(left.numberOfChildren, right.deleteChild(0));
		}
	}

	// Precondition:
	// (i + 1 < numberOfChildren) and (children[i]->numberOfItems >
	// minNumberOfItems)
	// and the entire B-tree is valid EXCEPT that
	// children[i] has only minNumberOfItems - 1 entries.
	// Postcondition: One entry has been shifted from the end of children[i] up to
	// items[i], and the original items[i] has been shifted down to the first entry
	// of children[i+1]. Also, if children[i] is not a leaf, then its last child has
	// been transfered over to be the first child of children[i+1].
	// As a result, the entire B-tree is now valid.
	@SuppressWarnings("unchecked")
	private void transferRight(int index) {
		BalancedTree<T> left = (BalancedTree<T>) children[index];
		BalancedTree<T> right = (BalancedTree<T>) children[index + 1];
		T parentItem = (T) items[index];
		items[index] = left.deleteItem(left.numberOfItems - 1);
		right.insertItem(0, parentItem);
		
		if (left.numberOfChildren > 0) {
			right.insertChild(0, left.deleteChild(left.numberOfChildren - 1));
		}
	}
}
