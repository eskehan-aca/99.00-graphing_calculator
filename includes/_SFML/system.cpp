#include "system.h"

System::System(GraphInfo* info):_g(info){
    _init_graph_info(info);
    cout<<"System instantiated successfully"<<endl;
}

//------------------------------------------------------------------

void System::Step(int command, GraphInfo* info){
    switch(command){
    //exit early
    case ESCAPE:
    case SAVE: 
    case -1: 
        break;
    float prevMin, prevMax, temp;
    
    //LETTERS==================================================================
    case ENTER_EQ:      if(systemDebug){cout<<"SYSTEM::STEP() switch ENTER_EQ"<<endl;}
    case HISTORY:
    case LOAD:
    case FORCE_UPDATE:
        _calculate_graph_info(info);
        _g.update();
        break;
    case RESET:
        _init_graph_info(info);
        _g.update();
        break;
    case HOME:
        info->_domain=sf::Vector2f(DOMAIN_MIN,DOMAIN_MAX);
        info->_range=sf::Vector2f(RANGE_MIN,RANGE_MAX);
    case CENTER:
        prevMin=info->_domain.x;
        prevMax=info->_domain.y;
        temp=(prevMax-prevMin)/2;
        info->_domain=sf::Vector2f(-temp,temp);
        prevMin=info->_range.x;
        prevMax=info->_range.y;
        temp=(prevMax-prevMin)/2;
        info->_range=sf::Vector2f(-temp,temp);
        _calculate_graph_info(info);
        if(systemDebug){cout<<"origin centered: "<<boolalpha<<info->_origin_centered<<endl;}
        _g.update();
        break;
    case INFO_LABEL:
        info->_graph_info=!info->_graph_info;
        break;

    //PANNING/ARROW KEYS=======================================================
    case PAN_RIGHT:
        prevMin=info->_domain.x;
        prevMax=info->_domain.y;
        temp=(prevMax-prevMin)/10;
        info->_domain=sf::Vector2f(prevMin+temp,prevMax+temp);
        _calculate_graph_info(info);
        _g.update();
        break;
    case PAN_LEFT:
        prevMin=info->_domain.x;
        prevMax=info->_domain.y;
        temp=(prevMax-prevMin)/10;
        info->_domain=sf::Vector2f(prevMin-temp,prevMax-temp);
        _calculate_graph_info(info);
        _g.update();
        break;
    case PAN_UP:
        prevMin=info->_range.x;
        prevMax=info->_range.y;
        temp=(prevMax-prevMin)/10;
        info->_range=sf::Vector2f(prevMin+temp,prevMax+temp);
        _calculate_graph_info(info);
        _g.update();
        break;
    case PAN_DOWN:
        prevMin=info->_range.x;
        prevMax=info->_range.y;
        temp=(prevMax-prevMin)/10;
        info->_range=sf::Vector2f(prevMin-temp,prevMax-temp);
        _calculate_graph_info(info);
        _g.update();
        break;
    
    //ZOOMING==================================================================
    case ZOOM_OUT:
        //domain
        prevMin=info->_domain.x;
        prevMax=info->_domain.y;
        temp=(prevMax-prevMin)/10;
        if(systemDebug){cout<<"zoom scale: "<<temp<<endl;}
        info->_domain=sf::Vector2f(prevMin-temp,prevMax+temp);
        //range
        prevMin=info->_range.x;
        prevMax=info->_range.y;
        temp=(prevMax-prevMin)/10;
        info->_range=sf::Vector2f(prevMin-temp,prevMax+temp);
        _calculate_graph_info(info);
        _g.update();
        break;
    case ZOOM_IN:
        //domain
        prevMin=info->_domain.x;
        prevMax=info->_domain.y;
        temp=(prevMax-prevMin)/10;
        if(systemDebug){cout<<"zoom scale: "<<temp<<endl;}
        info->_domain=sf::Vector2f(prevMin+temp,prevMax-temp);
        //range
        prevMin=info->_range.x;
        prevMax=info->_range.y;
        temp=(prevMax-prevMin)/10;
        info->_range=sf::Vector2f(prevMin+temp,prevMax-temp);
        _calculate_graph_info(info);
        _g.update();
        break;
    
    //POINTS PLOTTED===========================================================
    case INC_PTS:
        info->_num_points+=10;
        _calculate_graph_info(info);
        _g.update();
        break;
    case DEC_PTS:
        info->_num_points-=10;
        _calculate_graph_info(info);
        _g.update(); 
        break;

    //=========================================================================
    default:
        if(systemDebug){cout<<"SYSTEM::STEP(): switch UNKNOWN ["<<command<<"]"<<endl;}
        break;
    }
}

void System::Draw(sf::RenderWindow& window){
    window.clear();
    _g.draw(window);
}
void System::_init_graph_info(GraphInfo* info){
    if(systemDebug){cout<<"System: initializing GraphInfo"<<endl;}
    
    info->_equation=DEFAULT_EQUATION0;
    info->_graph_info=false;

    //CHANGING THESE MEANS WE HAVE TO RECALCULATE GRAPH INFO (call funct)
    info->_window_dimensions=sf::Vector2f(GRAPH_WIDTH,GRAPH_HEIGHT);
    info->_domain=sf::Vector2f(DOMAIN_MIN,DOMAIN_MAX);
    info->_range=sf::Vector2f(RANGE_MIN,RANGE_MAX);
    info->_num_points=NUM_POINTS;

    //CALLING GRAPHINFO TO INIT EVERYTHING ELSE
    _calculate_graph_info(info);
}
void System::_calculate_graph_info(GraphInfo* info){
    float x,y;

    //calculate _delta
    x=(info->_domain.y-info->_domain.x)/(info->_num_points-1);
    y=(info->_range.y-info->_range.x)/(info->_num_points-1);
    info->_delta=sf::Vector2f(x,y);
    
    //calculate _scale
    x=(GRAPH_WIDTH+GRAPH_PADDING)/(info->_num_points-1);
    y=(GRAPH_WIDTH+GRAPH_PADDING)/(info->_num_points-1);
    // currently just have the graph be square
    // y=GRAPH_HEIGHT/(info->_num_points-1);
    info->_scale=sf::Vector2f(x,y);
    
    //calculate _origin 
    x=(0-info->_domain.x)*(GRAPH_WIDTH/(info->_domain.y-info->_domain.x));
    y=(info->_range.y-0)*(GRAPH_HEIGHT/(info->_range.y-info->_range.x));
    info->_origin=sf::Vector2f(x,y);

    //determine if origin centered
    info->_origin_centered=(info->_origin==sf::Vector2f(GRAPH_WIDTH/2,GRAPH_HEIGHT/2));
}