#include "sidebar.h"

Sidebar::Sidebar(float height, float width):_height(height), _width(width){
    cout<<"Sidebar CTOR: TOP"<<endl;
    _items.reserve(50);

    //set up the sidebar rectangle:
    _sb_rect.setFillColor(sf::Color(105,105,105)); //(192,192,192)); //silver
    _sb_rect.setPosition(sf::Vector2f(height, 0));
    _sb_rect.setSize(sf::Vector2f(width, SCREEN_HEIGHT));
    if (!font.loadFromFile("Roboto-Thin.ttf")){
        cout<<"Sidebar() CTOR: Font failed to load"<<endl;
        cin.get();
        exit(-1);
    }
    cout<<"Sidebar CTOR: Font Loaded."<<endl;

    _sb_text.setFont(font);
    _sb_text.setCharacterSize(20);
    _sb_text.setStyle(sf::Text::Bold);
    _sb_text.setFillColor(sf::Color::Yellow);
    cout<<"Sidebar CTOR: Text object initialized."<<endl;

    //this is how you would position text on screen:
    //_sb_text.setPosition(sf::Vector2f(10, SCREEN_HEIGHT-_sb_text.getLocalBounds().height-5));

    _items.push_back("sidebar sample text");
    //Fill the _items vector with empty strings so that we can use [] to read them:
    for (int i=0 ; i<30; i++){
        _items.push_back("");
    }
    _items[SB_MOUSE_POSITION]="MOUSE POSITION";
    _items[SB_MOUSE_CLICKED]="MOUSE COMMAND";
    _items[SB_KEY_PRESSED]="KEYBOARD COMMAND";
    _items[SB_COMMAND_NAME]="COMMAND NAME";
    _items[SB_EQUATION_LABEL]="EQUATION LABEL";
    cout<<"Sidebar: CTOR: Exit."<<endl;
}

void Sidebar::Draw(sf::RenderWindow& window){
    const double VERTICAL_LINE_SPACING = 5.0;
    const double LEFT_MARGIN = 10.0;

    window.draw(_sb_rect);
    float height = SB_SPACING;  //??idk what this is

    for (vector<string>::iterator it = _items.begin(); it!= _items.end(); it++){
        bool blank=false;
        if(it->length()==0){
            //empty rows must be taken into account (getLocalBounds()) but not drawn
            blank=true;
            _sb_text.setString("BLANK");
        }
        else{_sb_text.setString(it->c_str());}
        _sb_text.setPosition(sf::Vector2f(_height+LEFT_MARGIN,height));
        height+=_sb_text.getLocalBounds().height+VERTICAL_LINE_SPACING;
        
        if(!blank)
            window.draw(_sb_text);
    }
}

string& Sidebar::operator [](int index){
    return _items[index];
}