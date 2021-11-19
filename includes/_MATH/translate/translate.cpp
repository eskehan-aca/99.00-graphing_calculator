#include "translate.h"

Translate::Translate(GraphInfo* info):_info(info){}

vector<sf::Vector2f>& Translate::translate(vector<sf::Vector2f>& coords){
    if(translateDebug){
        cout<<"delta: "<<_info->_delta<<endl;
        cout<<"scalex: "<<_info->_scale.x<<endl;
        cout<<"scaley: "<<_info->_scale.y<<endl;
    }
    
    for(int i=0; i<coords.size(); i++){
        if(translateDebug){
            cout<<"standardCoords["<<i<<"]=("<<coords[i].x<<","<<coords[i].y<<")\n";


            cout<<"origin x: "<<_info->_origin.x<<endl;
            cout<<"origin y: "<<_info->_origin.y<<endl;

            cout<<"scale x: "<<_info->_scale.x<<endl;
            cout<<"scale y: "<<_info->_scale.y<<endl;

        }



        //revisit this with linear scaling       
        float x=_info->_origin.x+(coords[i].x*_info->_scale.x);
        float y=_info->_origin.y-(coords[i].y*_info->_scale.y);

        //accomodate for shift in point_radius
        coords[i]=(sf::Vector2f(x-POINT_RADIUS,y-POINT_RADIUS));
        
        if(translateDebug){cout<<"("<<coords[i].x<<","<<coords[i].y<<")\n";}
    }
    
    return coords;
}