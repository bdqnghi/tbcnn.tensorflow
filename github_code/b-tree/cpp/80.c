///////////////////////////////////////////////////////////////////////////////
// btree.cpp
//
// B-Tree-block-fixed-C version 1.20 Copyright (c) 1995-2015 David R. Van Wagner
// See LICENSE.txt for licensing details
//
// btree@davevw.com
// http://www.davevw.com
///////////////////////////////////////////////////////////////////////////////

#include "btree.h"

#include <iostream> // for testing

// BT /////////////////////////////////////////////////////////////////////////

BT::BT(void* context,
        void (*getkey)(void* key, void* record),
        int (*comparekey)(void* key1, void* key2),
        bool (*read)(void* context, BT::BTIDX index, void* node, size_t size),
        bool (*write)(void* context, BT::BTIDX index, void* node, size_t size),
        bool active_sync)
{
    this->context = context;
    this->getkey = getkey;
    this->comparekey = comparekey;
    this->read = read;
    this->write = write;
    this->active_sync = active_sync;

    sync_in();

    // calculate number of nodes required for header
    reserved_idx = (sizeof(HEADER) + nodesize-1)/nodesize;

    iter_version = 0;

    freelist = 0;
}

void BT::init(BT::HEADER& header, int order, int recordsize, int maxnodes)
{
    header.intsize = sizeof(int);
    header.countsize = sizeof(INTRECORDS);
    header.idxsize = sizeof(BTIDX);
    header.ordersize = sizeof(INTENTRIES);
    header.order = order;
    header.recordsize = recordsize;
    header.nodesize = sizeof(BTIDX)*(order+1) + recordsize*(order-1) + sizeof(INTENTRIES);
    header.records = 0;
    header.root = 0;
    header.nodes = (sizeof(HEADER) + header.nodesize-1)/header.nodesize; // reserved entries for header
    header.free = maxnodes-header.nodes;
}

void BT::clear()
{
    free += nodes;
    nodes = reserved_idx;
    free -= reserved_idx;
    root = 0;
    records = 0;
    modified = true;
    sync_out();
}

BTITER BT::add(void* record)
{
    char* key = new char[recordsize];
    getkey(key, record);
    BTITER iter = add_internal(root, 0, 0, key, record, -1);
    if (iter != end())
    {
        ++records;
        ++iter_version;
        modified = true;
        sync_out();
    }
    delete [] key;
    return iter;
}

BTITER BT::add_internal(BT::BTIDX idx, BT::BTIDX left, BT::BTIDX right, void* key, void* record, INTENTRIES split_pos)
{
    INTENTRIES i, j, pos;
    pos = -1;

    if (split_pos < 0)
    {
        // find key and position, or simply node where it should be inserted
        BTITER iter = find_insert_position(idx, key);
        idx = iter.index;
        pos = iter.pos;
        i = pos;
    }
    else
        i = split_pos;

    // NOTE: MAY NOT BE A LEAF NODE:  because B-tree may temp. not be well formed

    char* node = new char[nodesize];

    if (idx == 0)
    {
        if (free <= 0)
        {
            delete [] node;
            throw_exception("B-Tree is full");
        }

        // allocate another node
        idx = nodes++;
        --free;

        // initialize node
        memset(node, 0, nodesize);

        // new root?
        if (root == 0)
            root = idx;
    }
    else 
    {
        if (!read(context, idx, node, nodesize))
        {
            delete [] node;
            throw_exception("Failed to read from B-Tree");
        }

        INTENTRIES& entries = *(INTENTRIES*)(node+nodesize-sizeof(INTENTRIES));
        if (pos >= 0 && pos < entries)
        {
            char* entry_key = new char[recordsize];
            char* precord = node + sizeof(BTIDX)*(order+1) + pos*recordsize;
            getkey(entry_key, precord);
            int compare = comparekey(key, entry_key);
            delete [] entry_key;
            if (compare == 0)
            {
                delete [] node;
                return end(); // key already present, add fails
            }
        }
    }

    INTENTRIES& entries = *(INTENTRIES*)(node+nodesize-sizeof(INTENTRIES));

    if (entries < order-1)
    {
        // fits, so insert it...
        if (i < entries)
        {
            // MUST SHIFT EXISTING RECORDS OVER TO INSERT
            for (j=entries-1; j>=i; --j)
            {
                // mode right pointer and record to right
                BTIDX* pidx = (BTIDX*)(node + (j+2)*sizeof(BTIDX));
                *(pidx+1) = *pidx;
                char* precord = node + sizeof(BTIDX)*(order+1) + j*recordsize;
                memcpy(precord+recordsize, precord, recordsize);
            }
            // move last right pointer to right
            BTIDX* pidx = (BTIDX*)(node + (j+2)*sizeof(BTIDX));
            *(pidx+1) = *pidx;
        }

        char* precord = node + sizeof(BTIDX)*(order+1) + i*recordsize;
        memcpy(precord, record, recordsize);
        pos = i;
        ++entries;

        if (left != 0)
        {
            BTIDX* pidx = (BTIDX*)(node + (pos+1)*sizeof(BTIDX));
            *pidx = left;
        }

        if (right != 0)
        {
            BTIDX* pidx = (BTIDX*)(node + (pos+1)*sizeof(BTIDX));
            *(pidx+1) = right;
        }

        if (!write(context, idx, node, nodesize))
        {
            delete [] node;
            throw_exception("Failed to write to B-Tree");
        }

        if (left != 0)
        {
            if (!read(context, left, node, nodesize))
            {
                delete [] node;
                throw_exception("Failed to read from B-Tree");
            }
            BTIDX& parent = *(BTIDX*)node;
            parent = idx;
            if (!write(context, left, node, nodesize))
            {
                delete [] node;
                throw_exception("Failed to write to B-Tree");
            }
        }
        if (right != 0)
        {
            if (!read(context, right, node, nodesize))
            {
                delete [] node;
                throw_exception("Failed to read from B-Tree");
            }
            BTIDX& parent = *(BTIDX*)node;
            parent = idx;
            if (!write(context, right, node, nodesize))
            {
                delete [] node;
                throw_exception("Failed to write to B-Tree");
            }
        }
    }
    else
    {
        // no room, split and insert into parent
        // note: node is full, don't need to look at count anymore...
        if (free <= 0)
        {
            delete [] node;
            throw_exception("B-Tree is full");
        }
        BTIDX new_idx = nodes++;
        --free;
        char* new_node = new char[nodesize];
        memset(new_node, 0, nodesize);
        BTIDX ptr = 0;
        BTITER added(*this, 0, 0);

        // assume has same parent, if it splits will fix itself
        *(BTIDX*)new_node = *(BTIDX*)node;

        // doesn't fit, split into two nodes, right first
        INTENTRIES& new_entries = *(INTENTRIES*)(new_node+nodesize-sizeof(INTENTRIES));
        new_entries = order/2;

        char* median_record = new char[recordsize];
        char* median_key = new char[recordsize];

        if (i < order/2)
        {
            // insert in original node
            pos = i;
            ptr = idx;

            // first fill in new node
            for (j=0; j<order/2; ++j)
            {
                BTIDX* pnewidx = (BTIDX*)(new_node + (j+1)*sizeof(BTIDX));
                BTIDX* pidx = (BTIDX*)(node + (j+order/2+1)*sizeof(BTIDX));
                *pnewidx = *pidx;

                char* pnewrecord = new_node + sizeof(BTIDX)*(order+1) + j*recordsize;
                char* precord = node + sizeof(BTIDX)*(order+1) + (j+order/2)*recordsize;
                memcpy(pnewrecord, precord, recordsize);
            }
            BTIDX* pnewidx = (BTIDX*)(new_node + (j+1)*sizeof(BTIDX));
            BTIDX* pidx = (BTIDX*)(node + (j+order/2+1)*sizeof(BTIDX));
            *pnewidx = *pidx;

            char* pmedian_record = node + sizeof(BTIDX)*(order+1) + (order/2-1)*recordsize;
            memcpy(median_record, pmedian_record, recordsize);
            getkey(median_key, median_record);

            // insert...
            for (j=order/2-1; j>i; --j)
            {
                BTIDX* pidx = (BTIDX*)(node + (j+1)*sizeof(BTIDX));
                *(pidx+1) = *pidx;

                char* precord = node + sizeof(BTIDX)*(order+1) + (j-1)*recordsize;
                memcpy(precord+recordsize, precord, recordsize);
            }
            pidx = (BTIDX*)(node + (j+1)*sizeof(BTIDX));
            *(pidx+1) = *pidx;
            char* precord = node + sizeof(BTIDX)*(order+1) + i*recordsize;
            memcpy(precord, record, recordsize);

            entries = order/2;
        }
        else if (i == order / 2)
        {
            // key is median, so insert in parent instead
            getkey(median_key, record);
            memcpy(median_record, record, recordsize);

            // just fill in new node
            for (j=0; j<order/2; ++j)
            {
                BTIDX* pnewidx = (BTIDX*)(new_node + (j+1)*sizeof(BTIDX));
                BTIDX* pidx = (BTIDX*)(node + (j+order/2+1)*sizeof(BTIDX));
                *pnewidx = *pidx;
                
                char* pnewrecord = new_node + sizeof(BTIDX)*(order+1) + j*recordsize;
                char* precord = node + sizeof(BTIDX)*(order+1) + (j+order/2)*recordsize;
                memcpy(pnewrecord, precord, recordsize);
            }
            BTIDX* pnewidx = (BTIDX*)(new_node + (j+1)*sizeof(BTIDX));
            BTIDX* pidx = (BTIDX*)(node + (j+order/2+1)*sizeof(BTIDX));
            *pnewidx = *pidx;

            entries = order/2;
        }
        else
        {
            // insert in new_node
            pos = i-order/2-1;
            ptr = new_idx;
            for (j=0; j<pos; ++j)
            {
                BTIDX* pnewidx = (BTIDX*)(new_node + (j+1)*sizeof(BTIDX));
                BTIDX* pidx = (BTIDX*)(node + (j+order/2+2)*sizeof(BTIDX));
                *pnewidx = *pidx;

                char* pnewrecord = new_node + sizeof(BTIDX)*(order+1) + j*recordsize;
                char* precord = node + sizeof(BTIDX)*(order+1) + (j+order/2+1)*recordsize;
                memcpy(pnewrecord, precord, recordsize);
            }
            BTIDX* pnewidx = (BTIDX*)(new_node + (j+1)*sizeof(BTIDX));
            BTIDX* pidx = (BTIDX*)(node + (j+order/2+2)*sizeof(BTIDX));
            char* pnewrecord = new_node + sizeof(BTIDX)*(order+1) + j*recordsize;
            memcpy(pnewrecord, record, recordsize);
            *pnewidx = *pidx;
            
            char* pmedian_record = node + sizeof(BTIDX)*(order+1) + (order/2)*recordsize;
            memcpy(median_record, pmedian_record, recordsize);
            getkey(median_key, median_record);

            for (j=pos+1; j<order/2; ++j)
            {
                BTIDX* pnewidx = (BTIDX*)(new_node + (j+1)*sizeof(BTIDX));
                BTIDX* pidx = (BTIDX*)(node + (j+order/2+1)*sizeof(BTIDX));
                *pnewidx = *pidx;

                char* pnewrecord = new_node + sizeof(BTIDX)*(order+1) + j*recordsize;
                char* precord = node + sizeof(BTIDX)*(order+1) + (j+order/2)*recordsize;
                memcpy(pnewrecord, precord, recordsize);
            }
            pnewidx = (BTIDX*)(new_node + (j+1)*sizeof(BTIDX));
            pidx = (BTIDX*)(node + (j+order/2+1)*sizeof(BTIDX));
            *pnewidx = *pidx;

            entries = order/2;
        }

        // RESET CHILDREN OF NEW_NODE TO POINT TO NEW PARENT
        for (j=0; j<=order/2; ++j) 
        {
            BTIDX* pidx = (BTIDX*)(new_node + (j+1)*sizeof(BTIDX));
            if (*pidx != 0)
            {
                char* child_node = new char[nodesize];
                if (!read(context, *pidx, child_node, nodesize))
                {
                    delete [] node;
                    delete [] median_record;
                    delete [] median_key;
                    delete [] child_node;
                    throw_exception("Failed to read from B-Tree");
                }
                BTIDX& child_parent = *(BTIDX*)child_node;
                child_parent = new_idx;
                if (!write(context, *pidx, child_node, nodesize))
                {
                    delete [] node;
                    delete [] median_record;
                    delete [] median_key;
                    delete [] child_node;
                    throw_exception("Failed to write to B-Tree");
                }
                delete [] child_node;
            }
        }

        // wipe out pointers moved to the new_node node
        for (j=order/2+1; j<order; ++j)
        {
            BTIDX* pidx = (BTIDX*)(node + (j+1)*sizeof(BTIDX));
            *pidx = 0;
        }

        // add to parent, create parent if necessary
        BTIDX& parent = *(BTIDX*)node;
        if (parent == 0) {
            if (free <= 0)
            {
                delete [] node;
                throw_exception("B-Tree is full");
            }
            parent = nodes++;
            --free;
            split_pos = -1;
            char* parent_node = new char[nodesize];
            memset(parent_node, 0, nodesize);
            if (!write(context, parent, parent_node, nodesize))
            {
                delete [] node;
                delete [] median_record;
                delete [] median_key;
                delete [] parent_node;
                throw_exception("Failed to write to B-Tree");
            }
            delete [] parent_node;
        } else {
            // NULL terminate the parent's pointer to this node
            char* parent_node = new char[nodesize];
            if (!read(context, parent, parent_node, nodesize))
            {
                delete [] node;
                delete [] median_record;
                delete [] median_key;
                delete [] parent_node;
                throw_exception("Failed to read from B-Tree");
            }
            INTENTRIES& parent_entries = *(INTENTRIES*)(parent_node+nodesize-sizeof(INTENTRIES));
            for (i=0; i <= parent_entries; ++i) 
            {
                BTIDX* pidx = (BTIDX*)(parent_node + (i+1)*sizeof(BTIDX));
                if (*pidx == idx) {
                    *pidx = 0;
                    break;
                }
            }
            split_pos = i;
            if (!write(context, parent, parent_node, nodesize))
            {
                delete [] node;
                delete [] median_record;
                delete [] median_key;
                delete [] parent_node;
                throw_exception("Failed to write to B-Tree");
            }
            delete [] parent_node;
        }

        // write to data store before calling recursively
        if (!write(context, idx, node, nodesize))
        {
            delete [] node;
            delete [] median_record;
            delete [] median_key;
            throw_exception("Failed to write to B-Tree");
        }
        if (!write(context, new_idx, new_node, nodesize))
        {
            delete [] node;
            delete [] median_record;
            delete [] median_key;
            throw_exception("Failed to write to B-Tree");
        }

        // insert the median and the split nodes into the parent node
        if (ptr == 0) {
            added = add_internal(parent, idx, new_idx, median_key, median_record, split_pos);
            pos = added.pos;
        } else
            added = add_internal(parent, idx, new_idx, median_key, median_record, split_pos);

        // reset root if necessary
        if (root==idx)
        {
            root = parent;
            modified = true;
sync_out(); // FOR TESTING
        }

        // TEST FOR INCONSISTENCY
        if (idx >= nodes)
            idx = idx;
        if (new_idx >= nodes)
            new_idx = new_idx;
        if (left >= nodes)
            left = left;
        if (right >= nodes)
            right = right;

        // read from data store after calling recursively
        if (!read(context, idx, node, nodesize))
        {
            delete [] node;
            delete [] median_record;
            delete [] median_key;
            throw_exception("Failed to read from B-Tree");
        }
        if (!read(context, new_idx, new_node, nodesize))
        {
            delete [] node;
            delete [] median_record;
            delete [] median_key;
            throw_exception("Failed to read from B-Tree");
        }

        if (left != 0) {
            if (ptr == 0) {
                BTIDX* pidx = (BTIDX*)(node + (order/2+1)*sizeof(BTIDX));
                *pidx = left;
                BTIDX* pnewidx = (BTIDX*)(new_node + sizeof(BTIDX));
                *pnewidx = right;
                char* right_node = new char[nodesize];
                if (!read(context, right, right_node, nodesize))
                {
                    delete [] node;
                    delete [] median_record;
                    delete [] median_key;
                    delete [] right_node;
                    throw_exception("Failed to read from B-Tree");
                }
                BTIDX& right_parent = *(BTIDX*)(right_node);
                right_parent = new_idx;
                if (!write(context, right, right_node, nodesize))
                {
                    delete [] node;
                    delete [] median_record;
                    delete [] median_key;
                    delete [] right_node;
                    throw_exception("Failed to write to B-Tree");
                }
                delete [] right_node;
                // write to disk before changing idx
                if (!write(context, idx, node, nodesize))
                {
                    delete [] node;
                    delete [] median_record;
                    delete [] median_key;
                    throw_exception("Failed to write to B-Tree");
                }
                idx = added.index;
            }
            else
            {
                // both left and right not NULL
                BTIDX* pidx;
                if (ptr == idx)
                    pidx = (BTIDX*)(node + (pos+1)*sizeof(BTIDX));
                else
                    pidx = (BTIDX*)(new_node + (pos+1)*sizeof(BTIDX));
                *pidx = left;
                *(pidx+1) = right;

                char* left_node = new char[nodesize];
                if (!read(context, left, left_node, nodesize))
                {
                    delete [] node;
                    delete [] median_record;
                    delete [] median_key;
                    delete [] left_node;
                    throw_exception("Failed to read from B-Tree");
                }
                BTIDX& left_parent = *(BTIDX*)(left_node);
                left_parent = ptr;
                if (!write(context, left, left_node, nodesize))
                {
                    delete [] node;
                    delete [] median_record;
                    delete [] median_key;
                    delete [] left_node;
                    throw_exception("Failed to write to B-Tree");
                }
                delete [] left_node;

                char* right_node = new char[nodesize];
                if (!read(context, right, right_node, nodesize))
                {
                    delete [] node;
                    delete [] median_record;
                    delete [] median_key;
                    delete [] right_node;
                    throw_exception("Failed to read from B-Tree");
                }
                BTIDX& right_parent = *(BTIDX*)(right_node);
                right_parent = ptr;
                if (!write(context, right, right_node, nodesize))
                {
                    delete [] node;
                    delete [] median_record;
                    delete [] median_key;
                    delete [] right_node;
                    throw_exception("Failed to write to B-Tree");
                }
                delete [] right_node;

                // write to disk before changing idx
                if (!write(context, idx, node, nodesize))
                {
                    delete [] node;
                    delete [] median_record;
                    delete [] median_key;
                    throw_exception("Failed to write to B-Tree");
                }
                idx = ptr;
            }
        }

        if (!write(context, new_idx, new_node, nodesize))
        {
            delete [] node;
            delete [] median_record;
            delete [] median_key;
            throw_exception("Failed to write to B-Tree");
        }

        delete [] new_node;
        delete [] median_record;
        delete [] median_key;
    }

    delete [] node;

    return BTITER(*this, idx, pos);
}

BTITER BT::find_insert_position(BT::BTIDX idx, void* key)
{
    INTENTRIES i = 0;
    BTIDX prev = 0;

    char* node = new char[nodesize];
    char* entry_key = new char[recordsize];

    while (idx != 0)
    {
        prev = idx;

        if (!read(context, idx, node, nodesize))
        {
            delete [] node;
            delete [] entry_key;
            throw_exception("Failed to read from B-Tree");
        }
        INTENTRIES& entries = *(INTENTRIES*)(node+nodesize-sizeof(INTENTRIES));
        for (i=0; i < entries; ++i)
        {
            char* record = node + sizeof(BTIDX)*(order+1) + i*recordsize;
            getkey(entry_key, record);  
            int compare = comparekey(key, entry_key);
            if (compare == 0)
            {
                // already exists, so we are done
                idx = 0;
                break;
            }
            else if (compare < 0)
            {
                idx = *(BTIDX*)(node + (i+1)*sizeof(BTIDX));
                break;
            }
        }
        if (idx == prev && i == entries)
            idx = *(BTIDX*)(node + (i+1)*sizeof(BTIDX));
    }

    delete [] node;
    delete [] entry_key;

    return BTITER(*this, prev, i);
}

bool BT::del(void* key)
{
    bool found = false;
    char* record = new char[recordsize];
    BTITER iter = find(key, record);
    if (iter != end())
    {
        char* record_key = new char[recordsize];
        getkey(record_key, record);
        if (comparekey(key, record_key) == 0)
            found = true;
        delete [] record_key;
    }
    delete [] record;
    if (found)
        return del(iter);
    else
        return false;
}

bool BT::del(const BTITER& iter)
{
    bool success = del_internal(iter);
    purge_freelist();
    return success;
}

bool BT::del_internal(const BTITER& iter)
{
    if (iter.index < reserved_idx || iter.pos < 0)
        return false;

    char* node = new char[nodesize];
    if (!read(context, iter.index, node, nodesize))
    {
        delete [] node;
        throw_exception("Failed to read from Btree");
    }

    //BTIDX& parent = *(BTIDX*)node;
    BTIDX* children = ((BTIDX*)node)+1;
    char* records = (char*)(&children[order]);
    INTENTRIES& entries = *(INTENTRIES*)(node + nodesize - sizeof(INTENTRIES));

    if (iter.pos < 0 || iter.pos >= entries)
    {
        delete [] node;
        return false;
    }

    if (children[0] == 0)
    {
        // LEAF
        for (int i=iter.pos+1; i<entries; ++i)
        {
            char* record = records+i*recordsize;
            memcpy(record-recordsize, record, recordsize);
        }
        if (--entries == 0)
            children[0] = 0;

        if (!write(context, iter.index, node, nodesize))
        {
            delete [] node;
            throw_exception("Failed to write to B-Tree");
        }

        if (entries == 0)
            underflow(iter.index, node);

        delete [] node;
        node = 0;

        --this->records; // using this to differentiate from local variable
        modified = true;
        sync_out();

        return true;
    }
    else
    {
        // INTERIOR: REPLACE BY ITS SUCCESSOR AND DELETE THE SUCCESSOR
        BTITER next = iter;
        ++next;
        if (next == end())
            return false;

        char* next_node = new char[nodesize];
        if (!read(context, next.index, next_node, nodesize))
        {
            delete [] node;
            delete [] next_node;
            throw_exception("Failed to read from B-Tree");
        }

        //BTIDX& next_parent = *(BTIDX*)next_node;
        BTIDX* next_children = ((BTIDX*)next_node)+1;
        char* next_records = (char*)(&next_children[order]);
        //INTENTRIES& next_entries = *(INTENTRIES*)(next_node + nodesize - sizeof(INTENTRIES));

        memcpy(records+iter.pos*recordsize, next_records+next.pos*recordsize, recordsize);

        // flush changes to data source before calling recursively
        if (!write(context, iter.index, node, nodesize))
        {
            delete [] node;
            delete [] next_node;
            throw_exception("Failed to write to B-Tree");
        }

        delete [] node;
        node = 0;
        delete [] next_node;
        next_node = 0;

        // TEST FOR INCONSISTENCY
        if (next.index >= nodes)
            next.index = next.index;

        // delete this successor
        return del_internal(next);
    }
}

void BT::underflow(BT::BTIDX idx, char* node)
{
    // UNDERFLOW: CHECK IF CAN BORROW FROM BROTHERS

    int i;

    BTIDX& parent = *(BTIDX*)node;
    BTIDX* children = ((BTIDX*)node)+1;
    char* records = (char*)(&children[order]);
    INTENTRIES& entries = *(INTENTRIES*)(node + nodesize - sizeof(INTENTRIES));

    if (parent == 0)
    {
        // DELETE ROOT

        remove_node(root);
        root = children[0];
        modified = true;
sync_out(); // FOR TESTING

        if (root != 0)
        {
            if (!read(context, root, node, nodesize))
            {
                delete [] node;
                node = 0;
                throw_exception("Failed to read from B-Tree");
            }

            BTIDX& child_parent = *(BTIDX*)node;
            BTIDX* child_children = ((BTIDX*)node)+1;
            //char* child_records = (char*)(&children[order]);
            INTENTRIES& child_entries = *(INTENTRIES*)(node + nodesize - sizeof(INTENTRIES));

            child_parent = 0;
            if (!write(context, root, node, nodesize))
            {
                delete [] node;
                node = 0;
                throw_exception("Failed to write to B-Tree");
            }

            char* grandchild_node = new char[nodesize];
            for (i=0; i<child_entries; ++i)
            {
                if (child_children[i] != 0)
                {
                    if (!read(context, child_children[i], grandchild_node, nodesize))
                    {
                        delete [] grandchild_node;
                        throw_exception("Failed to read from B-Tree");
                    }
                    BTIDX& grandchild_parent = *(BTIDX*)grandchild_node;
                    grandchild_parent = root;
                    if (!write(context, child_children[i], grandchild_node, nodesize))
                    {
                        delete [] grandchild_node;
                        throw_exception("Failed to write to B-Tree");
                    }
                }
            }
            delete [] grandchild_node;
        }
    }
    else
    {
        // SOLVE UNDERFLOW

        char* parent_node = new char[nodesize];
        if (!read(context, parent, parent_node, nodesize))
        {
            delete [] parent_node;
            throw_exception("Failed to read from B-Tree");
        }
        //BTIDX& parent_parent = *(BTIDX*)parent_node;
        BTIDX* parent_children = ((BTIDX*)parent_node)+1;
        char* parent_records = (char*)(&parent_children[order]);
        INTENTRIES& parent_entries = *(INTENTRIES*)(parent_node + nodesize - sizeof(INTENTRIES));

        // FIND IN PARENT
        for (i=0; i <= parent_entries && parent_children[i] != idx; ++i)
            ; // KEEP LOOKING

        // load left node just in case
        char* left_node = 0;
        if (i>0 && parent_children[i-1] != 0)
        {
            left_node = new char[nodesize];
            if (!read(context, parent_children[i-1], left_node, nodesize))
            {
                delete [] parent_node;
                delete [] left_node;
                throw_exception("Failed to read from B-Tree");
            }
        }

        // load right node just in case
        char* right_node = 0;
        if (i < parent_entries && parent_children[i+1] != 0)
        {
            right_node = new char[nodesize];
            if (!read(context, parent_children[i+1], right_node, nodesize))
            {
                delete [] parent_node;
                delete [] left_node;
                delete [] right_node;
                throw_exception("Failed to read from B-Tree");
            }
        }

        if (left_node != 0 && *(INTENTRIES*)(left_node + nodesize - sizeof(INTENTRIES)) > 1) 
        {
            // BORROW FROM LEFT BROTHER
            BTIDX brother = parent_children[i-1];
            BTIDX* brother_children = ((BTIDX*)left_node)+1;
            char* brother_records = (char*)(&brother_children[order]);
            INTENTRIES& brother_entries = *(INTENTRIES*)(left_node + nodesize - sizeof(INTENTRIES));

            memcpy(records, parent_records+(i-1)*recordsize, recordsize);
            children[1] = children[0];
            children[0] = brother_children[brother_entries];
            if (children[0] != 0)
            {
                char* child_node = new char[nodesize];
                if (!read(context, children[0], child_node, nodesize))
                {
                    delete [] parent_node;
                    delete [] left_node;
                    delete [] right_node;
                    delete [] child_node;
                    throw_exception("Failed to read from B-Tree");
                }
                BTIDX& child_parent = *(BTIDX*)child_node;
                child_parent = idx;
                if (!write(context, children[0], child_node, nodesize))
                {
                    delete [] parent_node;
                    delete [] left_node;
                    delete [] right_node;
                    delete [] child_node;
                    throw_exception("Failed to write to B-Tree");
                }
                delete [] child_node;
            }
            entries=1;
            memcpy(parent_records+(i-1)*recordsize, brother_records+(brother_entries-1)*recordsize, recordsize);
            --brother_entries;
            if (!write(context, brother, left_node, nodesize))
            {
                delete [] parent_node;
                delete [] left_node;
                delete [] right_node;
                throw_exception("Failed to write to B-Tree");
            }
            if (!write(context, parent, parent_node, nodesize))
            {
                delete [] parent_node;
                delete [] left_node;
                delete [] right_node;
                throw_exception("Failed to write to B-Tree");
            }
            if (!write(context, idx, node, nodesize))
            {
                delete [] parent_node;
                delete [] left_node;
                delete [] right_node;
                throw_exception("Failed to write to B-Tree");
            }
        } 
        else if (right_node != 0 && i < parent_entries && *(INTENTRIES*)(right_node+nodesize-sizeof(INTENTRIES)) > 1) 
        {
            // BORROW FROM RIGHT BROTHER
            BTIDX brother = parent_children[i+1];
            BTIDX* brother_children = ((BTIDX*)right_node)+1;
            char* brother_records = (char*)(&brother_children[order]);
            INTENTRIES& brother_entries = *(INTENTRIES*)(right_node + nodesize - sizeof(INTENTRIES));

            memcpy(records, parent_records+i*recordsize, recordsize);
            children[1] = brother_children[0];
            if (children[1] != 0)
            {
                char* child_node = new char[nodesize];
                if (!read(context, children[1], child_node, nodesize))
                {
                    delete [] parent_node;
                    delete [] left_node;
                    delete [] right_node;
                    delete [] child_node;
                    throw_exception("Failed to read from B-Tree");
                }
                BTIDX& child_parent = *(BTIDX*)child_node;
                child_parent = idx;
                if (!write(context, children[1], child_node, nodesize))
                {
                    delete [] parent_node;
                    delete [] left_node;
                    delete [] right_node;
                    delete [] child_node;
                    throw_exception("Failed to write to B-Tree");
                }
                delete [] child_node;
            }
            entries=1;
            memcpy(parent_records+i*recordsize, brother_records, recordsize);
            brother_children[0] = brother_children[1]; // REMOVE_INTERNAL WON'T DO THIS!
            if (!write(context, brother, right_node, nodesize))
            {
                delete [] parent_node;
                delete [] left_node;
                delete [] right_node;
                throw_exception("Failed to write to B-Tree");
            }
            if (!write(context, parent, parent_node, nodesize))
            {
                delete [] parent_node;
                delete [] left_node;
                delete [] right_node;
                throw_exception("Failed to write to B-Tree");
            }
            if (!write(context, idx, node, nodesize))
            {
                delete [] parent_node;
                delete [] left_node;
                delete [] right_node;
                throw_exception("Failed to write to B-Tree");
            }
            remove_internal(BTITER(*this, brother, 0));
        } 
        else 
        {
            // CAN'T BORROW FROM IMMEDIATE BROTHERS
            // COLLAPSE A BROTHER AND KEY FROM PARENT INSTEAD
            if (i>0) 
            {
                // COLLAPSE WITH LEFT BROTHER
                BTIDX brother = parent_children[i-1];
                BTIDX* brother_children = ((BTIDX*)left_node)+1;
                char* brother_records = (char*)(&brother_children[order]);
                INTENTRIES& brother_entries = *(INTENTRIES*)(left_node + nodesize - sizeof(INTENTRIES));

                memcpy(brother_records+recordsize, parent_records+(i-1)*recordsize, recordsize);
                brother_children[2] = children[0];
                if (brother_children[2] != 0)
                {
                    char* child_node = new char[nodesize];
                    if (!read(context, brother_children[2], child_node, nodesize))
                    {
                        delete [] parent_node;
                        delete [] left_node;
                        delete [] right_node;
                        delete [] child_node;
                        throw_exception("Failed to read from B-Tree");
                    }
                    BTIDX& child_parent = *(BTIDX*)child_node;
                    child_parent = brother;
                    if (!write(context, brother_children[2], child_node, nodesize))
                    {
                        delete [] parent_node;
                        delete [] left_node;
                        delete [] right_node;
                        delete [] child_node;
                        throw_exception("Failed to write to B-Tree");
                    }
                    delete [] child_node;
                }
                ++brother_entries;
                if (!write(context, brother, left_node, nodesize))
                {
                    delete [] parent_node;
                    delete [] left_node;
                    delete [] right_node;
                    throw_exception("Failed to write to B-Tree");
                }
                if (!write(context, parent, parent_node, nodesize))
                {
                    delete [] parent_node;
                    delete [] left_node;
                    delete [] right_node;
                    throw_exception("Failed to write to B-Tree");
                }
                if (!write(context, idx, node, nodesize))
                {
                    delete [] parent_node;
                    delete [] left_node;
                    delete [] right_node;
                    throw_exception("Failed to write to B-Tree");
                }
                remove_internal(BTITER(*this, parent, i-1));
                remove_node(idx);
            } 
            else {
                // COLLAPSE WITH RIGHT BROTHER
                BTIDX brother = parent_children[i+1];
                BTIDX* brother_children = ((BTIDX*)right_node)+1;
                char* brother_records = (char*)(&brother_children[order]);
                //INTENTRIES& brother_entries = *(INTENTRIES*)(right_node + nodesize - sizeof(INTENTRIES));

                memcpy(records, parent_records+i*recordsize, recordsize);
                memcpy(records+recordsize, brother_records, recordsize);

                children[1] = brother_children[0];
                if (children[1] != 0)
                {
                    char* child_node = new char[nodesize];
                    if (!read(context, children[1], child_node, nodesize))
                    {
                        delete [] parent_node;
                        delete [] left_node;
                        delete [] right_node;
                        delete [] child_node;
                        throw_exception("Failed to read from B-Tree");
                    }
                    BTIDX& child_parent = *(BTIDX*)child_node;
                    child_parent = idx;
                    if (!write(context, children[1], child_node, nodesize))
                    {
                        delete [] parent_node;
                        delete [] left_node;
                        delete [] right_node;
                        delete [] child_node;
                        throw_exception("Failed to write to B-Tree");
                    }
                    delete [] child_node;
                }

                children[2] = brother_children[1];
                if (children[2] != 0)
                {
                    char* child_node = new char[nodesize];
                    if (!read(context, children[2], child_node, nodesize))
                    {
                        delete [] parent_node;
                        delete [] left_node;
                        delete [] right_node;
                        delete [] child_node;
                        throw_exception("Failed to read from B-Tree");
                    }
                    BTIDX& child_parent = *(BTIDX*)child_node;
                    child_parent = idx;
                    if (!write(context, children[2], child_node, nodesize))
                    {
                        delete [] parent_node;
                        delete [] left_node;
                        delete [] right_node;
                        delete [] child_node;
                        throw_exception("Failed to write to B-Tree");
                    }
                    delete [] child_node;
                }
                entries=2;
                if (!write(context, brother, right_node, nodesize))
                {
                    delete [] parent_node;
                    delete [] left_node;
                    delete [] right_node;
                    throw_exception("Failed to write to B-Tree");
                }
                if (!write(context, parent, parent_node, nodesize))
                {
                    delete [] parent_node;
                    delete [] left_node;
                    delete [] right_node;
                    throw_exception("Failed to write to B-Tree");
                }
                if (!write(context, idx, node, nodesize))
                {
                    delete [] parent_node;
                    delete [] left_node;
                    delete [] right_node;
                    throw_exception("Failed to write to B-Tree");
                }
                remove_internal(BTITER(*this, parent, i));
                remove_node(brother);
            }
        }

        delete [] left_node;
        delete [] right_node;
        delete [] parent_node;
    }
}

void BT::remove_node(BT::BTIDX idx)
{
    // std::cout << "remove_node " << idx << std::endl;
    if (idx >= nodes)
    {
        std::cout << "trying to remove index " << idx << " past end" << std::endl;
    }
    else
    {
        // ADD TO END OF FREELIST, PARENT IS PREVIOUS FREELIST

        char* node = new char[nodesize];
        if (!read(context, idx, node, nodesize))
        {
            delete [] node;
            throw_exception("Failed to read from B-Tree");
        }
        BTIDX& parent = *(BTIDX*)node;
        BTIDX* children = ((BTIDX*)node)+1;
        char* records = (char*)(&children[order]);
        INTENTRIES& entries = *(INTENTRIES*)(node + nodesize - sizeof(INTENTRIES));

        parent = freelist;

        // WIPE REMAINING DATA IN NODE
        memset(children, 0, sizeof(BTIDX)*order);
        memset(records, 0, recordsize*(order-1));
        entries = 0;

        if (!write(context, idx, node, nodesize))
        {
            delete [] node;
            throw_exception("Failed to write to B-Tree");
        }
        freelist = idx;
        delete [] node;
    }
}

void BT::purge_freelist()
{
    // EMPTY THE FREELIST

    char* node = new char[nodesize];
    for (BTIDX next = 0; freelist != 0; freelist = next)
    {
        if (freelist > nodes-1 || freelist < reserved_idx)
        {
            // BAD INDEX
            delete [] node;
            std::cout << "Freelist is corrupt" << std::endl;
            return;
        }

        // GET NEXT BEFORE WE WRITE OVER IT
        if (!read(context, freelist, node, nodesize))
        {
            delete [] node;
            throw_exception("Failed to read from B-Tree");
        }
        next = *(BTIDX*)node;

        if (freelist == nodes-1)
        {
            // SPECIAL CASE, LAST ONE DISAPPERS
            memset(node, 0, nodesize);
            if (!write(context, freelist, node, nodesize))
            {
                delete [] node;
                throw_exception("Failed to write to B-Tree");
            }
            --nodes;
            modified = true;
sync_out(); // FOR TESTING
        }
        else
        {
            // REMOVE NODE BY REPLACING WITH LAST NODE

            if (!read(context, nodes-1, node, nodesize))
            {
                delete [] node;
                throw_exception("Failed to read from B-Tree");
            }
            if (!write(context, freelist, node, nodesize))
            {
                delete [] node;
                throw_exception("Failed to write to B-Tree");
            }

            BTIDX parent = *(BTIDX*)node; // purposefully not a reference, so can modify separately than node
            BTIDX* children = ((BTIDX*)node)+1;
            INTENTRIES& entries = *(INTENTRIES*)(node + nodesize - sizeof(INTENTRIES));

            if (next == nodes-1)
                next = freelist; // WE MOVED OUR NEXT, SO FIX IT
            if (parent != 0)
            {
                char* parent_node = new char[nodesize];
                // FIX PARENT
                if (!read(context, parent, parent_node, nodesize))
                {
                    delete [] node;
                    delete [] parent_node;
                    throw_exception("Failed to read from B-Tree");
                }
                BTIDX* parent_children = ((BTIDX*)parent_node)+1;
                INTENTRIES& parent_entries = *(INTENTRIES*)(parent_node + nodesize - sizeof(INTENTRIES));
                for (int i=0; i<=parent_entries; ++i)
                {
                    if (parent_children[i] == nodes-1)
                    {
                        parent_children[i] = freelist;
                        break;
                    }
                }
                if (!write(context, parent, parent_node, nodesize))
                {
                    delete [] node;
                    delete [] parent_node;
                    throw_exception("Failed to write to B-Tree");
                }
                delete [] parent_node;
            }

            // FIX CHILDREN
            char* child_node = new char[nodesize];
            for (int i=0; entries > 0 && i<=entries; ++i)
            {
                if (children[i] != 0)
                {
                    if (!read(context, children[i], child_node, nodesize))
                    {
                        delete [] node;
                        delete [] child_node;
                        throw_exception("Failed to read from B-Tree");
                    }
                    BTIDX& child_parent = *(BTIDX*)child_node;
                    child_parent = freelist;
                    if (!write(context, children[i], child_node, nodesize))
                    {
                        delete [] node;
                        delete [] child_node;
                        throw_exception("Failed to write to B-Tree");
                    }
                }
            }
            delete [] child_node;

            // FIX ALL NEXT INDEXES IN FREELIST
            parent = next;
            char* parent_node = new char[nodesize];
            while (parent != 0)
            {
                // FIX PARENT
                if (!read(context, parent, parent_node, nodesize))
                {
                    delete [] node;
                    delete [] parent_node;
                    throw_exception("Failed to read from B-Tree");
                }
                BTIDX& parent_parent = *(BTIDX*)parent_node;
                //BTIDX* parent_children = ((BTIDX*)parent_node)+1;
                //INTENTRIES& parent_entries = *(INTENTRIES*)(parent_node + nodesize - sizeof(INTENTRIES));
                if (parent_parent == nodes-1)
                {
                    parent_parent = freelist;

                    if (!write(context, parent, parent_node, nodesize))
                    {
                        delete [] node;
                        delete [] parent_node;
                        throw_exception("Failed to write to B-Tree");
                    }

                    break; // FOUND IT, SO DONE WITH LOOP
                }

                // NEXT
                parent = parent_parent;
            }
            delete [] parent_node;

            // ZERO OUT REMOVED NODE
            memset(node, 0, nodesize);
            if (!write(context, nodes-1, node, nodesize))
            {
                delete [] node;
                throw_exception("Failed to write to B-Tree");
            }

            // SUCCESS, DECREMENT NUMBER OF NODES, AND FIX ROOT
            if (root == nodes-1)
                root = freelist;
            --nodes;
            modified = true;
sync_out(); // FOR TESTING
        }
    }
    delete [] node;
}

void BT::remove_internal(const BTITER& iter)
{
    char* node = new char[nodesize];
    if (!read(context, iter.index, node, nodesize))
    {
        delete [] node;
        throw_exception("Failed to read from B-Tree");
    }

    //BTIDX& parent = *(BTIDX*)node;
    BTIDX* children = ((BTIDX*)node)+1;
    char* records = (char*)(&children[order]);
    INTENTRIES& entries = *(INTENTRIES*)(node + nodesize - sizeof(INTENTRIES));

    for (int i=iter.pos+1; i<entries; ++i)
    {
        memcpy(records+(i-1)*recordsize, records+i*recordsize, recordsize);
        children[i] = children[i+1];
    }
    --entries;
    if (entries == 0)
        underflow(iter.index, node);
    else
    {
        if (!write(context, iter.index, node, nodesize))
        {
            delete [] node;
            throw_exception("Failed to write to B-Tree");
        }
    }
    delete [] node;
}

bool BT::check(void (*progress)(int percent)) const
{
    // [x] traverse all nodes in left to right order
    // [x] count records & nodes, validate with header
    // [ ] confirm parent/child/level consistency
    // [x] confirm key order
    //
    //    4
    //  2   6
    // 1 3 5 7

    int last_percent;
    if (progress != 0)
        progress(last_percent = 0);

    if (records == 0)
    {
        if (nodes == reserved_idx && root == 0)
        {
            if (progress != 0)
                progress(last_percent = 100);
            return true;
        }
        else
            return false;
    }

    // verify root is within range
    if (root < reserved_idx || root >= nodes)
        return false;

    // verify root's parent is 0
    char* node = new char[nodesize];
    if (!read(context, root, node, nodesize))
    {
        delete [] node;
        return false;
    }
    if (*(BTIDX*)node != 0)
    {
        delete [] node;
        return false;
    }

    // start with left-most child node
    BTITER iter = begin();
    if (iter.index == 0 && iter.pos == 0)
    {
        delete [] node;
        return false;
    }

    // verify levels, starting on farthest levels
    int count_levels = levels();
    //int level = count_levels;

    BTIDX count_nodes = 0;
    INTRECORDS count_records = 0;
    char* last_key = 0;
    char* key = new char[recordsize];
    while (iter.index != 0)
    {
        // verify index
        if (iter.index <= 0 || iter.index >= nodes)
        {
            delete [] node;
            delete [] last_key;
            delete [] key;
            return false;
        }

        // verify position
        if (iter.pos < 0 || iter.pos >= order-1)
        {
            delete [] node;
            delete [] last_key;
            delete [] key;
            return false;
        }

        // read this node
        if (!read(context, iter.index, node, nodesize))
        {
            delete [] node;
            delete [] last_key;
            delete [] key;
            return false;
        }

        // structure of node
        //BTIDX& parent = *(BTIDX*)node;
        BTIDX* children = ((BTIDX*)node)+1;
        char* records = (char*)(&children[order]);
        INTENTRIES& entries = *(INTENTRIES*)(node + nodesize - sizeof(INTENTRIES));

        if (last_key != 0)
        {
            getkey(key, records+iter.pos*recordsize);
            if (comparekey(last_key, key) >= 0)
            {
                delete [] node;
                delete [] last_key;
                delete [] key;
                return false;
            }
        }

        // count the nodes
        if (iter.pos == 0)
        {
            // count the nodes
            ++count_nodes;

            // report progress if changed
            if (progress != 0)
            {
                int calc_percent = (int)((long)count_nodes*100/nodes);
                if (last_percent != calc_percent)
                    progress(last_percent = calc_percent);
            }

            // verify entries
            if (entries <= 0 || entries >= order)
            {
                delete [] node;
                delete [] last_key;
                delete [] key;
                return false;
            }

            // count the records
            count_records += entries;

            // check keys in sort order
            for (int i=0; i<entries-1; ++i)
            {
                if (i > 0)
                {
                    if (last_key == 0)
                        last_key = new char[recordsize];
                    getkey(last_key, records+(i-1)*recordsize);
                    getkey(key, records+i*recordsize);
                    if (comparekey(last_key, key) >= 0)
                    {
                        delete [] node;
                        delete [] last_key;
                        delete [] key;
                        return false;
                    }
                }
            }
            if (entries > 0)
            {
                if (last_key == 0)
                    last_key = new char[recordsize];
                getkey(last_key, records+iter.pos*recordsize);
            }

            // check children point to parent
            char* child_node = new char[nodesize];
            for (int i=0; i<entries; ++i)
            {
                if (children[i] == 0)
                {
                    // children must be all null or non-null
                    if (i > 0 && children[0] != 0)
                    {
                        delete [] node;
                        delete [] last_key;
                        delete [] key;
                        delete [] child_node;
                        return false;
                    }
                }
                else
                {
                    // children must be all null or non-null
                    if (i > 0 && children[0] == 0)
                    {
                        delete [] node;
                        delete [] last_key;
                        delete [] key;
                        delete [] child_node;
                        return false;
                    }

                    if (!read(context, children[i], child_node, nodesize))
                    {
                        delete [] node;
                        delete [] last_key;
                        delete [] key;
                        delete [] child_node;
                        return false;
                    }

                    BTIDX& child_parent = *(BTIDX*)child_node;

                    if (child_parent != iter.index)
                    {
                        delete [] node;
                        delete [] last_key;
                        delete [] key;
                        delete [] child_node;
                        return false;
                    }
                }
            }
            delete [] child_node;
        }
        
        // navigate to next node in order
        BTIDX idx = iter.index;
        do
        {
            //std::cout << *(int*)(records+iter.pos*recordsize) << std::endl;
            ++iter;
        }
        while (iter.index == idx);
    }
    delete [] node;
    delete [] last_key;
    delete [] key;

    if (count_records != records)
        return false;

    if (count_nodes + reserved_idx != nodes)
    {
        std::cout << "nodes is " << nodes << " but should be " << count_nodes + reserved_idx << std::endl;
        BTIDX max = count_nodes + reserved_idx;
        if (nodes > max)
        {
            max = nodes;
            std::cout << "too many" << std::endl;
            bool* traversed = new bool[max];
            for (BTIDX i=0; i<max; ++i)
                traversed[i] = false;
            for (iter = begin(); iter != end(); ++iter)
                if (iter.pos == 0)
                    traversed[iter.index] = true;
            for (BTIDX i=reserved_idx; i<max; ++i)
                if (!traversed[i])
                    std::cout << i << " orphaned" << std::endl;
            delete [] traversed;
        }
        else
            std::cout << "too few" << std::endl;

        return false;
    }

    // passed all tests
    return true;
}

BTITER BT::find(void* key, void* record) const
{
    BTIDX idx = root;
    BTIDX prev = 0;
    INTENTRIES i;
    INTENTRIES pos = -1;
    char* node = new char[nodesize];
    char* entry_key = new char[recordsize]; // note: don't know key size, so use recordsize

    while (idx != 0)
    {
        if (!read(context, idx, node, nodesize))
        {
            delete [] node;
            delete [] entry_key;
            throw_exception("Failed to read from B-Tree");
        }
        prev = idx;
        INTENTRIES& entries = *(INTENTRIES*)(node+nodesize-sizeof(INTENTRIES));
        for (i=0; i<entries; ++i)
        {
            char* node_record = node + sizeof(BTIDX)*(order+1) + i*recordsize;
            getkey(entry_key, node_record);
            int compare = comparekey(key, entry_key);
            if (compare < 0)
            {
                idx = *(BTIDX*)(node + (i+1)*sizeof(BTIDX));
                break;
            }
            else if (compare == 0)
            {
                pos = i;
                idx = 0;
                break;
            }
        }
        if (idx == prev && i == entries)
            idx = *(BTIDX*)(node + (i+1)*sizeof(BTIDX));
    }

    // read record
    if (pos >= 0)
        memcpy(record, node + sizeof(BTIDX)*(order+1) + pos*recordsize, recordsize);

    delete [] node;
    delete [] entry_key;

    if (pos < 0)
    {
        prev = 0;
        pos = 0;
    }

    return BTITER(*this, prev, pos);
}

bool BT::replace(void* key, void* record)
{
    char* node = new char[nodesize];
    char* cur_record = new char[recordsize];
    BTITER iter = find(key, cur_record);
    delete [] cur_record;

    if (iter == end())
    {
        delete [] node;
        return false;
    }
    if (!read(context, iter.index, node, nodesize))
    {
        delete [] node;
        throw_exception("Failed to read from B-Tree");
    }
    BTIDX* children = ((BTIDX*)node)+1; // TODO: test
    char* records = (char*)(&children[order]); // TODO: test
    char* dest_record = records+iter.pos*recordsize; // TODO: test
    memcpy(dest_record, record, recordsize);
    if (!write(context, iter.index, node, nodesize))
    {
        delete [] node;
        throw_exception("Failed to write to B-Tree");
    }
    delete [] node;
    return true;
}

BT::INTRECORDS BT::count() const
{
    return records;
}

int BT::sizeofnode() const
{
    return nodesize;
}

BT::BTIDX BT::numnodes() const
{
    return nodes;
}

BT::BTIDX BT::freenodes() const
{
    return free;
}

BT::BTIDX BT::offset() const
{
    return reserved_idx*nodesize;
}

int BT::levels() const
{
    int count = 0;
    char* node = new char[nodesize];
    BTIDX idx = root;
    while (idx != 0)
    {
        ++count;
        if (!read(context, idx, node, nodesize))
        {
            delete [] node;
            throw_exception("Failed to read from B-Tree");
        }
        idx = ((BTIDX*)node)[1]; // follow left branch
    }
    delete [] node;
    return count;
}

BTITER BT::begin() const
{
    BTIDX idx = root;
    BTIDX prev = 0;
    char* node = new char[nodesize];

    // follow down left size of tree
    while (idx != 0)
    {
        prev = idx;
        if (!read(context, idx, node, nodesize))
        {
            delete [] node;
            throw_exception("Failed to read from B-Tree");
        }
        INTENTRIES& entries = *(INTENTRIES*)(node+nodesize-sizeof(INTENTRIES));
        if (entries < 1)
            idx = 0;
        else
            idx = *(BTIDX*)(node + sizeof(BTIDX));
    }

    delete[] node;

    return BTITER(*this, prev, 0);
}

BTITER BT::end() const
{
    return BTITER(*this, 0, 0);
}

void BT::traverse(void (*op)(void* context, void* key, void* record)) const
{
    char* key = new char[recordsize];
    char* record = new char[recordsize];
    char* node = new char[nodesize];

    for (BTITER i = begin(); i != end(); ++i)
    {
        read(context, i.index, node, nodesize);
        memcpy(record, node + sizeof(BTIDX)*(order+1) + i.pos*recordsize, recordsize);
        getkey(key, record);
        op(context, key, record);
    }

    delete [] key;
    delete [] record;
    delete [] node;
}

void BT::sync_in()
{
    HEADER header;
    if (!read(context, 0, &header, sizeof(HEADER)))
        throw_exception("failed to read B-Tree header from data source");

    order = header.order;
    recordsize = header.recordsize;
    nodesize = header.nodesize;
    records = header.records;
    root = header.root;
    nodes = header.nodes;
    free = header.free;

    int expected_nodesize = sizeof(BTIDX)*(order+1) + recordsize*(order-1) + sizeof(INTENTRIES);

    if (nodesize != expected_nodesize
        || header.intsize != sizeof(int)
        || header.countsize != sizeof(INTRECORDS)
        || header.ordersize != sizeof(INTENTRIES)
        || header.idxsize != sizeof(BTIDX))
    {
        throw_exception("failed to initialize B-Tree from data source");
    }
}

void BT::sync_out(bool forced)
{
    if (modified && (active_sync || forced))
    {
        HEADER header;

        header.intsize = sizeof(int);
        header.countsize = sizeof(INTRECORDS);
        header.idxsize = sizeof(BTIDX);
        header.ordersize = sizeof(INTENTRIES);
        header.order = order;
        header.recordsize = recordsize;
        header.nodesize = nodesize;
        header.records = records;
        header.root = root;
        header.nodes = nodes;
        header.free = free;

        if (!write(context, 0, &header, sizeof(HEADER)))
            throw_exception("failed to write B-Tree header");

        modified = false;
    }
}

void BT::sync()
{
    sync_out(false);
}

void BT::display(std::ostream& (*dispkey)(std::ostream& str, void* key, void* record))
{
    display(0, root, dispkey);
}

void BT::display(int level, BT::BTIDX index, std::ostream& (*dispkey)(std::ostream& str, void* key, void* record))
{
    int i, j;

    if (records == 0) {
        std::cout << "EMPTY" << std::endl;
        return;
    }

    char* node = new char[nodesize];
    if (!read(context, index, node, nodesize))
    {
        delete [] node;
        throw_exception("Failed to read from B-Tree");
    }
    //BTIDX& parent = *(BTIDX*)node;
    BTIDX* children = ((BTIDX*)node)+1;
    char* records = (char*)(&children[order]);
    INTENTRIES& entries = *(INTENTRIES*)(node + nodesize - sizeof(INTENTRIES));

    char* key = new char[recordsize];

    for (i=0; i < entries; ++i) 
    {
        if (children[i] != 0) {
            std::cout << std::flush;
            display(level+1, children[i], dispkey);
        }
        char* record = records + i*recordsize;
        getkey(key, record);
        for (j=0; j<level*6; ++j)
            std::cout << ' ';
        std::cout.width(5);
        dispkey(std::cout, key, record);
        std::cout << std::endl;
    }
    if (children[i] != 0) {
        std::cout << std::flush;
        display(level+1, children[i], dispkey);
    }

    delete [] node;
    delete [] key;
}

void BT::dump_node(std::ostream& str, const HEADER* header, BT::BTIDX idx, char* node)
{
    BTIDX& parent = *(BTIDX*)node;
    BTIDX* children = ((BTIDX*)node)+1;
    char* records = (char*)(&children[header->order]);
    INTENTRIES& entries = *(INTENTRIES*)(node + header->nodesize - sizeof(INTENTRIES));

    //str << "  node " << idx << " (nodes=" << header->nodes << ")" << std::endl;
    //str << "   parent=" << parent << std::endl;
    //str << "   children=");
    //for (int i=0; i<=entries; ++i)
    //  str << children[i] << ' ';
    //str << std::endl;
    //str << "   entries=" << (int)entries << std::endl;
    //str << "   keys=");
    //for (int i=0; i<entries; ++i)
    //  str << *(int*)(records + i*header->recordsize) << ' ';
    //str << std::endl;
    
    str << '@' << idx << ':';
    int i;
    for (i=0; i<entries; ++i)
    {
        if (children[i] != 0)
            str << " @" << children[i];
        str << " " << *(int*)(records + i*header->recordsize);
    }
    if (entries > 0 && children[i] != 0)
        str << " @" << children[i];
    str << " ^@" << parent;
    str << std::endl;
}

void BT::dump_header(std::ostream& str, const BT::HEADER* header)
{
    str << "^@" << header->root;
    str << " records=" << header->records;
    str << " nodes=" << header->nodes;
    str << std::endl;
}

void BT::dump(std::ostream& str)
{
    HEADER header;
    read(context, 0, &header, sizeof(header));
    dump_header(str, &header);
    char* node = new char[header.nodesize];
    for (BT::BTIDX i=reserved_idx; i<header.nodes; ++i)
    {
        read(context, i, node, nodesize);
        dump_node(str, &header, i, node);
    }
    delete [] node;
}

BTBULK* BT::load_begin(INTRECORDS count)
{
    clear();
    return new BTBULK(order, count);
}

// example load order for full order 3 tree with 26 items
//                 (9                      18)
//     (3     6)           (12     15)             (21     24)
// (1 2) (4 5) (7 8) (10 11) (13 14) (16 17) (19 20) (22 23) (25 26)
void BT::load_record(BTBULK* bulk, void* record)
{
    char* node = 0;

    // set current level to leaf node
    int level = 0;

    while (true) // while not found a place to insert
    {
        // allocate node on current level if necessary, link children if any, mark this as parent, mark as root if at root level
        // allocate node on current level if necessary
        if (bulk->level_idx[level] == 0)
        {
            if (free <= 0)
                throw_exception("B-Tree is full");

            if (bulk->level_count[level] <= 0)
                throw_exception("Unexpected level already full");

            node = new char[nodesize];

            // allocate another node
            bulk->level_idx[level] = nodes++;
            --free;

            // initialize node
            memset(node, 0, nodesize);

            // new root?
            if (level == bulk->levels-1)
            {
                root = bulk->level_idx[level];
                modified = true;
            }

            // if not leaf, link child and mark this as parent
            if (level > 0)
            {
                // link child
                BTIDX* children = ((BTIDX*)node)+1;
                children[0] = bulk->level_idx[level-1];
                if (children[0] != 0)
                {
                    // update child's parent
                    char* child = new char[nodesize];
                    if (!read(context, children[0], child, nodesize))
                    {
                        delete [] node;
                        delete [] child;
                        throw_exception("Failed to read from B-Tree");
                    }
                    BTIDX& parent = *(BTIDX*)child;
                    parent = bulk->level_idx[level];
                    if (!write(context, children[0], child, nodesize))
                    {
                        delete [] node;
                        delete [] child;
                        throw_exception("Failed to write to B-Tree");
                    }
                    delete [] child;
                }
            }

            // if has parent, link child and parent
            if (level < bulk->levels-1 && bulk->level_idx[level+1] != 0)
            {
                // link to parent
                BTIDX& parent = *(BTIDX*)node;
                parent = bulk->level_idx[level+1];

                // link parent to child
                char* mother = new char[nodesize];
                if (!read(context, parent, mother, nodesize))
                {
                    delete [] node;
                    delete [] mother;
                    throw_exception("Failed to read from B-Tree");
                }
                BTIDX* children = ((BTIDX*)mother)+1;
                INTENTRIES& entries = *(INTENTRIES*)(mother+nodesize-sizeof(INTENTRIES));
                children[entries] = bulk->level_idx[level];
                if (!write(context, parent, mother, nodesize))
                {
                    delete [] node;
                    delete [] mother;
                    throw_exception("Failed to write to B-Tree");
                }
                delete [] mother;
            }

            // found a place to insert, so break out of loop
            break;
        }

        // read node at current position into memory
        node = new char[nodesize];
        if (!read(context, bulk->level_idx[level], node, nodesize))
        {
            delete [] node;
            throw_exception("Failed to read from B-Tree");
        }

        // identify entries in node
        INTENTRIES& entries = *(INTENTRIES*)(node+nodesize-sizeof(INTENTRIES));

        // if full or next to full on this level and still need another node, no room so go up a level if can, repeat from second step
        if (entries == order-2)
        {
            // only room for one more, check if we need another node
            if (bulk->level_count[level] == 1)
            {
                // check if more to store above
                int more = 0;
                for (int i=level+1; more==0 && i<bulk->levels; ++i)
                    more = bulk->level_count[i];

                if (more == 0)
                {
                    // check if node is left or right child of parent
                    bool left_child = false;
                    if (level < bulk->levels-1)
                    {
                        char* mother = new char[nodesize];
                        if (!read(context, bulk->level_idx[level+1], mother, nodesize))
                        {
                            delete [] node;
                            delete [] mother;
                            throw_exception("Failed to read from B-Tree");
                        }
                        BTIDX* children = ((BTIDX*)mother)+1;
                        INTENTRIES& mother_entries = *(INTENTRIES*)(mother+nodesize-sizeof(INTENTRIES));
                        left_child = (children[mother_entries-1] == bulk->level_idx[level]);
                        delete [] mother;
                    }

                    if (left_child)
                        bulk->level_idx[level] = 0; // don't try here again
                    else
                        break; // no more above, so room is here
                }
    
                // else fall through to moving up
            }
            else
                break; // more at this level, so use up this one
        }
        else if (entries < order-2)
            break; // room at this level, so use them up

        // check if are we out of room on level 0 and this is last one
        if (level == 0)
        {
            int more = 0;
            for (int i=0; i<bulk->levels; ++i)
                more += bulk->level_count[i];

            if (more < order && bulk->level_count[0] == more)
            {
                // mark that we need a new node at this level
                bulk->level_idx[0] = 0;
                level = 0;

                // free up memory
                delete [] node;
                node = 0;

                // continue loop
                continue;
            }
        }

        // move up
        ++level;

        // if no room above, then repeat from beginning at leaf level
        if (level == bulk->levels)
            level = 0;

        // free up memory
        delete [] node;
        node = 0;
    }

    // found or made room, so add element to current node 

    // children are full so clear the indexes
    for (int i=0; i<level; ++i)
        bulk->level_idx[i] = 0;

    // identify entries in node
    INTENTRIES& entries = *(INTENTRIES*)(node+nodesize-sizeof(INTENTRIES));

    // other fields
    //BTIDX& parent = *(BTIDX*)node;
    BTIDX* children = ((BTIDX*)node)+1;
    char* records = (char*)(&children[order]);

    // store record in node
    char* dest_record = records+entries*recordsize;
    memcpy(dest_record, record, recordsize);

    // increment entries in node
    entries++;

    // increment records stored
    this->records++;
    modified = true;

    if (!write(context, bulk->level_idx[level], node, nodesize))
    {
        delete [] node;
        throw_exception("Failed to write to B-Tree");
    }

    // release memory
    delete [] node;
    node = 0;

    // count decreases by one
    bulk->level_count[level]--;

    // check for overflow
    if (bulk->level_count[level] < 0)
        throw_exception("Bulk load overflow");

    // finished
}

void BT::load_end(BTBULK*& bulk)
{
    // check for success
    bool success = true;
    for (int i=0; success && i<bulk->levels-1; ++i)
        success = (bulk->level_count[i] == 0);
    success = success && (bulk->count == records);

    // free memory
    delete bulk;
    bulk = 0;

    // write root
    sync();

    // exception if failed
    if (!success)
        throw_exception("Bulk load failed");
}

