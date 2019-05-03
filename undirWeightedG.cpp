#include <iostream>
#include <string>
#include <cstdlib>
#include <queue>
#include <climits>

#include "undirWeightedG.h"
#include "minHeap.h"

#define M INT_MAX

using namespace std;

/** Constructors:
**/
// UWGraph->Node
UWGraph::Node::Node(string key): key(key), next(NULL), weight(0)
{

}

UWGraph::Node::Node(string key, int weight): key(key), next(NULL), weight(weight)
{

}

/** Constructors:
**/
UWGraph::UWGraph()
{
    for(int i=0; i<N; i++){
        this->ver[i] = NULL;
    }

    this->numVer = 0;
    this->numEdge = 0;
}

UWGraph::~UWGraph()
{
    for(int i=0; i<N; i++){
        deconstruct(ver[i]);
    }
}

/** Functions:
**/
void UWGraph::test()
{
    minHeap h;
    h.insert("A", 300);
    h.insert("B", 100);
    h.insert("C", 500);
    h.insert("D", 50);
    h.insert("E", 50);
    h.reHeap("E", 10);
    h.del();
    h.del();

    h.reHeap("E", 11);
    h.traverse();
}


// If insert success, numVer++:
int UWGraph::addVertex(string key)
{
    if(numVer > N){
        return -1;
    }

    for(int i=0; i<N; i++){
        if(ver[i] == NULL){
            ver[i] = new Node(key);
            numVer++;
            return 0;
        }
        else if(compStr1(ver[i]->key, key) == 1){
            continue;
        }
        else if(compStr1(ver[i]->key, key) == 0){
            return 1;
        }
        else{
            for(int j=numVer; j>i; j--){
                ver[j] = ver[j-1];
            }
            ver[i] = new Node(key);
            numVer++;
            return 0;
        }
    }
}

// If insert edge success, numEdge++:
int UWGraph::addEdge(string key1, string key2, int weight)
{
    int ifEdgeExist = this->findEdge(key1, key2);

    if(ifEdgeExist == 0){
        Node* pv1 = ver[this->findVertex(key1,0,numVer-1)];
        Node* pv2 = ver[this->findVertex(key2,0,numVer-1)];

        bool skip = false;
        while(pv1->next != NULL){
            if(this->compStr1(pv1->next->key, key2) == 1){
                pv1 = pv1->next;
            }
            else{
                Node* tmp = pv1->next;
                pv1->next = new Node(key2, weight);
                pv1->next->next = tmp;
                skip = true;
                break;
            }
        }
        if(skip){
            // black;
        }
        else{
            pv1->next = new Node(key2, weight);
        }

        skip = false;
        while(pv2->next != NULL){
            if(this->compStr1(pv2->next->key, key1) == 1){
                pv2 = pv2->next;
            }
            else{
                Node* tmp = pv2->next;
                pv2->next = new Node(key1, weight);
                pv2->next->next = tmp;
                skip = true;
                break;
            }
        }
        if(skip){
            //black;
        }
        else{
            pv2->next = new Node(key1, weight);
        }

        numEdge++;
    }

    if(ifEdgeExist == 1){
        cout << "Edge " << key1 << "---------" << key2
        << " already exist, do you want to change its weight? y/n \n";



        if(cin.get() == 'y'){
            Node* pv1 = ver[this->findVertex(key1,0,numVer-1)]->next;
            Node* pv2 = ver[this->findVertex(key2,0,numVer-1)]->next;

            while(pv1 != NULL){
                if(pv1->key == key2){
                    pv1->weight = weight;
                }
                pv1 = pv1->next;
            }

            while(pv2 != NULL){
                if(pv2->key == key1){
                    pv2->weight = weight;
                }
                pv2 = pv2->next;
            }
        }
        cin.get();
    }

    return ifEdgeExist;
}

// ! numEdge-- if erase edge success:
// Return 1 if erase success, else return 0:
int UWGraph::eraseEdge(string key1, string key2)
{
    if(findEdge(key1, key2) == 1){
        Node* pv = ver[this->findVertex(key1,0,numVer)];

        while(pv->next != NULL){
            if(pv->next->key == key2){
                Node* tmp = pv->next;

                pv->next = pv->next->next;
                delete tmp;
                break;
            }
            pv = pv->next;
        }

        pv = ver[this->findVertex(key2,0,numVer)];

        while(pv->next != NULL){
            if(pv->next->key == key1){
                Node* tmp = pv->next;

                pv->next = pv->next->next;
                delete tmp;
                break;
            }
            pv = pv->next;
        }

        numEdge--;
        return 1;
    }

    return 0;
}

// ! numVer-- if success:
// Return 1 if erase success, else return 0:
int UWGraph::eraseVer(string key)
{
    int ifVerExist = this->findVertex(key,0,numVer);

    if(ifVerExist != -1){
        Node* pv = ver[ifVerExist]->next;

        while(pv != NULL){
            string tmp = pv->key;
            pv = pv->next;
            eraseEdge(key, tmp);
            cout << tmp << endl;
        }

        for(int i=ifVerExist; i<numVer-1; i++){
            ver[i] = ver[i+1];
        }

        ver[numVer-1] = NULL;
        numVer--;
        return 1;
    }

    return 0;
}

int UWGraph::numOfVer() const
{
    cout << "This graph contains " << numVer << " vertexes. " << endl;
    return numVer;
}

int UWGraph::numOfEdge() const
{
    cout << "This graph contains " << numEdge << " edges. " << endl;
    return numEdge;
}

void UWGraph::printAllVer() const
{
    for(int i=0; i<numVer; i++){
        cout << "Vertex: " << ver[i]->key << "\tPath: " << ver[i]->weight << endl;
    }
}

void UWGraph::printAllEdge() const
{
    for(int i=0; i<numVer; i++){
        Node* pv = ver[i]->next;

        while(pv != NULL){
            if(this->compStr1(ver[i]->key, pv->key) == 1){
                cout << "Edge: " << ver[i]->key << "---------" << pv->key <<
                "\t" << pv->weight << endl;
            }
            pv = pv->next;
        }
    }
}

void UWGraph::printEdge(string key1, string key2) const
{
    int ifEdgeExist = this->findEdge(key1, key2);

    if(ifEdgeExist != 1){
        cout << "Edge: " << key1 << "---------" << key2 << " doesn't exist! " << endl;
    }
    else{
        Node* tmp = ver[this->findVertex(key1,0,numVer)];

        while(tmp->next != NULL){
            if(tmp->next->key == key2){
                cout << tmp->next->weight << endl;
            }
            tmp = tmp->next;
        }
    }
}

void UWGraph::printAllAdjacent(string key) const
{
    int v = this->findVertex(key,0,numVer);

    if(v != -1){
        Node* pv = ver[v]->next;

        while(pv != NULL){
            cout << "Adjacent of " << key << ": " << pv->key <<  endl;
            pv = pv->next;
        }

        return;
    }

    cout << "Vertex " << key << " doesn't exist!" << endl;
}

void UWGraph::BFS(string key) const
{
    std::queue<int> q;
    int visited[N] = {0}; // 0 indicate the vertex not visited; i indicate visited.


    int startVer = findVertex(key,0,numVer);

    if(startVer == -1){
        cout << "Invalid vertex doesn't exist!" << endl;
        return;
    }
    // Enqueue the starting Vertex:
    q.push(startVer);
    visited[startVer] = 1;

    while(!q.empty()){
        int tmp = q.front();
        cout << "Vertex: " << ver[tmp]->key << endl;

        Node* adj = ver[tmp]->next;
        while(adj != NULL){
            int theKey = findVertex(adj->key,0,numVer);

            if(visited[theKey] == 0){
                q.push(theKey);
                visited[theKey] = 1;
            }

            adj = adj->next;
        }

        q.pop();
    }
}

void UWGraph::DFS(string key) const
{
    int visited[N] = {0}; // 0 if element not visited; else 1.

    int theKey = findVertex(key,0,numVer);

    if(theKey == -1){
        cout << "Invalid vertex doesn't exist!" << endl;
        return;
    }

    visited[theKey] = 1;

    return _DFS(theKey, visited);
}

// Return 1 if the graph is acyclic; else return 0:
bool UWGraph::isAcyclic() const
{
    int isVisited[N] = {0}; // 0 if not visited; else 1.
    int startKey = 0;

    if(ver[startKey] != NULL){
        return _isAcyclicDFS(startKey, startKey, isVisited);
    }
    else{
        return true; // NULL graph case.
    }
}

// Return 1 if the graph is connected; else return 0:
// Return -1 if bug happens:
int UWGraph::isConnected() const
{
    int isVisited[N] = {0};
    const static int startKey = 0;
    int numDFS = _connectedDFS(startKey, isVisited);

    if(numDFS == numVer){
        return 1;
    }
    else if(numDFS > numVer){
        return -1;
    }
    else{
        return 0;
    }
}

int UWGraph::negativeEdge() const
{
    for(int i=0; i<N; i++){
        Node* tmp = ver[i];

        while(tmp != NULL){
            if(tmp->weight < 0){
                return 1;
            }
            tmp = tmp->next;
        }

        if(ver[i] == NULL){
            break;
        }
    }
}

void UWGraph::Dijkstra(string startKey) const
{
    int start = findVertex(startKey,0,numVer); // The vertex to start.
    string key[N] = {""};
    int weight[N] = {0};

    // Build heap:
    minHeap h;
    int i = 0;
    while(ver[i] != NULL){
        h.insert(ver[i]->key, M);
        i++;
    }
    h.reHeap(startKey, 0);

    //
    i = 0;
    while(!h.isEmpty()){
        key[i] = h.topStr();
        weight[i] = h.topWeight();

        h.del();
        cout << key[i] << " " << weight[i] << endl;

        Node* child = ver[findVertex(key[i],0,numVer)]->next;
        while(child != NULL){
            h.reHeap(child->key, weight[i] + child->weight);
            child = child->next;
        }
        i++;
    }
}


/**
// ++++++++ Private +++++++++++++++++++++++++++++++++++++++++++++++=+++++++++ Private;
**/

// If key1 < key2, return 1; if key1 = key2, return 0; if key1 > key2, return -1:
// ascending order:
int UWGraph::compStr1(string key1, string key2) const
{
    int lkey1 = key1.length();
    int lkey2 = key2.length();

    for(int i=0; i<min(lkey1,lkey2); i++){
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

    if(lkey1 == lkey2){
        return 0;
    }
    else if(lkey1 < lkey2){
        return 1;
    }
    else{
        return -1;
    }
}

// ! No NULL pointer check.
// If the key exist, return its index; else return -1:
int UWGraph::findVertex(string key, int left, int right) const
{
    int mid = (left + right)/2;

    if(left > right){
        return -1;
    }

    if(this->compStr1(ver[mid]->key, key) == 0){
        return mid;
    }
    else if(this->compStr1(key, ver[mid]->key) == 1){
        return findVertex(key, left, mid-1);
    }
    else{
        return findVertex(key, mid+1, right);
    }

}

// If  vertex connect to itself, return -1:
// Return 1 if edge already exist; return -1 if no such two vertexes; return 0 if
// add edge normally:
int UWGraph::findEdge(string key1, string key2) const
{
    int target = this->findVertex(key1, 0, numVer-1);

    if(target == -1 || this->findVertex(key2, 0, numVer-1) == -1){
        return -1;
    }

    Node* finder = ver[target]->next;

    while(finder != NULL){
        if(finder->key == key2){
            return 1;
        }
        finder = finder->next;
    }

    return 0;
}

void UWGraph::_DFS(int keyIndex, int visited[]) const
{
    cout << "Vertex: " << ver[keyIndex]->key << endl;

    Node* tmp = ver[keyIndex]->next;
    int nextKeyIndex = -1;

    while(tmp != NULL){
        nextKeyIndex = findVertex(tmp->key,0,numVer);
        if(visited[nextKeyIndex] == 0){
            visited[nextKeyIndex] = 1;
            _DFS(nextKeyIndex, visited); // recursion
        }
        tmp = tmp->next;
    }
}

bool UWGraph::_isAcyclicDFS(int rootKey, int justVisited, int visited[]) const
{
    visited[rootKey] = 1; // mark as visited.

    Node* tmp = ver[rootKey]->next;

    if(tmp == NULL){
        return true;
    }

    bool returnVal = true; // default true, once a cycle detected, everything is false.

    while(tmp != NULL){
        int child = findVertex(tmp->key,0,numVer);

        if(child == justVisited){
            tmp = tmp->next;
            continue;
        }

        if(visited[child] == 1){
            return false;
        }
        else{
            returnVal = _isAcyclicDFS(child, rootKey, visited) && returnVal;
            tmp = tmp->next;
        }
    }

    return returnVal;
}

int UWGraph::_connectedDFS(int rootKey, int isVisited[]) const
{
    if(ver[rootKey] ==  NULL){
        return 0;
    }

    isVisited[rootKey] = 1; // Set visited.

    Node* tmp = ver[rootKey]->next;
    int numVisited = 1;

    while(tmp != NULL){
        int curKey = findVertex(tmp->key,0,numVer);

        if(isVisited[curKey] == 1){
            tmp = tmp->next;
            continue;
        }
        else{
            isVisited[curKey] = 1;
            tmp = tmp->next;
            numVisited = _connectedDFS(curKey, isVisited)+ numVisited;
        }
    }

    return numVisited;
}

void UWGraph::deconstruct(Node* head)
{
    if(head == NULL){
        return;
    }

    deconstruct(head->next);
    delete head;

    return;
}
