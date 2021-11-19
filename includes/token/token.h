#ifndef TOKEN_H
#define TOKEN_H
#include "../constants.h"

using namespace std;
class Token{
public:
    Token(string tok, int type);

    virtual int Type();
    virtual void Print();

    friend ostream& operator<<(ostream& outs, const Token& t);
    friend ostream& operator<<(ostream& outs, Token* t);

private:
    string _tok;
    int _type;  //check constants.h file
};

#endif //TOKEN_H