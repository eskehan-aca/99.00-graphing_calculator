#ifndef PLOT_H
#define PLOT_H
#include "../../constants.h"

#include "../shunting_yard/shunting_yard.h"
#include "../translate/translate.h"
#include "../tokenize/tokenize.h"
#include "../rpn/rpn.h"

using namespace std;
class Plot{
public:
    Plot(GraphInfo* info);
    vector<sf::Vector2f> operator()();      //return vector of screenCoords
private:
    GraphInfo* _info;
};

#endif //PLOT_H