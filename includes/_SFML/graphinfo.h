#ifndef GRAPH_INFO_H
#define GRAPH_INFO_H
#include "../constants.h"

using namespace std;
struct GraphInfo{
    string _equation;                   //equation string (infix)

    //update with system: _calculate_graph_info()
    sf::Vector2f _window_dimensions;
    
    sf::Vector2f _domain;               //from x: [min,max]
    sf::Vector2f _range;                //from y: [min,max]

    int _num_points;                    //determine from domain/scale?
    
    //changing the above dimensions changes these!!

    sf::Vector2f _origin;               //graphs's (0,0) in screen coords
    sf::Vector2f _scale;                //scale to multiply points by (translate class)
    sf::Vector2f _delta;                //revisit and later make this vector (make sure to change plot() op)
    
    bool _origin_centered;              //true if origin=GRAPH_WIDTH/2,GRAPH_HEIGHT/2
    bool _graph_info;                   //display graphinfo text :)
};

#endif //GRAPH_INFO_H

//FUTURE FUNCTIONS?
//bool _origin_in                   //true if origin is within graph bounds
//int _angle;                       //?