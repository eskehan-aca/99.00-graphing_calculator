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
const bool translateDebug=false;
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

const float DOMAIN_MIN = -12;
const float DOMAIN_MAX = 8;
const float RANGE_MIN = -10;
const float RANGE_MAX = 10;

const int NUM_POINTS = 21;

const string DEFAULT_EQUATION0 = "";    //MODIFY ME!!
const string DEFAULT_EQUATION1 = "x";
const string DEFAULT_EQUATION2 = "x ^ 2";
const string DEFAULT_EQUATION3 = "x ^ 3 - 1";
const string DEFAULT_EQUATION4 = "cos ( x )";

///////////////////////////////////

const float SB_SPACING = 10;

const int SB_MOUSE_POSITION = 0;
const int SB_MOUSE_CLICKED = SB_MOUSE_POSITION+1;
const int SB_KEY_PRESSED = SB_MOUSE_CLICKED+1;
const int SB_COMMAND_NAME = SB_KEY_PRESSED+5;
const int SB_EQUATION_LABEL = SB_COMMAND_NAME+2;

///////////////////////////////////

//COMMANDS
enum COMMANDS{

    //KEYBOARD COMMANDS
        
    NUM_0,  //default equation 0
    NUM_1,  //default equation 1
    NUM_2,  //default equation 2
    NUM_3,  //default equation 3
    NUM_4,  //default equation 4
    
    R,      //reset origin
    C,      //center origin
    F,      //force update/recalculate

    RIGHT,  //pan right
    LEFT,   //pan left
    UP,     //pan up
    DOWN,   //pan down

    PLUS,   //zoom in
    MINUS,  //zoom out

    RBRACKET,   //increase # pts
    LBRACKET,   //decrease # pts

    ENTER,  //?????????????? get equation maybe    
    ESCAPE, //exit (no command # associated, just here for reference) --> should not *do* anything?

    

    //MOUSE COMMANDS
};

//-1 = no command
//functionalities:
//  - default eqs                           0-4
//  - escape                                esc

//  - zoom                                  plus minus
//  - pan                                   arrow keys

//  - increase num pts?                     brackets
//  - force update                          'f'
//  - reset origin                          'r'

//  - enter equation                        'enter'?
//  - change colors :) (pts,background)     'c'
//  - display grid lines                    'g'

#endif //CONSTANTS_H