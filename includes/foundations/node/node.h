#ifndef NODE_H
#define NODE_H
#include <iomanip>
#include <iostream>
#include <assert.h>
using namespace std;

template <typename ITEM_TYPE>
struct node{
    //CTOR
    node(const ITEM_TYPE& item=ITEM_TYPE(), node<ITEM_TYPE>* next=nullptr):_item(item), _next(next){}

    //FUNCTIONS
    friend ostream& operator<<(ostream& outs, const node<ITEM_TYPE> &printMe){
        if(&printMe==nullptr)
            outs<<"[NULLPTR]";
        else
            outs<<"["<<printMe._item<<"]->";
        return outs;
    }
    
    //VARIABLES
    ITEM_TYPE _item;
    node<ITEM_TYPE>* _next;
};

#endif //NODE_H