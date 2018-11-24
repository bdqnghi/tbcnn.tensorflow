#include "SkipList.h"

/*
�����ڵ�
*/
Node* create_node(int level, keyType key, valueType val)
{
	Node *p = (Node*)malloc(sizeof(Node) + level*sizeof(Node*));
	if (!p)
	{
		printf("Fail to Create node!\n");
		return NULL;
	}
	p->key = key;
	p->value = val;

	return p;
}

//����skiplist
skip_list* create_sl()
{
	skip_list *sl = (skip_list*)malloc(sizeof(skip_list));
	if (sl == NULL)
	{
		printf("Fail to create skip list!\n");
		return NULL;
	}

	sl->level = 0;		//��ʼ�Ĳ���Ϊ0
	Node *head = create_node(SKIPLIST_MAXLEVEL - 1, 0, 0);
	if (head == NULL)
	{
		printf("Fail to create skip list!\n");
		return NULL;
	}
	sl->head = head;
	for (int i = 0; i < SKIPLIST_MAXLEVEL; ++i)
	{
		head->next[i] = NULL;
	}
	srand(time(0));
	
	return sl;
}

//��������Ĳ���
int randomLevel()
{
	int level = 1;
	while (rand() % 2)
	{
		level++;
		if (level > SKIPLIST_MAXLEVEL)
			break;
	}

	level = (level > SKIPLIST_MAXLEVEL) ? SKIPLIST_MAXLEVEL : level;

	return level;
}

//����ڵ�
int insert(skip_list* sl, keyType key, valueType val)
{
	Node *update[SKIPLIST_MAXLEVEL];		//��Ҫ���µĽڵ�
	Node *q = NULL;							
	Node *p = sl->head;
	int i = sl->level - 1;

	//1������߲����²�����Ҫ�����λ�ã�������update
	//���ѽ���ڵ�ָ�뱣����update����
	for (; i >= 0; --i)
	{
		while ((q = p->next[i])&&(q->key < key))
		{
			p = q;
		} 
		update[i] = p;
	}
	if (q && q->key == key)		//����Ѿ�������
	{
		q->value = val;
		return 1;
	}
	//2�����������level
	int level = randomLevel();
	//�µĲ���������Ĳ�����
	if (level > sl->level)
	{
		for (i = sl->level; i < level; ++i)
		{
			update[i] = sl->head;		//����ڵ�Ҫ����ͷ���ĺ���
		}
		sl->level = level;
	}

	//3���½��ڵ�
	q = create_node(level, key, val);
	if (!q)
		return 0;
	for (i = level - 1; i >= 0; --i)
	{
		q->next[i] = update[i]->next[i];
		update[i]->next[i] = q;
	}

	return 1;
}

//ɾ���ڵ�
int erase(skip_list* sl, keyType key)
{
	Node *update[SKIPLIST_MAXLEVEL];
	Node *q = NULL;
	Node *p = sl->head;
	int i = sl->level - 1;

	for (; i >= 0; --i)
	{
		while ((q = p->next[i]) && (q->key < key))
		{
			p = q;
		}
		update[i] = p;
	}

	//�ж�
	if (!q || (q && q->key != key))
		return 0;
	//���ɾ��
	for (i = sl->level - 1; i >= 0; --i)
	{
		if (update[i]->next[i] == q)		//ɾ���ڵ�
		{
			update[i]->next[i] = q->next[i];
			//���ɾ��������߲�Ľڵ�,��level��1
			if (sl->head->next[i] == NULL)
				sl->level--;
		}
	}
	free(q);
	q = NULL;
	
	return 1;
}

//����
valueType* search(skip_list* sl, keyType key)
{
	Node *q = NULL;
	Node *p = sl->head;
	int i = sl->level - 1;

	for (; i >= 0; --i)
	{
		while ((q = p->next[i]) && (q->key < key))
		{
			p = q;
		}
		if (q && key == q->key)
			return &(q->value);
	}

	return NULL;
}

//��ӡ
void print_sl(skip_list *sl)
{
	Node *q;
	int i = sl->level - 1;
	for (; i >= 0; --i)
	{
		q = sl->head->next[i];
		printf("level %d:\n", i + 1);
		while (q)
		{
			printf("key:%d val:%d\t", q->key, q->value);
			q = q->next[i];
		}

		printf("\n");
	}
}

//�ͷ�
void free_sl(skip_list* sl)
{
	if (!sl)
		return;
	Node *q = sl->head;
	Node *next;
	while (q)
	{
		next = q->next[0];
		free(q);
		q = next;
	}
	free(sl);
}