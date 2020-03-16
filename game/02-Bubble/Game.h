#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE


#include "Scene.h"


#define SCREEN_WIDTH  480
#define SCREEN_HEIGHT 480


class Game
{
public:

	typedef unsigned int uint;

	static const uint DEFAULT_WINDOW_WIDTH = 480;
	static const uint DEFAULT_WINDOW_HEIGHT = 480;

	static const uint FPS = 60;

public:

	Game() {}
	
	
	static Game &instance()
	{
		static Game G;
	
		return G;
	}
	
	void init();
	bool update(int deltaTime);
	void render();
	
	// Input callback methods
	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);
	void mouseMoved(int x, int y);
	void mousePressed(int button);
	void mouseReleased(int button);
	
	bool getKey(int key) const;
	bool getSpecialKey(int key) const;

private:

	bool bPlay;                       // Continue to play game?
	Scene scene;                      // Scene to render
	bool keys[256], specialKeys[256]; // Store key states so that 
	                                  // we can have access at any time
};


#endif // _GAME_INCLUDE


