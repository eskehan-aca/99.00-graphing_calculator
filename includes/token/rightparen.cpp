#include "rightparen.h"

//CTOR
RightParen::RightParen():Token(")",RPAREN){}

//VIRTUAL
int RightParen::Type(){
    return RPAREN;
}
void RightParen::Print(){
    cout<<"[RPAREN]: "<<")"<<endl;    
}

//IO
ostream& operator <<(ostream& outs, const RightParen& p){
    cout<<")";
    return outs;
}