//
// Created by Rose on 2018/8/15.
//

#ifndef HINDEX_TEST_TOOL_H
#define HINDEX_TEST_TOOL_H

#include <unordered_map>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

//自己设计类，作为key和value

//edge_map
class EdgeClass
{
public:

    int v1;
    int v2;

public:
    EdgeClass() { }
    EdgeClass(int x, int y) { v1 = x; v2 = y;}

    const int& get1() const
    {
        return v1;
    }
    const int& get2() const
    {
        return v2;
    }
};

class EdgeHash
{
public:

    std::size_t operator()(const EdgeClass &key) const
    {
        using std::size_t;
        using std::hash;

        return ((hash<int>()(key.v1)
                 ^ (hash<int>()(key.v2) << 1)) >> 1);
    }
};

class EdgeEqualTo {
public:

    bool operator () (const EdgeClass &lhs, const EdgeClass &rhs) const
    {
        return lhs.v1  == rhs.v1
               && lhs.v2 == rhs.v2;
    }
};





#endif //HINDEX_TEST_TOOL_H
