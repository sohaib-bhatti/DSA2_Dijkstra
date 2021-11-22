#include <string>
#include <list>
#include "hash.h"
#include "heap.h"
using namespace std;




class graph{

private:
    class adjNode{
    public:
        string name;
        int cost;
        void * nodeP;
    };
    class node{
    public:
        string name;
        list <adjNode> adjList;
        int sourceCost;
        bool known = false;
        void * prevNode = nullptr;
    };

    list <node*> masterList;
public:
    hashTable vertexNames;


public:
    void addEdge(const string& source, const string& dest, int cost);
    void printGraph();
    void dijkstra(const string& start);
    void outputDijkstra(const string& start, const string& filename);

    graph();
};

