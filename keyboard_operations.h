#ifndef KEYBOARD_OPERATIONS_H
#define KEYBOARD_OPERATIONS_H

void keyboardOperations(void);			//defines what to do for each specific key-press. Movement keys defined here.
void keyUp(unsigned char, int, int);	//process the release of a key
void keySpecialUp(int, int, int);		//precess the release of a special key
void keyboard(unsigned char, int, int);		//processes the keydown event		Toggle keys defined here
void special(int, int, int);				//processes the special keydown event


#endif