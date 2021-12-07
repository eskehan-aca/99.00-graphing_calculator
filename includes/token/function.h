#ifndef FUNCTION_H
#define FUNCTION_H
#include "../constants.h"
#include "operator.h"

using namespace std;
class Function:public Operator{
public:
    Function(string tok);

    virtual int Type();
    virtual void Print();

    virtual int Precedence() const;

    friend ostream& operator<<(ostream& outs, const Function& f);
    //not used atm --> currently assuming that FUNCTIONS are 1 arg, OPERATORS are 2 arg
    virtual double perform(double lhs, double rhs);
    virtual double perform(double input);
    //could just set default arg value??LOL

private:
    string _funct;
};

#endif //FUNCTION_H