#ifndef __MINHEAP__
#define __MINHEAP__


#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

#define N 100

class minHeap
{
    struct hNode
    {
        string key;
        int weight;
    };

    private:
        hNode arr[N];

        int compNode(hNode n1, hNode n2);
        void swap(hNode heapArr[], int index1, int index2);

    public:
        // constructor:
        minHeap();
        ~minHeap();

        // If overflow, return 1; else return 0;
        int insert(string key, int weight);

        // delete Heap:
        // Return the hNode just deleted:
        void del();

        // Return 0 if the key doesn't exist; else return 1:
        // ! Can only percolate up!
        int reHeap(string key, int weight);

        // If the heap is empty, return 1; else return 0:
        bool isEmpty() const;

        // Return string of the top:
        string topStr() const;

        // Return weight of the top:
        int topWeight() const;

        void traverse() const;

};

#endif // __MINHEAP__
