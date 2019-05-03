#include <iostream>
#include <string>
#include <cstdlib>
#include <queue>
#include <stack>
#include <vector>
#include <climits>
#include <memory.h>

#include "dirGraph.h"
#include "undirWeightedG.h"
#include "minHeap.h"

#define M INT_MAX

using namespace std;

/** Node constructors:
**/
dirGraph::Node::Node(string key): key(key), next(NULL), weight(0)
{

}

dirGraph::Node::Node(string key, int weight): key(key), next(NULL), weight(weight)
{

}


/** Graph constructors:
**/
dirGraph::dirGraph()
{
    for(int i=0; i<N; i++){
        this->ver[i] = NULL;
    }

    this->numVer = 0;
    this->numEdge = 0;
}

dirGraph::~dirGraph()
{
    for(int i=0; i<numVer; i++){
        deconstruct(ver[i]);
    }
}


/** Public tester function:
**/

void dirGraph::tester()
{

}


/** Private functions:
**/

// If key1 < key2, return 1;
// If key1 = key2, return 0;
// If key1 > key2, return -1:
// ascending order:
int dirGraph::compStrAscend(string const &key1, string const &key2) const
{
    int key1Length = key1.length();
    int key2Length = key2.length();

    // Compare characters one by one:
    for(int i=0; i<min(key1Length,key2Length); i++){
        if(key1[i] == key2[i]){
            continue;
        }
        else if(key1[i] < key2[i]){
            return 1;
        }
        else{
            return -1;
        }
    }

    // Continue Compare by compare length:
    if(key1Length == key2Length){
        return 0;
    }
    else if(key1Length < key2Length){
        return 1;
    }
    else{
        return -1;
    }
}

// If the key exist, return its index;
// else return -1:
int dirGraph::findVertex(string const &key, int left, int right) const
{
    int mid = (left + right)/2;

    if(left > right){
        return -1;
    }

    int alphaOrder = compStrAscend(key, ver[mid]->key);

    if(alphaOrder == 0){
        return mid;
    }
    else if(alphaOrder == 1){
        return findVertex(key, left, mid-1);
    }
    else{
        return findVertex(key, mid+1, right);
    }

}

// Helper of DFS():
void dirGraph::_DFS(string const &key, int isVisited[]) const
{
    int k = findVertex(key,0,numVer-1);

    // check if the vertex already been visited;
    // if not, print:
    if(isVisited[k] == 1)
    {
        return;
    }
    else
    {
        cout << "Vertex: " << ver[k]->key << endl;
        isVisited[k] = 1;
    }

    // search for all its children:
    Node* finder = ver[k]->next;
    while(finder != NULL)
    {
        _DFS(finder->key, isVisited); // recursion
        finder = finder->next;
    }

    return;
}

void dirGraph::_eraseVer(Node* &head)
{
    if(head == NULL)
    {
        return;
    }

    _eraseVer(head->next);
    delete head;
    numEdge--;

    return;
}

// Helper of isCyclic() function:
// Return true if cyclic;
// Else return false.
// DFS based:
bool dirGraph::_isCyclic(string const &key, int isVisited[]) const
{
    // Get vertex's position in the graph;
    int k = findVertex(key,0,numVer-1);

    //
    if(isVisited[k] == 0) // Not visited yet.
    {
        // Mark as visited:
        isVisited[k] = 1;

        // Variable to return:
        bool toReturn = false;

        // search all successor:
        Node* finder = ver[k]->next;
        while(finder != NULL)
        {
            // One return a true, then final result will be true:
            toReturn = _isCyclic(finder->key, isVisited) || toReturn;

            // Cycle detected:
            if(toReturn)
            {
                return true;
            }

            // Search next successor:
            finder = finder->next;
        }

        // Done searching this round, mark as done!
        isVisited[k] = 2;

        // If no cycle detected, return false:
        return false;
    }
    else if(isVisited[k] == 1) // Run into vertex we just searched, cycle detected!
    {
        return true;
    }
    else // isVisited[k] == 2: // Already searched in last rounds, just return false.
    {
        return false;
    }
}

// Helper of topoOrder:
// If this graph is DAG, print vertexes in topological order;
// If this graph is acyclic, show there is a cycle and print all
// edges forming the cycle:
// Return true if DAG;
// Return false if cyclic:
bool dirGraph::_topoOrder(string const &start, int visited[], stack<string> &noSuccessor, queue<string> &loop) const
{
    int k = findVertex(start,0,numVer);

    // Not visited case:
    if(visited[k] == 0) // Not visited:
    {
        visited[k] = 1; // mark as visited.

        // search children:
        Node* finder = ver[k]->next;
        while(finder != NULL)
        {
            if(_topoOrder(finder->key, visited, noSuccessor, loop) == false)
            {
                return false;
            }
            finder = finder->next;
        }

        visited[k] = 2;
        noSuccessor.push(start);
        return true;
    }
    // Visited in current loop case:
    else if(visited[k] == 1) // visited current loop.
    {
        if(!loop.empty() && start == loop.front())
        {
            string tail = "";
            string head = "";

            while(!loop.empty())
            {
                tail = loop.front();
                loop.pop();

                if(!loop.empty())
                {
                    head = loop.front();
                }
                else
                {
                    head = start;
                }

                cout << "\tCycle edges: " << tail << " --------->" << head << endl;
            }

            return false; // cycle detected and print out.
        }

        loop.push(ver[k]->key); // push cycle vertexes.

        Node* finder = ver[k]->next;
        while(finder != NULL)
        {
            if(_topoOrder(finder->key, visited, noSuccessor, loop) == false)
            {
                return false;
            }

            finder = finder->next;
        }
        return true;
    }
    // Finished in last loop case:
    else // closed in previous loops.
    {
        return true;
    }
}

// Helper of connectivity:
// Return number of vertexes by DFS:
int dirGraph::countDFS(string const &key, int isVisited[]) const
{
    int k = findVertex(key,0,numVer-1);

    // check if the vertex already been visited;
    // if not, print:
    if(isVisited[k] == 1)
    {
        return 0;
    }
    else
    {
        isVisited[k] = 1; // mark as visited.

        int totolNum = 1; // 1 for one vertex.
        // search for all its children:
        Node* finder = ver[k]->next;
        while(finder != NULL)
        {
            totolNum = countDFS(finder->key, isVisited) + totolNum; // recursion
            finder = finder->next;
        }
        return totolNum;
    }
}

// Called by topoOrder_BFS()
// Gets predecessor information and stores them into dynamic array:
void dirGraph::predeInfo(int predInfo[]) const
{
    // Set Dynamic array zero;
    memset(predInfo,0,(numVer << 2));

    // Search for every edge to calculate number of predecessors.
    for(int i=0; i<numVer; i++)
    {
        // Search successors of each vertex:
        Node* finder = ver[i]->next;
        while(finder != NULL)
        {
            // Get successor vertex index in this graph:
            int k = findVertex(finder->key,0,numVer-1);

            //cout << "This: " << k << endl;

            // Mark the successor index with number of its predecessors:
            predInfo[k]++; // element of predInfo stores predecessors numbers of each vertex.

            // Next successor:
            finder = finder->next;
        }
    }

    /** Now all info about vertexes' predecessor had been stored in predInfo.
    **/

    return;
}


void dirGraph::deconstruct(Node* head)
{
    if(head == NULL){
        return;
    }

    deconstruct(head->next);
    delete head;

    return;
}


/** Public Functions:
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
**/

// Print all vertexes:
void dirGraph::printAllVer() const
{
    for(int i=0; i<numVer; i++)
    {
        cout << "\tVertex: " << ver[i]->key << endl;
    }

    return;
}

// Print all edges:
void dirGraph::printAllEdges() const
{
    for(int i=0; i<numVer; i++)
    {
        Node* finder = ver[i]->next;
        while(finder != NULL)
        {
            cout << "\tEdge: " << ver[i]->key << " ---------> " << finder->key << "\t" << "Distance: " << finder->weight << endl;
            finder = finder->next;
        }
    }

    return;
}

// Traverse the graph by BFS from specified vertex:
// Return 0 if the vertex specified does not exist:
// Return 1 if the vertex specified exist:
int dirGraph::BFS(string const &key) const
{
    int visiting = findVertex(key,0,numVer-1);
    std::queue<int> q;
    int isVisited[numVer] = {0}; // 0 indicate the vertex not visited; i indicate visited.

    if(visiting == -1)
    {
        return 0;
    }

    // Enqueue the starting Vertex:
    q.push(visiting);
    cout << "Vertex: " << ver[visiting]->key << endl;
    isVisited[visiting] = 1;

    // BFS display:
    while(!q.empty())
    {
        visiting = q.front();
        q.pop();

        Node* adjs = ver[visiting]->next;
        while(adjs != NULL)
        {
            int adjK = findVertex(adjs->key,0,numVer-1);

            if(isVisited[adjK] == 0)
            {
                q.push(adjK);
                cout << "Vertex: " << ver[adjK]->key << endl;
                isVisited[adjK] = 1;
            }
            adjs = adjs->next;
        }
    }
    return 1;
}

// Traverse the graph by DFS from specified vertex:
// Return 0 if the vertex specified does not exist:
// Return 1 if the vertex specified exist:
int dirGraph::DFS(string const &key) const
{
    int isVisited[numVer] = {0}; // 0 if not visited, else 1.
    int k = findVertex(key,0,numVer-1);

    // check if input is valid:
    if(k == -1)
    {
        return 0;
    }
    else
    {
        _DFS(key, isVisited);
        return 1;
    }
}

// Add one vertex to graph:
// Return 0 if successfully add one vertex;
// Return 1 if the vertex is already there;
// Return -1 if vertexes more or equal than N.

// Algorithm: Binary search:
int dirGraph::addVertex(string const &key)
{
    // Overflow case:
    if(numVer >= N)
    {
        return -1;
    }

    // Void array:
    if(numVer == 0)
    {
        ver[0] = new Node(key);
        numVer++;
        return 0;
    }

    // Already have vertex: locate new key in the array:
    int left = 0; // Range of array contain vertexes.
    int right = numVer-1; // Range of array contain vertexes.
    int mid = (left + right)/2; // find middle.

    while(left < mid)
    {
        int compare = compStrAscend(key, ver[mid]->key);

        if(compare == 0)
        {
            return 1;
        }
        else if(compare == 1)
        {
            right = mid - 1;
            mid = (left + right)/2;
        }
        else
        {
            left = mid + 1;
            mid = (left + right)/2;
        }
    }

    int pos = -1;

    if(left == right) // Theoretically no need to check if left == right.
    {
        int compare = compStrAscend(key, ver[mid]->key);

        if(compare == 0)
        {
            return 1;
        }
        else if(compare == 1)
        {
            pos = mid; // position on array to insert new key.
        }
        else
        {
            pos = mid + 1; // position on array to insert new key.
        }
    }
    else if(left < right)
    {
        int compare1 = compStrAscend(key, ver[mid]->key);
        int compare2 = compStrAscend(key, ver[mid + 1]->key);

        if(compare1 == 0 || compare2 == 0)
        {
            return 1;
        }

        if(compare1 == 1)
        {
            pos = mid;
        }
        else if(compare1 == -1 && compare2 == 1)
        {
            pos = mid + 1;
        }
        else
        {
            pos = mid + 2;
        }
    }

    for(int i=numVer; i>pos; i--) // reallocate elements in the array.
    {
        ver[i] = ver[i - 1];
    }

    ver[pos] = new Node(key);
    numVer++;
    return 0;
}

// Add one directed edge from key1 to key2 to graph:
// Return 1 if successfully add one edge;
// Return 0 if edge already exist;
// Return -1 if vertexes specified do not exist:
int dirGraph::addEdge(string const &key1, string const &key2, int weight)
{
    int k1 = findVertex(key1,0,numVer-1);
    int k2 = findVertex(key2,0,numVer-1);

    if(k1 == -1 || k2 == -1)
    {
        return -1;
    }

    Node* finder = ver[k1];
    while(finder->next != NULL)
    {
        if(finder->next->key == key2)
        {
            return 0;
        }
        else if(compStrAscend(key2, finder->next->key) == 1) // new key is smaller.
        {
            register Node* tmp = finder->next;
            finder->next = new Node(key2, weight);
            numEdge++;
            finder->next->next = tmp;
            return 1;
        }
        else
        {
            finder = finder->next;
        }
    }

    finder->next = new Node(key2, weight);
    numEdge++;
    return 1;
}

// Remove a vertex from the graph:
// Return 1 if success;
// Return 0 if no such vertex:
int dirGraph::eraseVer(string const &key)
{
    int k = findVertex(key,0,numVer-1);

    // check if vertex exist:
    if(k == -1)
    {
        return 0;
    }

    // Remove all outgoing edges of this vertex:
    _eraseVer(ver[k]->next);

    // Remove this vertex:
    delete ver[k];

    // Reallocate this vertex array;
    for(int i=k; i<numVer; i++)
    {
        ver[i] = ver[i+1];
    }

    // Decrease numVer:
    numVer--;

    return 1;
}

// Remove an edge (from key1 to key2) from the graph:
// If edge does not exist, return 0;
// else, remove and return 1:
int dirGraph::eraseEdge(string const &key1, string const &key2)
{
    int k1 = findVertex(key1,0,numVer-1);
    int k2 = findVertex(key2,0,numVer-1);

    if(k1 == -1 || k2 == -1)
    {
        return 0;
    }

    Node* finder = ver[k1];
    while(finder->next != NULL)
    {
        if(finder->next->key == key2)
        {
            register Node* tmp = finder->next;
            finder->next = finder->next->next;
            delete tmp;
            numEdge--;
            return 1;
        }
        finder = finder->next;
    }

    return 0;
}

// Upgrade the weight of an edge (from key1 to key2):
// Return 1 if successfully upgraded:
// Return 0 if edge does not exist:
int dirGraph::ugEdgeW(string const &key1, string const &key2, int weight) const
{
    int k1 = findVertex(key1,0,numVer-1);
    int k2 = findVertex(key2,0,numVer-1);

    if(k1 == -1 || k2 == -1)
    {
        return 0;
    }

    Node* finder = ver[k1]->next;
    while(finder != NULL)
    {
        if(finder->key == key2)
        {
            finder->weight = weight;
            return 1;
        }
        finder = finder->next;
    }

    return 0;
}

// Return how many vertexes in this graph:
int dirGraph::numOfVer() const
{
    return numVer;
}

// Return how many edges in this graph:
int dirGraph::numOfEdge() const
{
    return numEdge;
}

// Detect if a vertex has in-edges:
// Return 1 if it does;
// Return 0 if no in-edges:
int dirGraph::hasInEdges(string const &key) const
{
    //  Search whole graph, if an edge to key is found, return 1:
    for(int i=0; i<numVer; i++)
    {
        Node* finder  = ver[i]->next;

        while(finder != NULL)
        {
            if(finder->key == key)
            {
                return 1;
            }
            finder = finder->next;
        }
    }

    // edge to key not found, return 0;
    return 0;
}

// Return 1 if the graph is cyclic;
// Return 0 if not.
// DFS based.
bool dirGraph::isCyclic() const
{
    // Record of statues of vertexes: visited or not:
    // If not visited, mark as 0;
    // If visited in current search, mark as 1;
    // If visited in last searches, mark as 2.
    // Initialized to zero.
    int* isVisited = new int[numVer]();

    // Record of vertexes' predecessors:
    // 0: no predecessor;
    // 1: predecessor.
    int* predecessor = new int[numVer]();

    // Find out vertexes having predecessor:
    for(int i=0; i<numVer; i++)
    {
        Node* finder = ver[i]->next;
        while(finder != NULL)
        {
            predecessor[findVertex(finder->key,0,numVer-1)] = 1; // mark as having predecessor.
            finder = finder->next;
        }
    }

    // If no vertex without predecessor, true:
    bool noPredecessorCycle = true;

    // Search vertexes without predecessor and using as a start vertex:
    for(int i=0; i<numVer; i++)
    {
        if(predecessor[i] == 0)
        {
            // We have vertex without predecessor, put it false:
            noPredecessorCycle = false;

            // Detect if there are inner cycle (has vertex without predecessor but still has a cycle):
            if(_isCyclic(ver[i]->key, isVisited)) // Inner cycle detected.
            {
                return true;
            }
        }
    }

    // Determine cyclic or not:
    if(noPredecessorCycle)
    {
        // no predecessor cycle detected, return true:
        return true;
    }
    else
    {
        // No no - predecessor - cycle, and no inner cycle, return false:
        return false;
    }
}

// Do topological Sort on this graph:
// If this graph is DAG, print vertexes in topological order;
// If this graph is acyclic, show there is a cycle and print all
// edges forming the cycle:
// Return true if DAG;
// Return false if cyclic:
bool dirGraph::topoOrder_DFS() const
{
    int visited[numVer] = {0}; // label if a vertex is visited. 0: not visited; 1: visited; 2: visited and closed.
    stack<string> noSuccessor; // store the highest priority vertex right now.
    queue<string> loop; // store vertexes in a loop.
    int noPredecessor[numVer] = {0}; // 0 if no predecessor; else 1;
    string start = ""; // Pick up a arbitrary vertex to start.

    // find out all vertex without predecessor.
    for(int i=0; i<numVer; i++)
    {
        Node* finder = ver[i]->next;
        while(finder != NULL)
        {
            noPredecessor[findVertex(finder->key,0,numVer-1)] = 1; // mark as having predecessor.
            finder = finder->next;
        }
    }

    int anyNoPredecessorVer = 0; // 0 indicates that every vertex has predecessor.

    // check if vertex with on predecessor exists:
    for(int i=0; i<numVer; i++)
    {
        if(noPredecessor[i] == 0)
        {
            anyNoPredecessorVer = 1; // vertex without predecessor exist!
            start = ver[i]->key;

            if(_topoOrder(start, visited, noSuccessor, loop) == false)// false if cyclic.
            {
                return false;
            }
        }
    }

    // If no vertex without predecessor found:
    if(anyNoPredecessorVer == 0)
    {
        start = ver[0]->key; // pick up arbitrary vertex in this case.
        if(_topoOrder(start, visited, noSuccessor, loop) == false) // This case must be false.
        {
            return false;
        }
    }

    // Acyclic, pop all vertexes:
    int i=0;
    while(!noSuccessor.empty())
    {
        cout << "\t" << noSuccessor.top() << "\tTopological order  " << i << endl;
        noSuccessor.pop();
        i++;
    }

    return true;
}

// Do topological Sort ion this graph:
// If this graph is DAG, print vertexes in topological order;
// If this graph is acyclic, show there is a cycle and print all
// edges forming the cycle:
// Return true if DAG;
// Return false if cyclic:
// Using dynamic array:
bool dirGraph::topoOrder_BFS() const
{
    // Dynamic array used to store predecessor info of each vertex:
    int* predInfo = new int[numVer]();  // O(v + e)

    // Record of topological order:
    // Index = topological order:
    int* order = new int[numVer]();

    // Get the predecessor info:
    predeInfo(predInfo);

    // Check if the graph has cycle:
    if(isCyclic())
    {
        // Return false if cyclic:
        // Nothing will be printed on console:
        return false;
    }

    /** Topological order is the order that these vertexes been pushed into the queue:
        This algorithm put vertexes without predecessor to the queue all at one round.
    **/

    // Now, enqueue all vertexes without predecessor:
    queue<int> q;

    for(int i=0; i<numVer; i++)
    {
        if(predInfo[i] == 0)
        {
            q.push(i); // Here, i indicates the position of vertex in the graph.
        }
    }

    // Block of int i:
   {
       // Get and Record topological order:
        register int i = 0;

        // Dequeue if queue is not empty:
        while(!q.empty())
        {
            // Search successors of popped vertex:
            Node* finder = ver[q.front()]->next;
            while(finder != NULL)
            {
                // Successor number:
                int k = findVertex(finder->key,0,numVer-1);

                // Decrease number of predecessor:
                // Push vertex without predecessor:
                if(--predInfo[k] == 0)
                {
                    q.push(k);
                }

                // continue search;
                finder = finder->next;
            }

            // Records topological order:
            order[i] = q.front();

            // Pop:
            q.pop();

            // increment topological order:
            i++;
        }
   }

    // Print out topological order;
    for(int i=0; i<numVer; i++)
    {
        // Print to console in a format:
        cout << ver[order[i]]->key << "\tTopological Order: " << i << endl;
    }

    // Free memory space:
    for(int i=0; i<numVer; i++)
    {
        delete (predInfo + i);
        delete (order + i);
    }

    // Return true if acyclic:
    return true;
}

// Return 0 if not connected:
// Return 1 if weakly connected:
// Return 2 if strongly connected:
int dirGraph::connectivity() const
{
    UWGraph ug; // undirected graph;

    // create corresponding undirected graph:
    for(int i=0; i<numVer; i++)
    {
        ug.addVertex(ver[i]->key);
    }

    for(int i=0; i<numVer; i++)
    {
        Node* finder  = ver[i]->next;
        while(finder != NULL)
        {
            if(compStrAscend(ver[i]->key, finder->key) != 0) // just for speed.
            {
                ug.addEdge(ver[i]->key, finder->key, 1); // 1 is arbitrary weight of edge.
            }
            finder = finder->next;
        }
    }

    //
    if(ug.isConnected() == 0) // Not even weakly connected:
    {
        return 0;
    }
    else // weakly connected, test if strongly connected:
    {
        // Build a new directed graph with opposite direction edges:
        dirGraph dg;

        for(int i=0; i<numVer; i++)
        {
            dg.addVertex(ver[i]->key);
        }
        for(int i=0; i<numVer; i++)
        {
            Node* finder = ver[i]->next;
            while(finder != NULL)
            {
                dg.addEdge(finder->key, ver[i]->key, 1);
                finder = finder->next;
            }
        }

        // test if reverse graph is also connected:
        int isVisited[numVer] = {0};
        if(dg.countDFS(ver[0]->key, isVisited) == numVer)
        {
            return 2;
        }
        else
        {
            return 1;
        }
    }

    /** 1. determine strongly connect by reverse edges.
        2. determine connectivity by turn the graph into undirected graph.

        First determine if the graph is strongly connected or not.
        Then, if not strongly connected, determine if it is at least weakly connected.
    **/
}

// Return 1 if negative edges in graph;
// else return 0:
int dirGraph::negativeEdge() const
{
    for(int i=0; i<numVer; i++)
    {
        Node* finder = ver[i]->next;
        while(finder != NULL)
        {
            if(finder->weight < 0)
            {
                return 1;
            }
            finder = finder->next;
        }
    }
    return 0;
}

// Return 0 if error happens:
// else return 1:
int dirGraph::Dijkstra(string const &startVer) const
{
    // check:
    if(negativeEdge() == 1)
    {
        cout << "Negative edges contained, Dijkstra unavailable!" << endl;
        return 0;
    }

    // Dijkstra:
    string key[N] = {""};
    int weight[N] = {0};

    // Build heap:
    minHeap h;
    register int i = 0;
    while(ver[i] != NULL)
    {
        h.insert(ver[i]->key, M);
        i++;
    }
    h.reHeap(startVer, 0);

    // Print out distance result from starting point of all vertexes:
    i = 0;
    while(!h.isEmpty())
    {
        key[i] = h.topStr();
        weight[i] = h.topWeight();

        h.del();
        cout << key[i] << " " << weight[i] << endl;

        Node* child = ver[findVertex(key[i],0,numVer-1)]->next;
        while(child != NULL)
        {
            h.reHeap(child->key, weight[i] + child->weight);
            child = child->next;
        }
        i++;
    }

    // Normal return:
    return 1;
}

dirGraph* dirGraph::copyOf() const
{
    dirGraph* gtc = new dirGraph();

    // Copy vertexes to the new graph:
    for(int i=0; i<numVer; i++)
    {
        gtc->addVertex(ver[i]->key);
    }

    // Copy edges to the new edge:
    for(int i=0; i<numVer; i++)
    {
        Node* finder = ver[i]->next;
        while(finder != NULL)
        {
            gtc->addEdge(ver[i]->key, finder->key, finder->weight);
        }
    }

    return gtc;
}

dirGraph* dirGraph::Floyd_Warshall() const
{
    dirGraph* gtc = new dirGraph();

    // Add vertexes to the new graph:
    for(int i=0; i<numVer; i++)
    {
        gtc->addVertex(ver[i]->key);
    }

    // Copy edges to the new edge:
    for(int i=0; i<numVer; i++)
    {
        Node* finder = ver[i]->next;
        while(finder != NULL)
        {
            gtc->addEdge(ver[i]->key, finder->key, finder->weight);
            finder = finder->next;
        }
    }

    // Add more edges according to Floyd - Warshall:
    for(int i=0; i<numVer; i++)
    {
        string pivot = ver[i]->key; // ver[i]: pivot

        for(int j=0; j<numVer; j++)
        {
            if(j == i)
            {
                continue;
            }
            else
            {
                Node* originChild = ver[j]->next; // ver[j]: origin

                while(originChild != NULL)
                {
                    if(originChild->key == pivot) // edge from origin to pivot found!
                    {
                        Node* pivotChild = ver[i]->next;

                        while(pivotChild != NULL)
                        {
                            if(ver[j]->key != pivotChild->key)
                            {
                                gtc->addEdge(ver[j]->key, pivotChild->key, 1);
                            }
                            pivotChild = pivotChild->next;
                        }
                    }
                    originChild = originChild->next;
                }
            }
        }
    }

    /** Not tested yet, need to find a way to test it!
        Can create graph6 using class example.
    **/

    return gtc;
}


