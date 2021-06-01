#ifndef __DEQUE_H__
#define __DEQUE_H__

template <class T>
class Deque//todo change name to DoublyLinkedList
{
public:
    class DequeNode;

private:
    DequeNode *back_node;
    DequeNode *front_node;
    int size;

public:
    Deque();                                  //c'tor
    Deque(const Deque &deque);                //copy c'tor//todo implement
    DequeNode &operator=(const Deque &deque); //assignment operator//todo implement
    ~Deque();                                 //d'tor
    T &front();
    T &back();
    void push_back(T &val);
    void push_front(T &val);
    void pop_back();
    void pop_front();
    int get_size();
    void clear();
    bool empty();
}; //class Deque

template <class T>
Deque<T>::Deque() : back_node(nullptr), front_node(nullptr), size(0) {}

template <class T>
Deque<T>::~Deque()
{
    DequeNode *it = this->back;
    while (it != nullptr)
    {
        DequeNode *to_delete = it;
        it = it->getNext();
        delete to_delete;
    }
}

template <class T>
T &Deque<T>::front()
{

    return front_node->getVal();
}

template <class T>
T &Deque<T>::back()
{
    return back_node->getVal();
}

template <class T>
void Deque<T>::pop_front()
{
    if (this->size == 0)
    {
        return;
    }
    else if (this->size == 1)
    {
        delete this->front_node;
        this->front_node = nullptr;
        this->back_node = nullptr;
    }
    else
    {
        DequeNode *to_delete = this->front_node;
        this->front_node = this->front_node->getPrev();
        delete to_delete;
    }
    --this->size;
}

template <class T>
T &Deque<T>::pop_back()
{
    if (this->size == 0)
    {
        return;
    }
    else if (this->size == 1)
    {
        delete this->back_node;
        this->front_node = nullptr;
        this->back_node = nullptr;
    }
    else
    {
        DequeNode* to_delete = this->back_node;
        this->back_node = this->back_node->getNext();
        delete to_delete;
    }
    --this->size;
}

template <class T>
class Deque<T>::DequeNode
{
private:
    T val;
    DequeNode *next;
    DequeNode *prev;

public:
    DequeNode(T &val);
    DequeNode(const DequeNode &node);
    DequeNode &operator=(const DequeNode &node);
    DequeNode *getNext() const;
    DequeNode *getPrev() const;
    void setNext(DequeNode *node);
    void setPrev(DequeNode *node);
    T &getVal();
    void setVal(T &val);
}; //class Deque<T>::DequeNode

#endif //__DEQUE_H__