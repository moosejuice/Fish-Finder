#ifndef CAMERA_H
#define CAMERA_H

class Camera
{
	//friend void keyboard(unsigned char, int, int);
	friend void keyboardOperations(void);
public:
	void display_camera(void);
	void init_camera(void);
	void set_camera_free(void);

protected:
	int camera_mode;	//0 free(control with arrows), 1 always behind sub
	float camera_rotation;	//degrees
};


#endif