#pragma once
#include "GraphVertex.h"

class Graph
{
public:
    std::vector<GraphVertex*> vertices;
    //Just learned about pairs today and these are cool AF
    //Also, storing ints which correspond to their place in the verticies vector cause it feels less clunky than storing pointers
    std::vector<std::pair<int,int>> edges;

    Graph();

    void addVertex(int value);
    void addVertex(int value, int ParentID);
    void addRandom(int value);
    void addEdge(int node1, int node2);

    GraphVertex* GetNode(int nodeID);
    std::vector<GraphVertex*> GetAdjacent(int nodeID);
    std::vector<GraphVertex*> GetAllVertices();
    std::vector<std::pair<int, int>> GetAllEdges();
    int size();
    int isEmpty();
    void DeleteNode(int node);
    void DeleteEdge(int node1, int node2);
    void BreadthTraversal(int startNode);
    
    
    
};
