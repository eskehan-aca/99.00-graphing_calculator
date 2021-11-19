#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <SFML/Graphics.hpp>
#include <assert.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#include "_SFML/graphinfo.h"

//type for shunting --> formatting queue
//prec for rpn      --> evaluating queue

enum TOKEN_TYPES{
    LPAREN,   //shunting
    RPAREN,   //shunting
    NUMBER,
    VARIABLE,
    OPERATOR,
    FUNCTION, //prec 5? type 0
};

//OPERATOR LIST:    +, -, *, /, ^
const int numOpers=5;
const array<string,numOpers> operList{"+", "-", "*", "/", "^"};

//FUNCTION LIST:    sin, cos, tan, log
const int numFuncts=4;
const array<string,numFuncts> functList{"sin", "cos", "tan", "log"};

//DEBUG
const bool translateDebug=true;
const bool tokenizeDebug=false;
const bool graphDebug=false;
const bool queueDebug=false;
const bool typeDebug=false;
const bool plotDebug=false;
const bool rpnDebug=false;
const bool syDebug=false;

//SFML -- CHECK SFML FOLDER FOR DIFF CONST FILE
const float SCREEN_WIDTH = 1200;
const float SCREEN_HEIGHT = 800;

const float GRAPH_WIDTH = 500;
const float GRAPH_HEIGHT = 500;

const float POINT_RADIUS = 4;
const float LINE_WEIGHT = 1;

const float DOMAIN_MIN = -5;
const float DOMAIN_MAX = 5;
const float RANGE_MIN = -5;
const float RANGE_MAX = 5;

const int NUM_POINTS = 21;

const string DEFAULT_EQUATION = "x ^ 2 - 4";

///////////////////////////////////

const float WORK_PANEL = SCREEN_WIDTH*4/5;
const float SIDE_BAR = SCREEN_WIDTH*1/5;

const int SB_MOUSE_POSITION = 0;
const int SB_MOUSE_CLICKED = SB_MOUSE_POSITION+1;
const int SB_KEY_PRESSED = SB_MOUSE_CLICKED+1;

///////////////////////////////////

#endif //CONSTANTS_H