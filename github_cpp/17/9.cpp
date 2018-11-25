













#include "stdafx.h"
#include <iostream>
#include "BTree.h"


BTree::BTree()
{
	
	

	nodeCount = 1;				
	readCount = 0;
	writeCount = 0;

	
	fileStream.open("BTree.data", std::fstream::in | std::fstream::out | std::fstream::binary | std::fstream::trunc);

	rootNode = BTNode();
	rootNode.index = nodeCount++;
	diskWrite(rootNode);
	rootID = 1;
	return;
}

BTree::~BTree()
{
}

void BTree::insert(char* key)
{
	
	
	
	
	
	
	if (rootNode.keyCount == 2 * BRANCHING_FACTOR - 1)
	{
		BTNode s = BTNode();			
		s.index = nodeCount++;			
		s.leaf = false;					
		s.children[1] = rootID;			
		rootNode = s;					
		rootID = nodeCount - 1;			
										
		splitChild(rootNode, 1);		
		insertNonFull(rootNode, key);	
	}
	else
	{
		insertNonFull(rootNode, key);
	}
}

void BTree::splitChild(BTNode& node, int index)
{
	
	
	
	

	BTNode z = BTNode();			
	z.index = nodeCount++;			

	
	BTNode y = diskRead(node.children[index]);
	readCount++;

	
	
	z.leaf = y.leaf;

	
	
	
	
	z.keyCount = BRANCHING_FACTOR - 1;
	y.keyCount = BRANCHING_FACTOR - 1;
	
	
	for (int j = 1; j <= BRANCHING_FACTOR - 1; j++) z.keys[j] = y.keys[j + BRANCHING_FACTOR];

	
	
	
	
	
	if (!y.leaf) 
		for (int j = 1; j <= BRANCHING_FACTOR; j++)
			z.children[j] = y.children[j + BRANCHING_FACTOR];


	
	

	for (int j = node.keyCount + 1; j >= index + 1; j--)
		node.children[j + 1] = node.children[j];

	
	node.children[index + 1] = z.index;


	
	

	for (int j = node.keyCount; j >= index; j--) node.keys[j + 1] = node.keys[j];

	
	node.keys[index] = y.keys[BRANCHING_FACTOR];
	node.keyCount++;

	diskWrite(node);			
	diskWrite(y);				
	diskWrite(z);				
}

void BTree::insertNonFull(BTNode& node, char* key)
{
	
	
	
	
	

	int i = node.keyCount;			

	
	

	for (int x = 1; x <= i; x++)
	{
		if (strcmp(key, node.keys[x].key) == 0)
		{
			node.keys[x].count++;	
			diskWrite(node);		
			return;					
		}
	}

	
	
	

	if (node.leaf)
	{	
		
		
		while (i >= 1 && strcmp(key, node.keys[i].key) < 0)
		{
			
			
			node.keys[i + 1] = node.keys[i];
			i = i - 1;
		}

		strcpy_s(node.keys[i + 1].key, key);	
		node.keys[i + 1].count = 1;				
		node.keyCount++;						
		diskWrite(node);						
	}
	else
	{
		
		
		while (i >= 1 && strcmp(key, node.keys[i].key) < 0) i--;

		
		i++;
		
		
		

		BTNode *y = &diskRead(node.children[i]);
		readCount++;
		if (y->keyCount == 2 * BRANCHING_FACTOR - 1)
		{
			splitChild(node, i);
			if (strcmp(key, node.keys[i].key) > 0)
			{
				i++;
			}

			
			
			

			for (int x = 1; x <= node.keyCount; x++)
			{
				if (strcmp(key, node.keys[x].key) == 0)
				{
					node.keys[x].count++;
					diskWrite(node);
					return;
				}
			}

			
			y = &diskRead(node.children[i]);
			readCount++;
		}

		
		insertNonFull(*y, key);
	}
}

void BTree::list()
{
	
	

	
	IOTraverse(rootNode);
}

int BTree::getHeight()
{
	

	
	
	

	int height = 1;					
	BTNode currentNode = rootNode;	
	
	
	

	while (!currentNode.leaf)
	{
		currentNode = diskRead(currentNode.children[1]);
		height++;
	}

	return height;
}

double BTree::getLoadingFactor()
{
	
	

	
	
	return ((double)tGetKeyCount(diskRead(rootID)) / ((nodeCount - 1) * (BRANCHING_FACTOR * 2 - 1)));
}

int BTree::getTotalNodes()
{
	
	

	
	
	
	return nodeCount - 1;
}

int BTree::getFileSize()
{
	

	
	
	fileStream.close();
	fileStream.open("BTree.data");

	
	fileStream.seekp(0, std::ios::end);		
	return (fileStream.tellp() / 1024);		
}

int BTree::getTotalReads()
{
	
	
	
	return readCount;
}

int BTree::getTotalWrites()
{
	
	
	
	return writeCount;
}

BTree::BTNode BTree::diskRead(int nodeInd)
{
	
	
	

	BTNode loadedNode = BTNode();

	
	fileStream.seekg((nodeInd - 1) * sizeof(loadedNode));

	
	fileStream.read((char*)&loadedNode, sizeof(loadedNode));

	return loadedNode;
	
	
	
}

void BTree::diskWrite(BTree::BTNode& node)
{
	
	
	

	writeCount++;					

	
	fileStream.seekp((node.index - 1) * sizeof(node));

	
	fileStream.write((char*)&node, sizeof(node));
	fileStream.flush();
	return;
}

void BTree::IOTraverse(BTNode node)
{
	
	
	
	
	if (node.children[1] > 0)	IOTraverse(diskRead(node.children[1]));

	for (int i = 1; i <= node.keyCount; i++)
	{
		std::cout << node.keys[i].key << " " << node.keys[i].count << std::endl;
		if (node.children[i] > 0) 	IOTraverse(diskRead(node.children[i + 1]));
	}
}

int BTree::tGetKeyCount(BTNode node)
{
	
	
	

	int keyCount = node.keyCount;	
	int count = 0;					

	
	if (node.leaf) return node.keyCount;

	
	for (int i = 1; i <= node.keyCount; i++)
	{
		keyCount += tGetKeyCount(diskRead(node.children[i]));
		count = i;
	}

	
	
	if (node.children[count + 1] != 0) keyCount += tGetKeyCount(diskRead(node.children[count + 1]));

	return keyCount;
}