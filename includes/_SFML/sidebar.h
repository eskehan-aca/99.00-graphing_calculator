#ifndef SIDEBAR_H
#define SIDEBAR_H
#include "../constants.h"
#include "textbox.h"

using namespace std;
class Sidebar{
public:
    Sidebar(float leftMargin, float sbWidth);
    int mouseClick(sf::Vector2i position);   //returns the command associated with the function clicked from function history
    void updateHistory(vector<string>& history);
    void updateMode(int mode);
    void Draw(sf::RenderWindow& window);
    string& operator [](int index);

private:
    vector<string> _items;              //strings to place on the sidebar
    vector<float> _history_height;      //to save height y coord of hist items
    sf::RectangleShape _sb_rect;        //sidebar rectangle
    sf::Font _font;                     //used to draw text
    sf::Text _sb_text;                  //used to draw strings on the window object

    float _x_start;                     //x coord (left margin) for sidebar window
    float _width;                       //width of sidebar (left margin to screen bound)
    int _mode;                          //value of CALCULATOR_MODE enum

    void _init_sfml();
    void _init_vector();
    bool _fit_text();

    void _draw_eq_label(sf::RenderWindow& window, float& height);
    void _draw_funct_label(sf::RenderWindow& window, float& height);
    void _draw_history(sf::RenderWindow& window, float& height);
};

#endif // SIDEBAR_H
