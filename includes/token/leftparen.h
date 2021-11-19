#ifndef LEFT_PAREN_H
#define LEFT_PAREN_H
#include "../constants.h"
#include "token.h"

using namespace std;
class LeftParen:public Token{
public:
    LeftParen();

    virtual int Type();
    virtual void Print();

    friend ostream& operator<<(ostream& outs, const LeftParen& p);

private:
};

#endif //LEFT_PAREN_H