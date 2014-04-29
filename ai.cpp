#pragma once
#include "ai.h"
#include "global_variables.h"
#include "game.h"
#include "temp_inc_game.h"
#include <algorithm>

void AI::fast_fish_ai(int time_interval)		//pass a time interval in ms
{
	Vector3 desired_velocity_change;
	for (std::vector<Fish>::iterator it = game.myFish.begin(); it != game.myFish.end(); it++)
	{
		if(it->in_viewport || true)		//only update if in viewport, or in culling distance
		{
			if(!it->nearest_fish.empty())		//only do flocking if the fish has neighbors. else skip it and just move towards target velocity.
			{
				Vector3 separation, alignment, cohesion;
				separation = cohesion = alignment = Vector3::ZERO;
				int count = 0;
				for(std::vector<Fish::Fish_Distance>::iterator flock_ptr = it->nearest_fish.begin(); flock_ptr != it->nearest_fish.end(); flock_ptr++)
				{
					if ((*flock_ptr).fish_ptr->location != (*flock_ptr).fish_ptr->location)
					{
						std::cout << "SHIT HAS HIT THE FAN\n";
						(*flock_ptr).fish_ptr->location.set(0,100,0);
						(*flock_ptr).fish_ptr->current_velocity.set(0.1,0.1,0.1);
						return;
					}

					Vector3 distVect, co_vector;
					float replusion_weight, distance, alignment_repulsion, cohesion_repulsion, co_distance;
					distVect = it->location - (*flock_ptr).fish_ptr->location;
					co_vector = (*flock_ptr).fish_ptr->location - it->location;
					co_distance = co_vector.getNorm();
					distance = distVect.getNorm();
					if(distance < it->FISH_SEPARATION_MAX_DISTANCE)
					{
						replusion_weight = (it->FISH_SEPARATION_MAX_DISTANCE - distance)/it->FISH_SEPARATION_MAX_DISTANCE;
						replusion_weight *= replusion_weight;
					}	
					else
						replusion_weight = 0;
					if(distance < it->FISH_NEIGHBOR_MAX_DISTANCE)
						alignment_repulsion = (it->FISH_NEIGHBOR_MAX_DISTANCE - distance) / it->FISH_NEIGHBOR_MAX_DISTANCE;
					else
						alignment_repulsion = 0;
					if(co_distance < it->FISH_NEIGHBOR_MAX_DISTANCE)
					{
						cohesion_repulsion = (it->FISH_NEIGHBOR_MAX_DISTANCE - co_distance) / it->FISH_NEIGHBOR_MAX_DISTANCE;
						cohesion_repulsion *= cohesion_repulsion;
					}
					else
						cohesion_repulsion = 0;

					alignment += (alignment_repulsion * (*flock_ptr).fish_ptr->current_velocity);

					if( distance <= it->FISH_NEIGHBOR_MAX_DISTANCE)
						separation += ( -replusion_weight * distVect ) / distance;
					else
						separation += ( replusion_weight * distVect ) / distance;

					if( co_distance <= it->FISH_SEPARATION_MAX_DISTANCE )
						cohesion += ( -cohesion_repulsion * co_vector ) / co_distance;
					else
						cohesion += ( cohesion_repulsion * co_vector ) / co_distance;

					count++;
					if (count <= it->FISH_NEIGHBOR_MAX_COUNT)
						break;
				}
				if (count == 0)
				{
					std::cout << "BAD THINGS HAPPENED\n";
					break;
				}

				alignment += it->current_velocity;
				it->target_velocity = ( (it->FISH_SEPARATION_WEIGHT * separation) + (it->FISH_COHESION_WEIGHT * cohesion) + (it->FISH_ALIGNMENT_WEIGHT * alignment)).getNormalized();
				it->speed = it->max_speed;
			}
			desired_velocity_change = it->target_velocity*it->speed*time_interval/1000 - it->current_velocity*it->speed*time_interval/1000;

			if(desired_velocity_change.getNorm() > (it->acceleration*time_interval/1000))
			{
				desired_velocity_change.normalize();
				desired_velocity_change *= it->acceleration*time_interval/1000;
			}
			it->current_velocity += desired_velocity_change;
		}
	}
}

void AI::slow_fish_ai(int FishToUpdate)		
{
	for(int i = 0; i < FishToUpdate; i++)
	{
		slow_ai_iterator->flock_count = 0;
		slow_ai_iterator->nearest_fish.clear();

		if(slow_ai_iterator->in_viewport)
		{
			for (std::vector<Fish>::iterator it = game.myFish.begin(); it != game.myFish.end(); it++)
			{
				if(it->fish_type == slow_ai_iterator->fish_type)		//fish only flock with similar fish.
				{
					float t = it->location.getDistance(slow_ai_iterator->location);
					if(t < slow_ai_iterator->FISH_NEIGHBOR_MAX_DISTANCE && it != slow_ai_iterator)		//dont add fish to its own neighbor list
					{
						/*
						float angle1, angle;
						angle1 = cos(location.dotProduct(it->location)/(location.getNorm() * it->location.getNorm()));
						angle = acos(angle1);
						if (angle < 0 && angle > 11*pi/6)
							std::cout << angle*RadToDeg << " " << angle1*RadToDeg << std::endl;
						if( (angle > 0 && angle < (pi/6)) || (angle < 0 && angle > 11*pi/6) )
						*/
						//float angle1, angle;
						//angle1 = cos(slow_ai_iterator->location.dotProduct(it->location)/(it->location.getNorm() * slow_ai_iterator->location.getNorm()));
						//angle = acos(angle1);
						//if (angle < 0 && angle > 11*pi/6)
						//	std::cout << "FISH: " <<  angle*RadToDeg << " " << angle1*RadToDeg << std::endl;
						//if( (angle > 0 && angle < (pi/6)) || (angle < 0 && angle > 11*pi/6) )		//fish can see. give a flock a distinct leader
						//{
							Fish::Fish_Distance temp;
							temp.distance = t;
							temp.fish_ptr = it._Ptr;
							slow_ai_iterator->nearest_fish.push_back(temp);	
							slow_ai_iterator->flock_count++;
	//					}
					}
				}
			}
			sort(slow_ai_iterator->nearest_fish.begin(), slow_ai_iterator->nearest_fish.end(), slow_ai_iterator->sort_help );

			if(slow_ai_iterator->flock_count == 0)		//no neighbours. all alone
			{
				slow_ai_iterator->target_velocity = slow_ai_iterator->target_velocity.getRandomUnitVector();
				slow_ai_iterator->speed = slow_ai_iterator->max_speed;
			}
		}

		if (slow_ai_iterator == game.myFish.end())	//if just checked end, wrap around. else increment.
			slow_ai_iterator = game.myFish.begin();
		else
			slow_ai_iterator++;
	}
}