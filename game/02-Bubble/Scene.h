#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include "Level.h"
#include "Menu.h"
#include "Play.h"
#include "Player.h"


class Scene
{
public:

	enum class State { MENU, PLAY };

public:

	Scene();
	~Scene();

	void setState(State state);
	void setLevel(int level);

	void init();
	void update(int deltaTime);
	void render();

private:

	Scene::State state = Scene::State::MENU;

	Menu menu;
	Play play;

	GLfloat currentTime;
	glm::mat4 projection;
	ShaderProgram texProgram;
};


#endif // _SCENE_INCLUDE