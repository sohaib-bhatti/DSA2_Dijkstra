#ifndef _HASH_H
#define _HASH_H

#include <vector>
#include <string>

class hashTable {

public:

    // The constructor initializes the hash table.
    // Uses getPrime to choose a prime number at least as large as
    // the specified size for the initial size of the hash table.
    hashTable(int size = 0);

    // Insert the specified name into the hash table.
    // If an optional pointer is provided,
    // associate that pointer with the name.
    // Returns 0 on success,
    // 1 if name already exists in hash table,
    // 2 if rehash fails.
    int insert(const std::string &key, void *pv = nullptr);

    // Check if the specified name is in the hash table.
    // If so, return true; otherwise, return false.
    bool contains(const std::string &key);

    // Get the pointer associated with the specified name.
    // If the name does not exist in the hash table, return nullptr.
    // If an optional pointer to a bool is provided,
    // set the bool to true if the name is in the hash table,
    // and set the bool to false otherwise.
    void *getPointer(const std::string &key, bool *b = nullptr);

    // Set the pointer associated with the specified name.
    // Returns 0 on success,
    // 1 if the name does not exist in the hash table.
    int setPointer(const std::string &key, void *pv);

    // Delete the item with the specified name.
    // Returns true on success,
    // false if the specified name is not in the hash table.
    bool remove(const std::string &key);

private:

    // Each item in the hash table contains:
    // name - a string used as a name.
    // isOccupied - if false, this entry is empty,
    //              and the other fields are meaningless.
    // isDeleted - if true, this item has been lazily deleted.
    // pv - a pointer related to the name;
    //      nullptr if no pointer was provided to insert.
    class hashItem {
    public:
        std::string key {""};
        bool isOccupied {false};
        bool isDeleted {false};
        void *pv {nullptr};

        hashItem() = default;
    };

    int capacity; // The current capacity of the hash table.
    int filled; // Number of occupied items in the table.

    std::vector<hashItem> data; // The actual entries are here.

    // The hash function.
    int hash(const std::string &key);

    // Search for an item with the specified name.
    // Return the position if found, -1 otherwise.
    int findPos(const std::string &key);

    // The rehash function; makes the hash table bigger.
    // Returns true on success, false if memory allocation fails.
    bool rehash();

    // Return a prime number at least as large as size.
    // Uses a precomputed sequence of selected prime numbers.
    static int getPrime(int size);
};

#endif //_HASH_H
