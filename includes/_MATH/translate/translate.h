#ifndef TRANSLATE_H
#define TRANSLATE_H
#include "../../constants.h"

using namespace std;
class Translate{
public:
    Translate(GraphInfo* info);
    //translate reg coords into screenCoords
    vector<sf::Vector2f>& translate(vector<sf::Vector2f>& coords);
private:
    GraphInfo* _info;
};


#endif //TRANSLATE_H