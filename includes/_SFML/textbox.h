#ifndef TEXTBOX_H
#define TEXTBOX_H
#include "../constants.h"

using namespace std;
class Textbox{
public:
    Textbox(GraphInfo* info);

    void select();
    void _sort_input(sf::Event input);

    void Draw(sf::RenderWindow& window);

    bool isSelected() const;
    string getText() const;

private:
    GraphInfo* _info;

    sf::Text _text_display;
    sf::Font _font;
    
    string _prev;
    string _text;
    bool _selected;

    void _init_sfml();
};

#endif //TEXTBOX