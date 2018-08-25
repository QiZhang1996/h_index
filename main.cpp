#include <unordered_map>
#include <iostream>
#include <map>
#include <string>
#include "Hindex.h"
using namespace std;


int main()
{

    Hindex hindex, hindex2;
    hindex.readgraph("../graphfile.txt");

    hindex.buildHindex();

    cout << "h = " << hindex.gethindex() << endl;
    hindex.getB();
    hindex.getH();
    hindex.getC();
    cout << endl;

    hindex2.insertVertex(1, 2);
    hindex2.insertVertex(2, 4);
    hindex2.insertVertex(3, 4);
    hindex2.insertVertex(4, 2);
    hindex2.insertVertex(5, 4);
    hindex2.insertVertex(6, 5);
    hindex2.insertVertex(7, 3);
    hindex2.insertVertex(8, 3);
    hindex2.insertVertex(9, 3);

    hindex.insertEdge(5, 8);
    hindex.insertEdge(3, 8);
    hindex.insertEdge(2, 7);
    cout << "h = " << hindex.gethindex() << endl;
    hindex.getB();
    hindex.getH();
    hindex.getC();
    cout << endl;




    return 0;
}