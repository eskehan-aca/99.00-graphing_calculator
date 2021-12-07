#include "keybinds.h"
#define ESCAPE  27
#define COMMA   44
#define PERIOD  46
#define SLASH   47

Keybinds::Keybinds(){
    _selected=false;
    _init_vector();
    _init_sfml();
    cout<<"Keybinds instantiated successfully"<<endl;
}
void Keybinds::Draw(sf::RenderWindow& window){
    if(_selected){
        //background
        window.draw(_background);

        float x=_background.getPosition().x+SB_LEFT_MARGIN;
        float height=_background.getPosition().y+SB_VERTICAL_LINE_SPACING;
        
        for(int i=0; i<=_items.size(); i++){
            if(i==0){
                _text_display.setStyle(sf::Text::Underlined);
                height+=5;
            }
            else{
                _text_display.setStyle(sf::Text::Regular);
            }
            _text_display.setString(_items[i]);
            _text_display.setPosition(sf::Vector2f(x,height));
            height+=_text_display.getLocalBounds().height+SB_VERTICAL_LINE_SPACING;
            window.draw(_text_display);
        }
    }
}
void Keybinds::select(){
    if(keybindsDebug){cout<<"enter Keybind select function";}
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

    if(!_selected && keybindsDebug)
        cout<<"KEYBIND SELECTED FALSE: EXIT"<<endl;
}
void Keybinds::_init_sfml(){
    //init font
    if(!_font.loadFromFile("arial.ttf")){
        if(keybindsDebug){cout<<"TEXTBOX INIT_SFML(): Font failed to load"<<endl;}
        cin.get();
        assert(false);
    }
    
    //init background
    _background.setSize(sf::Vector2f(0.35*GRAPH_HEIGHT, 0.5*GRAPH_WIDTH));
    _background.setFillColor(sf::Color(40,40,40,220));
    _background.setPosition(sf::Vector2f(0.125*GRAPH_HEIGHT, 0.175*GRAPH_WIDTH));

    //init text
    _text_display.setFont(_font);
    _text_display.setCharacterSize(20);
    _text_display.setStyle(sf::Text::Bold);
    _text_display.setFillColor(sf::Color::White);
    float x=_background.getPosition().x+SB_LEFT_MARGIN;
    float y=_background.getPosition().y+SB_VERTICAL_LINE_SPACING;
    _text_display.setPosition(sf::Vector2f(x,y));
}
void Keybinds::_init_vector(){
    //init _items vector
    _items.reserve(50);

    _items.push_back("");
    _items[0]="KEYBINDS";
    _items.push_back("");
    _items.push_back("");
    // _items.push_back("equation history 1         [1]");
    // _items.push_back("equation history 2         [2]");
    // _items.push_back("equation history 3         [3]");
    // _items.push_back("equation history 4         [4]");
    // _items.push_back("");
    _items.push_back("[ENTER] input equation");
    _items.push_back("[SLASH] display help");
    _items.push_back("");
    _items.push_back("[C] center origin");
    _items.push_back("[H] restore default view");
    _items.push_back("[R] reset calculator");
    _items.push_back("[S] save equation history");
    _items.push_back("[L] load equation history");
    _items.push_back("[I] display graph info");
    _items.push_back("[F] force update");
    _items.push_back("");
    _items.push_back("[+] zoom in");
    _items.push_back("[-] zoom out");
    _items.push_back("");
    _items.push_back("[ARROW KEYS]  panning");
    _items.push_back("[L/R BRACKET] points plotted");
    // _items.push_back("pan right                  [RIGHT ARROW]");
    // _items.push_back("pan left                   [LEFT ARROW]");
    // _items.push_back("pan down                   [DOWN ARROW]");
    // _items.push_back("pan up                     [UP ARROW]");
    // _items.push_back("");
    // _items.push_back("increase # points          [RIGHT BRACKET]");
    // _items.push_back("decrease # points          [LEFT BRACKET]");

    if(keybindsDebug){
        for(int i=0; i<_items.size(); i++){
            cout<<_items[i]<<endl;
        }
        cout<<"keybind end init"<<endl;
    }
}