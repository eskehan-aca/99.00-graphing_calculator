#include "rpn.h"

//CTOR
RPN::RPN(Queue<Token*> &q):_postfix(q),_evaluated(false){
    //JUNK VALUES
    _answer=0;
    _has_var=false;
}

//FUNCTIONS
void RPN::set_input(Queue<Token*> &q){
    _postfix=q;
    _evaluated=false;
    //JUNK VALUES
    _answer=0;
    _has_var=false;
}

double RPN::evaluate(){
    if(_evaluated)  //will be true if prev given # for var and no arg this time or alr eval this funct w/ no var values
        return _answer;
    assert(!_postfix.empty());
    Queue<Token*> post=_postfix;

    if(rpnDebug){cout<<"double RPN::evaluate()"<<endl;}
    Stack<Token*> s;

    while(!(post.empty())){
        Token* pop=post.pop();
        
        switch(pop->Type()){
            case NUMBER:{
                s.push(pop);
                break;
            }
            case OPERATOR:{
                //pop x2 (REVISIT: number of args that operator requires)
                Token* right=s.pop();    //stack pop1 = right
                Token* left;            //stack pop2 = left
                
                //unary [-] minus operator
                if(s.empty() && static_cast<Operator*>(pop)->opStr()=="-"){
                    left=new Integer(0.0);
                    if(rpnDebug){cout<<"testing unary minus handling in RPN evaluate case op if statement"<<endl;}
                }
                else
                    left=s.pop();     
            
                assert(right->Type()==NUMBER && left->Type()==NUMBER);
                double rVal=static_cast<Integer*>(right)->Num();
                double lVal=static_cast<Integer*>(left)->Num();
            
                //perform operation
                double calc=static_cast<Operator*>(pop)->perform(lVal,rVal);
                Token* result=new Integer(calc);

                //push result to stack
                s.push(result);
                break;
            }
            case FUNCTION:{
                if(rpnDebug){cout<<"evaluating funct "<<*pop<<endl;}
                //pop x1 (REVISIT: number of args that operator requires)
                Token* input=s.pop();

                assert(input->Type()==NUMBER);
                double inVal=static_cast<Integer*>(input)->Num();

                //perform operation
                double calc=static_cast<Function*>(pop)->perform(inVal);
                Token* result=new Integer(calc);

                //push result to stack
                s.push(result);
                break;
            }
            default:{
                if(rpnDebug){cout<<"INVALID TOKEN, TYPE: "<<pop->Type()<<endl;}
                assert(false);
                break;
            }
        }
        
        if(rpnDebug){
            cout<<"stack: "<<s;
            cout<<"queue: "<<post;
        }
    }

    assert(post.empty() && s.size()==1);
    Token* result=s.pop(); 
    double answer=static_cast<Integer*>(result)->Num();

    _answer=answer;
    _evaluated=true;
    
    return answer;
}
double RPN::evaluate(double var){
    assert(!_postfix.empty());
    Queue<Token*> post=_postfix;

    if(rpnDebug){cout<<"double RPN::evaluate(double var)"<<endl;}
    Stack<Token*> s;

    while(!(post.empty())){
        Token* pop=post.pop();
        
        switch(pop->Type()){
        case NUMBER:{
            s.push(pop);
            break;
        }
        case OPERATOR:{
            //pop x2 (REVISIT: number of args that operator requires)
            Token* right=s.pop();    //stack pop1 = right
            Token* left;             //stack pop2 = left
            
            //unary [-] minus operator
            if(s.empty() && static_cast<Operator*>(pop)->opStr()=="-"){
                left=new Integer(0.0);
                if(rpnDebug){cout<<"testing unary minus handling in RPN evaluate case op if statement"<<endl;}
            }
            else
                left=s.pop();     
            
            assert(right->Type()==NUMBER && left->Type()==NUMBER);
            double rVal=static_cast<Integer*>(right)->Num();
            double lVal=static_cast<Integer*>(left)->Num();
            
            //perform operation
            double calc=static_cast<Operator*>(pop)->perform(lVal,rVal);
            Token* result=new Integer(calc);

            //push result to stack
            s.push(result);
            break;
        }
        case VARIABLE:{
            Token* subbed=new Integer(var);
            s.push(subbed);
            break;
        }
        case FUNCTION:{
            if(rpnDebug){cout<<"evaluating funct "<<*pop<<endl;}
            //pop x1 (REVISIT: number of args that operator requires)
            Token* input=s.pop();

            assert(input->Type()==NUMBER);
            double inVal=static_cast<Integer*>(input)->Num();

            //perform operation
            double calc=static_cast<Function*>(pop)->perform(inVal);
            Token* result=new Integer(calc);

            //push result to stack
            s.push(result);
            break;
        }
        default:{
            if(rpnDebug){cout<<"INVALID TOKEN, TYPE: "<<pop->Type()<<endl;}
            break;
        }
        }
        if(rpnDebug){
            cout<<"stack: "<<s;
            cout<<"queue: "<<post;
        }
    }

    assert(post.empty() && s.size()==1);
    Token* result=s.pop(); 
    double answer=static_cast<Integer*>(result)->Num();

    _answer=answer;
    _evaluated=true;
    
    return answer;
}

double RPN::operator ()(){
    assert(!_has_var);
    return evaluate();
}
double RPN::operator ()(double var){
    //assert(_has_var);
    return evaluate(var);
}