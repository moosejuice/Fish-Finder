#ifndef WRITE_TEXT_H
#define WRITE_TEXT_H
#include <string>

void write_text(float, float, void*, std::string);		//writes text at start location in refernece to window. (xloc, yloc, textToWrite)
int string_width(void*, std::string );		//gets the width of the string to be written.
void enter_2D(void);		//used to help write text in 2D mode
void exit_2D(void);			//exit 2D mode after text is written
void draw_hud(void);		//function to draw the HUD including co-ordinates, fps, points and number of fish.
void draw_pause_screen(void);

#endif