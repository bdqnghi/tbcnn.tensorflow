#include "BTree.h"
#include <sstream>

using namespace std;

/*
	BTree

	Assumption: nodes will never be empty, except for a leaf when root.
*/

BTree::BTree(const ScalarType& keyType, const ScalarType& valueType) : 
	_keyType(keyType), _valueType(valueType), _listCapacity(1), _count(0), _keyOnly(false)
{ 
	_root = new Node(*this);
}


BTree::BTree(const ScalarType& keyType) :
	_keyType(keyType), _valueType(standardtypes::StandardNodeType), _listCapacity(1), _count(0),  _keyOnly(true)
{
	_root = new Node(*this);
}

BTree::~BTree()
{
	delete _root;
}

void BTree::GetPath(void* key, BTree::Path& result)
{
	_root->GetPath(key, result);
}

void BTree::DoValuesMoved(Node* newLeaf)
{
	if (_valuesMovedCallback != NULL)
	{
		Node::iterator end = newLeaf->valueEnd();
		for (Node::iterator i = newLeaf->valueBegin(); i != end; ++i)
			_valuesMovedCallback(*i, newLeaf);
	}
}

void BTree::setValuesMovedCallback(onevaluesMovedHandler callback)
{
	_valuesMovedCallback = callback;
}

std::wstring BTree::ToString()
{
	return _root->ToString();
}

int BTree::Count()
{
	return _count;
}

void BTree::Delete(Path& path)
{
	//result is true when empty (or only one item for branches)
	path.Leaf->Delete(path.LeafIndex);
	//If the Leaf is the root, then we don't care about underflows, balancing, etc.
	if (path.Leaf != _root)
	{
		//If we deleted index 0, update routing nodes with new key.
		if (path.LeafIndex == 0)
		{
			auto pathNode = path.Branches.at(path.Branches.size() - 1);
			pathNode.pNode->UpdateKey(pathNode.Index, path, path.Branches.size() - 1);
		}

		//Rebalance tree after delete.
		Node* result = path.Leaf->RebalanceLeaf(path, path.Branches.size());
		if (result != NULL)
			_root = result;
	}

	_count--;
}

void BTree::Insert(Path& path, void* key, void* value)
{
	Split* result;
	//If we are a root node, it's an under-sized minimal node, and the node is full, expand it.
	if (_listCapacity < DefaultListCapacity && path.Leaf->_count == _listCapacity)
	{
		_listCapacity = _listCapacity * 2;
		Node* temp = new Node(*this, false, _root->_count); //Should pull size from list capacity, so is already doubled.
		//Copy old into temp.

		memcpy(temp->_keys, _root->_keys, temp->_count * _keyType.Size);
		if (!_keyOnly)
			memcpy(temp->_values, _root->_values, temp->_count * _valueType.Size);		

		_root->_count = -1; //-1 signals release Node, but not resources of keys and values.
		delete _root;

		_root = temp;
		path.Leaf = temp;

		result = path.Leaf->Insert(path.LeafIndex, key, value);

		DoValuesMoved(temp);
	}
	else
	{
		result = path.Leaf->Insert(path.LeafIndex, key, value);
	}

	while (result != NULL && path.Branches.size() > 0)
	{
		auto pathNode = path.Branches.back();
		path.Branches.pop_back();
		void* key = result->key;
		Node* node = result->right;
		delete result;

		result = pathNode.pNode->Insert(pathNode.Index, key, node);
	}

	if (result != NULL)
	{
		_root = new Node(*this, true, 1, _root, result->right, result->key);
		delete result;
	}

	_count++;
}

BTree::Path BTree::SeekToBegin()
{
	Path result;
	_root->SeekToFirst(result);
	return result;
}

BTree::Path BTree::SeekToEnd()
{
	Path result;
	_root->SeekToLast(result);

	result.LeafIndex = result.Leaf->_count > 0 ? result.Leaf->_count : 0;

	return result;
}

// BTree iterator
BTree::iterator::iterator(const BTree::Path& path)
	: _path(path), _eof(false)
{
	//Validate path: Iterators can only ever point at the end of the BTree (one index past the end of the last leaf)
	//or at an item in the tree. All other paths are invalid. (they may be valid for insertion, such as adding an item
	//to the end of the Leaf, but insertion and iteration are different concepts).
	//Don't validate on empty tree, because we'll throw an exception.
	if (!path.Match)
	{
		if ((_path.LeafIndex >= _path.Leaf->_count) && (_path.Branches.size() != 0 && _path.Branches[_path.Branches.size()-1].Index < _path.Branches[_path.Branches.size()-1].pNode->_count))
			MoveNext();

		if (_path.LeafIndex >= _path.Leaf->_count)
			_eof = true;
	}
}

void BTree::iterator::MoveNext()
{
	if(_eof)
		throw "Iteration past end of tree";

	//If we are at the maximum for this leaf, search path for node with greater values
	//If we find one, rebuild path
	//If not, set pointer to one past end of tree and set eof flag.
	if (_path.LeafIndex >= _path.Leaf->_count - 1)
	{
		size_t nummaxed = 0;
		bool open = false;
		size_t size = _path.Branches.size();
		while (nummaxed < size && !open)
		{
			BTree::PathNode& pnode = _path.Branches.at(size - 1 - nummaxed);
			if (pnode.Index == pnode.pNode->_count)
				++nummaxed;
			else
				open = true;
		}

		if (open == false)
		{
			_path.LeafIndex = _path.Leaf->_count;
			_eof = true;
		}
		else
		{
			for(size_t i = 0; i < nummaxed; i++)
				_path.Branches.pop_back();

			BTree::PathNode& pnode = _path.Branches.back();
			++pnode.Index;
			size_t offset = pnode.Index * sizeof(Node*);
			(*(Node**)(pnode.pNode->_values + offset))->SeekToFirst(_path);
		}
	}
	else
		++_path.LeafIndex;
}

void BTree::iterator::MovePrior()
{
	if (_path.LeafIndex == 0)
	{
		//We are at the minimum for this leaf. Check the path for any nodes with lesser values
		//If we find one, rebuild the path.
		//If not, throw exception (iteration past beginning).
		size_t nummin = 0;
		bool open = false;
		size_t size = _path.Branches.size();
		while (nummin < size && !open)
		{
			BTree::PathNode& pnode = _path.Branches.at(size - 1 - nummin);
			if (pnode.Index == 0)
				++nummin;
			else
				open = true;
		}

		if (open == false)
			throw "Iteration past start of tree";
		else
		{
			for(size_t i = 0; i < nummin; i++)
				_path.Branches.pop_back();

			BTree::PathNode& pnode = _path.Branches.back();
			--pnode.Index;
			size_t offset = pnode.Index * sizeof(Node*);
			(*(Node**)(pnode.pNode->_values + offset))->SeekToLast(_path);
			_eof = false;
		}
	}
	else
	{
		--_path.LeafIndex;
		_eof = false;
	}
}

BTree::iterator& BTree::iterator::operator++() 
{
	MoveNext();
	return *this;
}

BTree::iterator BTree::iterator::operator++(int)
{
	BTree::iterator tmp(*this); 
	operator++(); 
	return tmp;
}

BTree::iterator& BTree::iterator::operator--() 
{
	MovePrior();
	return *this;
}

BTree::iterator BTree::iterator::operator--(int)
{
	BTree::iterator tmp(*this); 
	operator--(); 
	return tmp;
}

bool BTree::iterator::operator==(const BTree::iterator& rhs) {return (_path.Leaf == rhs._path.Leaf) && (_path.LeafIndex == rhs._path.LeafIndex) && _eof == rhs._eof;}
bool BTree::iterator::operator!=(const BTree::iterator& rhs) {return (_path.Leaf != rhs._path.Leaf) || (_path.LeafIndex != rhs._path.LeafIndex) || _eof != rhs._eof;}
TreeEntry BTree::iterator::operator*()
{ 
	if (_path.LeafIndex >= _path.Leaf->_count)
		throw "Iterator not dereferenceable";

	return (*(_path.Leaf))[_path.LeafIndex];
}
