#ifndef __SINGLY_LINKED_LIST_H__
#define __SINGLY_LINKED_LIST_H__
#include <iostream>

template <class T>
class SinglyLinkedList
{
private:
    class SinglyLinkedNode
    {
    private:
        T *data;
        SinglyLinkedNode *next;

    public:
        SinglyLinkedNode(T &data);                                 //c'tor only with val
        SinglyLinkedNode(const SinglyLinkedNode &node);            //copy c'tor
        SinglyLinkedNode &operator=(const SinglyLinkedNode &node); //assignment operator
        ~SinglyLinkedNode();                                       //d'tor
        T *getData();
        void setData(T &new_data);
        SinglyLinkedNode *getNext();
        void setNext(SinglyLinkedNode *new_next);

    }; // class SinglyLinkedNode
    SinglyLinkedNode *head;
    int size;

public:
    SinglyLinkedList();  //c'tor
    ~SinglyLinkedList(); //d'tor
    //todo add copy c'tor and assignment operator
    T *front();
    void pop_front();
    void push_front(T data);
    class iterator;
    iterator end();
    iterator begin();

}; //class SinglyLinkedList

template <class T>
SinglyLinkedList<T>::SinglyLinkedNode::SinglyLinkedNode(T &data) : data(new T(data)), next(nullptr) {}

template <class T>
SinglyLinkedList<T>::SinglyLinkedNode::SinglyLinkedNode(const SinglyLinkedList<T>::SinglyLinkedNode &node) : data(new T(node.data)), next(node.next) {}

template <class T>
typename SinglyLinkedList<T>::SinglyLinkedNode &SinglyLinkedList<T>::SinglyLinkedNode::operator=(const SinglyLinkedNode &node)
{
    //node to be assigned is the same node
    if (this == &node)
    {
        return *this;
    }
    T *new_data = new T(node.data);
    this->data = new_data;
    this->next = node.next;
    return *this;
}

template <class T>
typename SinglyLinkedList<T>::SinglyLinkedNode *SinglyLinkedList<T>::SinglyLinkedNode::getNext()
{
    return this->next;
}

template <class T>
void SinglyLinkedList<T>::SinglyLinkedNode::setNext(SinglyLinkedList<T>::SinglyLinkedNode *new_next)
{
    this->next = new_next;
}

template <class T>
SinglyLinkedList<T>::SinglyLinkedNode::~SinglyLinkedNode()
{
    delete this->data;
}

template <class T>
SinglyLinkedList<T>::SinglyLinkedList() : head(nullptr), size(0) {}

template <class T>
SinglyLinkedList<T>::~SinglyLinkedList()
{
    SinglyLinkedList<T>::SinglyLinkedNode *it = head;
    while (it != nullptr)
    {
        SinglyLinkedList<T>::SinglyLinkedNode *to_delete = it;
        it = it->getNext();
        delete to_delete;
    }
}

template <class T>
T *SinglyLinkedList<T>::front()
{
    return this->head.getData();
}

template <class T>
void SinglyLinkedList<T>::pop_front()
{
    /*if list is empty do nothing*/
    if (this->size == 0)
    {
        return;
    }
    /*if list has more than zero objects*/
    else
    {
        SinglyLinkedList<T>::SinglyLinkedNode *new_head = this->head->getNext();
        delete this->head;
        this->head = new_head;
    }
    /*decrease size of list by one*/
    --this->size;
}

template <class T>
void SinglyLinkedList<T>::push_front(T data)
{
    SinglyLinkedList<T>::SinglyLinkedNode *new_node = new SinglyLinkedList<T>::SinglyLinkedNode(data);
    new_node->setNext(this->head);
    this->head = new_node;
    ++this->size;
}

template <class T>
typename SinglyLinkedList<T>::iterator SinglyLinkedList<T>::begin()
{
    return SinglyLinkedList<T>::iterator(this->head);
}

template <class T>
typename SinglyLinkedList<T>::iterator SinglyLinkedList<T>::end()
{
    return SinglyLinkedList<T>::iterator(nullptr);
}

template <class T>
class SinglyLinkedList<T>::iterator
{
private:
    SinglyLinkedList<T>::SinglyLinkedNode *curr_node;

public:
    iterator(SinglyLinkedList<T>::SinglyLinkedNode *curr_node);//c'tor
    iterator(const iterator& it) = default;//copy c'tor
    iterator& operator=(const iterator& it) = default;//assignment operator
    ~iterator() = default;//d'tor
    bool operator==(const iterator& it) const;
    bool operator!=(const iterator& it) const;
    T& operator*() const;
    iterator& operator++();//prefix (++it)
    iterator& operator++(int);//postfix (it++)
}; //class SinglyLinkedList<T>::iterator

template <class T>
SinglyLinkedList<T>::iterator::iterator(SinglyLinkedNode* curr_node) : curr_node(curr_node){}

template <class T>
bool SinglyLinkedList<T>::iterator::operator==(const SinglyLinkedList<T>::iterator& it) const
{
    return this->curr_node==it.curr_node;
}

template <class T>
bool SinglyLinkedList<T>::iterator::operator!=(const SinglyLinkedList<T>::iterator& it) const
{
    return this->curr_node!=it.curr_node;
}

template<class T>
T& SinglyLinkedList<T>::iterator::operator*() const
{
    return *(this->curr_node->getData());
}

template<class T>
typename SinglyLinkedList<T>::iterator& SinglyLinkedList<T>::iterator::operator++()
{
    this->curr_node = this->curr_node->getNext();
    return *this;
}

template <class T>
typename SinglyLinkedList<T>::iterator& SinglyLinkedList<T>::iterator::operator++(int)
{
    SinglyLinkedList<T>::iterator result = *this;
    ++(*this);
    return result;
}
#endif //__SINGLY_LINKED_LIST_H__