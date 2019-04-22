#include <iostream>
#include <string>
#include <cstdlib>
#include <conio.h>

#include "dirGraph.h"

#define L1 cout << endl; // One space line.
#define L2 cout << "\n" << endl; // Two space lines.

using namespace std;

void startInfo();
void graph1();
void graph2();
void graph3();
void graph4(bool cycle);
void graph5();
void graph6();
void helper();

int main()
{
    startInfo();
    helper();

    L2
    cout << "Start?  ESC to quit." << endl;

    while(true)
    {
        cout << "Choose graph: " << endl;

        int graph = 0;
        cin >> graph;
        cin.get();

        switch(graph)
        {
            case 1:
                graph1();
                break;

            case 2:
                graph2();
                break;

            case 3:
                graph3();
                break;

            case 4:
                graph4(false);
                L2
                cout << "Then cyclic case: " << endl;
                system("pause");
                L1
                graph4(true);
                break;

            case 5:
                graph5();
                break;

            case 6:
                graph6();
                break;

            default:
                helper();
        }

        L2
        cout << "Continue?  ESC to quit." << endl;

        if(getch() == 27)
        {
            return 0;
        }
        L1
    }

    return 0;
}

void startInfo()
{
    cout << "CS 5343 / Algorithm and Data Structure / Assignment 5" << endl;
    cout << "Name: Zailin Yuan" << endl;
    cout << "ID: zxy180026" << endl;
    cout << "Data: 04/10/2019" << endl;
    cout << "************************************************************************" << endl;
    cout << "Welcome!" << endl;
    L2
}

void graph1()
{
    dirGraph g;
    g.addVertex("a");
    g.addVertex("c");
    g.addVertex("b");
    g.addVertex("f");
    g.addVertex("e");
    g.addVertex("v");
    g.addVertex("u");
    g.addVertex("h");

    g.printAllVer();
    cout << g.numOfVer() << endl;

    g.addEdge("a", "b", 100);
    g.addEdge("a", "c", 100);
    g.addEdge("a", "d", 100);
    g.addEdge("a", "e", 100);
    g.addEdge("a", "f", 100);
    g.addEdge("a", "g", 100);
    g.addEdge("a", "h", 100);
    g.addEdge("a", "v", 100);
    g.addEdge("a", "u", 100);
    g.addEdge("b", "c", 100);
    g.addEdge("b", "v", 100);
    g.addEdge("c", "h", 100);
    g.addEdge("h", "u", 100);

    g.eraseEdge("a", "h");
    //g.eraseEdge("h", "u");
    //g.ugEdgeW("h", "u", 200);
    //g.eraseEdge("a", "c");

    //g.eraseVer("a");

    g.printAllEdges();
    cout << g.numOfEdge() << endl;

    //cout << g.hasInEdges("h") << endl;
    g.DFS("a");
    //g.BFS("a");
    cout << "++++++" << endl;
}

void graph2()
{
    dirGraph g;

    g.addVertex("A");
    g.addVertex("B");
    g.addVertex("C");
    g.addVertex("D");

    g.printAllVer();

    g.addEdge("A", "B", 100);
    g.addEdge("B", "C", 100);
    g.addEdge("C", "D", 100);
    g.addEdge("D", "B", 100);

    g.printAllEdges();

    L2
    g.topoOrder_DFS();
}

void graph3()
{
    dirGraph g;

    g.addVertex("A");
    g.addVertex("B");
    g.addVertex("C");
    g.addVertex("D");
    g.addVertex("E");
    g.addVertex("F");
    g.addVertex("G");
    g.addVertex("H");
    g.addVertex("I");
    g.addVertex("J");

    g.printAllVer();

    g.addEdge("A", "C", 1);
    g.addEdge("C", "F", 1);
    g.addEdge("F", "G", 1);
    g.addEdge("C", "D", 1);
    g.addEdge("D", "E", 1);
    g.addEdge("E", "H", 1);
    g.addEdge("H", "I", 1);
    g.addEdge("I", "J", 1);
    g.addEdge("B", "E", 1);

    g.printAllEdges();

    L2

    g.topoOrder_DFS();
}

void graph4(bool cycle)
{
    if(cycle == false)
    {
        cout << "Acyclic graph information: " << endl;
    }
    else
    {
        cout << "Cyclic graph information:  " << endl;
    }

    dirGraph g;

    g.addVertex("A");
    g.addVertex("B");
    g.addVertex("C");
    g.addVertex("D");
    g.addVertex("E");
    g.addVertex("F");
    g.addVertex("G");
    g.addVertex("H");
    g.addVertex("I");
    g.addVertex("J");
    g.addVertex("K");
    g.addVertex("L");
    g.addVertex("M");
    g.addVertex("N");
    g.addVertex("O");
    g.addVertex("P");
    g.addVertex("Q");
    g.addVertex("R");
    g.addVertex("S");
    g.addVertex("T");
    g.addVertex("U");

    g.printAllVer();

    g.addEdge("A", "B", 1);
    g.addEdge("A", "C", 1);
    g.addEdge("B", "D", 1);
    g.addEdge("B", "F", 1);
    g.addEdge("C", "F", 1);
    g.addEdge("E", "B", 1);
    g.addEdge("E", "D", 1);
    g.addEdge("F", "G", 1);
    g.addEdge("F", "H", 1);
    g.addEdge("R", "H", 1);
    g.addEdge("R", "I", 1);
    g.addEdge("H", "I", 1);
    g.addEdge("I", "G", 1);
    g.addEdge("L", "D", 1);
    g.addEdge("L", "M", 1);
    g.addEdge("D", "N", 1);
    g.addEdge("M", "N", 1);
    g.addEdge("N", "O", 1);
    g.addEdge("O", "K", 1);
    g.addEdge("G", "K", 1);
    g.addEdge("K", "P", 1);
    g.addEdge("P", "Q", 1);
    g.addEdge("Q", "S", 1);
    g.addEdge("S", "T", 1);
    g.addEdge("T", "U", 1);
    g.addEdge("F", "J", 1);

    if(cycle)
    {
        g.addEdge("S", "I", 1);
    }

    L1
    g.printAllEdges();

    cout << "Vertexes:\t" << g.numOfVer() << endl;
    cout << "Edges: \t" << g.numOfEdge() << endl;
    L2

    g.topoOrder_DFS();
    L1

    if(g.connectivity() == 0)
    {
        cout << "Not a connected graph." << endl;
    }
    else if(g.connectivity() == 1)
    {
        cout << "Weakly connected." << endl;
    }
    else if(g.connectivity() == 2)
    {
        cout << "Strongly connected." << endl;
    }
    else
    {
        cout << "Error!" << endl;
    }

    g.Dijkstra("A");
}

void graph5()
{
    dirGraph g;

    g.addVertex("A");
    g.addVertex("B");
    g.addVertex("C");
    g.addVertex("D");

    g.addEdge("A", "B", 1);
    g.addEdge("B", "C", 1);
    g.addEdge("C", "D", 1);
    g.addEdge("D", "A", 1);

    cout << g.connectivity() << endl;

    g.Dijkstra("A");
}

void graph6()
{
    dirGraph* g = new dirGraph();

    g->addVertex("LAX");
    g->addVertex("SFO");
    g->addVertex("ORD");
    g->addVertex("DFW");
    g->addVertex("MIA");
    g->addVertex("JFK"); //
    g->addVertex("BOS");
    g->printAllVer();
    cout << "Number of Vertexes: " << g->numOfVer() <<endl;

    g->addEdge("LAX", "ORD", 1400);
    g->addEdge("DFW", "SFO", 1000);
    g->addEdge("DFW", "LAX", 800);
    g->addEdge("DFW", "ORD", 500);
    g->addEdge("ORD", "DFW", 500);
    g->addEdge("JFK", "DFW", 700);
    g->addEdge("JFK", "SFO", 1500);
    g->addEdge("JFK", "BOS", 300);
    g->addEdge("JFK", "MIA", 800);
    g->addEdge("BOS", "JFK", 300);
    g->addEdge("BOS", "MIA", 900);
    g->addEdge("MIA", "DFW", 400);
    g->addEdge("MIA", "LAX", 1700);
    g->printAllEdges();
    cout << "Number of Edges: " << g->numOfEdge() <<endl;

    L2

    dirGraph* g2 = g->Floyd_Warshall();
    g2->printAllVer();
    cout << "Number of Vertexes: " << g2->numOfVer() <<endl;
    g2->printAllEdges();
    cout << "Number of Edges: " << g2->numOfEdge() <<endl;

    g2->Dijkstra("LAX");
}

void helper()
{
    cout << "All graphs are: " << endl;
    cout << "\tGraph1 is nothing." << endl;
    cout << "\tGraph2 is nothing." << endl;
    cout << "\tGraph3 is nothing." << endl;
    cout << "\tGraph5 is nothing." << endl;
    cout << "\tGraph6 is Floyd - Warshall Example." << endl;

    cout << "\tGraph4 is the most valuable." << endl;

    cout << "Press 1 to show graph1, and so on!" << endl;
}
