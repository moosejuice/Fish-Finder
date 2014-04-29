#ifndef FISH_H
#define FISH_H
#include "ObjLibrary\Vector3.h"
#include <vector>

/*
Fish.isCaptured:	Added Jan 15/14 to avoid deletion of vector elements. May come in handy in the future.
*/

class Fish {
public:
	struct Fish_Distance {
		std::vector<Fish>::pointer fish_ptr;
	//std::vector<Fish> fish_ptr;
		float distance;
	};
	Vector3 location;
	Vector3 previous_location;
	int red, blue, green;	//for color of fish
	int fish_type;			//to allow for different types of fish
	bool isCaptured;		//indicates if the fish has been captured yet. 
	int point_value;				//Default 3. point value of the fish, for the games point system. will be determined based upon fish_type
	float mass;				// in kg
	float speed;			// in m/s
	float acceleration;		//in m/s^2	
	//float flock_distance_max;	//in m
	//int flock_count_min;
	int flock_count;
	float max_speed;		//in m/s
	float FISH_NEIGHBOR_MAX_DISTANCE;
	int FISH_NEIGHBOR_MAX_COUNT;
	float FISH_COHESION_WEIGHT;
	float FISH_ALIGNMENT_WEIGHT;
	float FISH_SEPARATION_WEIGHT;
	float FISH_SEPARATION_MAX_DISTANCE;
	Vector3 current_velocity;
	Vector3 target_velocity;
	Vector3 delta_velocity;
	float fish_radius;
	//std::vector<Fish*> fish_in_flock;
	std::vector<Fish_Distance> nearest_fish;

	void draw(void);
	bool in_viewport;

	static bool sort_help(const Fish_Distance&, const Fish_Distance&);

};

void generate_fish(void);			//generates a random number of fish in range 100,200 in a random world location with random color
void add_fish(void);		//generates 1 new fish
void remove_fish(void);		//removes 1 fish
Fish random_fish(void);


#endif