Created by Chris Arnold.
Program was created using Visual Studio Professional 2012.
	Windows 7 Professional 64bit
	OpenGL with GLUT
HUD:
	Top left corner, the values from top to bottom are:
		1) Co-ordinates
		2) Buoyancy value
		3) Velocity vector

Movement:
	w/W - Move Submarine forward(Full thrust)
	s/S - Move Submarine backwards(Reverse thrust)
	a/A - Rotate Submarine Counter-Clock-Wise (Left)
	d/D - Rotate Submarine Clock-Wise (Right)
	Up Arrow - Increase Buoyancy (to move towards surface)
	Down Arrow - Decrease Buoyancy (To descent to ocean floor)
	Left Arrow - Rotate camera clockwise
	Right Arrow - Rotate camera counter-clockwise
	PgUp - Boost sub up
	PgDn - Boost sub down

	When camera rotates movement keys act in the same way
	Buoyancy of 1.000 will maintain altitude
	1  - the '1' key instantly sets buoyancy to 1.000 value.

Keyboard Controls:
	Esc - Exit Game.
	f/F - Toggle FPS display.
	c/C - Toggle Co-ordinate display.
	v/V - Toggle HUD/All onscreen text. 
	
	b/B - Toggle fish vs fish collision detection.

	2   - Set camera mode to free(manual rotation with arrow keys).
	3   - Set camera to behind sub(will always be directly behind the sub).
	4   - Set camera to follow the shark.

	y/Y - Increase physics update rate (DISABLED)
	h/H - Decrease physics update rate (DISABLED)
	u/U - Increase fast AI update rate (DISABLED)
	j/J - Decrease fast AI update rate (DISABLED)
	i/I - Increase slow AI update fraction (DISABLED)
	k/K - Decrease slow AI update fraction (DISABLED)
	R   - Toggle display of physics and AI update rates.(DISABLED)
	p/P - Toggle points display. (DISABLED)
	o/O - Toggle Fish Counter. (DISABLED)
	r   - Reset the camera (REPLACED) Accomplished now by 2
	L   - Toggle debug mode. Currently this disables the 10 fish capture limit. Also shows additional information. (DISABLED)
	G/g - Remove a fish from the world (DISABLED)
	T/t - Add a fish to the world (DISABLED)
	p/P - Show collision spheres (DISABLED)
	;   - Don't show collision spheres (DISABLED)
	o   _ Enable Fog (DISABLED)
	l   - Disable Fog (DISABLED)

	

To Win:
	When 10 Fish are captured, the game exits.