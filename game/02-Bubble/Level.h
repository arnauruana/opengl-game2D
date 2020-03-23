#ifndef _LEVEL_INCLUDE
#define _LEVEL_INCLUDE


#include "Object.h"
#include "Player.h"

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

private:

	bool loadObjects();

private:

	Player* player;
	std::vector<Object*> objects;

	ShaderProgram shader;
};


#endif // _LEVEL_INCLUDE