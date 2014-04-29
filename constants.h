#ifndef CONSTANTS_H
#define CONSTANTS_H

class constants {
public:
	void init_constants(void);
	float get_slow_ai_update_rate(void);
	float get_physics_update_rate(void);
	float get_fast_ai_update_rate(void);

protected:
		///update rates///
	float slow_ai_update_rate;		//per fast AI update
	float physics_update_rate;		//per sercond
	float fast_ai_update_rate;		//per second
};



#endif