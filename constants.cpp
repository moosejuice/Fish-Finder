#pragma once
#include "constants.h"

void constants::init_constants(void)
{
	///update rates///
	slow_ai_update_rate = 0.01f;
	physics_update_rate = 100.0;		//per sercond
	fast_ai_update_rate = 40.0;		//per second
}

float constants::get_slow_ai_update_rate(void)
{
	return slow_ai_update_rate;
}

float constants::get_physics_update_rate(void)
{
	return physics_update_rate;
}

float constants::get_fast_ai_update_rate(void)
{
	return fast_ai_update_rate;
}

