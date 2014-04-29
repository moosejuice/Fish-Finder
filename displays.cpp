#pragma once
#include "displays.h"
#include "global_variables.h"
#include <string>
#include "glut.h"
#include <sstream>
#include <iomanip>
#include "prototypes.h"
#include "temp_inc_game.h"
#include "drawings.h"
#include "ObjLibrary\TextureManager.h"


using namespace std;

void Display::init_display(void)
{
	enable_fog = true;
	fog_color[0]=0;
	fog_color[1]=0;
	fog_color[2]=0;
	fog_color[3]=1;
	
}


void Display::draw_main_game(void)
{

	bgColor = makeGradient(mySub.get_location().y/MAXLOCY);	

	glClearColor(bgColor.red, bgColor.green, bgColor.blue, 1.0);

	fog_color[0] = bgColor.red;
	fog_color[1] = bgColor.green;
	fog_color[2] = bgColor.blue;

	if(enable_fog)
	{
		glEnable(GL_FOG);
		glFogi(GL_FOG_MODE, GL_LINEAR);
		glHint(GL_FOG_HINT, GL_DONT_CARE);
		glFogfv(GL_FOG_COLOR, fog_color);
		glFogf(GL_FOG_START, 0);
		glFogf(GL_FOG_END, game.fogDistance);
	}
	else
	{
		glDisable(GL_FOG);
	}


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);	// which matrix
	glLoadIdentity();	// initialize the selected matrix
	game.display_camera();
	//main seafloor
	glPushMatrix();
		glTranslatef(-500, 0, -500);
		glCallList(ocean_floor);
	glPopMatrix();

	//never over these, just to make it appear infinite.
	//manually calculate if we need to even draw these display lists. 
	if(mySub.location.z < -250)
	{
		glPushMatrix();
			glTranslatef(-500, 0, -1500);
			glCallList(ocean_floor);
		glPopMatrix();
		if(mySub.location.x > 250)
		{
			glPushMatrix();
				glTranslatef(500, 0, -1500);
				glCallList(ocean_floor);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(500, 0, -500);
				glCallList(ocean_floor);
			glPopMatrix();
		}
		if(mySub.location.x < -250)
		{
			glPushMatrix();
				glTranslatef(-1500, 0, -1500);
				glCallList(ocean_floor);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-1500, 0, -500);
				glCallList(ocean_floor);
			glPopMatrix();
		}
	}
	if(mySub.location.z > 250)
	{
		glPushMatrix();
			glTranslatef(-500, 0, 500);
			glCallList(ocean_floor);
		glPopMatrix();
		if(mySub.location.x > 250)
		{
			glPushMatrix();
				glTranslatef(500, 0, 500);
				glCallList(ocean_floor);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(500, 0, -500);
				glCallList(ocean_floor);
			glPopMatrix();
		}
		if(mySub.location.x < -250)
		{
			glPushMatrix();
				glTranslatef(-1500, 0, -500);
				glCallList(ocean_floor);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-1500, 0, 500);
				glCallList(ocean_floor);
			glPopMatrix();
		}
	}
	if(mySub.location.z > -250 && mySub.location.z < 250)
	{
		if(mySub.location.x > 250)
		{
			glPushMatrix();
				glTranslatef(500, 0, -500);
				glCallList(ocean_floor);
			glPopMatrix();
		}
		if(mySub.location.x < -250)
		{
			glPushMatrix();
				glTranslatef(-1500, 0, -500);
				glCallList(ocean_floor);
			glPopMatrix();
		}

	}


	if(mySub.location.y > (MAXLOCY-30))
	{
		draw_skybox(0, mySub.location.y, 0, 1500, 200, 1500);
	}
		//draw_skybox(mySub.location.x, mySub.location.y, mySub.location.z, 500, 1000, 500);
	draw_fish();
//	axis_Display();
	mySub.draw();
	game.myShark.draw();
	if(game.display_hud)
		draw_hud();

}


//write_text, enter_2D and exit_2D adopted from http://wiki.freepascal.org/OpenGL_Tutorial#Using_display_lists
void Display::write_text(float x, float y, void *font, std::string text)
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

int Display::string_width(void *font, std::string text)
{
	int size = 0;
	int len = text.length();
	for(int i = 0; i < len; i++)
		size += glutBitmapWidth(font, int(text[i]));
	return size;
}

void Display::enter_2D(void)
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

void Display::exit_2D(void)
{
			glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
}

void Display::draw_hud(void)
{
		/////// All text writting here ///////
	enter_2D();
	void * font = GLUT_BITMAP_HELVETICA_18;
	stringstream ss;
	GLint m_viewport[4];	//height = 3, width = 2 of the current window
	glGetIntegerv(GL_VIEWPORT, m_viewport);		//populate m_viewport

	if(game.display_fish_counter)
	{
		ss << "Fish captured: " << fishCaptured << "/" << NUMFISH;
		write_text(10, 10, font, ss.str());		//text is written to the screen.
		ss.str("");
	}
	if(game.display_coordinates)
	{
		ss.setf(ios::fixed, ios::floatfield);
		ss << setprecision(1) << mySub.get_location().x << ", " << mySub.get_location().y << ", " << mySub.get_location().z;
		write_text( 10, m_viewport[3] - 20, font, ss.str());
		ss.str("");
	}
	if(game.display_fps)
	{
		ss << "FPS: " << game.FPS();
		write_text(10, 40, font, ss.str());
		ss.str("");
	}
	if(game.display_points)
	{
		ss << "Points: " << user_points;
		int string_size = string_width(font, ss.str());
		write_text( m_viewport[2] - string_size - 10, 10, font, ss.str());
		ss.str("");
	}

	if(game.display_update_rates)
	{
		ss.setf(ios::fixed, ios::floatfield);
		ss << setprecision(1) << "Physics Update Rate: " << game.physics_update_rate;
		write_text( 10, m_viewport[3] - 40, font, ss.str());
		ss.str("");

		ss << setprecision(2) << "Slow AI Update Rate: " << game.slow_ai_update_rate;
		write_text( 10, m_viewport[3] - 60, font, ss.str());
		ss.str("");

		ss << setprecision(1) << "Fast AI Update Rate: " << game.fast_ai_update_rate;
		write_text( 10, m_viewport[3] - 80, font, ss.str());
		ss.str("");

	}
		ss.setf(ios::fixed, ios::floatfield);
		ss << setprecision(4) << mySub.get_buoyancy();
		write_text( 10, m_viewport[3] - 40, font, ss.str());
		ss.str("");

		ss.setf(ios::fixed, ios::floatfield);
		ss << setprecision(4) << mySub.get_velocity();
		write_text( 10, m_viewport[3] - 60, font, ss.str());
		ss.str("");

	if(!game.enable_end_of_game)
	{
		ss << "DEBUG MODE";
		int string_size = string_width(font, ss.str());
		write_text( m_viewport[2] - string_size - 10, m_viewport[3] - 20, font, ss.str());
		ss.str("");
	


		ss.setf(ios::fixed, ios::floatfield);
		ss << setprecision(4) << "Forward velocity " << mySub.get_velocity().getNorm();
		write_text( 10, m_viewport[3] - 140, font, ss.str());
		ss.str("");

		ss.setf(ios::fixed, ios::floatfield);
		ss << setprecision(4) << "Rotation " << mySub.get_rotation();
		write_text( 10, m_viewport[3] - 160, font, ss.str());
		ss.str("");


		ss << "Avg Display time in ms: " << game.average_display;
		write_text( 10, m_viewport[3] - 180, font, ss.str());
		ss.str("");

		ss << "Avg update time in ms: " << game.average_update;
		write_text( 10, m_viewport[3] - 200, font, ss.str());
		ss.str("");

	}

	exit_2D();

		/////// End Text Writting ///////
}

void Display::draw_pause_screen(void)
{
	void * font = GLUT_BITMAP_HELVETICA_18;
	stringstream ss;
	GLint m_viewport[4];	//height = 3, width = 2 of the current window
	glGetIntegerv(GL_VIEWPORT, m_viewport);		//populate m_viewport
	int mid_width = m_viewport[2] / 2;
	int mid_height = m_viewport[3] / 2;

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	enter_2D();
	if(game.new_game)
	{
		ss << "Welcome to Fish Finder!";
		write_text( mid_width - string_width(font, ss.str())/2, mid_height + 60, font, ss.str());
		ss.str("");

		ss << "N/n To create a new game";
		write_text( mid_width - string_width(font, ss.str())/2, mid_height + 20, font, ss.str());
		ss.str("");

		ss << "L/l To load a saved game";
		write_text( mid_width - string_width(font, ss.str())/2, mid_height - 20, font, ss.str());
		ss.str("");
	}
	else
	{
		if(!game.game_over)
		{
			ss << "Escape to Resume";
			write_text( mid_width - string_width(font, ss.str())/2, mid_height + 60, font, ss.str());
			ss.str("");
			ss << "GAME PAUSED";
			write_text( mid_width - string_width(font, ss.str())/2, mid_height + 40, font, ss.str());
			ss.str("");
			if(!game.saved)
				ss << "S/s To save this game";
			else
				ss << "Saved!";
			write_text( mid_width - string_width(font, ss.str())/2, mid_height, font, ss.str());
			ss.str("");
		}
		else
		{
			ss << "GAME OVER";
			write_text( mid_width - string_width(font, ss.str())/2, mid_height + 40, font, ss.str());
			ss.str("");
		}
	}


	ss << "Q/q to quit";
	write_text( mid_width - string_width(font, ss.str())/2, mid_height - 40, font, ss.str());
	ss.str("");

	ss << "Fish captured: " << fishCaptured << "/" << NUMFISH;
	write_text(10, 10, font, ss.str());		//text is written to the screen.
	ss.str("");

	//ss.setf(ios::fixed, ios::floatfield);
	//ss << setprecision(1) << mySub.get_location().x << ", " << mySub.get_location().y << ", " << mySub.get_location().z;
	//write_text( 10, m_viewport[3] - 20, font, ss.str());
	//ss.str("");

	ss << "FPS: " << game.FPS();
	write_text(10, 40, font, ss.str());
	ss.str("");

	ss << "Points: " << user_points;
	int string_size = string_width(font, ss.str());
	write_text( m_viewport[2] - string_size - 10, 10, font, ss.str());
	ss.str("");

	if(!game.enable_end_of_game)
	{
		ss << "DEBUG MODE";
		int string_size = string_width(font, ss.str());
		write_text( m_viewport[2] - string_size - 10, m_viewport[3] - 20, font, ss.str());
		ss.str("");
	}

	//ss.setf(ios::fixed, ios::floatfield);
	//ss << setprecision(1) << "Physics Update Rate: " << game.physics_update_rate;
	//write_text( 10, m_viewport[3] - 40, font, ss.str());
	//ss.str("");

	//ss << setprecision(2) << "Slow AI Update Rate: " << game.slow_ai_update_rate;
	//write_text( 10, m_viewport[3] - 60, font, ss.str());
	//ss.str("");

	//ss << setprecision(1) << "Fast AI Update Rate: " << game.fast_ai_update_rate;
	//write_text( 10, m_viewport[3] - 80, font, ss.str());
	//ss.str("");


	int k = 0;
	int count = 0;
	for(int i = 0; i < 7; i++)
	{
		if ( (i%2) == 0 && i > 1)
			k++;	
		if(game.fish_caught[i] > 0)
		{
			count++;
			if(!(i%2))
			{
				ss <<  game.fish_names[i] << ": " << game.fish_caught[i];
				write_text( 10, m_viewport[3] - 60 - (k*20), font, ss.str());
				ss.str("");
			}
			else
			{
				ss <<  game.fish_names[i] << ": " << game.fish_caught[i];
				int string_size = string_width(font, ss.str());
				write_text( m_viewport[2] - string_size - 10, m_viewport[3] - 60 - (k*20), font, ss.str());
				ss.str("");
			}
			
		}

	}
	if(count == 7)
	{
		ss <<  "Congratulations You have caught all 7 types of fish. ";
		write_text( 10, m_viewport[3] - 20, font, ss.str());
		ss.str("");
	}
	else
	{
		ss <<  "You have caught " << count << " of 7 fish. ";
		write_text( 10, m_viewport[3] - 20, font, ss.str());
		ss.str("");
	}

	exit_2D();
}

void Display::draw_skybox(float x, float y, float z, float width, float height, float length)
{
		// Center the Skybox around the given x,y,z position
	//x = x - width  / 2;
	x = -750;
	//y = y - height / 2;
	y=MAXLOCY;
	//z = z - length / 2;
	z = -750;

	
	// Draw Front side
	//glEnable(GL_TEXTURE_2D);
	//TextureManager::activate("Skybox/front.bmp");
	//glBegin(GL_QUADS);	
	//	glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y,		z+length);
	//	glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y+height, z+length);
	//	glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y+height, z+length); 
	//	glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y,		z+length);
	//glEnd();

	// Draw Back side
	//glEnable(GL_TEXTURE_2D);
	//TextureManager::activate("Skybox/back.bmp");
	//glBegin(GL_QUADS);		
	//	glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y,		z);
	//	glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y+height, z); 
	//	glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y+height,	z);
	//	glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y,		z);
	//glEnd();

	// Draw Left side
	//glEnable(GL_TEXTURE_2D);
	//TextureManager::activate("Skybox/right.bmp");
	//glBegin(GL_QUADS);		
	//	glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y+height,	z);	
	//	glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y+height,	z+length); 
	//	glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y,		z+length);
	//	glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y,		z);		
	//glEnd();

	// Draw Right side
	//glEnable(GL_TEXTURE_2D);
	//TextureManager::activate("Skybox/left.bmp");
	//glBegin(GL_QUADS);		
	//	glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y,		z);
	//	glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y,		z+length);
	//	glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y+height,	z+length); 
	//	glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y+height,	z);
	//glEnd();

	// Draw Up side
	//glEnable(GL_TEXTURE_2D);
	//TextureManager::activate("Skybox/up.bmp");
	//glBegin(GL_QUADS);		
	//	glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y+height, z);
	//	glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y+height, z+length); 
	//	glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y+height,	z+length);
	//	glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y+height,	z);
	//glEnd();
	
	//// Draw Down side
	glEnable(GL_TEXTURE_2D);
	TextureManager::activate("Skybox/down.bmp");
	glBegin(GL_QUADS);		
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y,		z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y,		z+length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y,		z+length); 
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y,		z);
	glEnd();
}