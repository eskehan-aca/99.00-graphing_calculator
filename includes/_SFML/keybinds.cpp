#include "keybinds.h"
#define ESCAPE  27
#define COMMA   44
#define PERIOD  46
#define SLASH   47

Keybinds::Keybinds(){
    _selected=false;
    _init_sfml();
    cout<<"Keybinds instantiated successfully"<<endl;
}
void Keybinds::Draw(sf::RenderWindow& window){
    if(_selected){
        //background
        sf::RectangleShape background(sf::Vector2f(0.75*GRAPH_HEIGHT, 0.75*GRAPH_WIDTH));
        background.setFillColor(sf::Color(192,192,192));
        background.setPosition(sf::Vector2f(0.125*GRAPH_HEIGHT, 0.125*GRAPH_WIDTH));
        window.draw(background);

        //display text
        window.draw(_text_display);
    }
}
void Keybinds::select(){
    cout<<"enter Keybind select function";
    _selected=true;
}
bool Keybinds::selected() const{
    return _selected;
}
void Keybinds::sort_input(sf::Event input){
    //check that event is text input
    // if(input.type==sf::Event::KeyPressed && input.key.code==sf::Keyboard::Escape){
    //     _selected==false;
    // }
    if(input.type==sf::Event::TextEntered){
        int unicode=input.text.unicode;
        if(unicode<128){
            if(unicode==ESCAPE)
                _selected=false;    //esc to unselect
            if(unicode==SLASH)
                _selected=false;    //slash to unselect
        }
    }

    if(!_selected)
        cout<<"KEYBIND SELECTED FALSE: EXIT================"<<endl;
}
void Keybinds::_init_sfml(){
    //init font
    if (!_font.loadFromFile("arial.ttf")){
        cout<<"TEXTBOX INIT_SFML(): Font failed to load"<<endl;
        cin.get();
        exit(-1);
    }
    
    //init text
    _text_display=sf::Text("TEST", _font);
    _text_display.setCharacterSize(20);
    _text_display.setStyle(sf::Text::Bold);
    _text_display.setFillColor(sf::Color::White);
    _text_display.setPosition(sf::Vector2f(0.25*GRAPH_HEIGHT+50, 0.25*GRAPH_WIDTH+50));
}