#ifndef __UNDIR_WEIGHTED_GRAPH__
#define __UNDIR_WEIGHTED_GRAPH__


#include <iostream>
#include <string>
#include <cstdlib>

#define N 100

using namespace std;

class UWGraph
{
    struct Node
        {
            string key;
            struct Node* next;
            int weight;

            Node(string key);
            Node(string key, int weight);
        };

    private:

        Node* ver[N]; // Can not change externally

        int numVer; // Can not change externally
        int numEdge; // Can not change externally


        // If key1 < key2, return 1; if key1 = key2, return 0; if key1 > key2, return -1:
        // ascending order:
        int compStr1(string key1, string key2) const;

        // If the key exist, return its index; else return -1:
        int findVertex(string key, int left, int right) const;

        // Return 1 if edge already exist; return -1 if no such two vertexes; return 0 if
        // add edge normally:
        int findEdge(string key1, string key2) const;

        // Used by DFS():
        // Return number of vertexes visited:
        void _DFS(int keyIndex, int visited[]) const;

        // Used by isAcyclic():
        // Arguments: visited[] - record of which key is visited.
        // Arguments: rootKey - the parent key of all children to search.
        // Return true if acyclic; else return false.
        bool _isAcyclicDFS(int rootKey, int justVisisted, int visited[]) const;

        // Return 1 if the graph is connected; else return 0:
        // Return -1 if bug happens:
        // Return number of vertexes visited.
        // Used by isConnect(); compare return value and numVer to determine if the graph is
        // connected.
        int _connectedDFS(int rootKey, int isVisited[]) const;

        // Used for deconstructor:
        void deconstruct(Node* head);


    public:

        UWGraph(); // constructor
        UWGraph(const UWGraph& udg); // Copy constructor
        ~UWGraph(); // deconstructor

        // This function is used for testing private functions:
        void test();

        // Return 1 if already exist; return -1 if array is full; return 0 if need insert:
        int addVertex(string key);

        // If edge exist, return 1; else return 0; else if can't add, return -1:
        int addEdge(string key1, string key2, int weight);

        // Return 1 if erase success, else return 0:
        int eraseEdge(string key1, string key2);

        // Return 1 if erase success, else return 0:
        int eraseVer(string key);

        // Return how many vertexes in the graph:
        int numOfVer() const;

        // Return how many edges in the graph:
        int numOfEdge() const;

        // Print all vertexes:
        void printAllVer() const;

        // Print all edges:
        void printAllEdge() const;

        // Print edge and its weight:
        void printEdge(string key1, string key2) const;

        // Print all adjacent of specified vertex.
        // If vertex specified doesn't exist, cout:
        void printAllAdjacent(string key) const;

        // Traverse the graph by BFS:
        void BFS(string key) const;

        // Traverse the graph by DFS:
        // Return number of vertexes visited:
        void DFS(string key) const;

        // Return true if the graph is acyclic; else return false:
        bool isAcyclic() const;

        // Dijkstra' Algorithm to find all shortest path to specified vertex:
        // Argument: startKey - specified vertex to start.
        void Dijkstra(string startKey) const;

        // Return 1 if the graph is connected; else return 0:
        // Rely on _connectDFS();
        int isConnected() const;

        // Detect if there is any negative edges in the graph:
        // Return 1 if there is any negative edges; else return false:
        int negativeEdge() const;

};

#endif // __UNDIR_WEIGHTED_GRAPH__
