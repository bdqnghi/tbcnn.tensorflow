
#include "Linklist.h"

#define InitList(L)		InitStack(L)
#define DestroyList(L) 		DestroySatck(L)
#define ClearList(L) 		ClearStack(L)
#define ListEmpty(L) 		StackEmpty(L)
#define ListLength(L) 		SatckLength(L)
typedef struct
{
    ElemType 		data;
    struct LNode *	next;
} LNode, *LinkList;


typedef Linklist Stack;

Status GetTop(Stack S,ElemType &e){
	e = S->next->data;
	
	return True;
}

Status Push(Stack &S,ElemType e){
	Stack tmpNode = S;
	while(tmpNode->next){
		tmpNode = tmpNode->next;
	}
	Stack newNode = (Stack)malloc(sizeof(LNode));
	newNode->data = e;
	newNode->next = NULL:
	tmpNode->next = newNode;
	
	return True;
}
Status Pop(Stack &S,ElemType &e){
	Stack tmpNode = S,preNode;
	while(tmpNode->next){
		preNode = tmpNode;
		tmpNode = tmpNode->next;
		}
	}
	e = tmpNode->data;
	free(tmpNode);
	preNode->next = NULL;
	
	return True;
}

int main(){
	Stack S;
	InitStack(S);
	printf("%d\n", StackEmpty(S));
	return 0;
}