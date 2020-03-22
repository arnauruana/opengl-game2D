#include "Level.h"

#include <GL/glut.h>

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
	glutSetWindowTitle("WINDOW IS GAME");

	this->player = new Player();
	this->player->init(glm::ivec2(0, 0), this->shader);
	this->player->setPosition(glm::vec2(6 * 24, 9 * 24));

	this->loadObjects();
}

void collision(Object* object, Player* player)
{
	glm::vec2 posObj = object->getPosition();
	glm::vec2 posPlayer = player->getPosition();

	if (posObj.x == posPlayer.x && posObj.y == posPlayer.y)
	{
		switch (object->getBehaviour())
		{
			case Object::Behaviour::STOP:
			{
				switch (player->getAnimation())
				{
					case MOVE_FORWARD:
					{
						player->setPosition(glm::vec2(posPlayer.x, posPlayer.y - 24));
						break;
					}
					case MOVE_BACKWARD:
					{
						player->setPosition(glm::vec2(posPlayer.x, posPlayer.y + 24));
						break;
					}
					case MOVE_RIGHT:
					{
						player->setPosition(glm::vec2(posPlayer.x - 24, posPlayer.y));
						break;
					}
					case MOVE_LEFT:
					{
						player->setPosition(glm::vec2(posPlayer.x + 24, posPlayer.y));
						break;
					}
					default:
					{
						exit(1);
					}
				}
				break;
			}
			case Object::Behaviour::PUSH:
			{
				switch (player->getAnimation())
				{
					case MOVE_FORWARD:
					{
						object->setPosition(glm::vec2(posPlayer.x, posPlayer.y + 24));
						break;
					}
					case MOVE_BACKWARD:
					{
						object->setPosition(glm::vec2(posPlayer.x, posPlayer.y - 24));
						break;
					}
					case MOVE_RIGHT:
					{
						object->setPosition(glm::vec2(posPlayer.x + 24, posPlayer.y));
						break;
					}
					case MOVE_LEFT:
					{
						object->setPosition(glm::vec2(posPlayer.x - 24, posPlayer.y));
						break;
					}
					default:
					{
						exit(1);
					}
				}
				break;
			}
			case Object::Behaviour::WIN:
			{
				exit(0);
			}
			default:
			{
				exit(1);
			}
		}
	}
}

void Level::update(int deltaTime)
{
	this->player->update(deltaTime);

	for (int i = 0; i < objects.size(); ++i)
	{
		objects[i]->update(deltaTime);
		collision(objects[i], player);
	}

	// COLLISIONS //


}

void Level::render()
{
	for (int i = 0; i < objects.size(); ++i)
	{
		objects[i]->render();
	}

	this->shader.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f); // white => baba
	this->player->render();
}


bool Level::loadObjects()
{
	ifstream fin("levels/1.txt");

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

	int spriteSize;
	fin >> spriteSize;

	std::string obj;
	for (int r = 0; r < mapHeight; ++r)
	{
		for (int c = 0; c < mapWidth; ++c)
		{
			fin >> obj;

			if (obj != "none")
			{
				Object* object = Object::create();
				objects.push_back(object);

				if (obj == "rock")
				{
					object->setType(Object::Type::ROCK);
					object->setShader(this->shader);
				}

				if (obj == "flag")
				{
					object->setType(Object::Type::FLAG);
					object->setShader(this->shader);
				}

				if (obj == "wall")
				{
					object->setType(Object::Type::WALL);
					object->setShader(this->shader);
				}

				object->init();
				object->setPosition(glm::vec2(c * spriteSize, r * spriteSize));
			}
		}
	}

	return true;
}