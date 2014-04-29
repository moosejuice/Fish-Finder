#ifndef SHARK_H
#define SHARK_H
#include "ObjLibrary\Vector3.h"
#include "ObjLibrary/ObjModel.h"
#include "ObjLibrary/DisplayList.h"
#include "fish.h"

class Shark {
	friend void keyboard(unsigned char, int, int);
	friend class Camera;
public:
	void init_shark(void);
	void load_shark(void);
	void draw(void);
	void fast_AI(int);
	void slow_AI(void);
	void physics(int);
	void collision_detection(void);
	std::vector<Fish::Fish_Distance> nearest_fish;

protected:
	Vector3 location;
	Vector3 direction;		//initial direction of model. what rotation is in respect too.
	Vector3 steering_vector;
	Vector3 velocity;
	Vector3 previous_location;
	Vector3 explore_target;

	ObjModel sharkObj;
	DisplayList shark_list;

	bool escort_mode;
	float speed;
	std::vector<Fish>::pointer target_fish;			//pointer to sharks target fish. NULL if no target.
	float MASS;
	float MAX_SPEED;
	float ACCELERATION;
	float RADIUS;
	float ESCORT_DISTANCE;
	float ARRIVAL_SLOW_DISTANCE;
	float DETECT_FISH_RADIUS;
	float EXPLORE_CLOSE_ENOUGH;
	float PURSUIT_LOOK_AHEAD_FACTOR;
	int slow_AI_counter;

	void pick_explore_target(void);
};




#endif