#ifndef ANIMATE_H
#define ANIMATE_H
#include "../constants.h"
#include "sidebar.h"
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
    Sidebar sidebar;                    //rectangular message sidebar

    sf::RenderWindow _window;           //sfml window
    sf::CircleShape _cursor;            //dot to follow cursor movement
    
    //REVISIT TO DISPLAY USER INPUT ON SCREEN --> maybe in system instead??????
    sf::Text _equation_label;           //text to draw on main screen
    sf::Font font;                      //font to draw on main screen
    
    int command;                        //command to send to system
    bool mouseIn;                       //if mouse is in the screen

    //FUNCTIONS
    void processEvents();               //processing mouse movement, clicks, etc, modifies command int
    void update();                      //passes command to system step, called in Animate run loop
    void render();                      //calls draw();
    void Draw();                        //called by Animate render
};

string mouse_pos_string(sf::RenderWindow& _window);

#endif // ANIMATE_H