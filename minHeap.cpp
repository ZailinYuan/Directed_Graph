#include <iostream>
#include <string>
#include <cstdlib>

#include "minHeap.h"

using namespace std;

/** Constructors:
**/
minHeap::minHeap()
{
    arr[0].key = "";
    arr[0].weight = 0; // First element record number of elements in this heap.

    for(int i=1; i<N; i++){
        arr[i].key = "";
        arr[i].weight = -1;
    }
}

minHeap::~minHeap()
{

}

/** Functions:
**/

int minHeap::insert(string key, int weight)
{
    if(arr[0].weight >= 99){
        return 1;
    }

    int index = arr[0].weight;
    arr[index+1].key = key;
    arr[index+1].weight = weight;

    arr[0].weight++; // Counter++;

    int index2 = index + 1;
    int index1 = index2/2;

    while(index2 != 0){
        if(compNode(arr[index1], arr[index2]) == 0){
            this->swap(arr, index1, index2);
        }

        index2 = index1;
        index1 = index2/2;
    }
    return 0;
}

void minHeap::del()
{
    if(arr[0].weight <= 0){
        return;
    }

    int index = arr[0].weight; // Index in array.
    int index1 = 1; // top of the heap.
    int index2 = index1 * 2; // left child
    int index3 = index1 * 2 + 1;  // right child

    this->swap(arr, 1, index);
    arr[index].weight = -1;
    arr[index].key = "";
    arr[0].weight--;

    while(index2 <= arr[0].weight){
        if(index3 > arr[0].weight){
            if(compNode(arr[index1], arr[index2]) == 0){
                this->swap(arr, index1, index2);
                index1 = index2;
            }
            else{
                break;
            }
        }
        else{
            if(compNode(arr[index1], arr[index2]) == 1 && compNode(arr[index1], arr[index3]) == 1){
                break;
            }
            else{
                if(compNode(arr[index2], arr[index3]) == 1){
                    this->swap(arr, index1, index2);
                    index1 = index2;
                }
                else{
                    this->swap(arr, index1, index3);
                    index1 = index3;
                }
            }
        }
        index2 = index1 * 2;
        index3 = index1 * 2 + 1;
    }

    return;
}

int minHeap::reHeap(string key, int weight)
{
    int keyChanged = 0;

    for(int i=1; i<N; i++){
        if(arr[i].key == key){
            keyChanged = i;
        }
    }

    if(keyChanged == 0){
        return 0;
    }

    if(arr[keyChanged].weight <= weight){
        return 0; // If no need to upgrade.
    }

    arr[keyChanged].weight = weight;

    int index = keyChanged/2;

    while(index != 0){
        if(compNode(arr[index], arr[keyChanged]) == 0){
            this->swap(arr, index, keyChanged);
            keyChanged = index;
            index = keyChanged/2;
        }
        else{
            break;
        }
    }

    return 1;
}

bool minHeap::isEmpty() const
{
    if(arr[0].weight == 0){
        return true;
    }
    else{
        return false;
    }
}

string minHeap::topStr() const
{
    return arr[1].key;
}

int minHeap::topWeight() const
{
    return arr[1].weight;
}

void minHeap::traverse() const
{
    for(int i=1; i<N && arr[i].weight != -1; i++){
        cout << arr[i].key << "----" << arr[i].weight << endl;
    }
}


/** Private functions: +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++:
**/

// Return 1 if n1.weight <= n2.weight; else return 0:
int minHeap::compNode(hNode n1, hNode n2)
{
    if(n1.weight <= n2.weight){
        return 1;
    }
    else{
        return 0;
    }
}

void minHeap::swap(hNode heapArr[], int index1, int index2)
{
    hNode tmp = heapArr[index1];
    heapArr[index1] = heapArr[index2];
    heapArr[index2] = tmp;
}
