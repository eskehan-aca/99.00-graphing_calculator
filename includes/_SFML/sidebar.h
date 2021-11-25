#ifndef SIDEBAR_H
#define SIDEBAR_H
#include "../constants.h"
#include "textbox.h"

using namespace std;
class Sidebar{
public:
    Sidebar(float height, float width);
    void updateHistory(vector<string>& history);
    void Draw(sf::RenderWindow& window);
    string& operator [](int index);

private:
    vector<string> _items;              //strings to place on the sidebar
    sf::RectangleShape _sb_rect;        //sidebar rectangle
    sf::Font font;                      //used to draw text
    sf::Text _sb_text;                  //used to draw strings on the window object

    float _height;
    float _width;
};

#endif // SIDEBAR_H
