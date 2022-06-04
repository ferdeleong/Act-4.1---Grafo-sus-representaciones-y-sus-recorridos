#include "Graph.h"

//Complejidad: O(1) solo se manda a llamar la funcion 
Graph::Graph(int representa, std::istream& input) {
    if (representa == 1) {
      loadGraphList(input);
      representation = 1;
    }
    else {
      loadGraphMatrix(input);
      representation = 2;
    }
}

//Complejidad: O(n) porque se destruye cada nodo
Graph::~Graph() {
  if (representation == 1)
    adjList.clear();
  else
    adjMatrix.clear();
}

//Complejidad:
void Graph::loadGraphMatrix(std::istream& input) {
    std::string line;
    int i = 0;
    while (std::getline(input, line)) {
      if (i == 0) {
        i++;
        continue;
      }
      if (i == 1) {
        std::vector<int> res;
        split(line, res);
        numNodes = res[0];
        numEdges = res[2];
        // Reservar memoria para los renglones de la matriz de adyacencia
        adjMatrix.resize(numNodes+1);
        // Declara un vector de numNodes elementos en cada renglon (renglon 0 no utilizado) 
        for (int k = 1; k <= numNodes; k++) {
          std::vector<int> tmpVector(numNodes+1, 0);
          adjMatrix[k] = tmpVector; 
        }
        i++;
        continue; 
      }
      std::vector<int> res;
      split(line, res);
      int u = res[0];
      int v = res[1];
      // Grafos no dirigidos agrega aristas (u,v) y (v,u) 
      adjMatrix[u][v] = 1;
      adjMatrix[v][u] = 1;
      i++;
    }
}

//Complejidad:
void Graph::loadGraphList(std::istream& input) {
    std::string line;
    int i = 0;
    while (std::getline(input, line)) {
      if (i == 0) {
        i++;
        continue;
      }
      if (i == 1) {
        std::vector<int> res;
        split(line, res);
        numNodes = res[0];
        numEdges = res[2];
        // Reservar memoria para los renglones de la lista de adyacencia (renglon 0 no utilizado) 
        adjList.resize(numNodes+1);
        // Declara una lista vacia para cada renglon y la almacena en el vector
        for (int k = 1; k <= numNodes; k++) {
          LinkedList<int> tmpList;
          adjList[k] = tmpList; 
        }
        i++;
        continue; 
      }
      std::vector<int> res;
      split(line, res);
      int u = res[0];
      int v = res[1];
      // Grafos no dirigidos agrega aristas (u,v) y (v,u)       
      adjList[u].addLast(v);
      adjList[v].addLast(u);
      i++;
    }
  }

//Complejidad:
void Graph::split(std::string line, std::vector<int> & res) {
    size_t strPos = line.find(" ");
    size_t lastPos = 0;
    while (strPos != std::string::npos) {
      res.push_back(stoi(line.substr(lastPos, strPos - lastPos)));
      lastPos = strPos + 1;
      strPos = line.find(" ", lastPos);
    }
    res.push_back(stoi(line.substr(lastPos, line.size() - lastPos)));
}

//Complejidad: O(n) porque se visitan todos los nodos 
void Graph::printAdjList(){
	  std::cout << "Adjacency List" << std::endl;
		for (int i = 1; i <= numNodes; i++){
	        std::cout << "vertex " << i << ": ";
	        adjList[i].printList();
    }
}

//Complejidad: O(n) porque se visitan todos los nodos 
void Graph::printAdjMatrix(){
    std::cout << "Adjacency Matrix" << std::endl;
		for (int i = 1; i <= numNodes; i++){
	        std::cout << "vertex " << i << ": ";
	        for (int j = 1; j <= numNodes; j++){
							 std::cout << " " << adjMatrix[i][j];
					}
	        std::cout << std::endl;
    }
}

//Complejidad: O(1) solo se manda a llamar la funcion 
void Graph::printGraph() {
  if (representation == 1)
    printAdjList();
  else
    printAdjMatrix();
}

//Complejidad:  O(V+E) where V is vertices and E is edges
void Graph::BFS(int v) {
  // Declaramos un set del STL de C++ (elementos unicos y ordenados)
  std::set<int> visited;
  // Creamos una queue 
  QueueLinkedList<int> queue;
  // Marcamos el vertice actual v como visitado y entra al queue
  visited.insert(v);
  queue.enqueue(v);
  std::cout << "Recorrido BFS " << std::endl;
  while(!queue.isEmpty()) {
    // Extraemos un vertice del queue y lo procesamos (print) 
    v = queue.dequeue();
    std::cout << v << " ";
    // Obtenemos los vertices adyacentes del vertice v
    // Si estos no han sido visitados entonces se marcan como visitados
    // y los metemos al queue
    if (representation == 1) { // Lista de adyacencia
      // Recorrer nodos adyacentes de v
      for (int j = 0; j < (int)adjList[v].getNumElements(); j ++) {
        int u = adjList[v].getData(j);
        // Verifica si u ya fue visitado en tiempo O(log n)
        bool isInVisited = visited.find(u) != visited.end();
        if (!isInVisited) {
          visited.insert(u);
          queue.enqueue(u);
        }
      }
    }
    else { // Matriz de adyacencia
      // Recorrer nodos adyacentes a v
      for (int u = 1; u <= numNodes; u++) {
        int c = adjMatrix[v][u];
        if (c != 0) {
          // Verifica si u ya fue visitado en tiempo O(log n)
          bool isInVisited = visited.find(u) != visited.end();
          if (!isInVisited) {
            visited.insert(u);
            queue.enqueue(u);
          }
        }
      }
    }
  }
  std::cout << std::endl;
}

//Complejidad: O(V+E) where V is vertices and E is edges
void Graph::DFS(int v) {
  // Declaramos un set del STL de C++ (elementos unicos y ordenados)
  std::set<int> visited;
  // Creamos una Stack 
  StackLinkedList<int> stack;
  // Marcamos el vertice actual v como visitado y entra al queue
  visited.insert(v);
  stack.push(v);
  std::cout << "Recorrido DFS " << std::endl;
  while(!stack.isEmpty()) {
    // Extraemos un vertice del queue y lo procesamos (print) 
    v = stack.getTop();
    stack.pop();
    std::cout << v << " ";
    // Obtenemos los vertices adyacentes del vertice v
    // Si estos no han sido visitados entonces se marcan como visitados
    // y los metemos al queue
    if (representation == 1) { // Lista de adyacencia
      // Recorrer nodos adyacentes de v
      for (int j = 0; j < (int)adjList[v].getNumElements(); j ++) {
        int u = adjList[v].getData(j);
        // Verifica si u ya fue visitado en tiempo O(log n)
        bool isInVisited = visited.find(u) != visited.end();
        if (!isInVisited) {
          visited.insert(u);
          stack.push(u);
        }
      }
    }
    else { // Matriz de adyacencia
      // Recorrer nodos adyacentes a v
      for (int u = 1; u <= numNodes; u++) {
        int c = adjMatrix[v][u];
        if (c != 0) {
          // Verifica si u ya fue visitado en tiempo O(log n)
          bool isInVisited = visited.find(u) != visited.end();
          if (!isInVisited) {
            visited.insert(u);
            stack.push(u);
          }
        }
      }
    }
  }
  std::cout << std::endl;
  
}

//Complejidad: O(n) porque se visitan todos los nodos 
void Graph::copyGraph(int r, Graph &res) {
  res.numNodes = numNodes;
  res.numEdges = numEdges;
  res.representation = r;
  // copiar de lista a lista
  if (representation == 1 && r == 1) {
    res.adjList.resize(numNodes + 1);
    for (int k = 1; k <= numNodes; k++) {
      LinkedList<int> newList;
      res.adjList[k] = newList;
      LLNode<int> *ptr = adjList[k].getHead();
      while (ptr != nullptr) {
        res.adjList[k].addLast(ptr->data);
        std::cout << ptr->data << " ";
        ptr = ptr->next;
      }
    }
  }
}


