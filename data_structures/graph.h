#ifndef __GRAPH_H__
#define __GRAPH_H__
#include <unordered_map>
#include <list>

template <class T>
class GraphNode
{
private:
    int id;
    T *val;
    std::list<GraphNode<T> *> edges;

public:
    GraphNode(int id, T val);
    ~GraphNode();
    T *getVal();
    void setVal(T new_val);
};

template <class T>
GraphNode<T>::GraphNode(int id, T val) : id(id), val(new T(val)), edges() {}

template <class T>
class Graph
{
private:
    std::unordered_map<int, GraphNode<T> *> adjacency_list;

public:
    Graph();             //c'tor
    ~Graph();            //c'dtor
    Graph(Graph &graph); //copy c'tor
    void addNode(int id, T val);
    void removeNode(int id);
};

template <class T>
void Graph<T>::addNode(int id, T val)
{
    /*search for node with ID 'id' in adjacency list*/
    typename std::unordered_map<int, GraphNode<T> *>::iterator search = adjacency_list.find(id);
    /*if node with matching id doesn't exist add new node to the list*/
    if (search = adjacency_list.end())
    {
        GraphNode<T> *new_node = new GraphNode<T>(id, val);
        adjacency_list.insert(std::make_pair(id, new_node));
    }
    /*if node exists, update its existing value*/
    else
    {
        search->second->setVal(val);
    }
}

#endif