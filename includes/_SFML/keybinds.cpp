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

        float height=0.125*GRAPH_HEIGHT+SB_VERTICAL_LINE_SPACING;
        for(int i=0; i<=_items.size(); i++){
        if(i==0){
            _text_display.setStyle(sf::Text::Underlined);
        }
        else{
            _text_display.setStyle(sf::Text::Regular);
        }
        _text_display.setString(_items[i]);
        _text_display.setPosition(sf::Vector2f(0.125*GRAPH_WIDTH+SB_LEFT_MARGIN,height));
        height+=_text_display.getLocalBounds().height+SB_VERTICAL_LINE_SPACING;
        window.draw(_text_display);
        }
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
    
    //init background
    _background.setSize(sf::Vector2f(0.75*GRAPH_HEIGHT, 0.75*GRAPH_WIDTH));
    _background.setFillColor(sf::Color(40,40,40,200));
    _background.setPosition(sf::Vector2f(0.125*GRAPH_HEIGHT, 0.125*GRAPH_WIDTH));

    //init text
    _text_display.setFont(_font);
    _text_display.setCharacterSize(20);
    _text_display.setStyle(sf::Text::Bold);
    _text_display.setFillColor(sf::Color::White);
    _text_display.setPosition(sf::Vector2f(0.25*GRAPH_HEIGHT+50, 0.25*GRAPH_WIDTH+50));
}
void Keybinds::_init_vector(){
    //init _items vector
    _items.reserve(50);

    _items.push_back("");
    _items[0]="COMMAND                    SHORTCUT";
    _items.push_back("");
    _items.push_back("equation history 1         [1]");
    _items.push_back("equation history 2         [2]");
    _items.push_back("equation history 3         [3]");
    _items.push_back("equation history 4         [4]");
    _items.push_back("");
    _items.push_back("reset graph (zoom, pts)    [R]");
    _items.push_back("display graph info         [I]");
    _items.push_back("center origin              [C]");
    _items.push_back("force update               [F]");
    _items.push_back("save history               [S]");
    _items.push_back("");
    _items.push_back("zoom in                    [+]");
    _items.push_back("zoom out                   [-]");
    _items.push_back("");
    _items.push_back("pan right                  [RIGHT ARROW]");
    _items.push_back("pan left                   [LEFT ARROW]");
    _items.push_back("pan down                   [DOWN ARROW]");
    _items.push_back("pan up                     [UP ARROW]");
    _items.push_back("");
    _items.push_back("increase # points          [RIGHT BRACKET]");
    _items.push_back("decrease # points          [LEFT BRACKET]");
    _items.push_back("");
    _items.push_back("input equation             [ENTER]");
    _items.push_back("display help               [SLASH]");

    if(keybindsDebug){
        for(int i=0; i<_items.size(); i++){
            cout<<_items[i]<<endl;
        }
        cout<<"keybind end init"<<endl;
    }
}