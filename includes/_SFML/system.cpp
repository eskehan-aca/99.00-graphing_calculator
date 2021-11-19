#include "system.h"

System::System(GraphInfo* info):_g(info){
    init_graph_info(info);
}

//------------------------------------------------------------------

void System::Step(int command, GraphInfo* info){
    //calls step w/ user commands + new configs
    // pan left/right   ==> change domain
    // zoom in/out      ==> change domain
    // change eq
    // change # pts

    switch(command){
    case 0:
        _g.update();
        break;
    //equation defaults
    case 1:
        info->_equation=DEFAULT_EQUATION1;
        _g.update();
        break;
    case 2:
        info->_equation=DEFAULT_EQUATION2;
        _g.update();
        break;
    case 3:
        info->_equation=DEFAULT_EQUATION3;
        _g.update();
        break;
    case 4:
        info->_equation=DEFAULT_EQUATION4;
        _g.update();
        break;
    //other functs
    default:
        break;
    }
    
    //switch command:
    //case: modify graph info
}

void System::Draw(sf::RenderWindow& window){
    window.clear();
    _g.draw(window);
}
void System::init_graph_info(GraphInfo* info){
    cout<<"setinfo enter"<<endl;
    info->_equation=DEFAULT_EQUATION;
    info->_window_dimensions=sf::Vector2f(GRAPH_WIDTH,GRAPH_HEIGHT);
    
    //THIS NEEDS TO BE DEPENDENT ON DOMAIN/RANGE!!!!!!!!!!!!!!!!! REVISIT
    info->_origin=sf::Vector2f(GRAPH_WIDTH/2,GRAPH_HEIGHT/2);

    info->_domain=sf::Vector2f(DOMAIN_MIN,DOMAIN_MAX);
    info->_range=sf::Vector2f(RANGE_MIN,RANGE_MAX);
    info->_num_points=NUM_POINTS;

    float x=(info->_domain.y-info->_domain.x)/(info->_num_points-1);
    float y=(info->_range.y-info->_range.x)/(info->_num_points-1);
    info->_delta=sf::Vector2f(x,y);
    info->_scale=sf::Vector2f(GRAPH_WIDTH/(info->_num_points-1),GRAPH_HEIGHT/(info->_num_points-1)); //????????
    
    info->_angle=0;                        //????????
}