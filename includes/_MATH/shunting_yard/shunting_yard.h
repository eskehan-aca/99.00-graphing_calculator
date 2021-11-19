#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H
#include "../../constants.h"

#include "../../foundations/queue.h"
#include "../../foundations/stack.h"
#include "../../token/rightparen.h"
#include "../../token/leftparen.h"
#include "../../token/operator.h"
#include "../../token/function.h"
#include "../../token/integer.h"
#include "../../token/token.h"

class ShuntingYard{
public:
    ShuntingYard();
    ShuntingYard(Queue<Token*> &q);

    //modify priv variable
    void infix(Queue<Token*>& q);   //same as set input

    //return postfix queue
    Queue<Token*>& postfix();
    Queue<Token*>& postfix(Queue<Token*> &q);

private:
    Queue<Token*> _queue;
    bool _in_postfix;  //false meaning expression not yet corrected
};

#endif //SHUNTING_YARD_H 