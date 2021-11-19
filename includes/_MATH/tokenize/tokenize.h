#ifndef TOKENIZE_H
#define TOKENIZE_H
#include "../../constants.h"

#include <string.h>
#include <stdio.h>
#include "../../foundations/queue.h"
#include "../../token/rightparen.h"
#include "../../token/leftparen.h"
#include "../../token/variable.h"
#include "../../token/operator.h"
#include "../../token/function.h"
#include "../../token/integer.h"
#include "../../token/token.h"

//given string, turn into Queue<Tokens*>

class Tokenize{
public:
    Tokenize(string input);
    Queue<Token*>& get_token_queue();

private:
    //VARIABLES
    char* _cstr;
    bool _valid;
    Queue<Token*> _token_queue;
    
    //FUNCTIONS
    Token* _convert_token(char* token);
    void _convert_queue();

    int _token_type(const char* token);
    
    bool _is_funct(string tokstr);
    bool _is_oper(string tokstr);
};

#endif //TOKENIZE_H