#ifndef TEXTBOX_H
#define TEXTBOX_H
#include "../constants.h"

using namespace std;
class Textbox{
public:
    Textbox();

    void Draw(sf::RenderWindow& window);

private:
    sf::Text _text_display;
    sf::Font _font;
    
    string _text;
    bool _selected;

    void _init_sfml();
};

#endif //TEXTBOX