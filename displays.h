#ifndef DISPLAYS_H
#define DISPLAYS_H
#include <string>
//#include "game.h"
#include "gradient.h"

class Display {
public:
	void draw_main_game(void);
	void draw_pause_screen(void);
	void init_display(void);
	void draw_skybox(float x, float y, float z, float width, float height, float length);
	

protected:
	bool enable_fog;

private:
	void write_text(float, float, void*, std::string);		//writes text at start location in refernece to window. (xloc, yloc, textToWrite)
	int string_width(void*, std::string );		//gets the width of the string to be written.
	void enter_2D(void);		//used to help write text in 2D mode
	void exit_2D(void);			//exit 2D mode after text is written
	void draw_hud(void);		//function to draw the HUD including co-ordinates, fps, points and number of fish.
	color bgColor;
	float fog_color[4];
};


#endif