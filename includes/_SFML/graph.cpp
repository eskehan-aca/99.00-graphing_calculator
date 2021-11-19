#include "graph.h"

Graph::Graph(GraphInfo* info):_plotter(info),_info(info){
    update();
    _init_sfml();
}

void Graph::update(){    //MAKE SURE THAT UPDATE IS CALLED WHENEVER _INFO CHANGES
    _screen_points=_plotter();
}

void Graph::draw(sf::RenderWindow& window){    //MAKE SURE THAT UPDATE IS CALLED BEFORE DRAW!!
    _draw_background(window);
    _draw_points(window);
    _draw_label(window);
}

void Graph::_draw_background(sf::RenderWindow& window){
    //grid background
    sf::RectangleShape grid(sf::Vector2f(GRAPH_WIDTH,GRAPH_HEIGHT));
    grid.setPosition(sf::Vector2f(0,0));
    grid.setFillColor(sf::Color::Black);
    grid.setOutlineColor(sf::Color::White);
    grid.setOutlineThickness(LINE_WEIGHT);
    window.draw(grid);
    
    //y axis
    sf::RectangleShape yaxis(sf::Vector2f(LINE_WEIGHT*2,GRAPH_HEIGHT));
    yaxis.setPosition(sf::Vector2f(_info->_origin.x-LINE_WEIGHT,0));
    yaxis.setFillColor(sf::Color::White);
    window.draw(yaxis);

    //x axis
    sf::RectangleShape xaxis(sf::Vector2f(GRAPH_WIDTH,LINE_WEIGHT*2));
    xaxis.setPosition(sf::Vector2f(0,_info->_origin.y-LINE_WEIGHT));
    xaxis.setFillColor(sf::Color::White);
    window.draw(xaxis); 
}
void Graph::_draw_points(sf::RenderWindow& window){
    for(int i=0; i<_screen_points.size(); i++){       
        if(_screen_points[i].x<GRAPH_WIDTH && _screen_points[i].y<GRAPH_HEIGHT){
            sf::CircleShape point(POINT_RADIUS);
            point.setPosition(_screen_points[i]);
            point.setFillColor(sf::Color::Red);
            window.draw(point);
        }
        else if(_screen_points[i].x<SCREEN_WIDTH && _screen_points[i].y<SCREEN_HEIGHT){
            sf::CircleShape point(POINT_RADIUS);
            point.setPosition(_screen_points[i]);
            point.setFillColor(sf::Color::Red);
            window.draw(point);
            if(graphDebug){cout<<"out of bounds grid: screenCoords["<<i<<"]=("<<_screen_points[i].x<<","<<_screen_points[i].y<<")\n";}
        }
        else if(graphDebug){cout<<"out of bounds screen: screenCoords["<<i<<"]=("<<_screen_points[i].x<<","<<_screen_points[i].y<<")\n";}
    }
}
void Graph::_draw_label(sf::RenderWindow& window){
    string label="Graphing y = [ "+_info->_equation+" ]";
    _equation_label.setString(label);    //revisit this 
    window.draw(_equation_label);
}

void Graph::printpts(){
    for(int i=0; i<_screen_points.size(); i++){
        cout<<"("<<_screen_points[i].x<<", "<<_screen_points[i].y<<") ";}
}

void Graph::_init_sfml(){
    //init font
    if (!_font.loadFromFile("arial.ttf")){
        cout<<"GRAPH INIT_SFML(): Font failed to load"<<endl;
        cin.get();
        exit(-1);
    }
    
    //init label (revisit)
    _equation_label=sf::Text(_info->_equation, _font);
    _equation_label.setCharacterSize(20);
    _equation_label.setStyle(sf::Text::Bold);
    _equation_label.setFillColor(sf::Color::White);
    _equation_label.setPosition(sf::Vector2f(10, GRAPH_HEIGHT-_equation_label.getLocalBounds().height+5));
}