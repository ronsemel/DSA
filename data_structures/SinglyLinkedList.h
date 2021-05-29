#ifndef __SINGLY_LINKED_LIST_H__
#define __SINGLY_LINKED_LIST_H__
#include <iostream>

template <class T>
class singlyLinkedNode
{
private:
    T *data;
    singlyLinkedNode<T> *next;

public:
    singlyLinkedNode();//c'tor
    singlyLinkedNode(singlyLinkedNode& node);//copy c'tor
    singlyLinkedNode& operator=(const singlyLinkedNode& node);
    ~singlyLinkedNode();//d'tor
}; // class singlyLinkedNode

class singlyLinkedList
{
    singlyLinkedNode<class nodeData> *head;
}; //class SinglyLinkedList

#endif //__SINGLY_LINKED_LIST_H__