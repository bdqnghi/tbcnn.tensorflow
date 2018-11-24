// LinkedList.cpp

#include"linked-list.h"

namespace linked_list
{
	LinkedList::LinkedList(const LinkedList &source)
	{
		Node *lastAdded = NULL;
		for ( Node *sourcep = source.head
				; sourcep != NULL
				; sourcep = sourcep->next )
		{
			if ( sourcep == source.head )
			{
				head = new Node( sourcep->data, NULL );
				lastAdded = head;
			}
			else
			{
				lastAdded->next = new Node( sourcep->data, NULL );
				lastAdded = lastAdded->next;
			}
			return;
		}
	}

	LinkedList::~LinkedList()
	{
		while ( !isEmpty() ) pop();

		// alternate: killList( head );
	}

	void LinkedList::push( Node::value_type value )
	{
		// Node *newNode = new Node;
		// newNode->data = value;
		// newNode->next = head;
		// head = newNode;

		// only one line:
		head = new Node( value, head );
	}

	Node::value_type LinkedList::pop(void)
	{
		if ( isEmpty() )
			// really should throw exception or other error indicator
			return Node::value_type();
		
		Node *firstElement = head;
		head = head->next;
		value_type firstElementValue = firstElement->data;
		delete firstElement;
		return firstElementValue;
	}

	Node::value_type LinkedList::operator[]( size_t index )
	{
		Node *nodep;
		for ( nodep = head
				; index > 0
				; nodep = nodep->next )
			--index;
		return nodep->data;
	}

 	// if ?: operator does not exist
	template<class T>
	T choose( bool b, const T &tv, const T &fv )
	{
		if ( b )
			return tv;
		else
			return fv;
	}

	size_t LinkedList::size(void)
	{
		size_t count = 0;
		for ( Node *nodep = head
				; nodep != NULL
				; nodep = nodep->next )
			++count;
		return count;
	}
	
	bool LinkedList::isIn( int value )
	{
		// this is O(n)
		for ( Node *nodep = head ; nodep != NULL ; nodep = nodep->next )
			if ( value == nodep->data ) return true;
		return false;
	}

	bool LinkedList::kill( int value )
	{
		return kill( value, head );
	}

	bool LinkedList::kill( int value, node_ptr &np )
	{
		if ( np == NULL ) return false;
		if ( np->data != value )
			return kill( value, np->next );
		//Node *target = np;
		np = np->next;
		delete np;
		return true;
	}

	void LinkedList::killList( Node *listHead )
	{
		if ( listHead == NULL ) return;
		killList( listHead->next );
		// killList( (*listHead).next );
		delete listHead;
    }
    
    bool LinkedList::sortedPush( int value )
    {
        return sortedPush( value, head, head );
    }
    
    bool LinkedList::sortedPush( int value, node_ptr &previousp, node_ptr &currentp)
    {
        if(&previousp == &currentp && (currentp == NULL || value <= currentp->data))
        {
            //if pointers are the same then assume the first element "head"
            //if the value is less or equal to first element then just use push()
            push(value);
            return true;
        }
        else
        {
            if(value <= currentp->data)
            {
                //insert into the middle because this will be in order
                previousp->next = new Node( value, currentp );
                return true;
            }
            else
            {
                if(currentp->next == NULL)
                {
                    //encountered last element in the list so just append
                    currentp->next = new Node( value, NULL );
                    return true;
                }
                else
                {
                    //the value is greater than our currentp data so check the next element in
                    //the list.
                    return sortedPush(value, currentp, currentp->next);
                }
            }
        }
    }
}