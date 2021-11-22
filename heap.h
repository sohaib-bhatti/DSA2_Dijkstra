#include <string>
#include "hash.h"

using namespace std;



class heap {
public:
    //
    // heap - The constructor allocates space for the nodes of the heap
    // and the mapping (hash table) based on the specified capacity
    //
    heap(int capacity);

    //
    // insert - Inserts a new node into the binary heap
    //
    // Inserts a node with the specified id string, name,
    // and optionally a pointer.  They name is used to
    // determine the final position of the new node.
    //
    // Returns:
    //   0 on success
    //   1 if the heap is already filled to capacity
    //   2 if a node with the given id already exists (but the heap
    //     is not filled to capacity)
    //
    int insert(const std::string &id, int key, void *pv = nullptr);

    //
    // setKey - set the name of the specified node to the specified value
    //
    // I have decided that the class should provide this member function
    // instead of two separate increaseKey and decreaseKey functions.
    //
    // Returns:
    //   0 on success
    //   1 if a node with the given id does not exist
    //
    int setKey(const std::string &id, int key);

    //
    // deleteMin - return the data associated with the smallest name
    //             and delete that node from the binary heap
    //
    // If pId is supplied (i.e., it is not nullptr), write to that address
    // the id of the node being deleted. If pKey is supplied, write to
    // that address the name of the node being deleted. If ppData is
    // supplied, write to that address the associated void pointer.
    //
    // Returns:
    //   0 on success
    //   1 if the heap is empty
    //
    int deleteMin(std::string *pId = nullptr, int *pKey = nullptr, void *ppData = nullptr);

    //
    // remove - delete the node with the specified id from the binary heap
    //
    // If pKey is supplied, write to that address the name of the node
    // being deleted. If ppData is supplied, write to that address the
    // associated void pointer.
    //
    // Returns:
    //   0 on success
    //   1 if a node with the given id does not exist
    //
    int remove(const std::string &id, int *pKey = nullptr, void *ppData = nullptr);

private:

    int fullSpaces;
    int size;

    class node{
    public:
        string stringID;
        int key;
        void *p;

    };

    std::vector<node> data; // The actual binary heap
    hashTable mapping; // maps ids to node pointers


    void percolateUp(int posCur);
    void percolateDown(int posCur);
    int getPos(node *pn);

};



