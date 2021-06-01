#ifndef __VECTOR_H__
#define __VECTOR_H__
//assumes copy ctor and assignment operator
template <class T>
class Vector
{
private:
    T *arr;
    int size;
    int objects_saved;
    static const int ARRAY_INIT_SIZE = 10;
    static const int EXPAND_RATIO = 2;
    static const int SHRINK_RATIO = 4;
    void expandArray();
    void shrinkArray();

public:
    Vector();                                //c'tor
    Vector(const Vector &vector);            //copy c'tor //todo implement
    Vector &operator=(const Vector &vector); //assignment operator//todo implement
    ~Vector();
    T &operator[](int index) const;
    int getSize() const;
    T &back();
    void push_back(T &val);
    void pop_back();
    class iterator;//todo implement
}; //class Vector

template <class T>
Vector<T>::Vector() : arr(new T[ARRAY_INIT_SIZE]()), size(ARRAY_INIT_SIZE), objects_saved(0) {}

template <class T>
Vector<T>::~Vector()
{
    delete[] arr;
}

template <class T>
T &Vector<T>::operator[](int index) const
{
    return this->arr[index];
}

template <class T>
int Vector<T>::getSize() const
{
    return this->size;
}

template <class T>
T &Vector<T>::back()
{
    return this->arr[size - 1];
}

template <class T>
void Vector<T>::push_back(T &val)
{
    if (this->objects_saved == this->size)
    {
        this->expandArray();
    }
    this->arr[objects_saved++] = val;
}

template <class T>
void Vector<T>::pop_back()
{
    --objects_saved;
    if (objects_saved * SHRINK_RATIO < size)
    {
        this->shrinkArray();
    }
}

template <class T>
void Vector<T>::expandArray()
{
    T *new_arr = new T[size * EXPAND_RATIO]();
    for (int i = 0; i < size; ++i)
    {
        new_arr[i] = arr[i];
    }
    size *= EXPAND_RATIO;
    delete[] arr;
    arr = new_arr;
}

template <class T>
void Vector<T>::shrinkArray()
{
    int offset = size % SHRINK_RATIO;
    T *new_arr = new T[(size + offset) / SHRINK_RATIO]();
    for (int i = 0; i < size; ++i)
    {
        new_arr[i] = arr[i];
    }
    size = (size + offset) / SHRINK_RATIO;
    delete arr;
    arr = new_arr;
}
#endif //__VECTOR_H__
