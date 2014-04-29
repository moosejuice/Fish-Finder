#pragma once
#include <stdlib.h>
#include "keyboard_operations.h"
#include "prototypes.h"
#include "glut.h"
#include "global_variables.h"
#include "fish.h"
#include "game.h"
#include "temp_inc_game.h"

void keyboardOperations(void)
{
	//movement functions here. Toggles wont properly work here

	if(keyStates['a'] || keyStates['A'])
		mySub.set_turn_CCW(true);
	if(keyStates['d'] || keyStates['D'])
		mySub.set_turn_CW(true);

	if(keyStates['w'] || keyStates['W'])
		mySub.set_increase_velocity(true);
	if(keyStates['s'] || keyStates['S'])
		mySub.set_decrease_velocity(true);

	//if(keyStates['Y'] || keyStates['y'])
	//	default_physics_update_rate += 0.2;
	//if(keyStates['H'] || keyStates['h'])
	//	default_physics_update_rate -= 0.2;
	//if(keyStates['U'] || keyStates['u'])
	//	default_fast_ai_update_rate += 0.2;
	//if(keyStates['J'] || keyStates['j'])
	//	default_fast_ai_update_rate -= 0.2;
	//if(keyStates['I'] || keyStates['i'])
	//	default_slow_ai_update_rate += 0.01;
	//if(keyStates['K'] || keyStates['k'])
	//	default_slow_ai_update_rate -= 0.01;

	//special keypresses

	if(keySpecialStates[GLUT_KEY_UP])
	{
		mySub.set_increase_buoyancy(true);
	}
	if(keySpecialStates[GLUT_KEY_DOWN])
	{
		mySub.set_decrease_buoyancy(true);
	}
	if(keySpecialStates[GLUT_KEY_RIGHT])
		game.camera_rotation += 0.5;
	if(keySpecialStates[GLUT_KEY_LEFT])
		game.camera_rotation -= 0.5;

	//validate the submarines new position
		

}

void keyUp(unsigned char key, int x, int y)
{
	keyStates[key] = false;

	if(keyStates['w'] || keyStates['W'])
		mySub.set_increase_velocity(false);
	if(keyStates['s'] || keyStates['S'])
		mySub.set_decrease_velocity(false);
}

void keySpecialUp(int key, int x, int y)
{
	keySpecialStates[key] = false;
}

void keyboard(unsigned char key, int x, int y)
{
	keyStates[key] = true;

	if(!game.game_running)
	{
		if(key == 'q' || key == 'Q')
			exit(0);
		if(game.new_game && (key == 'n' || key == 'N'))
		{
			//game.init_game();
			game.create_new_game();
			game.new_game = false;
			game.game_running = true;
		}
		if(key == 'l' || key == 'L')
		{
			game.create_new_game();
			game.new_game = false;
			game.game_running = true;
			game.load_game();
			return;
			//game.enable_fog = true;
		}
		if(key == 's' || key == 'S')
			game.save_game();
	}

	//toggle functions here
	switch (key){
	case 'f':
	case 'F':
		game.display_fps = !game.display_fps;
		break;
	case 'c':
	case 'C':
		game.display_coordinates = !game.display_coordinates;
		break;
	case 'b':
	case 'B':
		game.enable_fish_vs_fish = !game.enable_fish_vs_fish;
		break;
	case 'V':
	case 'v':
		game.display_hud = !game.display_hud;
		break;
	//case 'L':
	//	game.enable_end_of_game = !game.enable_end_of_game;
	//	break;
	case ' ':
		game.myShark.escort_mode = !game.myShark.escort_mode;
		break;
	//case 'R':
	//	display_update_rates = !display_update_rates;
	//	break;
	//case 'r':
	//	theta = 90;
	//	break;
	//case 'T':
	//case 't':
	//	add_fish();
	//	break;
	//case 'G':
	//case 'g':
	//	remove_fish();
	//	break;
	case '1':
		mySub.set_buoyancy(1.0);
		break;
	case '2':
		game.set_camera_free();
		break;
	case '3':
		game.camera_mode = 1;
		break;
	case '4':
		game.camera_mode = 2;
		break;
	//case 'P':
	//case 'p':
	//	game.set_show_collision_spheres(true);
	//	break;
	//case ';':
	//	game.set_show_collision_spheres(false);
	//	break;
	//case 'o':
	//	game.enable_fog = true;
	//	break;
	//case 'l':
	//	game.enable_fog = false;
	//	break;
	case 27:
		if(!game.game_over && !game.new_game)
		{
			game.game_running = !game.game_running;
			game.saved = false;
		}
		break;
	//case 'p':
	//case 'P':
	//	display_points = !display_points;
	//	break;
	//case 'o':
	//case 'O':
	//	display_fish_counter = !display_fish_counter;
	//	break;
	}
}

void special(int special_key, int x, int y)
{
	keySpecialStates[special_key] = true;
	if(keySpecialStates[GLUT_KEY_PAGE_UP])
	{
		if(mySub.velocity.y < 25)
			mySub.velocity.y += 5;
	}
	if(keySpecialStates[GLUT_KEY_PAGE_DOWN])
	{
		if(mySub.velocity.y > -25)
			mySub.velocity.y -= 5;
	}
}