//
// Created by Rose on 2018/8/15.
//

#ifndef HINDEX_TEST_HINDEX_H
#define HINDEX_TEST_HINDEX_H


#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cassert>
#include <unordered_map>
#include <fstream>
#include <map>
#include "tool.h"


using namespace std;

class Hindex {

private:

    vector<vector<int>> graph;

    int E,V;
    unordered_map<EdgeClass, int, EdgeHash, EdgeEqualTo> EdgeMap;
    unordered_map<int, int> degree;

public:
    const unordered_map<int, int> &getDegree() const;

private:
    unordered_map<int, int> H;
    int h;
    vector<int> B;
    multimap<int, int> CMap;


public:

    Hindex(){

        E = V = 0;
        h = 0;

    }

    int readgraph(const char *str);

    int insertVertex(int x, int deg);
    int removeVertex(int x);

    int insertEdge(int x, int y);
    int removeEdge(int x, int y);


    int buildHindex();


    int gethindex();
    void getH();
    void getB();
    void getC();


};


#endif //HINDEX_TEST_HINDEX_H
