#include "BTree.h"
#include <sstream>

using namespace std;



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
	
	path.Leaf->Delete(path.LeafIndex);
	
	if (path.Leaf != _root)
	{
		
		if (path.LeafIndex == 0)
		{
			auto pathNode = path.Branches.at(path.Branches.size() - 1);
			pathNode.pNode->UpdateKey(pathNode.Index, path, path.Branches.size() - 1);
		}

		
		Node* result = path.Leaf->RebalanceLeaf(path, path.Branches.size());
		if (result != NULL)
			_root = result;
	}

	_count--;
}

void BTree::Insert(Path& path, void* key, void* value)
{
	Split* result;
	
	if (_listCapacity < DefaultListCapacity && path.Leaf->_count == _listCapacity)
	{
		_listCapacity = _listCapacity * 2;
		Node* temp = new Node(*this, false, _root->_count); 
		

		memcpy(temp->_keys, _root->_keys, temp->_count * _keyType.Size);
		if (!_keyOnly)
			memcpy(temp->_values, _root->_values, temp->_count * _valueType.Size);		

		_root->_count = -1; 
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


BTree::iterator::iterator(const BTree::Path& path)
	: _path(path), _eof(false)
{
	
	
	
	
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
