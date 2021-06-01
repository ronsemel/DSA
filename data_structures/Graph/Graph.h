#ifndef __GRAPH_H__
#define __GRAPH_H__
#include <unordered_map>
#include <list>
#include "Vector/Vector.h"
#include "Linked_Lists/SinglyLinkedList.h"

template <class T>
class Graph
{
public:
    class GraphNode;

private:
    std::unordered_map<int, GraphNode *> adjacency_list;

public:
    Graph();             //c'tor
    ~Graph();            //c'dtor
    Graph(Graph &graph); //copy c'tor
    void addNode(int id, T val);
    void removeNode(int id);
    /***ALGORITHMS***/
    Vector<GraphNode *> topologicalSort();
};

template <class T>
class Graph<T>::GraphNode
{
private:
    int id;
    T *val;
    std::list<GraphNode *> edges;
    friend class Graph;

public:
    GraphNode(int id, T val);
    ~GraphNode();
    T &getVal() const;
    void setVal(T new_val);
    void addEdge(GraphNode *new_edge);
}; //class Graph<T>::GraphNode

template <class T>
Graph<T>::GraphNode::GraphNode(int id, T val) : id(id), val(new T(val)), edges() {}

template <class T>
Graph<T>::GraphNode::~GraphNode()
{
    delete this->val;
}

template <class T>
T &Graph<T>::GraphNode::getVal() const
{
    return *(this->val);
}

template <class T>
void Graph<T>::GraphNode::setVal(T new_val)
{
    T *tmp = new T(new_val);
    try
    {
        delete this->val;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        throw;
    }
    this->val = tmp;
}

template <class T>
void Graph<T>::GraphNode::addEdge(Graph<T>::GraphNode *new_edge)
{
    this->edges.push_back(new_edge);
}

template <class T>
Vector<Graph<T>::GraphNode *> Graph<T>::topologicalSort()
{
    std::unordered_map<GraphNode *, int> in_degree;
    SinglyLinkedList<GraphNode*> sources_list;
    /*iterate over graph and update the in_degrees of each node*/
    /*first loop iterates over nodes in graph*/
    for (std::unordered_map<int, GraphNode *>::iterator it1 = this->adjacency_list.begin(); it != this->adjacency_list.end(); ++it)
    {
        /*second loop iterates over edges list of each GraphNode*/
        for (std::list<GraphNode *>::iterator it2 = it1->second.edges.begin(); it2 != it1->second.edges.end(); ++it)
        {
            std::unordered_map<GraphNode*, int>::iterator search = in_degree.find(*it2);
            if(search==in_degree.end())
            {
                in_degree.insert(std::make_pair(*it2,1));
            }
            else
            {
                search->second+=1;
            }
        }
    }
    /*update sources list*/
    for(std::unordered_map<GraphNode*,int>::iterator it = in_degree.begin(); it!=in_degree.end();++it)
    {
        if(it->second==0)
        {
            sources_list.push_front(it->first);
        }
    }
    
}

template <class T>
Graph<T>::Graph() : adjacency_list() {}

template <class T>
Graph<T>::~Graph()
{
    for (typename std::unordered_map<int, Graph<T>::GraphNode *>::iterator it = this->adjacency_list.begin(); it != this->adjacency_list.end(); ++it)
    {
        delete it->second;
    }
}

template <class T>
void Graph<T>::addNode(int id, T val)
{
    /*search for node with ID 'id' in adjacency list*/
    typename std::unordered_map<int, Graph<T>::GraphNode *>::iterator search = adjacency_list.find(id);
    /*if node with matching id doesn't exist add new node to the list*/
    if (search = adjacency_list.end())
    {
        Graph<T>::GraphNode *new_node = new Graph<T>::GraphNode(id, val);
        adjacency_list.insert(std::make_pair(id, new_node));
    }
    /*if node exists, update its existing value*/
    else
    {
        search->second->setVal(val);
    }
}

#endif