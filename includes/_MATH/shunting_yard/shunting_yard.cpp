#include "shunting_yard.h"

//CTOR
ShuntingYard::ShuntingYard():_in_postfix(false){
    _queue=Queue<Token*>();
}

ShuntingYard::ShuntingYard(Queue<Token*> &q):_queue(q), _in_postfix(false){}

void ShuntingYard::infix(Queue<Token*>& q){
    _queue=q;
    _in_postfix=false;
}

//FUNCTIONS
Queue<Token*>& ShuntingYard::postfix(){
    if(_in_postfix)
        return _queue;

    //CHANGE FROM INFIX TO POSTFIX
    //_queue holds infix value
    Queue<Token*> postfix;
    Stack<Token*> operators;

    while(!_queue.empty()){
        Token* pop=_queue.pop();
        
        if(pop->Type()==VARIABLE || pop->Type()==NUMBER){
            postfix.push(pop);
        }
        else if(pop->Type()==FUNCTION || pop->Type()==LPAREN){
            operators.push(pop);
        }
        else if(pop->Type()==RPAREN){
            Token* poppedOp=operators.pop();
            while(poppedOp->Type()!=LPAREN){
                //pop operators stack into pf q until u see LPAREN
                postfix.push(poppedOp);     //push op to pf q
                if(syDebug){cout<<"     RPAREN: pushed "<<poppedOp<<endl;}
                poppedOp=operators.pop();   //get next op -> exits while loop with poppedOp holding LPAREN
                if(syDebug){cout<<"     RPAREN: holding "<<poppedOp<<endl;}
            }
            if(syDebug){
                cout<<"========================================"<<endl;
                cout<<"============IN RPAREN SWITCH============"<<endl;
                cout<<"infix queue:    "<<_queue;
                cout<<"operator stack: "<<operators;
                cout<<"postfix queue:  "<<postfix;
                cout<<"poppedOp should be LPAREN: "<<poppedOp<<endl;
                cout<<"pop should be RPAREN: "<<pop<<endl;
                cout<<"========================================"<<endl;
            }
            assert(poppedOp->Type()==LPAREN && pop->Type()==RPAREN); //discard parentheses
        }
        else if(pop->Type()==OPERATOR){
            if(operators.empty() || operators.top()->Type()==LPAREN){
                operators.push(pop);
                //break out of operator if
            }
            else{
                //CRASHING HERE --> check for paren before calling precedence !! somehow....
                int popPrec=static_cast<Operator*>(pop)->Precedence();
                int stackPrec=static_cast<Operator*>(operators.top())->Precedence();
                if(popPrec>stackPrec || (popPrec==stackPrec && static_cast<Operator*>(pop)->Associativity())){
                    operators.push(pop);
                    //break out of operator if
                }
                else{
                    while(!operators.empty() && (operators.top()->Type()==OPERATOR||operators.top()->Type()==FUNCTION) && popPrec<=static_cast<Operator*>(operators.top())->Precedence()){
                        postfix.push(operators.pop());
                        if(syDebug){
                            cout<<"stackPrec: "<<stackPrec<<endl;
                            cout<<"(OPERATOR STACK): "<<operators;
                            cout<<"(POSTFIX QUEUE):  "<<postfix;
                        }
                    }
                    operators.push(pop);
                }
            }
        }
        else if(syDebug){cout<<"INVALID TOKEN: "<<pop<<endl;}
        if(syDebug){
            cout<<"infix queue:    "<<_queue;
            cout<<"operator stack: "<<operators;
            cout<<"postfix queue:  "<<postfix;
            cout<<"========================================"<<endl;
        }
    }
    while(!operators.empty()){
        Token* pop=operators.pop();
        assert(pop->Type()==OPERATOR || pop->Type()==FUNCTION);
        postfix.push(pop);
    }
    assert(_queue.empty() && operators.empty());
    //update priv vars!
    _queue=postfix;
    _in_postfix=true;
    return _queue;
}
Queue<Token*>& ShuntingYard::postfix(Queue<Token*> &q){
    _queue=q;
    _in_postfix=false;
    return postfix();
}