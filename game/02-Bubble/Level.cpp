#include "Level.h"

#include <fstream>
#include <iostream>
#include <vector>


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


void Level::init()
{

}

void Level::update(int deltaTime)
{

}

void Level::render()
{

}


bool Level::loadMap()
{
	ifstream fin("levels/map1.txt");

	if (!fin.is_open())
	{
		return false;
	}

	std::string header;
	fin >> header;
	if (header != "MAP")
	{
		return false;
	}

	int mapWidth, mapHeight;
	fin >> mapWidth >> mapHeight;

	int sizeSprite, sizeBlock;
	fin >> sizeSprite >> sizeBlock;

	std::vector<std::vector<std::string> > map(mapWidth, std::vector<string>(mapHeight));

	for (int i = 0; i < map.size(); ++i)
	{
		for (int j = 0; j < map.at(0).size(); ++j)
		{
			fin >> map.at(i).at(j);
		}
	}

	return true;
}