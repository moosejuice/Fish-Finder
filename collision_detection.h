#ifndef COLLISION_DETECTION_H
#define COLLISION_DETECTION_H
//#include "fish.h"
//#include "global_variables.h"
#include "ObjLibrary\Vector3.h"

class collision_detection {

public:
	void fish_collision_detection(void);
	//void sub_collision_detection(void);
	void check_fish_culling(void);
	float sub_fish_rad_squared;
	static void object_vs_ground(Vector3&, float, Vector3&, Vector3&);		//location vector and collision sphere size. Will check for ground collision
	static void object_vs_ground(Vector3&, float, Vector3&);
};

#endif
