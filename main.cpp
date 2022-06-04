/** 
* Elena Ballinas García A01173324
* Maria Fernanda De León A01197340

Fecha de creacion: 30 de mayo del 2022

* Ejemplo que implementa dos representaciones de Grafos
* (Matriz de adyacencia y Lista de adyacencia) y el 
* algoritmos BFS 
*
* Compilacion para debug:  
*    g++ -std=c++17 -g -o main *.cpp 
* Ejecucion con valgrind:
*    nix-env -iA nixpkgs.valgrind
*    valgrind --leak-check=full ./main < graph01.txt
*
* Compilacion para ejecucion:  
*    g++ -std=c++17 -O3 -o main *.cpp 
* Ejecucion:
*    ./main < graph01.txt
**/

#include <iostream>
#include <sstream>
#include "Graph.h"

int main() {
  std::cout << "Ejemplo de grafos (representaciones y DFS)!\n";
  std::stringstream inputInfo, inputInfoG3;;
  inputInfo << std::cin.rdbuf(); 
  inputInfoG3 << 0;
  // Construye un grafo a partir de la consola usando
  // representacion de Lista de adyacencia
  Graph g1(1, inputInfo);
  g1.printGraph();
  // Regresa a linea cero el archivo de entrada
  inputInfo.clear();
  inputInfo.seekg(0);
  // Construye un grafo a partir de la consola usando
  // representacion de Matriz de adyacencia
  Graph g2(2, inputInfo);
  g2.printGraph();
  // Algoritmo BFS iniciando en el nodo 1 del grafo g1
  g1.BFS(1);
  // Algoritmo BFS iniciando en el nodo 1 del grafo g2
  g2.BFS(1);
  // Algoritmo DFS iniciando en el nodo 1 del grafo g1
  g1.DFS(1);
  // Algoritmo DFS iniciando en el nodo 1 del grafo g2
  g2.DFS(1);

  //Copia un grafo
  Graph g3(1, inputInfoG3);
  g1.copyGraph(1, g3);
  g3.printGraph();
} 