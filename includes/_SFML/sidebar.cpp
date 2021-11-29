#include "sidebar.h"

Sidebar::Sidebar(float height, float width):_height(height), _width(width){
    //set up the sidebar rectangle:
    _sb_rect.setFillColor(sf::Color(105,105,105)); //(192,192,192)); //silver
    _sb_rect.setPosition(sf::Vector2f(height, 0));
    _sb_rect.setSize(sf::Vector2f(width, SCREEN_HEIGHT));
    
    //init font
    // if (!font.loadFromFile("Roboto-Thin.ttf")){
    if(!font.loadFromFile("arial.ttf")){
        cout<<"Sidebar CTOR: Font failed to load"<<endl;
        cin.get();
        exit(-1);
    }

    //init text
    _sb_text.setFont(font);
    _sb_text.setCharacterSize(30);
    _sb_text.setStyle(sf::Text::Bold);
    _sb_text.setFillColor(sf::Color::White);
    //_sb_text.setPosition(sf::Vector2f(10, SCREEN_HEIGHT-_sb_text.getLocalBounds().height-5));


    //fill the _items vector with index (or empty string) so we can use []
    _items.reserve(50);
    for(int i=0; i<40; i++){
        _items.push_back("");
    }

    _items[SB_FUNCTION_MODE]="function mode?";
    _items[SB_EQ_HIST_HEADER]="EQUATION HISTORY:";
    _items[SB_MOUSE_POSITION]="MOUSE POSITION";
    _items[SB_MOUSE_CLICKED]="MOUSE COMMAND";
    _items[SB_KEY_PRESSED]="KEYBOARD COMMAND";
    _items[SB_COMMAND_NAME]="COMMAND NAME";

    cout<<"items"<<endl;
    for(int i=0; i<_items.size(); i++)
        cout<<"["<<i+1<<"]: "<<_items[i]<<endl;

    //init _history_height vector
    _history_height.reserve(20);
    for(int i=0; i<20; i++){
        _history_height.push_back(0);
    }

    cout<<"Sidebar instantiated successfully"<<endl;
}

void Sidebar::Draw(sf::RenderWindow& window){
    window.draw(_sb_rect);
    _sb_text.setFillColor(sf::Color::White);

    float height=SB_VERTICAL_MARGIN;
    _draw_eq_label(window, height);
    _draw_funct_label(window, height);
    
    height+=3*SB_VERTICAL_LINE_SPACING;
    _draw_history(window, height);


    _sb_text.setString(_items[SB_MOUSE_POSITION]);
    height+=2*SB_VERTICAL_LINE_SPACING;
    _sb_text.setPosition(sf::Vector2f(_height+SB_LEFT_MARGIN,height));
    window.draw(_sb_text);
    
    // for (vector<string>::iterator it = _items.begin(); it!= _items.end(); it++){
    //     //empty rows must be taken into account (getLocalBounds()) but not drawn
    //     bool blank=false;
    //     if(it->length()==0){
    //         blank=true;
    //         _sb_text.setString("BLANK");}    //later replace w/ "no equation"?
    //     else
    //         _sb_text.setString(it->c_str());
        
    //     //bold the first index (will house equation currently being graphed)
    //     if(it==_items.begin())
    //         _sb_text.setStyle(sf::Text::Bold);
    //     else
    //         _sb_text.setStyle(sf::Text::Regular);

    //     //setting positions for ALL rows/prints
    //     _sb_text.setPosition(sf::Vector2f(_height+SB_LEFT_MARGIN,height));
    //     height+=_sb_text.getLocalBounds().height+SB_VERTICAL_LINE_SPACING;
    //         //first text @ height var (SB_VERTICAL_MARGIN)
    //         //second text @ height var + (textbox height + vertical line spacing var)
    //         //y coord --> subtract height var, div by () to find which it is referring to
    //         //if --> holding var
        
    //     if(!blank)
    //         window.draw(_sb_text);
        
    //     /*
    //     _sb_text.setString(it->c_str());
    //     _sb_text.setPosition(sf::Vector2f(_height+SB_LEFT_MARGIN,height));
    //     height+=_sb_text.getLocalBounds().height+SB_VERTICAL_LINE_SPACING;
    //     window.draw(_sb_text);
    //     cout<<"SIDEBAR DRAW: height: "<<height<<endl;
    //     */
    // }
}

void Sidebar::_draw_eq_label(sf::RenderWindow& window, float& height){
    //drawing equation label
    string eqLabel="Graphing y = [ "+_items[SB_EQUATION_LABEL]+" ]";
    if(_items[SB_FUNCTION_MODE]=="in function mode")
        eqLabel="y = [ "+_items[SB_EQUATION_LABEL]+" ]";
    _sb_text.setString(eqLabel);
    _sb_text.setStyle(sf::Text::Bold);
    _sb_text.setPosition(sf::Vector2f(_height+SB_LEFT_MARGIN,height));
    height+=_sb_text.getLocalBounds().height+SB_VERTICAL_LINE_SPACING;
    window.draw(_sb_text);
    //handle formatting --> diff if in function mode?
}
void Sidebar::_draw_funct_label(sf::RenderWindow& window, float& height){
    //drawing function mode label
    _sb_text.setString(_items[SB_FUNCTION_MODE]);
    if(_items[SB_FUNCTION_MODE]=="in function mode")
        _sb_text.setFillColor(sf::Color::Red);
    _sb_text.setStyle(sf::Text::Italic);
    _sb_text.setPosition(sf::Vector2f(_height+SB_LEFT_MARGIN,height));
    height+=_sb_text.getLocalBounds().height+SB_VERTICAL_LINE_SPACING;
    window.draw(_sb_text);
}
void Sidebar::_draw_history(sf::RenderWindow& window, float& height){
    //drawing history section
    for(int i=0; i<=DISPLAYED_HISTORY_ITEMS; i++){
        string eq;
        if(i==0){
            _history_height[i]=height; //starting point
            _sb_text.setStyle(sf::Text::Underlined);
        }
        else{
            _sb_text.setStyle(sf::Text::Regular);
            eq="["+to_string(i)+"]: ";
        }
        eq+=_items[SB_EQ_HIST_HEADER+i];
        _sb_text.setString(eq);
        _sb_text.setFillColor(sf::Color::White);
        _sb_text.setPosition(sf::Vector2f(_height+SB_LEFT_MARGIN,height));
        height+=_sb_text.getLocalBounds().height+SB_VERTICAL_LINE_SPACING;
        _history_height[i+1]=height;    //saving the end 
        window.draw(_sb_text);
    }
}

void Sidebar::updateHistory(vector<string>& history){
    for(int i=0; i<=DISPLAYED_HISTORY_ITEMS; i++){
        _items[SB_EQ_HIST_HEADER+i+1]=history[i];
    }
}
int Sidebar::mouseClick(sf::Vector2i position){
    //horizontal bound (within sidebar)
    if(position.x>_height){
        //accomodate for header
        for(int i=1; i<=DISPLAYED_HISTORY_ITEMS; i++){
            if(position.y>=_history_height[i] && position.y<_history_height[i+1]){
                cout<<"clicked history item "<<i<<endl;
                return i;
            }
        }
    }
    return -1;
}

string& Sidebar::operator [](int index){
    return _items[index];
}