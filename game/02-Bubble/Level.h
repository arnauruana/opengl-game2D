#ifndef _LEVEL_INCLUDE
#define _LEVEL_INCLUDE


#include "Object.h"
#include "Player.h"
#include "Sounds.h"

#include <GL/glut.h>

#include <iostream>
#include <fstream>
#include <vector>


class Level
{
public:

	Level();
	~Level();

	void setPath(const std::string& path);
	void setShader(const ShaderProgram& shader);

	void init();
	void update(int deltaTime);
	void render();

private:

	bool loadMap();
	void cleanMap();

	void assignBehaviours();
	void collision(Object* object, Object* player);
	bool collision(Object* object);
	Object* find(int posX, int posY) const;

private:

	bool updateBehaviour = false;
	bool babaIsYou;

	std::string path;

	Player* player;
	std::vector<Object*> objects;

	ShaderProgram shader;
};


#endif // _LEVEL_INCLUDE