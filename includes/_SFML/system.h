#ifndef SYSTEM_H
#define SYSTEM_H
#include "../constants.h"
#include "graph.h"

using namespace std;
class System{
public:
    System(GraphInfo* info);
    void Step(int command, GraphInfo* info);
    void Draw(sf::RenderWindow& widnow);

private:
    Graph _g;
    void _init_graph_info(GraphInfo* info);
    void _calculate_graph_info(GraphInfo* info);
};

#endif // SYSTEM_H
