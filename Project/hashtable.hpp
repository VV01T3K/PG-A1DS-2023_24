
class HashTable {
   private:
    const int hashGroups;
    int* table;
    bool* occupied;

   public:
    HashTable(int size) : hashGroups(size) {
        table = new int[hashGroups];
        occupied = new bool[hashGroups];
        for (int i = 0; i < hashGroups; i++) {
            occupied[i] = false;
        }
    }

    ~HashTable() {
        delete[] table;
        delete[] occupied;
    }

    int hashFunction(int key) { return key % hashGroups; }

    void insertItem(int key) {
        int hashedKey = hashFunction(key);
        int originalKey = hashedKey;
        while (occupied[hashedKey]) {
            hashedKey = (hashedKey + 1) % hashGroups;
            if (hashedKey == originalKey) {
                return;
            }
        }
        table[hashedKey] = key;
        occupied[hashedKey] = true;
    }

    void removeItem(int key) {
        int hashedKey = hashFunction(key);
        while (occupied[hashedKey] && table[hashedKey] != key) {
            hashedKey = (hashedKey + 1) % hashGroups;
        }
        if (table[hashedKey] == key) {
            occupied[hashedKey] = false;
        }
    }

    bool find(int key) {
        int hashedKey = hashFunction(key);
        while (occupied[hashedKey] && table[hashedKey] != key) {
            hashedKey = (hashedKey + 1) % hashGroups;
        }
        return table[hashedKey] == key;
    }
};