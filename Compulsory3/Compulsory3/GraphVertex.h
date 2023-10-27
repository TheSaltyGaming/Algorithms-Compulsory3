#pragma once
#include <vector>

class GraphVertex
{
public:
    bool isVisited = false;
    int data;
    std::vector<GraphVertex*> AdjacentVertices;
    GraphVertex(int value) : data(value){}
    
};
