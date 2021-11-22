#include "tokenize.h"

Tokenize::Tokenize(string input):_valid(false){
    _cstr=new char[input.length()+1];
    strcpy(_cstr, input.c_str());
    _token_queue=Queue<Token*>();
}

Queue<Token*>& Tokenize::get_token_queue(){
    _convert_queue();
    assert(_valid);
    return _token_queue;
}

//call function to take type char* and tokenize --> turn into queue<Token*>

Token* Tokenize::_convert_token(char* charToken){
    if(tokenizeDebug){cout<<"charToken: "<<string(charToken)<<endl;}
    switch(_token_type(charToken)){
        case LPAREN:
            if(tokenizeDebug){cout<<"LPAREN\t"<<endl;}
            return new LeftParen();
            break;
        case RPAREN:
            if(tokenizeDebug){cout<<"RPAREN\t"<<endl;}
            return new RightParen();
            break;
        case NUMBER:
            if(tokenizeDebug){cout<<"NUM\t"<<endl;}
            return new Integer(charToken);
            break;
        case VARIABLE:
            if(tokenizeDebug){cout<<"VAR\t"<<endl;}
            return new Variable(charToken);
            break;
        case OPERATOR:
            if(tokenizeDebug){cout<<"OP\t"<<endl;}
            return new Operator(charToken);
            break;
        case FUNCTION:
            if(tokenizeDebug){cout<<"FUNCT\t"<<endl;}
            return new Function(charToken);
            break;
        default:
            cout<<"Tokenize::_convert_token ERR: invalid token type"<<endl;
            cout<<"token: "<<string(charToken)<<endl;
            break;
    }
    cout<<"ERR: Tokenize::_convert_token did not return"<<endl;
    assert(false);
    return nullptr;
}
void Tokenize::_convert_queue(){
    if(_valid)
        return;

    assert(_token_queue.empty());

    char* charToken=strtok(_cstr," ");
    while(charToken!=NULL){
        Token* tok=_convert_token(charToken);
        if(tokenizeDebug){cout<<"Token: "<<tok<<"\tType: "<<*tok<<endl;}
        _token_queue.push(tok);
        charToken=strtok(NULL," ");
    }
    if(tokenizeDebug){cout<<_token_queue<<endl;}
    _valid=true;
}
int Tokenize::_token_type(const char* token){
    //check if double
    char* endptr=0;
    strtod(token, &endptr);
    if( !(*endptr!='\0' || endptr==token) )
        return NUMBER;

    string tokstr=token;

    //check if variable -- revisit!
    if(tokstr.size()==1 && isalpha(token[0]))
        return VARIABLE;

    //check if lparen
    if(tokstr=="(")
        return LPAREN;

    //check if rparen
    if(tokstr==")")
        return RPAREN;

    //check if operator
    if(_is_oper(tokstr))
        return OPERATOR;

    //check if function
    if(_is_funct(tokstr))
        return FUNCTION;

    assert(false);
    return -1;
}
bool Tokenize::_is_funct(string tokstr){
    for(int i=0; i<NUM_FUNCTS; i++)
        if(tokstr==FUNCT_LIST[i])
            return true;
    return false;
}
bool Tokenize::_is_oper(string tokstr){
    for(int i=0; i<NUM_OPERS; i++)
        if(tokstr==OPER_LIST[i])
            return true;
    return false;
}