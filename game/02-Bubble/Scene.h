#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>

#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"


const int MENU = 1;
const int CONT = 2;
const int CRED = 3;
const int PLAY = 4;

const int LVL1 = 1;
const int LVL2 = 2;
const int LVL3 = 3;
const int LVL4 = 4;
const int LVL5 = 5;

const int DEFAULT_STATE = MENU;
const int DEFAULT_LEVEL = LVL1;

const string PATH_LVL1 = "levels/level01.txt";
const string PATH_LVL2 = "levels/level02.txt";
const string PATH_LVL3 = "levels/level03.txt";
const string PATH_LVL4 = "levels/level04.txt";
const string PATH_LVL5 = "levels/level05.txt";


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{
public:
	Scene();
	~Scene();

	int getState();
	int getLevel();

	void setState(int state);
	void setLevel(int level);

	void init();
	void update(int deltaTime);
	void render();
	
	void initMenu();
	void updateMenu(int deltaTime);
	void renderMenu();
	
	void initControls();
	void updateControls(int deltaTime);
	void renderControls();

	void initCredits();
	void updateCredits(int deltaTime);
	void renderCredits();

	void initPlay();
	void updatePlay(int deltaTime);
	void renderPlay();

	void initLevel1();
	void updateLevel1(int deltaTime);
	void renderLevel1();

	void initLevel2();
	void updateLevel2(int deltaTime);
	void renderLevel2();

private:
	void initShaders();

private:
	GLfloat currentTime;
	glm::mat4 projection;
	ShaderProgram texProgram;

	Texture spritesheetMenu;
	Texture spritesheetControls;
	Texture spritesheetCredits;
	Texture spritesheetSelector;

	Sprite* spriteMenu;
	Sprite* spriteControls;
	Sprite* spriteCredits;
	Sprite* spriteSelector;
	
	TileMap* map1;
	TileMap* map2;
	TileMap* map3;
	TileMap* map4;
	TileMap* map5;

	Player* player1;
	Player* player2;
	Player* player3;
	Player* player4;
	Player* player5;

	GLint state = DEFAULT_STATE;	// { MENU | CONT | CRED | PLAY }
	GLint level = DEFAULT_LEVEL;	// { LVL1 | LVL2 | LVL3 | LVL4 | LVL5 }

	glm::vec2 selectorPos = glm::vec2(480.f / 7.f, 235.f);
};


#endif // _SCENE_INCLUDE

