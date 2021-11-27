#include "translate.h"

Translate::Translate(GraphInfo* info):_info(info){}

vector<sf::Vector2f>& Translate::translate(vector<sf::Vector2f>& coords){
    if(translateDebug){
        cout<<"delta x: "<<_info->_delta.x<<endl;
        cout<<"delta y: "<<_info->_delta.y<<endl;

        cout<<"origin x: "<<_info->_origin.x<<endl;
        cout<<"origin y: "<<_info->_origin.y<<endl;

        cout<<"scale x: "<<_info->_scale.x<<endl;
        cout<<"scale y: "<<_info->_scale.y<<endl;
    }
    
    for(int i=0; i<coords.size(); i++){
        if(translateDebug){
            cout<<"standardCoords["<<i<<"]=("<<coords[i].x<<","<<coords[i].y<<")\n";
        }

        float x,y;
        //scale the coordinate
        x=coords[i].x*(_info->_scale.x/_info->_delta.x);
        y=coords[i].y*(_info->_scale.y/_info->_delta.y);                        //CURRENTLY FITS ALL COORDS ON SCREEN --> REVISIT LATER/?
        if(translateDebug){cout<<"scale:  ("<<x<<","<<y<<")\n";}
        //shift to origin
        x=_info->_origin.x+x;
        y=_info->_origin.y-y;
        if(translateDebug){cout<<"shift:  ("<<x<<","<<y<<")\n";}
        //shift to accomodate graph padding
        x=x+GRAPH_PADDING/2;
        y=y+GRAPH_PADDING/2;
        if(translateDebug){cout<<"shift:  ("<<x<<","<<y<<")\n";}
        //shift to accomodate point_radius
        x-=POINT_RADIUS;
        y-=POINT_RADIUS;
        if(translateDebug){cout<<"radius: ("<<x<<","<<y<<")\n";}

        coords[i]=(sf::Vector2f(x,y));
        if(translateDebug){cout<<"("<<coords[i].x<<","<<coords[i].y<<")\n";}
    }
    
    return coords;
}