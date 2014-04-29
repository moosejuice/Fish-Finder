#pragma once
#include "gradient.h"
#include <algorithm>
#include <cmath>

//using namespace std;
/*
Adapted from http://stackoverflow.com/questions/8732401/how-to-figure-out-all-colors-in-a-gradient
to create function to calculate the specific color codes in a gradient
*/
color makeGradient(float percent)
{
	color newColor;
	color topColor = { 64, 224, 208 };
	color bottomColor = { 0, 0, 0 };
	newColor.red = makeChannel(topColor.red, bottomColor.red, percent);
	newColor.blue = makeChannel(topColor.blue, bottomColor.blue, percent);
	newColor.green = makeChannel(topColor.green, bottomColor.green, percent);

	return newColor;
}

float makeChannel(float x, float y, float percent)
{
	float ret = (y + (x-y)*(percent));
	ret = std::min(ret, float(255));
	ret = std::max(ret, float(0));
	return float(ret)/255;
}