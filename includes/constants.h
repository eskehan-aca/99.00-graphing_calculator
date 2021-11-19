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

const float GRAPH_WIDTH = 1000;
const float GRAPH_HEIGHT = 1000;
const float GRAPH_PADDING = 50;

const float WORK_PANEL = GRAPH_WIDTH+GRAPH_PADDING;
const float SIDE_BAR = 400;

const float SCREEN_WIDTH = GRAPH_WIDTH+GRAPH_PADDING+SIDE_BAR;
const float SCREEN_HEIGHT = GRAPH_WIDTH+GRAPH_PADDING;

const float POINT_RADIUS = 4;
const float LINE_WEIGHT = 1;

const float DOMAIN_MIN = -5;
const float DOMAIN_MAX = 5;
const float RANGE_MIN = -5;
const float RANGE_MAX = 5;

const int NUM_POINTS = 51;

const string DEFAULT_EQUATION = "cos ( x )";    //MODIFY ME!!
const string DEFAULT_EQUATION1 = "x";
const string DEFAULT_EQUATION2 = "x ^ 2";
const string DEFAULT_EQUATION3 = "x ^ 3 - 1";
const string DEFAULT_EQUATION4 = "2 * x - 4";

///////////////////////////////////

const float SB_SPACING = 10;

const int SB_MOUSE_POSITION = 0;
const int SB_MOUSE_CLICKED = SB_MOUSE_POSITION+1;
const int SB_KEY_PRESSED = SB_MOUSE_CLICKED+1;
const int SB_COMMAND_NAME = SB_KEY_PRESSED+5;
const int SB_EQUATION_LABEL = SB_COMMAND_NAME+2;

///////////////////////////////////

#endif //CONSTANTS_H