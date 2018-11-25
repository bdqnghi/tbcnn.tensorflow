
#include "btree.h"
#include <typeinfo>


BTreeIndex::BTreeIndex(DbRelation& relation, Identifier name,
                       ColumnNames key_columns, bool unique)
        : DbIndex(relation, name, key_columns, unique),
          closed(true),
          stat(nullptr),
          root(nullptr),
          file(relation.get_table_name() + "-" + name),
          key_profile() {
    if (!unique)
        throw DbRelationError("BTree index must have unique key");
	  this->build_key_profile();
}


BTreeIndex::~BTreeIndex() {
	  delete this->stat;
    delete this->root;
    this->stat = nullptr;
    this->root = nullptr;
}


void BTreeIndex::create() {
	  this->file.create();
    this->stat = new BTreeStat(this->file, this->STAT, this->STAT + 1, this->key_profile);
    this->root = new BTreeLeaf(this->file, this->stat->get_root_id(), this->key_profile, true);
    this->closed = false;
    Handles *handles = this->relation.select();
    for (auto const &handle: *handles) {
        this->insert(handle);
    }
}


void BTreeIndex::drop() {
	  this->file.drop();
}


void BTreeIndex::open() {
	  if (this->closed == true) {
        this->file.open();
        this->stat = new BTreeStat(this->file, this->STAT, this->key_profile);
        if (this->stat->get_height() == 1) {
            this->root = new BTreeLeaf(this->file, this->stat->get_root_id(), this->key_profile, false);
        } else {
            this->root = new BTreeInterior(this->file, this->stat->get_root_id(), this->key_profile, false) ;
        }
        this->closed = false;
    }
}


void BTreeIndex::close() {
	  this->file.close();
    this->stat = nullptr;
    this->root = nullptr;
    this->closed = true;
}


Handles* BTreeIndex::lookup(ValueDict* key_dict) const {
	  return this->_lookup(this->root, this->stat->get_height(), this->tkey(key_dict));
}


Handles* BTreeIndex::_lookup(BTreeNode *node, uint height, const KeyValue* key) const {
    Handles *handles = new Handles();
    if (dynamic_cast<BTreeLeaf*>(node) != NULL) {
        BTreeLeaf *leaf = (BTreeLeaf*)node;
        try {
            Handle handle = leaf->find_eq(key);
            handles->push_back(handle);
        } catch (std::out_of_range) {}
        return handles;
    } else {
        BTreeInterior *interior = (BTreeInterior*)node;
        return _lookup(interior->find(key, height), height - 1, key);
    }
}


void BTreeIndex::insert(Handle handle) {
    KeyValue *tkey = this->tkey(this->relation.project(handle, &this->key_columns));
    Insertion split_root = this->_insert(this->root, this->stat->get_height(), tkey, handle);

    if (!root->insertion_is_none(split_root)) {
        BTreeInterior *root = new BTreeInterior(this->file, 0, this->key_profile, true);
        root->set_first(this->root->get_id());
        root->insert(&split_root.second, split_root.first);
        root->save();
        this->stat->set_root_id(root->get_id());
        this->stat->set_height(this->stat->get_height() + 1);
        this->stat->save();
        delete this->root;
        this->root = root;
    }
}





Insertion BTreeIndex::_insert(BTreeNode *node, uint height, const KeyValue* key, Handle handle) {
    Insertion insertion;
    if (dynamic_cast<BTreeLeaf*>(node) != NULL) {
        BTreeLeaf *leaf = (BTreeLeaf*)node;
        insertion = leaf->insert(key, handle);
        leaf->save();
        return insertion;
    } else {
        BTreeInterior *interior = (BTreeInterior*)node;
        Insertion new_kid = this->_insert(interior->find(key, height), height - 1, key, handle);
        if (!interior->insertion_is_none(new_kid)) {
            insertion = interior->insert(&new_kid.second, new_kid.first);
            interior->save();
            return insertion;
        }
    }
    return node->insertion_none();
}


KeyValue *BTreeIndex::tkey(const ValueDict *key) const {
    KeyValue *rows = new KeyValue;
    for (auto const &column_name : this->key_columns) {
        rows->push_back(key->at(column_name));
    }
	  return rows;
}



void BTreeIndex::build_key_profile() {
    for (auto column_attribute : *this->relation.get_column_attributes(key_columns)) {
        this->key_profile.push_back(column_attribute.get_data_type());
    }
}


Handles* BTreeIndex::range(ValueDict* min_key, ValueDict* max_key) const {
    throw DbRelationError("Don't know how to do a range query on Btree index yet");
}


void BTreeIndex::del(Handle handle) {
    throw DbRelationError("Don't know how to delete from a BTree index yet");
}




void btree_test_set_row(ValueDict &row, int a, int b) {
    row["a"] = Value(a);
    row["b"] = Value(b);
}




bool test_btree() {
    
    ColumnNames column_names;
    column_names.push_back("a");
    column_names.push_back("b");
    ColumnAttributes column_attributes;
    ColumnAttribute ca(ColumnAttribute::INT);
    column_attributes.push_back(ca);
    ca.set_data_type(ColumnAttribute::INT);
    column_attributes.push_back(ca);
    
    HeapTable table1("btree_test_table", column_names, column_attributes);
    table1.create();
    
    ValueDict *row1 = new ValueDict();
    ValueDict *row2 = new ValueDict();
    btree_test_set_row(*row1, 12, 99);
    btree_test_set_row(*row2, 88, 101);
    table1.insert(row1);
    table1.insert(row2);
    
    for (int i = 0; i < 1000; i++) {
        ValueDict *row = new ValueDict();
        btree_test_set_row(*row, i+100, -i);
        table1.insert(row);
    }
    
    ColumnNames index_col_names;
    index_col_names.push_back(column_names.at(0));
    BTreeIndex index(table1, "test_index", index_col_names, true);
    index.create();

    
    ValueDict target1;
    target1["a"] = Value(12);
    Handles *handles1 = index.lookup(&target1);
    for (auto handle : *handles1) {
        ValueDict *result = table1.project(handle);
        for (auto const& entry : *row1) {
            if (entry.second != (*result)[entry.first]) {
                return false;
            }
        }
    }
    delete handles1;

    
    ValueDict target2;
    target2["a"] = Value(88);
    Handles *handles2 = index.lookup(&target2);
    for (auto handle : *handles2) {
        ValueDict *result = table1.project(handle);
        for (auto const& entry : *row2) {
            if (entry.second != (*result)[entry.first]) {
                return false;
            }
        }
    }
    delete handles2;

    
    ValueDict *empty = new ValueDict();
    ValueDict target3;
    target3["a"] = Value(6);
    Handles *handles3 = index.lookup(&target3);
    for (auto handle: *handles3) {
        ValueDict *result = table1.project(handle);
        for (auto const& entry: *empty) {
            if (entry.second != (*result)[entry.first]) {
                return false;
            }
        }
    }
    delete handles3;

    
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 1000; j++) {
            ValueDict row;
            row["a"] = Value(j+100);
            row["b"] = Value(-j);

            ValueDict target;
            target["a"] = Value(j + 100);

            Handles *handles4 = index.lookup(&target);
            for (auto handle: *handles4) {
                ValueDict *result = table1.project(handle);
                for (auto const& entry: row) {
                    if (entry.second != (*result)[entry.first]) {
                        return false;
                    }
                }
            }
            delete handles4;
        }
    }
    return true;
}
