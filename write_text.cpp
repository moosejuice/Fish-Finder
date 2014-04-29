#pragma once
#include "write_text.h"
#include "global_variables.h"
#include <string>
#include "glut.h"
#include <sstream>
#include <iomanip>
#include "prototypes.h"
#include "game.h"

using namespace std;

//write_text, enter_2D and exit_2D adopted from http://wiki.freepascal.org/OpenGL_Tutorial#Using_display_lists
void write_text(float x, float y, void *font, std::string text)
{
	int len = text.length();
	glPushAttrib(GL_CURRENT_BIT);
	glColor3ub(255,255,255);		//write with white text. Should be visible always under water
	glRasterPos2f(x, y);
	
    for (int i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, int(text[i]));	
    }
	glPopAttrib();
}

int string_width(void *font, std::string text)
{
	int size = 0;
	int len = text.length();
	for(int i = 0; i < len; i++)
		size += glutBitmapWidth(font, int(text[i]));
	return size;
}

void enter_2D(void)
{
	GLint m_viewport[4];
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
		glLoadIdentity();
		glGetIntegerv(GL_VIEWPORT, m_viewport);
		gluOrtho2D(0, m_viewport[2], 0, m_viewport[3]);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			glLoadIdentity();
			glDisable(GL_DEPTH_TEST);
}

void exit_2D(void)
{
			glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
}

void draw_hud(void)
{
	//	/////// All text writting here ///////
	//enter_2D();
	//void * font = GLUT_BITMAP_HELVETICA_18;
	//stringstream ss;
	//GLint m_viewport[4];	//height = 3, width = 2 of the current window
	//glGetIntegerv(GL_VIEWPORT, m_viewport);		//populate m_viewport

	//if(display_fish_counter)
	//{
	//	ss << "Fish captured: " << fishCaptured << "/" << NUMFISH;
	//	write_text(10, 10, font, ss.str());		//text is written to the screen.
	//	ss.str("");
	//}
	//if(display_coordinates)
	//{
	//	ss.setf(ios::fixed, ios::floatfield);
	//	ss << setprecision(1) << mySub.get_location().x << ", " << mySub.get_location().y << ", " << mySub.get_location().z;
	//	write_text( 10, m_viewport[3] - 20, font, ss.str());
	//	ss.str("");
	//}
	//if(display_fps)
	//{
	//	ss << "FPS: " << FPS();
	//	write_text(10, 40, font, ss.str());
	//	ss.str("");
	//}
	//if(display_points)
	//{
	//	ss << "Points: " << user_points;
	//	int string_size = string_width(font, ss.str());
	//	write_text( m_viewport[2] - string_size - 10, 10, font, ss.str());
	//	ss.str("");
	//}

	//if(display_update_rates)
	//{
	//	ss.setf(ios::fixed, ios::floatfield);
	//	ss << setprecision(1) << "Physics Update Rate: " << game.get_physics_update_rate();
	//	write_text( 10, m_viewport[3] - 40, font, ss.str());
	//	ss.str("");

	//	ss << setprecision(2) << "Slow AI Update Rate: " << game.get_slow_ai_update_rate();
	//	write_text( 10, m_viewport[3] - 60, font, ss.str());
	//	ss.str("");

	//	ss << setprecision(1) << "Fast AI Update Rate: " << game.get_fast_ai_update_rate();
	//	write_text( 10, m_viewport[3] - 80, font, ss.str());
	//	ss.str("");

	//}
	//	ss.setf(ios::fixed, ios::floatfield);
	//	ss << setprecision(4) << mySub.get_buoyancy();
	//	write_text( 10, m_viewport[3] - 40, font, ss.str());
	//	ss.str("");

	//	ss.setf(ios::fixed, ios::floatfield);
	//	ss << setprecision(4) << mySub.get_velocity();
	//	write_text( 10, m_viewport[3] - 60, font, ss.str());
	//	ss.str("");

	//if(!enable_end_of_game)
	//{
	//	ss << "DEBUG MODE";
	//	int string_size = string_width(font, ss.str());
	//	write_text( m_viewport[2] - string_size - 10, m_viewport[3] - 20, font, ss.str());
	//	ss.str("");
	//


	//	ss.setf(ios::fixed, ios::floatfield);
	//	ss << setprecision(4) << "Forward velocity " << mySub.get_velocity().getNorm();
	//	write_text( 10, m_viewport[3] - 140, font, ss.str());
	//	ss.str("");

	//	ss.setf(ios::fixed, ios::floatfield);
	//	ss << setprecision(4) << "Rotation " << mySub.get_rotation();
	//	write_text( 10, m_viewport[3] - 160, font, ss.str());
	//	ss.str("");


	//	ss << "Avg Display time in ms: " << average_display;
	//	write_text( 10, m_viewport[3] - 180, font, ss.str());
	//	ss.str("");

	//	ss << "Avg update time in ms: " << average_update;
	//	write_text( 10, m_viewport[3] - 200, font, ss.str());
	//	ss.str("");

	//}

	//exit_2D();

	//	/////// End Text Writting ///////
}

void draw_pause_screen(void)
{
	//void * font = GLUT_BITMAP_HELVETICA_18;
	//stringstream ss;
	//GLint m_viewport[4];	//height = 3, width = 2 of the current window
	//glGetIntegerv(GL_VIEWPORT, m_viewport);		//populate m_viewport
	//int mid_width = m_viewport[2] / 2;
	//int mid_height = m_viewport[3] / 2;

	//enter_2D();
	//if(!game_over)
	//{
	//	ss << "Escape to Resume";
	//	write_text( mid_width - string_width(font, ss.str())/2, mid_height, font, ss.str());
	//	ss.str("");
	//	ss << "GAME PAUSED";
	//}
	//else
	//	ss << "GAME OVER";

	//write_text( mid_width - string_width(font, ss.str())/2, mid_height + 20, font, ss.str());
	//ss.str("");

	//ss << "Q/q to quit";
	//write_text( mid_width - string_width(font, ss.str())/2, mid_height - 20, font, ss.str());
	//ss.str("");

	//ss << "Fish captured: " << fishCaptured << "/" << NUMFISH;
	//write_text(10, 10, font, ss.str());		//text is written to the screen.
	//ss.str("");

	//ss.setf(ios::fixed, ios::floatfield);
	//ss << setprecision(1) << mySub.get_location().x << ", " << mySub.get_location().y << ", " << mySub.get_location().z;
	//write_text( 10, m_viewport[3] - 20, font, ss.str());
	//ss.str("");

	//ss << "FPS: " << FPS();
	//write_text(10, 40, font, ss.str());
	//ss.str("");

	//ss << "Points: " << user_points;
	//int string_size = string_width(font, ss.str());
	//write_text( m_viewport[2] - string_size - 10, 10, font, ss.str());
	//ss.str("");

	//if(!enable_end_of_game)
	//{
	//	ss << "DEBUG MODE";
	//	int string_size = string_width(font, ss.str());
	//	write_text( m_viewport[2] - string_size - 10, m_viewport[3] - 20, font, ss.str());
	//	ss.str("");
	//}

	//ss.setf(ios::fixed, ios::floatfield);
	//ss << setprecision(1) << "Physics Update Rate: " << game.get_physics_update_rate();
	//write_text( 10, m_viewport[3] - 40, font, ss.str());
	//ss.str("");

	//ss << setprecision(2) << "Slow AI Update Rate: " << game.get_slow_ai_update_rate();
	//write_text( 10, m_viewport[3] - 60, font, ss.str());
	//ss.str("");

	//ss << setprecision(1) << "Fast AI Update Rate: " << game.get_fast_ai_update_rate();
	//write_text( 10, m_viewport[3] - 80, font, ss.str());
	//ss.str("");

	//exit_2D();
}