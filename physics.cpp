#pragma once
#include "physics.h"
#include "global_variables.h"
#include <vector>
#include "temp_inc_game.h"

void fish_physics(int time_interval)		//int time_interval in ms
{
	for (std::vector<Fish>::iterator it = game.myFish.begin(); it != game.myFish.end(); it++)
	{
		if(it->in_viewport)
		{
			it->previous_location = it->location;
			it->current_velocity.normalize();
			it->location = (it->current_velocity * it->speed * time_interval/1000) + it->location;

			/*
			if(it->location.x > MAXLOC)
				it->location.x -= MAXLOC;
			if(it->location.x < MINLOC)
				it->location.x -= MINLOC;

			if(it->location.z > MAXLOC)
				it->location.z -= MAXLOC;
			if(it->location.z < MINLOC)
				it->location.z -= MINLOC;

				*/
		}
	}
	
}

void submarine_physics(int delta_time)	//March 6, removed usage as a result of object creating and structure
{
	mySub.update_physics(delta_time);
}