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
    case 1:
        /* code */
        _g.update();
        break;
    
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
    info->_origin=sf::Vector2f(GRAPH_WIDTH/2,GRAPH_HEIGHT/2);
    info->_domain=sf::Vector2f(DOMAIN_MIN,DOMAIN_MAX);
    info->_range=sf::Vector2f(RANGE_MIN,RANGE_MAX);
    info->_num_points=NUM_POINTS;
    info->_delta=((info->_domain.y-info->_domain.x)/(info->_num_points-1));
    info->_scale=sf::Vector2f(GRAPH_WIDTH/(info->_num_points-1),GRAPH_HEIGHT/(info->_num_points-1)); //????????
    info->_angle=0;                        //????????
}