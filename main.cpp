#include <stdlib.h>
#include "glut.h"
#include "prototypes.h"
#include "keyboard_operations.h"
#include "game.h"
//#include "global_variables.h"
#include "temp_inc_game.h"

int main(int argc, char** argv)
{
	// initialize OpenGL; pass it the command line arguments
	glutInit(&argc, argv);	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  // single is default
	glutInitWindowSize(500, 500);  // default is 300 x 300
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Fish Finder v0.6");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	//glutDisplayFunc(game.display);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyUp);
	glutSpecialFunc(special);
	glutSpecialUpFunc(keySpecialUp);
	glutIdleFunc(idle);
	//glutIdleFunc(game.update);
	init();
	glutMainLoop();
	return 1;
}

