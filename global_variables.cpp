#pragma once
#include "global_variables.h"
#include "fish.h"
#include <vector>
//#include "gradient.h"


////////GLOBALS HERE////////

ObjModel fishObj;
DisplayList fish_list[7];
GLuint ocean_floor = NULL;

float heightmap[51][51];

//world variables/
//axis has x and z = 0 in the middle of the world
//the depth has the range 1 to 1000
float const MAXLOC = 500.0;		//since ocean is 1000x1000x1000, this will need to become 500
float const MINLOC = -500.0;		//and this to become -500 when it is scaled up
float const MINLOCY = 0.0;
float const MAXLOCY = 500.0;

int rows, cols;		//heitmap

//fish variables
int NUMFISH = 20;			//DEFAULT set to 20 here, generate fish will change this to between 100-200

std::vector<Fish>::iterator slow_ai_iterator;

//submarine variables///
Submarine mySub;

///key state variables
//these boolean keystates are true whenever the key is pressed. This was implemented to allow for > 1 keypress at a time.
bool keyStates[256] = {false};		//keyboard state.
bool keySpecialStates[256] = {false};		//special key states
//mulit key-press adopted from http://www.swiftless.com/tutorials/opengl/keyboard.html

//counters
int fishCaptured = 0;
//int frames = 0;

int new_time, base_time;
int user_points = 0;

int current_time, previous_time, previous_frame;




