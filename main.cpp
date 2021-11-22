#include <iostream>
#include <fstream>
#include <string>
#include "graph.h"
#include <ctime>

using namespace std;

string split(string phrase, int index){
    string firstWord;
    string secondWord;
    string thirdWord;
    int temp = 0;

    for(int i = 0; i < phrase.length(); i++)
    {
        if(phrase[i] == ' ' || phrase[i] == '\n')
        {
            temp = i;
            break;
        }
        firstWord += phrase[i];
    }
    for(int j = temp + 1; j < phrase.length(); j++){
        if(phrase[j] == ' ' || phrase[j] == '\n')
        {
            temp = j;
            break;
        }
        secondWord += phrase[j];
    }
    if(index == 0){
        return firstWord;
    }
    else if(index == 1){
        return secondWord;
    }
    else{
        for(int k = temp + 1; k <= phrase.length(); k++){

            if(phrase[k] == 0 || phrase[k] == ' ' || phrase[k] == '\n')
            {
                return thirdWord;
            }
            thirdWord += phrase[k];

        }
    }
    return "";
}


graph loadGraph(const string& filename){
    graph theGraph;
    string line;
    string temp;

    string source;
    string dest;
    int cost;

    ifstream input(filename);

    while(getline(input, line)){
        theGraph.addEdge(split(line, 0), split(line, 1), stoi(split(line, 2)));
    }
    return theGraph;
}

int main(){
    string inputFile;
    string startingVertex;
    string outputFile;

    graph myGraph = loadGraph("input.txt");

    myGraph.dijkstra("v1");

    myGraph.outputDijkstra("v1", "output.txt");


    /*
    cout << "Enter name of graph file: ";
    cin >> inputFile;
    cout << endl;
    graph givenGraph = loadGraph(inputFile);

    cout << "Enter name of starting vertex: " ;
    cin >> startingVertex;
    cout << endl;

    clock_t t1 = clock();
    givenGraph.Dijkstra(startingVertex);
    clock_t t2 = clock();
    double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;
    cout << "Total time (in seconds) to apply dijkstra's algorithm: " << timeDiff << endl;

    cout << "Enter name of output file: " << endl;
    cin >> startingVertex;
    cout << endl;
    */

}