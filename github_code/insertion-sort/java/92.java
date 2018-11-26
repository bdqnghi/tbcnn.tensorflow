package leetcode.leetcodes;

import org.junit.Test;

/*
 * Sort a linked list using insertion sort.
 */
public class SortListInsertionSort {

	public ListNode insertionSortList(ListNode head) {		
	
		if (head == null)
			return null;
		if (head.next == null) {
			return head;
		}
		ListNode first = head;
		ListNode testNode = head;

		while (testNode.next != null) {
			ListNode insertNode = testNode.next;
			
			if (testNode.val <= insertNode.val) {
				testNode = testNode.next;
				continue;
			}
			
			if (insertNode.val <= first.val) {
				testNode.next = insertNode.next;
				insertNode.next = first;
				first = insertNode;
				continue;
			}

			for (ListNode pointer = first; pointer != testNode; pointer = pointer.next) {
				if (pointer.val <= insertNode.val
						&& insertNode.val <= pointer.next.val) {
					testNode.next = insertNode.next;
					insertNode.next = pointer.next;
					pointer.next = insertNode;
					break;
				}
			}
		}

		return first;
	}

	@Test
	public void test() {
		int[] testList = new int[] {4,19,14,5,-3,1,8,5,11,15};
		ListNode[] nodeList = new ListNode[testList.length];

		for (int i = 0; i < nodeList.length; i++) {
			nodeList[i] = new ListNode(testList[i]);
		}

		for (int i = 0; i < nodeList.length - 1; i++) {
			nodeList[i].next = nodeList[i + 1];
		}

		showList(nodeList[0]);
		showList(insertionSortList(nodeList[0]));
	}
	
	public void showList(ListNode head) {
		while (head != null) {
			System.out.print(" " + head.val);
			head = head.next;
		}
		System.out.println();
	}
	
	public int length(ListNode head) {
		int count = 0;
		while (head != null) {
			head = head.next;
			count++;
			if (count > 10) {
				break;
			}
		}

		return count;
	}

}
