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
int Function::Identifier() const{

}
double Function::perform(double lhs, double rhs){
    //check #args//input required by function
}
double Function::perform(double input){
    //check #args//input required by function
    if(_funct=="sin")
        return sin(input);
    if(_funct=="cos")
        return cos(input);
    if(_funct=="tan")
        return tan(input);
    if(_funct=="log")
        return log(input);
    assert(false);
}

//IO
ostream& operator <<(ostream& outs, const Function& f){
    outs<<f._funct;
    return outs;
}