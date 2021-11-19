#ifndef QUEUE_H
#define QUEUE_H
#include "linked_list_functions/linked_list_functions.h"

template <typename T>
class Queue{
public:
    class Iterator{
    public:
        friend class Queue;                 //give access to list to access _ptr
        Iterator(node<T>* p=NULL):_ptr(p){} //CTOR. Point Iterator to where p is pointing to    
        //dereference operator
        T &operator*(){
            assert(_ptr);
            return _ptr->_item;
        }
        //member access operator
        T *operator->(){
            assert(_ptr);
            return &(_ptr->_item);
        }           
        //true if _ptr is NULL
        bool is_null(){
            return _ptr==nullptr;
        }
        //true if left != right
        friend bool operator!=(const Iterator &left, const Iterator &right){
            return left._ptr!=right._ptr;
        }
        //true if left == right
        friend bool operator==(const Iterator &left, const Iterator &right){
            return left._ptr==right._ptr;
        }
        //member operator:      ++it; or  ++it = new_value
        Iterator &operator++(){
            _ptr=_ptr->next;
            return *this;
        }
        //friend operator: it++
        friend Iterator operator++(Iterator &it, int unused){
            Iterator temp=it;
            it._ptr=(it._ptr->next);
            return temp;
        }

    private:
        node<T>* _ptr;              //pointer being encapsulated
    };

    Queue();
    Queue(const Queue<T>& copyMe);
    ~Queue();
    Queue& operator=(const Queue<T>& RHS);

    int size() const;
    bool empty();

    T front();
    T back();
    T pop();
    void push(T item);

    Iterator begin() const;         //Iterator to the head node
    Iterator end() const;           //Iterator to NULL
    
    void print_pointers();
    
    template<typename TT>
    friend ostream& operator<<(ostream& outs, const Queue<TT>& printMe){
        outs<<"[SIZE "<<printMe._size<<"]\t";
        _print_list(printMe._front,outs);
        return outs;
    }

private:
    node<T>* _front;    //head
    node<T>* _rear;
    int _size;
};

//----------------------------------------------------------------------------

template <typename T>
Queue<T>::Queue(){
    _front=nullptr;
    _rear=nullptr;
    _size=0;
}
template <typename T>
Queue<T>::Queue(const Queue<T>& copyMe){
    _front=nullptr;
    _rear=_copy_list(_front, copyMe._front);
    _size=copyMe._size;
    if(queueDebug)
        print_pointers();
}
template <typename T>
Queue<T>::~Queue(){
    _clear_list(_front);
    delete _front;
    if(queueDebug)
        cout<<"~Queue() DEBUG: *this: "<<*this<<endl;//should be nullptr 
}
template <typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& RHS){
    if(this==&RHS)
        return *this;
    _clear_list(_front);
    delete _front;
    if(queueDebug)
        cout<<"Queue =op DEBUG: _front (expect nullptr): "<<*_front<<endl;
    _rear=_copy_list(_front, RHS._front);
    _size=RHS._size;
    if(queueDebug)
        cout<<*this<<endl;
    return *this;
}

template <typename T>
bool Queue<T>::empty(){
    return _front==nullptr;
}
template <typename T>
T Queue<T>::front(){
    assert(!empty() && _front!=nullptr);
    return _front->_item;
}
template <typename T>
T Queue<T>::back(){
    assert(!empty() && _rear!=nullptr);
    return _rear->_item;
}
template <typename T>
void Queue<T>::push(T item){
    _rear=_insert_after(_front, _rear, item);
    _size++;
    if(queueDebug)
        cout<<"Queue push() DEBUG: "<<*this;
}
template <typename T>
T Queue<T>::pop(){
    //REVISIT THIS!!
    assert(!empty() && _front!=nullptr);
    _size--;
    return _delete_node(_front,_front);
}
template <typename T>
typename Queue<T>::Iterator Queue<T>::begin() const{
    return Iterator(_front);
}            
template <typename T>
typename Queue<T>::Iterator Queue<T>::end() const{
    return Iterator();
}
template <typename T>
void Queue<T>::print_pointers(){
    cout<<"_front: "<<*_front<<"\t";
    cout<<"_rear: "<<*_rear<<endl;
}
template <typename T>
int Queue<T>::size() const{
    return _size;
}


//----------------------------------------------------------------------------

#endif //QUEUE_H