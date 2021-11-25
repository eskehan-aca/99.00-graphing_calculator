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

private:
    GraphInfo* _info;
    Plot _plotter;
    vector<sf::Vector2f> _screen_points;

    //SFML THINGS (font?)
    sf::Font _font;                      //font to draw on main screen
    sf::Text _equation_label;
    sf::Text _point_counter;
    sf::Text _domain_display;
    sf::Text _range_display;

    //PRIVATE FUNCTIONS
    void _init_sfml();
    void _draw_background(sf::RenderWindow& window);
    void _draw_points(sf::RenderWindow& window);
    void _draw_labels(sf::RenderWindow& window);
};

#endif //GRAPH_H