#include "Graph.h"

#include <iostream>

Graph::Graph()
{
    addVertex(1);
    addVertex(2, 0);
    addVertex(3, 0);
    addVertex(22,2);

    //Print all Edges
    for (int i = 0; i < edges.size(); i++)
    {
        std::cout << edges[i].first << " - " << edges[i].second << std::endl;
    }
    std::cout << "ALl Vertices: " << std::endl;
    for (int j = 0; j < vertices.size(); j++)
    {
        std::cout << vertices[j]->data << std::endl;
    }
    
}

void Graph::addVertex(int value)
{
    //Just gonna use this for the first vertex i think. 
    GraphVertex* newVertex = new GraphVertex(value);
    vertices.push_back(newVertex);
}

void Graph::addVertex(int value, int ParentID)
{
    GraphVertex* ParentVertex = vertices[ParentID];
    
    //I could probably pass in the parent as well as the value? eh idk who knows. 
    GraphVertex* newVertex = new GraphVertex(value);
    vertices.push_back(newVertex);
    //Add parent to adjacency list, and add child to parent's adjacency list
    newVertex->AdjacentVertices.push_back(ParentVertex);
    ParentVertex->AdjacentVertices.push_back(newVertex);

    edges.emplace_back(ParentVertex->data, newVertex->data);
}

void Graph::addRandom(int value)
{
    srand(time(NULL));
    addVertex(value, rand() % vertices.size());
}

void Graph::addEdge(int node1, int node2)
{
    GraphVertex* ParentVertex = vertices[node1];
    GraphVertex* ChildVertex = vertices[node2];
    ChildVertex->AdjacentVertices.push_back(ParentVertex);
    ParentVertex->AdjacentVertices.push_back(ChildVertex);

    edges.emplace_back(ParentVertex->data, ChildVertex->data);
}

GraphVertex* Graph::GetNode(int nodeID)
{
    return vertices[nodeID];
}

std::vector<GraphVertex*> Graph::GetAdjacent(int nodeID)
{
    return vertices[nodeID]->AdjacentVertices;
}

std::vector<GraphVertex*> Graph::GetAllVertices()
{
    return vertices;
}

std::vector<std::pair<int, int>> Graph::GetAllEdges()
{
    return edges;
}

int Graph::size()
{
    return vertices.size();
}

int Graph::isEmpty()
{
    return vertices.size() == 0;
}

void Graph::DeleteNode(int node)
{
    GraphVertex* nodeToDelete = vertices[node];
    std::vector<GraphVertex*> adjacent = nodeToDelete->AdjacentVertices;
    //remove edges connected to node
    for (int i = 0; i < edges.size(); i++)
    {
        if (edges[i].first == nodeToDelete->data || edges[i].second == nodeToDelete->data)
        {
            //replace begin with 0 maybe?
            edges.erase(edges.begin() + i);
            //Prevents skipping an edge since the vector is now 1 shorter
            i--;
        }
    }
    //Update all neighbor nodes to remove references to this node
    //For every adjacent node
    for (int i = 0; i < adjacent.size(); i++)
    {
        //Checking the adjacent vercities of the adjacent node
        for (int j = 0; j < adjacent[i]->AdjacentVertices.size(); j++)
        {
            if (adjacent[i]->AdjacentVertices[j] == nodeToDelete)
            {
                adjacent[i]->AdjacentVertices.erase(adjacent[i]->AdjacentVertices.begin() + j);
                //Breaking so i don't have to run through the rest of the array
                break;
            }
        }
    }
    //Remove node from vertices vector
    vertices.erase(vertices.begin() + node);
    //Delete node
    delete nodeToDelete;

    //TODO: Do i connect the potential missing nodes to eachother here?
}

void Graph::DeleteEdge(int node1, int node2)
{
    GraphVertex* first = vertices[node1];
    GraphVertex* second = vertices[node2];
    //Remove edge from edges vector, but also remove the edge from the adjacency list of both nodes
    for (int i = 0; i < edges.size(); i++)
    {
        if (edges[i].first == node1 && edges[i].second == node2)
        {
            edges.erase(edges.begin() + i);
            break;
        }
    }
    //Remove node2 from node1's adjacency list
    for (int i = 0; i < first->AdjacentVertices.size(); i++)
    {
        if (first->AdjacentVertices[i] == second)
        {
            first->AdjacentVertices.erase(first->AdjacentVertices.begin() + i);
            break;
        }
    }
    //Remove node1 from node2's adjacency list
    for (int i = 0; i < second->AdjacentVertices.size(); i++)
    {
        if (second->AdjacentVertices[i] == first)
        {
            second->AdjacentVertices.erase(second->AdjacentVertices.begin() + i);
            break;
        }
    }
    
}

void Graph::BreadthTraversal(int startNode)
{
    
}

