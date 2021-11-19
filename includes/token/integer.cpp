#include "integer.h"

//CTOR
Integer::Integer(char* tok):Token(tok,NUMBER),_value(atof(tok)){}
Integer::Integer(string tok):Token(tok,NUMBER),_value(atof(tok.c_str())){}
Integer::Integer(double num):Token(to_string(num),NUMBER),_value(num){}

//VIRTUAL
int Integer::Type(){
    if(typeDebug){cout<<"calling Integer::Type()"<<endl;}
    return NUMBER;
}
void Integer::Print(){
    cout<<"[INTEGER]: "<<_value<<endl;    
}

//ACCESSOR
double Integer::Num() const{
    return _value;
}

//IO
ostream& operator <<(ostream& outs, const Integer& i){
    outs<<i._value;
    return outs;
}