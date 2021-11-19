#ifndef VARIABLE_H
#define VARIABLE_H
#include "../constants.h"
#include "token.h"

using namespace std;
class Variable:public Token{
public:
    Variable(string tok);

    virtual int Type();
    virtual void Print();
    
    string get_var() const;

    friend ostream& operator<<(ostream& outs, const Variable& v);

private:
    string _var;
};

#endif //VARIABLE_H