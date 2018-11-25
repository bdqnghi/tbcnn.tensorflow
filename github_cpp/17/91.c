




#include "stdafx.h"
#include "btree.h"


#define PTF_LEAF			(1 << 0)


#define ISLEAF(p)			(p->header.flags & PTF_LEAF)
#define SETLEAF(p)		(p->header.flags |= PTF_LEAF)
#define SETINTERNAL(p)(p->header.flags &= ~PTF_LEAF)
#define PAGENO(p)			(p->header.pageno)
#define NODES(p)			(p->header.nodes)


#define MAXNODES	\
	((PAGE_SIZE - sizeof(PageHeader)) / sizeof(Node) & ~1)


#define NODE(p, n)		(p->data[n])
#define KEY(p, n)			(p->data[n].key)
#define VALUE(p, n)		(p->data[n].value)
#define NEXT(p, n)		(p->data[n].next)


BTree::BTree()
	: io(PAGE_SIZE)
{
	root = pagestack.push();
	current = NULL;
	frame[0] = MakePage();
	frame[1] = MakePage();
}


BTree::~BTree()
{
	close();
	pagestack.pop();
	FreePage(frame[0]);
	FreePage(frame[1]);
}


void BTree::close()
{
	io.close();
}


void BTree::clear()
{
	memset(frame[0], 0, PAGE_SIZE);
	memset(frame[1], 0, PAGE_SIZE);
}


void BTree::pushpage()
{
	current = pagestack.push();
}


void BTree::poppage()
{
	current = pagestack.pop();
}


bool BTree::open(LPCTSTR filename, OpenMode m)
{
	clear();
	if (!io.open(filename, mode = m))
		return false;

	uint64_t size = io.getFileSize();
	if (size != 0)
		return readpage(0, root);		

	SETLEAF(root);								
	return writepage(root);				
}


bool BTree::readpage(pageid page_no, LPPAGE h)
{
	return io.readblock(page_no, h) == PAGE_SIZE;
}


bool BTree::writepage(LPPAGE h)
{
	return io.writeblock(PAGENO(h), h) == PAGE_SIZE;
}


bool BTree::insertpage(LPPAGE h)
{
	PAGENO(h) = io.getFileSize() / PAGE_SIZE;
	return io.insertblock(h) == PAGE_SIZE;
}


Datum BTree::search(const Datum& key)
{
	return searchR(root, key);
}


Datum BTree::searchR(LPPAGE h, const Datum& key)
{
	int j;
	
	if (ISLEAF(h)) { 
		for (j = 0; j < NODES(h); ++j) {
			if (KEY(h, j) == key)
				return VALUE(h, j);
		}
	} else { 
		for (j = 0; j < NODES(h); ++j) {
			if ((j+1 == NODES(h) || key < KEY(h, j+1))) {
				return searchN(NEXT(h, j), key);
			}
		}
	}

	return NullDatum;
}


Datum BTree::searchN(pageid page_no, const Datum& key)
{
	Datum d = NullDatum;

	pushpage();

	do {
		if (!readpage(page_no, current))
			break;

		d = searchR(current, key);
	} while (0);

	poppage();

	return d;
}


void BTree::insert(const Datum& key, const Datum& value)
{
	Node node;
	node.next = 0;
	node.key = key;
	node.value = value;

	LPPAGE u = insertR(root, node);
	if (u == 0) return;

	
	
	
	
	LPPAGE t = frame[1];
	memset(t, 0, PAGE_SIZE);

	insertpage(root);	

	SETINTERNAL(t);
	NODES(t) = 2;
	KEY(t, 0) = KEY(root, 0);
	KEY(t, 1) = KEY(u, 0);
	NEXT(t, 0) = PAGENO(root); NEXT(t, 1) = PAGENO(u);

	memcpy(root, t, PAGE_SIZE);
	writepage(root);
}


LPPAGE BTree::insertR(LPPAGE h, const Node& node)
{
	int i, j;
	Node t = node;

	if (ISLEAF(h)) { 
		for (j = 0; j < NODES(h); j++) {
			if (node.key < KEY(h, j)) break;
		}
	} else { 
		for (j = 0; j < NODES(h); j++) {
			if ((j+1 == NODES(h) || node.key < KEY(h, j+1))) {
				LPPAGE u = insertN(NEXT(h, j++), node);
				if (u == 0) return 0;
				t.key = KEY(u, 0); t.next = PAGENO(u);
				break;
			}
		}
	}

	for (i = NODES(h); i > j; i--) NODE(h, i) = NODE(h, i-1);
	NODE(h, j) = t;
	if (++NODES(h) < MAXNODES) {
		writepage(h);		
		return 0; 
	} 

	return split(h);	
}


LPPAGE BTree::insertN(pageid page_no, const Node& node)
{
	LPPAGE u = NULL;

	pushpage();
	
	do {
		if (!readpage(page_no, current))
			break;

		u = insertR(current, node);
	} while (0);

	poppage();

	return u;
}


LPPAGE BTree::split(LPPAGE h)
{
	LPPAGE t = frame[0];
	memset(t, 0, PAGE_SIZE);

	t->header.flags = h->header.flags;

	for (int j = 0; j < MAXNODES/2; j++) 
		NODE(t, j) = NODE(h, MAXNODES/2+j);

	NODES(h) = MAXNODES/2; NODES(t) = MAXNODES/2;

	writepage(h);
	insertpage(t);

	return t;
}
