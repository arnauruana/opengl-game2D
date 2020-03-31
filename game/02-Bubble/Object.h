#ifndef _OBJECT_INCLUDE
#define _OBJECT_INCLUDE


#include "Keyboard.h"
#include "Settings.h"
#include "ShaderProgram.h"
#include "Sprite.h"
#include "Texture.h"

#include <GL/glut.h>

#include <iostream>


class Object
{
public:

	enum class Type
	{
		NONE,

		BABA,
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
		TXT_YOU
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

	enum class Direction
	{
		BACKWARD,
		FORWARD,
		LEFT,
		RIGHT,
	};

	enum Baba
	{
		MOVE_BACKWARD,
		MOVE_FORWARD,
		MOVE_LEFT,
		MOVE_RIGHT,
	};

public:

	Object();
	~Object();

	static Object* create();

	Object::Behaviour getBehaviour() const;
	Object::Direction getDirection() const;
	Object::Type getType() const;
	glm::ivec2 getPosition() const;

	void setBehaviour(Object::Behaviour behaviour);
	void setDirection(Object::Direction direction);
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

	Object::Direction direction;

	Sprite* sprite;
	Texture texture;

	std::string path;
	Settings::Format format;

	ShaderProgram shader;
};


#endif // _OBJECT_INCLUDE