#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H
#include <vector>
#include "fish.h"
#include "submarine.h"
//#include "gradient.h"
#include "ObjLibrary/ObjModel.h"
#include "ObjLibrary/DisplayList.h"
#include "glut.h"
#include "game.h"

const double degToRad = 0.01745329251994329576923690768489;
const double RadToDeg = 57.295779513082320876798154814105;
const double pi = 3.1415926535897932384626433832795;

extern GLuint ocean_floor;
//state that these variables are already defined in another file (global_variables.cpp)
//mainly to clean up main.cpp and contain globals in a dedicated file.

extern float heightmap[][51];
//extern float fog_color[4];

extern float const MAXLOC, MINLOC, MINLOCY, MAXLOCY;
extern int NUMFISH, fishCaptured, new_time, base_time, user_points;
extern int rows, cols;

//extern float fogDistance;
extern bool keyStates[256], keySpecialStates[256];

extern int  current_time, previous_time, previous_frame;

extern Submarine mySub;
extern ObjModel fishObj;
extern DisplayList fish_list[7];
extern std::vector<Fish>::iterator slow_ai_iterator;

#endif