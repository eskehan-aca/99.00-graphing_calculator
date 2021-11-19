#ifndef RIGHT_PAREN_H
#define RIGHT_PAREN_H
#include "../constants.h"
#include "token.h"

using namespace std;
class RightParen:public Token{
public:
    RightParen();

    virtual int Type();
    virtual void Print();

    friend ostream& operator<<(ostream& outs, const RightParen& p);

private:
};

#endif //RIGHT_PAREN_H