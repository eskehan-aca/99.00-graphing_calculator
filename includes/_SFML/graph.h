#ifndef GRAPH_H
#define GRAPH_H
#include "../constants.h"
#include "../_MATH/plot/plot.h"

using namespace std;
class Graph{
public:
    Graph(GraphInfo* info);

    void update();                          //update vector of screenpts!
    void draw(sf::RenderWindow& window);    //main part
    
    void printpts();    //temp accessor

private:
    GraphInfo* _info;
    Plot _plotter;
    vector<sf::Vector2f> _screen_points;

    //SFML THINGS (font?)
    //sf::Text _equation_label;

    //PRIVATE FUNCTIONS
    //funct to draw equation label
    //funct to draw background
    //funct to draw grid pts
};

#endif //GRAPH_H