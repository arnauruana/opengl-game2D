#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE


#include "Scene.h"


class Game
{
public:

	static const GLuint GAME_WINDOW_WIDTH = 480;
	static const GLuint GAME_WINDOW_HEIGHT = 480;

	static const GLuint FPS = 60;

public:
		
	Game();
	~Game();
	
	static Game& instance()
	{
		static Game game;
		return game;
	}

	void init();
	bool update(int deltaTime);
	void render();
	void resize(int width, int height);

	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);

private:

	inline void toggleFullScreen();
	inline void enableFullScreen();
	inline void disableFullScreen();

	inline void saveWindowContext();
	inline void restoreWindowContext() const;

private:

	GLboolean exit;
	GLboolean windowF;

	GLuint windowH;
	GLuint windowW;
	GLuint windowX;
	GLuint windowY;

	Scene scene;
};


#endif // _GAME_INCLUDE