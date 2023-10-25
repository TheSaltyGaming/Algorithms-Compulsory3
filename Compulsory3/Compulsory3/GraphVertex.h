#pragma once
#include <vector>

class GraphVertex
{
public:
    int data;
    std::vector<GraphVertex*> AdjacentVertices;
    GraphVertex(int value) : data(value){}
    
};
