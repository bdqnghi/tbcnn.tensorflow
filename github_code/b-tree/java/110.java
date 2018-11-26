package learn.common.handlers;

import static java.lang.System.out;

import java.util.Scanner;
import java.util.Vector;

import learn.common.Menu;
import learn.ds.linkedlist.DoublyLinkedList;
import learn.ds.tree.btree.BTreeNode;
import learn.ds.tree.btree.TraversalOrder;

public class TreeHandler implements IHandler {
	
	private Vector<String> menuData;
	private BTreeNode bTreeHead;
	private Scanner scanner;
	private Menu menu;

	public TreeHandler()
	{
		menuData = new Vector<String>();
		menuData.add("B-Tree: InOrder");
		menuData.add("B-Tree: PreOrder");
		menuData.add("B-Tree: PostOrder");
		menuData.add("B-Tree: LevelOrder");
		menuData.add("B-Tree: Search");
		menuData.add("B-Tree: Delete");
		menuData.add("B-Tree: Mirror");
		menuData.add("B-Tree: LeftView");
		menuData.add("B-Tree: Tree to DList");

		menu = new Menu(menuData, "Tree Menu", this);
	}

	@Override
	public Menu getMenu()
	{
		return menu;
	}
	
	@Override
	public IHandler handle(int index)
	{
		if (createBTree() <= 0)
		{
			out.println(">>>>>>>>>>>> Insufficient items to sort, try again... \n");
			return null;
		}

		switch (index)
		{
		case 0:
		{
			bTreeHead.printTree(TraversalOrder.TRAVERSE_IN_ORDER);
			break;
		}
		case 1:
		{
			bTreeHead.printTree(TraversalOrder.TRAVERSE_PRE_ORDER);
			break;
		}
		case 2:
		{
			bTreeHead.printTree(TraversalOrder.TRAVERSE_POST_ORDER);
			break;
		}
		case 3:
		{
			bTreeHead.printTree(TraversalOrder.TRAVERSE_LEVEL_ORDER);
			break;
		}
		case 4:
		{
			bTreeHead.search(readSingleInput("search"));
			break;
		}
		case 5:
		{
			bTreeHead.search(readSingleInput("delete"));
			break;
		}
		case 8:
		{
			binaryTreeToDoublyLinkedList();
			break;
		}
		}
		
		return null;
	}
	
	protected int createBTree()
	{
		int retVal = 0;
		bTreeHead = new BTreeNode();

		System.out.println(">>>>>>>>>>>> Lets create the tree, enter an arrya of space seperated int(s):");
		System.out.println(">>>>>>>>>>>> e.g. 1 2 3 4  \n");

		scanner = new Scanner(System.in);
		String strInput = scanner.nextLine().trim();
		
		for (String value : strInput.split(" ")) {
			if (!value.trim().isEmpty())
			{
				try {
					bTreeHead.addNode(value);
					retVal++;
				} catch (NumberFormatException e) {
					//err.println("\n SKIPING INVALID ITEMS: " + value);
				}
			}
		}

		return retVal;
	}

	protected Integer readSingleInput(String title)
	{
		Integer retVal = null;
		System.out.println(">>>>>>>>>>>> Enter the '" + title + "' string: \n");
		scanner = new Scanner(System.in);
		String strInput = scanner.nextLine().trim();
		
		try {
			retVal = new Integer(strInput);
		} catch (NumberFormatException e) {
			System.err.println("\n INVALID INPUT: try again \n");
		}
		
		return retVal;
	}

	private void binaryTreeToDoublyLinkedList() {
		DoublyLinkedList<Integer> list = new DoublyLinkedList<>();
		inOrder(bTreeHead, list);
		list.printList("Tree_to_List");
	}

	private void inOrder(BTreeNode treeNode, DoublyLinkedList<Integer> list)
	{
		if (treeNode != null)
		{
			inOrder(treeNode.getLeft(), list);
			list.addNode(treeNode.getData());
			inOrder(treeNode.getRight(), list);
		}
	}
}
