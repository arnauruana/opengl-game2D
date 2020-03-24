#include "Level.h"


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

	if (!this->loadMap())
	{
		std::cerr << "[LEVEL::init] error while loading map" << std::endl;
		exit(EXIT_FAILURE);
	}
}

void Level::update(int deltaTime)
{
	this->updatePlayer(deltaTime);
	this->updateObjects(deltaTime);
}

void Level::render()
{
	this->renderObjects();
	this->renderPlayer();
}


bool Level::loadMap()
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
				if (obj == "baba")
				{
					this->player = new Player();
					this->player->init(glm::ivec2(0, 0), this->shader);
					this->player->setPosition(glm::vec2(c * spriteSize, r * spriteSize));
				}
				else
				{
					Object* object = Object::create();
					objects.push_back(object);

					if (obj == "rock") object->setType(Object::Type::ROCK);
					if (obj == "flag") object->setType(Object::Type::FLAG);
					if (obj == "wall") object->setType(Object::Type::WALL);

					object->setShader(this->shader);
					object->init();
					object->setPosition(glm::vec2(c * spriteSize, r * spriteSize));
				}
			}
		}
	}

	return true;
}


void Level::updatePlayer(int deltaTime)
{
	this->player->update(deltaTime);
}

void Level::renderPlayer()
{
	this->shader.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	this->player->render();
}


void Level::updateObjects(int deltaTime)
{
	for (int i = 0; i < objects.size(); ++i)
	{
		objects[i]->update(deltaTime);
		collision(objects[i], player);
	}
}

void Level::renderObjects()
{
	for (int i = 0; i < objects.size(); ++i)
	{
		objects[i]->render();
	}
}


void Level::collision(Object* object, Player* player)
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
			Settings::playing = false; // DEBUG
			break;
		}
		default:
		{
			exit(1);
		}
		}
	}
}