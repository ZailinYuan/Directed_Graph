#ifndef __DIRGRAPH__
#define __DIRGRAPH__


/**
    Use an array of struct Node and Linked list of struct Node to implement directed graph.
    __Adjacent Array
**/

#include <iostream>
#include <string>
#include <cstdlib>
#include <queue>
#include <stack>

#define N 100

using namespace std;

class dirGraph
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
        Node* ver[N]; // Graph base;
        int numVer; // Vertexes number
        int numEdge; // Edge number

        // If key1 < key2, return 1;
        // If key1 = key2, return 0;
        // If key1 > key2, return -1:
        // ascending order:
        int compStrAscend(string const &key1, string const &key2) const;

        // If the key exist, return its index;
        // else return -1:
        int findVertex(string const &key, int left, int right) const;

        // Helper of DFS():
        void _DFS(string const &key, int isVisited[]) const;

        // Helper of eraseVer():
        void _eraseVer(Node* &head);

        // Helper of isCyclic() function:
        // Return true if cyclic;
        // Else return false.
        bool _isCyclic(string const &key, int isVisited[]) const;

        // Helper of topoOrder:
        // If this graph is DAG, print vertexes in topological order;
        // If this graph is acyclic, show there is a cycle and print all
        // edges forming the cycle:
        // Return 1 if DAG;
        // Return 0 if cyclic:
        bool _topoOrder(string const &start, int visited[], stack<string> &noSuccessor, queue<string> &loop) const;

        // Return number of vertexes by DFS:
        int countDFS(string const &key, int isVisited[]) const;

        // Called by topoOrder_BFS()
        // Gets predecessor information and stores them into dynamic array:
        void predeInfo(int predInfo[]) const;

        // De-constructor:
        void deconstruct(Node* head);



    public:
        // Constructor:
        dirGraph();

        // Copy constructor:
        dirGraph(const dirGraph& dg2);

        // De - constructor:
        ~dirGraph();

        // Used for testing private functions:
        void tester();

        // Print all vertexes in this graph:
        void printAllVer() const;

        // Print all edges in this graph:
        void printAllEdges() const;

        // Traverse the graph by BFS from specified vertex:
        // Return 0 if the vertex specified does not exist:
        // Return 1 if the vertex specified exist:
        int BFS(string const &key) const;

        // Traverse the graph by DFS from specified vertex:
        // Return 0 if the vertex specified does not exist:
        // Return 1 if the vertex specified exist:
        int DFS(string const &key) const;

        // Add one vertex to graph:
        // Return 0 if successfully add one vertex;
        // Return 1 if the vertex is already there;
        // Return -1 if vertexes more or equal than N.
        // Array overflow or other reasons.
        int addVertex(string const &key);

        // Add one directed edge from key1 to key2 to graph:
        // Return 1 if successfully add one edge;
        // Return 0 if edge already exist;
        // Return -1 if vertexes specified do not exist:
        int addEdge(string const &key1, string const &key2, int weight);

        // Remove a vertex from the graph:
        // Return 1 if success;
        // Return 0 if no such vertex:
        int eraseVer(string const &key);

        // Remove an edge (from key1 to key2) from the graph:
        // If edge does not exist, return 0;
        // else, remove and return 1:
        int eraseEdge(string const &key1, string const &key2);

        // Upgrade the weight of an edge (from key1 to key2):
        // Return 1 if successfully upgraded:
        // Return 0 if edge does not exist:
        int ugEdgeW(string const &key1, string const &key2, int weight) const;

        // Return number of vertexes in graph:
        inline int numOfVer() const {return numVer;};

        // Return number of edges in graph:
        inline int numOfEdge() const {return numEdge;};

        // Detect if a vertex has in-edges:
        // Return 1 if it does;
        // Return 0 if no in-edges:
        int hasInEdges(string const &key) const;

        // Print all edges coming to the vertex specified:
        void inEdgesOF(string const &key) const;

        // Return true if the graph is cyclic;
        // Return false if not.
        // DFS based.
        bool isCyclic() const;

        // Do topological Sort ion this graph:
        // If this graph is DAG, print vertexes in topological order;
        // If this graph is acyclic, show there is a cycle and print all
        // edges forming the cycle:
        // Return 1 if DAG;
        // Return 0 if acyclic:
        bool topoOrder_DFS() const;

        // Do topological Sort ion this graph:
        // If this graph is DAG, print vertexes in topological order;
        // If this graph is acyclic, show there is a cycle and print all
        // edges forming the cycle:
        // Return 1 if DAG;
        // Return 0 if acyclic:
        bool topoOrder_BFS() const;

        // Return 0 if not connected:
        // Return 1 if weakly connected:
        // Return 2 if strongly connected:
        int connectivity() const;

        // Return 1 if negative edges in graph;
        // else return 0:
        int negativeEdge() const;

        // Return 0 if error happens:
        // else return 1:
        int Dijkstra(string const &startVer) const;

        int DAG_Based_Distance(string const &key) const;/** to be done
                                    **/

        int Bellman_Ford(string const &key) const;/** to be done
                                    **/

        // Copy object g, return the pointer to it:
        // dirGraph* copyOf() const;

        // Return a directed graph that is a transitive closure of specified directed graph g:
        dirGraph* Floyd_Warshall() const;

};

#endif // __DIRGRAPH__
