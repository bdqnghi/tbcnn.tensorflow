#include "GameCore.h"

Queue* CreateQueue()
{
	//Dynamically allocate memory for a Queue Structure
	Queue* L = new Queue;
	
	//Initialize the Queue Strucuture;
	L->Head = NULL;
	L->Rear = NULL;
	L->Count = 0;

	//Return the pointer to the Queue
	return L;
}
//AddNodeSorted "No rear"
/*
bool AddNodeSortedQueue(Queue* L, Enemy EnemyData)
{
	//Check if the Queue doesnt exist
	if (L == NULL)
		return false;
	
	//Create New Node;
	Node *NewNode = new Node();
	////Check if it was created
	if (NewNode == NULL)
		return false;
	//Set Node data to EnemyData
	NewNode->EnemyData = EnemyData;

	//Check whether to add Node at the beginning
	if (L->Head == NULL || L->Head->EnemyData.Time_Step >= NewNode->EnemyData.Time_Step)
	{
		NewNode->Next = L->Head;
		L->Head = NewNode;
		L->Count++;
	}
	else
	{
		//Find the node that I will insert Node after
		Node *TempNode = L->Head;
		while (TempNode->Next != NULL && TempNode->Next->EnemyData.Time_Step < NewNode->EnemyData.Time_Step)
			TempNode = TempNode->Next;

		//Insert Node after the chosen node
		NewNode->Next = TempNode->Next;
		TempNode->Next = NewNode;

		//Increment Counter
		L->Count++;
	}
	return true;
}
*/

//Add Node to End "Enqueue"
bool Enqueue(Queue *L, Enemy EnemyData)
{
	//Check whether the Queue exists
	if (L == NULL)
		return false;
	//Create New Node
	Node *NewNode = new Node;
	//Check if New Node Created
	if (NewNode == NULL)
		return false;
	//Set New Node Data
	NewNode->EnemyData = EnemyData;
	NewNode->Next = NULL;
	//check if empty Queue && make it front too
	if (L->Head == NULL)
	{
		L->Head = NewNode;
		L->Rear = NewNode;
		L->Count++;
		return true;
	}
	//If not empty Queue
	L->Rear->Next = NewNode;
	L->Rear = NewNode;
	L->Count++;
	return true;
}

//RemoveFirstSorted "No rear"
/*
bool RemoveFirst(Queue* L)
{
	//Check whether the Queue exists
	if (L == NULL || L->Head==NULL)
		return false;

	//Remove first Node
	Node* TempNode = L->Head;
	L->Head = L->Head->Next;
	delete TempNode;
	L->Count--;
	return true;
}
*/


//Remove Node from First "Dequeue"
bool Dequeue(Queue *L)
{
	//Check whether Queue exist or Queue is empty
	if (L == NULL || L->Rear==NULL)
		return false;

	Node *Temp = L->Head;
	L->Head = L->Head->Next;
	L->Count--;
	delete Temp;
	
	//If last enemy to dequeue set Rear to NULL
	if (L->Head == NULL)
		L->Rear = NULL;
	
	return true;

}

bool DestroyQueue(Queue * & L)
{
	//Check whether the Queue exists
	if (L == NULL)
		return false;

	//Delete All the Nodes in the Queue
	while (Dequeue(L)){}

	//Delete the pointer to the Queue
	delete L;
	L = NULL;
	return true;

}

void PrepareDraw(Queue* Active, Enemy **E)
{
	for (int i = 0; i < Active->Count; i++)
	{
		E[i] = &(Active->Head->EnemyData);
		Enqueue(Active, Active->Head->EnemyData);
		Dequeue(Active);
	}
}


