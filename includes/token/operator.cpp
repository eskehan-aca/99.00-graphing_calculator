#include "operator.h"

//CTOR
Operator::Operator(string tok):Token(tok,OPERATOR),_op(tok),_precedence(-1){
    _set_precedence();
}

//VIRTUAL
int Operator::Type(){
    if(typeDebug){cout<<"calling Operator::Type() on "<<*this<<endl;}
    return OPERATOR;
}
void Operator::Print(){
    cout<<"[OPERATOR]: "<<_op<<endl;
}

//ACCESSORS
int Operator::Precedence() const{
    assert(_precedence!=-1);
    return _precedence;
}
bool Operator::Associativity() const{
    return _op=="^";    //currently only ^ op is right associative
}
string Operator::opStr() const{
    return _op;
}
//ARITH
double Operator::perform(double lhs, double rhs){
    if(_op=="+")
        return lhs+rhs;
    if(_op=="-")
        return lhs-rhs;
    if(_op=="*")
        return lhs*rhs;
    if(_op=="/")
        return lhs/rhs;
    if(_op=="^")
        return pow(lhs,rhs);
    assert(false);
}

//CALL AFTER IDENTIFIER HAS BEEN SET!
void Operator::_set_precedence(){
    if(_op=="+" || _op=="-")
        _precedence=2;
    if(_op=="*" || _op=="/")
        _precedence=3;
    if(_op=="^")
        _precedence=4;
}

//IO
ostream& operator <<(ostream& outs, const Operator& f){
    cout<<f._op;
    return outs;
}