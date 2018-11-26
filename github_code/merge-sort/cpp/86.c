#include <iostream>

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
public:
	ListNode* CreatNode(int value)
	{
		ListNode* tmp = new ListNode(0);
		tmp->val = value;
		tmp->next = NULL;
		return tmp;
	}
	ListNode* ConnectNodeToList(ListNode* node_current, ListNode* node_next)
	{
		node_current->next = node_next;
		return node_current;
	}
	ListNode *mergeRecursion(ListNode*l1, ListNode* l2)
	{
		ListNode *mergelsit=NULL;
		
		if (NULL == l1)
			return l2;
		else if(NULL==l2)
			return l1;
		if (l1->val < l2->val)
		{
			mergelsit = l1;
			mergelsit->next = mergeRecursion(l1->next,l2);
		}
		else
		{
			mergelsit = l2;
			mergelsit->next = mergeRecursion(l1, l2->next);
		}
		return mergelsit;
	}
	ListNode* mergeCalculation(ListNode* l1, ListNode* l2) {
		ListNode* mergeListHead;
		ListNode* mergeLsitTail;
		if (NULL == l1) return l2;
		if (NULL == l2) return l1;
		//确定头结点
		if (l1->val > l2->val)
		{
			mergeListHead = l2;
			l2 = l2->next;
		}
		else
		{
			mergeListHead = l1;
			l1 = l1->next;
		}
		mergeLsitTail = mergeListHead;
		while ((NULL != l1) && (NULL != l2))
		{

			if (l1->val > l2->val)
			{
				mergeLsitTail = l2;
				l2 = l2->next;
			}
			else
			{
				mergeLsitTail = l1;
				l1 = l1->next;
			}
			mergeLsitTail = mergeLsitTail->next;
		}
		if (NULL == l1)
			mergeLsitTail= l2;
		else if(NULL ==l2)
			mergeLsitTail = l1;
		return mergeListHead;
	}
	void PrintList(ListNode* list)
	{
		if (NULL == list) std::cout << "NULL" << std::endl;
		while (list != NULL)
		{
			std::cout << list->val<<"->";
			list = list->next;
		}
		std::cout << std::endl;
	}
	int DestoryList(ListNode* list)
	{
		ListNode *tmp=list;
		while (NULL != list)
		{
			list = list->next;
			delete tmp;
			tmp = list;
		}
		return 0;
	}

};
int main()
{
	Solution MergeSortList;
	ListNode* no1 = MergeSortList.CreatNode(1);
	ListNode* no3 = MergeSortList.CreatNode(3);
	ListNode* no5 = MergeSortList.CreatNode(5);
	ListNode* no2 = MergeSortList.CreatNode(2);
	ListNode* no4 = MergeSortList.CreatNode(4);
	ListNode* no6 = MergeSortList.CreatNode(6);
	MergeSortList.ConnectNodeToList(no1,no3);
	MergeSortList.ConnectNodeToList(no3, no5);
	MergeSortList.ConnectNodeToList(no2,no4);
	MergeSortList.ConnectNodeToList(no4,no6);
	ListNode* merge_list_calculate = MergeSortList.mergeCalculation(no1,no2);
	MergeSortList.PrintList(no1);
	MergeSortList.PrintList(no2);
	ListNode* merge_list = MergeSortList.mergeRecursion(no1,no2);
	MergeSortList.PrintList(merge_list_calculate);
	MergeSortList.PrintList(merge_list);
	MergeSortList.DestoryList(merge_list_calculate);
	//MergeSortList.DestoryList(merge_list);
}
