//
// Created by Sohaib Bhatti on 11/20/2021.
//

#include "graph.h"
#include <iostream>
#include <fstream>


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

    // create a pseudo-node that stores info about the edge and pushes it to the source's adjacency list
    adjNode destPush;
    destPush.name = dest;
    destPush.cost = cost;
    destPush.nodeP = destNode;
    sourceNode->adjList.push_back(destPush);


}

void graph::printGraph(){
    for(auto const& currentNode : masterList){
        cout << endl << "VERTEX: " << currentNode->name << endl;
        for(auto const& currentNode1 : currentNode->adjList){
            cout << "CONNECTED VERTEX: " << currentNode1.name << " (" << currentNode1.cost << ")" << endl;
        }
    }
}

void graph::dijkstra(const string& start){
    int noVertices = masterList.size();
    heap dijkstraHeap(noVertices);
    for (auto const& currentNode : masterList){
        currentNode->sourceCost = INT_MAX;
        currentNode->known = false;
    }
    node *source = static_cast<node *> (vertexNames.getPointer(start));
    source->sourceCost = 0;
    source->prevNode = nullptr;
    source->known = true;
    dijkstraHeap.insert(source->name, source->sourceCost, source);

    node *temp = nullptr;
    string stringTmp;
    int cost;

    while(noVertices > 0){
        dijkstraHeap.deleteMin(&stringTmp, &cost, temp);
        if(!temp->known){
            temp->known = true;
            for (auto const &currentAdjNode: temp->adjList) {
                if ((temp->sourceCost + currentAdjNode.cost) < static_cast<node *>(currentAdjNode.nodeP)->sourceCost) {
                    static_cast<node *>(currentAdjNode.nodeP)->sourceCost = temp->sourceCost + currentAdjNode.cost;
                    static_cast<node *>(currentAdjNode.nodeP)->prevNode = temp;
                    dijkstraHeap.insert(static_cast<node *>(currentAdjNode.nodeP)->name,
                                        static_cast<node *>(currentAdjNode.nodeP)->sourceCost,
                                        currentAdjNode.nodeP);
                }
            }
            noVertices--;
        }


    }
}

void graph::outputDijkstra(const string& start, const string& filename){
    node * temp;
    list<string> vertexList;
    for(auto const& currentNode : masterList){
        ofstream output(filename);
        if(currentNode->prevNode == nullptr){
            output << currentNode->name << ": NO PATH" << endl;
        }
        else{
            temp = static_cast<node *>(currentNode->prevNode);
            while(true){
                if(temp->name == start){
                    break;
                }
                vertexList.push_front(temp->name);
                temp = static_cast<node *>(temp->prevNode);

            }
            output << currentNode->name << ": " << currentNode->sourceCost << " [";
            for(auto const& cVertex : vertexList){
                output << cVertex << ", ";
            }
            output << "]" << endl;
        }

    }
}


