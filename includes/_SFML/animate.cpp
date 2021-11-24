#include "animate.h"

Animate::Animate():_info(new GraphInfo()),_sidebar(WORK_PANEL, SIDE_BAR),_system(_info),_textbox(_info){
    cout<<"Animate CTOR: TOP"<<endl;
    _window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "GRAPHING CALCULATOR");
    _window.setFramerateLimit(15);

    _command=-1;
    _mouse_in=true;

    _cursor=sf::CircleShape();
    _cursor.setRadius(2.5);
    _cursor.setFillColor(sf::Color::Red);

    cout<<"Animate instantiated successfully."<<endl;
}
void Animate::run(){ 
    while (_window.isOpen()){
        processEvents();
        update();
        render(); //clear/Draw/display
    }
    cout<<endl<<"-------ANIMATE MAIN LOOP EXITING ------------"<<endl;
}
void Animate::render(){
    _window.clear();
    Draw();                                 //calling animate's Draw --> calls system & sidebar Draw
    _window.display();
}

void Animate::processEvents(){
    sf::Event event;
    float mouseX, mouseY;
    while(_window.pollEvent(event)){
        
        if(_textbox.selected())
            _textbox._sort_input(event);

        else{
            //REENTERING FROM TEXTBOX SELECTION?===================================
            _sidebar[SB_FUNCTION_MODE]="NOT IN FUNCTION MODE";     //clean this later
            // if(_textbox.modified()){
            //     cout<<"textbox was modified. entering cmd to update graph"<<endl;
            //     _command=ENTER_EQ;  //did not previously get passed to system
            // }
            // need to figure out a flag (within textbox class?) indicating to pass new eq w/ cmd to update graph 

            //=====================================================================
            
            switch (event.type){        //check the type of event
            case sf::Event::Closed:     // _window closed
                _window.close();
                break;
            //KEYBOARD INPUT=======================================================
            {
            case sf::Event::KeyPressed:
                switch(event.key.code){
                //OTHER============================================================
                case sf::Keyboard::Enter:
                    _sidebar[SB_KEY_PRESSED] = "ENTER";          //update eq to graph
                    _sidebar[SB_COMMAND_NAME] = "ENTER EQUATION";
                    _sidebar[SB_FUNCTION_MODE]="IN FUNCTION MODE";
                    _textbox.select();
                    cout<<"exiting case enter"<<endl;
                    break;
                case sf::Keyboard::Escape:
                    _sidebar[SB_KEY_PRESSED] = "ESC: EXIT";      //use to exit
                    _window.close();
                    _command=ESCAPE;
                    break;
                    
                //NUMBERS (default equations)=======================================
                case sf::Keyboard::Num0:
                    _sidebar[SB_KEY_PRESSED] = "NUM 0";
                    _sidebar[SB_COMMAND_NAME] = "DEFAULT GRAPH 0";
                    _sidebar[SB_EQUATION_LABEL] = DEFAULT_EQUATION0;
                    _command=NUM_0;
                    break;
                case sf::Keyboard::Num1:
                    _sidebar[SB_KEY_PRESSED] = "NUM 1";
                    _sidebar[SB_COMMAND_NAME] = "DEFAULT GRAPH 1";
                    _sidebar[SB_EQUATION_LABEL] = DEFAULT_EQUATION1;
                    _command=NUM_1;
                    break;
                case sf::Keyboard::Num2:
                    _sidebar[SB_KEY_PRESSED] = "NUM 2";
                    _sidebar[SB_COMMAND_NAME] = "DEFAULT GRAPH 2";
                    _sidebar[SB_EQUATION_LABEL] = DEFAULT_EQUATION2;
                    _command=NUM_2;
                    break;
                case sf::Keyboard::Num3:
                    _sidebar[SB_KEY_PRESSED] = "NUM 3";
                    _sidebar[SB_COMMAND_NAME] = "DEFAULT GRAPH 3";
                    _sidebar[SB_EQUATION_LABEL] = DEFAULT_EQUATION3;
                    _command=NUM_3;
                    break;
                case sf::Keyboard::Num4:
                    _sidebar[SB_KEY_PRESSED] = "NUM 4";
                    _sidebar[SB_COMMAND_NAME] = "DEFAULT GRAPH 4";
                    _sidebar[SB_EQUATION_LABEL] = DEFAULT_EQUATION3;
                    _command=NUM_4;
                    break;

                //LETTERS==========================================================
                case sf::Keyboard::R:
                    _sidebar[SB_KEY_PRESSED] = "R";
                    _sidebar[SB_COMMAND_NAME] = "RESET";
                    _command=RESET;
                    break;
                case sf::Keyboard::H:
                case sf::Keyboard::C:
                    _sidebar[SB_KEY_PRESSED] = "C/H";
                    _sidebar[SB_COMMAND_NAME] = "CENTER";
                    _command=CENTER;
                    break;
                case sf::Keyboard::I:
                    _sidebar[SB_KEY_PRESSED] = "I";
                    _sidebar[SB_COMMAND_NAME] = "GRAPH INFO";
                    _command=INFO_LABEL;
                    break;
                case sf::Keyboard::U:
                case sf::Keyboard::F:
                    _sidebar[SB_KEY_PRESSED] = "F/U";
                    _sidebar[SB_COMMAND_NAME] = "FORCE UPDATE";
                    _command=FORCE_UPDATE;
                    break;
                
                //PANNING/ARROW KEYS===============================================
                case sf::Keyboard::Right:
                    _sidebar[SB_KEY_PRESSED] = "RIGHT ARROW";    //use to pan
                    _sidebar[SB_COMMAND_NAME] = "PAN RIGHT";
                    _command=PAN_RIGHT;
                    break;
                case sf::Keyboard::Left:
                    _sidebar[SB_KEY_PRESSED] = "LEFT ARROW";     //use to pan
                    _sidebar[SB_COMMAND_NAME] = "PAN LEFT";
                    _command=PAN_LEFT;
                    break;
                case sf::Keyboard::Up:
                    _sidebar[SB_KEY_PRESSED] = "UP ARROW";       //use to pan
                    _sidebar[SB_COMMAND_NAME] = "PAN UP";
                    _command=PAN_UP;
                    break;
                case sf::Keyboard::Down:
                    _sidebar[SB_KEY_PRESSED] = "DOWN ARROW";     //use to pan
                    _sidebar[SB_COMMAND_NAME] = "PAN DOWN";
                    _command=PAN_DOWN;
                    break;
                
                //ZOOMING==========================================================
                case sf::Keyboard::Equal:
                    _sidebar[SB_KEY_PRESSED] = "PLUS";           //zoom in
                    _sidebar[SB_COMMAND_NAME] = "ZOOM IN";
                    _command=ZOOM_IN;
                    break;
                case sf::Keyboard::Hyphen:
                    _sidebar[SB_KEY_PRESSED] = "MINUS";          //zoom out
                    _sidebar[SB_COMMAND_NAME] = "ZOOM OUT";
                    _command=ZOOM_OUT;
                    break;

                //POINTS PLOTTED===================================================
                case sf::Keyboard::RBracket:
                    _sidebar[SB_KEY_PRESSED] = "RBRACKET";       //increase # pts
                    _sidebar[SB_COMMAND_NAME] = "INCREASE POINTS";
                    _command=INC_PTS;
                    break;
                case sf::Keyboard::LBracket:
                    _sidebar[SB_KEY_PRESSED] = "LEFT BRACKET";   //decrease # pts
                    _sidebar[SB_COMMAND_NAME] = "DECREASE POINTS";
                    _command=DEC_PTS;
                    break;
                }
                break;
            }

            //MOUSE INPUT==========================================================
            case sf::Event::MouseEntered:
                _mouse_in=true;
                break;
            case sf::Event::MouseLeft:
                _mouse_in=false;
                break;
            case sf::Event::MouseMoved:
                mouseX=event.mouseMove.x;
                mouseY=event.mouseMove.y;
                break;
            case sf::Event::MouseButtonReleased:
                if(event.mouseButton.button == sf::Mouse::Right){
                    _sidebar[SB_MOUSE_CLICKED]="RIGHT CLICK "+mouse_pos_string(_window);}
                else{
                    _sidebar[SB_MOUSE_CLICKED]="LEFT CLICK "+mouse_pos_string(_window);}
                break;
            
            //=====================================================================
            default:
                break;
            }
        }
    }
}
void Animate::update(){
    _system.Step(_command, _info);
    _command=-1;     //resetting _command

    //_equation_label.setString(_info->_equation);  //needs tp be updated HERE!! use to display input from user before graphing :)

    if(_mouse_in){
        _cursor.setPosition(sf::Mouse::getPosition(_window).x-2.5, sf::Mouse::getPosition(_window).y-2.5);   //_cursor red dot:
        _sidebar[SB_MOUSE_POSITION] = mouse_pos_string(_window);  //mouse location text for sidebar:
    }
}
void Animate::Draw(){
    _system.Draw(_window);
    _sidebar.Draw(_window); 
    _textbox.Draw(_window);

    if(_mouse_in){_window.draw(_cursor);}     //drawing dot to follow cursor --> draw last so it appears above everything else   
    //- - - - - - - - - - - - - - - - - - -
    //getPosition() gives you screen coords, getPosition(_window) gives you _window coords
    //cout<<"mosue pos: "<<sf::Mouse::getPosition(_window).x<<", "<<sf::Mouse::getPosition(_window).y<<endl;
    //- - - - - - - - - - - - - - - - - - -
}

string mouse_pos_string(sf::RenderWindow& _window){
    return "("+to_string(sf::Mouse::getPosition(_window).x)+", "+to_string(sf::Mouse::getPosition(_window).y)+")";
}