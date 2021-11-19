#ifndef ADD_ENTRY_H
#define ADD_ENTRY_H
#include "array_functions.h"
#include <iostream>
using namespace std;

template<class T>
T* add_entry(T* list, const T& new_entry, int& size, int& capacity);

template<class T>
T* remove_entry(T* list, const T& delete_me, int& size, int& capacity);

template <class T>
T *remove_last_entry(T *list, T &popped, int &size, int &capacity);

template <class T>
T *insert_entry(T *list, const T &insert_this, int insert_here, int &size,
                int &capacity);

template <class T>
T *erase_entry(T *list, int index, int &size, int &capacity);

//----------------------------------------------------------------------------

template <class T>
T* insert_entry(T *list, const T &insert_this, int insert_here, int &size, 
                int &capacity){
    if(size==capacity){
        capacity*=2;
        list = reallocate(list, size, capacity);
    }

    //this if-else creates the space for the new entry to be inserted, either
    //at the end (if) or at a specific index (else)
    if(insert_here==size)   //when we are appending, inc size to accomodate
        size++;             //shift_right does not work if insert_here>=size
                            //cannot shift right when adding to the very end
                            //as there is nothing to shift, append only
    else
        shift_right(list, size, insert_here);   //shift_right function will
                                                //check bounds of insert_here
    T* location=list+insert_here;
    *location=insert_this;

    /*
    //ALTERNATIVE METHOD - using _append function
    if(insert_here==size)
        _append(list, size, insert_this);
    else{
        shift_right(list, size, insert_here);
        T* location=list+insert_here;
        *location=insert_this;
    }
    */
    return list;
}

template<class T>
T* add_entry(T* list, const T& new_entry, int& size, int& capacity){
    return insert_entry(list, new_entry, size, size, capacity);
}

template <class T>
T* erase_entry(T *list, int index, int &size, int &capacity){
    shift_left(list, size, index);  //shift_left function will decrement size
                                    //shift_left function also has a check to
                                    //confirm that index != -1 (var delete_me)
                                    //does exist within the provided arr
    if(size<=capacity/4 && capacity/2>=MINIMUM_CAPACITY){
        capacity/=2;
        list = reallocate(list, size, capacity);
    }
    return list;
}

template<class T>
T* remove_entry(T* list, const T& delete_me, int& size, int& capacity){
    int index = search(list, size, delete_me);
    return erase_entry(list, index, size, capacity);
}

template <class T>
T* remove_last_entry(T *list, T &popped, int &size, int &capacity){
    T* pop=list+size-1;
    popped=*pop;
    return erase_entry(list, size-1, size, capacity);
}
#endif //ADD_ENTRY_H