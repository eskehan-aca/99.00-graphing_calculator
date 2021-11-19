#include "leftparen.h"

//CTOR
LeftParen::LeftParen():Token("(",LPAREN){}

//VIRTUAL
int LeftParen::Type(){
    return LPAREN;
}
void LeftParen::Print(){
    cout<<"[LPAREN]: "<<"("<<endl;    
}

//IO
ostream& operator <<(ostream& outs, const LeftParen& p){
    outs<<"(";
    return outs;
}