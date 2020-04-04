#ifndef _OBJECT_INCLUDE
#define _OBJECT_INCLUDE


#include "Keyboard.h"
#include "Settings.h"
#include "ShaderProgram.h"
#include "Sounds.h"
#include "Sprite.h"
#include "Texture.h"

#include <GL/glut.h>

#include <iostream>


class Object
{
public:

	inline static bool moved = false;

	bool dead = false;
	bool isFluid = false;

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

		TXT_IS,
		TXT_MAKE,

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
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT,
	};

	enum Animation
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

	int getAnimation() const;
	Object::Behaviour getBehaviour() const;
	Object::Direction getDirection() const;
	Object::Type getMake() const;
	Object::Type getType() const;
	glm::ivec2 getPosition() const;

	void setBehaviour(Object::Behaviour behaviour);
	void setDirection(Object::Direction direction);
	void setMake(Object::Type object);
	void setPosition(const glm::vec2& position);
	void setShader(const ShaderProgram& shader);
	void setType(Object::Type type);
	void setTexture(int caso);
	void move(Object::Direction direction);

	void init();
	void update(int deltaTime);
	void render();

private:

	Object::Behaviour behaviour;
	Object::Direction direction;
	Object::Type type;
	Object::Type make = Object::Type::NONE;
	glm::vec3 color;

	Sprite* sprite;
	Texture texture;

	std::string path;
	Settings::Format format;

	ShaderProgram shader;
};


#endif // _OBJECT_INCLUDE