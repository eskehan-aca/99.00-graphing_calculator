#include "sidebar.h"

Sidebar::Sidebar(float left, float width):_left(left), _width(width){
    cout<<"Sidebar CTOR: TOP"<<endl;
    _items.reserve(50);

    //set up the sidebar rectangle:
    _sb_rect.setFillColor(sf::Color(105,105,105)); //(192,192,192)); //silver
    _sb_rect.setPosition(sf::Vector2f(left, 0));
    _sb_rect.setSize(sf::Vector2f(width, SCREEN_HEIGHT));
    cout<<"Sidebar CTOR: about to load font."<<endl;
    if (!font.loadFromFile("Roboto-Thin.ttf")){
        cout<<"Sidebar() CTOR: Font failed to load"<<endl;
        cin.get();
        exit(-1);
    }
    cout<<"Sidebar CTOR: loaded font."<<endl;
    ////- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    _sb_text.setFont(font);
    _sb_text.setCharacterSize(20);
    _sb_text.setStyle(sf::Text::Bold);
    _sb_text.setFillColor(sf::Color::Yellow);
    cout<<"Sidebar CTOR: Text object initialized."<<endl;
    ////this is how you would position text on screen:
    //_sb_text.setPosition(sf::Vector2f(10, SCREEN_HEIGHT-_sb_text.getLocalBounds().height-5));

    _items.push_back("sidebar sample text");
    //Fill the _items vector with empty strings so that we can use [] to read them:
    for (int i=0 ; i<30; i++){
        _items.push_back("");
    }
    cout<<"Sidebar: CTOR: Exit."<<endl;
}

void Sidebar::Draw(sf::RenderWindow& window){
    const double VERTICAL_LINE_SPACING = 5.0;
    const double LEFT_MARGIN = 10.0;

    window.draw(_sb_rect);
    float height = 10;

    for (vector<string>::iterator it = _items.begin(); it!= _items.end(); it++){
        bool blank=false;
        if(it->length()==0){
            //empty rows must be taken into account (getLocalBounds()) but not drawn
            blank=true;
            _sb_text.setString("BLANK");
        }
        else{_sb_text.setString(it->c_str());}
        _sb_text.setPosition(sf::Vector2f(_left+LEFT_MARGIN,height));
        height+=_sb_text.getLocalBounds().height+VERTICAL_LINE_SPACING;
        
        if(!blank)
            window.draw(_sb_text);
    }
}

string& Sidebar::operator [](int index){
    return _items[index];
}