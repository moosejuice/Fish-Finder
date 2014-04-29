#pragma once
#include "submarine.h"
#include "glut.h"
#include "global_variables.h"
#include "game.h"
#include "temp_inc_game.h"
#include "collision_detection.h"


void Submarine::init_sub(void)
{
	subObj.load("submarine/submarine.obj");
	sub_list = subObj.getDisplayList();

	
	DRAG = 0.6;
	SUBMARINE_MASS = 100.0;
	GRAVITY = -9.8;
	BUOYANT_FORCE = 980.0;
	ENGINE_FORCE = 5000.0;
	TURN_RATE = 120.0;	//in degrees
	BUOYANCY_MIN = 0.1;
	BUOYANCY_RATE = 0.25;
	BUOYANCY_MAX = 1.5;
	TILT_MIN = 10.0; 
	TILT_MAX = -5.0;	//in degrees
	subSphereRadius = 3.0;			//m
	subSphereMaxDistance = 9.0;		//m
	sphereCount = 5;
	subOuterRadius = subSphereMaxDistance + subSphereRadius;

	sub_collison_spheres_list = glGenLists(2);
	glNewList(sub_collison_spheres_list, GL_COMPILE);
		glPushMatrix();
			glTranslatef(-9, 0, 0);
			glutWireSphere(subSphereRadius, 5, 10);	
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-4.5, 0, 0);
			glutWireSphere(subSphereRadius, 5, 10);	
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0, 0, 0);
			glutWireSphere(subSphereRadius, 5, 10);	
		glPopMatrix();
		glPushMatrix();
			glTranslatef(4.5, 0, 0);
			glutWireSphere(subSphereRadius, 5, 10);	
		glPopMatrix();
		glPushMatrix();
			glTranslatef(9, 0, 0);
			glutWireSphere(subSphereRadius, 5, 10);	
		glPopMatrix();
	glEndList();

	
}

void Submarine::reset_sub(void)
{
	location.set(0.0, 50.0, 0.0);
	previous_location = location;
	velocity.set(0,0,0);
	direction.set(1,0,0);

	buoyancy = 1.0;		//float in place
	increase_buoyancy = false;
	decrease_buoyancy = false;
	turn_CCW = false;
	turn_CW = false;
	rotation = 0;
	increase_velocity = false;
	decrease_velocity = false;
	collision1 = collision2 = collision3 = collision4 = Vector3::ZERO;
}


void Submarine::draw(void)
{
	glPushMatrix();
		glTranslatef(location.x, location.y, location.z);
		glRotatef(rotation, 0.0, 1.0, 0.0);
		glRotatef(vertical_rotation, 0.0, 0.0, 1.0);
		sub_list.draw();
	glPopMatrix();
	if(game.get_show_collision_spheres())
	{
		glPushMatrix();
			glColor3ub(188,198,204);
			glTranslatef(location.x, location.y, location.z);
			glRotatef(rotation, 0.0, 1.0, 0.0);
			glRotatef(vertical_rotation, 0.0, 0.0, 1.0);
			glutWireSphere(subOuterRadius, 10, 20);
		glPopMatrix();

		glPushMatrix();
			glColor3ub(188,198,204);
			glTranslatef(location.x, location.y, location.z);
			glRotatef(rotation, 0.0, 1.0, 0.0);
			glCallList(sub_collison_spheres_list);
		glPopMatrix();

	}
	//glPushMatrix();
	//	glColor3ub(255, 0, 0);
	//	glTranslatef(collision1.x, collision1.y, collision1.z);
	//	glutWireSphere(subSphereRadius, 15, 25);
	//glPopMatrix();
	//	glPushMatrix();
	//	glColor3ub(255, 0, 0);
	//	glTranslatef(collision2.x, collision2.y, collision2.z);
	//	glutWireSphere(subSphereRadius, 15, 25);
	//glPopMatrix();
	//	glPushMatrix();
	//	glColor3ub(255, 0, 0);
	//	glTranslatef(collision3.x, collision3.y, collision3.z);
	//	glutWireSphere(subSphereRadius, 15, 25);
	//glPopMatrix();
	//	glPushMatrix();
	//	glColor3ub(255, 0, 0);
	//	glTranslatef(collision4.x, collision4.y, collision4.z);
	//	glutWireSphere(subSphereRadius, 15, 25);
	//glPopMatrix();
	
}
void Submarine::update_buoyancy(int delta_time)
{
	if(increase_buoyancy)
	{
		buoyancy += BUOYANCY_RATE * delta_time / 1000;
		increase_buoyancy = false;
	}
	if(decrease_buoyancy)
	{
		buoyancy -= BUOYANCY_RATE * delta_time / 1000;
		decrease_buoyancy = false;
	}

	if( buoyancy > BUOYANCY_MAX )
		buoyancy = BUOYANCY_MAX;
	if( buoyancy < BUOYANCY_MIN)
		buoyancy = BUOYANCY_MIN;

	vertical_rotation = -(TILT_MIN + (buoyancy-BUOYANCY_MIN)*(TILT_MAX-TILT_MIN)/(BUOYANCY_MAX-BUOYANCY_MIN));
}

float Submarine::get_subSphereRadius(void)
{
	return subSphereRadius;
}

bool Submarine::get_increase_velocity(void)
{
	return increase_velocity;
}

bool Submarine::get_decrease_velocity(void)
{
	return decrease_velocity;
}

void Submarine::set_increase_velocity(bool value)
{
	increase_velocity = value;
}

void Submarine::set_decrease_velocity(bool value)
{
	decrease_velocity = value;
}

bool Submarine::get_increase_buoyancy(void)
{
	return increase_buoyancy;
}

bool Submarine::get_decrease_buoyancy(void)
{
	return decrease_buoyancy;
}

void Submarine::set_increase_buoyancy(bool value)
{
	increase_buoyancy = value;
}

void Submarine::set_decrease_buoyancy(bool value)	
{
	decrease_buoyancy = value;
}

float Submarine::get_buoyancy(void)
{
	return buoyancy;
}

void Submarine::set_buoyancy(float value)
{
	buoyancy = value;
}

float Submarine::get_DRAG(void)
{
	return DRAG;
}

float Submarine::get_GRAVITY(void)
{
	return GRAVITY;
}

float Submarine::get_BUOYANT_FORCE(void)
{
	return BUOYANT_FORCE;
}

float Submarine::get_ENGINE_FORCE(void)
{
	return ENGINE_FORCE;
}

float Submarine::get_TURN_RATE(void)	//in degrees
{
	return TURN_RATE;
}

float Submarine::get_BUOYANCY_MIN(void)
{
	return BUOYANCY_MIN;
}

float Submarine::get_BUOYANCY_RATE(void)
{
	return BUOYANCY_RATE;
}

float Submarine::get_BUOYANCY_MAX(void)
{
	return BUOYANCY_MAX;
}

float Submarine::get_TILT_MIN(void)
{
	return TILT_MIN;
}

float Submarine::get_TILT_MAX(void)		//in degrees
{
	return TILT_MAX;
}

float Submarine::get_SUBMARINE_MASS(void)
{
	return SUBMARINE_MASS;
}

void Submarine::set_turn_CCW(bool value)
{
	turn_CCW = value;
}

void Submarine::set_turn_CW(bool value)
{
	turn_CW = value;
}

Vector3 Submarine::get_location(void)
{
	return location;
}

Vector3 Submarine::get_velocity(void)
{
	return velocity;
}

float Submarine::get_rotation(void)
{
	return rotation;
}

float Submarine::get_subOuterRadius(void)
{
	return subOuterRadius;
}



void Submarine::check_world_bounds(void)
{
	//sub vs surface
	//if( (location.x + subOuterRadius) > MAXLOC)
	//{
	//	location.x = MAXLOC - subOuterRadius;
	//	velocity.x *= -1;
	//}
	//if( (location.x - subOuterRadius) < MINLOC)
	//{
	//	location.x = MINLOC + subOuterRadius;
	//	velocity.x *= -1;
	//}
	//
	if( (location.y) > MAXLOCY)		//ensure the sub does not exit ocean
	{
		location.y = MAXLOCY;
		velocity.y *= -1;
		//set_buoyancy(1.0);				//also set buoyancy to a neutral value
	}
	//if( (location.y + subOuterRadius) > MAXLOCY)		//ensure the sub does not exit ocean
	//{
	//	location.y = MAXLOCY - subOuterRadius;
	//	velocity.y *= -1;
	//	set_buoyancy(1.0);				//also set buoyancy to a neutral value
	//}
	//if( (location.z + subOuterRadius) > MAXLOC)
	//{
	//	location.z = MAXLOC - subOuterRadius;
	//	velocity.z *= -1;
	//}
	//if( (location.z - subOuterRadius) < MINLOC)
	//{
	//	location.z = MINLOC + subOuterRadius;
	//	velocity.z *= -1;
	//}

	if(location.x > MAXLOC)
		location.x = MINLOC;
	if(location.x < MINLOC)
		location.x = MAXLOC;

	if(location.z > MAXLOC)
		location.z = MINLOC;
	if(location.z < MINLOC)
		location.z = MAXLOC;

	//sub vs ground	
	game.object_vs_ground(location, subOuterRadius, velocity);

}



void Submarine::update_physics(int delta_time)
{
	previous_location=location;

	update_buoyancy(delta_time);		//update and check bounds on buoyancy
	
	//calculate buoyancy/gravity on vertical axis
	velocity.y = velocity.y + (GRAVITY * delta_time/1000) + (BUOYANT_FORCE/SUBMARINE_MASS* buoyancy*delta_time/1000);

	
	//calculate force of the engine on forward velocities
	if(increase_velocity)
	{
		//std::cout << "Forward Velocity calculated\n";
		velocity += direction.getRotatedY(rotation*pi/180) * (ENGINE_FORCE / SUBMARINE_MASS) * delta_time/1000;
		//increase_velocity = false;
	}
	if(decrease_velocity)
	{
		//std::cout << "Reverse Velocity calculated\n";
		velocity -= direction.getRotatedY(rotation*pi/180) * (ENGINE_FORCE / SUBMARINE_MASS) * delta_time/1000;
		//decrease_velocity = false;
	}
		
	check_rotation(delta_time);	
	
	velocity = velocity * pow(DRAG, float(delta_time)/1000.0);		//calculate drag
	//update the subs location
	location = (velocity * delta_time/1000) + location;
}



void Submarine::check_rotation(int delta_time)
{
		//check rotation of submarine
	if(turn_CCW)
	{
		//std::cout << "Rotation calculated\n";
		float degrees;
		degrees = TURN_RATE * delta_time/1000;
		//rotate velocity ccw by this amount of degrees
		turn_CCW = false;
		rotation += degrees;
	}
	if(turn_CW)
	{
		//std::cout << "Rotation calculated\n";
		float degrees = TURN_RATE * delta_time/1000;
		//rotate velocity cw by this amount degrees
		turn_CW = false;
		rotation -= degrees;
	}

		collision1.set(
			location.x + (sin((rotation+90)*degToRad)*cos(vertical_rotation*degToRad)*4.5), 
			location.y + (sin(vertical_rotation*degToRad)*4.5), 
			location.z + (cos((rotation+90)*degToRad)*cos(vertical_rotation*degToRad)*4.5));
		collision2.set(
			location.x - (sin((rotation+90)*degToRad)*cos(vertical_rotation*degToRad)*4.5), 
			location.y - (sin(vertical_rotation*degToRad)*4.5), 
			location.z - (cos((rotation+90)*degToRad)*cos(vertical_rotation*degToRad)*4.5));
		collision3.set(
			location.x + (sin((rotation+90)*degToRad)*cos(vertical_rotation*degToRad)*9), 
			location.y + (sin(vertical_rotation*degToRad)*9), 
			location.z + (cos((rotation+90)*degToRad)*cos(vertical_rotation*degToRad)*9));
		collision4.set(
			location.x - (sin((rotation+90)*degToRad)*cos(vertical_rotation*degToRad)*9), 
			location.y - (sin(vertical_rotation*degToRad)*9), 
			location.z - (cos((rotation+90)*degToRad)*cos(vertical_rotation*degToRad)*9));

	
}





