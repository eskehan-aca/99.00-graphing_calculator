#include "textbox.h"

Textbox::Textbox():_selected(false){
    _text="";
    _prev="";
    _init_sfml();
    cout<<"Textbox instantiated successfully"<<endl;
}
void Textbox::Draw(sf::RenderWindow& window){
    _text_display.setString(_text);
    window.draw(_text_display);
}
void Textbox::select(string prev){
    cout<<"enter Textbox select function";
    _selected=true;
    _prev=prev;
}
bool Textbox::isSelected() const{
    return _selected;
}
string Textbox::getText() const{
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
    //create checks that input in IS text
    int unicode=input.text.unicode;
    if(unicode<128){
         if(unicode==8 && !_text.empty())       //backspace
            _text.pop_back();
        else if(unicode==13 && _text!=_prev)     //enter -- currently exits instantly after any text is in the string --> function within class to determine if changed && if valid?
            _selected=false;
        else if(unicode==27)                    //escape
            _selected=false;
        else
            _text+=static_cast<char>(unicode);

        // cout<<"unicode: "<<unicode<<endl;
        // cout<<"char: "<<static_cast<char>(unicode)<<endl;
        /*
        if(unicode==8 && !_text.empty())        //delete key
            _text.pop_back();
        else if(unicode==13)    //enter key
            _selected=false;    //unselect envt
        else if(unicode==27)    //escape key    --> don't save changes?
            _selected=false;    //unselect envt
        else
            _text+=static_cast<char>(unicode);
        */
        if(_selected==false)
            cout<<"SELECTED FALSE: EXIT============================="<<endl;
    }
    cout<<"_text: "<<_text<<endl;
}