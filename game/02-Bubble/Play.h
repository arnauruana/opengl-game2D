#ifndef _PLAY_INCLUDE
#define _PLAY_INCLUDE


#include "Level.h"
//#include "Settings.h"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>


class Play
{
public:

	enum class State { LEVEL1, LEVEL2, LEVEL3, LEVEL4, LEVEL5 };

public:

	Play();
	~Play();

	void init();
	void update(int deltaTime);
	void render();

private:

	void initShader();

private:

	Play::State state;

	Level level1;
	Level level2;
	Level level3;
	Level level4;
	Level level5;

	ShaderProgram shader;
};


#endif // _PLAY_INCLUDE