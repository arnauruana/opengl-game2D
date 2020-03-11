#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();
	
	void initMenu();
	void updateMenu(int deltaTime);
	
	void initCredits();
	void updateCredits(int deltaTime);

	void initControls();
	void updateControls(int deltaTime);

	void init_Lvl1();
	void init_Lvl2();
	void init_Lvl3();
	void init_Lvl4();
	void init_Lvl5();

private:
	void initShaders();

private:
	TileMap *map;
	Player *player;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	Texture spritesheet, spritesheetSelector, spritesheetCredits, spritesheetControls;
	Sprite *sprite, *spriteSelector, *spriteCredits, *spriteControls;
	string state = "menu";  // {menu,controls,playing,credits)
	int current_lvl = 1; //{1,2,3,4,5}
};


#endif // _SCENE_INCLUDE

