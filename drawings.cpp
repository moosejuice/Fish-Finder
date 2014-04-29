#pragma once
#include "drawings.h"
#include "global_variables.h"
#include "glut.h"
#include "fish.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "ObjLibrary/TextureManager.h"
#include "temp_inc_game.h"

void axis_Display(void)
{
	//draw the x axis in red
	glBegin(GL_LINES);
		glColor3ub(255, 0, 0);
		glVertex3f( MINLOC, 0.0, 0.0);
		glVertex3f( MAXLOC, 0.0, 0.0);
	glEnd();

	//draw the y axis in green
	glBegin(GL_LINES);
		glColor3ub(0, 255, 0);
		glVertex3f(0.0, MINLOCY, 0.0);
		glVertex3f(0.0, MAXLOCY, 0.0);
	glEnd();

	//draw the z axis in blue
	glBegin(GL_LINES);
		glColor3ub(0, 0, 255);
		glVertex3f(0.0, 0.0, MINLOC);
		glVertex3f(0.0, 0.0, MAXLOC);
	glEnd();
}

void draw_ocean_floor(void)
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);	
	glShadeModel (GL_SMOOTH); 
	glEnable(GL_TEXTURE_2D);
	glColor3f(1, 1, 1);
	TextureManager::activate("seaFloor/sand1.bmp");

	for(int i = 0; i < 50; i++)
	{
		for(int j = 0; j < 50; j++)
		{
			glBegin(GL_TRIANGLE_STRIP);
				glTexCoord2f(0,0);
				glVertex3f(float(i*20), heightmap[i][j], float(j*20));

				glTexCoord2f(0,1);
				glVertex3f(float(i*20), heightmap[i][j+1], float(j*20+20));

				glTexCoord2f(1,0);
				glVertex3f(float(i*20+20), heightmap[i+1][j], float(j*20));

				glTexCoord2f(1,1);
				glVertex3f(float(i*20+20), heightmap[i+1][j+1], float(j*20+20));
			glEnd();
		}
		
	}
	glDisable(GL_TEXTURE_2D);

}

void draw_fish(void)
{
	//draw the fish in the list myFish
	for (std::vector<Fish>::iterator it = game.myFish.begin(); it != game.myFish.end(); it++)
	{
		if(it->in_viewport)
			it->draw();
	}
}

void read_height_map(void)
{
	
	std::ifstream heightFile ("SeaFloor/Heightmap.txt");
	if(!heightFile.is_open())
	{
		std::cout << "Could not open heightmap.txt" << std::endl;
	}
	else
		std::cout << "Opened heightmap.txt" << std::endl;

	heightFile >> rows >> cols;

	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			heightFile >> heightmap[i][j];
		}
	}
	for(int i = 0; i < 51; i++)
	{
		heightmap[i][50] = heightmap[i][0];
		heightmap[50][i] = heightmap[0][i];
	}
}


