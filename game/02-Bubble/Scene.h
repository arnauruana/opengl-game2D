#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include "Level.h"
#include "Menu.h"
#include "Play.h"
#include "Player.h"

#include <glm/gtc/matrix_transform.hpp>

#include <cmath>
#include <iostream>


const int MENU = 1;
const int PLAY = 2;

const int LVL1 = 1;
const int LVL2 = 2;
const int LVL3 = 3;
const int LVL4 = 4;
const int LVL5 = 5;

const int DEFAULT_STATE = PLAY;
const int DEFAULT_LEVEL = LVL1;


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

	void initPlay();
	void updatePlay(int deltaTime);
	void renderPlay();

	void initLevel2();
	void updateLevel2(int deltaTime);
	void renderLevel2();

private:

	void initShaders();

private:

	Scene::State state = Scene::State::MENU;

	GLint level = DEFAULT_LEVEL;

	Player* player1;
	Player* player2;

	GLfloat currentTime;
	ShaderProgram texProgram;
	
	glm::mat4 projection;

	Menu menu;

	Level map;
};


#endif // _SCENE_INCLUDE