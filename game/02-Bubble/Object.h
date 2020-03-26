#ifndef _OBJECT_INCLUDE
#define _OBJECT_INCLUDE


#include "Settings.h"
#include "ShaderProgram.h"
#include "Sprite.h"
#include "Texture.h"

#include <iostream>


class Object
{
public:

	enum class Type
	{
		NONE,

		FLAG,
		LAVA,
		ROCK,
		WALL,
		WATER,

		TXT_BABA,
		TXT_FLAG,
		TXT_LAVA,
		TXT_ROCK,
		TXT_WALL,
		TXT_WATER,

		TXT_IS,
		TXT_NEAR,

		TXT_DEFEAT,
		TXT_PUSH,
		TXT_STOP,
		TXT_WIN,
		TXT_YOU,
	};

	enum class Behaviour
	{
		NONE,

		DEFEAT,
		PUSH,
		STOP,
		WIN,
		YOU,

		PRE,
		OP,
		POST,
	};

public:

	Object();
	~Object();

	static Object* create();

	Object::Type getType() const;
	Object::Behaviour getBehaviour() const;
	glm::ivec2 getPosition() const;

	void setBehaviour(Object::Behaviour behaviour);
	void setPosition(const glm::vec2& position);
	void setShader(const ShaderProgram& shader);
	void setType(Object::Type type);

	void init();
	void update(int deltaTime);
	void render();

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