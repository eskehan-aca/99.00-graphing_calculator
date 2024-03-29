#ifndef ANIMATE_H
#define ANIMATE_H
#include <fstream>
#include "../constants.h"
#include "keybinds.h"
#include "sidebar.h"
#include "textbox.h"
#include "system.h"
#include "graph.h"

using namespace std;
class Animate{
public:
    Animate();
    void run();                         //calls process events -> update -> render (->draw)

private:
    GraphInfo* _info;                   //init by system
    System _system;                     //container for all the animated objects
    Sidebar _sidebar;                   //rectangular message sidebar
    Textbox _textbox;                   //textbox for user input
    Keybinds _keybinds;                 //display keybinds for commands
    
    vector<string> _history;            //vector to save function history

    sf::RenderWindow _window;           //sfml window
    sf::CircleShape _cursor;            //dot to follow cursor movement
        
    int _command;                       //command to send to system
    bool _mouse_in;                     //if mouse is in the screen
    //bool _sidebar_open;               // use to display graph eq

    //FUNCTIONS
    void processEvents();               //processing mouse movement, clicks, etc, modifies command int
    void update();                      //passes command to system step, called in Animate run loop
    void render();                      //calls draw();
    void Draw();                        //called by Animate render
};

string mouse_pos_string(sf::RenderWindow& _window);
bool save_file(string filename, const vector<string>& history);
bool load_file(string filename, vector<string>& history);

#endif // ANIMATE_H