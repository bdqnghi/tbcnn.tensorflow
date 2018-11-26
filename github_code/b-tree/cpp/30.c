/**
 * @file btree.cpp - implementation of BTreeIndex class inheritance of DbIndex
 *                   class
 * @Professor: Kevin Lundeen
 * @Students: Wonseok Seo, Amanda Iverson
 * @see "Seattle University, CPSC5300, Summer 2018"
 */
#include "btree.h"
#include <typeinfo>

/**
 * constructor for the BTreeIndex
 * @param relation         the relation holding target column to be used for index
 * @param name             name of the index
 * @param key_columns      key columns to be used for btree index
 * @param unique           boolean vlaue representing uniqueness
 */
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

// Destructor for btreeIndex object
BTreeIndex::~BTreeIndex() {
	  delete this->stat;
    delete this->root;
    this->stat = nullptr;
    this->root = nullptr;
}

/**
 * Create the btree index
 */
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

/**
 * Drop the btree index
 */
void BTreeIndex::drop() {
	  this->file.drop();
}

/**
 * Open existing btree index. Enables: lookup, range, insert, delete, update
 */
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

/**
 * Closes the btree index. Disables: lookup, range, insert, delete, update
 */
void BTreeIndex::close() {
	  this->file.close();
    this->stat = nullptr;
    this->root = nullptr;
    this->closed = true;
}

/**
 * Find all the rows whose columns are equal to key. Assumes key is a dictionary
 * whose keys are the column names in the index. Returns a list of row handles
 * @param key_dict     ValueDict type key to find the target, which is map of
                       pairs of Identifier (column name) and Value (int or text)
 * @return Handles*    Set of handles holding blockId and recordId as pair
 */
Handles* BTreeIndex::lookup(ValueDict* key_dict) const {
	  return this->_lookup(this->root, this->stat->get_height(), this->tkey(key_dict));
}

// helper function of looup funnction
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

/**
 * Insert a row with the given handle. Row must exist in relation already.
 * Make a recursive call out to a helper method to determine where the insertion
 * must occur.
 * @param handle     pair of blockId and recordId to be used for insertion
 */
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

// helper function for insert function.
// insert helper method. This is called both recursively and from the base
// insert method. The requirements for this insert are the defining features to
// sucesfully find a leaf, or internal node.
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

/**
 * function to get key values which is column_names in ValueDict in order
 * @param key             key holding target columns and values
 * @return KeyValue       list of Values of target
 */
KeyValue *BTreeIndex::tkey(const ValueDict *key) const {
    KeyValue *rows = new KeyValue;
    for (auto const &column_name : this->key_columns) {
        rows->push_back(key->at(column_name));
    }
	  return rows;
}

// helper function to build key profiles which is a vector of column attributes
// of the b-tree index key
void BTreeIndex::build_key_profile() {
    for (auto column_attribute : *this->relation.get_column_attributes(key_columns)) {
        this->key_profile.push_back(column_attribute.get_data_type());
    }
}

// Not part of sprint3
Handles* BTreeIndex::range(ValueDict* min_key, ValueDict* max_key) const {
    throw DbRelationError("Don't know how to do a range query on Btree index yet");
}

// Not part of sprint3
void BTreeIndex::del(Handle handle) {
    throw DbRelationError("Don't know how to delete from a BTree index yet");
}

/**
 * btree test
 */

// helper function to set row with int values
void btree_test_set_row(ValueDict &row, int a, int b) {
    row["a"] = Value(a);
    row["b"] = Value(b);
}

// These are the tests to confirm that the actions taken on our BtreeIndex
// implementation are behaving as expected.
// return true if pass, false if fail.
bool test_btree() {
    // set up column names and column attributes for heap table
    ColumnNames column_names;
    column_names.push_back("a");
    column_names.push_back("b");
    ColumnAttributes column_attributes;
    ColumnAttribute ca(ColumnAttribute::INT);
    column_attributes.push_back(ca);
    ca.set_data_type(ColumnAttribute::INT);
    column_attributes.push_back(ca);
    // create heap table to test
    HeapTable table1("btree_test_table", column_names, column_attributes);
    table1.create();
    //create rows and insert into the table
    ValueDict *row1 = new ValueDict();
    ValueDict *row2 = new ValueDict();
    btree_test_set_row(*row1, 12, 99);
    btree_test_set_row(*row2, 88, 101);
    table1.insert(row1);
    table1.insert(row2);
    // multiple rows with sequence of int values
    for (int i = 0; i < 1000; i++) {
        ValueDict *row = new ValueDict();
        btree_test_set_row(*row, i+100, -i);
        table1.insert(row);
    }
    // create index with columns name "a"
    ColumnNames index_col_names;
    index_col_names.push_back(column_names.at(0));
    BTreeIndex index(table1, "test_index", index_col_names, true);
    index.create();

    // test btree index with target(a, 12), expecting true
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

    // test btree index with target(a, 88), expecting true
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

    // test btree index with target(a, 6), expecting empty and true
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

    // test btree indices with multiple target with nested loop, expecting true
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
