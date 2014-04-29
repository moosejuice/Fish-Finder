#pragma once
#include "fish.h"
#include <time.h>
#include "global_variables.h"
//#include "ObjLibrary/TextureManager.h"
#include "glut.h"
#include "game.h"
#include "temp_inc_game.h"

void generate_fish(void)
{
	//number of fish between 100 and 200 to generate in the world
	NUMFISH = rand() % 100 + 100;
	//NUMFISH = 50;
	for(int i = 0; i < NUMFISH; i++)
	{
		game.myFish.push_back(random_fish());
	}
}

Fish random_fish(void)
{
	/*************
	gen 1 of 6 random fish..				odds of gen
	0 - simple orange fish		pt. 3			84/100
	1 - orca					pt. 25			1/100
	2 - stingray				pt. 15			1/100
	3 - manatee					pt. 10			2/100			max speed 10
	4 - bass					pt. 5			10/100
	5 - dolphin					pt. 20			1/100
	6 - whale					pt. 20			1/100	
	**************/
	Fish tempFish;
	int random;
	random = rand() % 100;
	switch (random)
	{
	case 1:
		tempFish.fish_type = 1;		//orca
		tempFish.acceleration = 5.0;
		tempFish.point_value = 25;
		tempFish.fish_radius = 15.0;
		tempFish.max_speed = 20.00;	
		break;
	case 2:
		tempFish.fish_type = 2;		//stingray
		tempFish.acceleration = 5.0;
		tempFish.point_value = 15;
		tempFish.fish_radius = 5.0;
		tempFish.max_speed = 15.00;	
		break;
	case 3:
		tempFish.fish_type = 3;		//manatee
		tempFish.acceleration = 5.0;
		tempFish.point_value = 10;
		tempFish.fish_radius = 5.0;
		tempFish.max_speed = 10.00;	
		break;
	case 4:
		tempFish.fish_type = 4;		//bass
		tempFish.acceleration = 7.0;
		tempFish.point_value = 5;
		tempFish.fish_radius = 5.0;
		tempFish.max_speed = 20.00;	
		break;
	case 5:
		tempFish.fish_type = 5;		//dolphin
		tempFish.acceleration = 10.0;
		tempFish.point_value = 20;
		tempFish.fish_radius = 5.0;
		tempFish.max_speed = 20.00;	
		break;
	case 6:
		tempFish.fish_type = 6;		//whale
		tempFish.acceleration = 8.0;
		tempFish.point_value = 20;
		tempFish.fish_radius = 5.0;
		tempFish.max_speed = 20.00;	
		break;
	default:
		tempFish.fish_type = 0;		//simple orange fish
		tempFish.acceleration = 10.0;
		tempFish.point_value = 3;
		tempFish.fish_radius = 5.0;
		tempFish.max_speed = 22.00;	
		break;
	}

		
		tempFish.in_viewport = true;
		tempFish.location.set(float( rand() % (2*int(MAXLOC)) - MAXLOC), float( rand() % (int(MAXLOCY)) - MINLOCY), float( rand() % (2*int(MAXLOC)) - MAXLOC));
		tempFish.previous_location = tempFish.location;
		tempFish.red = rand() % 256;
		tempFish.blue = 0;
		tempFish.green = rand() % 256;
		tempFish.isCaptured = false;
		tempFish.mass = 1.0;
		tempFish.speed = 5.0f;		
		tempFish.flock_count = 0;
				//m, total length = 10m, fish.obj is 1. fish.obj is currently doubled in size
		tempFish.current_velocity = Vector3::getRandomUnitVector();;
		tempFish.target_velocity = tempFish.current_velocity;
		tempFish.nearest_fish.clear();
		tempFish.FISH_NEIGHBOR_MAX_DISTANCE = 150.0;
		tempFish.FISH_NEIGHBOR_MAX_COUNT = 4;
		tempFish.FISH_COHESION_WEIGHT = 0.2;
		tempFish.FISH_ALIGNMENT_WEIGHT = 0.3;
		tempFish.FISH_SEPARATION_WEIGHT = 0.5;
		tempFish.FISH_SEPARATION_MAX_DISTANCE = 15.0;
		return(tempFish);
}

void add_fish(void)		//generates 1 new fish
{
		game.myFish.push_back(random_fish());
		NUMFISH++;
		
		for (std::vector<Fish>::iterator it = game.myFish.begin(); it != game.myFish.end(); it++)
		{
			it->nearest_fish.clear();
		}
		slow_ai_iterator = game.myFish.begin();			//iterator is invalidated when vector size is modified. reset it
}
void remove_fish(void)		//removes 1 fish
{
	if(NUMFISH > 0)
	{
		game.myFish.pop_back();
		NUMFISH--;
		slow_ai_iterator = game.myFish.begin();
		for (std::vector<Fish>::iterator it = game.myFish.begin(); it != game.myFish.end(); it++)
		{
			it->nearest_fish.clear();
		}
	}
}

bool Fish::sort_help(const Fish_Distance& first, const Fish_Distance& second)
{
	if(first.distance < second.distance)
		return true;
	else
		return false;
}


void Fish::draw(void)
{
	/*************
	gen 1 of 7 random fish..				odds of gen
	0 - simple orange fish		pt. 3			84/100
	1 - orca					pt. 25			1/100
	2 - stingray				pt. 15			1/100
	3 - manatee					pt. 10			2/100			max speed 10
	4 - bass					pt. 5			10/100
	5 - dolphin					pt. 20			1/100
	6 - whale					pt. 20			1/100	
	**************/
	if(!isCaptured)
		{
			float vert_rot = 0; //-current_velocity.getRotationX()*RadToDeg;
			switch (fish_type)
			{
			case 0:
					glPushMatrix();
						glTranslatef(location.x, location.y, location.z);	// unneeded since default position is (0, 0, 0)
						glRotatef((current_velocity.getRotationY()*RadToDeg ), 0.0, 1.0, 0.0);	// unneeded since default rotation is 0 degrees
						glRotatef( vert_rot , 1.0, 0.0, 0.0);

						glScalef(2.0, 2.0, 2.0);		// unneeded since default scaling is 1 in X, Y, and Z
						fish_list[0].draw();
					glPopMatrix();
					break;
			case 1:
					glPushMatrix();
						glTranslatef(location.x, location.y, location.z);	// unneeded since default position is (0, 0, 0)
						glRotatef((current_velocity.getRotationY()*RadToDeg), 0.0, 1.0, 0.0);	// unneeded since default rotation is 0 degrees
						glRotatef( vert_rot , 1.0, 0.0, 0.0);
						glScalef(3.0, 3.0, 3.0);		// unneeded since default scaling is 1 in X, Y, and Z
						fish_list[1].draw();
					glPopMatrix();
				break;
			case 2:
					glPushMatrix();
						glTranslatef(location.x, location.y, location.z);	// unneeded since default position is (0, 0, 0)
						glRotatef((current_velocity.getRotationY()*RadToDeg), 0.0, 1.0, 0.0);	// unneeded since default rotation is 0 degrees
						glRotatef( vert_rot , 1.0, 0.0, 0.0);
						glScalef(10.0, 10.0, 10.0);		// unneeded since default scaling is 1 in X, Y, and Z
						fish_list[2].draw();
					glPopMatrix();
				break;
			case 3:
					glPushMatrix();
						glTranslatef(location.x, location.y, location.z);	// unneeded since default position is (0, 0, 0)
						glRotatef((current_velocity.getRotationY()*RadToDeg), 0.0, 1.0, 0.0);	// unneeded since default rotation is 0 degrees
						glRotatef( vert_rot , 1.0, 0.0, 0.0);
						glScalef(10.0, 10.0, 10.0);		// unneeded since default scaling is 1 in X, Y, and Z
						fish_list[3].draw();
					glPopMatrix();
				break;
			case 4:
					glPushMatrix();
						glTranslatef(location.x, location.y, location.z);	// unneeded since default position is (0, 0, 0)
						glRotatef((current_velocity.getRotationY()*RadToDeg), 0.0, 1.0, 0.0);	// unneeded since default rotation is 0 degrees
						glRotatef( vert_rot , 1.0, 0.0, 0.0);
						glScalef(25.0, 25.0, 25.0);		// unneeded since default scaling is 1 in X, Y, and Z
						fish_list[4].draw();
					glPopMatrix();
				break;
			case 5:
					glPushMatrix();
						glTranslatef(location.x, location.y, location.z);	// unneeded since default position is (0, 0, 0)
						glRotatef((current_velocity.getRotationY()*RadToDeg), 0.0, 1.0, 0.0);	// unneeded since default rotation is 0 degrees
						glRotatef( vert_rot , 1.0, 0.0, 0.0);
						glScalef(6.0, 6.0, 6.0);		// unneeded since default scaling is 1 in X, Y, and Z
						fish_list[5].draw();
					glPopMatrix();
				break;
			case 6:
					glPushMatrix();
						glTranslatef(location.x, location.y, location.z);	// unneeded since default position is (0, 0, 0)
						glRotatef((current_velocity.getRotationY()*RadToDeg), 0.0, 1.0, 0.0);	// unneeded since default rotation is 0 degrees
						glRotatef( vert_rot , 1.0, 0.0, 0.0);
						glScalef(9.0, 9.0, 9.0);		// unneeded since default scaling is 1 in X, Y, and Z
						fish_list[6].draw();
					glPopMatrix();
				break;
			}
			
			if(game.get_show_collision_spheres())
			{
				glPushMatrix();
					glTranslatef(location.x, location.y, location.z);	// unneeded since default position is (0, 0, 0)
					glRotatef((current_velocity.getRotationY()*RadToDeg), 0.0, 1.0, 0.0);	// unneeded since default rotation is 0 degrees
					glRotatef(vert_rot, 1.0, 0.0, 0.0);
					glutWireSphere(fish_radius, 10, 20);
				glPopMatrix();
			}
		}
}

