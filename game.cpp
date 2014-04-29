#pragma once
#include "game.h"
#include "global_variables.h"
#include "Sleep.h"
#include <time.h>
#include "drawings.h"
#include "ObjLibrary/TextureManager.h"
#include <fstream>
//#include <iostream>

void Game::init_game(void)
{
	ObjModel fishObj[7];
//	std::cout << "Initialization Begun\n";
	init_constants();
	init_display();
	std::vector<Fish> myFish;		//holds all the fish in the world
	init_camera();

	new_game = true;
	update_culling_distance();
	std::cout << "Culling Distance: " << culling_distance << std::endl;
	game_running = true;

	fish_names[0] = "Orange Fish";
	fish_names[1] = "Orca";
	fish_names[2] = "Stingray";
	fish_names[3] = "Manatee";
	fish_names[4] = "Bass";
	fish_names[5] = "Dolphin";
	fish_names[6] = "Whale";

	mySub.init_sub();
		glColor3ub(0, 0, 0);		// drawing color = black
	glLineWidth(2.0f);
	glEnable(GL_DEPTH_TEST);
	//game.init_display();
	srand(unsigned int(time(NULL)));		//seed our generator here

	read_height_map();
	std::cout << "Initializing ocean floor\n";
	ocean_floor = glGenLists(1);
	//send the ocean floor information to the GPU and store it there for massive performance increase
	glNewList(ocean_floor, GL_COMPILE);
		draw_ocean_floor();
	glEndList();

	std::cout << "Initializing Fish";
	fishObj[0].load("Fish/fish.obj");
	fish_list[0] = fishObj[0].getDisplayList();
	std::cout << ".";
	fishObj[1].load("Fish/ORCA.obj");
	fish_list[1] = fishObj[1].getDisplayList();
	std::cout << ".";
	fishObj[2].load("Fish/STINGRAY.obj");
	fish_list[2] = fishObj[2].getDisplayList();
	std::cout << ".";
	fishObj[3].load("Fish/MANATEE2.obj");
	fish_list[3] = fishObj[3].getDisplayList();
	std::cout << ".";
	fishObj[4].load("Fish/LM_BASS.obj");
	fish_list[4] = fishObj[4].getDisplayList();
	std::cout << ".";
	fishObj[5].load("Fish/DOLPHIN.obj");
	fish_list[5] = fishObj[5].getDisplayList();
	std::cout << ".";
	fishObj[6].load("Fish/whale4s.obj");
	fish_list[6] = fishObj[6].getDisplayList();
	std::cout << ".";
	myShark.load_shark();

	std::cout << "\nInitializing Complete\n";
	game_running = false;
	//game.set_game_running(false);
	//
	physics_lag = 0;		//time in ms
	ai_lag = 0;
	previous_time = glutGet(GLUT_ELAPSED_TIME);
	current_time = previous_frame = previous_time;
}

void Game::create_new_game(void)
{
	myFish.empty();
	show_collision_spheres = false;
	//display toggles
	display_fps = false;
	display_coordinates = true;
	display_fish_counter = true;
	display_hud = true;
	display_points = true;
	enable_end_of_game = true;
	display_update_rates = false;
	game_running = false;
	game_over = false;
	enable_fish_vs_fish = false;
	enable_fog = true;
	saved = false;
	average_display = average_update = frames = start = 0;
	fish_caught[7] = 0;
	fish_types_caught = 0;
	fogDistance = 250.0;
	fps = 0;
	std::cout << "Generating Fish\n";
	generate_fish();
	fishCaptured = 0;
	user_points = 0;
	slow_ai_iterator = myFish.begin();
	myShark.init_shark();
	std::cout << "Initializing Submarine\n";
	//mySub.init_sub();
	mySub.reset_sub();
}


void Game::display(void)
{
	start = glutGet(GLUT_ELAPSED_TIME);

	if(game_running)
	{
		draw_main_game();
	}
	else
	{
		draw_pause_screen();
	}

	average_display = (average_display + glutGet(GLUT_ELAPSED_TIME) - start)/2;
	frames++;
		// ensure that all buffered OpenGL commands get done
	glFlush();	
	glutSwapBuffers();
//	std::cout << "Done GLUT display()\n";
}



bool Game::get_show_collision_spheres(void)
{
	return show_collision_spheres;
}

void Game::set_show_collision_spheres(bool value)
{
	show_collision_spheres = value;
}

void Game::update_culling_distance(void)
{
	Vector3 temp;
	GLint m_viewport[4];	//height = 3, width = 2 of the current window
	glGetIntegerv(GL_VIEWPORT, m_viewport);		//populate m_viewport
	temp = mySub.get_location();
	temp.x += m_viewport[2]/2;
	temp.y += m_viewport[3]/2;
	temp.z += fogDistance;
	culling_distance = mySub.get_location().getDistance(temp);
	
}

void Game::check_for_fish_capture(void)
{
	//for each fish, we need to calculate the distance between its center and the submarine center.
	//if close enough, that fish will be captured, captured with will be incremented
	//and that fish will be removed from the myFish vector

	//fish is "captured" if it's location sphere is with in 4 meters(units) of the outside of the submarine

	for (std::vector<Fish>::iterator it = myFish.begin(); it != myFish.end(); it++)
	{
		if(!it->isCaptured){
			float temp = mySub.get_subSphereRadius() + 6.0 + it->fish_radius;
			if(it->location.getDistanceSquared(mySub.get_location()) < temp*temp)
			{
				fishCaptured++;
				user_points += it->point_value;
				it->isCaptured = true;
			}
		}
	}
	
}

void Game::check_game_over(void)
{
	if(enable_end_of_game && fishCaptured >= 10)
	{
		//trigger win here. Set flag that game is over and open the menu
		game_running = false;
		game_over = true;
	}
}


void Game::update()
{
		/*std::cout << "Start GLUT idle()\n";*/
	start = glutGet(GLUT_ELAPSED_TIME);
	if(game_running)		//if game is paused, we wont update anything.
	{
		//deal with keyboard  before updating physics and AI
		keyboardOperations();		
		//determine the new update delta times in ms per update
		PhysicsFixedDeltaTime = 1 / ( get_physics_update_rate() / 1000);
		AIFixedDeltaTime = 1 / ( get_fast_ai_update_rate() / 1000);
		SlowFishUpdateNumber = NUMFISH * get_slow_ai_update_rate();	//acts as truncated rounding.

		current_time = glutGet(GLUT_ELAPSED_TIME);
		physics_lag += (current_time - previous_time);
		ai_lag += (current_time - previous_time);

		while(physics_lag > PhysicsFixedDeltaTime || ai_lag > AIFixedDeltaTime)
		{
			if((physics_lag - PhysicsFixedDeltaTime) > (ai_lag - AIFixedDeltaTime))
			{
				fish_physics(PhysicsFixedDeltaTime);
				mySub.update_physics(PhysicsFixedDeltaTime);
				physics_lag -= PhysicsFixedDeltaTime;
				myShark.physics(PhysicsFixedDeltaTime);

				mySub.check_world_bounds();
				fish_collision_detection();
				myShark.collision_detection();
			}
			else
			{
				slow_fish_ai(SlowFishUpdateNumber);
				fast_fish_ai(AIFixedDeltaTime);
				myShark.slow_AI();
				myShark.fast_AI(AIFixedDeltaTime);
				
				ai_lag -= AIFixedDeltaTime;
			}

		}

		//set velocity flags as false. This causes velocity to increase for every physics update in the above looopo instead of 1, giving us a max speed of ~ 90m/s instead of a max speed dependant on system speed
		mySub.set_decrease_velocity(false);
		mySub.set_increase_velocity(false);
		previous_time = current_time;
		
	//	check_game_over();
	}
	else	//game is paused.
	{
		sleep(0.03);	//slow down frame rate to about 30fps for pause screen.
		//while paused, keep previous and current time the same and upto date to avoid having the lag
		//function try to catch up all the paused time.
		current_time = glutGet(GLUT_ELAPSED_TIME);
		previous_time = current_time;	
	}
	average_update = (average_update + glutGet(GLUT_ELAPSED_TIME) - start)/2;
	glutPostRedisplay();
	
}

void Game::set_game_running(bool value)
{
	game_running = value;
}

int Game::FPS(void)
{
	new_time = glutGet(GLUT_ELAPSED_TIME);
	if ((new_time - base_time) > 1000.0)
	{
		fps = frames*1000.0/(new_time - base_time);
		base_time = new_time;
		frames = 0;
	}
	return fps;
}

void Game::save_game(void)
{
	std::ofstream saveFile;
	saveFile.open("game.save");
	if(saveFile.is_open())
	{
		saveFile << user_points << std::endl;
		for(int i = 0; i < 7; i++)
			saveFile << fish_caught[i] << " ";
		saveFile.close();
		saved = true;
	}

}



void Game::load_game(void)
{
	std::ifstream loadFile;
	loadFile.open("game.save");
	if(loadFile.is_open())
	{
		loadFile >> user_points;
		for(int i = 0; i < 7; i++)
			loadFile >> fish_caught[i];
		loadFile.close();
	}
}




