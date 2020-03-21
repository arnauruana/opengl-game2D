#ifndef _LEVEL_INCLUDE
#define _LEVEL_INCLUDE


#include "Player.h";
#include "TileMap.h"

#include <vector>


class Level
{
public:

	Level();
	~Level();

	void setShader(const ShaderProgram& shader);

	void init();
	void update(int deltaTime);
	void render();

public:

	bool loadMap();


private:

	TileMap* map;

	Player* player;

	ShaderProgram shader;
};


#endif // _LEVEL_INCLUDE