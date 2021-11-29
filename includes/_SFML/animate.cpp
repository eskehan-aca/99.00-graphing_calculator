#include "animate.h"

Animate::Animate():_info(new GraphInfo()),_sidebar(WORK_PANEL, SIDE_BAR),_system(_info),_textbox(),_keybinds(){
    cout<<"Animate CTOR: TOP"<<endl;
    _window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "GRAPHING CALCULATOR");
    _window.setFramerateLimit(15);

    _cursor=sf::CircleShape();
    _cursor.setRadius(CURSOR_RADIUS);
    _cursor.setFillColor(sf::Color::Red);

    _history.reserve(HISTORY_LIMIT);

    cout<<"load file"<<endl;
    load_file("defaults.txt",_history);
    for(int i=0; i<_history.size(); i++)
        cout<<"["<<i+1<<"]: "<<_history[i]<<endl;

    cout<<"update history"<<endl;
    _sidebar.updateHistory(_history);
    for(int i=0; i<_history.size(); i++)
        cout<<"["<<i+1<<"]: "<<_history[i]<<endl;

    _command=-1;
    _mouse_in=true;

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
    float mouseX, mouseY, temp;

    while(_window.pollEvent(event)){
    if(_textbox.selected()){
        _textbox.sort_input(event);
        _sidebar[SB_EQUATION_LABEL]=_textbox.text();
        bool exit=_textbox.selected();
        if(!exit){
            _sidebar[SB_FUNCTION_MODE]="not in function mode";  //CLEAN
            if(_textbox.modified()){
                _command=ENTER_EQ;
                _info->_equation=_textbox.text();
                _sidebar[SB_FUNCTION_MODE]="not in function mode";
                _history.insert(_history.begin(),_textbox.text());
                _sidebar.updateHistory(_history);
            }
            else
                _sidebar[SB_EQUATION_LABEL]=_info->_equation;   //restore to prev
        }
    }
    else if(_keybinds.selected()){
        _keybinds.sort_input(event);
        bool exit=_keybinds.selected();
        if(!exit)
            _sidebar[SB_FUNCTION_MODE]="not in function mode";
    }
    else{
        switch (event.type){        //check the type of event
        case sf::Event::Closed:     // _window closed
            _window.close();
            break;            
        //KEYBOARD INPUT=======================================================
        case sf::Event::KeyPressed:
            switch(event.key.code){
            //OTHER============================================================
            case sf::Keyboard::Enter:
                _sidebar[SB_KEY_PRESSED] = "ENTER";
                _sidebar[SB_COMMAND_NAME] = "ENTER EQUATION";
                _sidebar[SB_FUNCTION_MODE]="in function mode";
                _window.pollEvent(event);   //clear enter
                _textbox.select();
                cout<<"exiting case enter"<<endl;
                break;
            case sf::Keyboard::Slash:
                _sidebar[SB_KEY_PRESSED] = "SLASH";
                _sidebar[SB_COMMAND_NAME] = "HELP MENU";
                _sidebar[SB_FUNCTION_MODE]="displaying help menu";
                _window.pollEvent(event);   //clear slash
                _keybinds.select();
                cout<<"exiting case slash"<<endl;
                break;
            case sf::Keyboard::Escape:
                _sidebar[SB_KEY_PRESSED] = "ESC: EXIT";      //use to exit
                _window.close();
                _command=ESCAPE;
                break;
                
            //NUMBERS (access history)=========================================
            case sf::Keyboard::Num1:
                _sidebar[SB_KEY_PRESSED] = "NUM 1";
                _sidebar[SB_COMMAND_NAME] = "HISTORY ITEM 1";
                if(_sidebar[SB_EQUATION_LABEL]!=_history[0] && _history[0]!=_history[1]){
                    _info->_equation=_history[0];
                    _sidebar[SB_EQUATION_LABEL] = _history[0];
                    // _history.insert(_history.begin(),_history[0]);
                    _sidebar.updateHistory(_history);
                    _command=HISTORY;
                }
                break;
            case sf::Keyboard::Num2:
                _sidebar[SB_KEY_PRESSED] = "NUM 2";
                _sidebar[SB_COMMAND_NAME] = "HISTORY ITEM 2";
                _sidebar[SB_EQUATION_LABEL] = _history[1];
                _info->_equation=_history[1];
                if(_history[0]!=_history[1]){
                    _history.insert(_history.begin(),_history[1]);
                    _sidebar.updateHistory(_history);
                }
                _command=HISTORY;
                break;
            case sf::Keyboard::Num3:
                _sidebar[SB_KEY_PRESSED] = "NUM 3";
                _sidebar[SB_COMMAND_NAME] = "HISTORY ITEM 3";
                _sidebar[SB_EQUATION_LABEL] = _history[2];
                _info->_equation=_history[2];
                if(_history[0]!=_history[2]){
                    _history.insert(_history.begin(),_history[2]);
                    _sidebar.updateHistory(_history);
                }
                _command=HISTORY;
                break;
            case sf::Keyboard::Num4:
                _sidebar[SB_KEY_PRESSED] = "NUM 4";
                _sidebar[SB_COMMAND_NAME] = "HISTORY ITEM 4";
                _sidebar[SB_EQUATION_LABEL] = _history[3];
                _info->_equation=_history[3];
                if(_history[0]!=_history[3]){
                    _history.insert(_history.begin(),_history[3]);
                    _sidebar.updateHistory(_history);
                }
                _command=HISTORY;
                break;
        
            //LETTERS==========================================================
            case sf::Keyboard::S:
                if(save_file("test.txt",_history))
                    cout<<"file saved successfully"<<endl;
                _command=SAVE;
                break;
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
                _sidebar[SB_EQUATION_LABEL] = _info->_equation;
                _sidebar[SB_KEY_PRESSED] = "F/U";
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
            if(event.mouseButton.button == sf::Mouse::Left){
                _sidebar[SB_MOUSE_CLICKED]="LEFT CLICK "+mouse_pos_string(_window);
                if(_mouse_in){
                    int i=_sidebar.mouseClick(sf::Mouse::getPosition(_window));
                    if(i!=-1){
                        _sidebar[SB_COMMAND_NAME] = "CLICK HISTORY ITEM "+to_string(i);
                        _sidebar[SB_EQUATION_LABEL] = _history[i-1];
                        _info->_equation=_history[i-1];
                        if(i==1){
                            if(_sidebar[SB_EQUATION_LABEL]!=_history[0] && _history[0]!=_history[1]){
                                _info->_equation=_history[0];
                                _sidebar[SB_EQUATION_LABEL] = _history[0];
                            }
                        }
                        else if(_history[0]!=_history[i-1]){
                            _history.insert(_history.begin(),_history[i-1]);
                        }
                        _sidebar.updateHistory(_history);
                        _command=HISTORY;
                    }
                }
            }
            else{
                _sidebar[SB_MOUSE_CLICKED]="RIGHT CLICK "+mouse_pos_string(_window);}
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
    if(_mouse_in){
        _cursor.setPosition(sf::Mouse::getPosition(_window).x-CURSOR_RADIUS, sf::Mouse::getPosition(_window).y-CURSOR_RADIUS);   //_cursor red dot:
        _sidebar[SB_MOUSE_POSITION] = mouse_pos_string(_window);  //mouse location text for sidebar:
    }
}
void Animate::Draw(){
    _system.Draw(_window);
    _sidebar.Draw(_window); 
    _keybinds.Draw(_window);
    // _textbox.Draw(_window);                //unused atm

    if(_mouse_in){_window.draw(_cursor);}     //drawing dot to follow cursor --> draw last so it appears above everything else   
    //- - - - - - - - - - - - - - - - - - -
    //getPosition() gives you screen coords, getPosition(_window) gives you _window coords
    //cout<<"mosue pos: "<<sf::Mouse::getPosition(_window).x<<", "<<sf::Mouse::getPosition(_window).y<<endl;
    //- - - - - - - - - - - - - - - - - - -
}

string mouse_pos_string(sf::RenderWindow& _window){
    return "("+to_string(sf::Mouse::getPosition(_window).x)+", "+to_string(sf::Mouse::getPosition(_window).y)+")";
}
bool save_file(string filename, const vector<string>& history){
    ofstream outs;
    outs.open(filename);
    if(outs.fail()){
        cout<<"opening file "<<filename<<" failed"<<endl;
        return false;
    }
    for(int i=0; i<history.size(); i++){
        outs<<history[i]<<endl;
    }
    outs.close();
    return true;
}
bool load_file(string filename, vector<string>& history){
    ifstream ins;
    ins.open(filename);
    if(ins.fail()){
        cout<<"opening file "<<filename<<" failed"<<endl;
        return false;
    }
    string temp;
    while(getline(ins, temp)){
        if(!temp.empty())
            history.push_back(temp);
    }
    ins.close();
    return true;
}