#ifndef GRADIENT_H
#define GRADIENT_H

struct color		//define a color as red, blue and green portions
{
	float red;
	float blue;
	float green;
};

/*
//define top and bottom color of the world, calculate the new color based upon the percentage passed in.
*/
color makeGradient(float);						

/*
calculate the individual color components based upon the top/bottom color and the percent depth. ensure the
color values are in range. 
*/
float makeChannel(float, float, float);			


#endif

