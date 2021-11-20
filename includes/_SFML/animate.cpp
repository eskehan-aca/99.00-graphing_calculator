#include "animate.h"

Animate::Animate():_info(new GraphInfo()),sidebar(WORK_PANEL, SIDE_BAR),_system(_info){
    cout<<"Animate CTOR: TOP"<<endl;
    _window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "GRAPHING CALCULATOR");
    _window.setFramerateLimit(15);

    mouseIn=true;
    _cursor=sf::CircleShape();
    _cursor.setRadius(2.5);
    _cursor.setFillColor(sf::Color::Red);

    /*
    cout<<"load font"<<endl;
    if (!font.loadFromFile("arial.ttf")){
        cout<<"Animate() CTOR: Font failed to load"<<endl;
        cin.get();
        exit(-1);
    }
    //label for orig eq: (move this to graph class later)
    //make sure to modify this when eq gets changed
    _equation_label = sf::Text("USER INPUT", font);
    _equation_label.setCharacterSize(20);
    _equation_label.setStyle(sf::Text::Bold);
    _equation_label.setFillColor(sf::Color::White);
    _equation_label.setPosition(sf::Vector2f(10, GRAPH_HEIGHT-_equation_label.getLocalBounds().height-5));
    */

    cout<<"Animate instantiated successfully."<<endl;
}

void Animate::Draw(){
    _system.Draw(_window);
    sidebar.Draw(_window); 
    _window.draw(_equation_label);          //print equation text on top of graph --> check that this is updated?
                                            //move this to graph class eventually:)
    if(mouseIn){_window.draw(_cursor);}     //drawing dot to follow cursor --> draw last so it appears above everything else   
    //- - - - - - - - - - - - - - - - - - -
    //getPosition() gives you screen coords, getPosition(_window) gives you _window coords
    //cout<<"mosue pos: "<<sf::Mouse::getPosition(_window).x<<", "<<sf::Mouse::getPosition(_window).y<<endl;
    //- - - - - - - - - - - - - - - - - - -
}

void Animate::update(){
    _system.Step(command, _info);
    command=-1;     //resetting command

    //_equation_label.setString(_info->_equation);  //needs tp be updated HERE!! use to display input from user before graphing :)

    if(mouseIn){
        _cursor.setPosition(sf::Mouse::getPosition(_window).x-2.5, sf::Mouse::getPosition(_window).y-2.5);   //_cursor red dot:
        sidebar[SB_MOUSE_POSITION] = mouse_pos_string(_window);  //mouse location text for sidebar:
    }
}
void Animate::render(){
    _window.clear();
    Draw();
    _window.display();
}
void Animate::processEvents(){
    sf::Event event;
    float mouseX, mouseY;
    while(_window.pollEvent(event)){//or waitEvent
        
        switch (event.type){//check the type of event
        case sf::Event::Closed:     // _window closed
            _window.close();
            break;
        
        //KEYBOARD INPUT=======================================================
        {
        case sf::Event::KeyPressed:
            switch(event.key.code){

            //NUMERS (default equations)=======================================
            case sf::Keyboard::Num0:
                sidebar[SB_KEY_PRESSED] = "NUM 0";
                sidebar[SB_COMMAND_NAME] = "DEFAULT GRAPH 0";
                sidebar[SB_EQUATION_LABEL] = DEFAULT_EQUATION0;
                command=NUM_0;
                break;
            case sf::Keyboard::Num1:
                sidebar[SB_KEY_PRESSED] = "NUM 1";
                sidebar[SB_COMMAND_NAME] = "DEFAULT GRAPH 1";
                sidebar[SB_EQUATION_LABEL] = DEFAULT_EQUATION1;
                command=NUM_1;
                break;
            case sf::Keyboard::Num2:
                sidebar[SB_KEY_PRESSED] = "NUM 2";
                sidebar[SB_COMMAND_NAME] = "DEFAULT GRAPH 2";
                sidebar[SB_EQUATION_LABEL] = DEFAULT_EQUATION2;
                command=NUM_2;
                break;
            case sf::Keyboard::Num3:
                sidebar[SB_KEY_PRESSED] = "NUM 3";
                sidebar[SB_COMMAND_NAME] = "DEFAULT GRAPH 3";
                sidebar[SB_EQUATION_LABEL] = DEFAULT_EQUATION3;
                command=NUM_3;
                break;
            case sf::Keyboard::Num4:
                sidebar[SB_KEY_PRESSED] = "NUM 4";
                sidebar[SB_COMMAND_NAME] = "DEFAULT GRAPH 4";
                sidebar[SB_EQUATION_LABEL] = DEFAULT_EQUATION3;
                command=NUM_4;
                break;

            //LETTERS==========================================================
            case sf::Keyboard::R:
                sidebar[SB_KEY_PRESSED] = "R";
                sidebar[SB_COMMAND_NAME] = "RESET";
                command=R;
                break;
            case sf::Keyboard::C:
                sidebar[SB_KEY_PRESSED] = "C";
                sidebar[SB_COMMAND_NAME] = "RESET";
                command=C;
                break;
            case sf::Keyboard::F:
                sidebar[SB_KEY_PRESSED] = "F";
                sidebar[SB_COMMAND_NAME] = "FORCE UPDATE";
                command=F;
                break;
            
            //PANNING/ARROW KEYS===============================================
            case sf::Keyboard::Right:
                sidebar[SB_KEY_PRESSED] = "RIGHT ARROW";    //use to pan
                sidebar[SB_COMMAND_NAME] = "PAN RIGHT";
                command=RIGHT;
                break;
            case sf::Keyboard::Left:
                sidebar[SB_KEY_PRESSED] = "LEFT ARROW";     //use to pan
                sidebar[SB_COMMAND_NAME] = "PAN LEFT";
                command=LEFT;
                break;
            case sf::Keyboard::Up:
                sidebar[SB_KEY_PRESSED] = "UP ARROW";       //use to pan
                sidebar[SB_COMMAND_NAME] = "PAN UP";
                command=UP;
                break;
            case sf::Keyboard::Down:
                sidebar[SB_KEY_PRESSED] = "DOWN ARROW";     //use to pan
                sidebar[SB_COMMAND_NAME] = "PAN DOWN";
                command=DOWN;
                break;
            
            //ZOOMING==========================================================
            case sf::Keyboard::Equal:
                sidebar[SB_KEY_PRESSED] = "PLUS";           //zoom in
                sidebar[SB_COMMAND_NAME] = "ZOOM IN";
                command=PLUS;
                break;
            case sf::Keyboard::Hyphen:
                sidebar[SB_KEY_PRESSED] = "MINUS";          //zoom out
                sidebar[SB_COMMAND_NAME] = "ZOOM OUT";
                command=MINUS;
                break;

            //POINTS PLOTTED===================================================
            case sf::Keyboard::RBracket:
                sidebar[SB_KEY_PRESSED] = "RBRACKET";       //increase # pts
                sidebar[SB_COMMAND_NAME] = "INCREASE POINTS";
                command=RBRACKET;
                break;
            case sf::Keyboard::LBracket:
                sidebar[SB_KEY_PRESSED] = "LEFT BRACKET";   //decrease # pts
                sidebar[SB_COMMAND_NAME] = "DECREASE POINTS";
                command=LBRACKET;
                break;
            
            //OTHER============================================================
            case sf::Keyboard::Enter:
                sidebar[SB_KEY_PRESSED] = "ENTER";          //update
                sidebar[SB_COMMAND_NAME] = "ENTER";
                command=ENTER;
                break;
            case sf::Keyboard::Escape:
                sidebar[SB_KEY_PRESSED] = "ESC: EXIT";      //use to exit
                _window.close();
                command=ESCAPE;
                break;
            }
            break;
        }

        //MOUSE INPUT==========================================================
        case sf::Event::MouseEntered:
            mouseIn=true;
            break;
        case sf::Event::MouseLeft:
            mouseIn=false;
            break;
        case sf::Event::MouseMoved:
            mouseX=event.mouseMove.x;
            mouseY=event.mouseMove.y;
            break;
        case sf::Event::MouseButtonReleased:
            if(event.mouseButton.button == sf::Mouse::Right){
                sidebar[SB_MOUSE_CLICKED]="RIGHT CLICK "+mouse_pos_string(_window);}
            else{
                sidebar[SB_MOUSE_CLICKED]="LEFT CLICK "+mouse_pos_string(_window);}
            break;
        
        //=====================================================================
        default:
            break;
        }
    }
}
void Animate::run(){ 
    while (_window.isOpen()){
        processEvents();
        update();
        render(); //clear/Draw/display
    }
    cout<<endl<<"-------ANIMATE MAIN LOOP EXITING ------------"<<endl;
}

string mouse_pos_string(sf::RenderWindow& _window){
    return "("+to_string(sf::Mouse::getPosition(_window).x)+", "+to_string(sf::Mouse::getPosition(_window).y)+")";
}
