#ifndef LINKED_LIST_FUNCTIONS_H
#define LINKED_LIST_FUNCTIONS_H
#include "../node/node.h"

const bool linkedDebug=false;

//Linked List General Functions:
template <typename ITEM_TYPE>
ostream& _print_list(node<ITEM_TYPE>* head, ostream& outs=cout);

//recursive fun! :)
template <typename ITEM_TYPE>
ostream& _print_list_backwards(node<ITEM_TYPE> *head, ostream& outs=cout);

//return ptr to key or NULL
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _search_list(node<ITEM_TYPE>* head, ITEM_TYPE key);

template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_head(node<ITEM_TYPE> *&head, ITEM_TYPE insert_this);

//insert after ptr
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_after(node<ITEM_TYPE>*& head, node<ITEM_TYPE> *after_this, ITEM_TYPE insert_this);

//insert before ptr
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_before(node<ITEM_TYPE>*& head, node<ITEM_TYPE>* before_this, ITEM_TYPE insert_this);

//ptr to previous node
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _previous_node(node<ITEM_TYPE>* head, node<ITEM_TYPE>* prev_to_this);

//delete, return item
template <typename ITEM_TYPE>
ITEM_TYPE _delete_node(node<ITEM_TYPE>*&head, node<ITEM_TYPE>* delete_this);

//duplicate the list...
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _copy_list(node<ITEM_TYPE>* head);

//duplicate list and return the last node of the copy
//Add the following _copy_list function to your linked list library. This function will take the source and destination head pointers. Copies the source to destination list and returns the address of the last node in destination. 
//You will use this function in your Queue's copy constructor and assignment operator. You do not want to travel the entire length of the queue to find the rear. In fact, at no point in your project will you travel the length of the queue to find the rear.
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _copy_list(node<ITEM_TYPE>* &dest, node<ITEM_TYPE> *src);

//delete all the nodes
template <typename ITEM_TYPE>
void _clear_list(node<ITEM_TYPE>*& head);

//_item at this position
template <typename ITEM_TYPE>
ITEM_TYPE& _at(node<ITEM_TYPE>* head, int pos);

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
//                              Sorted List Routines. 
//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

//insert
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_sorted(node<ITEM_TYPE>* &head, ITEM_TYPE item, bool ascending=true);

//insert or add if a dup
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_sorted_and_add(node<ITEM_TYPE>* &head, ITEM_TYPE item, bool ascending=true);

//node after which this item goes order: 0 ascending
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _where_this_goes(node<ITEM_TYPE>* head, ITEM_TYPE item, bool ascending=true);

//Last Node in the list
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _last_node(node<ITEM_TYPE>* head);


//----------------------------------------------------------------------------

//Linked List General Functions:
template <typename ITEM_TYPE>
ostream& _print_list(node<ITEM_TYPE>* head, ostream& outs){
    /*
    cout<<"H->";
    node<ITEM_TYPE> *walker=head;
    while(walker!=nullptr){
        cout<<*walker;
        walker=walker->_next;
    }
    cout << "|||" << endl;
    */
    outs<<"H->";
    for(node<ITEM_TYPE> *walker=head; walker!=nullptr; walker=walker->_next)
        outs<<*walker;
    outs<<"|||"<<endl;
    return outs;
}

//recursive fun! :)
template <typename ITEM_TYPE>
ostream& _print_list_backwards(node<ITEM_TYPE> *head, ostream& outs){
    outs<<"|||->";
    for(node<ITEM_TYPE> *walker=_last_node(head); walker!=head; walker=_previous_node(head,walker))
        outs<<*walker;
    outs<<*head<<"H"<<endl;
    return outs;
}

//return ptr to key or nullptr
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _search_list(node<ITEM_TYPE>* head, ITEM_TYPE key){
    for(node<ITEM_TYPE> *walker=head; walker!=nullptr; walker=walker->_next){
        if(walker->_item==key)
            return walker;
    }
    return nullptr;
}

template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_head(node<ITEM_TYPE> *&head, ITEM_TYPE insert_this){
    node<ITEM_TYPE> *temp=new node<ITEM_TYPE>(insert_this, head);   //creating new node --> calls node CTOR. CTOR makes the temp node point to head
    head=temp;                                                      //point head to new node
    return head;
}

//insert after ptr
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_after(node<ITEM_TYPE>*& head, node<ITEM_TYPE> *after_this, ITEM_TYPE insert_this){
    if(head==nullptr)
        return _insert_head(head, insert_this);
    node<ITEM_TYPE> *temp=new node<ITEM_TYPE>(insert_this, after_this->_next);
    after_this->_next=temp;
    return temp;
}

//insert before ptr
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_before(node<ITEM_TYPE>*& head, node<ITEM_TYPE>* before_this, ITEM_TYPE insert_this){
    assert(head!=nullptr);
    node<ITEM_TYPE> *prev=_previous_node(head, before_this);
    if(prev==nullptr)                       //meaning head
        return _insert_head(head, insert_this);
    return _insert_after(head, prev, insert_this);
}

//ptr to previous node, nullptr if prev is head
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _previous_node(node<ITEM_TYPE>* head, node<ITEM_TYPE>* prev_to_this){
    assert(head!=nullptr);
    for(node<ITEM_TYPE> *walker=head; walker!=nullptr; walker=walker->_next){
        if(walker->_next==prev_to_this)
            return walker;
    }
    return nullptr; //returns nullptr if prev_to_this=first node (previous is head)
}

//delete, return item
template <typename ITEM_TYPE>
ITEM_TYPE _delete_node(node<ITEM_TYPE>*&head, node<ITEM_TYPE>* delete_this){
    assert(head!=nullptr && delete_this!=nullptr);  //empty
    ITEM_TYPE popped=delete_this->_item;
    node<ITEM_TYPE> *prev=_previous_node(head, delete_this);
    if(prev==nullptr)               //meaning head, you are deleting the first term
        head=delete_this->_next;     //SHOULD DELETE FIRST TERM!! --> reassign head                  
    else
        prev->_next=delete_this->_next;
    delete delete_this;
    return popped;
}

//duplicate the list...
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _copy_list(node<ITEM_TYPE>* head){
    node<ITEM_TYPE> *newHead=nullptr;
    node<ITEM_TYPE> *dstWalker=newHead;
    if(linkedDebug){
        cout<<"src list:";
        _print_list(head);
    }
    for(node<ITEM_TYPE> *srcWalker=head; srcWalker!=nullptr; srcWalker=srcWalker->_next){
        //get node item from src
        //insert into dst using _insert_after function
        //CHECK THAT YOU ARE MAKING A COPY!! 
        dstWalker=_insert_after(newHead, dstWalker, srcWalker->_item);
        if(linkedDebug){
            cout<<"copying node: "<<*srcWalker<<endl;
            cout<<"dst list:";
            _print_list(newHead);
            cout<<"dst walker pointing at: "<<*dstWalker<<endl;
        }
    }
    return newHead;
}

//duplicate list and return the last node of the copy
template <typename ITEM_TYPE>
node<ITEM_TYPE> *_copy_list(node<ITEM_TYPE>* &dest, node<ITEM_TYPE> *src){
    //Add the following _copy_list function to your linked list library. This function will take the source and destination head pointers. Copies the source to destination list and returns the address of the last node in destination. 
    //You will use this function in your Queue's copy constructor and assignment operator. You do not want to travel the entire length of the queue to find the rear. In fact, at no point in your project will you travel the length of the queue to find the rear.
    node<ITEM_TYPE> *dstWalker=dest;
    if(linkedDebug){
        cout<<"src list:";
        _print_list(src);
    }
    for(node<ITEM_TYPE> *srcWalker=src; srcWalker!=nullptr; srcWalker=srcWalker->_next){
        //get node item from src
        //insert into dst using _insert_after function
        //CHECK THAT YOU ARE MAKING A COPY!! 
        dstWalker=_insert_after(dest, dstWalker, srcWalker->_item);
        if(linkedDebug){
            cout<<"copying node: "<<*srcWalker<<endl;
            cout<<"dst list:";
            _print_list(dest);
            cout<<"dst walker pointing at: "<<*dstWalker<<endl;
        }
    }
    return dstWalker;
}

//delete all the nodes
template <typename ITEM_TYPE>
void _clear_list(node<ITEM_TYPE>*& head){
    /*
    for(node<ITEM_TYPE> *walker=head; walker!=nullptr; walker=walker->_next){    //THIS SEEMS POTENTIALLY VERY DANGEROUS?? 
        //ITEM_TYPE deletedItem=_delete_node(head, walker);
        if(linkedDebug){
            cout<<"deleting "<<_delete_node(head,walker)<<endl;
            _print_list(head);
            cout<<"walker: "<<*walker<<endl;
        }
    }
    */
    /*
    node<ITEM_TYPE> *element=head;
    while(element!=nullptr){
        _delete_node(head,element);
        element=head; //update element
    }
    */
    while(head!=nullptr){
        ITEM_TYPE removed=_delete_node(head,head);
        if(linkedDebug){
            cout<<"deleted: "<<removed<<endl;
            _print_list(head);
        }
    }
    head=nullptr;
}

//_item at this position
template <typename ITEM_TYPE>
ITEM_TYPE& _at(node<ITEM_TYPE>* head, int pos){
    int i=0;
    for(node<ITEM_TYPE> *walker=head; walker!=nullptr; walker=walker->_next){
        if(i==pos)
            return walker->_item;
        i++;
    }
    if(linkedDebug)
        cout<<"_at: NOT FOUND"<<endl;
}

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
//                              Sorted List Routines. 
//                              Assume a Sorted List
//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

//insert
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_sorted(node<ITEM_TYPE>* &head, ITEM_TYPE item, bool ascending){
    node<ITEM_TYPE> *marker=_where_this_goes(head,item,ascending);
    if(marker==nullptr)
        return _insert_head(head,item);
    return _insert_after(head,marker,item);
}

//insert or add if a dup
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_sorted_and_add(node<ITEM_TYPE>* &head, ITEM_TYPE item, bool ascending){
    node<ITEM_TYPE> *marker=_where_this_goes(head,item,ascending);
    if(marker==nullptr)
        return _insert_head(head,item);
    if(marker->_item==item){
        marker->_item+=item;
        return marker;
    }
    node<ITEM_TYPE> *_next=marker->_next;
    if(_next!=nullptr && _next->_item==item){
        _next->_item+=item;
        return _next;
    }
    return _insert_after(head,marker,item);
}

//node after which this item goes order: 0 ascending
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _where_this_goes(node<ITEM_TYPE>* head, ITEM_TYPE item, bool ascending){
    if(head==nullptr || (ascending && head->_item>item) || (!ascending && head->_item<item))
        return nullptr; //return head, same thing
    node<ITEM_TYPE> *walker=head;
    if(ascending){
        for(node<ITEM_TYPE> *ahead=walker->_next; ahead!=nullptr && ahead->_item<item; ahead=ahead->_next)
            walker=walker->_next;
    }
    else{
        for(node<ITEM_TYPE> *ahead=walker->_next; ahead!=nullptr && ahead->_item>item; ahead=ahead->_next)
            walker=walker->_next;
    }
    return walker;

}

//Last Node in the list
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _last_node(node<ITEM_TYPE>* head){
    for(node<ITEM_TYPE> *walker=head; walker!=nullptr; walker=walker->_next){
        if(walker->_next==nullptr)
            return walker;
    }
    if(linkedDebug)
        cout<<"_last_node: NOT FOUND"<<endl;
    return nullptr;
}

//----------------------------------------------------------------------------

#endif //LINKED_LIST_FUNCTIONS_H