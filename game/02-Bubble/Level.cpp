#include "Level.h"


Level::Level()
{
	this->map = NULL;
	this->player = NULL;
}

Level::~Level()
{
	if (this->map != NULL) delete this->map;
	if (this->player != NULL) delete this->player;
}


void Level::setShader(const ShaderProgram& shader)
{
	this->shader = shader;
}