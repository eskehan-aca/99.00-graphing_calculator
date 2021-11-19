#ifndef INTEGER_H
#define INTEGER_H
#include <stdlib.h>
#include "../constants.h"
#include "token.h"

using namespace std;
class Integer:public Token{
public:
    Integer(char* tok);
    Integer(string tok);
    Integer(double num);

    virtual int Type();
    virtual void Print();

    double Num() const;

    friend ostream& operator<<(ostream& outs, const Integer& i);

private:
    double _value;
};

#endif //INTEGER_H