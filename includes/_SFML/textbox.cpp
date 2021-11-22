#include "textbox.h"

Textbox::Textbox():_selected(false){
    _text="INPUT TEXT DISPLAY";
    _init_sfml();
    cout<<"Textbox instantiated successfully"<<endl;
}
void Textbox::Draw(sf::RenderWindow& window){
    window.draw(_text_display);
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