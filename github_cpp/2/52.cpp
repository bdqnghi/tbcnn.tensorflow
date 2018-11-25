







#include "LRUCache.h"
#include <assert.h>

LRUCache::LRUCache(size_t initialMaxSize, ofstream & outStreamParam)
    : outStream(outStreamParam)
{
    currentSize = 0;
    maxNoOfKeys = initialMaxSize;
    headOfCache = nullptr;
    tailOfCache = nullptr;
}

LRUCache::~LRUCache()
{
    LRUCacheNode * curr = headOfCache;
    LRUCacheNode * temp = nullptr;
    while (curr)
    {
        temp = curr;
        curr = curr->next;
        delete temp;
    }
    
    currentSize = 0;
}

void LRUCache::Bound(const size_t noOfKeys)
{
    if (noOfKeys < currentSize)
    {
        while (currentSize != noOfKeys)
        {
            RemoveTailNode();
        }
    }
    maxNoOfKeys = noOfKeys;
}

void LRUCache::Set(const KeyValuePair& keyValue)
{
    LRUCacheNode* cacheNode = FindLRUCacheNode(keyValue.first);
    if (cacheNode)
    {
        cacheNode->keyValue.second = keyValue.second;
        MoveToHead(cacheNode);
    }
    else
    {
        if (maxNoOfKeys < 1)
            return;
        
        if (currentSize == maxNoOfKeys)
        {
            RemoveTailNode();
        }
        
        LRUCacheNode* cacheNode = new LRUCacheNode(keyValue);
        InsertNewNodeAtHead(cacheNode);
        cacheMap.insert(make_pair(keyValue.first, cacheNode));
    }
}

void LRUCache::Peek(const string key) const
{
    LRUCacheNode* temp = FindLRUCacheNode(key);
    if (temp)
    {
        outStream << temp->keyValue.second << "\n";
    }
    else
    {
        outStream << "NULL\n";
    }
}

void LRUCache::Get(const string key)
{
    LRUCacheNode* cacheNode = FindLRUCacheNode(key);
    if (cacheNode)
    {
        outStream << cacheNode->keyValue.second << "\n";
        MoveToHead(cacheNode);
    }
    else
    {
        outStream << "NULL\n";
    }
}

void LRUCache::Dump()
{
    for (auto iter = cacheMap.begin(); iter != cacheMap.end(); ++iter)
    {
        outStream << iter->first << " " << iter->second->keyValue.second << "\n";
    }
}

LRUCacheNode* LRUCache::FindLRUCacheNode(const string key) const
{
    auto iterator = cacheMap.find(key);
    if (iterator != cacheMap.end())
    {
        assert(iterator->second != nullptr);
        return iterator->second;
    }
    else
    {
        return nullptr;
    }
}

void LRUCache::MoveToHead(LRUCacheNode *cacheNode)
{
    assert(cacheNode);
    if (cacheNode == headOfCache)
        return;
    
    RemoveCacheNode(cacheNode);
    InsertNewNodeAtHead(cacheNode);
}

void LRUCache::RemoveCacheNode(LRUCacheNode* cacheNode)
{
    assert(cacheNode);
    
    if (cacheNode->prev)
    {
        cacheNode->prev->next = cacheNode->next;
    }
    else
    {
        headOfCache = cacheNode->next;
    }
    
    if (cacheNode->next)
    {
        cacheNode->next->prev = cacheNode->prev;
    }
    else
    {
        tailOfCache = cacheNode->prev;
    }
    
    currentSize--;
    
}

void LRUCache::InsertNewNodeAtHead(LRUCacheNode* cacheNode)
{
    assert(cacheNode);
    
    if (!headOfCache)
    {
        headOfCache = cacheNode;
        tailOfCache = cacheNode;
        currentSize++;
        return;
    }
    
    cacheNode->next = headOfCache;
    
    headOfCache->prev = cacheNode;
    
    cacheNode->prev = nullptr;
    
    headOfCache = cacheNode;
    
    currentSize++;
}

void LRUCache::RemoveTailNode()
{
    assert(tailOfCache);
    LRUCacheNode* temp = tailOfCache;
    tailOfCache = tailOfCache->prev;
    if (tailOfCache)
    {
        tailOfCache->next = nullptr;
    }
    else
    {
        headOfCache = tailOfCache = nullptr;
    }
    cacheMap.erase(temp->keyValue.first);
    delete temp;
    currentSize--;

}