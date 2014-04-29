#pragma once
#include "camera.h"
#include "global_variables.h"
#include <math.h>
#include "glut.h"
#include "temp_inc_game.h"
void Camera::display_camera(void)
{
	switch (camera_mode){
	case 0:
		gluLookAt(
			mySub.location.x + 40.0*cos(camera_rotation*degToRad), 20.0+mySub.location.y, mySub.location.z + 40*sin(camera_rotation*degToRad),		// x,y,z of eye
			mySub.location.x, mySub.location.y, mySub.location.z,		// x,y,z of look at point
			0.0, 1.0, 0.0);		// x,y,z of up vector
		break;
	case 1:
		//mySub.rotation - 90;
		gluLookAt(
			mySub.location.x + 40.0*cos(-(mySub.rotation-180)*degToRad), 20.0+mySub.location.y, mySub.location.z + 40*sin(-(mySub.rotation-180)*degToRad),		// x,y,z of eye
			mySub.get_location().x, mySub.get_location().y, mySub.get_location().z,		// x,y,z of look at point
			0.0, 1.0, 0.0);		// x,y,z of up vector
		break;
	case 2:
		gluLookAt(
			game.myShark.location.x + 40.0*cos(-(game.myShark.velocity.getRotationY())-pi/2), 20.0+game.myShark.location.y, game.myShark.location.z + 40*sin(-(game.myShark.velocity.getRotationY())-pi/2),		// x,y,z of eye
			game.myShark.location.x, game.myShark.location.y, game.myShark.location.z,		// x,y,z of look at point
			0.0, 1.0, 0.0);		// x,y,z of up vector
		break;
	}

}

void Camera::init_camera(void)
{
	set_camera_free();
	camera_rotation = 90;
}

void Camera::set_camera_free(void)
{
	camera_mode = 0;
	camera_rotation = -(mySub.rotation+180);
}


