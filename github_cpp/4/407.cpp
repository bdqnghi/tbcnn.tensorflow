#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

const int HASH_SIZE = 23;

struct hash_node
{
	int key;
	struct hash_node *next;
};

void initialization(struct hash_node*);
void pointer_array(struct hash_node *[], struct hash_node*);
int hash_function(int);
void input(int, struct hash_node*, struct hash_node *[]);
void output(struct hash_node*, struct hash_node *[]);
void max_key(struct hash_node*, int&, struct hash_node *[]);

void main(void)
{
	srand(time(NULL));
	int users, max = -1;
	struct hash_node *pointer[HASH_SIZE]; //pointer array
	struct hash_node hash_table[HASH_SIZE]; //structure array
	initialization(hash_table); 
	printf("The array is initialized!\n\n");
	pointer_array(pointer, hash_table); //creating pointer array, but we can do without it
	printf("The array out of pointers is made!\n\n");
	printf("Enter the number of elements you want to enter(no more than 23): ");
	while (scanf("%d", &users) != 1 || users > HASH_SIZE)
	{
		printf("Wrong format! Try again!\n\n");
		while (getchar() != '\n');
	}
	input(users, hash_table, pointer);
	printf("\nThe hash_table was made!\n\n");
	output(hash_table, pointer);
	max_key(hash_table, max, pointer);
	printf("\nThe maximum key is %d", max);
	_getch();
	return;
}

void initialization(struct hash_node hash_table [])
{
	for (int i = 0; i < HASH_SIZE; ++i)
	{
		hash_table[i].key = 0;
		hash_table[i].next = NULL;
	}
	return;
}

void pointer_array(struct hash_node *pointer[], struct hash_node hash_table[])
{
	for (int i = 0; i < HASH_SIZE; ++i)
	{
		pointer[i] = &hash_table[i];
	}
	return;
}

int hash_function(int tmp)
{
	return tmp % HASH_SIZE;
}

void input(int users, struct hash_node hash_table[], struct hash_node *pointer[])
{
	for (int i = 0; i < users; ++i)
	{
		int tmp = rand() % 100;
		int hash = hash_function(tmp);
		if (hash_table[hash].key == 0)
		{
			hash_table[hash].key = tmp;
		}
		else
		{
			struct hash_node *current, *mem;
			current = pointer[hash];
			while (current->next != NULL)
			{
				current = current->next;
			}
			mem = (struct hash_node*)malloc(sizeof(struct hash_node));
			mem->key = tmp;
			mem->next = NULL;
			current->next = mem;
		}
	}
	return;
}

void output(struct hash_node hash_table[], struct hash_node *pointer[])
{
	struct hash_node *tmp;
	for (int i = HASH_SIZE - 1; i >= 0; --i)
	{
		printf("%d  ", hash_table[i].key);
		tmp = pointer[i];
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
			printf("%d  ", tmp->key);
		}
		printf("\n");
	}
	return;
}

void max_key(struct hash_node hash_table[], int &max, struct hash_node *pointer[])
{
	struct hash_node *tmp;
	for (int i = HASH_SIZE - 1; i >= 0; --i)
	{
		if (max <= hash_table[i].key)
		{
			max = hash_table[i].key;
		}
		if (hash_table[i].next != NULL)
		{
			for (tmp = hash_table[i].next; tmp != NULL; tmp = tmp->next)
			{
				if (max <= tmp->key)
				{
					max = tmp->key;
				}
			}
		}
	}
	return;
}