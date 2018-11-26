//===============================================================================================//
//	BTree.cpp - Contains function definitions for the BTree class.								 //
//																								 //
//	This file contains the definitions for the functions of the BTree class.  The main metric to //
// be tested is insert.  Thus, all the public functions that return data are based on the		 //
// performance of the insertion.  The functions, 'diskRead' and 'diskWrite' are implemented to	 //
// read and store the nodes of the BTree in a file specified in the constructor.				 //
//																								 //
// Class:		EECS 2510 Nonlinear Data Structures												 //
// Project #3:	BST/AVL/RBT/SkipList Comparison 												 //
// Author:		Adam Savel																		 //
// Date:		Mar 17, 2018																	 //
//===============================================================================================//

#include "stdafx.h"
#include <iostream>
#include "BTree.h"


BTree::BTree()
{
	//	BTree() - is the constructor to the B-Tree.  Here all class variables are initialized.
	// The root of the B-Tree is also instantiated and saved to the disk.

	nodeCount = 1;				//	Set to 1 because the root is about to be created.
	readCount = 0;
	writeCount = 0;

	//	Open the file stream to save the B-Tree nodes to a file.
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
	//	insert() - is a public function which takes a given key character array and inserts it into
	// the tree.  Due to the implementation of the B-Tree, if the root node is completely full, it
	// must be split before an insertion can take place, otherwise the program can continue with 
	// inserting since it knows it has at least one space.
	
	//	(2 * BRANCHING_FACTOR - 1) is equal to the max amount of keys allowed per node.
	if (rootNode.keyCount == 2 * BRANCHING_FACTOR - 1)
	{
		BTNode s = BTNode();			//	Create and initialize a new root node.
		s.index = nodeCount++;			//
		s.leaf = false;					//
		s.children[1] = rootID;			//	The new root's first child will be the root
		rootNode = s;					//	The class's root needs to point at the new node
		rootID = nodeCount - 1;			//	Because the nodeCount was incremented, the rootID value
										// should be one less than it's current value.
		splitChild(rootNode, 1);		//	Split the new root's first child
		insertNonFull(rootNode, key);	//	Now an insert can be performed
	}
	else
	{
		insertNonFull(rootNode, key);
	}
}

void BTree::splitChild(BTNode& node, int index)
{
	//	splitChild() - is a private function that takes a node and splits the child of a given
	// index.  The split involves first creating a new node.  The middle key in the original
	// child is moved into it's parent.  The upper half of key values are then moved into the new
	// child.  The new child is then made to be the large sibling to the original child.

	BTNode z = BTNode();			//	Allocate a new node.
	z.index = nodeCount++;			//	

	//	Read the given node's child at the given index.
	BTNode y = diskRead(node.children[index]);
	readCount++;

	
	//	If z is a leaf, then it would follow that the new node would also be a leaf.
	z.leaf = y.leaf;

	//	Both the z and y should have the same key counts which should be equal to one less than
	// half of the BRANCHING_FACTOR.
	//
	//	2 * t - 1 is the total number of keys.  One less than half is equal to t - 1;
	z.keyCount = BRANCHING_FACTOR - 1;
	y.keyCount = BRANCHING_FACTOR - 1;
	
	//	Use a for loop to move the second half of the keys from the original child to the new child
	for (int j = 1; j <= BRANCHING_FACTOR - 1; j++) z.keys[j] = y.keys[j + BRANCHING_FACTOR];

	
	//	If the original child was not a leaf, that means it has children.  The latter half of the
	// children must be moved over to the new child.  If the original child was a leaf, then all 
	// it's children are 0 and there is no need to copy them over.
	
	if (!y.leaf) 
		for (int j = 1; j <= BRANCHING_FACTOR; j++)
			z.children[j] = y.children[j + BRANCHING_FACTOR];


	//	Room needs to be made in the parent node for the new child.  From the original child's
	// position upwards, shift the child values over one.

	for (int j = node.keyCount + 1; j >= index + 1; j--)
		node.children[j + 1] = node.children[j];

	//	One last shift ensures that in the case where the loop doesn't run, a spot is still cleared.
	node.children[index + 1] = z.index;


	//	Room needs to be made in the parent node for the new key that was brought up from the
	// original child.  Shift the parent's keys to the right to make room for the child's key.

	for (int j = node.keyCount; j >= index; j--) node.keys[j + 1] = node.keys[j];

	//	Add the  child's key to the parent and increment the parent's key counter
	node.keys[index] = y.keys[BRANCHING_FACTOR];
	node.keyCount++;

	diskWrite(node);			//	Save any changes made.
	diskWrite(y);				//
	diskWrite(z);				//
}

void BTree::insertNonFull(BTNode& node, char* key)
{
	//	insertNonFull() - handles the insertion when it is known that there is room in the tree for
	// the given key.  This function continues down the tree until it either finds the key and
	// increments its count or it finds the place where the key belongs. One the way, if it comes
	// across a full node, it performs a split.  This function is rrecursive in nature in that it
	// calls itself to traverse the tree.

	int i = node.keyCount;			//	Keeps track of current location in the current node.

	//	First, the function needs to check to see if the given key is contained within the current
	// node.  This is done by traversing the key array.

	for (int x = 1; x <= i; x++)
	{
		if (strcmp(key, node.keys[x].key) == 0)
		{
			node.keys[x].count++;	//	If the key is found, increment the count, save, and exit.
			diskWrite(node);		//
			return;					//
		}
	}

	//	If the current node is a leaf and is not already contained within this node, the key must
	// be added.  Otherwise, continue down the tree, searching for the key or the position it 
	// belongs within.

	if (node.leaf)
	{	
		//	Shift the node's current keys over by one until the new key can be placed in the
		// correct place.
		while (i >= 1 && strcmp(key, node.keys[i].key) < 0)
		{
			//	Because this is an array of objects, the keys and counts can be moved with a simple
			// = statement.
			node.keys[i + 1] = node.keys[i];
			i = i - 1;
		}

		strcpy_s(node.keys[i + 1].key, key);	//	Copy the key into the the proper spot.
		node.keys[i + 1].count = 1;				//	Set the new key's count to 1
		node.keyCount++;						//	
		diskWrite(node);						//	Save any changes
	}
	else
	{
		//	All keys must be inserted into the leaf nodes.  Shift i until the correct position is
		// found.
		while (i >= 1 && strcmp(key, node.keys[i].key) < 0) i--;

		//  By nature of the while loop, it will always go past the correct location.
		i++;
		
		//	If the child at this location is full, perform a split.  Otherwise, it is safe to
		// perform an insert into the child.

		BTNode *y = &diskRead(node.children[i]);
		readCount++;
		if (y->keyCount == 2 * BRANCHING_FACTOR - 1)
		{
			splitChild(node, i);
			if (strcmp(key, node.keys[i].key) > 0)
			{
				i++;
			}

			//	In some rare cases, the key to be inserted is already in the tree AND was just
			// moved to the current node during the split.  For this reason, this node needs to be
			// checked once more for the key to be inserted.

			for (int x = 1; x <= node.keyCount; x++)
			{
				if (strcmp(key, node.keys[x].key) == 0)
				{
					node.keys[x].count++;
					diskWrite(node);
					return;
				}
			}

			//	Re-read Y from the disk to ensure it has the correct information
			y = &diskRead(node.children[i]);
			readCount++;
		}

		//	Now an insert can safely be done on the next node.
		insertNonFull(*y, key);
	}
}

void BTree::list()
{
	//	list() - a public function that displays, in order, every item contained within the tree.
	// This is implemented in a private recursive function that traverses the tree.

	//	Recursive traversal starting at the root. 
	IOTraverse(rootNode);
}

int BTree::getHeight()
{
	//	getHeight() returns the height of the b-tree as an integer to the caller.

	//	Because all leaf nodes are at the same exact height in the tree, we can traverse any path
	// and keep count of how many node we have passed through.  When we reach any leaf, we know
	// that the count maintained correlates to the height of the tree.

	int height = 1;					//	Keeps track of the height
	BTNode currentNode = rootNode;	//	Keeps track of the current node.
	
	//	Until a leaf is reached, keep going down the minimum side of the tree.  For every node we
	// pass through, increment the height count.

	while (!currentNode.leaf)
	{
		currentNode = diskRead(currentNode.children[1]);
		height++;
	}

	return height;
}

double BTree::getLoadingFactor()
{
	//	getLoadingFactor() - is a public function that returns the loading factor.  That is, the
	// proportion of available keys to keys in use.  

	//	The function first gets the total number of keys used and divides that by the total number
	// of available keys.
	return ((double)tGetKeyCount(diskRead(rootID)) / ((nodeCount - 1) * (BRANCHING_FACTOR * 2 - 1)));
}

int BTree::getTotalNodes()
{
	//	getTotalNodes() - is a public function that returns the number of nodes currently within
	// the tree.

	//	Because the number of nodes must be monitored for saving new nodes to the file, the
	// nodeCount-er must be correct for the tree to work properly.  Thus we can just return the
	// nodeCount - 1 since it is incremented after each node is added.
	return nodeCount - 1;
}

int BTree::getFileSize()
{
	//	getFileSize() - is a public function that returns the current file size of the stored tree.

	//	For some reason, until these two lines of code were added, this function would return 0 for
	// the file size.
	fileStream.close();
	fileStream.open("BTree.data");

	//	To read the filesize, we just need to read the offset of the last byte in the file.
	fileStream.seekp(0, std::ios::end);		//	Seek to the last byte in the file
	return (fileStream.tellp() / 1024);		//	Return the position value in kiloBytes
}

int BTree::getTotalReads()
{
	//	getTotalReads() - is a public function that returns the number of times a disk read was
	// performed.  Since this is kept track in the code, all that's needed is to return the
	// variable value.
	return readCount;
}

int BTree::getTotalWrites()
{
	//	getTotalWrites() is a public function taht returns the number of times a disk write was
	// performed. Since this is kept track in the code, all that's needed is to return the
	// variable value.
	return writeCount;
}

BTree::BTNode BTree::diskRead(int nodeInd)
{
	//	diskRead() - is a private function that reads the node at the index given and returns the
	// read node.  The input parameter, rather than defining a specific location, specifies an
	// index which is then interpreted as a location by multiplying it by the size of a BT node.

	BTNode loadedNode = BTNode();

	//	Seek to the specified location,
	fileStream.seekg((nodeInd - 1) * sizeof(loadedNode));

	//	From the location, read the next amount of bytes equal in size to the BT Node.
	fileStream.read((char*)&loadedNode, sizeof(loadedNode));

	return loadedNode;
	//	Note: the reason readCount is not incremented within this function is because other
	// functions than insert utilize the diskRead function.  This would, in turn, mess up the
	// results.
}

void BTree::diskWrite(BTree::BTNode& node)
{
	//	diskWrite() - is a private function that writes a given node to the index specified in the
	// storage file.  The input parameter, rather than defining a specific location, specifies an
	// index which is then interpreted as a location by multiplying it by the size of aa AVL node.

	writeCount++;					//	To keep track of the number of writes.

	//	Seek to the specified location.
	fileStream.seekp((node.index - 1) * sizeof(node));

	//	Write to the file and clear the cache of the file stream.
	fileStream.write((char*)&node, sizeof(node));
	fileStream.flush();
	return;
}

void BTree::IOTraverse(BTNode node)
{
	//	IOTraverse() - is a private function that prints out every key, in value order, into
	// the console.  It does this using recursion.  The function takes a node as a parameter. First
	// it displays the node's left-most children.  Then it goes into a loop, reading each key and
	// child respectively until it reaches the node's key count.
	if (node.children[1] > 0)	IOTraverse(diskRead(node.children[1]));

	for (int i = 1; i <= node.keyCount; i++)
	{
		std::cout << node.keys[i].key << " " << node.keys[i].count << std::endl;
		if (node.children[i] > 0) 	IOTraverse(diskRead(node.children[i + 1]));
	}
}

int BTree::tGetKeyCount(BTNode node)
{
	//	tGetKeyCount() - is a recursive function that traverses every node in the tree, counting
	// the total key counts within each node.  This function returns an integer that is equal to
	// the total key counts in all nodes below the one it was given.

	int keyCount = node.keyCount;	//	Initialize the needed variables
	int count = 0;					//

	//	If the node is a leaf, it has no nodes and can just return.
	if (node.leaf) return node.keyCount;

	//	For each of it's children, get the key counts.
	for (int i = 1; i <= node.keyCount; i++)
	{
		keyCount += tGetKeyCount(diskRead(node.children[i]));
		count = i;
	}

	//	There is always one more child than there are keys.  For this reason, there may be a child
	// to the right of the last key.
	if (node.children[count + 1] != 0) keyCount += tGetKeyCount(diskRead(node.children[count + 1]));

	return keyCount;
}