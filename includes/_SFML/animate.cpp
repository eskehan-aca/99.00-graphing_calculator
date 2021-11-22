#include "animate.h"

Animate::Animate():_info(new GraphInfo()),_sidebar(WORK_PANEL, SIDE_BAR),_system(_info){
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
                _sidebar[SB_KEY_PRESSED] = "NUM 0";
                _sidebar[SB_COMMAND_NAME] = "DEFAULT GRAPH 0";
                _sidebar[SB_EQUATION_LABEL] = DEFAULT_EQUATION0;
                command=NUM_0;
                break;
            case sf::Keyboard::Num1:
                _sidebar[SB_KEY_PRESSED] = "NUM 1";
                _sidebar[SB_COMMAND_NAME] = "DEFAULT GRAPH 1";
                _sidebar[SB_EQUATION_LABEL] = DEFAULT_EQUATION1;
                command=NUM_1;
                break;
            case sf::Keyboard::Num2:
                _sidebar[SB_KEY_PRESSED] = "NUM 2";
                _sidebar[SB_COMMAND_NAME] = "DEFAULT GRAPH 2";
                _sidebar[SB_EQUATION_LABEL] = DEFAULT_EQUATION2;
                command=NUM_2;
                break;
            case sf::Keyboard::Num3:
                _sidebar[SB_KEY_PRESSED] = "NUM 3";
                _sidebar[SB_COMMAND_NAME] = "DEFAULT GRAPH 3";
                _sidebar[SB_EQUATION_LABEL] = DEFAULT_EQUATION3;
                command=NUM_3;
                break;
            case sf::Keyboard::Num4:
                _sidebar[SB_KEY_PRESSED] = "NUM 4";
                _sidebar[SB_COMMAND_NAME] = "DEFAULT GRAPH 4";
                _sidebar[SB_EQUATION_LABEL] = DEFAULT_EQUATION3;
                command=NUM_4;
                break;

            //LETTERS==========================================================
            case sf::Keyboard::R:
                _sidebar[SB_KEY_PRESSED] = "R";
                _sidebar[SB_COMMAND_NAME] = "RESET";
                command=RESET;
                break;
            case sf::Keyboard::H:
            case sf::Keyboard::C:
                _sidebar[SB_KEY_PRESSED] = "C";
                _sidebar[SB_COMMAND_NAME] = "RESET";
                command=CENTER;
                break;
            case sf::Keyboard::I:
                _sidebar[SB_KEY_PRESSED] = "I";
                _sidebar[SB_COMMAND_NAME] = "GRAPH INFO";
                command=INFO_LABEL;
                break;
            case sf::Keyboard::F:
                _sidebar[SB_KEY_PRESSED] = "F";
                _sidebar[SB_COMMAND_NAME] = "FORCE UPDATE";
                command=FORCE_UPDATE;
                break;
            
            //PANNING/ARROW KEYS===============================================
            case sf::Keyboard::Right:
                _sidebar[SB_KEY_PRESSED] = "RIGHT ARROW";    //use to pan
                _sidebar[SB_COMMAND_NAME] = "PAN RIGHT";
                command=PAN_RIGHT;
                break;
            case sf::Keyboard::Left:
                _sidebar[SB_KEY_PRESSED] = "LEFT ARROW";     //use to pan
                _sidebar[SB_COMMAND_NAME] = "PAN LEFT";
                command=PAN_LEFT;
                break;
            case sf::Keyboard::Up:
                _sidebar[SB_KEY_PRESSED] = "UP ARROW";       //use to pan
                _sidebar[SB_COMMAND_NAME] = "PAN UP";
                command=PAN_UP;
                break;
            case sf::Keyboard::Down:
                _sidebar[SB_KEY_PRESSED] = "DOWN ARROW";     //use to pan
                _sidebar[SB_COMMAND_NAME] = "PAN DOWN";
                command=PAN_DOWN;
                break;
            
            //ZOOMING==========================================================
            case sf::Keyboard::Equal:
                _sidebar[SB_KEY_PRESSED] = "PLUS";           //zoom in
                _sidebar[SB_COMMAND_NAME] = "ZOOM IN";
                command=ZOOM_IN;
                break;
            case sf::Keyboard::Hyphen:
                _sidebar[SB_KEY_PRESSED] = "MINUS";          //zoom out
                _sidebar[SB_COMMAND_NAME] = "ZOOM OUT";
                command=ZOOM_OUT;
                break;

            //POINTS PLOTTED===================================================
            case sf::Keyboard::RBracket:
                _sidebar[SB_KEY_PRESSED] = "RBRACKET";       //increase # pts
                _sidebar[SB_COMMAND_NAME] = "INCREASE POINTS";
                command=INC_PTS;
                break;
            case sf::Keyboard::LBracket:
                _sidebar[SB_KEY_PRESSED] = "LEFT BRACKET";   //decrease # pts
                _sidebar[SB_COMMAND_NAME] = "DECREASE POINTS";
                command=DEC_PTS;
                break;
            
            //OTHER============================================================
            case sf::Keyboard::Enter:{
                _sidebar[SB_KEY_PRESSED] = "ENTER";          //update eq to graph
                _sidebar[SB_COMMAND_NAME] = "ENTER";
                command=ENTER;

            /*
                string strInput="";
                while(_window.pollEvent(event)){
                    if(event.type==sf::Event::TextEntered && event.text.unicode<128){
                        strInput+=static_cast<char>(event.text.unicode);
                        cout<<"strinput: ["<<strInput<<"]"<<endl;

                        if(event.text.unicode==13)
                            cout<<"should exit"<<endl;
                    }
                    if(event.type==sf::Event::MouseButtonPressed)
                        cout<<"MOUSE"<<endl;
                }
                cout<<"exit strinput: ["<<strInput<<"]"<<endl;
            */
            /*
                //entering a "function mode" --> should not leave this case

                //print prompt (revisit later)
                //create a new box (input display) to house all of this in

                //create a new event object????????
                //create a string to hold user input 
                //use sf::Event::TextEntered to get user input?
                //replace eq string :) (within System::Step) 

                //if statements to exit textEntered?

                sf::Event textInput;
                string strInput="";
                do{
                    while(_window.pollEvent(textInput) && textInput.type==sf::Event::TextEntered){
                        if(textInput.text.unicode<128){
                            strInput+=static_cast<char>(textInput.text.unicode);
                            cout<<strInput<<endl;
                        }
                    }
                }while(textInput.type==sf::Event::KeyPressed && textInput.key.code!=sf::Keyboard::Enter);
                cout<<strInput<<endl;

                //if function not changed (new str==old str) --> no need to update
            */
            /*
            //enter a loop that gets each letter until enter is hit again
                sf::Event input;
                string input_eq;
                char get;
                while(_window.pollEvent(input)){
                    if(input.type==sf::Event::KeyPressed && input.key.code!=sf::Keyboard::Enter){
                        get==
                    }
                }
            */

                break;
            }
            case sf::Keyboard::Escape:
                _sidebar[SB_KEY_PRESSED] = "ESC: EXIT";      //use to exit
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
void Animate::update(){
    _system.Step(command, _info);
    command=-1;     //resetting command

    //_equation_label.setString(_info->_equation);  //needs tp be updated HERE!! use to display input from user before graphing :)

    if(mouseIn){
        _cursor.setPosition(sf::Mouse::getPosition(_window).x-2.5, sf::Mouse::getPosition(_window).y-2.5);   //_cursor red dot:
        _sidebar[SB_MOUSE_POSITION] = mouse_pos_string(_window);  //mouse location text for sidebar:
    }
}
void Animate::Draw(){
    _system.Draw(_window);
    _sidebar.Draw(_window); 
    
    //_window.draw(_equation_label);        //print equation text on top of graph --> check that this is updated?
                                            //move this to graph class eventually:)
    if(mouseIn){_window.draw(_cursor);}     //drawing dot to follow cursor --> draw last so it appears above everything else   
    //- - - - - - - - - - - - - - - - - - -
    //getPosition() gives you screen coords, getPosition(_window) gives you _window coords
    //cout<<"mosue pos: "<<sf::Mouse::getPosition(_window).x<<", "<<sf::Mouse::getPosition(_window).y<<endl;
    //- - - - - - - - - - - - - - - - - - -
}

string mouse_pos_string(sf::RenderWindow& _window){
    return "("+to_string(sf::Mouse::getPosition(_window).x)+", "+to_string(sf::Mouse::getPosition(_window).y)+")";
}