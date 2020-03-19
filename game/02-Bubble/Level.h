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

private:

	TileMap* map;

	Player* player;

	ShaderProgram shader;
};


#endif // _LEVEL_INCLUDE