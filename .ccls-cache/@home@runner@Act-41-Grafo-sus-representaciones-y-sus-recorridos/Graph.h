#ifndef __GRAPH_H_
#define __GRAPH_H_
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include "LinkedList.h"
#include "QueueLinkedList.h"

class Graph {
  private:
    int numNodes;
    int numEdges;
    int representation; // 1 Adjacency list; 2 Adjacency matrix
    // Matriz de adyacencia (vector de vectores) 
    std::vector<std::vector<int>> adjMatrix;
    // Lista de adyacencia (vector de listas)
    std::vector<LinkedList<int>> adjList;

    void loadGraphList(std::istream& input);
    void loadGraphMatrix(std::istream& input);
    void split(std::string line, std::vector<int> & res);
    void printAdjList();
    void printAdjMatrix();

  
  public:
    Graph(int representacion, std::istream& input);
    ~Graph();
    void printGraph();
    void BFS(int v);


};




#endif // __GRAPH_H_