#ifndef _OBJECT_INCLUDE
#define _OBJECT_INCLUDE


#include "Settings.h"
#include "ShaderProgram.h"
#include "Sprite.h"
#include "TileMap.h"
#include "Texture.h"

#include <iostream>


class Object
{
public:

	enum class Type
	{
		FLAG,
		ROCK,
		WALL,
	};

	enum class Behaviour
	{
		KILL,
		MOVE,
		NONE,
		PUSH,
		STOP,
		WIN,
	};

public:

	static Object* create();

	Object::Behaviour getBehaviour();
	glm::ivec2 getPosition();

	void setBehaviour(Object::Behaviour behaviour);
	void setPosition(const glm::vec2& position);
	void setShader(const ShaderProgram& shader);
	void setType(Object::Type type);

	void init();
	void update(int deltaTime);
	void render();

private:

	Object();
	~Object();

private:

	Object::Type type;
	Object::Behaviour behaviour;

	glm::vec3 color;

	Sprite* sprite;
	Texture texture;

	std::string path = Settings::PATH_OBJECTS;
	Settings::Format format;
	
	ShaderProgram shader;
};


#endif // _OBJECT_INCLUDE