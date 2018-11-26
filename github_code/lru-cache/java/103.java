/**
 * HashMap+˫������ʵ��LRU����
 * http://www.lintcode.com/zh-cn/problem/lru-cache/
 * https://leetcode.com/problems/lru-cache/#/description
 * @author yzwall
 */
package datastructure;

import java.util.HashMap;

class Solution {
	private HashMap<Integer, CacheNode> map;
	private int capacity;
	// head.next��tail.nextָ������ͷβ����������ֹnull
	private CacheNode head = new CacheNode(-1, -1);
	private CacheNode tail = new CacheNode(-1, -1);
	
	private class CacheNode {
		int key, value;
		CacheNode pre, next;
		CacheNode(int key, int value) {
			this.key = key;
			this.value = value;
			this.pre = null;
			this.next = null;
		}
	}
	
	public Solution(int capacity) {
		this.map = new HashMap<>();
		this.capacity = capacity;
	}
	
	// �����нڵ���½��ڵ��ƶ�������β��
	private void moveToTail(CacheNode target, boolean isNew) {
		// β���ڵ���Ȼ����Ҫ�ƶ�
		if (target != tail.next) {
			if (!isNew) {
				// �޸ľɽڵ��˫������ָ��
			    target.pre.next = target.next; 
				target.next.pre = target.pre;
			}
			// ��ӽڵ㵽����β��
			tail.next.next = target;
			target.pre = tail.next;
			tail.next = target;
		}
	}
	
	// ���нڵ���ӵ�����β����δ���з���-1
	public int get(int key) {
		if (map.containsKey(key)) {
			CacheNode target = map.get(key);
			// �����нڵ��ƶ�������β��
			moveToTail(target, false);
			// ��ʱ����β��tail.next = target������nextָ��null����ֹ���ֻ�
			tail.next.next = null;
			return target.value;
		}
		return -1;
	}
	
	/**
	 * 1. �ڵ����У��޸Ľڵ㲢�ƶ�������β��tail.next
	 * 2. �ڵ�δ���У�
	 *    2.1 cache������ɾ������ͷ��head.next
	 *    2.2 cacheδ�����½��ڵ㲢��ӵ�����β��tail.next
	 */
	public void set(int key, int value) {
		// cache�д��ڽڵ�
		if (map.containsKey(key)) {
			CacheNode target = map.get(key);
			target.value = value;
			map.put(key, target);
			// �����ʹ������нڵ��ƶ�������β��
			moveToTail(target, false);
		} else if(map.size() < capacity) {	// cacheδ������ӽڵ�
			CacheNode newNode = new CacheNode(key, value);
			map.put(key, newNode);
			if (head.next == null) {
				head.next = newNode;
				newNode.pre = head;
				tail.next = newNode;
			} else {
				// ���½��ڵ��ƶ�������β��
				moveToTail(newNode, true);
			}
		} else {	// cache��������̭��������ͷ���ڵ㣬�½ڵ���뵽����β��
			CacheNode newNode = new CacheNode(key, value);
			map.remove(head.next.key);
			map.put(key, newNode);
			// cache��ֻ��һ��Ԫ��
			if (head.next == tail.next) {
				head.next = newNode;
				tail.next = newNode;
			} else {	// cache�в�ֹһ��Ԫ�أ�ɾ��ͷ��
			    head.next.next.pre = head; // ������ͷ��.pre = head
				head.next = head.next.next;// ������ͷ��
				// ���½��ڵ��ƶ�������β��
				moveToTail(newNode, true);
			}
		}
	}
}

public class LruCache_134 {
	public static void main(String[] args) {
		Solution ss = new Solution(1);
		ss.set(2, 1);
		System.out.println(ss.get(2));
		ss.set(3, 2);
		System.out.println(ss.get(2));
		System.out.println(ss.get(3)); 
	}
}
