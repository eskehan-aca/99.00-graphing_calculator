#ifndef TEXTBOX_H
#define TEXTBOX_H
#include "../constants.h"

using namespace std;
class Textbox{
public:
    Textbox();

    void select();
    void sort_input(sf::Event input);

    void Draw(sf::RenderWindow& window);

    bool modified() const;
    bool selected() const;
    string text() const;
    
    void reset();

private:
    sf::Text _text_display;
    sf::Font _font;
    
    string _prev;
    string _text;
    bool _selected;

    void _init_sfml();
    void _modify_graph_info();
};

#endif //TEXTBOX