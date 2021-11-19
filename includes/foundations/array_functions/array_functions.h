#ifndef ARRAY_FUNCTIONS_H
#define ARRAY_FUNCTIONS_H
#include <iostream>
#include <sstream>
#include <assert.h>

using namespace std;
const int MINIMUM_CAPACITY = 3;

template<class T>
T* allocate(int capacity= MINIMUM_CAPACITY);
//allocate 'capacity' elements. return array

template<class T>
T* reallocate(T* a, int size, int capacity);
//take array, resize it return new array. delete old array

template<class T>
void print_array(T* a, int size, int capacity = 0, ostream& outs = cout);
//prints (size/capacity) for debugging

template <class T>
void print(T* a, unsigned int how_many, ostream& outs = cout);
//print array

template<class T>
T* search_entry(T* a, int size, const T& find_me);      
//search for 'find me'

template <class T>
int search(T* a, int size, const T& find_me);           
//search for 'find_me' 

template <class T>
void shift_left(T* a, int& size, int shift_here);       
//shift left @ pos, erases @ pos

template <class T>
void shift_left(T* a, int& size, T* shift_here);        
//shift left @ pos, erases @ pos

template <class T>
void shift_right(T *a, int &size, int shift_here);      
//shift right, make a hole

template <class T>
void shift_right(T *a, int &size, T* shift_here);       
//shift right, make a hole

template<class T>
void copy_array(T *dest, const T* src, int many_to_copy);
//copy from src to dest

template <class T>
T* copy_array(const T *src, int size);
//return a copy of src

template <class T>
string array_string(const T *a, int size);
//return array as a string

template<typename T>
void _array_init(T *a, int size, T x=T());
//init array to provided int value

template<typename T>
void _append(T *a, int &size, T append_me);
//add to end of array

//----------------------------------------------------------------------------

template<class T>
T* allocate(int capacity){
    return new T[capacity];
}

template<class T>
T* reallocate(T* a, int size, int capacity){
    if(size>capacity)
        size=capacity;  //cannot copy more elements than space in array
                        //OR can also write this to just reallocate into an
                        //array made with the capacity set to (larger) size
    T* b = allocate<T>(capacity);
    _array_init(b, capacity);
    copy_array(b, a, size);
    delete[] a;
    return b;
}

template<class T>
void print_array(T* a, int size, int capacity, ostream& outs){
    if(capacity==0)
        outs << "("<<size<<")\t";
    else
        outs << "("<<size<<"/"<<capacity<<")\t";
    print(a, size, outs);
}

template <class T>
void print(T* a, unsigned int how_many, ostream& outs){
    T* walker = a;
    outs << "[";
    for(int i=0; i<how_many; i++){
        outs << "\t" << *walker;
        walker++;
    }
    outs << "\t]\n";
}

template<class T>
T* search_entry(T* a, int size, const T& find_me){
    T* walker = a;
    for(int i=0; i<size; i++){
        if(*walker==find_me)
            return walker;
        walker++;
    }
    return nullptr;
}

template <class T>
int search(T* a, int size, const T& find_me){
    T *found = search_entry(a, size, find_me);
    if(found==nullptr)
        return -1;
    return found-a;
}

template <class T>
void shift_left(T* a, int& size, int shift_here){
    if(shift_here>=size || shift_here<0||size==0)
        return; //out of bounds
    
    T* pointerShiftHere = a+shift_here;
    shift_left(a, size, pointerShiftHere);
}

template <class T>
void shift_left(T* a, int& size, T* shift_here){
    if(shift_here==nullptr)
        return; //out of bounds
    
    T *rightOne = shift_here+1;
    while(rightOne < a+size){
        //shift elements of block to the left starting at position shift_here
        *shift_here = *rightOne;
        //increment/decrement changes
        shift_here++;
        rightOne++;
    }
    size--;
}

template <class T>
void shift_right(T *a, int &size, int shift_here){
    if(shift_here>=size || shift_here<0)
        return; //out of bounds
    
    T* pointerShiftHere = a+shift_here;
    shift_right(a, size, pointerShiftHere);
}

template <class T>
void shift_right(T *a, int &size, T* shift_here){
    if(shift_here==nullptr)
        return; //out of bounds

    //a+size is already the new (increased size) end of array, so we can start
    //from that point and work backwards! 
    for (T *walker=a+size; walker>shift_here; walker--){
        //creating a pointer to copy the value to the left
        T *left_one = walker-1;
        *walker=*left_one;
    }
    size++;
}

template<class T>
void copy_array(T *dest, const T* src, int many_to_copy){
    assert(src!=nullptr);
    assert(dest!=nullptr);
    if(dest==nullptr)
        dest=allocate<T>(many_to_copy);   //should be +1?
    
    T *destWalker = dest;
    const T *srcWalker = src;
    
    for(int i=0; i<many_to_copy; i++){
        *destWalker=*srcWalker;
        destWalker++;
        srcWalker++;
    }
}

template <class T>
T* copy_array(const T *src, int size){
    assert(src!=nullptr);
    T* a = allocate<T>(size);
    copy_array(a, src, size);
    return a;
}

template <class T>
string array_string(const T *a, int size){
    ostringstream oss;
    print(a, size, oss);
    string str = "[SIZE "+to_string(size)+"]\t" + oss.str();
    return str;
}

template<typename T>
void _array_init(T* a, int size, T x){
    T* walker = a;
    for(int i=0; i<size; i++){
        *walker = x;
        walker++;
    }
}

template<typename T>
void _append(T* a, int& size, T append_me){
    T* walker = a+size;
    *walker = append_me;
    size++;
}

#endif //ARRAY_FUNCTIONS_H