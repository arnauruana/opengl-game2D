#include "Level.h"

#include <iostream>
#include <fstream>


Level::Level()
{
	this->player = NULL;
}

Level::~Level()
{
	if (this->player != NULL) delete this->player;
}


void Level::setShader(const ShaderProgram& shader)
{
	this->shader = shader;
}


void Level::init()
{
	this->loadObjects();
}

void Level::update(int deltaTime)
{
	for (int i = 0; i < objects.size(); ++i)
	{
		objects[i]->update(deltaTime);
	}
}

void Level::render()
{
	for (int i = 0; i < objects.size(); ++i)
	{
		objects[i]->render();
	}
}


bool Level::loadObjects()
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

	string obj;
	int i = 0;
	for (int r = 0; r < mapHeight; ++r)
	{
		for (int c = 0; c < mapWidth; ++c)
		{
			fin >> obj; cout << obj << endl;

			if (obj != "none")
			{
				objects.push_back(Object::create());

				if (obj == "rock")
				{
					objects[i]->setType(Object::Type::ROCK);
					objects[i]->setBehaviour(Object::Behaviour::PUSH);
					objects[i]->setShader(this->shader);
				}

				if (obj == "flag")
				{
					objects[i]->setType(Object::Type::FLAG);
					objects[i]->setBehaviour(Object::Behaviour::WIN);
					objects[i]->setShader(this->shader);
				}

				objects[i]->init();
				objects[i]->setPosition(glm::vec2(r * sizeSprite, c * sizeSprite));

				++i;
			}
		}
	}

	return true;
}