#pragma once
#include "shark.h"
#include "game.h"
#include "temp_inc_game.h"
#include "global_variables.h"
#include <algorithm>

void Shark::load_shark(void)
{
	sharkObj.load("Fish/HAMRHEAD.obj");
	//sharkObj.load("Fish/STINGRAY.obj");
	//sharkObj.load("Fish/MANATEE2.obj");
	//sharkObj.load("Fish/LM_BASS.obj");
	//sharkObj.load("Fish/DOLPHIN.obj");
//	sharkObj.load("Fish/Box_of_gold_florins.obj"); //needs to be placed under the surface
	shark_list = sharkObj.getDisplayList();
}
void Shark::init_shark(void)
{
	location.set(0.0,70.0,25.0);
	direction.set(1.0,0.0,0.0);
	explore_target.set(100,100,100);
	velocity.setZero();
	previous_location.set(0.0,50.0,0.0);// = location;

	MASS = 20.0;
	MAX_SPEED = 50.0;
	ACCELERATION = 25.0;
	RADIUS = 5.0;
	ESCORT_DISTANCE = 25.0;
	ARRIVAL_SLOW_DISTANCE = 50.0;
	DETECT_FISH_RADIUS = 200.0;
	EXPLORE_CLOSE_ENOUGH = 50.0;
	PURSUIT_LOOK_AHEAD_FACTOR = 0.025;
	escort_mode = true;
	speed = 0.0;
	target_fish = NULL;	
	slow_AI_counter = 0;
}


void Shark::draw(void)
{
	glPushMatrix();
		glTranslatef(location.x, location.y, location.z);
		glRotatef(velocity.getRotationY()*RadToDeg, 0.0, 1.0, 0.0);
		glScalef(5.0, 6.0, 5.0); 
		shark_list.draw();
	glPopMatrix();
	if(game.get_show_collision_spheres())
	{
		glPushMatrix();
			glColor3ub(188,198,204);
			glTranslatef(location.x, location.y, location.z);
			glutWireSphere(RADIUS, 10, 20);
		glPopMatrix();

	}
}

void Shark::fast_AI(int time)
{
	if(escort_mode)			//is in escort mode
	{
		if(location != location)
			location.set(100,100,100);
		if(velocity != velocity)
			velocity.set(0,0,0);

		Vector3 target_location;
		target_location.set(
			mySub.location.x + ESCORT_DISTANCE*cos(-(mySub.rotation-90)*degToRad),
			mySub.location.y,
			mySub.location.z + ESCORT_DISTANCE*sin(-(mySub.rotation-90)*degToRad));

		if( target_location.getDistanceSquared(location) < (ARRIVAL_SLOW_DISTANCE*ARRIVAL_SLOW_DISTANCE) )
		{
			speed = MAX_SPEED * target_location.getDistanceSquared(location)/(ARRIVAL_SLOW_DISTANCE*ARRIVAL_SLOW_DISTANCE);
			//linearly slow the shark
		}
		else
		{
			speed = MAX_SPEED;
		}

		steering_vector =  velocity*speed*time/1000 - ((location - target_location).getNormalized()*speed*time/1000);
		if(steering_vector.getNorm() > (ACCELERATION*time/1000))
		{
			steering_vector.normalize();
			steering_vector *= ACCELERATION*time/1000;
		}
		velocity += steering_vector;
	}
	else					//is in chase mode.
	{
		if(target_fish == NULL)
		{
			if(explore_target.getDistanceSquared(location) <= (EXPLORE_CLOSE_ENOUGH*EXPLORE_CLOSE_ENOUGH))		//shark reached destination
				pick_explore_target();

			//explore to target
			speed = MAX_SPEED;
			steering_vector = velocity*speed*time/1000 - ((location - explore_target).getNormalized()*speed*time/1000);
			if(steering_vector.getNorm() > (ACCELERATION*time/1000))
			{
				steering_vector.normalize();
				steering_vector *= ACCELERATION*time/1000;
			}
			velocity += steering_vector;
		}
		else
		{
			if(!target_fish->isCaptured)
			{
				//has a target fish that is not captured.
				speed = MAX_SPEED;
				Vector3 r, d;
				r = (target_fish->location + target_fish->current_velocity*target_fish->speed * PURSUIT_LOOK_AHEAD_FACTOR) - location;
				d = r / r.getNorm() * MAX_SPEED;
				//steering_vector = velocity*speed*time/1000 - ((location - target_fish->location + target_fish->current_velocity).getNormalized()*speed*time);
				steering_vector = d - velocity;
				if(steering_vector.getNorm() > (ACCELERATION*time/1000))
				{
					steering_vector.normalize();
					steering_vector *= ACCELERATION*time/1000;
				}
				velocity += steering_vector;
				//use pursue to try and catch the fish
			}
			else
			{
				target_fish = NULL;
				//continue on current path for a little bit. Looks and works better than immediately veering off. Espcially for catching groups of fish.
				explore_target = velocity.getNormalized()*1.25*MAX_SPEED + location;
				if (explore_target.y < 100)
					explore_target.y = 100;
			}

		}

	//	return;
	}


}

void Shark::slow_AI(void)
{
	slow_AI_counter++;
	if(slow_AI_counter >= NUMFISH)		//do this AI at same rate as fish. once for every time a fish gets a slow ai rate.
	{
		slow_AI_counter %= NUMFISH;
		if(!escort_mode)			//is in chase mode. Nothing to do here if in escort mode. 
		{
			nearest_fish.clear();
			bool has_fish;
			if(target_fish != NULL)
				has_fish = true;
			else
				has_fish = false;
			
			if(velocity != Vector3::ZERO)		//if shark is not moving, dont try to look for fish. start moving.
			{
				for (std::vector<Fish>::iterator it = game.myFish.begin(); it != game.myFish.end(); it++)
				{
					if(location.getDistanceSquared(it->location) <= (DETECT_FISH_RADIUS*DETECT_FISH_RADIUS))
					{
						float angle;
						angle = cos(location.dotProduct(it->location)/(location.getNorm() * it->location.getNorm()));
						//angle = acos(angle1);
						//std::cout << angle*RadToDeg << std::endl;
						//if (angle < pi/3 && angle > 0)
						//	std::cout << angle*RadToDeg << " " << angle1*RadToDeg << std::endl;
						if( acos(angle) < (pi/3) )		//shark can see
						{
							if(it->fish_type != 1)		//if fish is not orca. Hammerhead shark cannot takedown an orca
							{
								Fish::Fish_Distance temp;
								temp.distance = location.getDistanceSquared(it->location);
								temp.fish_ptr = it._Ptr;
								nearest_fish.push_back(temp);
							}
						}
					}
				}
			}
			if(!nearest_fish.empty())		//if shark can see fish, sort viewable fish and set target to closest fish.
			{
				sort(nearest_fish.begin(), nearest_fish.end(), Fish::sort_help );		
				target_fish = nearest_fish.front().fish_ptr;
				//std::cout << "Target Aquired: " << nearest_fish.front().distance << std::endl;
			}
			else
			{
				target_fish = NULL;
				if(has_fish)
					pick_explore_target();
			}
		}
	}
}

void Shark::physics(int time_interval)
{
		previous_location = location;
		velocity.normalize();
		location += (velocity * speed * time_interval/1000);// + location;
		//std::cout << location << std::endl;
}


void Shark::collision_detection(void)
{
	/***********************
	    Shark vs Ground
	************************/
	game.object_vs_ground(location, RADIUS, velocity);
	/***********************
	    Shark vs Sub
	************************/
	if( location.getDistanceSquared(mySub.location) < ((RADIUS+mySub.subOuterRadius)*(RADIUS+mySub.subOuterRadius)))
	{
		//adjust velocities in similar way as fish vs fish collisions. Setting each to previouis location would stop them in place. added an additional change to allow movement
		Vector3 between;
		between = location - mySub.location;
		velocity = velocity - 2*velocity.projection(between);
		location = previous_location + between/64;
		mySub.location = mySub.previous_location;
		mySub.velocity - mySub.velocity - 2*mySub.velocity.projection(between);
	}
	/***********************
	    Shark vs Fish
	************************/
	
	for (std::vector<Fish>::iterator it = game.myFish.begin(); it != game.myFish.end(); it++)
	{
		if(!it->isCaptured)
		{
			if(it->location.getDistanceSquared(location) < (RADIUS+it->fish_radius)*(RADIUS+it->fish_radius))
			{
					it->isCaptured = true;
					fishCaptured++;
					user_points += floor(it->point_value/2);
					game.fish_caught[it->fish_type]++;
					if(game.fish_caught[it->fish_type] == 1)
						game.fish_types_caught++;
					slow_AI_counter += NUMFISH;
					slow_AI();
			}
		}

	}

}


void Shark::pick_explore_target(void)
{
	float t;
	t=float( rand() % (int(MAXLOCY)) - MINLOCY);
	explore_target.set(float( rand() % (2*int(MAXLOC)) - MAXLOC), (t<100.0)?100:t , float( rand() % (2*int(MAXLOC)) - MAXLOC));
	//std::cout << "New Target: " << explore_target << std::endl;
}
