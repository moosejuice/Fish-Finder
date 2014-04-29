#pragma once
#include "collision_detection.h"
#include "temp_inc_game.h"
#include "global_variables.h"


void collision_detection::fish_collision_detection(void)
{
	for (std::vector<Fish>::iterator it = game.myFish.begin(); it != game.myFish.end(); it++)
	{
		if(!it->isCaptured)
		{
			sub_fish_rad_squared = (mySub.get_subOuterRadius() + game.myFish.front().fish_radius);
			sub_fish_rad_squared *= sub_fish_rad_squared;
			/* ========================================== */
			//fish vs surface
			/* ========================================== */
			//if((it->location.x - it->fish_radius) < MINLOC)
			//{
			//	it->location.x = MINLOC+it->fish_radius;
			//	it->current_velocity.x *= -1;
			//	it->target_velocity = it->current_velocity;
			//}
			//if((it->location.x + it->fish_radius) > MAXLOC){
			//	it->location.x = MAXLOC-it->fish_radius;
			//	it->current_velocity.x *= -1;
			//	it->target_velocity = it->current_velocity;
			//}
			//if((it->location.z - it->fish_radius) < MINLOC){
			//	it->location.z = MINLOC+it->fish_radius;
			//	it->current_velocity.z *= -1;
			//	it->target_velocity = it->current_velocity;
			//}
			//if((it->location.z + it->fish_radius) > MAXLOC){
			//	it->location.z = MAXLOC-it->fish_radius;
			//	it->current_velocity.z *= -1;
			//	it->target_velocity = it->current_velocity;
			//}

			if(it->location.x > MAXLOC)
			{it->location.x = MINLOC;}// it->nearest_fish.clear();}
			if(it->location.x < MINLOC)
			{it->location.x = MAXLOC;}//it->nearest_fish.clear();}

			if(it->location.z > MAXLOC)
			{it->location.z = MINLOC;}//it->nearest_fish.clear();}
			if(it->location.z < MINLOC)
			{it->location.z = MAXLOC;}//it->nearest_fish.clear();}

			 
			if((it->location.y + it->fish_radius) > MAXLOCY)
			{
				it->location = it->previous_location;
				it->current_velocity.y *= -1;
				it->target_velocity = it->current_velocity;
				int count = 0;
				for(std::vector<Fish::Fish_Distance>::iterator flock_ptr = it->nearest_fish.begin(); flock_ptr != it->nearest_fish.end(); flock_ptr++)
				{
					flock_ptr->fish_ptr->current_velocity.y *= -1;
					flock_ptr->fish_ptr->target_velocity = flock_ptr->fish_ptr->current_velocity;
					count++;
					if (count <= it->FISH_NEIGHBOR_MAX_COUNT)
						break;
				}
			}
			


			/* ========================================== */
			// fish vs fish 
			/* ========================================== */
			if(game.enable_fish_vs_fish)
			{
				for(std::vector<Fish::Fish_Distance>::iterator flock_ptr = it->nearest_fish.begin(); flock_ptr != it->nearest_fish.end(); flock_ptr++)
				{
					//since a fish is part of its own flock, dont bother checking for a collision with itself. If our iterator points to the same mem address as our flock pointer we can ignore
					if( (*flock_ptr).fish_ptr != it._Ptr )
					{
						if(it->location.getDistanceSquared((*flock_ptr).fish_ptr->location) < (it->fish_radius * 2))
						{
							it->location = it->previous_location;
							//To adjust the velocities, subtract twice the projection of the current velocity onto the vector between the fish from the velocity of each fish.
							Vector3 between;
							between = it->location - (*flock_ptr).fish_ptr->location;
							it->current_velocity = it->current_velocity - 2*it->current_velocity.projection(between);
							it->location = it->previous_location;
						}
					}
				}
			}

		/* ========================================== */
			//fish vs sub
		/* ========================================== */
			if(it->location.getDistanceSquared(mySub.get_location()) < sub_fish_rad_squared)
			{
				//outer layer breached. Must now check second layer
				//should place inner collision sphere calculation of submarine here..
				float fish_inner_sub_squared = (mySub.subSphereRadius+it->fish_radius)*(mySub.subSphereRadius+it->fish_radius);
				if(it->location.getDistanceSquared(mySub.collision1) < fish_inner_sub_squared)	//fish collision with sphere 1
				{
					it->isCaptured = true;
					fishCaptured++;
					user_points += it->point_value;
					game.fish_caught[it->fish_type]++;
					if(game.fish_caught[it->fish_type] == 1)
						game.fish_types_caught++;
					break;		//to not double count a fish being captured.
				}
				else if(it->location.getDistanceSquared(mySub.collision2) < fish_inner_sub_squared)	//fish collision with sphere 2
				{
					it->isCaptured = true;
					fishCaptured++;
					user_points += it->point_value;
					game.fish_caught[it->fish_type]++;
					if(game.fish_caught[it->fish_type] == 1)
						game.fish_types_caught++;
					break;
				}
				else if(it->location.getDistanceSquared(mySub.collision3) < fish_inner_sub_squared)	//fish collision with sphere 3
				{
					it->isCaptured = true;
					fishCaptured++;
					user_points += it->point_value;
					game.fish_caught[it->fish_type]++;
					if(game.fish_caught[it->fish_type] == 1)
						game.fish_types_caught++;
					break;
				}
				else if(it->location.getDistanceSquared(mySub.collision4) < fish_inner_sub_squared)	//fish collision with sphere 4
				{
					it->isCaptured = true;
					fishCaptured++;
					user_points += it->point_value;
					game.fish_caught[it->fish_type]++;
					if(game.fish_caught[it->fish_type] == 1)
						game.fish_types_caught++;
					break;
				}
				else if(it->location.getDistanceSquared(mySub.location) < fish_inner_sub_squared)	//fish collision with sphere at origin of sub
				{
					it->isCaptured = true;
					fishCaptured++;
					user_points += it->point_value;
					game.fish_caught[it->fish_type]++;
					if(game.fish_caught[it->fish_type] == 1)
						game.fish_types_caught++;
					break;
				}
			}
		/* ========================================== */
			//fish vs ground
		/* ========================================== */
			object_vs_ground(it->location, it->fish_radius, it->current_velocity, it->target_velocity);


		}
	}

}

void collision_detection::check_fish_culling(void)
{
	for (std::vector<Fish>::iterator it = game.myFish.begin(); it != game.myFish.end(); it++)
	{
		if(it->location.getDistanceSquared(mySub.get_location()) >= game.culling_distance)
			it->in_viewport = false;
	}
}

void collision_detection::object_vs_ground(Vector3 &location, float sphere, Vector3 &current_velocity, Vector3 &target_velocity)
{
	object_vs_ground(location, sphere, current_velocity);
	target_velocity = current_velocity;
}

void collision_detection::object_vs_ground(Vector3 &location, float sphere, Vector3 &current_velocity)
{
	//the heightmap is translated by -500, 0, -500, so we need to adjust the co-ordinates accordingly
	float x, y, z, cx, cz, qk, qi, fk, fi;
	int k, i;
	Vector3 p0, p1, p2, N;
	z = location.x + 500;
	x = location.z + 500;
	cx = (MAXLOC*2) / float(cols);
	cz = (MAXLOC*2) / float(rows);
	qk = z/cz;
	qi = x/cx;
	fk = qk - floor(qk);
	fi = qi - floor(qi);
	k = floor(qk);
	i = floor(qi);

	float t1,t2,t3;
	if( (fk + fi) < 1)
	{
		p0.set(i*cx, heightmap[k][i], k*cz);
		p1.set(i*cx, heightmap[k+1][i], (k+1)*cz);
		p2.set((i+1)*cz, heightmap[k][i+1], k*cz);
		N = (p1-p0).crossProduct((p2-p0));
		t1=heightmap[k][i];
		t2=heightmap[k+1][i];
			t3=heightmap[k][i+1];
	}
	else
	{
		p1.set(i*cx, heightmap[k+1][i], (k+1)*cz);
		p2.set((i+1)*cx, heightmap[k][i+1], k*cz);
		p0.set((i+1)*cx, heightmap[k+1][i+1], (k+1)*cz);
		N = (p2-p0).crossProduct((p1-p0));
		t1=heightmap[k+1][i+1];
		t2=heightmap[k+1][i];
		t3=heightmap[k][i+1];
	}
	y = (-N.x*x - N.z*z + N.dotProduct(p0))/N.y;

	if((location.y-sphere) < y)	//collision
	{
		location.y = y+sphere;		//location and known good value is used as previous locations here can lead to fish spawning under the ground and never emerging.
		current_velocity = current_velocity - 2*(current_velocity.projection(N));
	}
}

