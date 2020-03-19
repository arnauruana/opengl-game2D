#ifndef _OBJECT_INCLUDE
#define _OBJECT_INCLUDE


#include "ShaderProgram.h"
#include "Sprite.h"
#include "TileMap.h"
#include "Texture.h"


class Object
{
public:

	enum Type
	{
		ROCK,
		FLAG,
		FLOOR,
	};

public:

	Object();
	~Object();

	void setMap(TileMap* map);
	void setShader(const ShaderProgram& shader);
	void setType(Object::Type type);

	void init();
	void update(int deltaTime);
	void render();

private:

	Object::Type type;
	glm::ivec2 position;

	TileMap* map;

	Sprite* sprite;
	Texture texture;
	
	ShaderProgram shader;
};


#endif // _OBJECT_INCLUDE