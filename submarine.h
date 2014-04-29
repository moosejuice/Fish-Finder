#ifndef SUBMARINE_H
#define SUBMARINE_H
#include "ObjLibrary/Vector3.h"
#include "ObjLibrary/ObjModel.h"
#include "ObjLibrary/DisplayList.h"
#include "glut.h"

class Submarine {
public:
	friend class collision_detection;
	friend class Camera;
	friend class Shark;
	friend class Display;
	friend void special(int special_key, int x, int y);
	//functions
	void init_sub(void);
	void draw(void);
	void update_buoyancy(int);		//takes in delta time
	void check_rotation(int);		//takes in delta time
	void update_physics(int);		//physics update for the submarine
	void check_world_bounds(void);	//makes sure the submarine hasnt gone somewhere it shouldnt
	void reset_sub(void);

	//setters
	void set_increase_velocity(bool);
	void set_decrease_velocity(bool);
	void set_increase_buoyancy(bool);
	void set_decrease_buoyancy(bool);
	void set_buoyancy(float);
	void set_turn_CCW(bool);
	void set_turn_CW(bool);

	//getters
	bool get_increase_velocity(void);
	bool get_decrease_velocity(void);
	bool get_increase_buoyancy(void);
	bool get_decrease_buoyancy(void);
	float get_DRAG(void);
	float get_GRAVITY(void);
	float get_BUOYANT_FORCE(void);
	float get_ENGINE_FORCE(void);
	float get_TURN_RATE(void);	//in degrees
	float get_BUOYANCY_MIN(void); 
	float get_BUOYANCY_RATE(void); 
	float get_BUOYANCY_MAX(void);
	float get_TILT_MIN(void); 
	float get_TILT_MAX(void);	//in degrees
	float get_SUBMARINE_MASS(void);	
	float get_buoyancy(void);
	float get_subSphereRadius(void);
	float get_subOuterRadius(void);
	Vector3 get_location(void);
	Vector3 get_velocity(void);
	float get_rotation(void);
	


private:
	ObjModel subObj;
	DisplayList sub_list;

	Vector3 location;
	Vector3 previous_location;

	float rotation;			//in degrees about initial direction of object, (1,0,0) in this case
	float vertical_rotation;	//in degrees

	Vector3 velocity;
	Vector3 direction;

	Vector3 collision1, collision2, collision3, collision4;

	//movement control variables
	float buoyancy;	
	bool increase_buoyancy;
	bool decrease_buoyancy;
	bool increase_velocity;
	bool decrease_velocity;
	bool turn_CCW;
	bool turn_CW;

	//constants
	float DRAG;
	float GRAVITY;
	float BUOYANT_FORCE;
	float ENGINE_FORCE;
	float TURN_RATE;	//in degrees
	float BUOYANCY_MIN, BUOYANCY_RATE, BUOYANCY_MAX;
	float TILT_MIN, TILT_MAX;	//in degrees
	float SUBMARINE_MASS;		//in kg

	float subSphereRadius;
	float subSphereMaxDistance;
	int sphereCount;
	float subOuterRadius;

	GLuint sub_collison_spheres_list;
};



#endif