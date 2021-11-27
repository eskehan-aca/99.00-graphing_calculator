#include "graph.h"

Graph::Graph(GraphInfo* info):_plotter(info),_info(info){
    update();
    _init_sfml();
    cout<<"Graph instantiated successfully"<<endl;
}

void Graph::update(){    //UPDATE IS CALLED WHENEVER POINTS TO PLOT CHANGES
    if(_info->_equation.empty()){
        cout<<"no equation!!"<<endl;
        _screen_points.clear();
    }
    else
        _screen_points=_plotter();
}

void Graph::draw(sf::RenderWindow& window){    //MAKE SURE THAT UPDATE IS CALLED BEFORE DRAW!!
    _draw_background(window);
    _draw_points(window);
    _draw_labels(window);
}

void Graph::_draw_background(sf::RenderWindow& window){
    //background
    sf::RectangleShape background(sf::Vector2f(GRAPH_WIDTH+GRAPH_PADDING,GRAPH_HEIGHT+GRAPH_PADDING));
    background.setPosition(sf::Vector2f(0,0));
    background.setFillColor(sf::Color::Black);
    window.draw(background);

    //grid border
    sf::RectangleShape border(sf::Vector2f(GRAPH_WIDTH,GRAPH_HEIGHT));
    border.setPosition(sf::Vector2f(GRAPH_PADDING/2,GRAPH_PADDING/2));
    border.setFillColor(sf::Color::Black);
    border.setOutlineColor(sf::Color::White);
    border.setOutlineThickness(LINE_WEIGHT);
    window.draw(border);
    
    //y axis
    sf::RectangleShape yaxis(sf::Vector2f(LINE_WEIGHT*2,GRAPH_HEIGHT));
    yaxis.setPosition(sf::Vector2f(_info->_origin.x-LINE_WEIGHT+GRAPH_PADDING/2,GRAPH_PADDING/2));
    yaxis.setFillColor(sf::Color::White);
    window.draw(yaxis);

    //x axis
    sf::RectangleShape xaxis(sf::Vector2f(GRAPH_WIDTH,LINE_WEIGHT*2));
    xaxis.setPosition(sf::Vector2f(GRAPH_PADDING/2,_info->_origin.y-LINE_WEIGHT+GRAPH_PADDING/2));
    xaxis.setFillColor(sf::Color::White);
    window.draw(xaxis); 
}
void Graph::_draw_points(sf::RenderWindow& window){
    for(int i=0; i<_screen_points.size(); i++){       
        if((_screen_points[i].x>GRAPH_PADDING/2 && _screen_points[i].x<GRAPH_WIDTH+GRAPH_PADDING/2) && 
        (_screen_points[i].y>GRAPH_PADDING/2 && _screen_points[i].y<GRAPH_HEIGHT+GRAPH_PADDING/2)){
            sf::CircleShape point(POINT_RADIUS);
            point.setPosition(_screen_points[i]);
            point.setFillColor(sf::Color::Red);
            window.draw(point);
        }
        // else if(_screen_points[i].y<GRAPH_PADDING/2 || _screen_points[i].y>SCREEN_HEIGHT+GRAPH_PADDING/2){
        else if((_screen_points[i].x>=0 && _screen_points[i].x<=GRAPH_WIDTH+GRAPH_PADDING) && 
        (_screen_points[i].y>=0 && _screen_points[i].y<=GRAPH_HEIGHT+GRAPH_PADDING)){
            sf::CircleShape point(POINT_RADIUS);
            point.setPosition(_screen_points[i]);
            point.setFillColor(sf::Color(255,0,0,255/4)); //red, 25% opacity
            window.draw(point);
            if(graphDebug){cout<<"out of bounds border: screenCoords["<<i<<"]=("<<_screen_points[i].x<<","<<_screen_points[i].y<<")\n";}
        }
        else if(graphDebug){cout<<"out of bounds screen: screenCoords["<<i<<"]=("<<_screen_points[i].x<<","<<_screen_points[i].y<<")\n";}
    }
}
void Graph::_draw_labels(sf::RenderWindow& window){
    string eq="Graphing y = [ "+_info->_equation+" ]";
    _equation_label.setString(eq);
    window.draw(_equation_label);

    if(_info->_graph_info){
        string pt="Number of points: "+to_string(_info->_num_points);
        _point_counter.setString(pt);
        window.draw(_point_counter);

        string dm="Domain: ["+to_string(_info->_domain.x)+", "+to_string(_info->_domain.y)+"]";
        _domain_display.setString(dm);
        window.draw(_domain_display);

        string rg="Range: ["+to_string(_info->_range.x)+", "+to_string(_info->_range.y)+"]";
        _range_display.setString(rg);
        window.draw(_range_display);
    }
}

void Graph::_init_sfml(){
    //init font
    if(!_font.loadFromFile("arial.ttf")){
        cout<<"GRAPH INIT_SFML(): Font failed to load"<<endl;
        cin.get();
        exit(-1);
    }
    
    //init label (revisit)
    _equation_label=sf::Text("EQUATION LABEL", _font);
    _equation_label.setCharacterSize(20);
    _equation_label.setStyle(sf::Text::Bold);
    _equation_label.setFillColor(sf::Color::White);
    _equation_label.setPosition(sf::Vector2f(10, SCREEN_HEIGHT-GRAPH_PADDING/1.5));

    //init point counter
    _point_counter=sf::Text("POINT COUNTER", _font);
    _point_counter.setCharacterSize(15);
    _point_counter.setStyle(sf::Text::Regular);
    _point_counter.setFillColor(sf::Color::White);
    _point_counter.setPosition(sf::Vector2f(500, SCREEN_HEIGHT-GRAPH_PADDING/2));
    
    //init domain display
    _domain_display=sf::Text("DOMAIN DISPLAY", _font);
    _domain_display.setCharacterSize(15);
    _domain_display.setStyle(sf::Text::Regular);
    _domain_display.setFillColor(sf::Color::White);
    _domain_display.setPosition(sf::Vector2f(800, SCREEN_HEIGHT-GRAPH_PADDING/2));
    
    //init range display
    _range_display=sf::Text("RANGE DISPLAY", _font);
    _range_display.setCharacterSize(15);
    _range_display.setStyle(sf::Text::Regular);
    _range_display.setFillColor(sf::Color::White);
    _range_display.setPosition(sf::Vector2f(800, SCREEN_HEIGHT-GRAPH_PADDING));
}