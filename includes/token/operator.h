#ifndef OPERATOR_H
#define OPERATOR_H
#include <cmath>
#include "../constants.h"
#include "token.h"

using namespace std;
class Operator:public Token{
public:
    Operator(string tok);

    virtual int Type();
    virtual void Print();

    virtual int Precedence() const;
    bool Associativity() const; //returns true if right associative

    virtual double perform(double lhs, double rhs);

    friend ostream& operator<<(ostream& outs, const Operator& o);

private:
    string _op;
    int _precedence;

    //FUNCTIONS
    void _set_precedence();
};

#endif //OPERATOR_H