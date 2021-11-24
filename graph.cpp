//
// Created by Sohaib Bhatti on 11/20/2021.
//

#include "graph.h"
#include <iostream>
#include <fstream>
#include <climits>


graph::graph() = default;

void graph::addEdge(const string& source, const string& dest, int cost){
    node *sourceNode;
    node *destNode;


    /*check to see if either vertex already exists
     * if not, create it and add it to the master list of vertices
     * add it to the hash table of vertices to easily find pointers to each vertex
     * */

    if(!vertexNames.contains(source)){
        sourceNode = new node();
        sourceNode->name = source;
        masterList.push_back(sourceNode);
        vertexNames.insert(source, sourceNode);
    }
    else{

        sourceNode = static_cast<node *> (vertexNames.getPointer(source));
    }

    if(!vertexNames.contains(dest)){

        destNode = new node();
        destNode->name = dest;
        masterList.push_back(destNode);
        vertexNames.insert(dest, destNode);
    }
    else{
        destNode = static_cast<node *> (vertexNames.getPointer(dest));
    }

    // create a pseudo-node that stores info about the edge and push it to the source's adjacency list
    adjNode destPush;
    destPush.name = dest;
    destPush.cost = cost;
    destPush.nodeP = destNode;
    sourceNode->adjList.push_back(destPush);


}

// implements Dijkstra's algorithm
void graph::dijkstra(const string& start){

    // creates a heap to prioritize vertices for the algorithm
    heap dijkstraHeap(masterList.size());

    // ensures that the initial distance from the source is infinity. Initializes the source node.
    for (auto const& currentNode : masterList){
        currentNode->sourceCost = INT_MAX;
    }
    node *source = static_cast<node *> (vertexNames.getPointer(start));
    source->sourceCost = 0;
    source->prevNode = nullptr;
    dijkstraHeap.insert(source->name, source->sourceCost, source);

    string stringTmp;
    while(dijkstraHeap.fullSpaces != 0){
        // looks for the currently cheapest node that isn't known and stores it in nodeTemp
        dijkstraHeap.deleteMin(&stringTmp);
        node *nodeTemp = static_cast<node *> (vertexNames.getPointer(stringTmp));

        // the algorithm
        for (auto const &currentAdjNode: nodeTemp->adjList){
            // check if the current cost of that vertex plus the weight of the new cost is lower than the older one
            if((nodeTemp->sourceCost + currentAdjNode.cost) < static_cast<node *>(currentAdjNode.nodeP)->sourceCost){
                // update the old cost of that vertex and store the previous node on the best path
                static_cast<node *>(currentAdjNode.nodeP)->sourceCost = nodeTemp->sourceCost + currentAdjNode.cost;
                static_cast<node *>(currentAdjNode.nodeP)->prevNode = nodeTemp;

                //insert adjacent nodes into the heap as they are not known
                dijkstraHeap.insert(static_cast<node *>(currentAdjNode.nodeP)->name,
                                    static_cast<node *>(currentAdjNode.nodeP)->sourceCost,
                                    currentAdjNode.nodeP);
                }
        }


    }
}

void graph::outputDijkstra(const string& start, const string& filename){
    node * temp;
    list<string> vertexList;
    ofstream output(filename);
    for(auto const& currentNode : masterList){
        if(currentNode->name == start){
            output << currentNode->name << ": " << currentNode->sourceCost << " [" << currentNode->name << "]" << endl;
        }
        else if(currentNode->prevNode == nullptr){
           output << currentNode->name << ": NO PATH" << endl;
        }
        // push_front() is the equivalent of a stack
        else{
            vertexList.push_front(currentNode->name);
            temp = static_cast<node *>(currentNode->prevNode);
            while(true){
                if(temp->name == start){
                    vertexList.push_front(start);
                    break;
                }
                vertexList.push_front(temp->name);
                temp = static_cast<node *>(temp->prevNode);

            }
            string path = currentNode->name + ": " + to_string(currentNode->sourceCost) + " [";
            for(auto const& cVertex : vertexList){
                path += (cVertex + ", ");
            }
            path.resize(path.size() - 2);
            path += "]";
            output << path << endl;
            vertexList.clear();
            path.clear();

        }

    }
}



