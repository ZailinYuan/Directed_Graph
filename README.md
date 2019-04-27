# Directed_Graph

Renew date:  04/26/2019

This is a directed weighted graph. It has basic functions like add vertexes and weighted edges, traverse all vertexes and edges, and record and print statictical information like number of vertexes / edges. Besides that, algorithms like Dijakstar's algorithm, Floyd - Warshall algorithm and topological sorting algorithms are also implementede in this graph. All functions and it's instructions are listed below:

Functions:

  1.
       // Print all vertexes in this graph to console:
       
       void printAllVer() const;  
      
  2.
       // Print all edges in this graph to console (includes weight of the edge):
       
       void printAllEdges() const;
       
  3.    // Traverse the graph by BFS from specified vertex and print to console:
        // Return 0 if the vertex specified does not exist:
        // Return 1 if the vertex specified exist:
        // Arg: string const &key is the starting vertex user specified.
        
        int DFS(string const &key) const;
        
        
  4.
        // Traverse the graph by DFS from specified vertex and print out to console:
        // Return 0 if the vertex specified does not exist:
        // Return 1 if the vertex specified exist:
        // Arg: string const &key is the starting vertex user specified.
        
        int DFS(string const &key) const;

  5. 
        // Add one vertex to graph:
        // Return 0 if successfully add one vertex;
        // Return 1 if the vertex is already there;
        // Return -1 if vertexes more or equal than N. Array overflow or other reasons.
        // Arg: name of the vertex to be added:
        
        int addVertex(string const &key);
        
   6.
        // Add one directed weighed edge from key1 to key2 to graph:
        // Return 1 if successfully add one edge;
        // Return 0 if edge already exist;
        // Return -1 if vertexes specified do not exist:
        // Arg: name of vertex start, name of vertex end, edge weight:
        
        int addEdge(string const &key1, string const &key2, int weight);

  7.
        // Remove a vertex from the graph:
        // Return 1 if success;
        // Return 0 if no such vertex:
        // Arg: the vertex to be removed:
        
        int eraseVer(string const &key);

  8.
        // Remove an edge (from key1 to key2) from the graph:
        // If edge does not exist, return 0;
        // else, remove and return 1:
        // Args: two vertexes that specify this edge:
        
        int eraseEdge(string const &key1, string const &key2);

  9.
        // Upgrade the weight of an edge (from key1 to key2):
        // Return 1 if successfully upgraded:
        // Return 0 if edge does not exist:
        // Arg: name of vertex start, name of vertex end, edge weight:
        
        int ugEdgeW(string const &key1, string const &key2, int weight) const;

  10.
        // Return number of vertexes in graph:
        
        int numOfVer() const;

  11.
        // Return number of edges in graph:
        
        int numOfEdge() const;

  12. 
        // Detect if a vertex has in-edges:
        // Return 1 if it does;
        // Return 0 if no in-edges:
        // Args: the vertex to be found
        
        int hasInEdges(string const &key) const;

  13.
        // Print all edges coming to the vertex specified:
        // Args: the vertex that is the destination:
        
        void inEdgesOF(string const &key) const;

  14.
        // Detect if an directed graph is cyclic or not:
        // Return 1 if the graph is cyclic;
        // Return 0 if not.
        // DFS based.
        
        bool isCyclic() const;

  15. 
        // Do topological Sort ion this graph:
        // If this graph is DAG, print vertexes in topological order;
        // If this graph is acyclic, show there is a cycle and print all
        // edges forming the cycle:
        // Return 1 if DAG;
        // Return 0 if acyclic:
        
        bool topoOrder_DFS() const;

  16.
        // Do topological Sorting on this graph:
        // If this graph is DAG, print vertexes in topological order to console;
        // If this graph is acyclic, show there is a cycle and print all edges forming the cycle to console;
        // Return 1 if DAG;
        // Return 0 if acyclic:
        
        bool topoOrder_BFS() const;

  17.
        // Check connnectivity of the graph:
        // Return 0 if not connected:
        // Return 1 if weakly connected:
        // Return 2 if strongly connected:
        
        int connectivity() const;

  18.
        // Check if the graph contains negative weighted edges:
        // Return 1 if negative edges in graph;
        // else return 0:
        
        int negativeEdge() const;

  19.
        // Dijkstar's algorithm finds out shortest distance from all vertexes to a specified vertex:
        // Return 0 if error happens:
        // else return 1:
        // Args: startVer is the vertex specified.
        
        int Dijkstra(string const &startVer) const;

  19.
        
        int DAG_Based_Distance(string const &key) const;/** to be done
                                    **/

  20.
        int Bellman_Ford(string const &key) const;/** to be done
                                    **/
  
  21.
        // This is a deep copy function of this graph; it creates a new graph and return its pointer:
        // Copy object g, return the pointer to it:
        
        dirGraph* copyOf() const;

  22.
        // Floyd - Warshall algorithm check the connectivity of each vertex to other vertexes;
        // Return a directed graph that is a transitive closure of specified directed graph g:
        
        dirGraph* Floyd_Warshall() const;


