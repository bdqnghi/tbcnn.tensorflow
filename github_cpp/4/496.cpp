const int TABLE_SIZE = 128;
 
class HashMap {
private:
      HashEntry **table;//this is something i need to google
public:
      HashMap() {
            table = new HashEntry*[TABLE_SIZE];//pointer to an array of size table size which is a global variable
            for (int i = 0; i < TABLE_SIZE; i++)
                  table[i] = NULL;//set all values to null for now
      }
 
      int get(int key) {
            int hash = (key % TABLE_SIZE);//getting key using taking the mod of the value with the table size
            while (table[hash] != NULL && table[hash]->getKey() != key)//while the table item is not null and the getkey does not return the key 
                  hash = (hash + 1) % TABLE_SIZE;//generate another hash using the mod methd but the next value in the table
            if (table[hash] == NULL)
                  return -1;//just exit if the value is none
            else
                  return table[hash]->getValue();//if this all work we can just return the hash of the table/array
      }
 
      void put(int key, int value) {//we are inserting the values into the table using this function
            int hash = (key % TABLE_SIZE);//make the hash again
            while (table[hash] != NULL && table[hash]->getKey() != key)
                  hash = (hash + 1) % TABLE_SIZE;
            if (table[hash] != NULL)
                  delete table[hash];//remove the value if there is a collision
            table[hash] = new HashEntry(key, value);//update out table if there was a deletion
      }     
 
      ~HashMap() {//destructor to free up memory and prevent memory leaks
            for (int i = 0; i < TABLE_SIZE; i++)
                  if (table[i] != NULL)
                        delete table[i];//delete all the values 
            delete[] table;//make sure to delete the whole table finally
      }
};
