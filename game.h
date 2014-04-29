#ifndef GAME_H
#define GAME_H
#include "collision_detection.h"
#include "constants.h"
#include "ai.h"
#include "displays.h"
#include "keyboard_operations.h"
#include "camera.h"
#include "fish.h"
#include "ObjLibrary/ObjModel.h"
#include "ObjLibrary/DisplayList.h"
//#include "global_variables.h"
#include "glut.h"
#include "shark.h"



class Game : public constants, public AI, public Display, public collision_detection , public Camera
{
	friend class Display;
	friend class collision_detection;
	friend class AI;
	friend class Fish;
	friend class Camera;
	friend class Shark;
	friend void keyboard(unsigned char key, int x, int y);
	friend void idle();
	friend void check_for_fish_capture();
	friend void draw_fish(void);
	friend void fish_physics(int);
	friend void init(void);
	friend void fish_world_edge_check(void);
	friend void check_for_fish_capture(void);
	friend void generate_fish(void);
	friend void add_fish(void);
	friend void remove_fish(void);

public:

	void init_game(void);
	void create_new_game(void);
	bool get_show_collision_spheres(void);
	int FPS(void);

	void set_show_collision_spheres(bool);
	void display(void);
	void check_game_over(void);
	void update_culling_distance(void);
	void check_for_fish_capture(void);
	void update();
	void set_game_running(bool);

	void save_game(void);
	void load_game(void);
	//void set_new_game(bool);
	Shark myShark;

private:
	bool show_collision_spheres;
	std::vector<Fish> myFish;
	//display toggles
bool display_fps;
bool display_coordinates;
bool display_fish_counter;
bool display_hud;
bool display_points;
bool enable_end_of_game;
bool display_update_rates;
bool game_running;
bool game_over;
bool new_game;
bool enable_fish_vs_fish;
int average_display, average_update, start, frames;
float culling_distance;
int physics_lag;		//time in ms
int ai_lag;
int PhysicsFixedDeltaTime;	//time in ms
int AIFixedDeltaTime;		//time in ms 
int SlowFishUpdateNumber;
float fogDistance;
int fps;
DisplayList orca_list;
ObjModel orcaObj;
int fish_caught[7];
bool saved;
char *fish_names[7];
int fish_types_caught;
};

#endif