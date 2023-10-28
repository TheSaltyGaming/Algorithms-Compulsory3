#include "Graph.h"

#include <iostream>
#include <queue>

Graph::Graph()
{
    addVertex(1);
    addVertex(2, 0);
    addVertex(3, 0);
    addVertex(33, 1);
    addVertex(4, 1);
    addVertex(22,2);
    addVertex(5, 2);
    addVertex(6, 0);

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

    BreadthTraversal(0);
    
}

/**
 * \brief Creates a vertex with no parent
 * \param value value of vertex
 */
void Graph::addVertex(int value)
{
    //Just gonna use this for the first vertex i think. 
    GraphVertex* newVertex = new GraphVertex(value);
    vertices.push_back(newVertex);
}

/**
 * \brief Creates a vertex and links it with another vertex
 * \param value value of vertex
 * \param ParentID parent vertex
 */
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

/**
 * \brief Creates vertex at a random location in the graph
 * \param value vertex value
 */
void Graph::addRandom(int value)
{
    srand(time(NULL));
    addVertex(value, rand() % vertices.size());
}

/**
 * \brief Creates an edge between two nodes
 * \param node1 Node 1
 * \param node2 Node 2
 */
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

/**
 * \brief Returns all adjacent vertices of a node
 * \param nodeID node to check
 * \return vector of adjacent vertices
 */
std::vector<GraphVertex*> Graph::GetAdjacent(int nodeID)
{
    return vertices[nodeID]->AdjacentVertices;
}

/**
 * \brief Returns all vertices in graph
 * \return list of all vertices in graph
 */
std::vector<GraphVertex*> Graph::GetAllVertices()
{
    return vertices;
}

/**
 * \brief Returns all edges in graph
 * \return Vector of all edges in graph
 */
std::vector<std::pair<int, int>> Graph::GetAllEdges()
{
    return edges;
}

/**
 * \brief Returns the number of vertices in the graph
 * \return number of vertices in graph
 */
int Graph::size()
{
    return vertices.size();
}

/**
 * \brief Checks if graph is empty
 * \return true if graph is empty
 */
int Graph::isEmpty()
{
    return vertices.size() == 0;
}

/**
 * \brief Deletes a node from the tree and disconnects all edges connected to it
 * \param node node to delete
 */
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
    
}

/**
 * \brief Deletes the edge between two nodes
 * \param node1 Node 1
 * \param node2 Node 2
 */
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

/**
 * \brief Performs a breadth first traversal of the graph
 * \param startNode node to start from
 */
void Graph::BreadthTraversal(int startNode)
{
    if (isEmpty()) return;
    // Mark all the vertices as not visited
    for (int i = 0; i < vertices.size(); i++)
    {
        vertices[i]->isVisited = false;
    }
    vertices[startNode]->isVisited = true;
    std::queue<GraphVertex*> queue;
    queue.push(vertices[startNode]);
    while (!queue.empty())
    {
        std::cout << queue.front()->data << " ";
        GraphVertex* current = queue.front();
        queue.pop();
        for (int i = 0; i < current->AdjacentVertices.size(); i++)
        {
            if (!current->AdjacentVertices[i]->isVisited)
            {
                current->AdjacentVertices[i]->isVisited = true;
                queue.push(current->AdjacentVertices[i]);
            }
        }
    }
}

