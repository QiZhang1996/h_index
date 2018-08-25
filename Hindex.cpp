//
// Created by Rose on 2018/8/15.
//

#include "Hindex.h"

int Hindex::gethindex()
{
    return h;
}

void Hindex::getH()
{
    cout << "Set H ={";

    for (unordered_map<int, int>::iterator it = H.begin(); it != H.end(); it++) {

        cout << "V" << it->first << ", ";
    }
    cout << "}" << endl;

    return;
}
void Hindex::getB()
{
    cout << "Set B ={";
    for (vector<int>::iterator it = B.begin(); it != B.end(); it++) {

        cout << "V" << *it << ", ";
    }
    cout << "}" << endl;
    return;
}
void Hindex::getC()
{

//    /*第一种方法*/

    multimap<int, int>::iterator  it = CMap.begin();
    for(it = CMap.begin(); it != CMap.end(); it++){

        cout << "C[" << it->first << "]: " << it->second << endl;


    }

    return;
}

int Hindex::readgraph(const char *str){

    FILE *in = fopen(str, "r");
    if(in == NULL){

        cout << "files not exist" << endl;
        exit(1);

    }

    fscanf(in ,"%d %d", &V, &E);
    graph.resize(V+1);

    int x = 0, y = 0;

    while(fscanf(in, "%d %d", &x, &y) != EOF){

        //assert(0 <= x && x <= V);
        //assert(0 <= y && y <= V);

        graph[x].emplace_back(y);
        graph[y].emplace_back(x);
        EdgeClass edge(x, y);
        EdgeMap[edge] = 1;

    }

    for(int i = 1; i <=  V; i++){

        degree[i] = graph[i].size();

    }

    fclose(in);

    //graph_test
    /*for(int i = 1; i <= V; i++){

        vector<int>::iterator it;

        cout << "vertex" << i << ": ";

        for( it = graph[i].begin(); it != graph[i].end(); it++){

            cout << *it << ", ";
        }

        cout << endl;

    }*/

    //graph_test
    /*unordered_map<EdgeClass, int, EdgeHash, EdgeEqualTo>::iterator iter;
    EdgeClass num(2, 3);
    iter = EdgeMap.find(num);

    if (iter != EdgeMap.end())
        cout << "v1: " << iter->first.get1() << " - " << "v2: " << iter->first.get2() << endl;

    else
        cout << "Not found!" << endl;*/


    //degree_test
    /*for(int i = 1; i <= V; i++){

        cout << "V: " << i << "deg: " << degree[i] << endl;


    }*/

    return 1;

}


int Hindex::insertVertex(int x, int deg)
{

    //inser deg
    degree[x] = deg;

    //insert C
    CMap.insert(make_pair(deg, x));

    //judge h
    if (deg <= h) {

        //not change h
        return 0;

    }
    else
    {
        //judge B
        if (!B.empty()) {
            //remove y from B and H
            int y = B.at(B.size() - 1);
            B.pop_back();
            H.erase(y);
            CMap.insert(make_pair(h, y));

            H[x] = deg;

        }
        else
        {
            h = h + 1;
            H[x] = deg;
            if(CMap.count(h) != 0){

                B.clear();
                //copy c[h] to B

                multimap<int, int>::size_type  cnt = CMap.count(h);
                multimap<int, int>::iterator  iter = CMap.find(h);
                for(;cnt > 0; cnt--, iter++)
                {

                    B.push_back(iter->second);

                }

                CMap.erase(h);

            }
            else{
                //empty B
                B.clear();

            }

        }
    }
    return 1;

}


int Hindex::removeVertex(int x){

    int dx = degree[x];

    //remove from deg
    degree.erase(x);


    //remove from B
    vector<int>::iterator iter2;

    iter2 = find(B.begin(), B.end(), x);

    if (iter2 != B.end()) {

        B.erase(iter2);

    }
    else
    {
        //remove from C
        multimap<int, int>::size_type  cnt = CMap.count(dx);
        multimap<int, int>::iterator  iter = CMap.find(dx);
        if(iter != CMap.end())
        {

            for(;cnt > 0; cnt--, iter++)
            {

                if(iter->second == x){

                    CMap.erase(iter);

                    break;
                }
            }


        }


    }

    if (H.find(x) == H.end()) {

        return dx;

    }
    else
    {
        //remove from H
        H.erase(x);

        if (CMap.count(h) == 0)
        {
            h = h - 1;
            if (!B.empty())
            {

                for(vector<int>::iterator it = B.begin(); it != B.end(); it++){

                    CMap.insert(pair<int, int>(h + 1, *it));
                }

                B.clear();

            }

        }
        else
        {

            multimap<int, int>::size_type  cnt = CMap.count(h);
            multimap<int, int>::iterator  iter = CMap.find(h);
            int y = iter->second;

            CMap.erase(iter);

            B.push_back(y);

            H.erase(x);

            H[y] = h;

        }

    }
    return dx;

}


int Hindex::insertEdge(int x, int y){

    //add EdgeMap
    //add neighbor

    int dx = degree[x] + 1;
    int dy = degree[y] + 1;
    removeVertex(x);
    insertVertex(x, dx);
    removeVertex(y);
    insertVertex(y, dy);


}
int Hindex::removeEdge(int x, int y){

    //remove EdgeMap
    //remove neighbor

    int dx = degree[x] - 1;
    int dy = degree[y] - 1;
    removeVertex(x);
    insertVertex(x, dx);
    removeVertex(y);
    insertVertex(y, dy);

}

int Hindex::buildHindex(){

    for(int i = 1; i <= V; i++){

        insertVertex(i, degree[i]);

    }

    return 1;

}

const unordered_map<int, int> &Hindex::getDegree() const {
    return degree;
}

