#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <SFML/Graphics.hpp>
#include <assert.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "_SFML/graphinfo.h"

//=============================================================================
//TOGGLE DEBUG

const bool translateDebug=false;
const bool tokenizeDebug=false;
const bool keybindsDebug=false;
const bool textboxDebug=false;
const bool animateDebug=false;
const bool historyDebug=false;
const bool sidebarDebug=false;
const bool systemDebug=false;
const bool graphDebug=false;
const bool queueDebug=false;
const bool typeDebug=false;
const bool plotDebug=false;
const bool rpnDebug=false;
const bool syDebug=false;

//=============================================================================
//DEFAULT VALUES

const float GRAPH_WIDTH = 1000;
const float GRAPH_HEIGHT = 1000;
const float GRAPH_PADDING = 50;

const float WORK_PANEL = GRAPH_WIDTH+GRAPH_PADDING;     //revisit this
const float SIDE_BAR = 400;

const float SCREEN_WIDTH = GRAPH_WIDTH+GRAPH_PADDING+SIDE_BAR;
const float SCREEN_HEIGHT = GRAPH_WIDTH+GRAPH_PADDING;

const float CURSOR_RADIUS = 2;
const float POINT_RADIUS = 4;
const float LINE_WEIGHT = 1;

const float DOMAIN_MIN = -10;
const float DOMAIN_MAX = 10;
const float RANGE_MIN = -10;
const float RANGE_MAX = 10;

//remove later
const int NUM_POINTS = 151;
const string DEFAULT_EQUATION0 = "";

//=============================================================================
//SIDEBAR CONFIG

const int HISTORY_LIMIT = 40;
const int DISPLAYED_HISTORY_ITEMS = 4;

//SPACING 
const float SB_LEFT_MARGIN = 15;
const float SB_VERTICAL_MARGIN = 15;
const float SB_VERTICAL_LINE_SPACING = 10;

//MESSAGES
const int SB_EQUATION_LABEL = 0;
const int SB_CALCULATOR_MODE = SB_EQUATION_LABEL+1;
const int SB_EQ_HIST_HEADER = SB_CALCULATOR_MODE+1;
const int SB_DOMAIN_DISPLAY = SB_EQ_HIST_HEADER+DISPLAYED_HISTORY_ITEMS+1;
const int SB_RANGE_DISPLAY = SB_DOMAIN_DISPLAY+1;
const int SB_MOUSE_POSITION = SB_RANGE_DISPLAY+1;

/* CURRENTLY UNUSED: 
const int SB_EQ_HIST_1 = SB_EQ_HIST_HEADER+1;
const int SB_EQ_HIST_2 = SB_EQ_HIST_HEADER+2;
const int SB_EQ_HIST_3 = SB_EQ_HIST_HEADER+3;
const int SB_EQ_HIST_4 = SB_EQ_HIST_HEADER+4;
const string DEFAULT_EQUATION1 = "1 / x";
const string DEFAULT_EQUATION2 = "sec ( x )";
const string DEFAULT_EQUATION3 = "sqrt ( x )";
const string DEFAULT_EQUATION4 = "3 * sin ( x )";
*/

//remove later
const int SB_MOUSE_CLICKED = SB_MOUSE_POSITION+1;
const int SB_KEY_PRESSED = SB_MOUSE_CLICKED+1;
const int SB_COMMAND_NAME = SB_KEY_PRESSED+1;

//=============================================================================
//ENUMS + OTHER

enum CALCULATOR_MODES{
    GRAPHING_EQ,
    TEXT_INPUT,
    HELP_MENU,
    FILE_SAVE,
    FILE_LOAD,
    SAVE_FAIL,  //change to file fail rather than save fail specifically
    RESET_CALC,
};
enum COMMANDS{
    //KEYBOARD COMMANDS
    //-1 = no command
        
    NUM_0,      //default equation 0
    NUM_1,      //default equation 1
    NUM_2,      //default equation 2
    NUM_3,      //default equation 3
    NUM_4,      //default equation 4
    HISTORY,    //accessing history - CURRENTLY DOESN'T WORK
    
    SAVE,       //save file         S
    LOAD,       //load file         L
    RESET,      //reset origin      R
    HOME,       //center, reset zoomH
    CENTER,     //center origin     C, H
    INFO_LABEL, //toggle graph info I
    FORCE_UPDATE,//recalculate      F, U

    PAN_RIGHT,  //pan right         arrow keys
    PAN_LEFT,   //pan left
    PAN_UP,     //pan up
    PAN_DOWN,   //pan down

    ZOOM_IN,   //zoom in            +
    ZOOM_OUT,  //zoom out           -

    INC_PTS,   //increase # pts     ]
    DEC_PTS,   //decrease # pts     [

    ENTER_EQ,  //?????????????? get equation maybe    
    ESCAPE,    //exit (no command # associated, just here for reference) --> should not *do* anything?

    //MOUSE COMMANDS
    RIGHT_CLICK,
    LEFT_CLICK,
};
enum TOKEN_TYPES{
    LPAREN,   //shunting
    RPAREN,   //shunting
    NUMBER,
    VARIABLE,
    OPERATOR,
    FUNCTION, //prec 5? type 0
};

//REVISIT THIS!!!
//operators have 2 args, functions have 1
//type for shunting --> formatting queue
//prec for rpn      --> evaluating queue

//OPERATORS
const int NUM_OPERS=5;
const array<string,NUM_OPERS> OPER_LIST{"+", "-", "*", "/", "^"};

//FUNCTIOS
const int NUM_FUNCTS=13;
const array<string,NUM_FUNCTS> FUNCT_LIST{"sin", "cos", "tan", "arcsin", "arccos", "arctan", "log", "sqrt", "csc", "sec", "cot", "abs"};

//=============================================================================

#endif //CONSTANTS_H