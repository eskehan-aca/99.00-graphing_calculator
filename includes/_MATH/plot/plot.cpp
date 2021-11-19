#include "plot.h"

Plot::Plot(GraphInfo* info):_info(info){}

vector<sf::Vector2f> Plot::operator()(){
    //init RPN obj with postfix queue 
    Tokenize eq(_info->_equation);
    ShuntingYard sy(eq.get_token_queue());
    RPN rpn(sy.postfix());
    
    //getting graph coords from RPN obj
    vector<sf::Vector2f> coords;
    for(int i=0; i<_info->_num_points; i++){
        double xval=(_info->_domain.x)+(i*_info->_delta);
        double yval=rpn(xval);
        coords.push_back(sf::Vector2f(xval,yval));
    }
    if(plotDebug){
        cout<<"plot class coordinates: ";
        for(int i=0; i<coords.size(); i++)
            cout<<"["<<i<<"]("<<coords[i].x<<", "<<coords[i].y<<")  ";
    }
    
    //translate graph coords into screen coords
    Translate convert(_info);
    coords=convert.translate(coords);
    if(plotDebug){
        cout<<"screen coordinates: ";
        for(int i=0; i<coords.size(); i++)
            cout<<"("<<coords[i].x<<", "<<coords[i].y<<") ";
    }
    return coords;
}