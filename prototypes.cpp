#pragma once
#include "prototypes.h"
//#include "Sleep.h"
#include <math.h>
#include <vector>
#include <time.h>
#include "glut.h"
#include "fish.h"
#include "gradient.h"
#include "keyboard_operations.h"
#include "global_variables.h"
#include "write_text.h"
#include "drawings.h"
#include "ai.h"
#include "physics.h"
#include "ObjLibrary\ObjModel.h"
#include "collision_detection.h"
#include "game.h"
#include "temp_inc_game.h"

using namespace std;

void display(void)
{
	game.display();
}

void idle ()
{
	game.update();
}

void init(void)
{
	std::cout << "Initialization Begun\n";
	game.init_game();
}

void reshape(int w , int h)
{
	if(w < 500)
		w=500;
	if(h < 500)
		h=500;
	glutReshapeWindow(w, h);
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (double)w / (double)h, 0.1, 1000.0);		//increased zfar plane to 500
	game.update_culling_distance();
}



void fish_world_edge_check(void)	//depreciated. Covered in collision detection
{

	for (std::vector<Fish>::iterator it = game.myFish.begin(); it != game.myFish.end(); it++)
	{
		//preliminary edge of world detection. Just move it back inside boundery by cubeSize
		if(it->location.x < MINLOC)
			it->location.x = MINLOC+it->fish_radius;
		if(it->location.x > MAXLOC)
			it->location.x = MAXLOC-it->fish_radius;

		if(it->location.y < 0)
			it->location.y = 0+it->fish_radius;
		if(it->location.y > MAXLOCY)
			it->location.y = MAXLOCY-it->fish_radius; 

		if(it->location.z < MINLOC)
			it->location.z = MINLOC+it->fish_radius;
		if(it->location.z > MAXLOC)
			it->location.z = MAXLOC-it->fish_radius;
	}
}








