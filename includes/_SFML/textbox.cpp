#include "textbox.h"
#define DELETE  8
#define ENTER   13
#define ESCAPE  27

Textbox::Textbox(){
    _selected=false;
    _text="";
    _prev="";
    _init_sfml();
    cout<<"Textbox instantiated successfully"<<endl;
}
void Textbox::Draw(sf::RenderWindow& window){
    _text_display.setString(_text);
    window.draw(_text_display);
}
void Textbox::select(){
    if(textboxDebug){cout<<"enter Textbox select function"<<endl;}
    _selected=true;
    _prev=_text;
}
bool Textbox::selected() const{
    return _selected;
}
bool Textbox::modified() const{
    return _prev!=_text;
}
string Textbox::text() const{
    return _text;
}
void Textbox::_init_sfml(){
    //init font
    if (!_font.loadFromFile("arial.ttf")){
        if(textboxDebug){cout<<"TEXTBOX INIT_SFML(): Font failed to load"<<endl;}
        cin.get();
        assert(false);
    }
    
    //init text
    _text_display=sf::Text(_text, _font);
    _text_display.setCharacterSize(20);
    _text_display.setStyle(sf::Text::Bold);
    _text_display.setFillColor(sf::Color::White);
    _text_display.setPosition(sf::Vector2f(10, GRAPH_HEIGHT-_text_display.getLocalBounds().height-10));
}
void Textbox::sort_input(sf::Event input){
    //check that event is text input
    if(input.type==sf::Event::TextEntered){
        int unicode=input.text.unicode;
        if(unicode<128){
            if(unicode!=DELETE && unicode!=ENTER && unicode!=ESCAPE)
                _text+=static_cast<char>(unicode);
            else if(unicode==DELETE && !_text.empty())
                _text.pop_back();
            else if(unicode==ENTER && modified())
                _selected=false;    //enter if new eq
            else if(unicode==ESCAPE){
                _text=_prev;        //reset text
                _selected=false;    //unselect
            }
            else if(textboxDebug)
                cout<<"hit enter but no changes to string --> nothing happens"<<endl;
        if(textboxDebug){cout<<"_text: "<<_text<<endl;}
        }
    }
    if(!_selected && textboxDebug){cout<<"SELECTED FALSE: EXIT TEXTBOX SORT_INPUT"<<endl;}
}
void Textbox::reset(){
    _selected=false;
    _text="";
    _prev="";
}
void Textbox::setText(string text){
    _text=text;
}