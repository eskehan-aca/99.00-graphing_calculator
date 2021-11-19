#ifndef GRAPH_INFO_H
#define GRAPH_INFO_H
#include "../constants.h"

using namespace std;
struct GraphInfo{
    string _equation;                   //equation string (infix)

    sf::Vector2f _window_dimensions;    //600x600? for rn
    sf::Vector2f _origin;               //graphs's (0,0) in screen coords
    sf::Vector2f _domain;               //from x: [min,max]
    sf::Vector2f _range;                //from y: [min,max]
    
    sf::Vector2f _scale;                //
    sf::Vector2f _delta;                //revisit and later make this vector (make sure to change plot() op)
    
    
    int _num_points;                    //determine from domain/scale?
    int _angle;                         //?
};

#endif //GRAPH_INFO_H