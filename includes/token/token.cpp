#include "token.h"

//CTOR
Token::Token(string tok, int type):_tok(tok),_type(type){
    assert(_type!=-1);
    if(typeDebug){cout<<"token ctor: "<<*this<<endl;}
}

//VIRTUAL
int Token::Type(){
    if(typeDebug){cout<<"calling Token::Type() on "<<*this<<endl;}
    return _type;
}
void Token::Print(){
    
}

//IO
ostream& operator <<(ostream& outs, const Token& t){
    //have this call Print() if possible??
    outs<<"["<<t._type<<"] token: "<<t._tok;
    return outs;
}
ostream& operator<<(ostream& outs, Token* t){
    outs<<t->_tok;
    return outs;
}