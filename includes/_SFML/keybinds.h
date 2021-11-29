#ifndef KEYBINDS_H
#define KEYBINDS_H
#include "../constants.h"

using namespace std;
class Keybinds{
public:
    Keybinds();

    void select();
    void sort_input(sf::Event input);

    void Draw(sf::RenderWindow& window);

    bool selected() const;

private:
    sf::Text _text_display;
    sf::Font _font;
    
    bool _selected;
    void _init_sfml();
};

#endif //KEYBINDS