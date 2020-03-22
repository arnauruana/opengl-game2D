#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE


#include "Scene.h"

#include <GL/glut.h>


class Game
{
public:

	typedef unsigned int uint;

	static const uint GAME_WINDOW_WIDTH = 480;
	static const uint GAME_WINDOW_HEIGHT = 480;

	static const uint FPS = 60;

public:
		
	Game();
	~Game();
	
	static Game& instance()
	{
		static Game game;
		return game;
	}
	
	bool getKey(int key) const;
	bool getSpecialKey(int key) const;

	void init();
	bool update(int time);
	void render();
	void resize(int width, int height);

	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);

	void mousePressed(int button);
	void mouseReleased(int button);
	void mouseMoved(int x, int y);

private:

	void toggleFullScreen();
	void enableFullScreen();
	void disableFullScreen();

	void saveWindowContext();
	void restoreWindowContext();

private:

	bool playing;

	bool key[256];
	bool skey[256];

	bool windowF;
	uint windowH;
	uint windowW;
	uint windowX;
	uint windowY;

	Scene scene;
};


#endif // _GAME_INCLUDE