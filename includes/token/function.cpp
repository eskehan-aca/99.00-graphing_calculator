#include "function.h"

//CTOR
Function::Function(string tok):Operator(tok),_funct(tok){}

//VIRTUAL
int Function::Type(){
    return FUNCTION;
}
void Function::Print(){
    cout<<"[FUNCTION]: "<<_funct<<endl;    
}

int Function::Precedence() const{
    return 5;
}
double Function::perform(double lhs, double rhs){
    //check #args//input required by function
    assert(false);
    return -1;
}
double Function::perform(double input){
    //check #args//input required by function
    if(_funct=="sin")
        return sin(input);
    if(_funct=="cos")
        return cos(input);
    if(_funct=="tan")
        return tan(input);
    if(_funct=="arcsin")
        return asin(input);
    if(_funct=="arccos")
        return acos(input);
    if(_funct=="arctan")
        return atan(input);
    if(_funct=="log")
        return log(input);
    if(_funct=="sqrt")          
        return sqrt(input);
    if(_funct=="csc")
        return 1/sin(input);
    if(_funct=="sec")
        return 1/cos(input);
    if(_funct=="cot")
        return 1/tan(input);
    if(_funct=="abs")
        return abs(input);
    assert(false);
    return -1;
}

//IO
ostream& operator <<(ostream& outs, const Function& f){
    outs<<f._funct;
    return outs;
}