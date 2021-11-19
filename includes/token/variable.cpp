#include "variable.h"

//CTOR
Variable::Variable(string tok):Token(tok,VARIABLE),_var(tok){}

//VIRTUAL
int Variable::Type(){
    return VARIABLE;
}
void Variable::Print(){
    cout<<"[VARIABLE]: "<<_var<<endl;    
}

//ACCESSOR
string Variable::get_var() const{
    return _var;
}

//IO
ostream& operator <<(ostream& outs, const Variable& v){
    outs<<v._var;
    return outs;
}