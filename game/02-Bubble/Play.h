#ifndef _PLAY_INCLUDE
#define _PLAY_INCLUDE


#include "Level.h"

#include <iostream>


class Play
{
public:

	enum class State { LEVEL1, LEVEL2, LEVEL3, LEVEL4, LEVEL5 };

public:

	Play();
	~Play();

	void setShader(const ShaderProgram& shader);

	void init();
	void update(int deltaTime);
	void render();

private:

	Play::State state = Play::State::LEVEL1;

	Level level1;
	Level level2;
	Level level3;
	Level level4;
	Level level5;

	ShaderProgram shader;
};


#endif // _PLAY_INCLUDE