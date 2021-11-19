#ifndef RPN_H
#define RPN_H
#include "../../constants.h"

#include "../../foundations/queue.h"
#include "../../foundations/stack.h"
#include "../../token/operator.h"
#include "../../token/function.h"
#include "../../token/integer.h"
#include "../../token/token.h"

class RPN{
public:
    RPN(Queue<Token*> &q);
    
    void set_input(Queue<Token*> &q);
    
    double operator ()();    
    double operator ()(double var);    

private:
    //VARIABLES
    Queue<Token*> _postfix;
    double _answer;
    bool _evaluated;
    bool _has_var;

    //FUNCTIONS
    double evaluate();
    double evaluate(double var);
    //reviit this ==> combine into 1 funct and have it rely on _has_var bool
};

#endif //RPN_H