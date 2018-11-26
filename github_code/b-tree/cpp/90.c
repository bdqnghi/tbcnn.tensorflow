
#include "btree.h"


/************
 * BTreeBase
 ************/

BTreeBase::BTreeBase(DbRelation& relation, Identifier name, ColumnNames key_columns, bool unique)
        : DbIndex(relation, name, key_columns, unique),
          stat(nullptr),
          root(nullptr),
          closed(true),
          file(relation.get_table_name() + "-" + name),
          key_profile() {
    if (!unique)
        throw DbRelationError("BTree index must have unique key");
    build_key_profile();
}

BTreeBase::~BTreeBase() {
    delete this->stat;
    delete this->root;
}

// Create the index.
void BTreeBase::create() {
    this->file.create();
    this->stat = new BTreeStat(this->file, STAT, STAT + 1, this->key_profile);
    this->root = make_leaf(this->stat->get_root_id(), true);
    this->closed = false;

    Handles *handles = nullptr;
    try {
        // now build the index! -- add every row from relation into index
        //this->file.begin_write();
        handles = this->relation.select();
        for (auto const &handle: *handles)
            insert(handle);
        //this->file.end_write();
        delete handles;
    } catch(...) {
        delete handles;
        drop();
        throw;
    }
}

// Drop the index.
void BTreeBase::drop() {
    this->file.drop();
    this->closed = true;
}

// Open existing index. Enables: lookup, range, insert, delete, update.
void BTreeBase::open() {
    if (this->closed) {
        this->file.open();
        this->stat = new BTreeStat(this->file, STAT, this->key_profile);
        if (this->stat->get_height() == 1)
            this->root = make_leaf(this->stat->get_root_id(), false);
        else
            this->root = new BTreeInterior(this->file, this->stat->get_root_id(), this->key_profile, false);
        this->closed = false;
    }
}

// Closes the index. Disables: lookup, range, insert, delete, update.
void BTreeBase::close() {
    this->file.close();
    delete this->stat;
    this->stat = nullptr;
    delete this->root;
    this->root = nullptr;
    this->closed = true;
}

// Find all the rows whose columns are equal to key. Assumes key is a dictionary whose keys are the column
// names in the index. Returns a list of row handles.
Handles* BTreeBase::lookup(ValueDict* key_dict) {
    open();
    KeyValue *key = tkey(key_dict);
    BTreeLeafBase *leaf = _lookup(this->root, this->stat->get_height(), key);
    Handles *handles = new Handles();
    try {
        BTreeLeafValue value = leaf->find_eq(key);
        handles->push_back(value.h);
    } catch (std::out_of_range &e) {
        ; // not found, so we return an empty list
    }
    delete key;
    return handles;
}

// Recursive lookup.
BTreeLeafBase* BTreeBase::_lookup(BTreeNode *node, uint depth, const KeyValue* key) {
    if (depth == 1) { // base case: leaf
        return (BTreeLeafBase *)node;
    } else { // interior node: find the block to go to in the next level down and recurse there
        BTreeInterior *interior = (BTreeInterior *) node;
        return _lookup(find(interior, depth, key), depth - 1, key);
    }
}

Handles* BTreeBase::_range(KeyValue *tmin, KeyValue *tmax, bool return_keys) {
    Handles *results = new Handles();
    BTreeLeafBase *start = _lookup(this->root, this->stat->get_height(), tmin);
    for (auto const& mval: start->get_key_map()) {
        if (tmax != nullptr && mval.first > *tmax)
            return results;
        if (tmin == nullptr || mval.first >= *tmin) {
            if (return_keys)
                results->push_back(Handle(mval.first));
            else
                results->push_back(Handle(mval.second.h));
        }
    }
    BlockID next_leaf_id = start->get_next_leaf();
    while (next_leaf_id > 0) {
        BTreeLeafBase *next_leaf = this->make_leaf(next_leaf_id, false);
        for (auto const& mval: next_leaf->get_key_map()) {
            if (tmax != nullptr && mval.first > *tmax)
                return results;
            if (return_keys)
                results->push_back(Handle(mval.first));
            else
                results->push_back(Handle(mval.second.h));
        }
        next_leaf_id = next_leaf->get_next_leaf();
    }
    return results;
}

// Insert a row with the given handle. Row must exist in relation already.
void BTreeBase::insert(Handle handle) {
    ValueDict *row = this->relation.project(handle, &this->key_columns);
    KeyValue *key = tkey(row);
    delete row;

    Insertion split = _insert(this->root, this->stat->get_height(), key, handle);
    if (!BTreeNode::insertion_is_none(split))
        split_root(split);
}

// if we split the root grow the tree up one level
void BTreeBase::split_root(Insertion insertion) {
    BlockID rroot = insertion.first;
    KeyValue boundary = insertion.second;
    BTreeInterior *root = new BTreeInterior(this->file, 0, this->key_profile, true);
    root->set_first(this->root->get_id());
    root->insert(&boundary, rroot);
    root->save();
    this->stat->set_root_id(root->get_id());
    this->stat->set_height(this->stat->get_height() + 1);
    this->stat->save();
    this->root = root;
}

// Recursive insert. If a split happens at this level, return the (new node, boundary) of the split.
Insertion BTreeBase::_insert(BTreeNode *node, uint depth, const KeyValue* key, BTreeLeafValue leaf_value) {
    if (depth == 1) {
        BTreeLeafBase *leaf = (BTreeLeafBase *)node;
        try {
            return leaf->insert(key, leaf_value);
        } catch (DbBlockNoRoomError &e) {
            return leaf->split(make_leaf(0, true), key, leaf_value);
        }
    } else {
        BTreeInterior *interior = (BTreeInterior *)node;
        Insertion new_kid = _insert(find(interior, depth, key), depth - 1, key, leaf_value);
        if (!BTreeNode::insertion_is_none(new_kid)) {
            BlockID nnode = new_kid.first;
            KeyValue boundary = new_kid.second;
            return interior->insert(&boundary, nnode);
        }
        return BTreeNode::insertion_none();
    }
}

// Call the interior node's find method and construct an appropriate BTreeNode at the next level with the response
BTreeNode *BTreeBase::find(BTreeInterior *node, uint height, const KeyValue* key)  {
    BlockID down = node->find(key);
    if (height == 2)
        return make_leaf(down, false);
    else
        return new BTreeInterior(this->file, down, this->key_profile, false);
}

// Delete an index entry
void BTreeBase::del(Handle handle) {
    KeyValue *tkey = this->tkey(this->relation.project(handle));
    BTreeLeafBase *leaf = this->_lookup(this->root, this->stat->get_height(), tkey);
    leaf->del(tkey);
    delete tkey;
}

// Figure out the data types of each key component and encode them in self.key_profile
void BTreeBase::build_key_profile() {
    ColumnAttributes *key_attributes = this->relation.get_column_attributes(this->key_columns);
    for (auto& ca: *key_attributes)
        key_profile.push_back(ca.get_data_type());
    delete key_attributes;
}

KeyValue *BTreeBase::tkey(const ValueDict *key) const {
    if (key == nullptr)
        return nullptr;
    KeyValue *kv = new KeyValue();
    for (auto& col_name: this->key_columns)
        kv->push_back(key->at(col_name));
    return kv;
}

std::ostream &BTreeBase::_dump(std::ostream &out, BlockID block_id, uint height) {
    out << "(h:" << height << ")";
    if (height == 1) {
        BTreeLeafBase *leaf = make_leaf(block_id, false);
        out << leaf << std::endl;
        delete leaf;
    } else {
        BTreeInterior node(this->file, block_id, this->key_profile, false);
        out << &node << std::endl;
        for (auto const& pointer: node.get_pointers())
            _dump(out, pointer, height - 1);
    }
    return out;
}

std::ostream &operator<<(std::ostream &out, BTreeBase &btree) {
    //out << "STAT: " << btree.stat << std::endl;
    out << "(h:" << btree.stat->get_height() << ")ROOT: ";
    if (btree.stat->get_height() > 1) {
        BTreeInterior *root = (BTreeInterior *) btree.root;
        out << root << std::endl;
        btree._dump(out, root->get_first(), btree.stat->get_height() - 1);
        for (auto const& pointer: root->get_pointers())
            btree._dump(out, pointer, btree.stat->get_height() - 1);
    } else {
        out << (BTreeLeafIndex *) btree.root;
    }
    return out;
}



/************
 * BTreeIndex
 ************/

BTreeIndex::BTreeIndex(DbRelation& relation, Identifier name, ColumnNames key_columns, bool unique)
        : BTreeBase(relation, name, key_columns, unique) {
}

BTreeIndex::~BTreeIndex() {
}

// Construct an appropriate leaf
BTreeLeafBase *BTreeIndex::make_leaf(BlockID id, bool create) {
    return new BTreeLeafIndex(this->file, id, this->key_profile, create);
}

// Range of values in index
Handles* BTreeIndex::range(ValueDict* min_key, ValueDict* max_key) {
    KeyValue *tmin = tkey(min_key);
    KeyValue *tmax = tkey(max_key);
    Handles *handles = _range(tmin, tmax, false);
    delete tmin;
    delete tmax;
    return handles;
}

std::ostream &BTreeIndex::_dump(std::ostream &out, BlockID block_id, uint height) {
    out << "(h:" << height << ")";
    if (height == 1) {
        BTreeLeafIndex node(this->file, block_id, this->key_profile, false);
        out << &node << std::endl;
    } else {
        BTreeInterior node(this->file, block_id, this->key_profile, false);
        out << &node << std::endl;
        for (auto const& pointer: node.get_pointers())
            _dump(out, pointer, height - 1);
    }
    return out;
}



/************
 * BTreeFile
 ************/

BTreeFile::BTreeFile(DbRelation& relation,
                     Identifier name,
                     ColumnNames key_columns,
                     ColumnNames non_key_column_names,
                     ColumnAttributes non_key_column_attributes,
                     bool unique)
        : BTreeBase(relation, name, key_columns, unique),
          non_key_column_names(non_key_column_names),
          non_key_column_attributes(non_key_column_attributes) {
}

BTreeFile::~BTreeFile() {
}

// Construct an appropriate leaf
BTreeLeafBase *BTreeFile::make_leaf(BlockID id, bool create) {
    return new BTreeLeafFile(this->file, id, this->key_profile,
                             this->non_key_column_names, this->non_key_column_attributes, create);
}

// Range of values in file
Handles* BTreeFile::range(KeyValue *tmin, KeyValue *tmax) {
    return _range(tmin, tmax, true);
}


// Get the values not in the primary key (Throws std::out_of_range if not found.)
ValueDict* BTreeFile::lookup_value(KeyValue *key) {
    open();
    BTreeLeafBase *leaf = _lookup(this->root, this->stat->get_height(), key);
    BTreeLeafValue value = leaf->find_eq(key);
    return value.vd;
}

// Insert a row with the given handle. Row must exist in relation already.
// The BTree leaf owns the ValueDict *row handle after this call, so don't delete it.
void BTreeFile::insert_value(ValueDict *row) {
    KeyValue *key = tkey(row);
    BTreeLeafValue value(new ValueDict(*row));
    Insertion split = _insert(this->root, this->stat->get_height(), key, value);
    if (!BTreeNode::insertion_is_none(split))
        split_root(split);
}


/************
 * BTreeTable
 ************/

BTreeTable::BTreeTable(Identifier table_name, ColumnNames column_names, ColumnAttributes column_attributes,
                       const ColumnNames& primary_key)
        : DbRelation(table_name, column_names, column_attributes, primary_key){
    ColumnNames nonCols;
    ColumnAttributes nonColAttrs;
    for(auto const& key : primary_key) {
        for (auto const &col : column_names) {
            if (col != key)
                nonCols.push_back(col);
        }
    }
    nonColAttrs = *get_column_attributes(nonCols);
    index = new BTreeFile(*this,table_name, primary_key, nonCols, nonColAttrs, true);
}
BTreeTable::~BTreeTable() {}

void BTreeTable::create() {
    index->create();
}
void BTreeTable::create_if_not_exists() {
    try{
        index->open();
    }catch(DbException& e){
        index->create();
    }
}
void BTreeTable::drop() {
    index->drop();
}
void BTreeTable::open() {
    index->open();
}
void BTreeTable::close() {
    index->close();
}
Handle BTreeTable::insert(const ValueDict* row) {
    ValueDict *newRow = validate(row);
    index->insert_value(newRow);
    KeyValue *keyVal = index->tkey(newRow);
    return Handle(*keyVal);
}
Handle BTreeTable::update(const Handle handle, const ValueDict* new_values) {
    ValueDict* row = project(handle);
    ValueDict* newRow = row;
    ValueDict* newVals = validate(new_values);
    for(auto const& key : *newVals){
        (*newRow)[key.first] = key.second;
    }
    KeyValue* new_tkey = index->tkey(newRow);
    index->del(handle);
    index->insert_value(newRow);
    return handle;
}
void BTreeTable::del(const Handle handle) {
    index->del(handle);
}
Handles* BTreeTable::select() {
    return select(nullptr);
}
Handles* BTreeTable::select(const ValueDict* where) {
    KeyValue* minval;
    KeyValue* maxval;
    ValueDict* additionalWhere;
    Handles *handles = new Handles;
    make_range(where, minval, maxval, additionalWhere);
    for(auto const& tkey : *index->range(minval, maxval)) {
        if (additionalWhere == nullptr || selected(tkey, additionalWhere))
            handles->push_back(tkey);
    }
    return handles;
}
Handles* BTreeTable::select(Handles *current_selection, const ValueDict* where) {
    KeyValue* minval;
    KeyValue* maxval;
    ValueDict* additionalWhere;
    Handles *handles = new Handles;
    make_range(where, minval, maxval, additionalWhere);
    for(auto const& tkey : *current_selection)
        if(additionalWhere == nullptr || selected(tkey, additionalWhere))
            handles->push_back(tkey);
    return handles;
}
ValueDict* BTreeTable::project(Handle handle) {
    KeyValue vals = handle.key_value;
    ValueDict *foundVals = index->lookup_value(&vals);
    ValueDict *result = new ValueDict;
    if(foundVals== nullptr)
        throw DbRelationError("Cannot project: invalid handle");
    int i = 0;
    for(auto const& foundVal : *foundVals)
        (*result)[foundVal.first] = foundVal.second;
    for(auto const& col : *primary_key) {
        (*result)[col] = vals[i];
        ++i;
    }
    return result;
}

ValueDict* BTreeTable::project(Handle handle, const ColumnNames* column_names) {
    ColumnNames nonCols, keyCols;
    KeyValue vals = handle.key_value;
    int i = 0;
    bool foundPKey;
    ValueDict* result = new ValueDict;
    ValueDict *foundVals = index->lookup_value(&vals);
    if(foundVals->size()==0)
        throw DbRelationError("Cannot project: invalid handle");
    for(auto const& col : *column_names) {
        foundPKey = false;
        for(auto const& pkey : *primary_key) {
            if(col == pkey){
                (*result)[col] = vals[i];
                foundPKey = true;
                break;
            }
        }
        if(!foundPKey)
            nonCols.push_back(col);
        i++;
    }
    if(!nonCols.empty()){
        for(auto const& col : nonCols)
            (*result)[col] = foundVals->at(col);
    }
    return result;
}

ValueDict* BTreeTable::validate(const ValueDict* row) const {
    ValueDict* full_row = new ValueDict;
    Value rowVal;
    uint i = 0;
    ColumnAttribute checkAttr;
    ColumnAttributes colAttrs = this->get_column_attributes();
    for(auto const& col : column_names) {
        try {
            rowVal = row->at(col);
        } catch(std::out_of_range) {
            throw DbRelationError("Don't know how to handle NULLs, defaults, etc. yet");
        }
        checkAttr = rowVal.data_type;
        if(colAttrs[i].get_data_type() != checkAttr.get_data_type())
            throw DbRelationError("value for column " + col + "in " +
                                  ( rowVal.data_type == ColumnAttribute::INT ? std::to_string(rowVal.n) : rowVal.s)+" is unacceptable");
        (*full_row)[col] = rowVal;
        ++i;
    }
    return full_row;
}
bool BTreeTable::selected(Handle handle, const ValueDict* where) {
    ValueDict row = *this->project(handle, where);
    for(auto const& col : *where)
        if(row.at(col.first) != where->at(col.first))
            return false;
    return true;

}
void BTreeTable::make_range(const ValueDict *where,
                            KeyValue *&minval, KeyValue *&maxval, ValueDict *&additional_where) {
    if(where == nullptr) {
        minval = new KeyValue;
        maxval = nullptr;
        additional_where = nullptr;
        return;
    }
    additional_where = new ValueDict;
    for(auto const& whereVal : *where)
    {
        additional_where->insert(std::pair<Identifier,Value>(whereVal.first,whereVal.second));
    }

    KeyValue* tkey = new KeyValue;
    for(auto const& c : *primary_key) {
        if(where->find(c)!=where->end()){
            tkey->push_back(where->at(c));
            additional_where->erase(c);
        }
        else
            break;
    }
    if(additional_where->size() ==0)
        additional_where = nullptr;
    if(tkey->size() !=0) {
        minval = tkey;
        maxval = tkey;
    }
    else {
        minval = nullptr;
        maxval = nullptr;
    }
}
bool test_compare_btree_table(DbRelation &table, Handle handle, int a, std::string b) {
    ValueDict result = *table.project(handle);
    Value value = (result)["a"];
    if (value.n != a)
        return false;
    value = (result)["b"];
    if (value.s != b)
        return false;
    return true;
}
bool test_btree() {
    ColumnNames column_names;
    column_names.push_back("a");
    column_names.push_back("b");
    ColumnAttributes column_attributes;
    column_attributes.push_back(ColumnAttribute(ColumnAttribute::INT));
    column_attributes.push_back(ColumnAttribute(ColumnAttribute::INT));
    HeapTable table("__test_btree", column_names, column_attributes);
    table.create();
    ValueDict row1, row2;
    row1["a"] = Value(12);
    row1["b"] = Value(99);
    row2["a"] = Value(88);
    row2["b"] = Value(101);
    table.insert(&row1);
    table.insert(&row2);
    for (int i = 0; i < 1000; i++) {
        ValueDict row;
        row["a"] = Value(i + 100);
        row["b"] = Value(-i);
        table.insert(&row);
    }
    column_names.clear();
    column_names.push_back("a");
    BTreeIndex index(table, "fooindex", column_names, true);
    index.create();
    ValueDict lookup;
    lookup["a"] = 12;
    Handles *handles = index.lookup(&lookup);
    ValueDict *result = table.project(handles->back());
    if (*result != row1) {
        std::cout << "first lookup failed" << std::endl;
        return false;
    }
    delete handles;
    delete result;
    lookup["a"] = 88;
    handles = index.lookup(&lookup);
    result = table.project(handles->back());
    if (*result != row2) {
        std::cout << "second lookup failed" << std::endl;
        return false;
    }
    delete handles;
    delete result;
    lookup["a"] = 6;
    handles = index.lookup(&lookup);
    if (handles->size() != 0) {
        std::cout << "third lookup failed" << std::endl;
        return false;
    }
    delete handles;

    for (uint j = 0; j < 10; j++)
        for (int i = 0; i < 1000; i++) {
            lookup["a"] = i + 100;
            handles = index.lookup(&lookup);
            result = table.project(handles->back());
            row1["a"] = i + 100;
            row1["b"] = -i;
            if (*result != row1) {
                std::cout << "lookup failed " << i << std::endl;
                return false;
            }
            delete handles;
            delete result;
        }
    index.drop();
    table.drop();
    /**********************
       BTree Table Test
    **********************/
    ColumnNames columnNames, primaryKey;
    ColumnAttributes columnAttributes;
    columnNames.push_back("id");
    columnAttributes.push_back(ColumnAttribute(ColumnAttribute::INT));
    columnNames.push_back("a");
    columnAttributes.push_back(ColumnAttribute(ColumnAttribute::INT));
    columnNames.push_back("b");
    columnAttributes.push_back(ColumnAttribute(ColumnAttribute::TEXT));
    primaryKey.push_back("id");
    BTreeTable bTable("_test_btable", columnNames,columnAttributes,primaryKey);
    bTable.create_if_not_exists();
    ValueDict *row;
    ValueDicts expected;
    Handles bHandles;
    std::cout<<"Creating BTree Table Successful"<<std::endl;
    std::string bVal = "Quackian the Quirky Quark";
    for(int i = 0; i < 100; ++i){
        row = new ValueDict;
        (*row)["id"] = Value(i);
        (*row)["a"] = Value(i*2);
        (*row)["b"] = Value(bVal);
        expected.push_back(row);
        bHandles.push_back(bTable.insert(row));
        KeyValue kVal;
        kVal.push_back(Value(i));
    }
    std::cout<<"Inserting into BTree Table Successful"<<std::endl;
    bool bTest;
    for(auto const& handle : *bTable.select()){
        bTest = false;
        for(auto expect : expected) {
            if (test_compare_btree_table(bTable, handle, (*expect)["a"].n, (*expect)["b"].s)) {
                bTest = true;
                break;
            }
        }
        if(!bTest){
            std::cout<<"general selection failed"<<std::endl;
            return false;
        }
    }
    std::cout<<"Select BTree Table Successful"<<std::endl;
    row = (expected)[0];
    Handles *bHandlesFound = bTable.select(row);
    if(bHandlesFound->size()==0) {
        std::cout<<"Select Where did not find inserted value"<<std::endl;
        return false;
    }
    for(auto const& handle : *bHandlesFound){
        if (!test_compare_btree_table(bTable, handle, (*row)["a"].n, (*row)["b"].s)) {
            std::cout << "select with where found wrong value" << std::endl;
            return false;
        }
    }
    std::cout<<"Select Where BTree Table Successful"<<std::endl;
    for(int i = 0; i < 25; ++i){
        KeyValue keyValue;
        keyValue.push_back(Value(i));
        Handle bHandle(keyValue);
        bTable.del(bHandle);
    }
    ValueDict key;
    key.insert(std::pair<Identifier,Value>("id",Value(10)));
    handles = bTable.select(&key);
    if(handles->size() == 0)
        std::cout<<"Delete From BTree Table Successful"<<std::endl;
    std::cout<<"handle|  id   |   a   |   b"<<std::endl;
    std::cout<<"----------------------------"<<std::endl;
    for(auto const& handle: *bTable.select()){
        ValueDict* print = bTable.project(handle);
        KeyValue kval = handle.key_value;
        for(auto const k : kval)
            std::cout<<k.n<<"   ";
        std::cout<<(*print)["id"].n<<"      "<<(*print)["a"].n<<"      "<<(*print)["b"].s<<std::endl;
    }
    bTable.drop();
    std::cout<<"Drop BTree successful"<<std::endl;
    return true;
}
