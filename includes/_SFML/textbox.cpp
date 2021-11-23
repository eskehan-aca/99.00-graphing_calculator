#include "textbox.h"

Textbox::Textbox(GraphInfo* info):_info(info){
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
    cout<<"enter Textbox select function";
    _selected=true;
    _prev=_text;
}
bool Textbox::selected() const{
    return _selected;
}
string Textbox::text() const{
    return _text;
}
void Textbox::_init_sfml(){
    //init font
    if (!_font.loadFromFile("arial.ttf")){
        cout<<"TEXTBOX INIT_SFML(): Font failed to load"<<endl;
        cin.get();
        exit(-1);
    }
    
    //init text
    _text_display=sf::Text(_text, _font);
    _text_display.setCharacterSize(20);
    _text_display.setStyle(sf::Text::Bold);
    _text_display.setFillColor(sf::Color::White);
    _text_display.setPosition(sf::Vector2f(10, GRAPH_HEIGHT-_text_display.getLocalBounds().height-10));
}
void Textbox::_sort_input(sf::Event input){
    //check that event is text input
    if(input.type==sf::Event::TextEntered){
        int unicode=input.text.unicode;
        if(unicode<128){
            if(unicode==8 && !_text.empty())       //backspace
                _text.pop_back();
            else if(unicode==13 && _text!=_prev)    //enter -- currently exits instantly after any text is in the string --> function within class to determine if changed && if valid?
                _selected=false;
            else if(unicode==27){
                _text=_prev;                       //reset changes
                _selected=false;
            }                    //escape
            else
                _text+=static_cast<char>(unicode);
        }
        cout<<"_text: "<<_text<<endl;
    }
    if(_selected==false){
        cout<<"SELECTED FALSE: EXIT============================="<<endl;
        _modify_graph_info();
    }
}
void Textbox::_modify_graph_info(){
    //check if strings are diff?
    //check if text is legal
}