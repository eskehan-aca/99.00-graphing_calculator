#include "system.h"

System::System(GraphInfo* info):_g(info){
    _init_graph_info(info);
}

//------------------------------------------------------------------

void System::Step(int command, GraphInfo* info){
    //confirm if these need to each have _g.update()???
    switch(command){
    case -1: break;     //not a command
    float prevMin, prevMax, temp;
    //DEFAULT EQUATIONS========================================================
    case NUM_0:
        info->_equation=DEFAULT_EQUATION0;
        _g.update();
        break;
    case NUM_1:
        info->_equation=DEFAULT_EQUATION1;
        _g.update();
        break;
    case NUM_2:
        info->_equation=DEFAULT_EQUATION2;
        _g.update();
        break;
    case NUM_3:
        info->_equation=DEFAULT_EQUATION3;
        _g.update();
        break;
    case NUM_4:
        info->_equation=DEFAULT_EQUATION4;
        _g.update();
        break;

    //LETTERS==================================================================
    case R:
        info->_domain=sf::Vector2f(DOMAIN_MIN,DOMAIN_MAX);
        info->_range=sf::Vector2f(RANGE_MIN,RANGE_MAX);
        _calculate_graph_info(info);
        _g.update();
        break;
    case C:
        //revisit --> preserve scale and delta x? just shift (center) domain
        prevMin=info->_domain.x;
        prevMax=info->_domain.y;
        temp=(prevMax-prevMin)/2;
        info->_domain=sf::Vector2f(-temp,temp);
        prevMin=info->_range.x;
        prevMax=info->_range.y;
        temp=(prevMax-prevMin)/2;
        info->_range=sf::Vector2f(-temp,temp);
        _calculate_graph_info(info);
        // assert(info->_origin_centered); //LOL IDK
        cout<<"origin centered: "<<boolalpha<<info->_origin_centered<<endl;
        _g.update();
        break;
    case F:
        _calculate_graph_info(info);
        _g.update();
        break;

    //PANNING/ARROW KEYS=======================================================
    case RIGHT:
        prevMin=info->_domain.x;
        prevMax=info->_domain.y;
        temp=(prevMax-prevMin)/10;
        info->_domain=sf::Vector2f(prevMin+temp,prevMax+temp);
        _calculate_graph_info(info);
        _g.update();
        break;
    case LEFT:
        prevMin=info->_domain.x;
        prevMax=info->_domain.y;
        temp=(prevMax-prevMin)/10;
        info->_domain=sf::Vector2f(prevMin-temp,prevMax-temp);
        _calculate_graph_info(info);
        _g.update();
        break;
    case UP:
        prevMin=info->_range.x;
        prevMax=info->_range.y;
        temp=(prevMax-prevMin)/10;
        info->_range=sf::Vector2f(prevMin+temp,prevMax+temp);
        _calculate_graph_info(info);
        _g.update();
        break;
    case DOWN:
        prevMin=info->_range.x;
        prevMax=info->_range.y;
        temp=(prevMax-prevMin)/10;
        info->_range=sf::Vector2f(prevMin-temp,prevMax-temp);
        _calculate_graph_info(info);
        _g.update();
        break;
    
    //ZOOMING==================================================================
    case PLUS:
        //domain
        prevMin=info->_domain.x;
        prevMax=info->_domain.y;
        temp=(prevMax-prevMin)/10;
        info->_domain=sf::Vector2f(prevMin-temp,prevMax+temp);
        //range
        // prevMin=info->_range.x;
        // prevMax=info->_range.y;
        // temp=(prevMax-prevMin)/10;
        // info->_range=sf::Vector2f(prevMin-temp,prevMin+temp);
        _calculate_graph_info(info);
        _g.update();
        break;
    case MINUS:
        //domain
        prevMin=info->_domain.x;
        prevMax=info->_domain.y;
        temp=(prevMax-prevMin)/10;
        info->_domain=sf::Vector2f(prevMin+temp,prevMax-temp);
        //range
        // prevMin=info->_range.x;
        // prevMax=info->_range.y;
        // temp=(prevMax-prevMin)/10;
        // info->_range=sf::Vector2f(prevMin+temp,prevMin-temp);
        _calculate_graph_info(info);
        _g.update();
        break;
    
    //POINTS PLOTTED===========================================================
    case RBRACKET:
        info->_num_points+=10;
        _calculate_graph_info(info);
        _g.update();
        break;
    case LBRACKET:
        info->_num_points-=10;
        _calculate_graph_info(info);
        _g.update(); 
        break;

    //OTHER====================================================================
    case ENTER:
        //revisit 
        cout<<"press enter: nothing happens :)"<<endl;
        break;
    case ESCAPE:
        cout<<"SYSTEM::STEP() switch ESCAPE: you should not be here!"<<endl; 
        break;

    //=========================================================================
    default:    //??????????
        cout<<"SYSTEM::STEP(): unknown command input ["<<command<<"], updating graph object"<<endl;
        _g.update();
        break;
    }
}

void System::Draw(sf::RenderWindow& window){
    window.clear();
    _g.draw(window);
}
void System::_init_graph_info(GraphInfo* info){
    cout<<"_init_graph_info enter"<<endl;

    info->_equation=DEFAULT_EQUATION0;

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
    x=GRAPH_WIDTH/(info->_num_points-1);
    y=GRAPH_HEIGHT/(info->_num_points-1);
    info->_scale=sf::Vector2f(x,y);
    
    //calculate _origin 
    x=(0-info->_domain.x)*(GRAPH_WIDTH/(info->_domain.y-info->_domain.x));
    y=(info->_range.y-0)*(GRAPH_HEIGHT/(info->_range.y-info->_range.x));
    info->_origin=sf::Vector2f(x,y);

    //determine if origin centered
    info->_origin_centered=(info->_origin==sf::Vector2f(GRAPH_WIDTH/2,GRAPH_HEIGHT/2));
}