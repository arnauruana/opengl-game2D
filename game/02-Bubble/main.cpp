#include "Game.h"

#include <GL/glew.h>
#include <GL/glut.h>


const float TPF = 1000.f / Game::FPS;

int prevTime;


void idleCallback()
{
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	int deltaTime = currentTime - prevTime;

	if (deltaTime >= TPF)
	{
		if (!Game::instance().update(deltaTime))
		{
			exit(EXIT_SUCCESS);
		}

		prevTime = currentTime;
		glutPostRedisplay();
	}
}

void drawCallback()
{
	Game::instance().render();
}

void resizeCallback(int width, int height)
{
	Game::instance().resize(width, height);
}


void keyboardDownCallback(unsigned char key, int x, int y)
{
	Game::instance().keyPressed(key);
}

void keyboardUpCallback(unsigned char key, int x, int y)
{
	Game::instance().keyReleased(key);
}

void specialDownCallback(int key, int x, int y)
{
	Game::instance().specialKeyPressed(key);
}

void specialUpCallback(int key, int x, int y)
{
	Game::instance().specialKeyReleased(key);
}


void mouseCallback(int button, int state, int x, int y)
{
	switch (state)
	{
	case GLUT_DOWN:
		Game::instance().mousePressed(button);
		break;
	case GLUT_UP:
		Game::instance().mouseReleased(button);
		break;
	default:
		exit(EXIT_FAILURE);
	}
}

void motionCallback(int x, int y)
{
	Game::instance().mouseMoved(x, y);
}


inline void initWindow(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(Game::GAME_WINDOW_WIDTH, Game::GAME_WINDOW_HEIGHT);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - Game::GAME_WINDOW_WIDTH) / 2,
		(glutGet(GLUT_SCREEN_HEIGHT) - Game::GAME_WINDOW_HEIGHT) / 2);
	glutCreateWindow("WINDOW IS GAME");
	
	//glutSetCursor(GLUT_CURSOR_NONE);
}

inline void initFunctions()
{
	glutIdleFunc(idleCallback);
	glutDisplayFunc(drawCallback);
	glutReshapeFunc(resizeCallback);

	glutKeyboardFunc(keyboardDownCallback);
	glutKeyboardUpFunc(keyboardUpCallback);
	glutSpecialFunc(specialDownCallback);
	glutSpecialUpFunc(specialUpCallback);

	glutMouseFunc(mouseCallback);
	glutMotionFunc(motionCallback);
	glutPassiveMotionFunc(motionCallback);
}


inline void initGlut(int argc, char** argv)
{
	initWindow(argc, argv);
	initFunctions();
}

inline void initGlew()
{
	glewExperimental = GL_TRUE;
	glewInit();
}

inline void initGame()
{
	Game::instance().init();
}


inline void start()
{
	prevTime = glutGet(GLUT_ELAPSED_TIME);
	glutMainLoop();
}


int main(int argc, char** argv)
{
	initGlut(argc, argv);
	initGlew();
	initGame();

	start();
}